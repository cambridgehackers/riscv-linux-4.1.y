#include <linux/init.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/genhd.h>
#include <linux/hdreg.h>
#include <linux/spinlock.h>
#include <linux/irqreturn.h>
#include <linux/module.h>

#include <asm/connectal.h>
#include "generated/portal.h"
#include "generated/GeneratedTypes.h"

static int blk_verbose = 0;
#define DRIVER_NAME "connectalblk"

#define SECTOR_SIZE_SHIFT	(9)
#define SECTOR_SIZE		(1UL << SECTOR_SIZE_SHIFT)

struct connectalblk_device {
	struct connectal_device *dev;
	struct gendisk *disk;
	volatile uint32_t *req_regs;
	volatile uint32_t *resp_regs;
	spinlock_t lock;
	u64 size;		/* size in bytes */
	struct request *req;
	unsigned int tag;
};

struct connectalblk_request {
	u64 addr;
	u64 offset;	/* offset in bytes */
	u64 size;	/* length in bytes */
	u64 tag;
} __packed;

static int major;

static int connectalblk_segment(struct connectalblk_device *dev,
				struct request *req)
{
	static struct connectalblk_request pkt;
	u64 offset, size, end;
	int err = 0;
	int i;
	PortalInternal *pint = 0;

	if (blk_verbose) printk("%s:%d rq_data_dir %d READ %d\n", __FUNCTION__, __LINE__, rq_data_dir(req), READ);
	offset = (blk_rq_pos(req) << SECTOR_SIZE_SHIFT);
	size = (blk_rq_cur_sectors(req) << SECTOR_SIZE_SHIFT);

	end = offset + size;
	if (unlikely(end < offset || end > dev->size)) {
		dev_err(&dev->dev->dev, "out-of-bounds access:"
			" offset=%llu size=%llu\n", offset, size);
		return -EINVAL;
	}

	rmb();
	pkt.addr = __pa(bio_data(req->bio));
	pkt.offset = offset;
	pkt.size = size;
	pkt.tag = dev->tag;

	dev->req = req;
	//FIXME use generated code
#if 0
	while (dev->req_regs[9] == 0)
		/* wait for not full */;
	
	dev->req_regs[8] = ((rq_data_dir(req) == READ) ? 0 : 1);
	dev->req_regs[8] = pkt.addr;
	dev->req_regs[8] = offset;
	dev->req_regs[8] = size;
	dev->req_regs[8] = dev->tag;
#else
	BlockDevRequest_transfer(pint, ((rq_data_dir(req) == READ) ? 0 : 1), pkt.addr, offset, size, dev->tag);
#endif

	for (i = 0; i < 10; i++) {
		int notEmpty = dev->resp_regs[9];
		if (notEmpty)
			break;
	}

	//if (blk_verbose) printk("sent blockdev request resp.notEmpty=%x tag=%x\n", dev->resp_regs[9], dev->resp_regs[8]);
	if (blk_verbose) printk("sent blockdev request resp.notEmpty=%x\n", dev->resp_regs[9]);

	wmb();
	WARN_ON(__blk_end_request_cur(dev->req, err));
	dev->req = NULL;

	return 0;
}

static void connectalblk_request(struct request_queue *q)
{
	struct connectalblk_device *dev;
	struct request *req;
	int ret;

	dev = q->queuedata;
	if (dev->req != NULL)
		return;

	while ((req = blk_fetch_request(q)) != NULL) {
		if (req->cmd_type == REQ_TYPE_FS) {
			ret = connectalblk_segment(dev, req);
			if (unlikely(ret)) {
				WARN_ON(__blk_end_request_cur(req, ret));
				continue;
			}
			//blk_stop_queue(q);
			break;
		} else {
			blk_dump_rq_flags(req, DRIVER_NAME
				": ignored non-fs request");
			__blk_end_request_all(req, -EIO);
			continue;
		}
	}
}

static irqreturn_t connectalblk_isr(struct connectal_device *dev, sbi_device_message *msg)
{
	struct connectalblk_device *connectalblk_dev;
	irqreturn_t ret;
	int err;

	connectalblk_dev = dev_get_drvdata(&dev->dev);
	ret = IRQ_NONE;

	spin_lock(&connectalblk_dev->lock);
	if (unlikely(connectalblk_dev->req == NULL)) {
		dev_err(&dev->dev, "null request\n");
		goto out;
	}

	err = 0;
	if (unlikely(msg->data != connectalblk_dev->tag)) {
		dev_err(&dev->dev, "tag mismatch: expected=%u actual=%lu\n",
			connectalblk_dev->tag, msg->data);
		err = -EIO;
	}

	wmb();
	WARN_ON(__blk_end_request_cur(connectalblk_dev->req, err));
	connectalblk_dev->req = NULL;
	blk_start_queue(connectalblk_dev->disk->queue);
	ret = IRQ_HANDLED;
out:
	spin_unlock(&connectalblk_dev->lock);
	return ret;
}

static const struct block_device_operations connectalblk_fops = {
	.owner		= THIS_MODULE,
};

static int connectalblk_probe(struct device *dev)
{
	static unsigned int index = 0;
	static const char prefix[] = " size=";

	struct connectal_device *connectal_dev;
	struct connectalblk_device *connectalblk_dev;
	struct gendisk *disk;
	struct request_queue *queue;
	const char *str;
	u64 size;
	int ret;

	printk("%s:%d\n", __FUNCTION__, __LINE__);

	dev_info(dev, "detected disk\n");
	connectal_dev = to_connectal_dev(dev);

	str = strstr(connectal_dev->id, prefix);
#if 0
	// request size of block device
	if (unlikely(str == NULL
	    || kstrtou64(str + sizeof(prefix) - 1, 10, &size))) {
		dev_err(dev, "error determining size of disk\n");
		return -ENODEV;
	}
	if (unlikely(size & (SECTOR_SIZE - 1))) {
		dev_warn(dev, "disk size not a multiple of sector size:"
			" %llu\n", size);
	}
#else
	size = 174516224;
#endif
	ret = -ENOMEM;
	connectalblk_dev = devm_kzalloc(dev, sizeof(struct connectalblk_device), GFP_KERNEL);
	if (unlikely(connectalblk_dev == NULL))
		goto out;

	connectalblk_dev->size = size;
	connectalblk_dev->dev = connectal_dev;
	connectalblk_dev->tag = index;
	connectalblk_dev->req_regs = ioremap(0xc0005000, 0x1000);
	connectalblk_dev->resp_regs = ioremap(0xc0002000, 0x1000);

	spin_lock_init(&connectalblk_dev->lock);

	disk = alloc_disk(1);
	if (unlikely(disk == NULL))
		goto out;

	queue = blk_init_queue(connectalblk_request, &connectalblk_dev->lock);
	if (unlikely(queue == NULL))
		goto out_put_disk;

	queue->queuedata = connectalblk_dev;
	blk_queue_max_segments(queue, 1);
	blk_queue_dma_alignment(queue, CONNECTAL_ALIGN - 1);

	disk->queue = queue;
	disk->major = major;
	disk->minors = 1;
	disk->first_minor = 0;
	disk->fops = &connectalblk_fops;
	set_capacity(disk, size >> SECTOR_SIZE_SHIFT);
	snprintf(disk->disk_name, DISK_NAME_LEN - 1, "connectalblk%u", index++);

	connectalblk_dev->disk = disk;
	add_disk(disk);
	dev_info(dev, "added %s\n", disk->disk_name);

	ret = connectal_request_irq(connectal_dev, connectalblk_isr);
	if (unlikely(ret))
		goto out_del_disk;

	dev_set_drvdata(dev, connectalblk_dev);
	printk("%s:%d SUCCEEDED\n", __FUNCTION__, __LINE__);
	return 0;

out_del_disk:
	del_gendisk(disk);
	blk_cleanup_queue(disk->queue);
out_put_disk:
	put_disk(disk);
out:
	return ret;
}


static struct connectal_driver connectalblk_driver = {
	.type = "disk",
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.probe = connectalblk_probe,
	},
};

static int __init connectalblk_init(void)
{
	int ret;

	printk("%s:%d\n", __FUNCTION__, __LINE__);
	ret = register_blkdev(0, DRIVER_NAME);
	if (unlikely(ret < 0))
		return ret;
	major = ret;

	ret = connectal_register_driver(&connectalblk_driver);
	if (unlikely(ret))
		unregister_blkdev(0, DRIVER_NAME);

	printk("%s:%d ret=%d\n", __FUNCTION__, __LINE__, ret);
	return ret;
}

static void __exit connectalblk_exit(void)
{
	unregister_blkdev(major, DRIVER_NAME);
	connectal_unregister_driver(&connectalblk_driver);
}

module_init(connectalblk_init);
module_exit(connectalblk_exit);

MODULE_DESCRIPTION("CONNECTAL block driver");
MODULE_LICENSE("GPL");
