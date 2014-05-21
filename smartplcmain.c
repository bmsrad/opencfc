#include "vxWorks.h"
#include "taskLib.h"
#include "logLib.h"
#include "sysLib.h"
#include "rebootLib.h"
#include <semLib.h>
#include <semSmLib.h>
#include <smNameLib.h>
#include <taskLib.h>
#include <taskHookLib.h>
#include <sysLib.h>
#include <smMemLib.h>
#include <smObjLib.h>
#include <time.h>
#include <wdLib.h>

#include "oem/config.h"
#include "oem/odk_prj.h"
#include "smartplc/odk_plc.h"
#include "smartplc/lzs.h"
#include "smartplc/external.h"
#include "smartplc/lzstypes.h"
#include "smartplc/structs.h"
#include "smartplc/lzsdwlws.h"

#include "tskScheduler/userConfig.h"
#include "tskScheduler/tskConfig.h"
#include "tskScheduler/tskDriver.h"
#include "tskScheduler/tskService.h"
#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
#include <excLib.h>
#include <esf.h>
#include "arch/ppc/private/excArchLibP.h"
#endif

#ifdef __cplusplus
   extern "C" {
#endif


#ifdef USE_T0_WATCHDOG
WDOG_ID t0WatchDogId;
#endif

/* CPU load measurement */
void taskSwitchHook(WIND_TCB *pOldTcb, WIND_TCB *pNewTcb);

/* clock synchronization */
#ifdef CLOCK_SYNCHRONIZATION
#ifdef _MASTER_CPU_
int tidTaskClockSync;
void clockSyncTask(void);
#else
void clockSyncIntHandler(int);
struct timespec *pClockSyncTS;
#endif
#endif /* CLOCK_SYNCHRONIZATION */

/* exception handling */
#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
void exception_handler(ESFPPC* pEsf);
void install_exception_handler();
#endif

/* exception handling (ACFAIL and SYSFAIL) */
void exception_IntHandler_acfail(void);
void exception_IntHandler_sysfail(void);
IMPORT UINT32 univBaseAdrs;

/* T0 watchdog */
#ifdef USE_T0_WATCHDOG
void UpdateWatchdog();
void WatchdogHandler();
#endif
SEM_ID SocketCreatOK;/*jyw create socket before restore program*/
SEM_ID taskCyclicSemID_sys;

SEM_ID task1SemID_nor;
SEM_ID task2SemID_nor;
SEM_ID task3SemID_nor;
SEM_ID task4SemID_nor;
SEM_ID task5SemID_nor;
#if 0
SEM_ID int1SemID;
SEM_ID int2SemID;
SEM_ID int3SemID;
SEM_ID int4SemID;
SEM_ID int5SemID;
SEM_ID int6SemID;
SEM_ID int7SemID;
SEM_ID int8SemID;
#endif
SEM_ID task0SemID;

SEM_ID* tcpTxSemID;
unsigned char getCharInfo = 0;
int startplcmain(void)
{
/*****************************************************
*  initalization area
*****************************************************/
	LZSBOOL fWarmStart = LZSFALSE;
	LZSBOOL fColdStart = LZSFALSE;
	tPlcTaskDefTable* pTaskDefTab;
	LZSCHAR* pProjectName = LZSNULL;
	LZSCHAR* pResName = LZSNULL;

	/* initialize runtime system and communication */
    if (LzsEnvInitialize() != kLzsSuccess)
    {
		logMsg("Error initializing SmartPLC!\n",0,0,0,0,0,0);
		return 1;
    }

/*****************************************************
*  task creation area
*****************************************************/
	/*create a semaphore for each SmartPLC task */
	task0SemID = semBCreate (SEM_Q_FIFO, SEM_EMPTY);

	taskCyclicSemID_sys = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

	task1SemID_nor = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	task2SemID_nor = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	task3SemID_nor = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	task4SemID_nor = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	task5SemID_nor = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	SocketCreatOK = semBCreate (SEM_Q_FIFO, SEM_EMPTY);

#if 0
	int1SemID = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	int2SemID = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	int3SemID = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	int4SemID = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	int5SemID = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	int6SemID = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	int7SemID = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
	int8SemID = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
#endif

	if (task0SemID == NULL) logMsg("create task0SemID error!\n", 0, 0, 0, 0, 0, 0);

	if (taskCyclicSemID_sys == NULL) logMsg("create taskCyclicSemID_sys error!\n", 0, 0, 0, 0, 0, 0);

	if (task1SemID_nor == NULL) logMsg("create task1SemID_nor error!\n", 0, 0, 0, 0, 0, 0);
	if (task2SemID_nor == NULL) logMsg("create task2SemID_nor error!\n", 0, 0, 0, 0, 0, 0);
	if (task3SemID_nor == NULL) logMsg("create task3SemID_nor error!\n", 0, 0, 0, 0, 0, 0);
	if (task4SemID_nor == NULL) logMsg("create task4SemID_nor error!\n", 0, 0, 0, 0, 0, 0);
	if (task5SemID_nor == NULL) logMsg("create task5SemID_nor error!\n", 0, 0, 0, 0, 0, 0);
#if 0
	if (int1SemID == NULL) logMsg("create int1SemID error!\n", 0, 0, 0, 0, 0, 0);
	if (int2SemID == NULL) logMsg("create int2SemID error!\n", 0, 0, 0, 0, 0, 0);
	if (int3SemID == NULL) logMsg("create int3SemID error!\n", 0, 0, 0, 0, 0, 0);
	if (int4SemID == NULL) logMsg("create int4SemID error!\n", 0, 0, 0, 0, 0, 0);
	if (int5SemID == NULL) logMsg("create int5SemID error!\n", 0, 0, 0, 0, 0, 0);
	if (int6SemID == NULL) logMsg("create int6SemID error!\n", 0, 0, 0, 0, 0, 0);
	if (int7SemID == NULL) logMsg("create int7SemID error!\n", 0, 0, 0, 0, 0, 0);
	if (int8SemID == NULL) logMsg("create int8SemID error!\n", 0, 0, 0, 0, 0, 0);
#endif

	/* create SmartPLC tasks */
	tidTask0 = taskSpawn ("tTask0", TASK0_PRIO, TASK_FLAGS, STACK_SIZE, (FUNCPTR) task0fun,0,0,0,0,0,0,0,0,0,0);

	tidCyclicTask_sys = taskSpawn("tCyclicTask_sys", CYCLIC_TASK_SYS_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) cyclictask_sys,0,0,0,0,0,0,0,0,0,0);

	tidTask1_nor = taskSpawn ("tTask1_nor", TASK1_NOR_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) task1fun_nor,0,0,0,0,0,0,0,0,0,0);
	tidTask2_nor = taskSpawn ("tTask2_nor", TASK2_NOR_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) task2fun_nor,0,0,0,0,0,0,0,0,0,0);
	tidTask3_nor = taskSpawn ("tTask3_nor", TASK3_NOR_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) task3fun_nor,0,0,0,0,0,0,0,0,0,0);
	tidTask4_nor = taskSpawn ("tTask4_nor", TASK4_NOR_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) task4fun_nor,0,0,0,0,0,0,0,0,0,0);
	tidTask5_nor = taskSpawn ("tTask5_nor", TASK5_NOR_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) task5fun_nor,0,0,0,0,0,0,0,0,0,0);

	/******************* Test task 2011-11-16 ********************/



#if 0
	tidTaskInt1 = taskSpawn ("tTaskInt1", INTERRUPT1_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) taskIntFun_I1,0,0,0,0,0,0,0,0,0,0);
	tidTaskInt2 = taskSpawn ("tTaskInt2", INTERRUPT2_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) taskIntFun_I2,0,0,0,0,0,0,0,0,0,0);
	tidTaskInt3 = taskSpawn ("tTaskInt3", INTERRUPT3_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) taskIntFun_I3,0,0,0,0,0,0,0,0,0,0);
	tidTaskInt4 = taskSpawn ("tTaskInt4", INTERRUPT4_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) taskIntFun_I4,0,0,0,0,0,0,0,0,0,0);
	tidTaskInt5 = taskSpawn ("tTaskInt5", INTERRUPT5_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) taskIntFun_I5,0,0,0,0,0,0,0,0,0,0);
	tidTaskInt6 = taskSpawn ("tTaskInt6", INTERRUPT6_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) taskIntFun_I6,0,0,0,0,0,0,0,0,0,0);
	tidTaskInt7 = taskSpawn ("tTaskInt7", INTERRUPT7_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) taskIntFun_I7,0,0,0,0,0,0,0,0,0,0);
	tidTaskInt8 = taskSpawn ("tTaskInt8", INTERRUPT8_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) taskIntFun_I8,0,0,0,0,0,0,0,0,0,0);
#endif
	taskSpawn("tPlcIdle", 255, TASK_FLAGS, STACK_SIZE, (FUNCPTR) plcIdle,0,0,0,0,0,0,0,0,0,0);
#ifdef USE_T0_WATCHDOG
	if ((t0WatchDogId = wdCreate()) == NULL)
	{
		logMsg("Watchdog create error!\n",0,0,0,0,0,0);
	}
#endif

	tidTaskComm = taskSpawn ("tPlcComm", TASK_COMM_PRIO, TASK_FLAGS, STACK_SIZE,
	        (FUNCPTR) plcComm,0,0,0,0,0,0,0,0,0,0);
	/* clock synchronization */
#ifdef CLOCK_SYNCHRONIZATION
#ifdef _MASTER_CPU_
	tidTaskClockSync = taskSpawn("tClockSync", TASK_CLOCK_SYNC_PRIO, TASK_FLAGS, STACK_SIZE,
			(FUNCPTR) clockSyncTask,0,0,0,0,0,0,0,0,0,0);
#else
	if (ERROR == smNameFind("clock_sync", (void**)&pClockSyncTS,(int*)NULL, WAIT_FOREVER))
	{
		logMsg("timeSync nameFind error: %d\n",errno,0,0,0,0,0);
	}
	else
	{
		logMsg("timeSync name found\n",0,0,0,0,0,0);
	}
	pClockSyncTS = (struct timespec*)smObjGlobalToLocal(pClockSyncTS);

	if (ERROR == sysVmeIntConnect(INUM_TO_IVEC(CLOCK_SYNC_INT_VECTOR), (FUNCPTR)clockSyncIntHandler, 0))
	{
		logMsg("timeSync intConnect failed: %d\n",errno,0,0,0,0,0);
	}
	else
	{
		logMsg("timeSync intConnect OK\n",0,0,0,0,0,0);
	}

	sysIntEnable(CLOCK_SYNC_INT_LEVEL);
#endif
#endif /* CLOCK_SYNCHRONIZATION */

	TicksCounter = 0;

	board_Msg = BOARD_MSG;

/*	tcpTxSemID = semBCreate (SEM_Q_FIFO, SEM_EMPTY);*/

    logMsg("This board is in slot number %d\n",bSlotNumber_g,0,0,0,0,0);

/*****************************************************
*  start SmartPLC
*****************************************************/
    logMsg("SmartPLC start\n",0,0,0,0,0,0);

    /* handle persistency and retain variables */
    #ifndef _LZS_NO_PERSISTENCE_

	#ifdef USE_DATA_CONSISTENCY_SHM
	#ifndef _MASTER_CPU_
	/* SLAVE CPUs: give the master some more time to initialize the shared memory */
	logMsg("Slave waiting period (%u seconds)...\n",SHM_SLAVE_DELAY / 1000,0,0,0,0,0);
	taskDelay(SHM_SLAVE_DELAY);

	#endif
	#endif

	/*LzsRestoreSystem(LzsEnvGetStorageName());*/
#if 1 /*jyw*/
	/* semTake(SocketCreatOK, WAIT_FOREVER); */

	if (getCharInfo == 0) /* from startup safety function */
	{
		if (LzsRestoreSystem(LzsEnvGetStorageName()) == kLzsSuccess)
		{
			/*LZSTRACE0("SmartPLC: restored from persistency file\n");*/
			logMsg("SmartPLC: restored from persistency file\n",0,0,0,0,0,0);

			/* display project and resource name */
			pTaskDefTab = LzsTdtGetAddr();
			if (pTaskDefTab != LZSNULL)
			{
				pProjectName = ((LZSCHAR*)pTaskDefTab) + STRUCT_OFFSET_PRJNAME;
				logMsg("Project: %s\n",pProjectName,0,0,0,0,0);
				pResName = ((LZSCHAR*)pTaskDefTab) + STRUCT_OFFSET_RESNAME;
				logMsg("Resource: %s\n",pResName,0,0,0,0,0);
			}

			#ifdef _LZS_RETAIN_
			if (LzsEnvReadRetain())
			{
				fWarmStart = LZSTRUE;
			}
			else
			#endif
			{
				fColdStart = LZSTRUE;
			}

			#ifdef _LZS_DYNAMIC_RETAIN_
			LzsEnvLoadDynamicRetain();
			#endif
		}
		else
		{
			logMsg("SmartPLC: no application restored from persistency file\n",0,0,0,0,0,0);
			/*LzsErrlogRegisterError(kLzsInitialError, kLzsInitRestoreError, 0, 0, 0);*/ /* commented out because this is normal when there is no peristency data stored => do not register any errors */
		}
	}
    #endif
#endif /*jyw*/
	/*severStart();*/

	#ifdef _MASTER_CPU_
	taskSpawn("tCommHMI",HMI_COMM_PRIO,VX_FP_TASK,STACK_SIZE,(FUNCPTR)severStart,0,0,0,0,0,0,0,0,0,0);
	#endif

	/* enable communication */
	fEnableCommunication = LZSTRUE;

	/* start execution (if restore was successful) */
	if (fColdStart)
	{
		LzsColdStart();
	}
	else if (fWarmStart)
	{
		LzsWarmStart();
	}
	semGive(SocketCreatOK);/*jyw 20140514*/
/*****************************************************
*  end of main
*****************************************************/
	return 0;
}

/*------------------------------*/
/* SmartPLC function prototypes */
/*------------------------------*/
unsigned char LzsIpMainLoop(tTaskControl*);
unsigned char LzsCmdMainLoop(void);

/*********************************************************
* Name: taskScheduleInitInterrupts
* Function:  This function enables all the interrupts for I1 ~ I8
*********************************************************/
#if 0
void taskScheduleInitInterrupts(void)
{
#ifndef _ONE_TASK_ONLY_T1_

/****************************************
* I1 interrupt
****************************************/
#ifdef INT1_ENABLE
	INT_HANDLE_I1(int1SemID);
#endif

/****************************************
* I2 interrupt
****************************************/
#ifdef INT2_ENABLE
	INT_HANDLE_I2(int2SemID);
#endif

/****************************************
* I3 interrupt
****************************************/
#ifdef INT3_ENABLE
	INT_HANDLE_I3(int3SemID);
#endif

/****************************************
* I4 interrupt
****************************************/
#ifdef INT4_ENABLE
	INT_HANDLE_I4(int4SemID);
#endif

/****************************************
* I5 interrupt
****************************************/
#ifdef INT5_ENABLE
	INT_HANDLE_I5(int5SemID);
#endif

/****************************************
* I6 interrupt
****************************************/
#ifdef INT6_ENABLE
	INT_HANDLE_I6(int6SemID);
#endif

/****************************************
* I7 interrupt
****************************************/
#ifdef INT7_ENABLE
	INT_HANDLE_I7(int7SemID);
#endif

/***************************************
* I8 interrupt
****************************************/
#ifdef INT8_ENABLE
	INT_HANDLE_I8(int8SemID);
#endif

#endif
}
#endif
/*********************************************************
* Name: taskScheduleInitTimer
* Function:  This function configures the T0 interrupt
*********************************************************/
void taskScheduleInitTimer(float interval)
{
/****************************************
* T0 interrupt
****************************************/
	if(board_Msg == MASTER_BOARD)
	{
/*==================================
 *  20100121 SKK MODIFY  -- START
 * ================================*/
		/*setClockRate(AUXCLOCK, 0.0001);*/
/*==================================
 *  20100121 SKK MODIFY  -- END
 * ================================*/

		/*auxclockInterrupt(task0SemID,interval);*/
	}

	if(board_Msg == SLAVE_BOARD)
	{
		/*mailboxInterrupt(task0SemID);*/
	}
}

/*********************************************************
*Name: task0fun
*Function:  This function schedule the cyclic tasks.
*					 from T1 to T5.
*********************************************************/
void task0fun(void)
{
	unsigned int task_Status_sys_T0 = 0;

	/* skip the first three timer interrupts after startup, until the frequency becomes more stable */
	/*semTake(task0SemID,WAIT_FOREVER);
	semTake(task0SemID,WAIT_FOREVER);
	semTake(task0SemID,WAIT_FOREVER);*/

	/*FOREVER*/
    if(dwtask0start ==1)
	{
	    /*logMsg("task0fun start\n",0,0,0,0,0,0);*/
		/*semTake(task0SemID,WAIT_FOREVER);*/

		LOCK_TASK_SWITCH(); /* task switch disable */

		#ifdef USE_T0_WATCHDOG
		/* cancel watchdog */
		if (wdCancel(t0WatchDogId) == ERROR)
		{
			logMsg("Error stopping T0 watchdog!\n",0,0,0,0,0,0);
		}
		#endif

		/* if not running, do not schedule any tasks */
		if (!(wLzsSysFlags_l & LZSSTAT_RUNNING))
		{
			UNLOCK_TASK_SWITCH(); /* task switch enable */
			return;
		}

		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStartPerformanceMeasurement(pPerformanceDataT0Task);
		#endif

		/* wait for all tasks ready */
		if (task_Ready != ALLTASKS_MASK)
		{
			UNLOCK_TASK_SWITCH(); /* task switch enable */
			return;
		}

		/* check shared memory configuration */
		#ifdef USE_SHARED_MEMORY
		if (!CheckSHMConfigValid())
		{
			/* in this case, do not continue scheduling */
			UNLOCK_TASK_SWITCH(); /* task switch enable */
			return;
		}
		#endif

		/* check shared memory configuration */
		#ifdef USE_STATION_HWCONFIG_CRC_CHECK
		if (!CheckHwConfigValid())
		{
			/* in this case, do not continue scheduling */
			UNLOCK_TASK_SWITCH(); /* task switch enable */
			continue;
		}
		#endif

		/* check for errors */
		if (globalError)
		{
			/* in this case, do not continue scheduling */
			UNLOCK_TASK_SWITCH(); /* task switch enable */
			return;
		}

		/* check if T0 is disabled (either from configuration or during online edit) */
		#ifndef _LZS_DWLWITHOUTSTOP_
		if (pTaskConfig_g == LZSNULL || pTaskConfig_g->dwT0Interval == 0)
		#else
		if (pTaskConfig_g == LZSNULL || pTaskConfig_g->dwT0Interval == 0 || fLockReplaceResource_l)
		#endif
		{
			/* in this case, do not continue scheduling */
			UNLOCK_TASK_SWITCH(); /* task switch enable */
			return;
		}

		#ifdef USE_T0_WATCHDOG
		/* restart watchdog (done here because it must not be started if T0 is disabled!) */
		if (wdStart(t0WatchDogId, LzsEnvGetWatchdogTimeout(), WatchdogHandler, NULL) == ERROR)
		{
			logMsg("Error starting T0 watchdog!\n",0,0,0,0,0,0);
		}
		#endif

		/* state of the system mode task at the beginning of T0 is used for cycle error checking (because the original task_Status_sys will be modified here!) */
		/* only flags for T-tasks are checked here */
		task_Status_sys_T0 = task_Status_sys & TTASKS_MASK;

 /*******************************************************
 * if run at master, the master should sent t0 clock to VME bus
 *******************************************************/
#ifdef MULTI_CPU_SYN
 		if(board_Msg == MASTER_BOARD)
		{
			/*SEND_T0_SIGNAL(0x55aa55aa55);*/
		}
#endif
 /*******************************************************/

		TicksCounter++;
		TicksCounter = TicksCounter % Task5Para;

#ifndef _ONE_TASK_ONLY_T1_

		/* check if T1 is enabled */
		if (pTaskConfig_g->dwT1Factor != 0 && !globalError)
		{
			if ((TicksCounter + Task1Para / 2) % Task1Para == 0) /* T1 should be scheduled */
			{
				if (task_Status_sys_T0 == 0 && (task_Status_nor & T1_ACTIVE) == 0) /* all tasks' system mode and the last T1 have finished */
				{
					/* cycle error handling */
					if (T1CycleErrorCount > 0)
					{
						T1CycleErrorCount--;
					}

					task_Status_sys |= T1_ACTIVE;
					task_Status_nor |= T1_ACTIVE;

					#ifdef SCHEDULER_DEBUG
					T1SCounterStart++;
					T1NCounterStart++;
					#endif
			    }
			    else /* the last T1 has NOT finished */
			    {
			    	T1CycleErrorCount += 2;

			    	if (T1CycleErrorCount > MAX_CYCLE_ERROR)
			    	{
			    		/* too many cycle errors for this task: register fatal cycle error (this will stop the system) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsFatalCycleError, kT1Task, task_Status_sys_T0, task_Status_nor);
						logMsg("T1 fatal cycle error (task_Status_sys_T0=0x%x, task_Status_sys=0x%x, task_Status_nor=0x%x, mode flags=%d)\n",task_Status_sys_T0,task_Status_sys,task_Status_nor,arrayModeFlags[kT1Task],0,0);
			    	}
			    	else
			    	{
			    		/* skip the cycle for this task and only register single cycle error (system will keep running) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsSingleCycleError, kT1Task, task_Status_sys_T0, task_Status_nor);
					}
			    }
			}
		}

		/* check if T2 is enabled */
		if (pTaskConfig_g->dwT2Factor != 0 && !globalError)
		{
			if ((TicksCounter + Task2Para / 2) % Task2Para == 0) /* T2 should be scheduled */
			{
				if (task_Status_sys_T0 == 0 && (task_Status_nor & T2_ACTIVE) == 0) /* all tasks' system mode and the last T2 have finished */
			    {
					/* cycle error handling */
					if (T2CycleErrorCount > 0)
					{
						T2CycleErrorCount--;
					}

					task_Status_sys |= T2_ACTIVE;
					task_Status_nor |= T2_ACTIVE;

					#ifdef SCHEDULER_DEBUG
					T2SCounterStart++;
					T2NCounterStart++;
					#endif
			    }
			    else /* the last T2 has NOT finished */
			    {
			    	T2CycleErrorCount += 2;

			    	if (T2CycleErrorCount > MAX_CYCLE_ERROR)
			    	{
			    		/* too many cycle errors for this task: register fatal cycle error (this will stop the system) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsFatalCycleError, kT2Task, task_Status_sys_T0, task_Status_nor);
						logMsg("T2 fatal cycle error (task_Status_sys_T0=0x%x, task_Status_sys=0x%x, task_Status_nor=0x%x, mode flags=%d)\n",task_Status_sys_T0,task_Status_sys,task_Status_nor,arrayModeFlags[kT2Task],0,0);
			    	}
			    	else
			    	{
			    		/* skip the cycle for this task and only register single cycle error (system will keep running) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsSingleCycleError, kT2Task, task_Status_sys_T0, task_Status_nor);
					}
			    }
			}
		}

		/* check if T3 is enabled */
		if (pTaskConfig_g->dwT3Factor != 0 && !globalError)
		{
			if ((TicksCounter + Task3Para / 2) % Task3Para == 0) /* T3 should be scheduled */
			{
				if (task_Status_sys_T0 == 0 && (task_Status_nor & T3_ACTIVE) == 0) /* all tasks' system mode and the last T3 have finished */
				{
					/* cycle error handling */
					if (T3CycleErrorCount > 0)
					{
						T3CycleErrorCount--;
					}

					task_Status_sys |= T3_ACTIVE;
					task_Status_nor |= T3_ACTIVE;

					#ifdef SCHEDULER_DEBUG
					T3SCounterStart++;
					T3NCounterStart++;
					#endif
			    }
			    else /* the last T3 has NOT finished */
			    {
			    	T3CycleErrorCount += 2;

			    	if (T3CycleErrorCount > MAX_CYCLE_ERROR)
			    	{
			    		/* too many cycle errors for this task: register fatal cycle error (this will stop the system) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsFatalCycleError, kT3Task, task_Status_sys_T0, task_Status_nor);
						logMsg("T3 fatal cycle error (task_Status_sys_T0=0x%x, task_Status_sys=0x%x, task_Status_nor=0x%x, mode flags=%d)\n",task_Status_sys_T0,task_Status_sys,task_Status_nor,arrayModeFlags[kT3Task],0,0);
			    	}
			    	else
			    	{
			    		/* skip the cycle for this task and only register single cycle error (system will keep running) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsSingleCycleError, kT3Task, task_Status_sys_T0, task_Status_nor);
					}
			    }
			}
		}

		/* check if T4 is enabled */
		if (pTaskConfig_g->dwT4Factor != 0 && !globalError)
		{
			if ((TicksCounter + Task4Para / 2) % Task4Para == 0) /* T4 should be scheduled */
			{
				if (task_Status_sys_T0 == 0 && (task_Status_nor & T4_ACTIVE) == 0) /* all tasks' system mode and the last T4 have finished */
				{
					/* cycle error handling */
					if (T4CycleErrorCount > 0)
					{
						T4CycleErrorCount--;
					}

					task_Status_sys |= T4_ACTIVE;
					task_Status_nor |= T4_ACTIVE;

					#ifdef SCHEDULER_DEBUG
					T4SCounterStart++;
					T4NCounterStart++;
					#endif
				}
				else /* the last T4 has NOT finished */
				{
			    	T4CycleErrorCount += 2;

			    	if (T4CycleErrorCount > MAX_CYCLE_ERROR)
			    	{
			    		/* too many cycle errors for this task: register fatal cycle error (this will stop the system) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsFatalCycleError, kT4Task, task_Status_sys_T0, task_Status_nor);
						logMsg("T4 fatal cycle error (task_Status_sys_T0=0x%x, task_Status_sys=0x%x, task_Status_nor=0x%x, mode flags=%d)\n",task_Status_sys_T0,task_Status_sys,task_Status_nor,arrayModeFlags[kT4Task],0,0);
			    	}
			    	else
			    	{
			    		/* skip the cycle for this task and only register single cycle error (system will keep running) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsSingleCycleError, kT4Task, task_Status_sys_T0, task_Status_nor);
					}
				}
			}
		}

		/* check if T5 is enabled */
		if (pTaskConfig_g->dwT5Factor != 0 && !globalError)
		{
			if ((TicksCounter + Task5Para / 2) % Task5Para == 0) /* T5 should be scheduled */
			{
				if (task_Status_sys_T0 == 0 && (task_Status_nor & T5_ACTIVE) == 0) /* all tasks' system mode and the last T5 have finished */
				{
					/* cycle error handling */
					if (T5CycleErrorCount > 0)
					{
						T5CycleErrorCount--;
					}

					task_Status_sys |= T5_ACTIVE;
					task_Status_nor |= T5_ACTIVE;

					#ifdef SCHEDULER_DEBUG
					T5SCounterStart++;
					T5NCounterStart++;
					#endif
			    }
			    else /* the last T5 has NOT finished */
			    {
			    	T5CycleErrorCount += 2;

			    	if (T5CycleErrorCount > MAX_CYCLE_ERROR)
			    	{
			    		/* too many cycle errors for this task: register fatal cycle error (this will stop the system) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsFatalCycleError, kT5Task, task_Status_sys_T0, task_Status_nor);
						logMsg("T5 fatal cycle error (task_Status_sys_T0=0x%x, task_Status_sys=0x%x, task_Status_nor=0x%x, mode flags=%d)\n",task_Status_sys_T0,task_Status_sys,task_Status_nor,arrayModeFlags[kT5Task],0,0);
			    	}
			    	else
			    	{
			    		/* skip the cycle for this task and only register single cycle error (system will keep running) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsSingleCycleError, kT5Task, task_Status_sys_T0, task_Status_nor);
					}
			    }
			}
		}

#else /* _ONE_TASK_ONLY_T1_ */

		/* check if T1 is enabled */
		if (pTaskConfig_g->dwT1Factor != 0)
		{
			if ((TicksCounter + Task1Para / 2) % Task1Para == 0) /* T1 should be scheduled */
			{
				if ((task_Status_sys & T1_ACTIVE) == 0 && (task_Status_nor & T1_ACTIVE) == 0) /* the last T1 has finished */
				{
					/* cycle error handling */
					if (T1CycleErrorCount > 0)
					{
						T1CycleErrorCount--;
					}

					task_Status_sys |= T1_ACTIVE;
					task_Status_nor |= T1_ACTIVE;

					semGive(task1SemID_nor); /* starts system AND normal mode! */
			    }
			    else /* the last T1 has NOT finished */
			    {
			    	T1CycleErrorCount += 2;

			    	if (T1CycleErrorCount > MAX_CYCLE_ERROR)
			    	{
			    		/* too many cycle errors for this task: register fatal cycle error (this will stop the system) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsFatalCycleError, kT1Task, task_Status_sys_T0, task_Status_nor);
			    	}
			    	else
			    	{
			    		/* skip the cycle for this task and only register single cycle error (system will keep running) */
						LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsSingleCycleError, kT1Task, task_Status_sys_T0, task_Status_nor);
					}
			    }
			}
		}

#endif /* _ONE_TASK_ONLY_T1_ */

		/* start system mode task */
		if (task_Status_sys != 0)
		{
			semGive(taskCyclicSemID_sys);
		}

		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStopPerformanceMeasurement(pPerformanceDataT0Task);
		#endif

		UNLOCK_TASK_SWITCH(); /* task switch enable */
	}
}

/*********************************************************
*Name : cyclictask_sys(void)
*Function: This routine use to implement the
*
*********************************************************/

#ifndef _ONE_TASK_ONLY_T1_

void cyclictask_sys(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	unsigned int task_Status_nor_SYS = 0;

	task_Ready |= SYS_ACTIVE;

	FOREVER
	{
		semTake(taskCyclicSemID_sys, WAIT_FOREVER);

		LOCK_TASK_SWITCH(); /* task switch disable */

		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStartPerformanceMeasurement(pPerformanceDataSYSTask);
		#endif

		#ifdef SCHEDULER_DEBUG
		SYSCounterStart++;
		#endif

		/* after system mode, start the same set of tasks in normal mode */
		task_Status_nor_SYS = task_Status_sys;

		SYS_ENTRY();

		if (task_Status_sys & T1_ACTIVE) /* T1 system mode must be executed */
		{
			/* preprocessing */
			#ifdef USE_DATA_CONSISTENCY_SHM
			PublishSHMDCWriteBuffer(kT1Task); /* release write buffer (from previous cylce) */
			#endif

			#ifdef USE_DATA_CONSISTENCY
			SetDCBuffers(kT1Task);
			#endif

			T1_TA_GET();
			UNLOCK_TASK_SWITCH();

			/* execute IEC 61131 application */
			LzsIpMainLoop(pControlSetT1S);

			LOCK_TASK_SWITCH();
			task_Status_sys &= ~T1_ACTIVE;

			#ifdef SCHEDULER_DEBUG
			T1SCounterEnd++;
			#endif
		}

		if (task_Status_sys & T2_ACTIVE) /* T2 system mode must be executed */
		{
			/* preprocessing */
			#ifdef USE_DATA_CONSISTENCY_SHM
			PublishSHMDCWriteBuffer(kT2Task); /* release write buffer (from previous cylce) */
			#endif

			#ifdef USE_DATA_CONSISTENCY
			SetDCBuffers(kT2Task);
			#endif

			T2_TA_GET();
			UNLOCK_TASK_SWITCH();

			/* execute IEC 61131 application */
			LzsIpMainLoop(pControlSetT2S);

			LOCK_TASK_SWITCH();
			task_Status_sys &= ~T2_ACTIVE;

			#ifdef SCHEDULER_DEBUG
			T2SCounterEnd++;
			#endif
		}

		if (task_Status_sys & T3_ACTIVE) /* T3 system mode must be executed */
		{
			/* preprocessing */
			#ifdef USE_DATA_CONSISTENCY_SHM
			PublishSHMDCWriteBuffer(kT3Task); /* release write buffer (from previous cylce) */
			#endif

			#ifdef USE_DATA_CONSISTENCY
			SetDCBuffers(kT3Task);
			#endif

			T3_TA_GET();
			UNLOCK_TASK_SWITCH();

			/* execute IEC 61131 application */
			LzsIpMainLoop(pControlSetT3S);

			LOCK_TASK_SWITCH();
			task_Status_sys &= ~T3_ACTIVE;

			#ifdef SCHEDULER_DEBUG
			T3SCounterEnd++;
			#endif
		}

		if (task_Status_sys & T4_ACTIVE) /* T4 system mode must be executed */
		{
			/* preprocessing */
			#ifdef USE_DATA_CONSISTENCY_SHM
			PublishSHMDCWriteBuffer(kT4Task); /* release write buffer (from previous cylce) */
			#endif

			#ifdef USE_DATA_CONSISTENCY
			SetDCBuffers(kT4Task);
			#endif

			T4_TA_GET();
			UNLOCK_TASK_SWITCH();

			/* execute IEC 61131 application */
			LzsIpMainLoop(pControlSetT4S);

			LOCK_TASK_SWITCH();
			task_Status_sys &= ~T4_ACTIVE;

			#ifdef SCHEDULER_DEBUG
			T4SCounterEnd++;
			#endif
		}

		if (task_Status_sys & T5_ACTIVE) /* T5 system mode must be executed */
		{
			/* preprocessing */
			#ifdef USE_DATA_CONSISTENCY_SHM
			PublishSHMDCWriteBuffer(kT5Task); /* release write buffer (from previous cylce) */
			#endif

			#ifdef USE_DATA_CONSISTENCY
			SetDCBuffers(kT5Task);
			#endif

			T5_TA_GET();
			UNLOCK_TASK_SWITCH();

			/* execute IEC 61131 application */
			LzsIpMainLoop(pControlSetT5S);

			LOCK_TASK_SWITCH();
			task_Status_sys &= ~T5_ACTIVE;

			#ifdef SCHEDULER_DEBUG
			T5SCounterEnd++;
			#endif
		}

  	  	SYS_EXIT();

		/* start scheduled normal mode tasks */
		if (!globalError)
		{
			if (task_Status_nor_SYS & T1_ACTIVE)
			{
				task_Status_nor_SYS &= ~T1_ACTIVE;
				semGive(task1SemID_nor);
			}
			if (task_Status_nor_SYS & T2_ACTIVE)
			{
				task_Status_nor_SYS &= ~T2_ACTIVE;
				semGive(task2SemID_nor);
			}
			if (task_Status_nor_SYS & T3_ACTIVE)
			{
				task_Status_nor_SYS &= ~T3_ACTIVE;
				semGive(task3SemID_nor);
			}
			if (task_Status_nor_SYS & T4_ACTIVE)
			{
				task_Status_nor_SYS &= ~T4_ACTIVE;
				semGive(task4SemID_nor);
			}
			if (task_Status_nor_SYS & T5_ACTIVE)
			{
				task_Status_nor_SYS &= ~T5_ACTIVE;
				semGive(task5SemID_nor);
			}
		}

		#ifdef SCHEDULER_DEBUG
		SYSCounterEnd++;
		#endif

		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStopPerformanceMeasurement(pPerformanceDataSYSTask);
		#endif

		UNLOCK_TASK_SWITCH();
	}
}

/*********************************************************
*Name: task?fun_???
*Function:  This area is the entity of the cyclic tasks.
*					 from T1 to T5.
*********************************************************/

/*************************************************
*   T1
*************************************************/
void task1fun_nor(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= T1_ACTIVE;

	FOREVER
	{
		semTake(task1SemID_nor, WAIT_FOREVER);

		/* preprocessing */
		LOCK_TASK_SWITCH();
		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStartPerformanceMeasurement(pPerformanceDataT1Task);
		#endif

		T1_ENTRY();
		UNLOCK_TASK_SWITCH();

		#ifdef USE_SHARED_MEMORY
		#ifdef USE_DATA_CONSISTENCY_SHM
		SetSHMDCWriteBuffer(kT1Task); /* selection of write buffer */
		#endif

		LzsIpMainLoop(pControlSetT1FI); /* fast import */

		#ifdef USE_DATA_CONSISTENCY_SHM
		LOCK_TASK_SWITCH();
		SetSHMDCReadBuffers(kT1Task); /* selection of read buffers */
		UNLOCK_TASK_SWITCH();

		LzsIpMainLoop(pControlSetT1CI); /* consistent import */

		LOCK_TASK_SWITCH();
		UnlockSHMDCReadBuffers(kT1Task); /* release read buffers */
		UNLOCK_TASK_SWITCH();
		#endif
		#endif

		/* execute IEC 61131 application */
		LzsIpMainLoop(pControlSetT1N);

		#ifdef USE_SHARED_MEMORY
		#ifdef USE_DATA_CONSISTENCY_SHM
		LzsIpMainLoop(pControlSetT1CE); /* consistent export */
		#endif
		LzsIpMainLoop(pControlSetT1FE); /* fast export */
		#endif

		/* postprocessing */
		LOCK_TASK_SWITCH();
		#ifdef USE_DATA_CONSISTENCY
		UnlockDCBuffers(kT1Task);
		#endif

		T1_EXIT();
		task_Status_nor &= ~T1_ACTIVE;

		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStopPerformanceMeasurement(pPerformanceDataT1Task);
		#endif

		#ifdef SCHEDULER_DEBUG
		T1NCounterEnd++;
		#endif
		UNLOCK_TASK_SWITCH();
	}
}

/*************************************************
*   T2
*************************************************/
void task2fun_nor(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= T2_ACTIVE;

	FOREVER
	{
		semTake(task2SemID_nor, WAIT_FOREVER);

		/* preprocessing */
		LOCK_TASK_SWITCH();
		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStartPerformanceMeasurement(pPerformanceDataT2Task);
		#endif

		T2_ENTRY();
		UNLOCK_TASK_SWITCH();

		#ifdef USE_SHARED_MEMORY
		#ifdef USE_DATA_CONSISTENCY_SHM
		SetSHMDCWriteBuffer(kT2Task); /* selection of write buffer */
		#endif

		LzsIpMainLoop(pControlSetT2FI); /* fast import */

		#ifdef USE_DATA_CONSISTENCY_SHM
		LOCK_TASK_SWITCH();
		SetSHMDCReadBuffers(kT2Task); /* selection of read buffers */
		UNLOCK_TASK_SWITCH();

		LzsIpMainLoop(pControlSetT2CI); /* consistent import */

		LOCK_TASK_SWITCH();
		UnlockSHMDCReadBuffers(kT2Task); /* release read buffers */
		UNLOCK_TASK_SWITCH();
		#endif
		#endif

		/* execute IEC 61131 application */
		LzsIpMainLoop(pControlSetT2N);

		#ifdef USE_SHARED_MEMORY
		#ifdef USE_DATA_CONSISTENCY_SHM
		LzsIpMainLoop(pControlSetT2CE); /* consistent export */
		#endif
		LzsIpMainLoop(pControlSetT2FE); /* fast export */
		#endif

		/* postprocessing */
		LOCK_TASK_SWITCH();
		#ifdef USE_DATA_CONSISTENCY
		UnlockDCBuffers(kT2Task);
		#endif

		T2_EXIT();
		task_Status_nor &= ~T2_ACTIVE;

		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStopPerformanceMeasurement(pPerformanceDataT2Task);
		#endif

		#ifdef SCHEDULER_DEBUG
		T2NCounterEnd++;
		#endif
		UNLOCK_TASK_SWITCH();
	}
}

/*************************************************
*   T3
*************************************************/
void task3fun_nor(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= T3_ACTIVE;

	FOREVER
	{
		semTake(task3SemID_nor, WAIT_FOREVER);

		/* preprocessing */
		LOCK_TASK_SWITCH();
		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStartPerformanceMeasurement(pPerformanceDataT3Task);
		#endif

		T3_ENTRY();
		UNLOCK_TASK_SWITCH();

		#ifdef USE_SHARED_MEMORY
		#ifdef USE_DATA_CONSISTENCY_SHM
		SetSHMDCWriteBuffer(kT3Task); /* selection of write buffer */
		#endif

		LzsIpMainLoop(pControlSetT3FI); /* fast import */

		#ifdef USE_DATA_CONSISTENCY_SHM
		LOCK_TASK_SWITCH();
		SetSHMDCReadBuffers(kT3Task); /* selection of read buffers */
		UNLOCK_TASK_SWITCH();

		LzsIpMainLoop(pControlSetT3CI); /* consistent import */

		LOCK_TASK_SWITCH();
		UnlockSHMDCReadBuffers(kT3Task); /* release read buffers */
		UNLOCK_TASK_SWITCH();
		#endif
		#endif

		/* execute IEC 61131 application */
		LzsIpMainLoop(pControlSetT3N);

		#ifdef USE_SHARED_MEMORY
		#ifdef USE_DATA_CONSISTENCY_SHM
		LzsIpMainLoop(pControlSetT3CE); /* consistent export */
		#endif
		LzsIpMainLoop(pControlSetT3FE); /* fast export */
		#endif

		/* postprocessing */
		LOCK_TASK_SWITCH();
		#ifdef USE_DATA_CONSISTENCY
		UnlockDCBuffers(kT3Task);
		#endif

		T3_EXIT();
		task_Status_nor &= ~T3_ACTIVE;

		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStopPerformanceMeasurement(pPerformanceDataT3Task);
		#endif

		#ifdef SCHEDULER_DEBUG
		T3NCounterEnd++;
		#endif
		UNLOCK_TASK_SWITCH();
	}
}

/*************************************************
*   T4
*************************************************/
void task4fun_nor(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= T4_ACTIVE;

	FOREVER
	{
		semTake(task4SemID_nor, WAIT_FOREVER);

		/* preprocessing */
		LOCK_TASK_SWITCH();
		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStartPerformanceMeasurement(pPerformanceDataT4Task);
		#endif

		T4_ENTRY();
		UNLOCK_TASK_SWITCH();

		#ifdef USE_SHARED_MEMORY
		#ifdef USE_DATA_CONSISTENCY_SHM
		SetSHMDCWriteBuffer(kT4Task); /* selection of write buffer */
		#endif

		LzsIpMainLoop(pControlSetT4FI); /* fast import */

		#ifdef USE_DATA_CONSISTENCY_SHM
		LOCK_TASK_SWITCH();
		SetSHMDCReadBuffers(kT4Task); /* selection of read buffers */
		UNLOCK_TASK_SWITCH();

		LzsIpMainLoop(pControlSetT4CI); /* consistent import */

		LOCK_TASK_SWITCH();
		UnlockSHMDCReadBuffers(kT4Task); /* release read buffers */
		UNLOCK_TASK_SWITCH();
		#endif
		#endif

		/* execute IEC 61131 application */
		LzsIpMainLoop(pControlSetT4N);

		#ifdef USE_SHARED_MEMORY
		#ifdef USE_DATA_CONSISTENCY_SHM
		LzsIpMainLoop(pControlSetT4CE); /* consistent export */
		#endif
		LzsIpMainLoop(pControlSetT4FE); /* fast export */
		#endif

		/* postprocessing */
		LOCK_TASK_SWITCH();
		#ifdef USE_DATA_CONSISTENCY
		UnlockDCBuffers(kT4Task);
		#endif

		T4_EXIT();
		task_Status_nor &= ~T4_ACTIVE;

		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStopPerformanceMeasurement(pPerformanceDataT4Task);
		#endif

		#ifdef SCHEDULER_DEBUG
		T4NCounterEnd++;
		#endif
		UNLOCK_TASK_SWITCH();
	}
}

/*************************************************
*   T5
*************************************************/
void task5fun_nor(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= T5_ACTIVE;

	FOREVER
	{
		semTake(task5SemID_nor, WAIT_FOREVER);

		/* preprocessing */
		LOCK_TASK_SWITCH();
		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStartPerformanceMeasurement(pPerformanceDataT5Task);
		#endif

		T5_ENTRY();
		UNLOCK_TASK_SWITCH();

		#ifdef USE_SHARED_MEMORY
		#ifdef USE_DATA_CONSISTENCY_SHM
		SetSHMDCWriteBuffer(kT5Task); /* selection of write buffer */
		#endif

		LzsIpMainLoop(pControlSetT5FI); /* fast import */

		#ifdef USE_DATA_CONSISTENCY_SHM
		LOCK_TASK_SWITCH();
		SetSHMDCReadBuffers(kT5Task); /* selection of read buffers */
		UNLOCK_TASK_SWITCH();

		LzsIpMainLoop(pControlSetT5CI); /* consistent import */

		LOCK_TASK_SWITCH();
		UnlockSHMDCReadBuffers(kT5Task); /* release read buffers */
		UNLOCK_TASK_SWITCH();
		#endif
		#endif

		/* execute IEC 61131 application */
		LzsIpMainLoop(pControlSetT5N);

		#ifdef USE_SHARED_MEMORY
		#ifdef USE_DATA_CONSISTENCY_SHM
		LzsIpMainLoop(pControlSetT5CE); /* consistent export */
		#endif
		LzsIpMainLoop(pControlSetT5FE); /* fast export */
		#endif

		/* postprocessing */
		LOCK_TASK_SWITCH();
		#ifdef USE_DATA_CONSISTENCY
		UnlockDCBuffers(kT5Task);
		#endif

		T5_EXIT();
		task_Status_nor &= ~T5_ACTIVE;

		#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
		LzsEnvStopPerformanceMeasurement(pPerformanceDataT5Task);
		#endif

		#ifdef SCHEDULER_DEBUG
		T5NCounterEnd++;
		#endif
		UNLOCK_TASK_SWITCH();
	}
}


#if 0
/*********************************************************
*Name: taskIntFun_I?
*Function:  This area is the entity of the interrupt tasks.
*					 from I1 to I8.
*********************************************************/

/*************************************************
*   I1
*************************************************/
void taskIntFun_I1(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= I1_ACTIVE;

	FOREVER
	{
		semTake(int1SemID, WAIT_FOREVER);

		/* check for running/stop mode and online edit */
		#ifndef _LZS_DWLWITHOUTSTOP_
		if (wLzsSysFlags_l & LZSSTAT_RUNNING)
		#else
		if ((wLzsSysFlags_l & LZSSTAT_RUNNING) && !fLockReplaceResource_l)
		#endif
		{
			/* check if enabled */
			if (pTaskConfig_g != LZSNULL && pTaskConfig_g->bI1Source != 0)
			{
				/* preprocessing */
				LOCK_TASK_SWITCH();
				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStartPerformanceMeasurement(pPerformanceDataI1Task);
				#endif

				task_Status_sys |= I1_ACTIVE;
				task_Status_nor |= I1_ACTIVE;

				I1_ENTRY();

				#ifdef USE_DATA_CONSISTENCY
				SetDCBuffers(kI1Task);
				#endif

				SET_SYS_MODE();

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI1S);

				SET_NOR_MODE();
				UNLOCK_TASK_SWITCH();

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI1FI); /* fast import */
				#endif

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI1N);

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI1FE); /* fast export */
				#endif

				/* postprocessing */
				LOCK_TASK_SWITCH();
				#ifdef USE_DATA_CONSISTENCY
				UnlockDCBuffers(kI1Task);
				#endif

				I1_EXIT();
				task_Status_sys &= ~I1_ACTIVE;
				task_Status_nor &= ~I1_ACTIVE;

				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStopPerformanceMeasurement(pPerformanceDataI1Task);
				#endif
				UNLOCK_TASK_SWITCH();
			}
		}
	}
}

/*************************************************
*   I2
************************************************/
void taskIntFun_I2(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= I2_ACTIVE;

	FOREVER
	{
		semTake(int2SemID, WAIT_FOREVER);

		/* check for running/stop mode and online edit */
		#ifndef _LZS_DWLWITHOUTSTOP_
		if (wLzsSysFlags_l & LZSSTAT_RUNNING)
		#else
		if ((wLzsSysFlags_l & LZSSTAT_RUNNING) && !fLockReplaceResource_l)
		#endif
		{
			/* check if enabled */
			if (pTaskConfig_g != LZSNULL && pTaskConfig_g->bI2Source != 0)
			{
				/* preprocessing */
				LOCK_TASK_SWITCH();
				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStartPerformanceMeasurement(pPerformanceDataI2Task);
				#endif

				task_Status_sys |= I2_ACTIVE;
				task_Status_nor |= I2_ACTIVE;

				I2_ENTRY();

				#ifdef USE_DATA_CONSISTENCY
				SetDCBuffers(kI2Task);
				#endif

				SET_SYS_MODE();

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI2S);

				SET_NOR_MODE();
				UNLOCK_TASK_SWITCH();

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI2FI); /* fast import */
				#endif

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI2N);

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI2FE); /* fast export */
				#endif

				/* postprocessing */
				LOCK_TASK_SWITCH();
				#ifdef USE_DATA_CONSISTENCY
				UnlockDCBuffers(kI2Task);
				#endif

				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStopPerformanceMeasurement(pPerformanceDataI2Task);
				#endif

				I2_EXIT();
				task_Status_sys &= ~I2_ACTIVE;
				task_Status_nor &= ~I2_ACTIVE;
				UNLOCK_TASK_SWITCH();
			}
		}
	}
}

/*************************************************
*   I3
*************************************************/
void taskIntFun_I3(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= I3_ACTIVE;

	FOREVER
	{
		semTake(int3SemID, WAIT_FOREVER);

		/* check for running/stop mode and online edit */
		#ifndef _LZS_DWLWITHOUTSTOP_
		if (wLzsSysFlags_l & LZSSTAT_RUNNING)
		#else
		if ((wLzsSysFlags_l & LZSSTAT_RUNNING) && !fLockReplaceResource_l)
		#endif
		{
			/* check if enabled */
			if (pTaskConfig_g != LZSNULL && pTaskConfig_g->bI3Source != 0)
			{
				/* preprocessing */
				LOCK_TASK_SWITCH();
				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStartPerformanceMeasurement(pPerformanceDataI3Task);
				#endif

				task_Status_sys |= I3_ACTIVE;
				task_Status_nor |= I3_ACTIVE;

				I3_ENTRY();

				#ifdef USE_DATA_CONSISTENCY
				SetDCBuffers(kI3Task);
				#endif

				SET_SYS_MODE();

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI3S);

				SET_NOR_MODE();
				UNLOCK_TASK_SWITCH();

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI3FI); /* fast import */
				#endif

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI3N);

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI3FE); /* fast export */
				#endif

				/* postprocessing */
				LOCK_TASK_SWITCH();
				#ifdef USE_DATA_CONSISTENCY
				UnlockDCBuffers(kI3Task);
				#endif

				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStopPerformanceMeasurement(pPerformanceDataI3Task);
				#endif

				I3_EXIT();
				task_Status_sys &= ~I3_ACTIVE;
				task_Status_nor &= ~I3_ACTIVE;
				UNLOCK_TASK_SWITCH();
			}
		}
	}
}

/*************************************************
*   I4
*************************************************/
void taskIntFun_I4(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= I4_ACTIVE;

	FOREVER
	{
		semTake(int4SemID, WAIT_FOREVER);

		/* check for running/stop mode and online edit */
		#ifndef _LZS_DWLWITHOUTSTOP_
		if (wLzsSysFlags_l & LZSSTAT_RUNNING)
		#else
		if ((wLzsSysFlags_l & LZSSTAT_RUNNING) && !fLockReplaceResource_l)
		#endif
		{
			/* check if enabled */
			if (pTaskConfig_g != LZSNULL && pTaskConfig_g->bI4Source != 0)
			{
				/* preprocessing */
				LOCK_TASK_SWITCH();
				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStartPerformanceMeasurement(pPerformanceDataI4Task);
				#endif

				task_Status_sys |= I4_ACTIVE;
				task_Status_nor |= I4_ACTIVE;

				I4_ENTRY();

				#ifdef USE_DATA_CONSISTENCY
				SetDCBuffers(kI4Task);
				#endif

				SET_SYS_MODE();

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI4S);

				SET_NOR_MODE();
				UNLOCK_TASK_SWITCH();

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI4FI); /* fast import */
				#endif

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI4N);

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI4FE); /* fast export */
				#endif

				/* postprocessing */
				LOCK_TASK_SWITCH();
				#ifdef USE_DATA_CONSISTENCY
				UnlockDCBuffers(kI4Task);
				#endif

				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStopPerformanceMeasurement(pPerformanceDataI4Task);
				#endif

				I4_EXIT();
				task_Status_sys &= ~I4_ACTIVE;
				task_Status_nor &= ~I4_ACTIVE;
				UNLOCK_TASK_SWITCH();
			}
		}
	}
}

/*************************************************
*   I5
*************************************************/
void taskIntFun_I5(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= I5_ACTIVE;

	FOREVER
	{
		semTake(int5SemID, WAIT_FOREVER);

		/* check for running/stop mode and online edit */
		#ifndef _LZS_DWLWITHOUTSTOP_
		if (wLzsSysFlags_l & LZSSTAT_RUNNING)
		#else
		if ((wLzsSysFlags_l & LZSSTAT_RUNNING) && !fLockReplaceResource_l)
		#endif
		{
			/* check if enabled */
			if (pTaskConfig_g != LZSNULL && pTaskConfig_g->bI5Source != 0)
			{
				/* preprocessing */
				LOCK_TASK_SWITCH();
				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStartPerformanceMeasurement(pPerformanceDataI5Task);
				#endif

				task_Status_sys |= I5_ACTIVE;
				task_Status_nor |= I5_ACTIVE;

				I5_ENTRY();

				#ifdef USE_DATA_CONSISTENCY
				SetDCBuffers(kI5Task);
				#endif

				SET_SYS_MODE();

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI5S);

				SET_NOR_MODE();
				UNLOCK_TASK_SWITCH();

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI5FI); /* fast import */
				#endif

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI5N);

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI5FE); /* fast export */
				#endif

				/* postprocessing */
				LOCK_TASK_SWITCH();
				#ifdef USE_DATA_CONSISTENCY
				UnlockDCBuffers(kI5Task);
				#endif

				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStopPerformanceMeasurement(pPerformanceDataI5Task);
				#endif

				I5_EXIT();
				task_Status_sys &= ~I5_ACTIVE;
				task_Status_nor &= ~I5_ACTIVE;
				UNLOCK_TASK_SWITCH();
			}
		}
	}
}

/*************************************************
*   I6
*************************************************/
void taskIntFun_I6(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= I6_ACTIVE;

	FOREVER
	{
		semTake(int6SemID, WAIT_FOREVER);

		/* check for running/stop mode and online edit */
		#ifndef _LZS_DWLWITHOUTSTOP_
		if (wLzsSysFlags_l & LZSSTAT_RUNNING)
		#else
		if ((wLzsSysFlags_l & LZSSTAT_RUNNING) && !fLockReplaceResource_l)
		#endif
		{
			/* check if enabled */
			if (pTaskConfig_g != LZSNULL && pTaskConfig_g->bI6Source != 0)
			{
				/* preprocessing */
				LOCK_TASK_SWITCH();
				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStartPerformanceMeasurement(pPerformanceDataI6Task);
				#endif

				task_Status_sys |= I6_ACTIVE;
				task_Status_nor |= I6_ACTIVE;

				I6_ENTRY();

				#ifdef USE_DATA_CONSISTENCY
				SetDCBuffers(kI6Task);
				#endif

				SET_SYS_MODE();

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI6S);

				SET_NOR_MODE();
				UNLOCK_TASK_SWITCH();

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI6FI); /* fast import */
				#endif

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI6N);

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI6FE); /* fast export */
				#endif

				/* postprocessing */
				LOCK_TASK_SWITCH();
				#ifdef USE_DATA_CONSISTENCY
				UnlockDCBuffers(kI6Task);
				#endif

				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStopPerformanceMeasurement(pPerformanceDataI6Task);
				#endif

				I6_EXIT();
				task_Status_sys &= ~I6_ACTIVE;
				task_Status_nor &= ~I6_ACTIVE;
				UNLOCK_TASK_SWITCH();
			}
		}
	}
}

/*************************************************
*   I7
*************************************************/
void taskIntFun_I7(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= I7_ACTIVE;

	FOREVER
	{
		semTake(int7SemID, WAIT_FOREVER);

		/* check for running/stop mode and online edit */
		#ifndef _LZS_DWLWITHOUTSTOP_
		if (wLzsSysFlags_l & LZSSTAT_RUNNING)
		#else
		if ((wLzsSysFlags_l & LZSSTAT_RUNNING) && !fLockReplaceResource_l)
		#endif
		{
			/* check if enabled */
			if (pTaskConfig_g != LZSNULL && pTaskConfig_g->bI7Source != 0)
			{
				/* preprocessing */
				LOCK_TASK_SWITCH();
				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStartPerformanceMeasurement(pPerformanceDataI7Task);
				#endif

				task_Status_sys |= I7_ACTIVE;
				task_Status_nor |= I7_ACTIVE;

				I7_ENTRY();

				#ifdef USE_DATA_CONSISTENCY
				SetDCBuffers(kI7Task);
				#endif

				SET_SYS_MODE();

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI7S);

				SET_NOR_MODE();
				UNLOCK_TASK_SWITCH();

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI7FI); /* fast import */
				#endif

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI7N);

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI7FE); /* fast export */
				#endif

				/* postprocessing */
				LOCK_TASK_SWITCH();
				#ifdef USE_DATA_CONSISTENCY
				UnlockDCBuffers(kI7Task);
				#endif

				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStopPerformanceMeasurement(pPerformanceDataI7Task);
				#endif

				I7_EXIT();
				task_Status_sys &= ~I7_ACTIVE;
				task_Status_nor &= ~I7_ACTIVE;
				UNLOCK_TASK_SWITCH();
			}
		}
	}
}

/*************************************************
*   I8
*************************************************/
void taskIntFun_I8(void)
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	task_Ready |= I8_ACTIVE;

	FOREVER
	{
		semTake(int8SemID, WAIT_FOREVER);

		/* check for running/stop mode and online edit */
		#ifndef _LZS_DWLWITHOUTSTOP_
		if (wLzsSysFlags_l & LZSSTAT_RUNNING)
		#else
		if ((wLzsSysFlags_l & LZSSTAT_RUNNING) && !fLockReplaceResource_l)
		#endif
		{
			/* check if enabled */
			if (pTaskConfig_g != LZSNULL && pTaskConfig_g->bI8Source != 0)
			{
				/* preprocessing */
				LOCK_TASK_SWITCH();
				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStartPerformanceMeasurement(pPerformanceDataI8Task);
				#endif

				task_Status_sys |= I8_ACTIVE;
				task_Status_nor |= I8_ACTIVE;

				I8_ENTRY();

				#ifdef USE_DATA_CONSISTENCY
				SetDCBuffers(kI8Task);
				#endif

				SET_SYS_MODE();

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI8S);

				SET_NOR_MODE();
				UNLOCK_TASK_SWITCH();

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI8FI); /* fast import */
				#endif

				/* execute IEC 61131 application */
				LzsIpMainLoop(pControlSetI8N);

				#ifdef USE_SHARED_MEMORY
				LzsIpMainLoop(pControlSetI8FE); /* fast export */
				#endif

				/* postprocessing */
				LOCK_TASK_SWITCH();
				#ifdef USE_DATA_CONSISTENCY
				UnlockDCBuffers(kI8Task);
				#endif

				#ifdef ENABLE_PERFORMANCE_MONITORING_TASKS
				LzsEnvStopPerformanceMeasurement(pPerformanceDataI8Task);
				#endif

				I8_EXIT();
				task_Status_sys &= ~I8_ACTIVE;
				task_Status_nor &= ~I8_ACTIVE;
				UNLOCK_TASK_SWITCH();
			}
		}
	}
}
#endif
#endif /*_ONE_TASK_ONLY_T1_*/

#ifdef _ONE_TASK_ONLY_T1_

/*void task1fun_sys_nor(void)*/
void task1fun_nor(void) /* used the old name, so that configuration can be unchanged */
{
	BACKUP_DECLARATIONS()

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	FOREVER
	{
		semTake(task1SemID_nor, WAIT_FOREVER);

		T1_ENTRY();

		SET_SYS_MODE();

		/* execute IEC 61131 application - system mode */
		LzsIpMainLoop(pControlSetT1S);

		task_Status_sys &= ~T1_ACTIVE;

		SET_NOR_MODE();

		/* execute IEC 61131 application - normal mode */
		LzsIpMainLoop(pControlSetT1N);

		T1_EXIT();
		task_Status_nor &= ~T1_ACTIVE;
	}
}

#endif /*_ONE_TASK_ONLY_T1_*/

/*----------------------------------------------------------------------------*/
/* FUNCTION: plcComm                                                          */
/* DESCRIPT: executes the command main loop of SmartPLC                       */
/*----------------------------------------------------------------------------*/
void plcComm(void)
{
	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	install_exception_handler();
	#endif

	FOREVER
	{
		/* enable upload of watch data */
		if (LzsSysGetStatus(LZSSTAT_PROGRAM_VALID))
		{
			LzsWatchMarkDataValid(LZS_CON_ID_PROGSYS);

			#ifdef _LZS_SUPPORT_OPC_CONNECT
			{
				LZSBYTE bConnectionId;
				for (bConnectionId = 1; bConnectionId <= _LZS_MAX_NUMBER_OPC_CONNECTIONS; bConnectionId++)
				{
					LzsWatchMarkDataValid(bConnectionId);
				}
			}
			#endif
		}

		if (fEnableCommunication)
		{
			/* execute commands from OpenPCS */
			LzsCmdMainLoop();
		}
#ifndef _LZS_NO_PERSISTENCE_
#ifdef _LZS_SAVESYSTEMCMD_
		if (LzsEnvGetActivateSaveSystem() == LZSTRUE)
		{
			/* save system */
			LzsEnvResetActivateSaveSystem();
			LzsEnvSaveSystemCmd();
		}

		if (LzsEnvGetActivateRestoreSystem() == LZSTRUE)
		{
			/* restore system */
			LzsEnvResetActivateRestoreSystem();
			LzsEnvRestoreSystemCmd();
		}
#endif
#endif
		#ifdef _LZS_DWLWITHOUTSTOP_
		/* do online edit (only if a new resource is available) */
	    LzsDwlWithoutStopReplaceRes();
		#endif

		#ifdef USE_T0_WATCHDOG
		/* update recorded watchdog data */
		UpdateWatchdog();
		#endif

		#ifdef _LZS_ERROR_LOG_LED_DISPLAY
		LzsEnvUpdateLedDisplay();
		#endif

		taskDelay(1); /* run 100 times per second maximum (if other tasks leave enough CPU time free) */
	}
}
#if 0
/*================================================================
* CPU load measurement
*===============================================================*/
#define MEASUREMENT_PERIOD_TICKS 33000000
LZSBOOL periodStarted = LZSFALSE;
LZSDWORD periodStartTick = 0;
LZSDWORD lastTick = 0;
LZSDWORD newTick = 0;
LZSDWORD sumIdleTime = 0;
LZSDWORD periodDuration = 0;
LZSDWORD timeDifference = 0;

void taskSwitchHook(WIND_TCB *pOldTcb, WIND_TCB *pNewTcb)
{
	/* NOTE: this function does not use LzsEnvGetPerformanceDiffTime() for performance reasons - to avoid function calls and floating point operations */
	/* instead, it contains the code for calculating time differences directly here */

	if (pNewTcb->priority == 255) /* monitor the idle task - detect by its priority (255) */
	{
		if (periodStarted)
		{
			/* continue measurement (start of idle task) */
			lastTick = LzsEnvGetPerformanceTickCount();
		}
		else
		{
			/* start a new measurement period */
			periodStartTick = LzsEnvGetPerformanceTickCount();
			lastTick = periodStartTick;
			periodStarted = LZSTRUE;
		}
	}
	else if (pOldTcb->priority == 255)
	{
		if (periodStarted)
		{
			/* continue measurement (end of idle task) */
			newTick = LzsEnvGetPerformanceTickCount();

			/* calculate time difference and maintain sum of idle time */
			if (newTick < lastTick)
			{
				/* overflow */
				timeDifference = 0xFFFFFFFF - lastTick + newTick;
			}
			else
			{
				timeDifference = newTick - lastTick;
			}

			sumIdleTime += timeDifference;

			/* check if measurement must be finished (measurement period is over?) */
			if (newTick < periodStartTick)
			{
				/* overflow */
				periodDuration = 0xFFFFFFFF - periodStartTick + newTick;
			}
			else
			{
				periodDuration = newTick - periodStartTick;
			}

			if (periodDuration >= MEASUREMENT_PERIOD_TICKS)
			{
				/* finish measurement by setting the load values (idle time and period duration) in the process image */
				/* important: do this only if there is a valid program, otherwise (e.g. during download!) the process image pointer is not valid! */
				if (wLzsSysFlags_l & LZSSTAT_PROGRAM_VALID)
				{
					*((LZSDWORD*)(pProcImgSeg_l + 2040)) = sumIdleTime;
					*((LZSDWORD*)(pProcImgSeg_l + 2044)) = periodDuration;
				}

				/* reset variables for the next measurement period */
				sumIdleTime = 0;
				periodStarted = LZSFALSE;
			}
		}
	}
}
#endif
/* A special task is used to monitor the idle time, because:
   - In the task switch hook function, pOldTcb and pNewTcb are never NULL
   - There is no "idle" task set up by VxWorks
   - When a low priority task ends, control goes back to some of the priority 0 tasks (tJobTask, tExcTask, tLogTask, tNbioLog)
   - When a low priority task starts, control comes from a priority 0 task
   - But monitoring priority 0 tasks returns totally wrong results (not suitable to determine the CPU load)
   - With log messages in the task switch hook function, you can see sequences like this (priority old task -> priority new task):
     0x2309530 (tLogTask): 0 -> 50
     0x2339760 (tNetTask): 50 -> 0
     0x2309530 (tLogTask): 0 -> 50
     0x2339760 (tNetTask): 50 -> 0
     0x2309530 (tLogTask): 0 -> 50
     0x2339760 (tNetTask): 50 -> 0
     0x2309530 (tLogTask): 0 -> 50
     0x2339760 (tNetTask): 50 -> 0
     0x2309530 (tLogTask): 0 -> 71
     0x2600390 (tPlcComm): 71 -> 0
     0x2309530 (tLogTask): 0 -> 71
     0x2600390 (tPlcComm): 71 -> 0
     0x2309530 (tLogTask): 0 -> 71
     0x2600390 (tPlcComm): 71 -> 0
     0x2309530 (tLogTask): 0 -> 71
     0x2600390 (tPlcComm): 71 -> 0
     0x2309530 (tLogTask): 0 -> 250
     0x2333410 (tDcacheUpd): 250 -> 0
     0x2309530 (tLogTask): 0 -> 250
     0x2333410 (tDcacheUpd): 250 -> 0
     0x2309530 (tLogTask): 0 -> 250
     0x2333410 (tDcacheUpd): 250 -> 0 */
void plcIdle(void)
{
	FOREVER
	{
	}
}

/*================================================================
* Exception handling (CPU exceptions)
*===============================================================*/
#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
/* this function is used by each task to replace the original exception handler */
void exception_handler(ESFPPC* pEsf)
{
	int task_number;
    int taskId;
	LZSDWORD array_dwRegisters[NUM_REGS_EXCEPTIONBUFFER];

	/* find out which task caused the exception */
	taskId = taskIdSelf();
	if (taskId == tidTaskInt1) task_number = kI1Task;
	else if (taskId == tidTaskInt2) task_number = kI2Task;
	else if (taskId == tidTaskInt3) task_number = kI3Task;
	else if (taskId == tidTaskInt4) task_number = kI4Task;
	else if (taskId == tidTaskInt5) task_number = kI5Task;
	else if (taskId == tidTaskInt6) task_number = kI6Task;
	else if (taskId == tidTaskInt7) task_number = kI7Task;
	else if (taskId == tidTaskInt8) task_number = kI8Task;
	else if (taskId == tidTask1_nor) task_number = kT1Task;
	else if (taskId == tidTask2_nor) task_number = kT2Task;
	else if (taskId == tidTask3_nor) task_number = kT3Task;
	else if (taskId == tidTask4_nor) task_number = kT4Task;
	else if (taskId == tidTask5_nor) task_number = kT5Task;
	else if (taskId == tidCyclicTask_sys) task_number = kSYSTask;
	else if (taskId == tidTaskMain) task_number = kMainTask;
	else if (taskId == tidTaskComm) task_number = kCommTask;
	else
	{
		logMsg("exception_handler: unknown source task (priority %d)\n", taskIdCurrent->priority, 0, 0, 0, 0, 0);
		task_number = -1;
	}

	/* get registers */
	LzsEnvGetRegisters(array_dwRegisters, (void*)pEsf);

	/* register exception (this will usually stop the system) */
	LzsErrlogRegisterException(pEsf->vecOffset, array_dwRegisters, NUM_REGS_EXCEPTIONBUFFER);
	logMsg("CPU exception! Vector: 0x%x Task: %d MSR: 0x%x CR: 0x%x\n", pEsf->vecOffset, task_number, pEsf->regSet.msr, pEsf->regSet.cr, 0, 0);

	/* enable communication for diagnostics - in case the exception happened during startup in the main task */
	fEnableCommunication = LZSTRUE;

	/* prepare communication restart, in case the exception comes from the communication task (such as on manual coldstart) */
	if (task_number == kCommTask)
	{
		tidTaskComm = taskSpawn ("tPlcComm", TASK_COMM_PRIO, TASK_FLAGS, STACK_SIZE, (FUNCPTR)plcComm,0,0,0,0,0,0,0,0,0,0);
	}

	/* call original VxWorks exception handler (which stops the task) */
	/*excExcHandle(pEsf);*/

	/* OR: */

	/* prepare restart and stop the task */
	globalRestartTask = task_number;
	taskExit(0);
}

void install_exception_handler()
{
	excVecSet((FUNCPTR*)_EXC_OFF_RESET, (FUNCPTR) exception_handler);
	excVecSet((FUNCPTR*)_EXC_OFF_MACH, (FUNCPTR) exception_handler);
	excVecSet((FUNCPTR*)_EXC_OFF_DATA, (FUNCPTR) exception_handler);
	excVecSet((FUNCPTR*)_EXC_OFF_INST, (FUNCPTR) exception_handler);
	/*excVecSet((FUNCPTR*)_EXC_OFF_INTR, (FUNCPTR) exception_handler);*/ /* system does not run with this vector installed */
	/*excVecSet((FUNCPTR*)_EXC_OFF_ALIGN, (FUNCPTR) exception_handler);*/ /* system does not run with this vector installed */
	/*excVecSet((FUNCPTR*)_EXC_OFF_PROG, (FUNCPTR) exception_handler);*/ /* we do not handle this exception, because it occurs when debugging! */
	excVecSet((FUNCPTR*)_EXC_OFF_FPU, (FUNCPTR) exception_handler);
	/*excVecSet((FUNCPTR*)_EXC_OFF_DECR, (FUNCPTR) exception_handler);*/ /* system does not run with this vector installed */
	excVecSet((FUNCPTR*)_EXC_OFF_SYSCALL, (FUNCPTR) exception_handler);
	excVecSet((FUNCPTR*)_EXC_OFF_TRACE, (FUNCPTR) exception_handler);
	excVecSet((FUNCPTR*)_EXC_OFF_INST_BRK, (FUNCPTR) exception_handler);
	excVecSet((FUNCPTR*)_EXC_OFF_SYS_MNG, (FUNCPTR) exception_handler);
}
#endif /* _LZS_ERROR_LOG_CPUEXCEPTIONS */

/*================================================================
* Exception handling (ACFAIL and SYSFAIL handling)
*===============================================================*/
/* U2 bridge(vme bridge) manage the acfail and sysfail interrupt.
 * after interrupt connect, you can generate the interrupt by connect acfail or sysfail signal to Ground.
 * acfail and sysfail signal are standard VMEBUS signal. */
#if 0
void exception_IntHandler_acfail(void)
{
	int a;

	sysUnivIntDisable(UNIVERSE_ACFAIL_INT);

	a=sysInLong(univBaseAdrs + 0x304);
	logMsg("ACFAIL handler: state is 0x%x\n",a,0,0,0,0,0);

	sysOutLong(univBaseAdrs + 0x304, 0x8000); /* clear interrupt flag */

	a=sysInLong(univBaseAdrs + 0x304);
	logMsg("ACFAIL handler: new state is 0x%x\n",a,0,0,0,0,0);

	/* register exception */
	LzsErrlogRegisterException(ACFAIL_VECTOR, LZSNULL, 0);

	sysUnivIntEnable(UNIVERSE_SYSFAIL_INT | UNIVERSE_ACFAIL_INT);
}

void exception_IntHandler_sysfail(void)
{
	int a;

	sysUnivIntDisable(UNIVERSE_SYSFAIL_INT);

	a=sysInLong(univBaseAdrs + 0x304);
	logMsg("SYSFAIL handler: state is 0x%x\n",a,0,0,0,0,0);

	sysOutLong(univBaseAdrs + 0x304, 0x4000); /* clear interrupt flag */

	a=sysInLong(univBaseAdrs + 0x304);
	logMsg("SYSFAIL handler: new state is 0x%x\n",a,0,0,0,0,0);

	/* register exception */
	LzsErrlogRegisterException(SYSFAIL_VECTOR, LZSNULL, 0);

	sysUnivIntEnable(UNIVERSE_SYSFAIL_INT | UNIVERSE_ACFAIL_INT);
}
#endif
/*================================================================
* Watchdog
*===============================================================*/
#ifdef USE_T0_WATCHDOG
void UpdateWatchdog()
{
	int i;
	LZSDWORD dwTimeDiff;
	LZSDWORD dwTimeStampNow = LzsEnvGetTickCount();

	/* remove recorded watchdog errors which are from before the watchdog time span */
	for (i = 0; i < NUM_WD_ERRORS_BEFORE_STOP; i++)
	{
		if (arrayWDErrors[i].fIsValid == LZSTRUE)
		{
			/* get timestamp difference to now */
			if (dwTimeStampNow < arrayWDErrors[i].dwTimeStamp)
			{
				/* overflow */
				dwTimeDiff = 0xFFFFFFFF - arrayWDErrors[i].dwTimeStamp + dwTimeStampNow;
			}
			else
			{
				dwTimeDiff = dwTimeStampNow - arrayWDErrors[i].dwTimeStamp;
			}

			if (dwTimeDiff >= WD_TIMESPAN_MS)
			{
				/* remove (invalidate) record */
				arrayWDErrors[i].fIsValid = LZSFALSE;
			}
		}
	}
}

void WatchdogHandler()
{
	logMsg("Watchdog timeout!\n",0,0,0,0,0,0);

	dwNumWDEvents++;

	if (dwNumWDEvents >= NUM_WD_EVENTS_BEFORE_REINIT)
	{
		/* reinitialize timer */
		clockDisable(AUXCLOCK);
		clockInterruptStart(AUXCLOCK, &task0SemID);

		/* reset variables */
		dwNumWDEvents = 0;

		/* register watchdog error */
		logMsg("Watchdog ERROR!\n",0,0,0,0,0,0);
		LzsErrlogRegisterError(kLzsTaskAdministrationError, kLzsWatchdogTimeoutError, 0, 0, 0);
	}

	/* restart watchdog (if still running) */
	if (wLzsSysFlags_l & LZSSTAT_RUNNING)
	{
		if (wdStart(t0WatchDogId, LzsEnvGetWatchdogTimeout(), WatchdogHandler, NULL) == ERROR)
		{
			logMsg("Error starting T0 watchdog!\n",0,0,0,0,0,0);
		}
		else
		{
			logMsg("Watchdog for T0 restarted (%d ms)\n",LzsEnvGetWatchdogTimeout(),0,0,0,0,0);
		}
	}
}
#endif

/*================================================================
* Clock synchronization
*===============================================================*/
#ifdef CLOCK_SYNCHRONIZATION
#ifdef _MASTER_CPU_
void clockSyncTask(void)
{
	struct timespec *ts;

	ts = (struct timespec*)smMemMalloc(sizeof(struct timespec));
	if (ts == NULL)
	{
		logMsg("Shared memory initialization for clock sync error\n",0,0,0,0,0,0);
		return;
	}

	if (smNameAdd("clock_sync", (void*)smObjLocalToGlobal(ts), T_SM_BLOCK) == ERROR)
	{
		logMsg("Shared memory initialization: name add error (MASTER)!\n",0,0,0,0,0,0);
		return;
	}

	FOREVER
	{
		taskDelay(CLOCK_SYNC_INTERVAL);

		clock_gettime(CLOCK_REALTIME, ts);

		/*
		logMsg("clock sync %ds%dns\n",ts->tv_sec,ts->tv_nsec,0,0,0,0);
		*/

		if (ERROR == sysBusIntGen(CLOCK_SYNC_INT_LEVEL, CLOCK_SYNC_INT_VECTOR))
		{
			logMsg("error generating Bus Interrupt\n",0,0,0,0,0,0);
		}
	}
}

#else

/* interrupt service routine for clock synchronization */
void clockSyncIntHandler(int i)
{
	clock_settime(CLOCK_REALTIME, pClockSyncTS);
	/*
	logMsg("clock sync ok %ds%dns\n",pClockSyncTS->tv_sec,pClockSyncTS->tv_nsec,0,0,0,0);
	*/
}
#endif
#endif /* CLOCK_SYNCHRONIZATION */
