/*****************************************************************************
 *    (c) 2005 infoteam Software GmbH
 *    infoteam Software GmbH, Am Bauhof 9, 91088 Bubenreuth, Germany
 *    Tel. +49-9131-7800-0   EMail info@infoteam.de
 *****************************************************************************/

#ifndef __LZSEXTCTRLVAR_H_
#define __LZSEXTCTRLVAR_H_

#include <inttypes.h>

typedef struct {
  char *pszPath;
  uint16_t wSegment;
  uint16_t wOffset;
  uint16_t wType;
  uint16_t wSize;  
} tVarCacheNode;

extern int VarCacheInsert(char *pszPath, unsigned nPathLen,
              uint16_t wSegment, uint16_t wOffset, 
              uint16_t wType, uint16_t wSize);

extern tVarCacheNode *VarCacheLookup(char *pszPath, unsigned nPathLen);

extern void VarCacheReset(void);

#endif
