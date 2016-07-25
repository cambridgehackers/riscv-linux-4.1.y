#include "GeneratedTypes.h"
#ifndef _SERIALINDICATION_H_
#define _SERIALINDICATION_H_
#include "portal.h"

class SerialIndicationProxy : public Portal {
    SerialIndicationCb *cb;
public:
    SerialIndicationProxy(int id, int tile = DEFAULT_TILE, SerialIndicationCb *cbarg = &SerialIndicationProxyReq, int bufsize = SerialIndication_reqinfo, PortalPoller *poller = 0) :
        Portal(id, tile, bufsize, NULL, NULL, this, poller), cb(cbarg) {};
    SerialIndicationProxy(int id, PortalTransportFunctions *transport, void *param, SerialIndicationCb *cbarg = &SerialIndicationProxyReq, int bufsize = SerialIndication_reqinfo, PortalPoller *poller = 0) :
        Portal(id, DEFAULT_TILE, bufsize, NULL, NULL, transport, param, this, poller), cb(cbarg) {};
    SerialIndicationProxy(int id, PortalPoller *poller) :
        Portal(id, DEFAULT_TILE, SerialIndication_reqinfo, NULL, NULL, NULL, NULL, this, poller), cb(&SerialIndicationProxyReq) {};
    int rx ( const uint8_t c ) { return cb->rx (&pint, c); };
};

extern SerialIndicationCb SerialIndication_cbTable;
class SerialIndicationWrapper : public Portal {
public:
    SerialIndicationWrapper(int id, int tile = DEFAULT_TILE, PORTAL_INDFUNC cba = SerialIndication_handleMessage, int bufsize = SerialIndication_reqinfo, PortalPoller *poller = 0) :
           Portal(id, tile, bufsize, cba, (void *)&SerialIndication_cbTable, this, poller) {
    };
    SerialIndicationWrapper(int id, PortalTransportFunctions *transport, void *param, PORTAL_INDFUNC cba = SerialIndication_handleMessage, int bufsize = SerialIndication_reqinfo, PortalPoller *poller=0):
           Portal(id, DEFAULT_TILE, bufsize, cba, (void *)&SerialIndication_cbTable, transport, param, this, poller) {
    };
    SerialIndicationWrapper(int id, PortalPoller *poller) :
           Portal(id, DEFAULT_TILE, SerialIndication_reqinfo, SerialIndication_handleMessage, (void *)&SerialIndication_cbTable, this, poller) {
    };
    SerialIndicationWrapper(int id, PortalTransportFunctions *transport, void *param, PortalPoller *poller):
           Portal(id, DEFAULT_TILE, SerialIndication_reqinfo, SerialIndication_handleMessage, (void *)&SerialIndication_cbTable, transport, param, this, poller) {
    };
    virtual void disconnect(void) {
        printf("SerialIndicationWrapper.disconnect called %d\n", pint.client_fd_number);
    };
    virtual void rx ( const uint8_t c ) = 0;
};
#endif // _SERIALINDICATION_H_
