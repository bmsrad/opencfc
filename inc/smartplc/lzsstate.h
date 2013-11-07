#ifndef _LZSSTATE_H_
#define _LZSSTATE_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

/* */
/* functions to manage the internal system status */
/* */
void  LzsSysInitStatus (void);
LZSPUBLIC32 void  LZSPUBLIC LzsSysSetStatus  (LZSWORD StatusFlag_p, LZSBYTE SetClr_p);
LZSPUBLIC32 LZSBOOL  LZSPUBLIC LzsSysGetStatus  (LZSWORD StatusFlag_p);
void  LzsSysSendMode   (void);
void  LzsSysUpdateMode (void);
LZSWORD  LzsSysCallback   (LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);

#ifdef _LZS_SUPPORT_OPC_CONNECT
LZSWORD LzsResInfoCallback(LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);
LZSPUBLIC32 void LZSPUBLIC LzsSysSetLogin(LZSBYTE bConnectionId_p);
LZSPUBLIC32 void LZSPUBLIC LzsSysClearLogin(LZSBYTE bConnectionId_p);
LZSPUBLIC32 LZSBOOL LZSPUBLIC LzsSysCheckLogin(LZSBYTE bConnectionId_p);

LZSPUBLIC32 void LZSPUBLIC LzsSysSetNetError(LZSBYTE bConnectionId_p);
LZSPUBLIC32 void LZSPUBLIC LzsSysClearNetError(LZSBYTE bConnectionId_p);
LZSPUBLIC32 LZSBOOL LZSPUBLIC LzsSysCheckNetError(LZSBYTE bConnectionId_p);

LZSPUBLIC32 LZSBOOL LZSPUBLIC LzsSysCheckLogoutDone(LZSBYTE bConnectionId_p);
LZSPUBLIC32 void LZSPUBLIC LzsSysClearLogoutDone(LZSBYTE bConnectionId_p);
LZSPUBLIC32 void LZSPUBLIC LzsSysSetLogoutDone(LZSBYTE bConnectionId_p);
#endif

/* */
/* functions to realize flow control */
/* */
LZSBYTE  LzsCtlLogin    (LZSBYTE bConnectionId_p);
LZSBYTE  LzsCtlLogout   (LZSBYTE bConnectionId_p);
LZSBYTE  LzsCtlReset    (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSPUBLIC32 LZSBYTE  LZSPUBLIC LzsCtlSetState (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSPUBLIC32 LZSBYTE  LZSPUBLIC LzsCtlRunStopSwitch( LZSBYTE bSwitchState_p);
LZSPUBLIC32 void LZSPUBLIC LzsColdStart(void);
LZSPUBLIC32 void LZSPUBLIC LzsWarmStart(void);
LZSPUBLIC32 void LZSPUBLIC LzsHotStart(void);
LZSPUBLIC32 void LZSPUBLIC LzsStop(void);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsRunInitMode(void);
LZSPUBLIC32 void LZSPUBLIC LzsCtlStopNow(void);
LZSPUBLIC32 void LZSPUBLIC LzsSetProgramMode(LZSBOOL fSet);


#endif
