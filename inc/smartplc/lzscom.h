#ifndef _LZSCOM_H_
#define _LZSCOM_H_

/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION: funtions to control the runtime system an realize the command    */
/*                 and the data server                                                 */
/*********************************************************************************/

#define LZS_CON_ID_PROGSYS 0

/* */
/* functions to control and encapsulate the RTS */
/* */
void  LzsPlcStart       (LZSBYTE bStartMode_p);
void  LzsPlcStop        (void);

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsIpMainLoop                                                    */
/* DESCRIPT: this function runs the RuntimeKernel to execute the IEC-1131     */
/*           program, loaded to the PLC                                       */
/*----------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBOOL  LZSPUBLIC LzsIpMainLoop(tTaskControl* pTaskControl);

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsCmdMainLoop                                                   */
/* DESCRIPT: this function checks the communication line to the programming   */
/*           system and executes commands received from it                    */
/*----------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBOOL  LZSPUBLIC LzsCmdMainLoop(void);

LZSPUBLIC32 LZSBOOL  LZSPUBLIC LzsCmdMainLoopOPC(void);


LZSBYTE  LzsPlcExecPSCmd   (tLzsPSCmd LZSFAR* pLzsPSCmd_p);

#ifdef _LZS_SUPPORT_OPC_CONNECT
LZSBYTE  LzsPlcExecOPCCmd  (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
#endif

LZSWORD  LzsPlcErrCallback (tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);

LZSBYTE LzsOEMSendCmd(LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);

/*
 * functions for command control of the SPS
 */
void  LzsCsvInitCmdServer (LZSBYTE bConnectionId_p);
void  LzsCsvSetMaxRecSize     (LZSBYTE bConnectionId_p, LZSWORD wMaxRecSize_p);
void  LzsCsvUnlockCmdReceipt  (LZSBYTE bConnectionId_p);
void  LzsCsvEnableCmdReceipt  (LZSBYTE bConnectionId_p);
void  LzsCsvPresetCmd (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p, LZSBYTE bMode_p);

LZSBOOL  LzsCsvCheckCmdReceipt   (tLzsPSCmd LZSFAR* pLzsPSCmd_p);

LZSBOOL LzsCsvSendLockTime(LZSBYTE bConnectionId_p, LZSDWORD dwLockTime_p);

#ifdef _LZS_SUPPORT_OPC_CONNECT
LZSBOOL  LzsCsvCheckCmdReceiptOPC   (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
#endif

void  LzsCsvReadCommand       (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBOOL  LzsCsvSetExtRetCode     (LZSBYTE bConnectionId_p, tPlcMemPtr pExtErrCode_p, LZSWORD wSize_p);
void  LzsCsvSendReceipt       (LZSBYTE bConnectionId_p, LZSBYTE bErrCode_p);
LZSBYTE  LzsCsvSendRequestedData (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);

/*
 * functions to manage asynchronous internal data
 */
void  LzsDsvInitDataServer (void);
LZSBYTE  LzsDsvGetEventHandle (void);
LZSBOOL  LzsDsvSignalEvent    (LZSBYTE bConnectionId_p, tEventCallback pEventCallBack_p, LZSBYTE bEventHandle_p);
LZSWORD  LzsDsvExecEventHdlr  (LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p,LZSWORD wBuffSize_p,LZSBYTE bMode_p);


/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsRestartNetAndSetNeterror                                      */
/* DESCRIPT: when a networkerror occures the network layer has to be restered */
/*           the internal state LZSSTAT_NETERROR is set until the next valid     */
/*             command is receipt                                               */
/*----------------------------------------------------------------------------*/
/* [SYSTEC 26.06.2003 -rs]: Parameter <LZSBYTE bNetStat_p> newly inserted */
/*-----------------------------------------------------------------------*/
/* void LzsRestartNetAndSetNetError(void);                               */
/*-----------------------------------------------------------------------*/
void LzsRestartNetAndSetNetError (LZSBYTE bConnectionId_p, LZSBYTE bNetStat_p);
/*-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*  wait for finish of data shipment                                    */
/*-------------------------------------------------------------------------*/
/* [SYSTEC: 30.04.2003 -rs]: functions added in the context of non-blocking*/
/*                           network functions                             */
/*-------------------------------------------------------------------------*/
#ifdef _NET_USE_NONBLOCKING_API_
LZSBYTE  LzsCsvWaitForNetSendCompletion (LZSDWORD dwTimeOut_p);
#endif


#endif /*_LZSCOM_H_*/
