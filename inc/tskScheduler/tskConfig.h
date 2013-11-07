/*******************************************************
*      File Message Area
*
* File name:   		tskConfig.h
* Description:
* Create date: 		09-07-25
* Author:					Shen KK
* Modify record:
*
*******************************************************/
#ifndef  _TSKCONFIG_H_
#define  _TSKCONFIG_H_
#include "semlib.h"

/*==============================================
*system define area
*==============================================*/

/**************************/
/*#define FOREVER while(1)*/

/**************************/
#define MASTER_BOARD    			0x01
#define SLAVE_BOARD					0x10

/**************************/
#define SEND_T0_SIGNAL(value)  		sysOutLong(MAILBOX0,value);           /*the value is used to check right or wrong by slave board*/



/**************************
*task "active" (running/scheduled) flags
**************************/
#define T1_ACTIVE					0x0001
#define T2_ACTIVE					0x0002
#define T3_ACTIVE					0x0004
#define T4_ACTIVE					0x0008
#define T5_ACTIVE					0x0010

#define I1_ACTIVE					0x0020
#define I2_ACTIVE					0x0040
#define I3_ACTIVE					0x0080
#define I4_ACTIVE					0x0100
#define I5_ACTIVE					0x0200
#define I6_ACTIVE					0x0400
#define I7_ACTIVE					0x0800
#define I8_ACTIVE					0x1000

#define TTASKS_MASK					0x001F



/**************************
*task cycle error configuration
**************************/
#define MAX_CYCLE_ERROR 3 /* maximum number of consecutive cycle errors tolerated */



/**************************
*define all the tasks' priority
**************************/
#define TASK_MAIN_PRIO					8

#define STOP_SCHEDULER_PRIO				9

#define INTERRUPT1_PRIO					10
#define INTERRUPT2_PRIO					11
#define INTERRUPT3_PRIO					12
#define INTERRUPT4_PRIO					13
#define INTERRUPT5_PRIO					14
#define INTERRUPT6_PRIO					15
#define INTERRUPT7_PRIO					16
#define INTERRUPT8_PRIO					17

#define TASK0_PRIO						20

#define CYCLIC_TASK_SYS_PRIO			40/*21*/

#define TASK1_NOR_PRIO					41/*22*/
#define TASK2_NOR_PRIO					42/*23*/
#define TASK3_NOR_PRIO					43/*24*/
#define TASK4_NOR_PRIO					44/*25*/
#define TASK5_NOR_PRIO					45/*26*/
#define TASK6_NOR_PRIO					46/*26*/

#define HMI_COMM_PRIO					60

#define TASK_LISTEN_PRIO				70

#define TASK_COMM_PRIO					71

#define TCP_COMM_PRIO					72

#define TASK_MSG_QUEUE_PRIO				80



/***********************************
*defines for clock synchronization
***********************************/
#define TASK_CLOCK_SYNC_PRIO			90
#define CLOCK_SYNC_INT_LEVEL			2
#define CLOCK_SYNC_INT_VECTOR			64
#define CLOCK_SYNC_INTERVAL				5000



/***********************************
*task mode setting macro
***********************************/
#define SET_NOR_MODE() mode = kNormalMode;
#define SET_SYS_MODE() mode = kSystemMode;
#define SET_INI_MODE() mode = kInitMode;


/***********************************
* the macros about TA
************************************/
/*BACKUP*/
#define TA_BACKUP() dps_ta_bak = dps_ta

/*RESTORE*/
#define TA_RESTORE() dps_ta = dps_ta_bak

/*GET*/
#define T1_TA_GET()						  dps_ta = dps_t1_ta
#define T2_TA_GET()						  dps_ta = dps_t2_ta
#define T3_TA_GET()						  dps_ta = dps_t3_ta
#define T4_TA_GET()						  dps_ta = dps_t4_ta
#define T5_TA_GET()						  dps_ta = dps_t5_ta


#define I1_TA_GET()						  dps_ta = dps_i1_ta
#define I2_TA_GET()						  dps_ta = dps_i2_ta
#define I3_TA_GET()						  dps_ta = dps_i3_ta
#define I4_TA_GET()						  dps_ta = dps_i4_ta
#define I5_TA_GET()						  dps_ta = dps_i5_ta
#define I6_TA_GET()						  dps_ta = dps_i6_ta
#define I7_TA_GET()						  dps_ta = dps_i7_ta
#define I8_TA_GET()						  dps_ta = dps_i8_ta


/***********************************
* the macros about MODE
************************************/
/*BACKUP*/
#define MODE_BACKUP() dps_mode_bak = mode

/*RESTORE*/
#define MODE_RESTORE() mode = dps_mode_bak


/***********************************
* the macros about register set and NC help segment
************************************/
/*BACKUP*/
#define REG_BACKUP() pProgramData_bak = pCurrentProgramData_g;

/*RESTORE*/
#define REG_RESTORE() 	pCurrentProgramData_g = pProgramData_bak;



/*****************************
*Task entry and exit
*****************************/
/*ENTRY*/
#define SYS_ENTRY();			REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		SET_SYS_MODE();

#define T1_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		T1_TA_GET();		SET_NOR_MODE();
#define T2_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		T2_TA_GET();		SET_NOR_MODE();
#define T3_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		T3_TA_GET();		SET_NOR_MODE();
#define T4_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		T4_TA_GET();		SET_NOR_MODE();
#define T5_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		T5_TA_GET();		SET_NOR_MODE();

#define I1_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		I1_TA_GET();
#define I2_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		I2_TA_GET();
#define I3_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		I3_TA_GET();
#define I4_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		I4_TA_GET();
#define I5_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		I5_TA_GET();
#define I6_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		I6_TA_GET();
#define I7_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		I7_TA_GET();
#define I8_ENTRY();				REG_BACKUP();		MODE_BACKUP();		TA_BACKUP();		I8_TA_GET();


/*EXIT*/
#define SYS_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();

#define T1_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define T2_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define T3_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define T4_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define T5_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();

#define I1_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define I2_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define I3_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define I4_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define I5_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define I6_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define I7_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();
#define I8_EXIT();				TA_RESTORE();		MODE_RESTORE();		REG_RESTORE();


/*DECLARATIONS OF BACKUP VARIABLES, to be declared locally in each task function (=> stack variables)*/
#define BACKUP_DECLARATIONS() \
	unsigned char dps_mode_bak; /* to backup 'mode' before giving a new value to it */ \
	float dps_ta_bak;           /* to backup 'dps_ta' before giving a new value to it */ \
	void* pProgramData_bak;     /* to backup 'pCurrentProgramData_g' (VM register set) */ \


/******************************
*Task lock
******************************/
#define LOCK_TASK_SWITCH()		taskLock()
#define UNLOCK_TASK_SWITCH()	taskUnlock()


/******************************
*Bus lock
******************************/
#ifdef ENABLE_PERFORMANCE_MONITORING

#define LOCK_BUS() \
			LzsEnvStartPerformanceMeasurement(pPerformanceDataCustom1); \
			sysVmeLock(); \
			LzsEnvStopPerformanceMeasurement(pPerformanceDataCustom1);
#define UNLOCK_BUS() \
			LzsEnvStartPerformanceMeasurement(pPerformanceDataCustom6); \
			sysVmeUnlock(); \
			LzsEnvStopPerformanceMeasurement(pPerformanceDataCustom6);

#else

#define LOCK_BUS()		sysVmeLock()
#define UNLOCK_BUS()	sysVmeUnlock()

#endif


/*******************************
*Date & Time of system
*******************************/
#define  RTC_YEAR
#define  RTC_MONTH
#define  RTC_DOM						/*DAY OF MONTH*/
#define  RTC_DOW						/*DAY OF WEEK*/
#define  RTC_HOUR
#define	 RTC_MINUTE
#define  RTC_SECOND


/******************************
* Shared memory struct
******************************/
#undef USE_SHARED_MEMORY  /* ----------------yuhai--------2010-03-26---------------*/


#define SHM_BUFFER_SIZE		(64 * 1024)

#ifdef USE_SHARED_MEMORY
#ifndef SHM_BUFF
	typedef struct SHM_BUFF
	{
		SEM_ID semSmId;
		char buff [SHM_BUFFER_SIZE];
	} SHM_BUFF;
#endif

#endif



/***************************************************************
*  end of header file
****************************************************************/
#endif

