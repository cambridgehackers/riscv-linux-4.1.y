#include "GeneratedTypes.h"

int BlockDevResponse_transferDone ( struct PortalInternal *p, const uint32_t tag )
{
    volatile unsigned int* temp_working_addr_start = p->transport->mapchannelReq(p, CHAN_NUM_BlockDevResponse_transferDone, 2);
    volatile unsigned int* temp_working_addr = temp_working_addr_start;
    if (p->transport->busywait(p, CHAN_NUM_BlockDevResponse_transferDone, "BlockDevResponse_transferDone")) return 1;
    p->transport->write(p, &temp_working_addr, tag);
    p->transport->send(p, temp_working_addr_start, (CHAN_NUM_BlockDevResponse_transferDone << 16) | 2, -1);
    return 0;
};

BlockDevResponseCb BlockDevResponseProxyReq = {
    portal_disconnect,
    BlockDevResponse_transferDone,
};
BlockDevResponseCb *pBlockDevResponseProxyReq = &BlockDevResponseProxyReq;

const uint32_t BlockDevResponse_reqinfo = 0x10008;
const char * BlockDevResponse_methodSignatures(void)
{
    return "{\"transferDone\": [\"long\"]}";
}

int BlockDevResponse_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd)
{
    static int runaway = 0;
    int   tmp __attribute__ ((unused));
    int tmpfd __attribute__ ((unused));
    BlockDevResponseData tempdata __attribute__ ((unused));
    volatile unsigned int* temp_working_addr = p->transport->mapchannelInd(p, channel);
    memset(&tempdata, 0, sizeof(tempdata));
    switch (channel) {
    case CHAN_NUM_BlockDevResponse_transferDone: {
        
        p->transport->recv(p, temp_working_addr, 1, &tmpfd);
        tmp = p->transport->read(p, &temp_working_addr);
        tempdata.transferDone.tag = (uint32_t)(((tmp)&0xfffffffful));((BlockDevResponseCb *)p->cb)->transferDone(p, tempdata.transferDone.tag);
      } break;
    default:
        PORTAL_PRINTF("BlockDevResponse_handleMessage: unknown channel 0x%x\n", channel);
        if (runaway++ > 10) {
            PORTAL_PRINTF("BlockDevResponse_handleMessage: too many bogus indications, exiting\n");
#ifndef __KERNEL__
            exit(-1);
#endif
        }
        return 0;
    }
    return 0;
}
