#include "GeneratedTypes.h"
#ifndef _BLOCKDEVREQUEST_H_
#define _BLOCKDEVREQUEST_H_
#include "portal.h"

class BlockDevRequestProxy : public Portal {
    BlockDevRequestCb *cb;
public:
    BlockDevRequestProxy(int id, int tile = DEFAULT_TILE, BlockDevRequestCb *cbarg = &BlockDevRequestProxyReq, int bufsize = BlockDevRequest_reqinfo, PortalPoller *poller = 0) :
        Portal(id, tile, bufsize, NULL, NULL, this, poller), cb(cbarg) {};
    BlockDevRequestProxy(int id, PortalTransportFunctions *transport, void *param, BlockDevRequestCb *cbarg = &BlockDevRequestProxyReq, int bufsize = BlockDevRequest_reqinfo, PortalPoller *poller = 0) :
        Portal(id, DEFAULT_TILE, bufsize, NULL, NULL, transport, param, this, poller), cb(cbarg) {};
    BlockDevRequestProxy(int id, PortalPoller *poller) :
        Portal(id, DEFAULT_TILE, BlockDevRequest_reqinfo, NULL, NULL, NULL, NULL, this, poller), cb(&BlockDevRequestProxyReq) {};
    int transfer ( const BlockDevOp op, const uint32_t dramaddr, const uint32_t offset, const uint32_t size, const uint32_t tag ) { return cb->transfer (&pint, op, dramaddr, offset, size, tag); };
};

extern BlockDevRequestCb BlockDevRequest_cbTable;
class BlockDevRequestWrapper : public Portal {
public:
    BlockDevRequestWrapper(int id, int tile = DEFAULT_TILE, PORTAL_INDFUNC cba = BlockDevRequest_handleMessage, int bufsize = BlockDevRequest_reqinfo, PortalPoller *poller = 0) :
           Portal(id, tile, bufsize, cba, (void *)&BlockDevRequest_cbTable, this, poller) {
    };
    BlockDevRequestWrapper(int id, PortalTransportFunctions *transport, void *param, PORTAL_INDFUNC cba = BlockDevRequest_handleMessage, int bufsize = BlockDevRequest_reqinfo, PortalPoller *poller=0):
           Portal(id, DEFAULT_TILE, bufsize, cba, (void *)&BlockDevRequest_cbTable, transport, param, this, poller) {
    };
    BlockDevRequestWrapper(int id, PortalPoller *poller) :
           Portal(id, DEFAULT_TILE, BlockDevRequest_reqinfo, BlockDevRequest_handleMessage, (void *)&BlockDevRequest_cbTable, this, poller) {
    };
    BlockDevRequestWrapper(int id, PortalTransportFunctions *transport, void *param, PortalPoller *poller):
           Portal(id, DEFAULT_TILE, BlockDevRequest_reqinfo, BlockDevRequest_handleMessage, (void *)&BlockDevRequest_cbTable, transport, param, this, poller) {
    };
    virtual void disconnect(void) {
        printf("BlockDevRequestWrapper.disconnect called %d\n", pint.client_fd_number);
    };
    virtual void transfer ( const BlockDevOp op, const uint32_t dramaddr, const uint32_t offset, const uint32_t size, const uint32_t tag ) = 0;
};
#endif // _BLOCKDEVREQUEST_H_
