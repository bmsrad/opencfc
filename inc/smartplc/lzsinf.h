#ifndef _LZSINF_H_
#define _LZSINF_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION: information funtions                                           */
/*********************************************************************************/

/* */
/* Query- and request-functions of the PLC */
/* */

void  LzsInfInitInfoSrv    (void);

LZSBOOL  LzsInfRegisterError (LZSBYTE bConnectionId_p, LZSBYTE bErrCode_p);
LZSBYTE  LzsInfGetError (LZSBYTE bConnectionId_p);

tLzsErrTabEntry LZSCONST* LzsGetIpErrorEntry(LZSBYTE bIpErrCode_p);
tLzsErrTabEntry LZSCONST* LzsGetLzsErrorEntry(LZSBYTE bLzsErrCode_p);
tLzsErrTabEntry  LZSCONST* LzsInfGetErrorEntry(LZSBYTE bPlcErrCode_p);

LZSCONST LZSCHAR* LzsGetFBErrorString(LZSBYTE bFBErrCode_p);
LZSCONST LZSCHAR* LzsGetIpErrorString(LZSBYTE bIpErrCode_p);
LZSCONST LZSCHAR* LzsGetLzsErrorString(LZSBYTE bLzsErrCode_p);

void LzsInfoEvalCapabilities(void);

LZSBYTE  LzsInfGetResVersion  (LZSBYTE bConnectionId_p);
LZSBYTE  LzsInfGetPlcVersion  (LZSBYTE bConnectionId_p);

/* [SYSTEC: 21.06.2002 -rs]: function inserted */
LZSWORD  LzsInfErrCallback (LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);
LZSWORD  LzsInfExtCapCallback (LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);

#endif /*_LZSINF_H_*/
