#ifndef _LZSWATCH_H_
#define _LZSWATCH_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

/* */
/* functions for watching variables */
/* */
void  LzsWatchInitWatchTab    (LZSBYTE bConnectionId_p);
tLzsWatchTable* LzsWatchGetWatchTable(LZSBYTE bConnectionId_p);
LZSBYTE  LzsWatchDiscardWatchTab (LZSBYTE bConnectionId_p);
LZSBYTE  LzsWatchEnableWatching  (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsWatchAddInstruction  (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
void  LzsWatchMarkDataValid   (LZSBYTE bConnectionId_p);
LZSBYTE  LzsWatchDelInstruction    (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);

LZSWORD  LzsWatchCallback        (LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);
LZSBOOL  LzsWatchSendData        (tLzsWatchTable LZSFAR* pWatchTable_p);
LZSBOOL  LzsWatchExecInstruction (tLzsWatchTable LZSFAR* pWatchTable_p, LZSWORD wWatchId_p);
LZSWORD  LzsWatchCheckInstruction (tLzsWatchTable LZSFAR* pWatchTable_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
#ifdef _LZS_SUPPORT_OPC_CONNECT
LZSBYTE LzsEnableDataRequests(LZSBYTE bConnectionId_p);
LZSBYTE LzsDisableDataRequests(LZSBYTE bConnectionId_p);
#endif

/* */
/* functions to set  */
/* */
LZSBYTE  LzsSetSingleVariable (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsSetMultiVariable (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsSetMultiVariableCont (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsSetVariable (tLzsSetData LZSFAR* pLzsSetData);
LZSBYTE  LzsWatchAddMulInstruction (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsWatchAddMulInstructionCont (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
void LzsWatchGetInfo(LZSBYTE bConnectionId_p, LZSDWORD *dwMaxWatchEntries,LZSDWORD *dwUsedWatchEntries);

/* retrieves a variable's value into the passed buffer */
LZSWORD     LzsWatchGetValue(tLzsSegTabEntry LZSFAR *pSegTab_p, tPlcSegNr SegNr_p, tPlcOffset Offset_p, 
                         tLzsAccessType AccessType_p, LZSWORD wSize_p, tPlcMemPtr pBuffer_p);

#endif
