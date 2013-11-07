/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: shared memory data-exchange / control interface 
 *                (helper functions defined by OEM)
 *  
 *****************************************************************************/
 
#ifndef _LZSSHMENV_H_
#define _LZSSHMENV_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "smartplc/shm/lzsshmstructs.h"

void LzsShmEnvGetTimeStamp(LZSSHMTSTAMP    *pTimeStamp);

#ifdef __cplusplus
};
#endif

#endif

