#ifndef _LZSPFLOW_H_
#define _LZSPFLOW_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

/* */
/* functions to implement powerflow */
/* */
void        LzsPflowInitPowerflow   (void);
LZSBYTE        LzsPflowStart           (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE        LzsPflowStop            (void);
tPlcMemPtr  LzsPflowOpenDataBuffer  (void);
void        LzsPflowCloseDataBuffer (LZSWORD wUsedBuffSize_p);
LZSWORD        LzsPflowCallback        (LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);

/* Multi-Pflow */
LZSBYTE  LzsIpPflowStart    (tPlcPgmNr wPflowPgmNr_p,tPlchInst  hPflowInst_p, tPlcOffset StartOffs_p,
                          tPlcOffset EndOffs_p, LZSWORD wDataBuffSize_p);
                          
LZSBYTE  LzsIpPflowStop     (void);

#endif /*_LZSPFLOW_H_*/
