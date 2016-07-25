#include "GeneratedTypes.h"

int SerialRequest_tx ( struct PortalInternal *p, const uint8_t c )
{
    volatile unsigned int* temp_working_addr_start = p->transport->mapchannelReq(p, CHAN_NUM_SerialRequest_tx, 2);
    volatile unsigned int* temp_working_addr = temp_working_addr_start;
    if (p->transport->busywait(p, CHAN_NUM_SerialRequest_tx, "SerialRequest_tx")) return 1;
    p->transport->write(p, &temp_working_addr, c);
    p->transport->send(p, temp_working_addr_start, (CHAN_NUM_SerialRequest_tx << 16) | 2, -1);
    return 0;
};

SerialRequestCb SerialRequestProxyReq = {
    portal_disconnect,
    SerialRequest_tx,
};
SerialRequestCb *pSerialRequestProxyReq = &SerialRequestProxyReq;

const uint32_t SerialRequest_reqinfo = 0x10008;
const char * SerialRequest_methodSignatures(void)
{
    return "{\"tx\": [\"long\"]}";
}

int SerialRequest_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd)
{
    static int runaway = 0;
    int   tmp __attribute__ ((unused));
    int tmpfd __attribute__ ((unused));
    SerialRequestData tempdata __attribute__ ((unused));
    volatile unsigned int* temp_working_addr = p->transport->mapchannelInd(p, channel);
    memset(&tempdata, 0, sizeof(tempdata));
    switch (channel) {
    case CHAN_NUM_SerialRequest_tx: {
        
        p->transport->recv(p, temp_working_addr, 1, &tmpfd);
        tmp = p->transport->read(p, &temp_working_addr);
        tempdata.tx.c = (uint8_t)(((tmp)&0xfful));((SerialRequestCb *)p->cb)->tx(p, tempdata.tx.c);
      } break;
    default:
        PORTAL_PRINTF("SerialRequest_handleMessage: unknown channel 0x%x\n", channel);
        if (runaway++ > 10) {
            PORTAL_PRINTF("SerialRequest_handleMessage: too many bogus indications, exiting\n");
#ifndef __KERNEL__
            exit(-1);
#endif
        }
        return 0;
    }
    return 0;
}
