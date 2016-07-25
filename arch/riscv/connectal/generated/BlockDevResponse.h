#include "GeneratedTypes.h"
#ifndef _BLOCKDEVRESPONSE_H_
#define _BLOCKDEVRESPONSE_H_
#include "portal.h"

class BlockDevResponseProxy : public Portal {
    BlockDevResponseCb *cb;
public:
    BlockDevResponseProxy(int id, int tile = DEFAULT_TILE, BlockDevResponseCb *cbarg = &BlockDevResponseProxyReq, int bufsize = BlockDevResponse_reqinfo, PortalPoller *poller = 0) :
        Portal(id, tile, bufsize, NULL, NULL, this, poller), cb(cbarg) {};
    BlockDevResponseProxy(int id, PortalTransportFunctions *transport, void *param, BlockDevResponseCb *cbarg = &BlockDevResponseProxyReq, int bufsize = BlockDevResponse_reqinfo, PortalPoller *poller = 0) :
        Portal(id, DEFAULT_TILE, bufsize, NULL, NULL, transport, param, this, poller), cb(cbarg) {};
    BlockDevResponseProxy(int id, PortalPoller *poller) :
        Portal(id, DEFAULT_TILE, BlockDevResponse_reqinfo, NULL, NULL, NULL, NULL, this, poller), cb(&BlockDevResponseProxyReq) {};
    int transferDone ( const uint32_t tag ) { return cb->transferDone (&pint, tag); };
};

extern BlockDevResponseCb BlockDevResponse_cbTable;
class BlockDevResponseWrapper : public Portal {
public:
    BlockDevResponseWrapper(int id, int tile = DEFAULT_TILE, PORTAL_INDFUNC cba = BlockDevResponse_handleMessage, int bufsize = BlockDevResponse_reqinfo, PortalPoller *poller = 0) :
           Portal(id, tile, bufsize, cba, (void *)&BlockDevResponse_cbTable, this, poller) {
    };
    BlockDevResponseWrapper(int id, PortalTransportFunctions *transport, void *param, PORTAL_INDFUNC cba = BlockDevResponse_handleMessage, int bufsize = BlockDevResponse_reqinfo, PortalPoller *poller=0):
           Portal(id, DEFAULT_TILE, bufsize, cba, (void *)&BlockDevResponse_cbTable, transport, param, this, poller) {
    };
    BlockDevResponseWrapper(int id, PortalPoller *poller) :
           Portal(id, DEFAULT_TILE, BlockDevResponse_reqinfo, BlockDevResponse_handleMessage, (void *)&BlockDevResponse_cbTable, this, poller) {
    };
    BlockDevResponseWrapper(int id, PortalTransportFunctions *transport, void *param, PortalPoller *poller):
           Portal(id, DEFAULT_TILE, BlockDevResponse_reqinfo, BlockDevResponse_handleMessage, (void *)&BlockDevResponse_cbTable, transport, param, this, poller) {
    };
    virtual void disconnect(void) {
        printf("BlockDevResponseWrapper.disconnect called %d\n", pint.client_fd_number);
    };
    virtual void transferDone ( const uint32_t tag ) = 0;
};
#endif // _BLOCKDEVRESPONSE_H_
