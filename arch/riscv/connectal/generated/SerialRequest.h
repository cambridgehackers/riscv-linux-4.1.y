#include "GeneratedTypes.h"
#ifndef _SERIALREQUEST_H_
#define _SERIALREQUEST_H_
#include "portal.h"

class SerialRequestProxy : public Portal {
    SerialRequestCb *cb;
public:
    SerialRequestProxy(int id, int tile = DEFAULT_TILE, SerialRequestCb *cbarg = &SerialRequestProxyReq, int bufsize = SerialRequest_reqinfo, PortalPoller *poller = 0) :
        Portal(id, tile, bufsize, NULL, NULL, this, poller), cb(cbarg) {};
    SerialRequestProxy(int id, PortalTransportFunctions *transport, void *param, SerialRequestCb *cbarg = &SerialRequestProxyReq, int bufsize = SerialRequest_reqinfo, PortalPoller *poller = 0) :
        Portal(id, DEFAULT_TILE, bufsize, NULL, NULL, transport, param, this, poller), cb(cbarg) {};
    SerialRequestProxy(int id, PortalPoller *poller) :
        Portal(id, DEFAULT_TILE, SerialRequest_reqinfo, NULL, NULL, NULL, NULL, this, poller), cb(&SerialRequestProxyReq) {};
    int tx ( const uint8_t c ) { return cb->tx (&pint, c); };
};

extern SerialRequestCb SerialRequest_cbTable;
class SerialRequestWrapper : public Portal {
public:
    SerialRequestWrapper(int id, int tile = DEFAULT_TILE, PORTAL_INDFUNC cba = SerialRequest_handleMessage, int bufsize = SerialRequest_reqinfo, PortalPoller *poller = 0) :
           Portal(id, tile, bufsize, cba, (void *)&SerialRequest_cbTable, this, poller) {
    };
    SerialRequestWrapper(int id, PortalTransportFunctions *transport, void *param, PORTAL_INDFUNC cba = SerialRequest_handleMessage, int bufsize = SerialRequest_reqinfo, PortalPoller *poller=0):
           Portal(id, DEFAULT_TILE, bufsize, cba, (void *)&SerialRequest_cbTable, transport, param, this, poller) {
    };
    SerialRequestWrapper(int id, PortalPoller *poller) :
           Portal(id, DEFAULT_TILE, SerialRequest_reqinfo, SerialRequest_handleMessage, (void *)&SerialRequest_cbTable, this, poller) {
    };
    SerialRequestWrapper(int id, PortalTransportFunctions *transport, void *param, PortalPoller *poller):
           Portal(id, DEFAULT_TILE, SerialRequest_reqinfo, SerialRequest_handleMessage, (void *)&SerialRequest_cbTable, transport, param, this, poller) {
    };
    virtual void disconnect(void) {
        printf("SerialRequestWrapper.disconnect called %d\n", pint.client_fd_number);
    };
    virtual void tx ( const uint8_t c ) = 0;
};
#endif // _SERIALREQUEST_H_
