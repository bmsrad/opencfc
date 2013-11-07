/******************************************************************************
 *  (c) 2005 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 *  DESCRIPTION:    download of new resource while current resource is executed
 *  
 *****************************************************************************/

#ifndef _LZSDWLWS_H_
#define _LZSDWLWS_H_

#include "smartplc/lzstypes.h"

LZSBYTE LzsDwlWithoutStop(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsDwlWithoutStopCont(tLzsPSCmd LZSFAR* pLzsPSCmd_p);

LZSBYTE LzsDwlWithoutStopReplaceRes(void);

#endif

