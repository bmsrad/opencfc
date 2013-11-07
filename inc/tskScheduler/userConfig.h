/*******************************************************
*      File Message Area
*
* File name:   		userConfig.h
* Description:
* Create date: 		09-07-25
* Author:					Shen KK
* Modify record:
*
*******************************************************/
#ifndef _USER_CONFIG_H_
#define _USER_CONFIG_H_
#include "semlib.h"


/*===============================================
*user define  area
*===============================================*/

/**************************
* Platform
**************************/

#define SBC_VME7050
#undef  SBC_VG5

/**************************
* Debug msg
**************************/
#undef  DEBUG_MSG

/**************************
* multiCPU syn msg
**************************/
#undef  MULTI_CPU_SYN

/**************************
* board msg
**************************/
#ifndef BOARD_MSG
	#define BOARD_MSG					MASTER_BOARD         /*MASTER_BOARD or  SLAVE_BOARD*/
#endif

/**************************
* task spawn flags
**************************/

#define TASK_FLAGS			VX_FP_TASK

/**************************
* task stack size msg
**************************/

#define STACK_SIZE			(100 * 1024)     /*set the size of task's stack*/
                                             /*TO DO: use the checkStack function to determine the required stack size!!!*/

/**************************
* interrupt assignment msg
**************************/
#define INT_HANDLE_ENABLE


#define INT1_ENABLE
#undef INT2_ENABLE
#undef INT3_ENABLE
#undef INT4_ENABLE
#undef INT5_ENABLE
#undef INT6_ENABLE
#undef INT7_ENABLE
#undef INT8_ENABLE


#ifdef INT_HANDLE_ENABLE

#ifdef  INT1_ENABLE
#define INT_HANDLE_I1(mSemID)    pciTdmInterrupt(mSemID)
#endif
#ifdef  INT2_ENABLE
#define INT_HANDLE_I2(mSemID)
#endif
#ifdef  INT3_ENABLE
#define INT_HANDLE_I3(mSemID)
#endif
#ifdef  INT4_ENABLE
#define INT_HANDLE_I4(mSemID)
#endif
#ifdef  INT5_ENABLE
#define INT_HANDLE_I5(mSemID)
#endif
#ifdef  INT6_ENABLE
#define INT_HANDLE_I6(mSemID)
#endif
#ifdef  INT7_ENABLE
#define INT_HANDLE_I7(mSemID)
#endif
#ifdef  INT8_ENABLE
#define INT_HANDLE_I8(mSemID)
#endif

#endif



/*****************************
*Shared memory
******************************/
#undef USE_SHARED_MEMORY    /* ----------------yuhai--------2010-03-26---------------*/

#ifdef USE_SHARED_MEMORY

#define _MASTER_CPU_
#undef _SLAVE_CPU_

#define SHM_BUFFER_SIZE		(64 * 1024)
#define SHM_BUFFER_NAME		"sharedMemory"

#define SHMDC_NAME          "shmDCMemory"
#define SHMDC_BUFFER_SIZE   (896 * 1024)

#define SHM_SLAVE_DELAY 10000

#define SHM_SLAVE_NUM_RETRIES 10
#define SHM_SLAVE_RETRY_WAIT 2000

typedef struct SHM_BUFFER
{
	SEM_ID  sm_semId;
	char    sm_buff[SHM_BUFFER_SIZE];

} SHM_BUFFER;

#endif



/*******************************************************
* end of file
*******************************************************/
#endif

