/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: extern control interface - CRC-based checksum
 *  
 *****************************************************************************/

#ifndef _LZS_LZSENVEXTCTRLCRC_H_
#define _LZS_LZSENVEXTCTRLCRC_H_

/* sample checksum implemention: 16-bit CRC (table based) */
extern unsigned short LzsEnvExtCtrlCalcCrc16(const unsigned char *pBuffer_p, unsigned int nLen_p);

#endif
