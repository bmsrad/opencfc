/*****************************************************************************
 *    (c) 2006 infoteam Software GmbH
 *    infoteam Software GmbH, Am Bauhof 9, 91088 Bubenreuth, Germany
 *    Tel. +49-9131-7800-0   EMail info@infoteam.de
 *****************************************************************************/

#ifndef _LZSEXTCTRLCHECKSUM_H_
#define _LZSEXTCTRLCHECKSUM_H_

#undef CheckSumFunction 

/* uncomment the following to enable a 16-bit CRC checksum. 
   Also add lzsenvextiocrc.c to your project. */
/*
#include "smartplc/extctrl/lzsenvextctrlcrc.h"
#define CheckSumFunction LzsEnvExtCtrlCalcCrc16 
*/

/* LzsCalcCheckSum
   wrapper checksum function used by FifoCtrl.
   If CheckSumFunction is defined, then CalcChecksum will call the 
   checksum function given by  #define CheckSumFunction.
   Else, it will return 0.

   CheckSumFunction's declaration must be:
   unsigned int f(const unsigned char *pBuffer, unsigned int nBufferLen)   
*/   
extern unsigned int LzsExtCtrlCalcChecksum(const unsigned char *pBuffer, unsigned int nBufferLen);

#endif
