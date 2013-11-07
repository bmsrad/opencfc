/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: shared memory data-exchange / control interface (variable data)
 *  
 *****************************************************************************/

#ifndef _LZSSHMDATA_H_
#define _LZSSHMDATA_H_

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _LZS_SHM_INTERFACE_
#ifndef _OPC
#define NO_OPC_INTERFACE
#endif
#endif

#ifndef NO_OPC_INTERFACE
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmDataInitialize(void);
LZSPUBLIC32 void    LZSPUBLIC LzsShmDataShutdown(void);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmDataOnDwlPrepare(void);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmDataOnDwlComplete(void);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmDataProcessRequestsFromClient(void);

LZSPUBLIC32 LZSDWORD LZSPUBLIC LzsShmDataGetSegmentLen(void *pSharedMem);
LZSPUBLIC32 LZSBOOL LZSPUBLIC LzsShmDataCopySharedMem(void *pDestSharedMem, void *pSourceSharedMem);
#endif

#ifdef __cplusplus
};
#endif

#endif /* LZSSHMDATA_H */

