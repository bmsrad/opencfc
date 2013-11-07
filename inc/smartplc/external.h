/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 9 , D-91088 Bubenreuth                     */
/* (C) 2001                                                                      */
/*                                                                               */
/*                                                                               */
/* DESCRIPTION: extern declaration of global variables                                                 */
/*********************************************************************************/
#ifndef _EXTERNAL_H_
#define _EXTERNAL_H_

#include    "oem/config.h"        /* configuration defines */
#include    "oem/odk_prj.h"

#include    "smartplc/odk_plc.h"       /* P158 global */
#include    "smartplc/odk_szm.h"
#include    "smartplc/lzs.h"

#include    "p163ip/ip_def.h"           /* IP   lokal */
#include    "p163ip/ip_opc.h"           /* IP   lokal */
#include    "p163ip/ip_cmds.h"          /* IP   lokal */

#include    "tskScheduler/userConfig.h"
#include    "tskScheduler/tskConfig.h"
#include    "tskScheduler/tskScheduler.h"

void LzsGlobalsInit(void);

extern LZSWORD wNumberOfPrograms_g;
extern LZSBYTE Error_g; /* global variable for return value <IpCycle, LzsNccCallNc, IpRunBLCode> */

extern LZSWORD wLzsSysFlags_l;

#ifdef _DUMP_FUNCTION_
extern LZSBYTE DumpBuffer_g[DUMP_BUFFER_SIZE];
#endif

extern LZSBOOL bProgramModeSet;

extern tProgSysVersion LZSFAR LoggedInProgSysVersion;

#ifdef _IP_PFLOW_
extern LZSBOOL     LZSNEAR  fPflowEnable_g;      /* Flag Powerflow Ein/Aus */
/* B.S. FHL 2001/401 (Pflow Blinks with SFC)*/
extern LZSBOOL fPflowInstanceWasReached_g;
extern tLzsPflowRange LzsPflowRange_g;   /* Struktur mit Pflow-Range */
extern LZSBOOL fPflowChangeRange_g;
extern LZSBOOL fPflowStop_g;

#ifndef PFLOWADMINSIZE
    #ifndef _LZS_8BITBYTES_
        #define PFLOWADMINSIZE    ((LZS_NET_SIZEOF_BYTE+LZS_NET_SIZEOF_WORD) / LZS_NET_SIZEOF_BYTE)
    #else
        #define PFLOWADMINSIZE    ((LZS_SIZEOF_BYTE+LZS_SIZEOF_WORD) / LZS_SIZEOF_BYTE)
    #endif
#endif

extern LZSBYTE  LZSFAR  PflowBuff_l[LZSPFLOWBUFFSIZE];  /* Puffer für Powerflowdaten */
extern LZSWORD       wUsedPflowBuffSize_l;        /* Füllstand Powerflow-Puffer */
extern LZSBOOL       fPflowActive_l;              /* Flag Poweflow On/Off */
extern LZSBYTE       bLzsPlowEventHandle_l;       /* Handle für CallBack-Funktion */
#endif

extern LZSWORD  LZSNEAR  wPtrRef;
extern LZSBYTE bBitMask;
extern LZSWORD  LZSNEAR  hFarDS;
extern LZSWORD  LZSNEAR  wOffs;
extern LZSBOOL  LZSNEAR  fRetCode;

/* Variablen fuer Standardfunktionen (Verwendung nur in IP_CMDS3.C) */
/* und ggf. Powerflow */
extern LZSBOOL  LZSNEAR  fBit;

/* for CRC checksums */
extern LZSBOOL bCRCLookupInitialized;
extern LZSDWORD crcLookupTable[0x100];

#ifdef IP_TIME
extern LZSDWORD  LZSNEAR  dCycleStartTime;           /* Hilfsvar. für Zykluszeitmessung */
#endif

extern tPlcPgmNr        wPflowPgmNr_g;                    /* Program for pflow */

extern tPlchInst        hPflowInst_g;               /* Instanzhandle PowerFlow-Sektion */
extern tPlcOffset        wPflowStartOffs_g;          /* Startoffset PowerFlow-Sektion */
extern tPlcOffset        wPflowEndOffs_g;            /* Endoffset PowerFlow-Sektion */
extern LZSWORD            wPflowDataBuffSize_g;       /* Puffer-Groesze f. PowerFlow-Daten */

extern LZSWORD            wIPOffs_g;                  /* akt. Offs. des Instructionpointers */

extern tPlcMemPtr        pDataBuff_g;                /* Ptr auf PowerFlow-Datenpuffer */
extern LZSWORD            wUsedBuffSize_g;            /* belegeter PowerFlow-Datenpuffer */
extern LZSBOOL            fPflowOK_g;                 /* Flag "OK / Fehler" */
extern LZSBOOL            fPflowBuffOK_g;               /* buffer for powerflow data valid  */

/*  Zur Mitfuehrung des AE-Types bei Push-/Pop-Befehlen wird ein separates
    Stacksegment verwendet, das als Secundary-Segment des "regulaeren"
    AE-Stacksegmentes behandelt wird. Daher ist die Nummer des AE-
    Stacksegmentes aufzubewahren. Zum Aufbau des Stacks siehe die
    Funktionen <LzsMemCrPushAEType> und <LzsMemCrPopAEType>.
                                                                           */
extern LZSWORD   UsedIStackEntrys;                /* akt. Stacktiefe Instanz-Stack */
extern LZSWORD   MaxIStackEntrys;                 /* max. Stacktiefe Instanz-Stack */
extern LZSWORD   UsedAStackEntrys;                /* akt. Stacktiefe AE-Stack */
extern LZSWORD   MaxAStackEntrys;                 /* max. Stacktiefe AE-Stack */


/* Number of all Breakpoints set */
extern LZSWORD wBreakPointNum_g;
extern LZSBOOL fBreakEnable_g;
extern LZSBOOL fSingleStep_g;
extern LZSWORD wSingleStepPrg_g;
extern LZSWORD wLastBreakPointPrg_g;

/*-----------------------------------------------------------------------------------------*/
/*from lzstable.c*/
extern tSegmentChangeInfo sSegChgInfo_g;
extern tPlcSegNr    nTempSegNumber_l;
extern tPlcPgmNr   nTempPrgNumber_l;
extern tPlcMemPtr    pTempSeg_l;
extern LZSBOOL        fTempSegToExchange_l;        /*flag to tell the kernel there is segment to exchange*/

/*-----------------------------------------------------------------------------------------*/
/*from lzsdwl.c*/
/*-fg- 19991223*/
extern LZSBYTE    fDwlIsPIallocated_g;
extern tPlcMemPtr pCopyTableSegment_g;

#ifdef _LZS_PRAGMANOCLEAR_                        /* tell some compilers not to reset variable on startup*/
#pragma noclear
#endif
extern tLzsResourceGlobData ResourceGlobalData_g;

#ifdef _LZS_NETVARS_
tPlcMemPtr pNetImageCopy_g;

#endif

#ifdef _LZS_PRAGMANOCLEAR_
#pragma clear
#endif

/*-----------------------------------------------------------------------------------------*/
/*from stdfb.c*/
extern LZSDWORD dColdStartTime_g;
extern LZSDWORD dLastCSTime_g;

/*-----------------------------------------------------------------------------------------*/
/*from lzsip.c*/
/*--------------------------------------------------------------------------- */
/*  BEGIN Variables that should not be cleared when SAVERAM is used           */
/*--------------------------------------------------------------------------- */
#ifdef _LZS_PRAGMANOCLEAR_
#pragma noclear
#endif
    /*--------------------------------------------------------------------------- */
    /*  Variablen zur Verwaltung des Prozeßabbildes */
    /*--------------------------------------------------------------------------- */
extern tPlcMemPtr pProcImgSeg_l; /* Pointer to Segment with Processimage */
extern tPlcSegNr ProcImgSegNum_l; /* Segmentnumber of Processimage Segment */
extern LZSWORD wProcImgSegSize_l; /* Size of the Segment */

extern tLzsResourceSegmentTables LZSFAR* pSegmentTables_l; /* array; one tLzsResourceSegmentTables structure for each program */
extern tLzsResourceSegmentTables LZSFAR* pSegmentTables2_l; /* array; one tLzsResourceSegmentTables structure for each program AND system task */

    /* Variablen zur allgemeinen Programmverwaltung */
extern LZSWORD        wPgmCount_g;        /* Count of Programs downloaded                 */
extern LZSWORD        wPgm0TaskIndex_g;    /* Index of prg 0 = resource global */
extern LZSWORD        nLastSegPgm0_g;        /* last resource global segment  */
extern LZSWORD        nLastSegPgm0Linked_g; /* last segment linked from task 0 to other tasks */

#ifdef _LZS_PRAGMANOCLEAR_
#pragma clear
#endif
/*--------------------------------------------------------------------------- */
/*  END Variables that should not be cleared when SAVERAM is used           */
/*--------------------------------------------------------------------------- */

extern LZSWORD        wNonSleepingTasks_l;
extern LZSBYTE        bLzsIpEventHandle_l;        /* Handle für CallBack-Funktion */
extern LZSBYTE        bLzsDumpEventHandle_l;

/*-------------------------------------------------------------------------*/
/* [SYSTEC: 02.05.2003 -rs]: Inserted new variables for executing           */
/*                           start/stop/error-tasks                        */
/*-------------------------------------------------------------------------*/
extern LZSWORD         wStartTaskNum_g;
extern LZSWORD         wStopTaskNum_g;
extern LZSWORD         wErrorTaskNum_g;
extern LZSWORD         wWinShutdownTaskNum_g;
extern LZSWORD         wSignaledEventTaskNum_g;
extern tEventTaskType  SignaledEventTaskType_g;
extern LZSDWORD        dwEventTaskCycles_g;
extern LZSDWORD        dwEventTaskStartTime_g;
/*-------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------*/
/*from lzstable.c*/
/*--------------------------------------------------------------------------- */
/*  BEGIN Variables that should not be cleared when SAVERAM is used           */
/*--------------------------------------------------------------------------- */
#ifdef _LZS_PRAGMANOCLEAR_
#pragma noclear
#endif
/*  Variablen zur Verwaltung der TaskDefinitionTable */
extern tPlcTaskDefTable  LZSFAR*  pTaskDefTab_l;  /* Pointer auf TaskDefinitionTab */
extern tPlcMemPtr              pTaskDefSeg_l;  /* Pointer auf Seganfang (für FREE) */
#ifdef _LZS_PRAGMANOCLEAR_
#pragma clear
#endif
/*--------------------------------------------------------------------------- */
/*  END Variables that should not be cleared when SAVERAM is used           */
/*--------------------------------------------------------------------------- */
extern tLzsResourceSegmentTables LZSFAR* pSegmentTablesSAVE_l;
extern tPlcTaskDefTable       LZSFAR* pTaskDefTabSAVE_l;    /* pointer to saved tdt */

#ifdef _LZS_TASKINFO_

extern    LZSWORD wCurrTask_g;
extern    tTaskInfo *sTaskInfos_g;

#endif

/*--------------------------------------------------------------------------- */
/*  Variables to handle firmware blocks / from lzsfirm.c                     */
/*--------------------------------------------------------------------------- */

extern tLzsIecFB LZSCONST*  fpIecFBTab_l[LZS_FIRMWARETABS];         /* Pointer auf Sprungtabelle */
extern LZSWORD              wFBTabEntrys_l[LZS_FIRMWARETABS];       /* Anzahl Einträge in Sprungtabelle */
extern LZSBYTE              bIecFBErr_l;          /* ErrorCode eines Firmware-FB */

/*--------------------------------------------------------------------------- */
/*  for forcing                     */
/*--------------------------------------------------------------------------- */

/*remember time of last communication*/
#ifndef _LZS_SUPPORT_OPC_CONNECT
extern LZSDWORD    dwLastCommandTime_g;
#else
extern LZSDWORD arrLastCommandTimes_g[1+_LZS_MAX_NUMBER_OPC_CONNECTIONS];
#endif

#ifndef _LZS_SUPPORT_OPC_CONNECT
extern LZSDWORD dwLockedTime_g;
#else
extern LZSDWORD arrLockedTimes_g[1+_LZS_MAX_NUMBER_OPC_CONNECTIONS];
#endif

#ifdef _LZS_SUPPORT_OPC_CONNECT
tLzsResVersion oldResVersion_g;
LZSBYTE bLzsResInfoEventHandle_g;
#endif

extern LZSWORD  wByrefInfoSegment_g;

/* global variale to store the current control command */
extern tLzsCtrLst eCurrentStartMode;
extern LZSDWORD dwStartCycleTime_g;
extern LZSDWORD dwCycleTime_g;

/* returned with login command reply*/
extern LZSDWORD dwLZSCapabilities[10];

extern LZSDWORD dwForceEntriesUsed_g;

extern LZSWORD wDeCorrectRefOffset_g;

/*--------------------------------------------------------------------------- */
/*  for retain                                                                */
/*--------------------------------------------------------------------------- */
#ifdef _LZS_RETAIN_
extern tPlcMemPtr pRetainTable_g;
extern LZSWORD wRetainTableEntries_g;
extern tPlcMemPtr pRetainData_g;
extern LZSDWORD dwRetainDataSize_g;
#endif

/* handle for watch callback function */
extern LZSBYTE bLzsWatchEventHandle_g;

/*--------------------------------------------------------------------------- */
/*  for task/program switch (P0699-specific)                                  */
/*--------------------------------------------------------------------------- */
extern tLzsResourceSegmentTables LZSFAR* pCurrentProgramData_g;

/*--------------------------------------------------------------------------- */
/*  for shared memory (P0699-specific)                                        */
/*--------------------------------------------------------------------------- */


#ifdef USE_SHARED_MEMORY
/* extern SHM_BUFFER* pShmBuff_g; */
extern SHM_BUFFER* pShmBuff_g;
#ifdef USE_DATA_CONSISTENCY_SHM
extern LZSBYTE* pShmDCBuff_g;
extern LZSDWORD* pShmDCChecksum_g;
extern LZSBYTE* pShmDCIndex_g;
extern LZSDWORD dwSHMSize_g; /* (only used by the master CPU) */
extern LZSDWORD dwShmDCChecksum_g;
extern SEM_ID shmDCSemId_g;
#endif
#endif

extern LZSBYTE staticNullSegment_g[16];

/*--------------------------------------------------------------------------- */
/*  for configuration data (P0699-specific)                                   */
/*--------------------------------------------------------------------------- */
extern tTaskConfig* pTaskConfig_g;
extern tTargetConfig* pTargetConfig_g;
extern LZSWORD* pExecOrderConfig_g;

/*--------------------------------------------------------------------------- */
/*  for program execution control (P0699-specific)                            */
/*--------------------------------------------------------------------------- */
extern tTaskControl arrayControlSets_g[NUM_TASKS * NUM_MODES];
#ifndef _ONE_TASK_ONLY_T1_
extern tTaskControl* pControlSetI1I;
extern tTaskControl* pControlSetI1S;
extern tTaskControl* pControlSetI1FI;
extern tTaskControl* pControlSetI1N;
extern tTaskControl* pControlSetI1FE;
extern tTaskControl* pControlSetI2I;
extern tTaskControl* pControlSetI2S;
extern tTaskControl* pControlSetI2FI;
extern tTaskControl* pControlSetI2N;
extern tTaskControl* pControlSetI2FE;
extern tTaskControl* pControlSetI3I;
extern tTaskControl* pControlSetI3S;
extern tTaskControl* pControlSetI3FI;
extern tTaskControl* pControlSetI3N;
extern tTaskControl* pControlSetI3FE;
extern tTaskControl* pControlSetI4I;
extern tTaskControl* pControlSetI4S;
extern tTaskControl* pControlSetI4FI;
extern tTaskControl* pControlSetI4N;
extern tTaskControl* pControlSetI4FE;
extern tTaskControl* pControlSetI5I;
extern tTaskControl* pControlSetI5S;
extern tTaskControl* pControlSetI5FI;
extern tTaskControl* pControlSetI5N;
extern tTaskControl* pControlSetI5FE;
extern tTaskControl* pControlSetI6I;
extern tTaskControl* pControlSetI6S;
extern tTaskControl* pControlSetI6FI;
extern tTaskControl* pControlSetI6N;
extern tTaskControl* pControlSetI6FE;
extern tTaskControl* pControlSetI7I;
extern tTaskControl* pControlSetI7S;
extern tTaskControl* pControlSetI7FI;
extern tTaskControl* pControlSetI7N;
extern tTaskControl* pControlSetI7FE;
extern tTaskControl* pControlSetI8I;
extern tTaskControl* pControlSetI8S;
extern tTaskControl* pControlSetI8FI;
extern tTaskControl* pControlSetI8N;
extern tTaskControl* pControlSetI8FE;
#endif
extern tTaskControl* pControlSetT1I;
extern tTaskControl* pControlSetT1S;
extern tTaskControl* pControlSetT1FI;
extern tTaskControl* pControlSetT1CI;
extern tTaskControl* pControlSetT1N;
extern tTaskControl* pControlSetT1CE;
extern tTaskControl* pControlSetT1FE;
#ifndef _ONE_TASK_ONLY_T1_
extern tTaskControl* pControlSetT2I;
extern tTaskControl* pControlSetT2S;
extern tTaskControl* pControlSetT2FI;
extern tTaskControl* pControlSetT2CI;
extern tTaskControl* pControlSetT2N;
extern tTaskControl* pControlSetT2CE;
extern tTaskControl* pControlSetT2FE;
extern tTaskControl* pControlSetT3I;
extern tTaskControl* pControlSetT3S;
extern tTaskControl* pControlSetT3FI;
extern tTaskControl* pControlSetT3CI;
extern tTaskControl* pControlSetT3N;
extern tTaskControl* pControlSetT3CE;
extern tTaskControl* pControlSetT3FE;
extern tTaskControl* pControlSetT4I;
extern tTaskControl* pControlSetT4S;
extern tTaskControl* pControlSetT4FI;
extern tTaskControl* pControlSetT4CI;
extern tTaskControl* pControlSetT4N;
extern tTaskControl* pControlSetT4CE;
extern tTaskControl* pControlSetT4FE;
extern tTaskControl* pControlSetT5I;
extern tTaskControl* pControlSetT5S;
extern tTaskControl* pControlSetT5FI;
extern tTaskControl* pControlSetT5CI;
extern tTaskControl* pControlSetT5N;
extern tTaskControl* pControlSetT5CE;
extern tTaskControl* pControlSetT5FE;
#endif

/*--------------------------------------------------------------------------- */
/*  for shared memory data consistency (P0699-specific)                       */
/*--------------------------------------------------------------------------- */
extern LZSWORD wFirstSegNumSHMDCBuffers;
extern LZSWORD wLastSegNumSHMDCBuffers;

#ifdef USE_DATA_CONSISTENCY_SHM
/* for each shared memory data consistency buffer segment: structure with buffer information to be used at runtime; ALLOCATED and initialized when processing the shared memory configuration */
extern tSHMDCBufferInfo* array_BufferInfo;

/* for each task on this CPU: segment number of own buffer segment; to be set when processing the shared memory configuration */
extern LZSWORD array_wSHMDCOwnBuffers[NUM_TASKS];

/* for each task: list of segment numbers of buffer segments where the task is client; ALLOCATED and initialized when processing the shared memory configuration */
extern LZSWORD* array_pSHMDCSourceBuffers[NUM_TASKS];

/* for each task: list of pointers to buffer segments where the task is client; ALLOCATED when processing the shared memory configuration, used during buffer selection to minimize the bus lock times */
extern LZSBYTE** array_pSHMDCSourceBufferPointers[NUM_TASKS];

/* for each task: buffer number for the current write buffer; to be set on task start */
extern LZSWORD array_wSHMDCWriteBuffer[NUM_TASKS];

/* for each task: list of buffer numbers of buffer segments which are locked by the task; ALLOCATED and initialized when processing the shared memory configuration */
extern LZSWORD* array_pSHMDCLockedBuffers[NUM_TASKS];
#endif

/*--------------------------------------------------------------------------- */
/*  for hardware configuration and communication proxy (P0699-specific)       */
/*--------------------------------------------------------------------------- */
extern LZSBYTE bSlotNumber_g;
extern LZSBYTE bProxyLogicalSlotNumber_g;

/*--------------------------------------------------------------------------- */
/*  from tskScheduler.c (P0699-specific)                                      */
/*--------------------------------------------------------------------------- */
extern int volatile  *temp_addr;

extern int globalError;

extern unsigned char mode;							/*mode=0: init mode; mode=1: system mode; mode=2: normal mode - please use enum tFBModes from tskScheduler.h (=> kInitMode/kSystemMode/kNormalMode)!*/

extern float    dps_t0;						/*T0 time cycle value in milliseconds (e.g. for 0.1 ms, dps_t0 is 0.1)*/
extern unsigned int dps_t0_us;				/*T0 time cycle value in microseconds (e.g. for 0.1 ms, dps_t0_us is 100) - to avoid floating point inaccuracies*/

extern float  dps_ta;						/*sampling time ('ta') for the currently executing task, in milliseconds*/

extern float	 dps_t1_ta;					/*'ta' value of task T1, in milliseconds (calculated from T0 and the task's multiplication factor)*/
extern float	 dps_t2_ta;					/*'ta' value of task T2, in milliseconds (calculated from T0 and the task's multiplication factor)*/
extern float	 dps_t3_ta;					/*'ta' value of task T3, in milliseconds (calculated from T0 and the task's multiplication factor)*/
extern float	 dps_t4_ta;					/*'ta' value of task T4, in milliseconds (calculated from T0 and the task's multiplication factor)*/
extern float	 dps_t5_ta;					/*'ta' value of task T5, in milliseconds (calculated from T0 and the task's multiplication factor)*/

extern float	 dps_i1_ta;					/*'ta' value of task I1, in milliseconds ("equivalent sampling time" configured by the user)*/
extern float	 dps_i2_ta;					/*'ta' value of task I2, in milliseconds ("equivalent sampling time" configured by the user)*/
extern float	 dps_i3_ta;					/*'ta' value of task I3, in milliseconds ("equivalent sampling time" configured by the user)*/
extern float	 dps_i4_ta;					/*'ta' value of task I4, in milliseconds ("equivalent sampling time" configured by the user)*/
extern float	 dps_i5_ta;					/*'ta' value of task I5, in milliseconds ("equivalent sampling time" configured by the user)*/
extern float	 dps_i6_ta;					/*'ta' value of task I6, in millseconds ("equivalent sampling time" configured by the user)*/
extern float	 dps_i7_ta;					/*'ta' value of task I7, in milliseconds ("equivalent sampling time" configured by the user)*/
extern float	 dps_i8_ta;					/*'ta' value of task I8, in milliseconds ("equivalent sampling time" configured by the user)*/



/*****************************************/
extern unsigned char board_Msg;     /*this variable defines the board's master mode or slave mode*/

extern unsigned int task_Status_sys;   /*used to define the tasks' status (system mode)*/
extern unsigned int task_Status_nor;   /*used to define the tasks' status (normal mode)*/

/* counters for cycle errors */
extern unsigned int T1CycleErrorCount;
#ifndef _ONE_TASK_ONLY_T1_
extern unsigned int T2CycleErrorCount;
extern unsigned int T3CycleErrorCount;
extern unsigned int T4CycleErrorCount;
extern unsigned int T5CycleErrorCount;
extern unsigned int I1CycleErrorCount;
extern unsigned int I2CycleErrorCount;
extern unsigned int I3CycleErrorCount;
extern unsigned int I4CycleErrorCount;
extern unsigned int I5CycleErrorCount;
extern unsigned int I6CycleErrorCount;
extern unsigned int I7CycleErrorCount;
extern unsigned int I8CycleErrorCount;
#endif

extern unsigned char T0_sem_cnt;  /*to record the T0's semaphore numbers, normaly it should be 1*/

/**************TASK RELATIONS DEFINE ******************/

extern int Task1Para;     /*task cycle parameter for T1*/
extern int Task2Para;     /*task cycle parameter for T2*/
extern int Task3Para;     /*task cycle parameter for T3*/
extern int Task4Para;     /*task cycle parameter for T4*/
extern int Task5Para;     /*task cycle parameter for T5*/

extern unsigned int TicksCounter;    /* count the ticks */

#ifdef SCHEDULER_DEBUG
extern unsigned int SYSCounter;
extern unsigned int T1SCounter;
extern unsigned int T1NCounter;
extern unsigned int T2SCounter;
extern unsigned int T2NCounter;
extern unsigned int T3SCounter;
extern unsigned int T3NCounter;
extern unsigned int T4SCounter;
extern unsigned int T4NCounter;
extern unsigned int T5SCounter;
extern unsigned int T5NCounter;
#endif



/*--------------------------------------------------------------------------- */
/*  for single-CPU data consistency (P0699-specific)                          */
/*--------------------------------------------------------------------------- */
#ifdef USE_DATA_CONSISTENCY
extern tPlcMemPtr pI1Buffers[14];
extern tPlcMemPtr pI2Buffers[13];
extern tPlcMemPtr pI3Buffers[12];
extern tPlcMemPtr pI4Buffers[11];
extern tPlcMemPtr pI5Buffers[10];
extern tPlcMemPtr pI6Buffers[ 9];
extern tPlcMemPtr pI7Buffers[ 8];
extern tPlcMemPtr pI8Buffers[ 7];
extern tPlcMemPtr pT1Buffers[ 6];
extern tPlcMemPtr pT2Buffers[ 5];
extern tPlcMemPtr pT3Buffers[ 4];
extern tPlcMemPtr pT4Buffers[ 3];
extern tPlcMemPtr pT5Buffers[ 2];

extern tPlcMemPtr* array_pBuffers[NUM_TASKS];

extern LZSWORD bI1BufferLocks[14];
extern LZSWORD bI2BufferLocks[13];
extern LZSWORD bI3BufferLocks[12];
extern LZSWORD bI4BufferLocks[11];
extern LZSWORD bI5BufferLocks[10];
extern LZSWORD bI6BufferLocks[ 9];
extern LZSWORD bI7BufferLocks[ 8];
extern LZSWORD bI8BufferLocks[ 7];
extern LZSWORD bT1BufferLocks[ 6];
extern LZSWORD bT2BufferLocks[ 5];
extern LZSWORD bT3BufferLocks[ 4];
extern LZSWORD bT4BufferLocks[ 3];
extern LZSWORD bT5BufferLocks[ 2];

extern LZSWORD* array_pBufferLocks[NUM_TASKS];

extern LZSBYTE bLatestConsistent[NUM_TASKS];
extern LZSBYTE bWriteBuffer[NUM_TASKS];
extern LZSBYTE bLockedBuffers[NUM_TASKS][NUM_TASKS];
#endif

#ifdef ENABLE_PERFORMANCE_MONITORING
/*--------------------------------------------------------------------------- */
/*  for performance monitoring (P0699-specific)                               */
/*--------------------------------------------------------------------------- */
/* 4 * 8 sets are for Ix modes = 32 */ /* (init mode is not measured) */
/* 6 * 5 sets are for Tx modes = 30 */ /* (init mode is not measured) */
/* 15 sets are for the tasks   = 15 */
/* -------------------------------- */
/* altogether (sets)             77 */
/* each set (bytes)              24 */
/* size of marker section      1848 */
/* -------------------------------- */
/* plus 8 custom sets            85 */
/* each set (bytes)              24 */
/* size of marker section      2040 */
extern tPerformanceData* pPerformanceDataT0Task;
extern tPerformanceData* pPerformanceDataSYSTask;
extern tPerformanceData* pPerformanceDataT1Task;
extern tPerformanceData* pPerformanceDataT2Task;
extern tPerformanceData* pPerformanceDataT3Task;
extern tPerformanceData* pPerformanceDataT4Task;
extern tPerformanceData* pPerformanceDataT5Task;
extern tPerformanceData* pPerformanceDataI1Task;
extern tPerformanceData* pPerformanceDataI2Task;
extern tPerformanceData* pPerformanceDataI3Task;
extern tPerformanceData* pPerformanceDataI4Task;
extern tPerformanceData* pPerformanceDataI5Task;
extern tPerformanceData* pPerformanceDataI6Task;
extern tPerformanceData* pPerformanceDataI7Task;
extern tPerformanceData* pPerformanceDataI8Task;
extern tPerformanceData* pPerformanceDataCustom1;
extern tPerformanceData* pPerformanceDataCustom2;
extern tPerformanceData* pPerformanceDataCustom3;
extern tPerformanceData* pPerformanceDataCustom4;
extern tPerformanceData* pPerformanceDataCustom5;
extern tPerformanceData* pPerformanceDataCustom6;
extern tPerformanceData* pPerformanceDataCustom7;
extern tPerformanceData* pPerformanceDataCustom8;
#endif


#endif
