/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: shared memory data-exchange / control interface 
 *                (variable path dictionary functions)
 *  
 *****************************************************************************/

#ifndef _LZSSHMVARTAB_H_
#define _LZSSHMVARTAB_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "smartplc/odk_plc.h"
#include "smartplc/shm/lzsshmconfig.h"

extern void LzsShmVarTabInsertEntry(LZSWORD wProg_i, LZSWORD wSegment_i, LZSWORD wOffset_i, LZSWORD wSize_i, LZSWORD wType_i);
extern LZSBOOL LzsShmVarTabGetEntry(LZSWORD wProg_i, LZSWORD wSegment_i, LZSWORD wOffset_i, LZSWORD* wSize_o, LZSWORD* wType_o);
extern void LzsShmVarTabRemoveAll(void);

#ifdef LZS_SHM_SUPPORT_ARRAYS
extern LZSBOOL LzsShmVarTabGetArrayEntry(LZSWORD wProg_i, LZSWORD wSegment_i, LZSWORD wOffset_i, 
                                       LZSWORD* p_wSize_o, LZSWORD* p_wType_o, 
                                       LZSWORD* p_wNumberElements_o);

extern void LzsShmVarTabInsertArrayEntry(LZSWORD wProg_i, LZSWORD wSegment_i, LZSWORD wOffset_i, 
                                      LZSWORD wSize_i, LZSWORD wType_i, LZSWORD wNumberElements);
#endif

#ifdef __cplusplus
};
#endif

#endif
