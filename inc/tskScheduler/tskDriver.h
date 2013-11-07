/*******************************************************
*      File Message Area
*
* File name:   		tskTimer.h
* Description:		this file is a header file of tskTimer.c
* Create date: 		09-03-20
* Author:				  Shen KK
* Modify record:
*
*******************************************************/

#ifndef _TSKTIMER_H_
#define _TSKTIMER_H_
/********************************************************/

#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "drv/pci/pciConfigLib.h"
#include "drv/pci/pciIntlib.h"
#include "drv/pci/pciConfigShow.h"
#include "drv/pci/pciHeaderDefs.h"
#include "pci.h"
#include "vmlib.h"
#include "iv.h"
#include "taskLib.h"
#include "fioLib.h"
#include "logLib.h"
#include "intLib.h"
#include "sysLib.h"
#include "math.h"
#include "semLib.h"

#include "vxWorks.h"
#include "taskLib.h"
#include "logLib.h"
#include "sysLib.h"
#include "rebootLib.h"
#include <semLib.h>
#include <semSmLib.h>
#include <smNameLib.h>
#include <taskLib.h>
#include <sysLib.h>
#include <smMemLib.h>
#include <smObjLib.h>

#include "vxWorks.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "pci.h"
#include "vmlib.h"
#include "iv.h"
#include "taskLib.h"
#include "fioLib.h"
#include "logLib.h"
#include "intLib.h"
#include "sysLib.h"
#include "math.h"
#include "semLib.h"


#include "vxWorks.h"
#include "userConfig.h"
#include "tskConfig.h"

#include "inc/smartplc/odk_plc.h"
#include "VME7050/xj/userdefine.h"
/*******************************************
*Debug message functions:
********************************************/
#ifndef traceMsg
#define traceMsg0(msg)    logMsg(msg,0,0,0,0,0,0);
#endif



/******************************************
*Auxclock driver
*******************************************/

#define AUXCLK_INTERVAL_TIME			0.0001


#define AUXCLOCK  	0x01
#define SYSCLOCK  	0x10



ULONG clockDisable(UCHAR timerType);
BOOL setClockRate(UCHAR timerType,float requestTime);
BOOL resumeClock(UCHAR timerType);
ULONG  clockInterruptStart(UCHAR timerType, SEM_ID *pClockSem);


unsigned long long getClockTicks();


unsigned int getAuxClkRatio(float interval);
void auxInt(SEM_ID ClockSem);
void setRtc(int year,int month,int day,int hour,int minute,int second);
void getDaysMS(void);
void sysClkInt(void);
/******************************************
*Mailbox driver
*******************************************/




#ifdef  SBC_VG5
#define RTC_ADDRESS			0xEFF10020
#define MAILBOX0			0x8cfe0348
#endif


#define MAILBOX1 (MAILBOX0 + 0x4 )
#define MAILBOX2 (MAILBOX0 + 0x8 )
#define MAILBOX3 (MAILBOX0 + 0xC )



/******************************************
*  interrupt  drivers
*******************************************/
#if 0
void mailboxInterrupt(SEM_ID mSemID);
void auxclockInterrupt(SEM_ID mSemID, float interval);
#endif




/******************************************
* WatchDog & RTC
*******************************************/

#if 0
BOOL watchdogInit(void);
unsigned long getSystemDate(void);
unsigned long getSystemTime(void);
STATUS setSystemDate(unsigned long newdate);
STATUS setSystemTime(unsigned long newtime);
#endif

#endif
