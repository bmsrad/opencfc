#ifndef _LZSENV_H_
#define _LZSENV_H_

/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Do, 22 Okt  98                                                                 */
/*                                                                               */
/* DESCRIPTION: function prototypes of environment part of the runtime system    */
/*********************************************************************************/

typedef void (LZSPUBLIC *tLzsEnvSerialize) (LZSBYTE LZSFAR* pSeg_p,LZSWORD wSize_p,LZSWORD wSegNum_p,LZSWORD wProgNum_p,LZSDWORD dwUserData_p);
 
LZSPUBLIC32 LZSBYTE  LZSPUBLIC LzsEnvInitialize (void);
LZSPUBLIC32 LZSBYTE  LZSPUBLIC LzsEnvShutDown (void);

/* [SYSTEC: 04.05.2005 -rs]: function newly inserted */
LZSPUBLIC32  LZSBYTE  LZSPUBLIC LzsEnvProcess (void);

#ifdef _IP_BREAKPOINTS_
void LzsEnvBreakPointReached(
    tIpBreakPoint LZSFAR* pBreakPoint_p    /* [i] Pointer to breakpoint struct */
    );
#endif
    
void LzsEnvDisableAllOutputs(LZSWORD wMode);

LZSBYTE LzsEnvOEMCommand(LZSBYTE bConnectionId_p, LZSINT iCmd_p,LZSDWORD dwValue_p);
/*
 * functions to adapt to different enviroments
 */
LZSPUBLIC32 void  LZSPUBLIC LzsEnvResetSystem (LZSBYTE bRestartMode_p);
void  LzsEnvActivateBkgTask(void);
void LzsEnvSchedule(void);
void LzsEnvStartCmd(LZSBYTE bCommand_p);
void LzsEnvCommunicationInterrupted(LZSBYTE bConnectionId_p, LZSDWORD dElapsedTime_p);

#ifdef _USE_WATCHDOG_
void  LzsEnvResetWatchdogTimeout (void); 
#endif

#ifdef _LZS_OEM_VERSIONHANDLING_
/* [SYSTEC: 13.12.2001 -rs]: prototype inserted again */
LZSPUBLIC32 void  LZSPUBLIC LzsEnvGetPlcVersion (tLzsPlcVersion LZSFAR* pPlcVersion_p);
#endif
LZSBYTE LzsEnvCheckConfiguration(tPlcMemPtr pConfigSegment_p);
LZSBYTE LzsEnvCheckSingleSegment(tPlcMemPtr pSingleSegment_p);

void LzsEnvSysSetStatus(LZSWORD StatusFlag_p, LZSBYTE SetClr_p);
LZSBYTE  LzsEnvInitProcImg(tPlcMemPtr pProcImgSeg_p, LZSWORD wSegSize_p);
LZSBYTE  LzsEnvReadProcImg(tPlcMemPtr pProcImgSeg_p, LZSWORD wSegSize_p);
LZSBYTE  LzsEnvWriteProcImg(tPlcMemPtr pProcImgSeg_p, LZSWORD wSegSize_p);

LZSBYTE LzsEnvMoveSegment(LZSBYTE bSegType_p, LZSDWORD dwSegSize_p, tPlcMemPtr* ppSeg_p);

#ifndef _LZS_8BITBYTES_
LZSBYTE LzsEnvSizeSegment( LZSDWORD * dSegSize_p, tPlcMemPtr *ppSeg_p );
#endif

/*
 * functions to implement persistence
 */
LZSPUBLIC32 LZSCONST LZSCHAR *LzsEnvGetStorageName(void);
LZSBOOL LzsEnvSaveOpen(LZSCONST LZSCHAR * pszStorageName_p,LZSDWORD length);
LZSBOOL LzsEnvRestoreOpen(LZSCONST LZSCHAR * pszStorageName_p);
void LzsEnvRestoreClose(void);
void LzsEnvSaveClose(void);
void LzsEnvSaveByte(LZSBYTE b);
LZSBYTE LzsEnvRestoreByte(void);

#ifdef _LZS_SAVESYSTEMCMD_
LZSBYTE LzsEnvSaveSystemCmd(void);
#endif

/*
 * functions to implement retain
 */
#ifdef _LZS_RETAIN_
LZSBOOL LzsEnvEnableRetain(void);
LZSBOOL LzsEnvWriteRetain(void);
LZSPUBLIC32 LZSBOOL LZSPUBLIC LzsEnvReadRetain(void);
LZSCONST LZSCHAR* LzsEnvGetRetainStorageName(LZSBYTE bParam);
#endif

LZSBYTE LzsEnvHardwareRun(void);
void LzsEnvBeginDwlResource(void);

/* 
 * raw file download 
 */
#ifdef _LZS_DWL_RAWFILE_
LZSBYTE LzsEnvDwlRawFile(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsEnvDwlRawFileSegment(tLzsPSCmd LZSFAR* pLzsPSCmd_p, LZSBOOL fLastSegment);
LZSBYTE LzsEnvDwlContRawFileSegment(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsEnvSetFileTimeOfRawFile(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsEnvGetRawFileInfo(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsEnvCloseRawFile();
LZSBYTE LzsEnvDeleteRawFile(LZSCONST LZSCHAR* pszRawFilePath);
#endif

/*
 *    Clock
 */
LZSPUBLIC32 LZSDWORD LzsEnvGetTickCount(void);
#ifdef ENABLE_PERFORMANCE_MONITORING
LZSPUBLIC32 LZSDWORD LzsEnvGetPerformanceTickCount(void);
LZSPUBLIC32 float LzsEnvGetPerformanceDiffTime(LZSDWORD tick1, LZSDWORD tick2);
LZSPUBLIC32 void LzsEnvStartPerformanceMeasurement(tPerformanceData* pPerformanceData);
LZSPUBLIC32 void LzsEnvStopPerformanceMeasurement(tPerformanceData* pPerformanceData);
#endif
LZSPUBLIC32 void LzsEnvGetSysTime(LZSDWORD* p_dwDate, LZSDWORD* p_dwTimeOfDay);

/*
 *    Memory management
 */
void LZSFAR* LzsEnvMemAlloc(LZSDWORD dwMemSize);
void LzsEnvMemFree(void LZSFAR* pMem);
LZSBOOL IsInIecMemory(void* pMem);
void LzsEnvMemGetInfo(LZSDWORD LZSFAR* pdwMaxMem_p, LZSDWORD LZSFAR* pdwUsedMem_p);
void LZSFAR* LzsEnvMemAllocNoSegBoundary (LZSDWORD dMemSize);
LZSPUBLIC32 void LZSPUBLIC LzsEnvMemInitialize(void);
LZSPUBLIC32 void LZSPUBLIC LzsEnvClearMemory(void);
#ifdef USE_SHARED_MEMORY
LZSPUBLIC32 void LZSPUBLIC LzsEnvSharedMemInitialize(void);
#endif
void LzsEnvMemTrace(void);

/*
 *  Special memory allocation
 */
void LZSFAR* LzsEnvSpecialMalloc(LZSDWORD dwMemSize, tPlcSegType SegType);
void LzsEnvSpecialFree(void LZSFAR* pMem,tPlcSegType SegType);
void LzsEnvMemDump(void);
LZSBOOL LzsEnvMemCheck(void);

void LzsEnvInitFlash(void);


void LzsEnvGetOEMCap(LZSDWORD *pdwOEMCapInfo);

#ifdef UNDER_RTSS
 void LzsEnvWatchdogSet();
#endif /* UNDER_RTSS */

#ifdef _LZS_DATASEGDESTRUCTOR_
void LzsEnvPreFreeDataSegment(LZSWORD wPgmIndex_p, tPlcSegNr SegNr_p, LZSCONST tSegHeader *pSegHdrInf_p, LZSCONST tPlcMemPtr pSeg_p);
#endif

#ifdef _LZS_HISTDATA_

LZSBYTE LzsEnvHistInitialize(void);
LZSBYTE LzsEnvHistInitElemBuffer(LZSWORD wID_p);
void LzsEnvHistFreeElemBuffer(LZSWORD wID_p);
void LzsEnvHistRecord(LZSWORD wPgmIndex_p);
LZSBYTE LzsEnvHistGetRange(LZSWORD wCount_p, tPlcMemPtr pListOfIDs_p,
                           tPlcMemPtr *pResult_p, LZSDWORD *pdwResultSize_p, 
                           void (**ppFuncFreeResult_p)(tPlcMemPtr pResult_p, LZSDWORD dwSize_p)
                           );

#ifdef _LZS_HISTDATA_LOCKING_
LZSBOOL LzsEnvHistLockMutex(void);
void LzsEnvHistUnlockMutex(void);
#endif /* _LZS_HISTDATA_LOCKING_ */

#endif /* _LZS_HISTDATA_ */                 

#ifdef _LZS_OEMVERSINFO_
             void LzsEnvGetOemVersion(tOemVersion* sOemVersion_p);
#endif

/* [SYSTEC: 25.06.2003 -rs]: function inserted */
tLzsErrTabEntry LZSCONST*  LzsEnvGetOemLzsError (LZSBYTE bLzsErrorCode_p);
tLzsErrTabEntry LZSCONST*  LzsEnvGetOemFbError  (LZSBYTE bFbErrorCode_p);



/*-------------------------------------------------------------------------*/
/*  Fieldbus Interface functions                                           */
/*-------------------------------------------------------------------------*/

/* [SYSTEC: 22.05.2003 -rs]: changed return values from <void> to <LZSBYTE> */
LZSBYTE  LzsEnvRegisterSysState (LZSBYTE bConnectionId_p, LZSBYTE bSysState_p);

/* [SYSTEC: 22.05.2003 -rs]: changed return values of all following functions from <void> to <LZSBYTE> */
/* [SYSTEC: 02.07.2003 -rs]: Function <SysNetReInitNodeCtrl> newly inserted */
/* [SYSTEC: 20.01.2005 -rs]: Function <SysNetStartNodeScan> newly inserted */
/* [SYSTEC: 12.10.2006 -rs]: Functions <SysNetStartNodeConfig> and <SysNetExecNodeConfig> new inserted */
LZSBYTE  SysNetIoInitialize    (LZSCONST LZSBYTE LZSFAR* pInitData_p);
LZSBYTE  SysNetIoShutDown      (void);
LZSBYTE  SysNetReInitNodeCtrl  (void);
LZSBYTE  SysNetStartNodeConfig (void);
LZSBYTE  SysNetExecNodeConfig  (void);
LZSBYTE  SysNetIoCreate        (tPlcMemPtr pNetImgCache_p, tPlcSegSize wNetImgCacheSize_p);
LZSBYTE  SysNetIoDestroy (void);
LZSBYTE  SysNetIoStart   (LZSBYTE bStartMode_p);
LZSBYTE  SysNetIoStop    (void);
LZSPUBLIC32 LZSBYTE  SysNetIoProc    (void);
LZSPUBLIC32 LZSBYTE  SysNetIoErrInit (void);

/* P0699-specific */
LZSBYTE LzsEnvProcessHwConfig(void);
LZSBYTE LzsEnvApplyExecutionOrder(LZSWORD* pStart);

/* reboot the PLC, e.g. after firmware download */
LZSBYTE LzsEnvRebootPlc();

#ifdef USE_DATA_CONSISTENCY_SHM
LZSBYTE LzsEnvProcessSHMConfig(void);
LZSWORD GetLastSHMDCSegment(LZSWORD* pStart);
LZSWORD GetNumClientsForSHMDCSegment(LZSWORD wSeg, LZSWORD* pStart);
LZSDWORD GetSHMDCSegmentChecksum(tPlcMemPtr pSHMConfigSeg, LZSWORD wSize);
LZSDWORD CalcTotalSHMDCMemSize(LZSWORD* pStart);
LZSBYTE InitSHMDCMemory(LZSWORD* pStart);
void ClearSHMDCMemory();
LZSBYTE SetOwnBuffers(LZSWORD* pStart);
LZSBYTE SetSourceBuffers(LZSWORD* pStart);
LZSBYTE SetBufferInfo();
LZSBOOL CheckSHMDCValid();
void SetSHMDCWriteBuffer(LZSWORD wTask);
void SetSHMDCReadBuffers(LZSWORD wTask);
void PublishSHMDCWriteBuffer(LZSWORD wTask);
void UnlockSHMDCReadBuffers(LZSWORD wTask);
#endif

#ifdef USE_DATA_CONSISTENCY
void SetDCBuffers(LZSWORD wTask);
void UnlockDCBuffers(LZSWORD wTask);
#endif

#define ALIGN_4_W(x) ((x + 3) & 0xFFFC)
#define ALIGN_4_DW(x) ((x + 3) & 0xFFFFFFFC)

/* defines for PPC op-codes */
#define BO_ALWAYS				20
#define BO_CONDITION_TRUE		12
#define BO_CONDITION_FALSE		 4

#define BI_CONDITION_LT			 0
#define BI_CONDITION_GT			 1
#define BI_CONDITION_EQ			 2
#define BI_CONDITION_SO			 3

#define ADDI(D, A, Imm) ((14 << 26) | ((LZSDWORD)D << 21) | ((LZSDWORD)A << 16) | Imm)
#define ADDIS(D, A, Imm) ((15 << 26) | ((LZSDWORD)D << 21) | ((LZSDWORD)A << 16) | Imm)
#define ORI(A, S, Imm) ((24 << 26) | ((LZSDWORD)S << 21) | ((LZSDWORD)A << 16) | Imm)
#define ADDX(D, A, B) ((31 << 26) | ((LZSDWORD)D << 21) | ((LZSDWORD)A << 16) | ((LZSDWORD)B << 11) | 532)

#define STW(S, A, d)  ((36 << 26) | ((LZSDWORD)S << 21) | ((LZSDWORD)A << 16) | (LZSWORD)d)
#define STH(S, A, d)  ((44 << 26) | ((LZSDWORD)S << 21) | ((LZSDWORD)A << 16) | (LZSWORD)d)
#define STB(S, A, d)  ((38 << 26) | ((LZSDWORD)S << 21) | ((LZSDWORD)A << 16) | (LZSWORD)d)
#define LWZ(D, A, d)  ((32 << 26) | ((LZSDWORD)D << 21) | ((LZSDWORD)A << 16) | (LZSWORD)d)
#define LHZ(D, A, d)  ((40 << 26) | ((LZSDWORD)D << 21) | ((LZSDWORD)A << 16) | (LZSWORD)d)
#define LBZ(D, A, d)  ((34 << 26) | ((LZSDWORD)D << 21) | ((LZSDWORD)A << 16) | (LZSWORD)d)

#define STWU(S, A, d) ((37 << 26) | ((LZSDWORD)S << 21) | ((LZSDWORD)A << 16) | (LZSWORD)d)
/*
 * --- doesn't work ?!?!?!?!?! ----
#define BCLRX(bo, bi, x) ((19 << 26) | ((LZSDWORD)bo << 21) | ((LZSDWORD)bi << 16) | 32 | x)
*/
#define RET 0x4E800020

#define BLRL 0x4E800021
#define MFLR(r) ( (LZSDWORD) 0x7C0802A6 | (LZSDWORD) r)
#define MTLR(r) ( (LZSDWORD) 0x7C0803A6 | (LZSDWORD) r)

#define CMPI(cr, A, Imm) 		((0x0B<<26) | (cr<<23) | (1<<21) | (A<<16) | Imm)
#define BCX(bo, bi, Addr)		((0x10<<26) | (bo<<21) | (bi<<16) | (Addr<<2))

#define NANDX(S, A, B)			((0x1F<<26) | (S<<21) | (A<<16) | (B<<11) | 0x3B8)
#define ANDI(S, A, Imm)			((0x1C<<26) | (S<<21) | (A<<16) | Imm)


#endif /* _LZSENV_H_ */



