/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: shared memory data-exchange / control interface 
 *                (helper functions used internally)
 *  
 *****************************************************************************/
 
#ifndef _LZSSHMUTIL_H_
#define _LZSSHMUTIL_H_

#ifdef __cplusplus
   extern "C" {
#endif 

void LzsShmUtilSafeStrCpy(char * pszDest, unsigned int nDestSize, const char* pszSrc);

#ifdef __cplusplus
   }
#endif

#endif

