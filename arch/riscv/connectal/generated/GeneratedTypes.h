#ifndef __GENERATED_TYPES__
#define __GENERATED_TYPES__
#include "portal.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct S1 {
    uint32_t a : 32;
    uint32_t b : 32;
} S1;
typedef struct S2 {
    uint32_t a : 32;
    uint16_t b : 16;
    uint8_t c : 7;
} S2;
typedef enum E1 { E1Choice1, E1Choice2, E1Choice3,  } E1;
typedef struct S3 {
    uint32_t a : 32;
    E1 e1;
} S3;
typedef uint32_t Address;
typedef uint32_t Intptr;
typedef uint8_t Byte;
typedef struct Say6ReqSimple {
    uint32_t a : 32;
    uint64_t b : 40;
    uint32_t c : 32;
} Say6ReqSimple;
typedef enum AccelIfcNames { AccelIfcNamesNone=0, PlatformAccelIfcNames_MemServerRequestS2H=1, PlatformAccelIfcNames_MMURequestS2H=2, PlatformAccelIfcNames_MemServerIndicationH2S=3, PlatformAccelIfcNames_MMUIndicationH2S=4, AccelIfcNames_SerialIndicationH2S=5, AccelIfcNames_SimpleRequestH2S=6, AccelIfcNames_BlockDevResponseH2S=7, AccelIfcNames_SerialRequestS2H=8, AccelIfcNames_SimpleRequestS2H=9, AccelIfcNames_BlockDevRequestS2H=10,  } AccelIfcNames;
typedef enum BlockDevOp { BlockDevRead, BlockDevWrite,  } BlockDevOp;
typedef struct BlockDevTransfer {
    BlockDevOp op;
    uint32_t dramaddr : 32;
    uint32_t offset : 32;
    uint32_t size : 32;
    uint32_t tag : 32;
} BlockDevTransfer;
typedef enum ChannelType { ChannelType_Read, ChannelType_Write,  } ChannelType;
typedef struct DmaDbgRec {
    uint32_t x : 32;
    uint32_t y : 32;
    uint32_t z : 32;
    uint32_t w : 32;
} DmaDbgRec;
typedef enum DmaErrorType { DmaErrorNone, DmaErrorSGLIdOutOfRange_r, DmaErrorSGLIdOutOfRange_w, DmaErrorMMUOutOfRange_r, DmaErrorMMUOutOfRange_w, DmaErrorOffsetOutOfRange, DmaErrorSGLIdInvalid, DmaErrorTileTagOutOfRange,  } DmaErrorType;
typedef uint32_t SpecialTypeForSendingFd;
typedef enum TileState { Idle, Stopped, Running,  } TileState;
typedef struct TileControl {
    uint8_t tile : 2;
    TileState state;
} TileControl;
typedef enum XsimIfcNames { XsimIfcNames_XsimMsgRequest, XsimIfcNames_XsimMsgIndication,  } XsimIfcNames;
typedef enum IfcNames { IfcNamesNone=0, PlatformIfcNames_MemServerRequestS2H=1, PlatformIfcNames_MMURequestS2H=2, PlatformIfcNames_MemServerIndicationH2S=3, PlatformIfcNames_MMUIndicationH2S=4, IfcNames_QemuAccelIndicationH2S=5, IfcNames_MemServerPortalResponseH2S=6, IfcNames_SerialIndicationH2S=7, IfcNames_BlockDevRequestH2S=8, IfcNames_QemuAccelRequestS2H=9, IfcNames_MemServerPortalRequestS2H=10, IfcNames_SerialRequestS2H=11, IfcNames_BlockDevResponseS2H=12,  } IfcNames;


typedef uint32_t bsvvector_Luint32_t_L128[128];
typedef int32_t bsvvector_Lint32_t_L4[4];
typedef int16_t bsvvector_Lint16_t_L16[16];
typedef uint32_t bsvvector_Luint32_t_L128[128];
typedef int32_t bsvvector_Lint32_t_L4[4];
typedef int16_t bsvvector_Lint16_t_L16[16];
typedef int16_t bsvvector_Lint16_t_L16[16];
int SimpleRequest_say1 ( struct PortalInternal *p, const uint32_t v );
int SimpleRequest_say2 ( struct PortalInternal *p, const uint16_t a, const uint16_t b );
int SimpleRequest_say3 ( struct PortalInternal *p, const S1 v );
int SimpleRequest_say4 ( struct PortalInternal *p, const S2 v );
int SimpleRequest_say5 ( struct PortalInternal *p, const uint32_t a, const uint64_t b, const uint32_t c );
int SimpleRequest_say6 ( struct PortalInternal *p, const uint32_t a, const uint64_t b, const uint32_t c );
int SimpleRequest_say7 ( struct PortalInternal *p, const S3 v );
int SimpleRequest_say8 ( struct PortalInternal *p, const bsvvector_Luint32_t_L128 v );
int SimpleRequest_sayv1 ( struct PortalInternal *p, const bsvvector_Lint32_t_L4 arg1, const bsvvector_Lint32_t_L4 arg2 );
int SimpleRequest_sayv2 ( struct PortalInternal *p, const bsvvector_Lint16_t_L16 v );
int SimpleRequest_sayv3 ( struct PortalInternal *p, const bsvvector_Lint16_t_L16 v, const int16_t count );
int SimpleRequest_reftest1 ( struct PortalInternal *p, const Address dst, const Intptr dst_stride, const Address src1, const Intptr i_src_stride1, const Address src2, const Intptr i_src_stride2, const Byte i_width, const Byte i_height, const int qpelInt, const int hasWeight, const Byte i_offset, const Byte i_scale, const Byte i_denom );
enum { CHAN_NUM_SimpleRequest_say1,CHAN_NUM_SimpleRequest_say2,CHAN_NUM_SimpleRequest_say3,CHAN_NUM_SimpleRequest_say4,CHAN_NUM_SimpleRequest_say5,CHAN_NUM_SimpleRequest_say6,CHAN_NUM_SimpleRequest_say7,CHAN_NUM_SimpleRequest_say8,CHAN_NUM_SimpleRequest_sayv1,CHAN_NUM_SimpleRequest_sayv2,CHAN_NUM_SimpleRequest_sayv3,CHAN_NUM_SimpleRequest_reftest1};
extern const uint32_t SimpleRequest_reqinfo;

typedef struct {
    uint32_t v;
} SimpleRequest_say1Data;
typedef struct {
    uint16_t a;
    uint16_t b;
} SimpleRequest_say2Data;
typedef struct {
    S1 v;
} SimpleRequest_say3Data;
typedef struct {
    S2 v;
} SimpleRequest_say4Data;
typedef struct {
    uint32_t a;
    uint64_t b;
    uint32_t c;
} SimpleRequest_say5Data;
typedef struct {
    uint32_t a;
    uint64_t b;
    uint32_t c;
} SimpleRequest_say6Data;
typedef struct {
    S3 v;
} SimpleRequest_say7Data;
typedef struct {
    bsvvector_Luint32_t_L128 v;
} SimpleRequest_say8Data;
typedef struct {
    bsvvector_Lint32_t_L4 arg1;
    bsvvector_Lint32_t_L4 arg2;
} SimpleRequest_sayv1Data;
typedef struct {
    bsvvector_Lint16_t_L16 v;
} SimpleRequest_sayv2Data;
typedef struct {
    bsvvector_Lint16_t_L16 v;
    int16_t count;
} SimpleRequest_sayv3Data;
typedef struct {
    Address dst;
    Intptr dst_stride;
    Address src1;
    Intptr i_src_stride1;
    Address src2;
    Intptr i_src_stride2;
    Byte i_width;
    Byte i_height;
    int qpelInt;
    int hasWeight;
    Byte i_offset;
    Byte i_scale;
    Byte i_denom;
} SimpleRequest_reftest1Data;
typedef union {
    SimpleRequest_say1Data say1;
    SimpleRequest_say2Data say2;
    SimpleRequest_say3Data say3;
    SimpleRequest_say4Data say4;
    SimpleRequest_say5Data say5;
    SimpleRequest_say6Data say6;
    SimpleRequest_say7Data say7;
    SimpleRequest_say8Data say8;
    SimpleRequest_sayv1Data sayv1;
    SimpleRequest_sayv2Data sayv2;
    SimpleRequest_sayv3Data sayv3;
    SimpleRequest_reftest1Data reftest1;
} SimpleRequestData;
int SimpleRequest_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*say1) (  struct PortalInternal *p, const uint32_t v );
    int (*say2) (  struct PortalInternal *p, const uint16_t a, const uint16_t b );
    int (*say3) (  struct PortalInternal *p, const S1 v );
    int (*say4) (  struct PortalInternal *p, const S2 v );
    int (*say5) (  struct PortalInternal *p, const uint32_t a, const uint64_t b, const uint32_t c );
    int (*say6) (  struct PortalInternal *p, const uint32_t a, const uint64_t b, const uint32_t c );
    int (*say7) (  struct PortalInternal *p, const S3 v );
    int (*say8) (  struct PortalInternal *p, const bsvvector_Luint32_t_L128 v );
    int (*sayv1) (  struct PortalInternal *p, const bsvvector_Lint32_t_L4 arg1, const bsvvector_Lint32_t_L4 arg2 );
    int (*sayv2) (  struct PortalInternal *p, const bsvvector_Lint16_t_L16 v );
    int (*sayv3) (  struct PortalInternal *p, const bsvvector_Lint16_t_L16 v, const int16_t count );
    int (*reftest1) (  struct PortalInternal *p, const Address dst, const Intptr dst_stride, const Address src1, const Intptr i_src_stride1, const Address src2, const Intptr i_src_stride2, const Byte i_width, const Byte i_height, const int qpelInt, const int hasWeight, const Byte i_offset, const Byte i_scale, const Byte i_denom );
} SimpleRequestCb;
extern SimpleRequestCb SimpleRequestProxyReq;

int SimpleRequestJson_say1 ( struct PortalInternal *p, const uint32_t v );
int SimpleRequestJson_say2 ( struct PortalInternal *p, const uint16_t a, const uint16_t b );
int SimpleRequestJson_say3 ( struct PortalInternal *p, const S1 v );
int SimpleRequestJson_say4 ( struct PortalInternal *p, const S2 v );
int SimpleRequestJson_say5 ( struct PortalInternal *p, const uint32_t a, const uint64_t b, const uint32_t c );
int SimpleRequestJson_say6 ( struct PortalInternal *p, const uint32_t a, const uint64_t b, const uint32_t c );
int SimpleRequestJson_say7 ( struct PortalInternal *p, const S3 v );
int SimpleRequestJson_say8 ( struct PortalInternal *p, const bsvvector_Luint32_t_L128 v );
int SimpleRequestJson_sayv1 ( struct PortalInternal *p, const bsvvector_Lint32_t_L4 arg1, const bsvvector_Lint32_t_L4 arg2 );
int SimpleRequestJson_sayv2 ( struct PortalInternal *p, const bsvvector_Lint16_t_L16 v );
int SimpleRequestJson_sayv3 ( struct PortalInternal *p, const bsvvector_Lint16_t_L16 v, const int16_t count );
int SimpleRequestJson_reftest1 ( struct PortalInternal *p, const Address dst, const Intptr dst_stride, const Address src1, const Intptr i_src_stride1, const Address src2, const Intptr i_src_stride2, const Byte i_width, const Byte i_height, const int qpelInt, const int hasWeight, const Byte i_offset, const Byte i_scale, const Byte i_denom );
int SimpleRequestJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern SimpleRequestCb SimpleRequestJsonProxyReq;

typedef uint32_t bsvvector_Luint32_t_L128[128];
typedef int32_t bsvvector_Lint32_t_L4[4];
typedef int16_t bsvvector_Lint16_t_L16[16];
int SerialRequest_tx ( struct PortalInternal *p, const uint8_t c );
enum { CHAN_NUM_SerialRequest_tx};
extern const uint32_t SerialRequest_reqinfo;

typedef struct {
    uint8_t c;
} SerialRequest_txData;
typedef union {
    SerialRequest_txData tx;
} SerialRequestData;
int SerialRequest_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*tx) (  struct PortalInternal *p, const uint8_t c );
} SerialRequestCb;
extern SerialRequestCb SerialRequestProxyReq;

int SerialRequestJson_tx ( struct PortalInternal *p, const uint8_t c );
int SerialRequestJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern SerialRequestCb SerialRequestJsonProxyReq;

int SerialIndication_rx ( struct PortalInternal *p, const uint8_t c );
enum { CHAN_NUM_SerialIndication_rx};
extern const uint32_t SerialIndication_reqinfo;

typedef struct {
    uint8_t c;
} SerialIndication_rxData;
typedef union {
    SerialIndication_rxData rx;
} SerialIndicationData;
int SerialIndication_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*rx) (  struct PortalInternal *p, const uint8_t c );
} SerialIndicationCb;
extern SerialIndicationCb SerialIndicationProxyReq;

int SerialIndicationJson_rx ( struct PortalInternal *p, const uint8_t c );
int SerialIndicationJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern SerialIndicationCb SerialIndicationJsonProxyReq;

int BlockDevRequest_transfer ( struct PortalInternal *p, const BlockDevOp op, const uint32_t dramaddr, const uint32_t offset, const uint32_t size, const uint32_t tag );
enum { CHAN_NUM_BlockDevRequest_transfer};
extern const uint32_t BlockDevRequest_reqinfo;

typedef struct {
    BlockDevOp op;
    uint32_t dramaddr;
    uint32_t offset;
    uint32_t size;
    uint32_t tag;
} BlockDevRequest_transferData;
typedef union {
    BlockDevRequest_transferData transfer;
} BlockDevRequestData;
int BlockDevRequest_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*transfer) (  struct PortalInternal *p, const BlockDevOp op, const uint32_t dramaddr, const uint32_t offset, const uint32_t size, const uint32_t tag );
} BlockDevRequestCb;
extern BlockDevRequestCb BlockDevRequestProxyReq;

int BlockDevRequestJson_transfer ( struct PortalInternal *p, const BlockDevOp op, const uint32_t dramaddr, const uint32_t offset, const uint32_t size, const uint32_t tag );
int BlockDevRequestJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern BlockDevRequestCb BlockDevRequestJsonProxyReq;

int BlockDevResponse_transferDone ( struct PortalInternal *p, const uint32_t tag );
enum { CHAN_NUM_BlockDevResponse_transferDone};
extern const uint32_t BlockDevResponse_reqinfo;

typedef struct {
    uint32_t tag;
} BlockDevResponse_transferDoneData;
typedef union {
    BlockDevResponse_transferDoneData transferDone;
} BlockDevResponseData;
int BlockDevResponse_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*transferDone) (  struct PortalInternal *p, const uint32_t tag );
} BlockDevResponseCb;
extern BlockDevResponseCb BlockDevResponseProxyReq;

int BlockDevResponseJson_transferDone ( struct PortalInternal *p, const uint32_t tag );
int BlockDevResponseJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern BlockDevResponseCb BlockDevResponseJsonProxyReq;

int MemServerRequest_addrTrans ( struct PortalInternal *p, const uint32_t sglId, const uint32_t offset );
int MemServerRequest_setTileState ( struct PortalInternal *p, const TileControl tc );
int MemServerRequest_stateDbg ( struct PortalInternal *p, const ChannelType rc );
int MemServerRequest_memoryTraffic ( struct PortalInternal *p, const ChannelType rc );
enum { CHAN_NUM_MemServerRequest_addrTrans,CHAN_NUM_MemServerRequest_setTileState,CHAN_NUM_MemServerRequest_stateDbg,CHAN_NUM_MemServerRequest_memoryTraffic};
extern const uint32_t MemServerRequest_reqinfo;

typedef struct {
    uint32_t sglId;
    uint32_t offset;
} MemServerRequest_addrTransData;
typedef struct {
    TileControl tc;
} MemServerRequest_setTileStateData;
typedef struct {
    ChannelType rc;
} MemServerRequest_stateDbgData;
typedef struct {
    ChannelType rc;
} MemServerRequest_memoryTrafficData;
typedef union {
    MemServerRequest_addrTransData addrTrans;
    MemServerRequest_setTileStateData setTileState;
    MemServerRequest_stateDbgData stateDbg;
    MemServerRequest_memoryTrafficData memoryTraffic;
} MemServerRequestData;
int MemServerRequest_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*addrTrans) (  struct PortalInternal *p, const uint32_t sglId, const uint32_t offset );
    int (*setTileState) (  struct PortalInternal *p, const TileControl tc );
    int (*stateDbg) (  struct PortalInternal *p, const ChannelType rc );
    int (*memoryTraffic) (  struct PortalInternal *p, const ChannelType rc );
} MemServerRequestCb;
extern MemServerRequestCb MemServerRequestProxyReq;

int MemServerRequestJson_addrTrans ( struct PortalInternal *p, const uint32_t sglId, const uint32_t offset );
int MemServerRequestJson_setTileState ( struct PortalInternal *p, const TileControl tc );
int MemServerRequestJson_stateDbg ( struct PortalInternal *p, const ChannelType rc );
int MemServerRequestJson_memoryTraffic ( struct PortalInternal *p, const ChannelType rc );
int MemServerRequestJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern MemServerRequestCb MemServerRequestJsonProxyReq;

int MMURequest_sglist ( struct PortalInternal *p, const uint32_t sglId, const uint32_t sglIndex, const uint64_t addr, const uint32_t len );
int MMURequest_region ( struct PortalInternal *p, const uint32_t sglId, const uint64_t barr12, const uint32_t index12, const uint64_t barr8, const uint32_t index8, const uint64_t barr4, const uint32_t index4, const uint64_t barr0, const uint32_t index0 );
int MMURequest_idRequest ( struct PortalInternal *p, const SpecialTypeForSendingFd fd );
int MMURequest_idReturn ( struct PortalInternal *p, const uint32_t sglId );
int MMURequest_setInterface ( struct PortalInternal *p, const uint32_t interfaceId, const uint32_t sglId );
enum { CHAN_NUM_MMURequest_sglist,CHAN_NUM_MMURequest_region,CHAN_NUM_MMURequest_idRequest,CHAN_NUM_MMURequest_idReturn,CHAN_NUM_MMURequest_setInterface};
extern const uint32_t MMURequest_reqinfo;

typedef struct {
    uint32_t sglId;
    uint32_t sglIndex;
    uint64_t addr;
    uint32_t len;
} MMURequest_sglistData;
typedef struct {
    uint32_t sglId;
    uint64_t barr12;
    uint32_t index12;
    uint64_t barr8;
    uint32_t index8;
    uint64_t barr4;
    uint32_t index4;
    uint64_t barr0;
    uint32_t index0;
} MMURequest_regionData;
typedef struct {
    SpecialTypeForSendingFd fd;
} MMURequest_idRequestData;
typedef struct {
    uint32_t sglId;
} MMURequest_idReturnData;
typedef struct {
    uint32_t interfaceId;
    uint32_t sglId;
} MMURequest_setInterfaceData;
typedef union {
    MMURequest_sglistData sglist;
    MMURequest_regionData region;
    MMURequest_idRequestData idRequest;
    MMURequest_idReturnData idReturn;
    MMURequest_setInterfaceData setInterface;
} MMURequestData;
int MMURequest_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*sglist) (  struct PortalInternal *p, const uint32_t sglId, const uint32_t sglIndex, const uint64_t addr, const uint32_t len );
    int (*region) (  struct PortalInternal *p, const uint32_t sglId, const uint64_t barr12, const uint32_t index12, const uint64_t barr8, const uint32_t index8, const uint64_t barr4, const uint32_t index4, const uint64_t barr0, const uint32_t index0 );
    int (*idRequest) (  struct PortalInternal *p, const SpecialTypeForSendingFd fd );
    int (*idReturn) (  struct PortalInternal *p, const uint32_t sglId );
    int (*setInterface) (  struct PortalInternal *p, const uint32_t interfaceId, const uint32_t sglId );
} MMURequestCb;
extern MMURequestCb MMURequestProxyReq;

int MMURequestJson_sglist ( struct PortalInternal *p, const uint32_t sglId, const uint32_t sglIndex, const uint64_t addr, const uint32_t len );
int MMURequestJson_region ( struct PortalInternal *p, const uint32_t sglId, const uint64_t barr12, const uint32_t index12, const uint64_t barr8, const uint32_t index8, const uint64_t barr4, const uint32_t index4, const uint64_t barr0, const uint32_t index0 );
int MMURequestJson_idRequest ( struct PortalInternal *p, const SpecialTypeForSendingFd fd );
int MMURequestJson_idReturn ( struct PortalInternal *p, const uint32_t sglId );
int MMURequestJson_setInterface ( struct PortalInternal *p, const uint32_t interfaceId, const uint32_t sglId );
int MMURequestJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern MMURequestCb MMURequestJsonProxyReq;

int MemServerIndication_addrResponse ( struct PortalInternal *p, const uint64_t physAddr );
int MemServerIndication_reportStateDbg ( struct PortalInternal *p, const DmaDbgRec rec );
int MemServerIndication_reportMemoryTraffic ( struct PortalInternal *p, const uint64_t words );
int MemServerIndication_error ( struct PortalInternal *p, const uint32_t code, const uint32_t sglId, const uint64_t offset, const uint64_t extra );
enum { CHAN_NUM_MemServerIndication_addrResponse,CHAN_NUM_MemServerIndication_reportStateDbg,CHAN_NUM_MemServerIndication_reportMemoryTraffic,CHAN_NUM_MemServerIndication_error};
extern const uint32_t MemServerIndication_reqinfo;

typedef struct {
    uint64_t physAddr;
} MemServerIndication_addrResponseData;
typedef struct {
    DmaDbgRec rec;
} MemServerIndication_reportStateDbgData;
typedef struct {
    uint64_t words;
} MemServerIndication_reportMemoryTrafficData;
typedef struct {
    uint32_t code;
    uint32_t sglId;
    uint64_t offset;
    uint64_t extra;
} MemServerIndication_errorData;
typedef union {
    MemServerIndication_addrResponseData addrResponse;
    MemServerIndication_reportStateDbgData reportStateDbg;
    MemServerIndication_reportMemoryTrafficData reportMemoryTraffic;
    MemServerIndication_errorData error;
} MemServerIndicationData;
int MemServerIndication_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*addrResponse) (  struct PortalInternal *p, const uint64_t physAddr );
    int (*reportStateDbg) (  struct PortalInternal *p, const DmaDbgRec rec );
    int (*reportMemoryTraffic) (  struct PortalInternal *p, const uint64_t words );
    int (*error) (  struct PortalInternal *p, const uint32_t code, const uint32_t sglId, const uint64_t offset, const uint64_t extra );
} MemServerIndicationCb;
extern MemServerIndicationCb MemServerIndicationProxyReq;

int MemServerIndicationJson_addrResponse ( struct PortalInternal *p, const uint64_t physAddr );
int MemServerIndicationJson_reportStateDbg ( struct PortalInternal *p, const DmaDbgRec rec );
int MemServerIndicationJson_reportMemoryTraffic ( struct PortalInternal *p, const uint64_t words );
int MemServerIndicationJson_error ( struct PortalInternal *p, const uint32_t code, const uint32_t sglId, const uint64_t offset, const uint64_t extra );
int MemServerIndicationJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern MemServerIndicationCb MemServerIndicationJsonProxyReq;

int MMUIndication_idResponse ( struct PortalInternal *p, const uint32_t sglId );
int MMUIndication_configResp ( struct PortalInternal *p, const uint32_t sglId );
int MMUIndication_error ( struct PortalInternal *p, const uint32_t code, const uint32_t sglId, const uint64_t offset, const uint64_t extra );
enum { CHAN_NUM_MMUIndication_idResponse,CHAN_NUM_MMUIndication_configResp,CHAN_NUM_MMUIndication_error};
extern const uint32_t MMUIndication_reqinfo;

typedef struct {
    uint32_t sglId;
} MMUIndication_idResponseData;
typedef struct {
    uint32_t sglId;
} MMUIndication_configRespData;
typedef struct {
    uint32_t code;
    uint32_t sglId;
    uint64_t offset;
    uint64_t extra;
} MMUIndication_errorData;
typedef union {
    MMUIndication_idResponseData idResponse;
    MMUIndication_configRespData configResp;
    MMUIndication_errorData error;
} MMUIndicationData;
int MMUIndication_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*idResponse) (  struct PortalInternal *p, const uint32_t sglId );
    int (*configResp) (  struct PortalInternal *p, const uint32_t sglId );
    int (*error) (  struct PortalInternal *p, const uint32_t code, const uint32_t sglId, const uint64_t offset, const uint64_t extra );
} MMUIndicationCb;
extern MMUIndicationCb MMUIndicationProxyReq;

int MMUIndicationJson_idResponse ( struct PortalInternal *p, const uint32_t sglId );
int MMUIndicationJson_configResp ( struct PortalInternal *p, const uint32_t sglId );
int MMUIndicationJson_error ( struct PortalInternal *p, const uint32_t code, const uint32_t sglId, const uint64_t offset, const uint64_t extra );
int MMUIndicationJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern MMUIndicationCb MMUIndicationJsonProxyReq;

int XsimMsgRequest_msgSink ( struct PortalInternal *p, const uint32_t portal, const uint32_t data );
int XsimMsgRequest_msgSinkFd ( struct PortalInternal *p, const uint32_t portal, const SpecialTypeForSendingFd data );
enum { CHAN_NUM_XsimMsgRequest_msgSink,CHAN_NUM_XsimMsgRequest_msgSinkFd};
extern const uint32_t XsimMsgRequest_reqinfo;

typedef struct {
    uint32_t portal;
    uint32_t data;
} XsimMsgRequest_msgSinkData;
typedef struct {
    uint32_t portal;
    SpecialTypeForSendingFd data;
} XsimMsgRequest_msgSinkFdData;
typedef union {
    XsimMsgRequest_msgSinkData msgSink;
    XsimMsgRequest_msgSinkFdData msgSinkFd;
} XsimMsgRequestData;
int XsimMsgRequest_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*msgSink) (  struct PortalInternal *p, const uint32_t portal, const uint32_t data );
    int (*msgSinkFd) (  struct PortalInternal *p, const uint32_t portal, const SpecialTypeForSendingFd data );
} XsimMsgRequestCb;
extern XsimMsgRequestCb XsimMsgRequestProxyReq;

int XsimMsgRequestJson_msgSink ( struct PortalInternal *p, const uint32_t portal, const uint32_t data );
int XsimMsgRequestJson_msgSinkFd ( struct PortalInternal *p, const uint32_t portal, const SpecialTypeForSendingFd data );
int XsimMsgRequestJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern XsimMsgRequestCb XsimMsgRequestJsonProxyReq;

int XsimMsgIndication_msgSource ( struct PortalInternal *p, const uint32_t portal, const uint32_t data );
enum { CHAN_NUM_XsimMsgIndication_msgSource};
extern const uint32_t XsimMsgIndication_reqinfo;

typedef struct {
    uint32_t portal;
    uint32_t data;
} XsimMsgIndication_msgSourceData;
typedef union {
    XsimMsgIndication_msgSourceData msgSource;
} XsimMsgIndicationData;
int XsimMsgIndication_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*msgSource) (  struct PortalInternal *p, const uint32_t portal, const uint32_t data );
} XsimMsgIndicationCb;
extern XsimMsgIndicationCb XsimMsgIndicationProxyReq;

int XsimMsgIndicationJson_msgSource ( struct PortalInternal *p, const uint32_t portal, const uint32_t data );
int XsimMsgIndicationJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern XsimMsgIndicationCb XsimMsgIndicationJsonProxyReq;

int QemuAccelRequest_start ( struct PortalInternal *p );
int QemuAccelRequest_reset ( struct PortalInternal *p );
int QemuAccelRequest_status ( struct PortalInternal *p );
int QemuAccelRequest_setupDma ( struct PortalInternal *p, const uint32_t objId );
enum { CHAN_NUM_QemuAccelRequest_start,CHAN_NUM_QemuAccelRequest_reset,CHAN_NUM_QemuAccelRequest_status,CHAN_NUM_QemuAccelRequest_setupDma};
extern const uint32_t QemuAccelRequest_reqinfo;

typedef struct {
        int padding;

} QemuAccelRequest_startData;
typedef struct {
        int padding;

} QemuAccelRequest_resetData;
typedef struct {
        int padding;

} QemuAccelRequest_statusData;
typedef struct {
    uint32_t objId;
} QemuAccelRequest_setupDmaData;
typedef union {
    QemuAccelRequest_startData start;
    QemuAccelRequest_resetData reset;
    QemuAccelRequest_statusData status;
    QemuAccelRequest_setupDmaData setupDma;
} QemuAccelRequestData;
int QemuAccelRequest_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*start) (  struct PortalInternal *p );
    int (*reset) (  struct PortalInternal *p );
    int (*status) (  struct PortalInternal *p );
    int (*setupDma) (  struct PortalInternal *p, const uint32_t objId );
} QemuAccelRequestCb;
extern QemuAccelRequestCb QemuAccelRequestProxyReq;

int QemuAccelRequestJson_start ( struct PortalInternal *p );
int QemuAccelRequestJson_reset ( struct PortalInternal *p );
int QemuAccelRequestJson_status ( struct PortalInternal *p );
int QemuAccelRequestJson_setupDma ( struct PortalInternal *p, const uint32_t objId );
int QemuAccelRequestJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern QemuAccelRequestCb QemuAccelRequestJsonProxyReq;

int MemServerPortalRequest_read32 ( struct PortalInternal *p, const uint32_t addr );
int MemServerPortalRequest_write32 ( struct PortalInternal *p, const uint32_t addr, const uint32_t data );
int MemServerPortalRequest_read64 ( struct PortalInternal *p, const uint32_t addr );
int MemServerPortalRequest_write64 ( struct PortalInternal *p, const uint32_t addr, const uint64_t data );
enum { CHAN_NUM_MemServerPortalRequest_read32,CHAN_NUM_MemServerPortalRequest_write32,CHAN_NUM_MemServerPortalRequest_read64,CHAN_NUM_MemServerPortalRequest_write64};
extern const uint32_t MemServerPortalRequest_reqinfo;

typedef struct {
    uint32_t addr;
} MemServerPortalRequest_read32Data;
typedef struct {
    uint32_t addr;
    uint32_t data;
} MemServerPortalRequest_write32Data;
typedef struct {
    uint32_t addr;
} MemServerPortalRequest_read64Data;
typedef struct {
    uint32_t addr;
    uint64_t data;
} MemServerPortalRequest_write64Data;
typedef union {
    MemServerPortalRequest_read32Data read32;
    MemServerPortalRequest_write32Data write32;
    MemServerPortalRequest_read64Data read64;
    MemServerPortalRequest_write64Data write64;
} MemServerPortalRequestData;
int MemServerPortalRequest_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*read32) (  struct PortalInternal *p, const uint32_t addr );
    int (*write32) (  struct PortalInternal *p, const uint32_t addr, const uint32_t data );
    int (*read64) (  struct PortalInternal *p, const uint32_t addr );
    int (*write64) (  struct PortalInternal *p, const uint32_t addr, const uint64_t data );
} MemServerPortalRequestCb;
extern MemServerPortalRequestCb MemServerPortalRequestProxyReq;

int MemServerPortalRequestJson_read32 ( struct PortalInternal *p, const uint32_t addr );
int MemServerPortalRequestJson_write32 ( struct PortalInternal *p, const uint32_t addr, const uint32_t data );
int MemServerPortalRequestJson_read64 ( struct PortalInternal *p, const uint32_t addr );
int MemServerPortalRequestJson_write64 ( struct PortalInternal *p, const uint32_t addr, const uint64_t data );
int MemServerPortalRequestJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern MemServerPortalRequestCb MemServerPortalRequestJsonProxyReq;

int QemuAccelIndication_started ( struct PortalInternal *p );
enum { CHAN_NUM_QemuAccelIndication_started};
extern const uint32_t QemuAccelIndication_reqinfo;

typedef struct {
        int padding;

} QemuAccelIndication_startedData;
typedef union {
    QemuAccelIndication_startedData started;
} QemuAccelIndicationData;
int QemuAccelIndication_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*started) (  struct PortalInternal *p );
} QemuAccelIndicationCb;
extern QemuAccelIndicationCb QemuAccelIndicationProxyReq;

int QemuAccelIndicationJson_started ( struct PortalInternal *p );
int QemuAccelIndicationJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern QemuAccelIndicationCb QemuAccelIndicationJsonProxyReq;

int MemServerPortalResponse_read32Done ( struct PortalInternal *p, const uint32_t data );
int MemServerPortalResponse_read64Done ( struct PortalInternal *p, const uint64_t data );
int MemServerPortalResponse_writeDone ( struct PortalInternal *p );
enum { CHAN_NUM_MemServerPortalResponse_read32Done,CHAN_NUM_MemServerPortalResponse_read64Done,CHAN_NUM_MemServerPortalResponse_writeDone};
extern const uint32_t MemServerPortalResponse_reqinfo;

typedef struct {
    uint32_t data;
} MemServerPortalResponse_read32DoneData;
typedef struct {
    uint64_t data;
} MemServerPortalResponse_read64DoneData;
typedef struct {
        int padding;

} MemServerPortalResponse_writeDoneData;
typedef union {
    MemServerPortalResponse_read32DoneData read32Done;
    MemServerPortalResponse_read64DoneData read64Done;
    MemServerPortalResponse_writeDoneData writeDone;
} MemServerPortalResponseData;
int MemServerPortalResponse_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
typedef struct {
    PORTAL_DISCONNECT disconnect;
    int (*read32Done) (  struct PortalInternal *p, const uint32_t data );
    int (*read64Done) (  struct PortalInternal *p, const uint64_t data );
    int (*writeDone) (  struct PortalInternal *p );
} MemServerPortalResponseCb;
extern MemServerPortalResponseCb MemServerPortalResponseProxyReq;

int MemServerPortalResponseJson_read32Done ( struct PortalInternal *p, const uint32_t data );
int MemServerPortalResponseJson_read64Done ( struct PortalInternal *p, const uint64_t data );
int MemServerPortalResponseJson_writeDone ( struct PortalInternal *p );
int MemServerPortalResponseJson_handleMessage(struct PortalInternal *p, unsigned int channel, int messageFd);
extern MemServerPortalResponseCb MemServerPortalResponseJsonProxyReq;
#ifdef __cplusplus
}
#endif
#endif //__GENERATED_TYPES__
