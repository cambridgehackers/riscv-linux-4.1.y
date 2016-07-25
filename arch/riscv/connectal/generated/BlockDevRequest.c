#include "GeneratedTypes.h"

int BlockDevRequest_transfer ( struct PortalInternal *p, const BlockDevOp op, const uint32_t dramaddr, const uint32_t offset, const uint32_t size, const uint32_t tag )
{
    volatile unsigned int* temp_working_addr_start = p->transport->mapchannelReq(p, CHAN_NUM_BlockDevRequest_transfer, 6);
    volatile unsigned int* temp_working_addr = temp_working_addr_start;
    if (p->transport->busywait(p, CHAN_NUM_BlockDevRequest_transfer, "BlockDevRequest_transfer")) return 1;
    p->transport->write(p, &temp_working_addr, op);
    p->transport->write(p, &temp_working_addr, dramaddr);
    p->transport->write(p, &temp_working_addr, offset);
    p->transport->write(p, &temp_working_addr, size);
    p->transport->write(p, &temp_working_addr, tag);
    p->transport->send(p, temp_working_addr_start, (CHAN_NUM_BlockDevRequest_transfer << 16) | 6, -1);
    return 0;
};

BlockDevRequestCb BlockDevRequestProxyReq = {
    portal_disconnect,
    BlockDevRequest_transfer,
};
BlockDevRequestCb *pBlockDevRequestProxyReq = &BlockDevRequestProxyReq;

const uint32_t BlockDevRequest_reqinfo = 0x10018;
const char * BlockDevRequest_methodSignatures(void)
{
    return "{\"transfer\": [\"long\", \"long\", \"long\", \"long\", \"long\"]}";
}

int BlockDevRequest_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd)
{
    static int runaway = 0;
    int   tmp __attribute__ ((unused));
    int tmpfd __attribute__ ((unused));
    BlockDevRequestData tempdata __attribute__ ((unused));
    volatile unsigned int* temp_working_addr = p->transport->mapchannelInd(p, channel);
    memset(&tempdata, 0, sizeof(tempdata));
    switch (channel) {
    case CHAN_NUM_BlockDevRequest_transfer: {
        
        p->transport->recv(p, temp_working_addr, 5, &tmpfd);
        tmp = p->transport->read(p, &temp_working_addr);
        tempdata.transfer.op = (BlockDevOp)(((tmp)&0x1ul));
        tmp = p->transport->read(p, &temp_working_addr);
        tempdata.transfer.dramaddr = (uint32_t)(((tmp)&0xfffffffful));
        tmp = p->transport->read(p, &temp_working_addr);
        tempdata.transfer.offset = (uint32_t)(((tmp)&0xfffffffful));
        tmp = p->transport->read(p, &temp_working_addr);
        tempdata.transfer.size = (uint32_t)(((tmp)&0xfffffffful));
        tmp = p->transport->read(p, &temp_working_addr);
        tempdata.transfer.tag = (uint32_t)(((tmp)&0xfffffffful));((BlockDevRequestCb *)p->cb)->transfer(p, tempdata.transfer.op, tempdata.transfer.dramaddr, tempdata.transfer.offset, tempdata.transfer.size, tempdata.transfer.tag);
      } break;
    default:
        PORTAL_PRINTF("BlockDevRequest_handleMessage: unknown channel 0x%x\n", channel);
        if (runaway++ > 10) {
            PORTAL_PRINTF("BlockDevRequest_handleMessage: too many bogus indications, exiting\n");
#ifndef __KERNEL__
            exit(-1);
#endif
        }
        return 0;
    }
    return 0;
}
