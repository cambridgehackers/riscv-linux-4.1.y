#include "GeneratedTypes.h"

int SerialIndication_rx ( struct PortalInternal *p, const uint8_t c )
{
    volatile unsigned int* temp_working_addr_start = p->transport->mapchannelReq(p, CHAN_NUM_SerialIndication_rx, 2);
    volatile unsigned int* temp_working_addr = temp_working_addr_start;
    if (p->transport->busywait(p, CHAN_NUM_SerialIndication_rx, "SerialIndication_rx")) return 1;
    p->transport->write(p, &temp_working_addr, c);
    p->transport->send(p, temp_working_addr_start, (CHAN_NUM_SerialIndication_rx << 16) | 2, -1);
    return 0;
};

SerialIndicationCb SerialIndicationProxyReq = {
    portal_disconnect,
    SerialIndication_rx,
};
SerialIndicationCb *pSerialIndicationProxyReq = &SerialIndicationProxyReq;

const uint32_t SerialIndication_reqinfo = 0x10008;
const char * SerialIndication_methodSignatures(void)
{
    return "{\"rx\": [\"long\"]}";
}

int SerialIndication_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd)
{
    static int runaway = 0;
    int   tmp __attribute__ ((unused));
    int tmpfd __attribute__ ((unused));
    SerialIndicationData tempdata __attribute__ ((unused));
    volatile unsigned int* temp_working_addr = p->transport->mapchannelInd(p, channel);
    memset(&tempdata, 0, sizeof(tempdata));
    switch (channel) {
    case CHAN_NUM_SerialIndication_rx: {
        
        p->transport->recv(p, temp_working_addr, 1, &tmpfd);
        tmp = p->transport->read(p, &temp_working_addr);
        tempdata.rx.c = (uint8_t)(((tmp)&0xfful));((SerialIndicationCb *)p->cb)->rx(p, tempdata.rx.c);
      } break;
    default:
        PORTAL_PRINTF("SerialIndication_handleMessage: unknown channel 0x%x\n", channel);
        if (runaway++ > 10) {
            PORTAL_PRINTF("SerialIndication_handleMessage: too many bogus indications, exiting\n");
#ifndef __KERNEL__
            exit(-1);
#endif
        }
        return 0;
    }
    return 0;
}
