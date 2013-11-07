/***********************  I n c l u d e  -  F i l e  ************************
 *
 *       $RCSfile: vmeaccess.h,v $
 *
 *       $Author: yaoshiju $
 *       $Date: 2006/05/31 04:31:15 $
 *       $Revision: 1.1 $
 *-------------------------------[ History ]---------------------------------
 *
 *---------------------------------------------------------------------------
 * (c) Copyright 2003 by Beijing Masic co,Ltd. Beijing China
 ****************************************************************************/

#ifndef VMEACCESS_H
#define VMEACCESS_H

#include <vxWorks.h> 

#ifdef __cplusplus
extern "C" {
#endif

/*访问A24位地址*/
extern int ReadVmeByByte  (UINT8*  pResult ,int address,int length);
extern int WriteVmeByByte (UINT8*  pSource ,int address,int length);
extern int ReadVmeByWord  (UINT16* pResult ,int address,int length,int isSwaped);
extern int WriteVmeByWord (UINT16* pSource ,int address,int length,int isSwaped);
extern int ReadVmeByDWord (UINT32* pResult ,int address,int length,int isSwaped);
extern int WriteVmeByDWord(UINT32* pSource ,int address,int length,int isSwaped);

/*访问自身双端口寄存器*/
extern int ReadSramByByte  (UINT8*  pResult ,int address,int length);
extern int WriteSramByByte (UINT8*  pSource ,int address,int length);
extern int ReadSramByWord  (UINT16* pResult ,int address,int length,int isSwaped);
extern int WriteSramByWord (UINT16* pSource ,int address,int length,int isSwaped);
extern int ReadSramByDWord (UINT32* pResult ,int address,int length,int isSwaped);
extern int WriteSramByDWord(UINT32* pSource ,int address,int length,int isSwaped);

/*访问A32为地址        访问Vme总线*/
extern int ReadVmeByByteA32  (UINT8*  pResult ,int address,int length);
extern int WriteVmeByByteA32 (UINT8*  pSource ,int address,int length);
extern int ReadVmeByWordA32  (UINT16* pResult ,int address,int length,int isSwaped);
extern int WriteVmeByWordA32(UINT16* pSource ,int address,int length,int isSwaped);
extern int ReadVmeByDWordA32 (UINT32* pResult ,int address,int length,int isSwaped);
extern int WriteVmeByDWordA32(UINT32* pSource ,int address,int length,int isSwaped);


extern int ReadVmeByByteA16  (UINT8*  pResult ,int address,int length);
extern int WriteVmeByByteA16 (UINT8* pSource  ,int address,int length);

/*访问CMX016       访问内存映像网  */                                               
extern int ReadCmxByByte  (UINT8*  pResult,int slotno ,int address,int length);
extern int WriteCmxByByte (UINT8*  pSource,int slotno ,int address,int length);
extern int ReadCmxByWord  (UINT16* pResult,int slotno ,int address,int length);
extern int WriteCmxByWord(UINT16* pSource,int slotno ,int address,int length);
extern int ReadCmxByDWord (UINT32* pResult,int slotno ,int address,int length);
extern int WriteCmxByDWord(UINT32* pSource,int slotno ,int address,int length);


#ifdef __cplusplus
}
#endif

#endif /*VMEACCESS_H*/