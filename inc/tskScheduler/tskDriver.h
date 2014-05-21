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

#ifdef  SBC_VME7050
#define RTC_ADDRESS			0XFE057FF0
#define MAILBOX0			0x8cfe0348
#endif

#define MAILBOX1 (MAILBOX0 + 0x4 )
#define MAILBOX2 (MAILBOX0 + 0x8 )
#define MAILBOX3 (MAILBOX0 + 0xC )



/******************************************
*  interrupt  drivers
*******************************************/
void mailboxInterrupt(SEM_ID mSemID);
void auxclockInterrupt(SEM_ID mSemID, float interval);



/******************************************
* WatchDog & RTC
*******************************************/
BOOL watchdogInit(void);
unsigned long getSystemDate(void);
unsigned long getSystemTime(void);
STATUS setSystemDate(unsigned long newdate);
STATUS setSystemTime(unsigned long newtime);



/******************************************
* Shared memory
*******************************************/

/*STATUS shmWrite(unsigned int addr, char *pData , unsigned int dataSize);
char * shmRead(unsigned int addr,unsigned int length);*/



/******************************************
 * Location for exception handling buffers
 * ***************************************/
#define EXCEPTION_MEM_OFFSET 0x200000
#define EXCEPTION_MEM_ADDR (sysMemTop() + EXCEPTION_MEM_OFFSET)
#define EXCEPTION_MEM_LEN (0x1000000 - EXCEPTION_MEM_OFFSET)
#define EXCEPTION_MEM_MAGIC 0x67F58AC4
#define EXCEPTION_MEM_MAGIC2 0xA147BD09



/*******************************************
 *  PCI 9030
 * *****************************************/
#define DEVICEID 0x0374/*0x90300x9030*/
#define VENDORID 0x10b5

#define BASEADD_NUM					6
#define INTCSR						0x4c

typedef struct STPCI_HWA_DMA_PARAMETER
 {
   int nChannle;
   BOOL bDirect; /*TRUE  T  DEV--->PCI, FALSE R  DEV<----PCI*/
   unsigned long ulDMAMode;
   void *pDataBuffer; /* CH 0 data address*/
   void *pDataBufferCH0; /* CH 0 data address*/
   void *pDataBufferCH1; /* CH 0 data address*/
   unsigned long dDataNum; /*dma all Num*/
   unsigned long dDataLength; /*dma length every time*/

 } PCI_HWA_DMA_PARAMETER,  *PPCI_HWA_DMA_PARAMETER;

 typedef struct STPCI_HWA_DEVICE
   {
	 PCI_HEADER_DEVICE *pDev;
	 unsigned int irq;
	 void *pRegBase;

	 unsigned long dBoardNo;
	 /*UINT32 IOBaseAddress[BASEADD_NUM];*/
	 unsigned long IOBaseAddress[BASEADD_NUM];
	 PCI_HWA_DMA_PARAMETER stDma;
	 unsigned long dBoardKind;
	 char strBoardKindName[50];
	 SEM_ID semBID_DataReadyEvent;
	 SEM_ID *psemBID_BufferFullEvent;
	 SEM_ID semBID_BufferFullEvent;
	 SEM_ID semBID_Int;

	 VOIDFUNCPTR Isr_Irq;
	 int tidDpcFor_Irq;
	 BOOL flagIntConnecting;
	 unsigned long ulDmaMaxLength;
   } PCI_HWA_DEVICE;

   struct STPCI_HWA_DEVICE Dev9030[1];

int HWA9030_Device_WriteDword(int num, unsigned long dBarNo, unsigned long dOffSet, unsigned long dValue);
int HWA9030_Device_WriteDword16(int num, unsigned long dBarNo, unsigned long dOffSet, unsigned short dValue);
int HWA9030_Device_WriteDword32(int num, unsigned long dBarNo, unsigned long dOffSet, unsigned long dValue);
int HWA9030_Device_ReadDword16(int num, unsigned long dBarNo, unsigned long dOffSet, unsigned short *pdValue);
int HWA9030_Device_ReadDword_fpga16(int num, unsigned long dBarNo, unsigned long dOffSet, unsigned short *pdValue);
int HWA9030_Device_ReadDword32(int num, unsigned long dBarNo, unsigned long dOffSet, unsigned long *pdValue);
int HWA9030_Device_Init(int num);

int HWA9030_Device_intConnect(int num, SEM_ID sem );
void HWA9030_Device_ISR(int num);

void pciTdmInterrupt(SEM_ID mSemID);



/********************************************************
* end of header file
********************************************************/
#endif
