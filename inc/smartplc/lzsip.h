#ifndef _LZSIP_H_
#define _LZSIP_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION: functions to                                                                   */
/*********************************************************************************/

/* */
/* functions to control the interpreter */
/* */
void LzsIpInitIpControl(void);
LZSBYTE LzsIpGetIpErrCode(void);
LZSBYTE LzsIpInitTask(LZSBOOL fOnlineEdit);
LZSBYTE LzsIpRunCycle(tTaskControl* pTaskControl);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsIpOnSystemTick(LZSDWORD dSystemTick_p);

LZSWORD LzsIpErrCallback(LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);
LZSWORD LzsDumpCallback(LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);

/* B.S. 18.05.98 */
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsIpTriggerInterruptString(LZSCONST LZSCHAR LZSFAR* pszInterruptName_p);

/* */
/* substitute C-Standard functions */
/* */
void MemCopy(tPlcMemPtr pDst, tPlcMemPtr pSrc, tPlcByteCount wLen);
void StrCopy(LZSCHAR LZSFAR* pDst, LZSCONST LZSCHAR LZSFAR* pSrc);
LZSUINT StrLen(LZSCONST LZSCHAR *pStr);
#ifdef _LZS_DSALIGNMENT_DSP563_
    void MemCopy_LMem(tPlcMemPtr pDst, tPlcMemPtr pSrc, tPlcByteCount wLen);
    int MemCopy_1_to_6(tPlcMemPtr pDst, tPlcMemPtr pSrc, int iLen);
#endif
void LzsIecInitFrmwBlcks(void);
void LzsIecCloseFrmwBlcks(void);  /* [SYSTEC/CANopen: 23.08.2006 -rs]: function inserted */
void LzsIecSetFBTable(void);

/* */
/* Internal functions */
/* */
void LzsDbgTraceSegmentTable(void);


/*-------------------------------------------------------------------------*/
/* [SYSTEC: 02.05.2003 -rs]: the following functions newly inserted        */
/*                           for execution of                              */
/*                           Start/Stop/Error-Tasks                        */
/*-------------------------------------------------------------------------*/

typedef enum
{
    kEventTaskUnknown          =  0,
    kEventTaskColdStart        =  1,
    kEventTaskWarmStart        =  2,
    kEventTaskHotStart         =  3,
    kEventTaskSingleCycleStart =  4,
    kEventTaskHardStop         =  5,
    kEventTaskSoftStop         =  6,
    kEventTaskSingleCycleStop  =  7,
    kEventTaskProgExecError    =  8,
    kEventTaskDivByZeroError   =  9,
    kEventTaskArrayIndexError  = 10,
    kEventTaskFwFbExecError    = 11,
	kEventTaskWinShutdown	   = 12,
	kEventTaskBlueScreen	   = 13,
	kEventTaskIecCycleError	   = 14,
	kEventTaskRtxBaseTimerError	= 15
} tEventTaskType;

typedef enum
{
    kEventTaskSuccess     = 0,
    kEventTaskNoEventTask = 1

} tEventTaskErrorCode;



LZSBYTE  LzsIpEventTaskSearch   (void);
LZSBYTE  LzsIpEventTaskSignal   (tEventTaskType EventTaskType_p);
LZSBYTE  LzsIpEventTaskRunCycle (void);
LZSBYTE  LzsIpEventTaskFinished (void);
LZSBYTE  LzsIpEventTaskRunCtrl  (LZSBOOL  fRunRequest_p,
                                 LZSBOOL             LZSFAR* pfRunState_p,
                                 tEventTaskType      LZSFAR* pEventCode_p,
                                 LZSDWORD            LZSFAR* pdwEventTaskStartTime_p,
                                 LZSDWORD            LZSFAR* pdwEventTaskCycles_p,
                                 tEventTaskErrorCode LZSFAR* pErrorCode_p);


#endif /*_LZSIP_H_*/
