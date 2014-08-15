/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Di, 15 Dez  98                                                                */
/*                                                                               */
/* DESCRIPTION: Environment interface of OpenPCS Runtime System                  */
/*********************************************************************************/

/* ======================================================================== */
/*  The functions in this module represent the interface to the environment */
/* ======================================================================== */

/*#define SMARTPLC_TRACE*/

#include    "oem/config.h"        /* configuration defines */
#include    "oem/odk_prj.h"
#include    "smartplc/odk_plc.h"
#include    "smartplc/nl_sks.h"
#include    "smartplc/lzs.h"
#include    "smartplc/odk_szm.h"
#include    "oem/oem_def.h"
#include    "smartplc/external.h"
#include	"smartplc/structs.h"
#include	"smartplc/lzspers.h"
#include	"smartplc/reservedsegments.h"

#include    "tskScheduler/userConfig.h"
#include    "tskScheduler/tskConfig.h"
#include    "tskScheduler/tskDriver.h"


#include <ioLib.h>
#include <tickLib.h>
#include <memLib.h>
#include <logLib.h>
#include <semLib.h>
#include <semSmLib.h>
#include <smNameLib.h>
#include <sysLib.h>
#include <smMemLib.h>
#include <smObjLib.h>

#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
#include <esf.h>
#endif

extern void sysVmeLock(void);
extern void sysVmeUnlock(void);
IMPORT UINT32 univBaseAdrs;
extern unsigned int G_dwTickCount;

/************************************************************/
/* for persistency                                          */
/************************************************************/
#define PERSISTENCY_BUFFER_SIZE 512
#define IECProgram "/ata0/iecrom.dat"
#ifdef _LZS_DYNAMIC_RETAIN_
#define DRDataFile "/ata0/dretain.dat"
#endif

LZSDWORD dwByteCounter;
LZSBYTE arrBufferPersistence[PERSISTENCY_BUFFER_SIZE];
int iecProgFd;
/***********************************************************/

/* write the name of your hardware here */
/* use characters instead of a string */
LZSCHAR g_hardware_name[] = {'S','m','a','r','t','P','L','C','\0'} ;

#ifdef _LZS_DWL_RAWFILE_
#define sFilenameBackup "/ata0/vxworks_backup"
#define sFilenameTemp   "/ata0/vxworks_new"
#define sFilename       "/ata0/vxworks"
int RawFileTemp;
#endif

/***************************************************************************/
/* here you can define your memory for the IEC program                     */

/* IECMEMORY is dynamically allocated in LzsEnvMemInitialize */
#define LZS_MAXMEM (1 * 1024 * 1024)
LZSBYTE* IECMEMORY;

#ifdef _LZS_PRAGMANOCLEAR_  /* when Saveram is used IEC-memory should not be cleared */
#pragma noclear
#endif
/***************************************************************************/

/* counter for used mem */
LZSDWORD dwUsedMem_l = 0;

#ifdef _LZS_PRAGMANOCLEAR_
#pragma clear
#endif

/*----------------------------------------------------------------------------*/
/* DESCRIPT: structure for internal memory management                         */
/*----------------------------------------------------------------------------*/
struct sMemHeader
{
#ifdef LZSENV_MEMHEADER_NOBITFIELDS        /* define this, if your compiler has no or broken bitfield support */
    LZSBOOL     fFree;
    LZSDWORD    dSize;
#else
    LZSDWORD    fFree : 1;
    LZSDWORD    dSize : 31;
#endif
    struct sMemHeader *pPrev;
    struct sMemHeader *pNext;
} ;

typedef struct sMemHeader tMemHeader;

/*#############################################################################*/
/*                                                                             */
/*            LED FUNCTIONS                                                    */
/*                                                                             */
/*#############################################################################*/

#ifdef _LZS_ERROR_LOG_LED_DISPLAY

typedef struct ledDisplyPara_st
{
	unsigned int redLedCycTime;
	unsigned int greenLedCycTime;
	unsigned int redLedCurCnt;
	unsigned int greenLedCurCnt;

} ledDisplyPara_st;

typedef struct ledDisplayMode_st
{
	unsigned int redLedCycle;
	unsigned int greenLedCycle;

} ledDisplayMode_st;

#define LEDLIGHTTIME				200
#define LEDALWAYSLIGHT				0xffffffff
#define LEDLIGHTOFF					0x0

#define LEDDISPLAYMODENB			11
#define PLCSTOP_LEDCATEGORY			(NUM_ERROR_CATEGORIES)
#define EXCEPTION_LEDCATEGORY		(NUM_ERROR_CATEGORIES+1)
#define PLCRUNOK_LEDCATEGORY		(NUM_ERROR_CATEGORIES+2)
#define PLCINITOK_LEDCATEGORY		(NUM_ERROR_CATEGORIES+3)
#define PLCTASKERR_LEDCATEGORY		(NUM_ERROR_CATEGORIES+4)

const ledDisplayMode_st ledDisModeTable[LEDDISPLAYMODENB]=
{
/*Init state*/
	{LEDLIGHTOFF,1000},							/*0 -- Initial successful*/
	{LEDALWAYSLIGHT,LEDLIGHTOFF},				/*1 -- Initial error*/
/*Run state*/
	{LEDLIGHTOFF,1000},							/*2 -- running ok,  */
	{LEDALWAYSLIGHT,1000},						/*3 -- user error, */
	{500,1000},									/*4 -- Task administration error */
	{1000,1000},								/*5 -- Communication error */
	{2000,1000},								/*6 -- Monitoring error */
/*Stop state*/
	{LEDALWAYSLIGHT,LEDALWAYSLIGHT},			/*7 -- user stop*/
	{500,LEDALWAYSLIGHT},						/*8 -- runtime error*/
	{1000,LEDALWAYSLIGHT},						/*9 -- hardware error*/
	{2000,LEDALWAYSLIGHT}						/*10 - System fault and exceptions*/
};

/* NOTE: for error categories, see lzstypes.h! */
const unsigned int ledDisplayOfErrCategoryTable_g[] =
{
	 0, 1, 4, 9, 3, 8, 8, 8, 5, 5, 5, 5, 5, 5, 5, 5, /* categories 0..15 */
	 5, 5,10,10,10,10,10,10,10,10,10,10,10,10,10,10, /* categories 16..31 */
	10,10,10,10,10,10,10,10,10,10, 7,10, 2, 0, 8 /* categories 32..46, where number 42 is for error/user stop (7), number 43 is for exceptions (10), number 44 is for running OK (2), number 45 is for init OK (0), number 46 is for fatal task cycle error (8) (all these are not defined as categories in lzstypes.h!) */
};

ledDisplyPara_st ledDisplayPara_g;				/*global variable*/

/**********************************************************************/
/* FUNCTION:    LzsEnvUpdateLedDisplay                                */
/* DESCRIPTION:	to light LED                                          */
/* RETURN:      N.A.                                                  */
/* CALLED:      communication task                                    */
/**********************************************************************/
LZSBOOL fRedLedOn = LZSFALSE;
LZSBOOL fGreenLedOn = LZSFALSE;
LZSDWORD dwLastTick = 0;

void LzsEnvUpdateLedDisplay(void)
{
	LZSBOOL fSwitchRedLedOn = LZSFALSE;
	LZSBOOL fSwitchRedLedOff = LZSFALSE;
	LZSBOOL fSwitchGreenLedOn = LZSFALSE;
	LZSBOOL fSwitchGreenLedOff = LZSFALSE;
	LZSDWORD dwTicksDiff = 0;
	LZSDWORD dwCurTick = LzsEnvGetTickCount();

	if (dwCurTick < dwLastTick)
	{
		/* overflow */
		dwTicksDiff = 0xFFFFFFFF - dwLastTick + dwCurTick;
	}
	else
	{
		dwTicksDiff = dwCurTick - dwLastTick;
	}

	/*Red LED*/
	if (ledDisplayPara_g.redLedCycTime == LEDLIGHTOFF)
	{
		/* switch red LED off (later), if necessary */
		if (fRedLedOn) fSwitchRedLedOff = LZSTRUE;
	}
	else if (ledDisplayPara_g.redLedCycTime == LEDALWAYSLIGHT)
	{
		/* switch red LED on (later), if necessary */
		if (!fRedLedOn) fSwitchRedLedOn = LZSTRUE;
	}
	else
	{
		if (ledDisplayPara_g.redLedCurCnt >= LEDLIGHTTIME)
		{
			/* switch red LED off (later), if necessary */
			if (fRedLedOn) fSwitchRedLedOff = LZSTRUE;
		}
		else if (ledDisplayPara_g.redLedCurCnt == 0)
		{
			/* switch red LED on (later), if necessary */
			if (!fRedLedOn) fSwitchRedLedOn = LZSTRUE;
		}

		ledDisplayPara_g.redLedCurCnt += dwTicksDiff;
		if (ledDisplayPara_g.redLedCurCnt >= ledDisplayPara_g.redLedCycTime)
		{
			ledDisplayPara_g.redLedCurCnt = 0;
		}
	}

	/*Green LED*/
	if (ledDisplayPara_g.greenLedCycTime == LEDLIGHTOFF)
	{
		/* switch green LED off (later), if necessary */
		if (fGreenLedOn) fSwitchGreenLedOff = LZSTRUE;
	}
	else if (ledDisplayPara_g.greenLedCycTime == LEDALWAYSLIGHT)
	{
		/* switch green LED on (later), if necessary */
		if (!fGreenLedOn) fSwitchGreenLedOn = LZSTRUE;
	}
	else
	{
		if (ledDisplayPara_g.greenLedCurCnt >= LEDLIGHTTIME)
		{
			/* switch green LED off (later), if necessary */
			if (fGreenLedOn) fSwitchGreenLedOff = LZSTRUE;
		}
		else if (ledDisplayPara_g.greenLedCurCnt == 0)
		{
			/* switch green LED on (later), if necessary */
			if (!fGreenLedOn) fSwitchGreenLedOn = LZSTRUE;
		}

		ledDisplayPara_g.greenLedCurCnt += dwTicksDiff;
		if (ledDisplayPara_g.greenLedCurCnt >= ledDisplayPara_g.greenLedCycTime)
		{
			ledDisplayPara_g.greenLedCurCnt = 0;
		}
	}

	/* now switch - only if necessary, to save system calls */
	if (fSwitchRedLedOn)
	{
		sysCardFailLedOn();
		fRedLedOn = LZSTRUE;
	}
	if (fSwitchRedLedOff)
	{
		sysCardFailLedOff();
		fRedLedOn = LZSFALSE;
	}
	if (fSwitchGreenLedOn)
	{
		sysUserLedOn();
		fGreenLedOn = LZSTRUE;
	}
	if (fSwitchGreenLedOff)
	{
		sysUserLedOff();
		fGreenLedOn = LZSFALSE;
	}

	dwLastTick = dwCurTick;
}

/**********************************************************************/
/* FUNCTION:    LzsSetLedDisplayMode                                  */
/* DESCRIPTION: to set LED's display mode, according to the category  */
/*              of faults                                             */
/* RETURN:      OK,ERROR                                              */
/* CALLED:      LzsErrlogRegisterError, LzsErrlogRegisterException    */
/**********************************************************************/
LZSBYTE LzsSetLedDisplayMode(LZSDWORD dwCategory)
{
	unsigned int index = 0;
	index = ledDisplayOfErrCategoryTable_g[dwCategory];

	if (index < LEDDISPLAYMODENB)
	{
		ledDisplayPara_g.redLedCycTime = ledDisModeTable[index].redLedCycle;
		ledDisplayPara_g.greenLedCycTime = ledDisModeTable[index].greenLedCycle;
		ledDisplayPara_g.redLedCurCnt = 0;
		ledDisplayPara_g.greenLedCurCnt = 0;

		return kLzsSuccess;
	}

	return kLzsGeneralError;
}

#endif /* _LZS_ERROR_LOG_LED_DISPLAY */

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvInitialize                                                 */
/* DESCRIPT: Start the runtime kernel and system                              */
/* CALLED:   main                                                             */
/*----------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE  LZSPUBLIC LzsEnvInitialize (void)
{
	LZSBYTE bRetCode = kLzsSuccess;



	#ifdef _LZS_ERROR_LOG
	if (LzsErrlogInitErrorlog() != kLzsSuccess)
	{

		return kLzsInitErrLogError;
	}
	#endif

	#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
	if (LzsErrlogInitExceptionBuffer() != kLzsSuccess)
	{

		return kLzsInitExceptionBufferError;
	}
	#endif

	LzsEnvMemInitialize();
	#ifdef USE_SHARED_MEMORY
	LzsEnvSharedMemInitialize();
	#endif

	/* check memory initialization */
	if (IECMEMORY == LZSNULL)
	{
		logMsg("Memory initialization failed!\n",0,0,0,0,0,0);
		LzsErrlogRegisterError(kLzsInitialError, kLzsInitMemoryError, 0, 0, 0);
		return kLzsInitMemoryError;
	}
	/* check shared memory initialization */
	#ifdef USE_SHARED_MEMORY
	#ifdef USE_DATA_CONSISTENCY_SHM
	if (pShmBuff_g == LZSNULL || pShmDCBuff_g == LZSNULL)
	#else
	if (pShmBuff_g == LZSNULL)
	#endif
	{
		#ifdef _MASTER_CPU_
		logMsg("Shared memory initialization failed (MASTER)!\n",0,0,0,0,0,0);
		#else
		logMsg("Shared memory initialization failed (SLAVE)!\n",0,0,0,0,0,0);
		#endif

		LzsErrlogRegisterError(kLzsInitialError, kLzsInitSHMError, 0, 0, 0);
		return kLzsInitSHMError;
	}
	#endif
	#ifdef USE_STATION_HWCONFIG
	if (pShmHwBuff_g == LZSNULL)
	{
		#ifdef _MASTER_CPU_
		logMsg("Shared memory initialization failed (MASTER)!\n",0,0,0,0,0,0);
		#else
		logMsg("Shared memory initialization failed (SLAVE)!\n",0,0,0,0,0,0);
		#endif

		LzsErrlogRegisterError(kLzsInitialError, kLzsInitSHMError, 0, 0, 0);
		return kLzsInitSHMError;
	}
	#endif

	/* determine slot number of the board (1 for slot 1, 21 for slot 21) */
	/*其中sysInLong()函数用于从寄存器读出数据，
	其中的参数为寄存器的地址。*/
	/*bSlotNumber_g = (LZSBYTE)(0x1f - ((sysInLong(0xeff08100) >> 24) & 0x1f));*/
	bSlotNumber_g=0;
	/* publish information about this CPU in shared memory */
	#ifdef USE_STATION_HWCONFIG
	pShmHwBuff_g->arrayCPUs[bSlotNumber_g - 1].fIsPresent = LZSTRUE;
	#ifdef _MASTER_CPU_
	pShmHwBuff_g->arrayCPUs[bSlotNumber_g - 1].fIsMaster = LZSTRUE;
	#else
	pShmHwBuff_g->arrayCPUs[bSlotNumber_g - 1].fIsMaster = LZSFALSE;
	#endif
	#endif

	/* set logical slot number for communication proxy */
	#ifdef USE_COMMUNICATION_PROXY
	#ifdef _MASTER_CPU_
	bProxyLogicalSlotNumber_g = 0;
	#else
	bProxyLogicalSlotNumber_g = bSlotNumber_g;
	#endif
	#else
	bProxyLogicalSlotNumber_g = 0;
	#endif /* USE_COMMUNICATION_PROXY */

	/* initialize the breakpoint list*/
	#ifdef _IP_BREAKPOINTS_
	LzsBreakPointInitialize();
	#endif /* _IP_BREAKPOINTS_ */

	/* initialize network */
	if (NetInitialize(NET_COLDSTART, LZSNULL, bProxyLogicalSlotNumber_g) != NET_SUCCESS)
	{
		logMsg("Error on network startup!\n",0,0,0,0,0,0);
		LzsErrlogRegisterError(kLzsInitialError, kLzsInitCommError, 0, 0, 0);
	}
	#ifdef _LZS_SUPPORT_OPC_CONNECT
	NetInitializeOPC(NET_COLDSTART, LZSNULL);
	#endif

	#ifdef _LZS_ERROR_LOG_LED_DISPLAY
	if (bRetCode == kLzsSuccess)
	{
		LzsSetLedDisplayMode(PLCINITOK_LEDCATEGORY);
	}
	#endif

	/* boot system */
	LzsPlcStart(LZSCOLDSTART);
	return bRetCode;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvShutDown                                                      */
/* DESCRIPT: Shut down the whole Run-Time-Kernel and System*/
/* CALLED: */
/*----------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE  LZSPUBLIC LzsEnvShutDown (void)
{
	LZSTRACE0("\n-> LZS: LzsShutDown:");

	/* de-initialize RTS */
	LzsPlcStop();

	/* shutdown network */
	NetShutDown (NET_SHUTDOWN, bProxyLogicalSlotNumber_g);

	#ifdef _LZS_SUPPORT_OPC_CONNECT
	NetShutDownOPC(NET_SHUTDOWN);
	#endif

	/* free IEC memory */
	free(IECMEMORY);

	return kLzsSuccess;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvResetSystem                                                */
/* DESCRIPT: Reset the System                                                 */
/* CALLED: LzsPlcExecPSCmd when SKS send RESET                                */
/*----------------------------------------------------------------------------*/
LZSPUBLIC32 void  LZSPUBLIC LzsEnvResetSystem (LZSBYTE bRestartMode_p)
{
	#ifdef _IP_BREAKPOINTS_
    if (0 < wBreakPointNum_g)
    {
        LzsBreakPointRemoveAll(LZSNULL);
        if (pCurrentProgramData_g->TaskData.m_Status & kIpExecBrkCmd)
        {
            LzsBreakPointCtrlGo(LZSNULL, LZSTRUE);
        }
    }
	#endif

	#ifdef _FORCE_VARIABLES_
    LzsForceInitForceTab();
	#endif

    LzsStop(); /* first stop the program*/
    /*
        here we have to delete the persistent IEC programm.
        This may be done by deleting the file by using
    */

    /*_unlink(pszStorageName_p);*/

    /*
        or init the flash memory
    */

    /*LzsEnvInitFlash(); */

    /* wait for program stopped */
    /*while (!(LzsSysStatus_l & LZSSTAT_ACCPT_DOWNLOAD)); */

    /*remove program from memory */
    /*LzsTdtDelTaskDefSeg();*/

	/* Send new State to Programming environment */
    LzsSysUpdateMode();
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsRestartNetAndSetNeterror                                      */
/* DESCRIPT: see lzscom.h                                                     */
/*----------------------------------------------------------------------------*/
void LzsRestartNetAndSetNetError (LZSBYTE bConnectionId_p, LZSBYTE bNetStat_p)
{
    LZSTRACE0("\n-> LZS: LzsRestartNetAndSetNetError... ");

    /*--------------------------------------------------------------------------*/
    /* [SYSTEC 26.06.2003 -rs]: Set status <LZSSTAT_NETERROR> only at real      */
    /*                          network error, but then also register error code*/
    /*--------------------------------------------------------------------------*/
    if (bNetStat_p != NET_RESTART_COMM)
    {
        #ifndef _LZS_SUPPORT_OPC_CONNECT
        LzsSysSetStatus (LZSSTAT_NETERROR, LZSSET);
        #else
        /* set net-error only for this connection */
        LzsSysSetNetError(bConnectionId_p);
        #endif

        /*LzsErrlogRegisterError(kLzsInternalError, kLzsNetErrorLastSession, 0, 0, 0);*/
        /*LzsInfRegisterError(bConnectionId_p, kLzsNetErrorLastSession);*/
    }

    #ifdef _LZS_SUPPORT_OPC_CONNECT
    if(bConnectionId_p > 0)
    {
        LZSTRACE0("\n-> LZS: NetShutDownOPC(NET_ERROR_DOWN) / NetInitializeOPC(NET_ERROR_INIT)... ");
        NetShutDownOPC (NET_ERROR_DOWN);
        NetInitializeOPC (NET_ERROR_INIT, LZSNULL);
    }
    else
    {
    #endif
        LZSTRACE0("\n-> LZS: NetShutDown(NET_ERROR_DOWN) / NetInitialize(NET_ERROR_INIT)... ");
        NetShutDown(NET_ERROR_DOWN, bProxyLogicalSlotNumber_g);
        NetInitialize(NET_ERROR_INIT, LZSNULL, bProxyLogicalSlotNumber_g);
    #ifdef _LZS_SUPPORT_OPC_CONNECT
    }
    #endif

    LzsCsvUnlockCmdReceipt(bConnectionId_p);
    LzsCsvEnableCmdReceipt(bConnectionId_p);
}

/*----------------------------------------------------------------------------*/
/*  FUNCTION: LzsEnvDisableAllOutputs                                         */
/*    DESCRIPT: Called by LZS when a breakpoint is reached or for other         */
/*            disturbing reasons                                              */
/*              It should implement code to disable the outputs of the plc.     */
/*  CALLED:                                                                     */
/*----------------------------------------------------------------------------*/
void LzsEnvDisableAllOutputs(LZSWORD wMode)
{

    switch(wMode){
        case LZS_DISABLE_OUTPUTS_HWSTOP:        /*RUN/STOP switch to stop*/
        case LZS_DISABLE_OUTPUTS_SWSTOP:        /*TUI -> STOP*/
        case LZS_DISABLE_OUTPUTS_ERRORSTOP:        /*execution error STOP*/
            /*memset(pProcImgSeg_l,0,wProcImgSegSize_l);*/ /* not necessary to clear process image */
            break;

        case LZS_DISABLE_OUTPUTS_BREAKSTOP:        /*breakpoint reached*/
            break;

        default:
            break;
    }
}

/*----------------------------------------------------------------------------*/
/*  FUNCTION: LzsEnvOEMCommand                                                */
/*    DESCRIPT: OEM Command from SKS                                            */
/*  CALLED:      LzsPlcExecPSCmd when the SKS send the command kLzsCmdOEMSendCmd */
/*----------------------------------------------------------------------------*/
LZSBYTE LzsEnvOEMCommand(LZSBYTE bConnectionId_p, LZSINT iCmd_p,		/* [i] number of the OEM defined command */
                    LZSDWORD dwValue_p        /* [i] a 4 Byte Value for the command    */
                    )
{
    switch ( iCmd_p )
    {
    /* TODO: Implement your own OEM Commands */

    default:
        /* Undefined OEM Command */
        break;
    }

    return kLzsSuccess;
}

/********************************************************************/
/* FUNCTION        : LzsEnvBeginDwlResource                            */
/* DESCRIPTION    : here you can initialize something before a resource*/
/*                  is downloaded                                        */
/* RETURN        : void                                                 */
/* CALLED        :                                                   */
/********************************************************************/
void LzsEnvBeginDwlResource(void)
{
    /* #error *** INSERT YOUR CODE HERE *** */
    return;
}

/********************************************************************/
/* FUNCTION        : LzsEnvInitFlash                            */
/* DESCRIPTION    : here you can initialize flash memory before a complete resource*/
/*                  is downloaded                                        */
/* RETURN        : void                                                 */
/* CALLED        :                                                   */
/********************************************************************/
void LzsEnvInitFlash(void)
{
    /* #error *** INSERT YOUR CODE HERE *** */
    return;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvStartCmd                                                   */
/* DESCRIPT: here you can implement something before a special command is     */
/*           executed                                                         */
/* CALLED:   before Login/Logout/Reset                                        */
/*----------------------------------------------------------------------------*/
void LzsEnvStartCmd(LZSBYTE bCommand_p)
{
    switch (bCommand_p)
    {
        case kLzsCmdLogin:
            break;

        case kLzsCmdLogout:
#ifdef _IP_BREAKPOINTS_
            if (0 < wBreakPointNum_g)
            {
                LzsBreakPointRemoveAll(LZSNULL);
                if (pCurrentProgramData_g->TaskData.m_Status & kIpExecBrkCmd)
                {
                    LzsBreakPointCtrlGo(LZSNULL, LZSTRUE);
                }
            }
#endif

#ifdef _FORCE_VARIABLES_
            /* switch off forcing */
            LzsForceInitForceTab();
#endif
            break;

        case kLzsCmdReset:
            break;

        default:
            break;
    }
}

#ifdef _LZS_DATASEGDESTRUCTOR_
/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvPreFreeDataSegment                                          */
/* DESCRIPT: data segment destruction notification                              */
/* CALLED: before freeing a data segment and before reseting a data segment   */
/*            on cold or warm start.                                              */
/*----------------------------------------------------------------------------*/
void LzsEnvPreFreeDataSegment(LZSWORD wPgmIndex_p, tPlcSegNr nSegNr_p, LZSCONST tSegHeader *pSegHdr_p, LZSCONST tPlcMemPtr pSeg_p)
{
    ;
}
#endif


#ifndef _LZS_8BITBYTES_
/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvSizeSegment                                                                                             */
/* DESCRIPT: If 1 Byte == 16/32 Bit, store one Word/DWord in one Byte                  */
/* CALLED: LzsEnvMoveSegment                                                                                                  */
/* RETURN: error flag                                                                                                                  */
/*----------------------------------------------------------------------------*/
LZSBYTE LzsEnvSizeSegment( LZSDWORD  * dSegSize_p,  /*[i/o]:size of the segment*/
                           tPlcMemPtr *ppSeg_p )    /*[i/o]:pointer to the segmentpointer; has to be set to new one*/
{
    int i,j;
    tPlcMemPtr pNewMem = LZSNULL;
    LZSDWORD   dSegSize = dSegSize_p[0];
    LZSDWORD   dNewSegSize;
    LZSDWORD   oldPos;
    LZSDWORD   newPos;
    LZSBYTE    bRetCode;
#ifdef _LZS_16BITBYTES_
    LZSWORD    wVal;
#else    /* _LZS_32BITBYTES_ */
    LZSDWORD     wVal;
#endif

    /*force to even until compiler is corrected*/
#ifdef _LZS_16BITBYTES_
    if (dSegSize & 0x0001)
    {
        dSegSize++;
    }
#else    /* _LZS_32BITBYTES_ */
  while (dSegSize % 4 != 0)
  {
    dSegSize++;
  }
#endif

    /* set new segment size */
#ifdef _LZS_16BITBYTES_
    dNewSegSize = dSegSize / 2;
#else    /* _LZS_32BITBYTES_ */
    dNewSegSize = dSegSize >> 2;
#endif

    pNewMem=(tPlcMemPtr)LZSMALLOC(dNewSegSize);
    if (LZSNULL == pNewMem)
    {
        /* not enough memory */
        LzsSysSetStatus(LZSSTAT_PLCERROR, LZSSET);
		LzsErrlogRegisterError(kLzsInternalError, kLzsNoMem, 0, 0, 0);
        bRetCode = kLzsNoMem;
        goto Exit;
    }

#ifdef _LZS_16BITBYTES_
  for ( i=0,j=0 ; i< dSegSize; i+=2,j++)
#else    /* _LZS_32BITBYTES_ */
  for ( i=0,j=0 ; i< dSegSize; i+=4,j++)
#endif
  {
#ifdef _LZS_16BITBYTES_
      wVal=LzsNetAbsGetWord((*ppSeg_p)+i);
      *((LZSWORD *)(pNewMem+j)) = wVal;
#else    /* _LZS_32BITBYTES_ */
      wVal=LzsNetAbsGetDword((*ppSeg_p)+i);
      *((LZSDWORD *)(pNewMem+j)) = wVal;


#endif
  }
  *((LZSWORD *)pNewMem) = dSegSize;

    LZSFREE(*ppSeg_p);

    *ppSeg_p    = (tPlcMemPtr)pNewMem;
    bRetCode    = kLzsSuccess;
    *dSegSize_p = dNewSegSize;

Exit:

    return bRetCode;
}
#endif /* ifndef _LZS_8BITBYTES_ */


/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvMoveSegment                                                */
/* DESCRIPT: Move a segment to another place in memory and change the pointer */
/*           to the segment                                                   */
/* CALLED:   when downloading segments and before registering in seg table    */
/*----------------------------------------------------------------------------*/
LZSBYTE LzsEnvMoveSegment(LZSBYTE bSegType_p, /* [i]: type of segment; see odk_plc.h */
                          LZSDWORD dwSegSize_p, /*[i]  :size of the segment*/
                          tPlcMemPtr* ppSeg_p /* [i/o]: pointer to the segmentpointer; has to be set to new one */
                         )
{
    tSegHeader SegHdrInf; /* Struktur f黵 Segmentheader */
    tPlcMemPtr pNew;
    LZSWORD wRealSize;
    tPlcSegType bSegType;
    tPlcMemPtr dwAddress;
    LZSBYTE bRetCode;

	/*#ifndef _LZS_NO_PERSISTENCE_
	if (LzsSysGetStatus(LZSSTAT_RECOVERING)
	#ifdef _LZS_DIRECT_BYREF_
	   && !(bSegType_p == kPlcSegByRefInfo)
	#endif
	   )
	{
		return kLzsSuccess;
	}
	#endif */

    #ifndef _LZS_8BITBYTES_
    /* resizing of segment */
    /* for other segment types look in odk_plc.h*/
    switch (bSegType_p)
    {
        case kPlcSegCode:
        case kPlcSegData:
        case kPlcSegInit:
        case kPlcSegNativeCode:
        case kPlcSegHardwareConfig:
			/* resize segment if called during the download;
			   if called from LzsRestoreSystem, the seg. is already resized */
			if (!LzsSysGetStatus(LZSSTAT_RECOVERING))
			{
			    bRetCode = LzsEnvSizeSegment(&dwSegSize_p, ppSeg_p);
			    if (kLzsSuccess != bRetCode)
			    {
			        goto Exit;
			    }
			}
            break;

        default:
            break;
    }
	#endif

    /* moving of segment */
    switch (bSegType_p)
    {
        #ifdef _LZS_PERSISTENCE_MIXED_
        case kPlcSegData:
            /* example implementation: */
            /* move data segment to flash memory */

            /* pointer to flash must be correctly aligned */
            /*
            #ifdef _LZS_DSALIGNMENT_2_
            if ((int)pFlash & 0x0001) pFlash++;
            #else
                #ifdef _LZS_DSALIGNMENT_4_
                while(((LZSDWORD)pFlash % 4) != 0) pFlash++;
                #endif
            #endif
            MemCopy(pFlash, *ppSeg_p, dwSegSize_p);
            FREE(*ppSeg_p );
            *ppSeg_p = pFlash;
            pFlash += dwSegSize_p;
            */
	        break;
        #endif

        case kPlcSegCode:
        case kPlcSegInit:
        case kPlcSegNativeCode:
        case kPlcSegHardwareConfig:
        case kPlcSegSource:
        case kPlcSegSource2:
            break;

		case kPlcSegData:
			/*pNew = LZSMALLOC_FAST(dwSegSize_p);
			if (pNew != LZSNULL)
			{
				memcpy(pNew, *ppSeg_p, dwSegSize_p);
				LZSFREE(*ppSeg_p);
				*ppSeg_p = pNew;
			}
			else
			{
				LzsErrlogRegisterError(kLzsInternalError, kLzsNoMem, 0, 0, 0);
				return kLzsNoMem;
			}*/
            break;

        case kPlcSegOemSeg:
			/* we got an OEM Segment have to treat here*/
			LzsMemGetSegHeader (*ppSeg_p, &SegHdrInf);

			/* the segment looks as follows:
			 * 6 Byte Header
			 * 1 Word real size of the segment that should be created
			 * 1 Word segment type
			 * 1 DWORD the address where the segment should be (if not allocated here)
			 */
			wRealSize = LzsMemAbsGetWord(*ppSeg_p+SegHdrInf.m_HeaderSize);

			bSegType =LzsMemAbsGetByte(*ppSeg_p+SegHdrInf.m_HeaderSize+LZS_SIZEOF_WORD);
			dwAddress =(tPlcMemPtr)LzsMemAbsGetDword(*ppSeg_p+SegHdrInf.m_HeaderSize+LZS_SIZEOF_WORD+LZS_SIZEOF_WORD);

			/* if we do not allocate here
			 * we use
			 * pNew = dwAddress
			 */
			pNew = LZSMALLOC(wRealSize);

			/* it is necessary to set the segment header correct
			 * to be handeled in the runtime system
			 */
			SegHdrInf.m_SegSize = wRealSize;
			SegHdrInf.m_SegType = bSegType;
			LzsMemSetSegHeader(pNew,&SegHdrInf);

			/* we free the downloaded segment to save memory */
			LZSFREE(*ppSeg_p);

			*ppSeg_p = pNew;
            break;

#ifdef _LZS_DIRECT_BYREF_
        case kPlcSegByRefInfo:
                wByrefInfoSegment_g = 1;
            break;
#endif

        default:
            break;
    }

    bRetCode = kLzsSuccess;

#ifndef _LZS_8BITBYTES_
Exit:
#endif

    return bRetCode;
}



/********************************************************************/
/* FUNCTION        : LzsEnvSchedule                                    */
/* DESCRIPTION    : this function will be called from communication   */
/*                    part of the runtime system to allow scheduleing */
/* RETURN        : void                                                */
/* CALLED        :                                                   */
/********************************************************************/
void LzsEnvSchedule()
{
    /* allow the OS to run some other tasks */
    /* the time other tasks are allowed to interrupt the runtime system*/
    /* may be very critical and depends on the environment */
    return;
}

#ifdef _LZS_OEMVERSINFO_
/********************************************************************/
/* FUNCTION        : LzsEnvGetOemVersion                                */
/* DESCRIPTION    : this function will be called from                 */
/*                LzsInfGetPlcVersion to get OEM Version info       */
/* RETURN        : void                                                */
/* CALLED        :                                                   */
/********************************************************************/
#define OEMMAJORVER 0
#define OEMMINORVER 0
#define OEMREVISVER 0
#define OEMBUILDVER 0
void LzsEnvGetOemVersion(tOemVersion * sOemVersion_p)
{
    /* Put your Version information here Major.Minor.Revision.Build */
    /* This will be diplayed in the PLC Version dilog of OpenPCS    */
    sOemVersion_p->wOemVerMajor        = OEMMAJORVER;
    sOemVersion_p->wOemVerMinor        = OEMMINORVER;
    sOemVersion_p->wOemVerRevision     = OEMREVISVER;
    sOemVersion_p->wOemVerBuild        = OEMBUILDVER;
    return;
}
#endif


/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetOemLzsErrorString                                          */
/* DESCRIPT: Get OEM-specific error info for tLzsErrorCode                    */
/* CALLED:   LzsInfGetError when no standard error info was found             */
/*----------------------------------------------------------------------------*/
tLzsErrTabEntry LZSCONST*  LzsEnvGetOemLzsError (LZSBYTE bLzsErrorCode_p)
{
    return LZSNULL;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetOEMCap                                                  */
/* DESCRIPT: Get OEM-specific 32Bit capabilities                              */
/* CALLED:   LzsInfoEvalCapabilities                                          */
/*----------------------------------------------------------------------------*/
void LzsEnvGetOEMCap(LZSDWORD *pdwOEMCapInfo)
{
    *pdwOEMCapInfo = 0;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetOemLzsErrorString                                       */
/* DESCRIPT: Get OEM-specific error info for tIecErrorCode                    */
/* CALLED:   LzsInfGetError when no standard error info was found             */
/*----------------------------------------------------------------------------*/
tLzsErrTabEntry LZSCONST*  LzsEnvGetOemFbError (LZSBYTE bFbErrorCode_p)
{
    return LZSNULL;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetWatchdogTimeout                                         */
/* DESCRIPTION: This function will be called to get the watchdog timeout      */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
LZSDWORD LzsEnvGetWatchdogTimeout(void)
{
    /* watchdog timeout depends on T0 setting */
	LZSDWORD dwTimeoutDesired_us = pTaskConfig_g->dwT0Interval * 150 / 100; /* dwT0Interval is in microseconds; add a 50% reserve to not activate the watchdog without a reason */

    /* minimum timeout on this platform is 1 ms (in case of system clock rate 1000/s)! */
    /* but it seems that when the timeout is set to <n>, the system might trigger the watchdog within a time span of between <n - 1> and <n> ticks, so we add 2 here to avoid too early timeouts */
	return (dwTimeoutDesired_us / 1000 + 2);
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetRegisters                                               */
/* DESCRIPTION: This function will be called to get CPU register contents     */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
void LzsEnvGetRegisters(LZSDWORD* pArrayRegs, void* pExceptionInfo)
{
#if 0
	LZSWORD i;
	ESFPPC* pEsf = (ESFPPC*)pExceptionInfo;

	if (pArrayRegs != LZSNULL)
	{
		/* initialize array of register values */
		for (i = 0; i < NUM_REGS_EXCEPTIONBUFFER; i++)
		{
			pArrayRegs[i] = 0;
		}

		/* get and set register values */
		if (pEsf != LZSNULL)
		{
			pArrayRegs[0] = pEsf->regSet.gpr[0]; /* R0 */
			pArrayRegs[1] = pEsf->regSet.gpr[1]; /* R1 */
			pArrayRegs[2] = pEsf->regSet.gpr[2]; /* R2 */
			pArrayRegs[3] = pEsf->regSet.gpr[3]; /* R3 */
			pArrayRegs[4] = pEsf->regSet.gpr[4]; /* R4 */
			pArrayRegs[5] = pEsf->regSet.gpr[5]; /* R5 */
			pArrayRegs[6] = pEsf->regSet.gpr[6]; /* R6 */
			pArrayRegs[7] = pEsf->regSet.gpr[7]; /* R7 */
			pArrayRegs[8] = pEsf->regSet.gpr[8]; /* R8 */
			pArrayRegs[9] = pEsf->regSet.gpr[9]; /* R9 */
			pArrayRegs[10] = pEsf->regSet.gpr[10]; /* R10 */
			pArrayRegs[11] = pEsf->regSet.gpr[11]; /* R11 */
			pArrayRegs[12] = pEsf->regSet.gpr[12]; /* R12 */
			pArrayRegs[13] = pEsf->regSet.gpr[13]; /* R13 */
			pArrayRegs[14] = pEsf->regSet.gpr[14]; /* R14 */
			pArrayRegs[15] = pEsf->regSet.gpr[15]; /* R15 */
			pArrayRegs[16] = pEsf->regSet.gpr[16]; /* R16 */
			pArrayRegs[17] = pEsf->regSet.gpr[17]; /* R17 */
			pArrayRegs[18] = pEsf->regSet.gpr[18]; /* R18 */
			pArrayRegs[19] = pEsf->regSet.gpr[19]; /* R19 */
			pArrayRegs[20] = pEsf->regSet.gpr[20]; /* R20 */
			pArrayRegs[21] = pEsf->regSet.gpr[21]; /* R21 */
			pArrayRegs[22] = pEsf->regSet.gpr[22]; /* R22 */
			pArrayRegs[23] = pEsf->regSet.gpr[23]; /* R23 */
			pArrayRegs[24] = pEsf->regSet.gpr[24]; /* R24 */
			pArrayRegs[25] = pEsf->regSet.gpr[25]; /* R25 */
			pArrayRegs[26] = pEsf->regSet.gpr[26]; /* R26 */
			pArrayRegs[27] = pEsf->regSet.gpr[27]; /* R27 */
			pArrayRegs[28] = pEsf->regSet.gpr[28]; /* R28 */
			pArrayRegs[29] = pEsf->regSet.gpr[29]; /* R29 */
			pArrayRegs[30] = pEsf->regSet.gpr[30]; /* R30 */
			pArrayRegs[31] = pEsf->regSet.gpr[31]; /* R31 */

			pArrayRegs[32] = pEsf->regSet.msr; /* machine state register */
			pArrayRegs[33] = pEsf->regSet.lr; /* link register */
			pArrayRegs[34] = pEsf->regSet.ctr; /* count register */
			pArrayRegs[35] = pEsf->regSet.pc; /* program counter */
			pArrayRegs[36] = pEsf->regSet.cr; /* condition register */
			pArrayRegs[37] = pEsf->regSet.xer; /* fixed-point exception register */;
			pArrayRegs[38] = pEsf->regSet.pgTblPtr; /* base of page table */
			pArrayRegs[39] = pEsf->regSet.scSrTblPtr; /* SR regs array ptr - kernel protection map */
			pArrayRegs[40] = pEsf->regSet.srTblPtr; /* SR regs array ptr - user protection map */
		}

		/* VME bus registers */
		pArrayRegs[41] = sysInLong(univBaseAdrs + 0x408); /* MISC_STAT */
		pArrayRegs[42] = sysInLong(univBaseAdrs + 0xf88); /* V_AMERR */
		pArrayRegs[43] = sysInLong(univBaseAdrs + 0xf8c); /* VAERR */
		pArrayRegs[44] = sysInLong(univBaseAdrs + 0x4); /* PCI_CSR */
		pArrayRegs[45] = sysInLong(univBaseAdrs + 0x18c); /* L_CMDERR */
		pArrayRegs[46] = sysInLong(univBaseAdrs + 0x190); /* LAERR */
	}
#endif
}

/*************************************************************************/
/* FUNCTION      : LzsEnvCommunicationInterrupted                        */
/* DESCRIPTION   : this function will be called from communication       */
/*                    part of the runtime system,                        */
/*                    when Status Looged in but no command is received   */
/*                    -> communication broken                            */
/* RETURN        : void                                                  */
/* CALLED        :                                                       */
/*************************************************************************/
void LzsEnvCommunicationInterrupted(LZSBYTE bConnectionId_p, LZSDWORD dElapsedTime_p)
{
    /* stop system, disable outputs or whatever */
    if (dElapsedTime_p > 15000)
    {
        #ifdef _LZS_SUPPORT_OPC_CONNECT
        if(bConnectionId_p == LZS_CON_ID_PROGSYS)
        {
        #endif

            #ifdef _IP_BREAKPOINTS_
            if (0 < wBreakPointNum_g)
            {
                LzsBreakPointRemoveAll(LZSNULL);
                if (pCurrentProgramData_g->TaskData.m_Status & kIpExecBrkCmd)
                {
                    LzsBreakPointCtrlGo(LZSNULL, LZSTRUE);
                }
            }
            #endif

			#ifdef _FORCE_VARIABLES_
            LzsForceInitForceTab();
			#endif

        #ifdef _LZS_SUPPORT_OPC_CONNECT
        }
        #endif

        #ifndef _LZS_SUPPORT_OPC_CONNECT
        LzsSysSetStatus(LZSSTAT_LOGIN,LZSCLR); /* remove login state*/
        #else
        LzsSysClearLogin(bConnectionId_p);
        #endif

        /* restart network */
        LzsRestartNetAndSetNetError(bConnectionId_p, NET_ERROR);

    }
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvActivateBkgTask                                              */
/* DESCRIPT: Here you may insert some background process which is called with */
/*             each Cycle                                                          */
/* CALLED:      LzsIpRunCycle                                                       */
/*----------------------------------------------------------------------------*/
void  LzsEnvActivateBkgTask (void)
{
    /* TODO: Here you may insert some background process which is called with each Cycle */
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvHardwareRun                                                  */
/* DESCRIPT: returns the mode which is used when the hardware switch is set   */
/*           to RUN                                                           */
/* CALLED:   LzsCtlRunStopSwitch()                                            */
/*----------------------------------------------------------------------------*/
LZSBYTE LzsEnvHardwareRun()
{

    /*#error *** SELECT one MODE here ****/

    /*return kLzsCtrWarmStart; */
    /*return kLzsCtrHotStart; */
    return kLzsCtrColdStart;
}




/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvRegisterSysState                                           */
/* DESCRIPT: Here you may react to the Run-Time-Kernel Status                 */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
LZSBYTE  LzsEnvRegisterSysState (LZSBYTE bConnectionId_p, LZSBYTE bSysState_p)
{
    LZSBYTE bRetCode = kLzsSuccess;

    LZSTRACE0("\n-> LZS: LzsEnvRegisterSysState ");

    switch (bSysState_p)
    {
        case kLzsStateLogin:
        case kLzsStateLogout:
        case kLzsStateReset:
        {
            LZSTRACE0("(kLzsStateLogin/kLzsStateLogout/kLzsStateReset) ");
            break;
        }

		case kLzsStateColdStart:
        case kLzsStateWarmStart:
        case kLzsStateHotStart:
        {
            LZSTRACE0("(kLzsStateColdStart/kLzsStateWarmStart/kLzsStateHotStart) ");

			#ifdef _LZS_ERROR_LOG_LED_DISPLAY
			LzsSetLedDisplayMode(PLCRUNOK_LEDCATEGORY);
			#endif

            break;
        }

        case kLzsStateSingleCycle:
        {
            LZSTRACE0("(kLzsStateSingleCycle) ");
			break;
        }

        case kLzsStateHardStopReq:
        case kLzsStateSoftStopReq:
        {
            LZSTRACE0("(kLzsStateHardStopReq/kLzsStateSoftStopReq) ");

			#ifdef _LZS_ERROR_LOG_LED_DISPLAY
			LzsSetLedDisplayMode(PLCSTOP_LEDCATEGORY);
			#endif

            break;
        }

        case kLzsStateHardStopped:
        case kLzsStateSoftStopped:
        {
            LZSTRACE0("(kLzsStateHardStopped/kLzsStateSoftStopped) ");
            break;
        }

        case kLzsStateDwlPrepare:
        {
            LZSTRACE0("(kLzsStateDwlPrepare) ");
			break;
        }

        case kLzsStateDwlLastSeg:
        {
			LZSTRACE0("(kLzsStateDwlLastSeg) ");

			#ifndef _LZS_NO_PERSISTENCE_
			/* send lock-time for saving persistency data */
			/* communication will pause for the specified time */
			LzsCsvSendLockTime(LZS_CON_ID_PROGSYS, 0);
            #endif

            break;
        }

        case kLzsStateDwlComplete:
        {
            LZSTRACE0("(kLzsStateDwlComplete) ");
            break;
        }

        case kLzsStateDwlFinished:
        {
            LZSTRACE0("(kLzsStateDwlFinished) ");
            break;
        }

        case kLzsStateOnlChangePrepare:
        {
            LZSTRACE0("(kLzsStateOnlChangePrepare) ");
            break;
        }

        case kLzsStateOnlChangeComplete:
        {
            LZSTRACE0("(kLzsStateOnlChangeComplete) ");
            break;
        }

        case kLzsStateStartupTaskFinished:
        {
            LZSTRACE0("(kLzsStateStartupTaskFinished) ");
            break;
        }

        default:
        {
            LZSTRACE0("(default) ");
            break;
        }
    }

    LzsInfRegisterError(bConnectionId_p, bRetCode);

    return (bRetCode);
}

/********************************************************************/
/* FUNCTION        : LzsEnvSysSetStatus                                 */
/* DESCRIPTION    : this function will be called from LzsSysSetStatust*/
/*                status flags as described in lzsdefs.h and        */
/*                    LZSSET                                          */
/*                    LZSCLR                                            */
/* RETURN        : void                                              */
/********************************************************************/
void LzsEnvSysSetStatus(LZSWORD StatusFlag_p, LZSBYTE SetClr_p)
{
    switch (StatusFlag_p)
	{
		default:
			return;
	}
}

/*#############################################################################*/
/*            Download Rawfile UNIT                                            */
/*                                                                             */
/*    The following functions will be called from OpenPCS programming system   */
/*    to download a "non-IEC61131-3" file via OpenPCS                          */
/*    In P0699, used for downloading firmware files (image of OS + SmartPLC)   */
/*#############################################################################*/

#ifdef _LZS_DWL_RAWFILE_

/********************************************************************/
/* FUNCTION:    LzsEnvDwlRawFile                                    */
/* DESCRIPTION: this function will be called from LzsPlcExecPSCmd   */
/*              to start the download of a file via OpenPCS         */
/* RETURN:      LZSBYTE                                             */
/********************************************************************/
LZSBYTE LzsEnvDwlRawFile(tLzsPSCmd LZSFAR* pLzsPSCmd_p)
{
    /* expected format of command:
                                +0        +4        +0(min)-128(max)
   +---------------+-----------+-----------+----------+
   | CmdDwlRawFile | ParamSize |  FileSize | FileName |
   +---------------+-----------+-----------+----------+
   */

	LZSDWORD		dwFileSize;                   /* Size of file to be downloaded */
	LZSBYTE			bRetCode;                   /* ErrorCode of function */
	/* ULARGE_INTEGER	i64FreeBytesToCaller; */

	/* check the state of LZS */
	/* download of raw file is only possible if LZS is in login and stop mode */
	/* programming system logged in? */
	#ifndef _LZS_SUPPORT_OPC_CONNECT
	if (!LzsSysGetStatus(LZSSTAT_LOGIN))
	#else
	if (!LzsSysCheckLogin(LZS_CON_ID_PROGSYS))
	#endif
    {
		LzsErrlogRegisterError(kLzsInternalError, kLzsModeErr, 0, 0, 0);
		bRetCode = kLzsModeErr;
		goto Exit;
	}

	/* system in stop mode? */
	if (LzsSysGetStatus(LZSSTAT_RUNNING))
    {
		LzsErrlogRegisterError(kLzsInternalError, kLzsNotValidInRunState, 0, 0, 0);
		bRetCode = kLzsNotValidInRunState;
		goto Exit;
	}

	dwFileSize = LzsMemAbsGetDword(pLzsPSCmd_p->m_pParamLst);

	/* create the file */
	RawFileTemp = open(sFilenameTemp, O_CREAT | O_RDWR, 0644);

	if (RawFileTemp == ERROR /*NULL*/)
	{
		logMsg("Error opening temporary firmware file: %s (error %d)\n",sFilenameTemp,errno,0,0,0,0);
		LzsErrlogRegisterError(kLzsInternalError, kLzsInvalidFilePath, 0, 0, 0);
		bRetCode = kLzsInvalidFilePath;
		goto Exit;
	}
	/* receipt received command */
	pLzsPSCmd_p->m_fSendRec = LZSTRUE;

	bRetCode = kLzsSuccess;

	Exit:

	return bRetCode;
}

/*********************************************************************/
/* FUNCTION:    LzsEnvDwlRawFileSegment                              */
/* DESCRIPTION: this function will be called from LzsPlcExecPSCmd    */
/*              to download one segment of a (raw) file via OpenPCS  */
/* RETURN:      LZSBYTE                                              */
/*********************************************************************/
LZSBYTE LzsEnvDwlRawFileSegment(tLzsPSCmd LZSFAR* pLzsPSCmd_p, LZSBOOL fLastSegment)
{
    /* expected format of command:
                                      +0               +2              +2
   +----------------------+-----------+----------------+---------------+
   | CmdDwlRawFileSegment | ParamSize | RawFileSegSize | RawFileSegNum |
   +----------------------+-----------+----------------+---------------+
   */

	LZSBYTE			bRetCode;				   /* ErrorCode of function */
	tPlcSegNr		nSegNum;                   /* number of raw file segment */
	tPlcSegSize		wSegSize;                  /* size of segment to be downloaded */
	tPlcMemPtr		pBuffer;

	wSegSize = LzsMemAbsGetWord(pLzsPSCmd_p->m_pParamLst+0);
	nSegNum  = LzsMemAbsGetWord(pLzsPSCmd_p->m_pParamLst+2);

	LZSTRACE2("--------------------[RawFileSegNum=%u, Size=%u]... ", nSegNum, wSegSize);

	LZSTRACE0("\n-> LZS: LzsDwlRawFileSegment [NetRecData(NET_DATA)] ");

	if (0 == wSegSize)
	{
		wSegSize = 1;	/* if segment size is 0, a single dummy byte is send (since 0 bytes cannot be sent via TCPIP driver) */
	}

	/* create temporary buffer for the raw file segment */
	pBuffer = (tPlcMemPtr) (LZSMALLOC (wSegSize));

	if (pBuffer == LZSNULL)
    {
		/* not enough memory to process the segment */
		/* LzsSysSetStatus(LZSSTAT_PLCERROR, LZSSET); */
		LzsErrlogRegisterError(kLzsInternalError, kLzsNoMem, 0, 0, 0);
		bRetCode = kLzsNoMem;
		goto Exit;
    }

	NetRecData ((LZSBYTE LZSFAR*)pBuffer, wSegSize, NET_DATA, NET_RxTIMEOUT, bProxyLogicalSlotNumber_g);

	/* deposit internal command incl. parameter */
	pLzsPSCmd_p->m_bCommand    = kLzsCmdContDwlRawFileSegment;

	/* set flag "last segment" */
	pLzsPSCmd_p->m_wParamSize += sizeof(LZSBYTE);
	*(LZSBYTE LZSFAR *)(pLzsPSCmd_p->m_pParamLst+4)=fLastSegment;
	pLzsPSCmd_p->m_wParamSize  += sizeof(pBuffer)/ LZS_SIZEOF_BYTE;

	/* copy the buffer-pointer into the param list */
    MemCopy ((LZSBYTE LZSFAR*)(pLzsPSCmd_p->m_pParamLst+5), (LZSBYTE LZSFAR*)(&pBuffer), sizeof(LZSBYTE LZSFAR*)/ LZS_SIZEOF_BYTE);

	LzsCsvPresetCmd (LZS_CON_ID_PROGSYS, pLzsPSCmd_p, kLzsEnableExtrnComm);

	bRetCode = kLzsSuccess;

	Exit:

	if(kLzsSuccess != bRetCode)
	{
		/* close and delete the file */
		LzsEnvCloseRawFile();
		LzsEnvDeleteRawFile(sFilenameTemp);
	}

	return bRetCode;
}

/*********************************************************************/
/* FUNCTION:    LzsEnvSetFileTimeOfRawFile                           */
/* DESCRIPTION: this function will be called from LzsPlcExecPSCmd    */
/*              to set the file time of a (raw) file after the       */
/*              last segment of the raw file has been downloaded     */
/* RETURN:      LZSBYTE                                              */
/*********************************************************************/
LZSBYTE LzsEnvSetFileTimeOfRawFile(tLzsPSCmd LZSFAR* pLzsPSCmd_p)
{
    /* expected format of command: (internal command)
                                       +0          +2        +2        Low  +4  High  +4   Low  +4 High  +4
   +--------------------------+-----------+-----------+---------+--------+---------+---------+--------+
   | CmdDwlRawFileLastSegment | ParamSize |  SegSize  | SegNum  | CreationFiletime | ModifiedFiletime |
   +--------------------------+-----------+-----------+---------+--------+---------+---------+--------+
   */

	return kLzsSuccess;
}

/****************************************************************************/
/* FUNCTION:    LzsEnvDwlContRawFileSegment                                 */
/* DESCRIPTION: this function will be called from LzsPlcExecPSCmd           */
/*              it waits for the raw file data to be received               */
/* RETURN:      LZSBYTE                                                     */
/****************************************************************************/
LZSBYTE LzsEnvDwlContRawFileSegment(tLzsPSCmd LZSFAR* pLzsPSCmd_p)
{
    /* expected format of command:
                                       +0          +2        +2                  +1            +4
   +--------------------------+-----------+-----------+---------+---------------+-----------+
   | CmdDwlContRawFileSegment | ParamSize |  SegSize  | SegNum  | IsLastSegment | pBuffer   |
   +--------------------------+-----------+-----------+---------+---------------+-----------+
   */

	tPlcMemPtr		pBuffer;                       /* general segmentpointer */
	LZSBYTE			bNetStat;                   /* Networkstatus */
	LZSBYTE			bRetCode;                   /* ErrorCode of function */
	tPlcSegNr		nSegNum;                    /* Segmentnumber */
	tPlcSegSize		wSegSize;                  /* size of segment to be downloaded */
	LZSBOOL			fLastSegment;

	LZSTRACE0("\n-> LZS: LzsDwlContRawFileSegment ... ");

	bRetCode = kLzsSuccess;

	wSegSize = LzsMemAbsGetWord(pLzsPSCmd_p->m_pParamLst+0);
	nSegNum  = LzsMemAbsGetWord(pLzsPSCmd_p->m_pParamLst+2);

	fLastSegment = *(LZSBYTE LZSFAR*)(pLzsPSCmd_p->m_pParamLst+4);
	MemCopy((LZSBYTE LZSFAR*)(&pBuffer), (LZSBYTE LZSFAR*)(pLzsPSCmd_p->m_pParamLst+5), sizeof(LZSBYTE LZSFAR*)/LZS_SIZEOF_BYTE);

	bNetStat = NetGetRxStatus(bProxyLogicalSlotNumber_g);

	switch (bNetStat)
    {
        /* received segment completely */
        case NET_SUCCESS:
			/* write to file */
			write(RawFileTemp, pBuffer, wSegSize);

	        /* free the allocated buffer */
	        if (LZSNULL != pBuffer)
            {
		        LZSFREE(pBuffer);
            }

	        if (LZSTRUE == fLastSegment)
	        {
		        LzsEnvCloseRawFile();

				/* delete old firmware backup file */
				if (0 != remove(sFilenameBackup))
				{
					logMsg("Error removing firmware backup file: %s (error %d)\n",sFilenameBackup,errno,0,0,0,0);
				}
				else
				{
					logMsg("Firmware backup file removed: %s\n",sFilenameBackup,0,0,0,0,0);
				}

				/* rename existing firmware file */
				if (0 != rename(sFilename, sFilenameBackup))
				{
					logMsg("Error renaming firmware file: %s; backup file name: %s (error %d)\n",sFilename,sFilenameBackup,errno,0,0,0);
				}
				else
				{
					logMsg("Existing firmware file renamed to: %s\n",sFilenameBackup,0,0,0,0,0);
				}

				/* rename new firmware file */
				if (0 != rename(sFilenameTemp, sFilename))
				{
					logMsg("Error renaming new firmware file: %s; file name: %s (error %d)\n",sFilenameTemp,sFilename,errno,0,0,0);
				}
				else
				{
					logMsg("New firmware file stored as: %s\n",sFilename,0,0,0,0,0);
				}
	        }

            /* receipt received segment */
		    pLzsPSCmd_p->m_fSendRec = LZSTRUE;

			break;

        /* no data available */
        case NET_NODATA:
            /* don't receipt command */
            pLzsPSCmd_p->m_fSendRec = LZSFALSE;

            /* no data received, but also no timeout */
            /* so wait */
            LZSTRACE0(" (waiting for raw file segment) ");

			LzsCsvPresetCmd (LZS_CON_ID_PROGSYS, pLzsPSCmd_p, kLzsEnableExtrnComm);

			break;

        /* TimeOut or network error */
        default:
            /*LZSTRACE0(" (*** TimeOut/Network Error ***) ");*/

            /* Call parameter <NET_ERROR> newly inserted */
            /* LzsRestartNetAndSetNetError (NET_ERROR); */

			LzsErrlogRegisterError(kLzsInternalError, kLzsNetError, 0, 0, 0);
			bRetCode = kLzsNetError;

			/* close file handle */
			LzsEnvCloseRawFile();

			/* delete the file */
			LzsEnvDeleteRawFile(sFilenameTemp);

			/* free the allocated buffer */
	        if(LZSNULL != pBuffer)
            {
		        LZSFREE(pBuffer);
            }

			break;
    }

	/* The return code will be returned as receipt to the IDE by <LzsRunExecPSCmd>  */

	return  bRetCode;
}

/****************************************************************************/
/* FUNCTION:    LzsEnvCloseRawFile                                          */
/* DESCRIPTION: closes the destination file of the downloaded raw file      */
/* RETURN:      LZSBYTE                                                     */
/****************************************************************************/
LZSBYTE LzsEnvCloseRawFile()
{
	close(RawFileTemp);
	return kLzsSuccess;
}

/****************************************************************************/
/* FUNCTION:    LzsEnvDeleteRawFile                                         */
/* DESCRIPTION: deletes the destination file of the downloaded raw file     */
/* RETURN:      LZSBYTE                                                     */
/****************************************************************************/
LZSBYTE LzsEnvDeleteRawFile(LZSCONST LZSCHAR* pszRawFilePath)
{
	LZSBYTE bRetCode;

	if (0 == remove(pszRawFilePath))
	{
		bRetCode = kLzsError;
	}
	else
	{
		bRetCode = kLzsSuccess;
	}

	return bRetCode;
}

/****************************************************************************/
/* FUNCTION:    LzsEnvGetRawFileInfo                                        */
/* DESCRIPTION: this function will be called from LzsPlcExecPSCmd           */
/*              it retrieves the file info from an existing raw file        */
/* RETURN:      LZSBYTE                                                     */
/****************************************************************************/
LZSBYTE LzsEnvGetRawFileInfo(tLzsPSCmd LZSFAR* pLzsPSCmd_p)
{
    /* expected format of command:
                                       +0          +1(min)-128(max)
   +--------------------+-----------+------------+
   | CmdGetRawFileInfo  | ParamSize |  Filename  |
   +--------------------+-----------+------------+
   */

    /* receipt to IDE:

     LZSBYTE        LZSWORD        LZSBYTE        LZSDWORD          LOW-LZSDWORD   HIGH-LZSDWORD
   +-----------+-------------+------------------+-----------+--------------+--------------+
   | bRetCode  | ExtDataSize |  kLzsRawFileInf  | FileSize  |         LastChangedTime     |
   +-----------+-------------+------------------+-----------+--------------+--------------+

    In the case of an error (i.e. file size two big for a DWORD),
    FileSize 0 will be returned.
    */

    return kLzsSuccess;
}

#endif /* _LZS_DWL_RAWFILE_ */

/***************************************************************************/
/* FUNCTION     : LzsEnvRebootPlc                                          */
/* DESCRIPTION  : sends the PLC the reboot command                         */
/* RETURN       : LZSBYTE                                                  */
/***************************************************************************/

LZSBYTE LzsEnvRebootPlc()
{
	LZSBYTE bRetCode = kLzsSuccess;

	/* check the state of LZS */
	/* reboot is only possible if LZS is in login and stop mode */
	/* programming system logged in? */
	#ifndef _LZS_SUPPORT_OPC_CONNECT
	if (!LzsSysGetStatus(LZSSTAT_LOGIN))
	#else
	if (!LzsSysCheckLogin(LZS_CON_ID_PROGSYS))
	#endif
    {
		LzsErrlogRegisterError(kLzsInternalError, kLzsModeErr, 0, 0, 0);
		bRetCode = kLzsModeErr;
		goto Exit;
	}

	/* system in stop mode? */
	if (LzsSysGetStatus(LZSSTAT_RUNNING))
    {
		LzsErrlogRegisterError(kLzsInternalError, kLzsNotValidInRunState, 0, 0, 0);
		bRetCode = kLzsNotValidInRunState;
		goto Exit;
	}

	reboot(0 /*BOOT_COLD*/);

Exit:
	return bRetCode;
}

/********************************************************************/
/* FUNCTION:    LzsEnvCheckSingleSegment                            */
/* DESCRIPTION: this function will be called after a single segment */
/*              has been downloaded                                 */
/* RETURN:      LZSBYTE                                             */
/* CALLED:      from LzsDwlSingleSegmentCont                        */
/********************************************************************/
LZSBYTE LzsEnvCheckSingleSegment(tPlcMemPtr pSingleSegment_p)
{
    tSegHeader SegHdrInf;                 /* Struct for segment header */
    LZSBYTE rc = kLzsSuccess;

    LzsMemGetSegHeader (pSingleSegment_p, &SegHdrInf);
    if (kPlcSegHardwareConfig == SegHdrInf.m_SegType)
    {
        rc = LzsEnvCheckConfiguration(pSingleSegment_p);

        /* you may set an error condition here or simply return */
        /* if no error is set the new segment won't be exchanged */
        if (kLzsSuccess != rc )
        {
            LzsSysSetStatus (LZSSTAT_PLCERROR, LZSSET);
            LzsDsvSignalEvent (LZS_CON_ID_PROGSYS, LzsIpErrCallback, bLzsIpEventHandle_l);
        }
    }
    else
    {
        rc = kLzsSuccess;
    }

    return rc;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvCheckConfiguration                                         */
/* DESCRIPT: here you can check your configuration if the hardware            */
/*           configurator has tunneld a segment for configuration information */
/* CALLED:   LzsRestoreSystem -> LzsCheckConfiguration                        */
/* RETURN:   kLzsSuccess if configuration is ok                               */
/*           kLzsConfigError if not                                           */
/*----------------------------------------------------------------------------*/
LZSBYTE LzsEnvCheckConfiguration(tPlcMemPtr pConfigSegment_p)
{
    LZSBYTE rc = kLzsConfigError;

    if (LZSNULL == pConfigSegment_p)
    {
        /* if there is no configuration segment we have to return ok */
        rc = kLzsSuccess;
    }
    else
    {
		rc = kLzsSuccess;
		/*rc=kLzsConfigError;*/
    }

    /* for checking the extended version info call LzsGetOemVersion */
    /* for an example, please see sample Win32IPC */
    return rc;
}




/*###########################################################################*/
/*           PROCESS IMAGE MANAGEMENT                                        */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*  The process image is the segment where the runtime system reads and      */
/*  writes variables declared as %I, %Q or %M (input / output / maker )      */
/*  The structure of this segment is as follows:                             */
/*  +------------+                                                           */
/*  | Header     |  6 byte                                                   */
/*  |   :        |                                                           */
/*  |   :        |                                                           */
/*  |   :        |                                                           */
/*  |   :        |                                                           */
/*  |   :        |                                                           */
/*  +------------+                                                           */
/*  | Input      |  i.e.: 16 bit input = 2 byte                              */
/*  |   :        |                                                           */
/*  +------------+                                                           */
/*  | Output     |  i.e.: 8 bit input = 1 byte                               */
/*  +------------+                                                           */
/*  | Marker     |  i.e.: 64 bit  = 8 byte                                   */
/*  |   :        |                                                           */
/*  |   :        |                                                           */
/*  |   :        |                                                           */
/*  |   :        |                                                           */
/*  |   :        |                                                           */
/*  |   :        |                                                           */
/*  |   :        |                                                           */
/*  +------------+                                                           */
/*############################################################################*/


/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvInitProcImg                                                */
/* DESCRIPT: here you have to add code to initialize physical I/Os            */
/*           This function is called by the runtime system after a download   */
/*           is done and all segments were initialisized.                     */
/*----------------------------------------------------------------------------*/
LZSBYTE  LzsEnvInitProcImg (tPlcMemPtr pProcImgSeg_p, /* [i] pointer to beginning of process image without header */
                            LZSWORD wSegSize_p           /* [i] size of the segment -Header Size*/
                        )
{
	#ifdef ENABLE_PERFORMANCE_MONITORING
    LZSWORD i = 0;
    tPerformanceData* pData;
    #endif

	/* P0699-specific: process image is only used for performance monitoring! */
	/* performance monitoring is enabled by defining ENABLE_PERFORMANCE_MONITORING in config.h */

	/* clear memory */
	memset(pProcImgSeg_p, 0, wSegSize_p);

	#ifdef ENABLE_PERFORMANCE_MONITORING
    /* set default values for performance monitoring */
    while (i < (wSegSize_p - 8)) /* at the end of the process image (marker section), there are 8 bytes reserved for CPU load measurements! */
    {
		pData = (tPerformanceData*)(pProcImgSeg_p + i);
		pData->executionTimeMin = 3.402823E38; /* FLT_MAX */
		i += sizeof(tPerformanceData);
    }
	#endif

    return (kLzsSuccess);
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvReadProcImg                                                */
/* DESCRIPT: This function is called by the runtime system at the beginning   */
/*           of every IpCycle.                                                */
/*           here you have to read input from your hardware and write         */
/*           it into the process image pointed to by pProcImgSeg_p            */
/*----------------------------------------------------------------------------*/
extern unsigned int T6NCounter;
union t
{
	char ch[4];
	unsigned int uiT;
}tTemp;
LZSBYTE  LzsEnvReadProcImg (tPlcMemPtr pProcImgSeg_p, /* [i] pointer to beginning of process image without header */
                            LZSWORD wSegSize_p           /* [i] size of the segment */
                        )
{
    /* TODO: Here the Processimage is exchanged with the physical I/O */

    return (kLzsSuccess);
}



/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvWriteProcImg                                               */
/* DESCRIPT: This function is called by the runtime system at the end         */
/*           of every IpCycle.                                                */
/*           here you have to read the process image and write it             */
/*           it to outputs                                                    */
/*----------------------------------------------------------------------------*/
LZSBYTE  LzsEnvWriteProcImg (tPlcMemPtr pProcImgSeg_p, /* [i] pointer to beginning of process image without header */
                            LZSWORD wSegSize_p            /* [i] size of the segment */
                        )
{
    /* TODO: Here the Processimage is exchanged with the physical I/O */
	logMsg("Enter LzsEnvWriteProcImg\n",0,0,0,0,0,0);
	if(*(pProcImgSeg_p+8)==1)
		logMsg("Output I0.0 is true!\n",0,0,0,0,0,0);
	else
		logMsg("Output I0.0 is true!\n",0,0,0,0,0,0);
    return (kLzsSuccess);
}


/*#############################################################################*/
/*            PERSISTENCE UNIT                                                 */
/*                                                                             */
/*    The following functions are for saving and restoring the IEC program     */
/*    This may be a Harddisk, a Flashram or something like that where it can   */
/*    be loaded from after power on                                            */
/*#############################################################################*/

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetStorageName()                                           */
/* DESCRIPT: returns a name to the storage, i.e. the filename                 */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
LZSCONST LZSCHAR * LzsEnvGetStorageName()
{
    LZSSTATIC char *szName = IECProgram;
    return (const char*)szName;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvClearData                                                  */
/* DESCRIPT:  erase data from  persistence                                    */
/* RETURN:   LZSTRUE: success, LZSFALSE: error                                */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvClearData(LZSCONST LZSCHAR * pszStorageName_p)
{
    unlink(pszStorageName_p);

    return LZSTRUE;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvSaveOpen                                                   */
/* DESCRIPT: Add your code here to initialize persistence for saving          */
/*           i.e. fopen for persistence on a file with write mode             */
/* RETURN:   LZSTRUE: success, LZSFALSE: error                                */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvSaveOpen(LZSCONST LZSCHAR * pszStorageName_p,    /*[i] optional name of the storage*/
                    LZSDWORD length            /*[i] optional length of data that shoul be stored*/
                    )
{
	/* reset byte counter */
    dwByteCounter = 0;

	/* open/create persistency file */
	iecProgFd = open(pszStorageName_p, O_CREAT | O_RDWR, 0644);

	if (iecProgFd == ERROR)
	{
		LZSTRACE0("Persistency: SaveOpen failed!\n");
		return LZSFALSE;
	}
	else
	{
		LZSTRACE0("Persistency: SaveOpen success.\n");
	}

	return LZSTRUE;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvRestoreOpen                                                */
/* DESCRIPT: Add your code here to initialize persistence for restore         */
/*           i.e. fopen for persistence on a file with read mode              */
/* RETURN:   LZSTRUE: success, LZSFALSE: error                                */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvRestoreOpen(LZSCONST LZSCHAR * pszStorageName_p /*[i] optional name of the storage*/
                        )
{
	/* open persistency file */
	iecProgFd = open(pszStorageName_p, O_RDONLY, 0644);

	if (iecProgFd == ERROR)
	{
		LZSTRACE0("Persistency: RestoreOpen failed!\n");
		return LZSFALSE;
	}
	else
	{
		LZSTRACE0("Persistency: RestoreOpen success.\n");
	}

    return LZSTRUE;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvSaveClose                                                  */
/* DESCRIPT: Add your code here to finish persistence for saving              */
/*           i.e. fopen for persistence on a file with read mode              */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
void LzsEnvSaveClose(void)
{
	/* write out the rest of the data contained in the buffer */
	if (dwByteCounter > 0)
	{
		write(iecProgFd, arrBufferPersistence, dwByteCounter);
	}

	/* close persistency file */
	close(iecProgFd);
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvRestoreClose                                               */
/* DESCRIPT: Add your code here to initialize persistence for restore         */
/*           i.e. fopen for persistence on a file with read mode              */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
void LzsEnvRestoreClose(void)
{
	/* close persistency file */
	close(iecProgFd);
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvSaveByte                                                   */
/* DESCRIPT: add your code here to store one byte                             */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
void LzsEnvSaveByte(LZSBYTE b)
{
	/* add new byte to the buffer */
	arrBufferPersistence[dwByteCounter] = b;

	/* increment byte counter */
	dwByteCounter++;

	/* if buffer is full, write out the data to the file system */
	if (dwByteCounter >= PERSISTENCY_BUFFER_SIZE)
	{
		write(iecProgFd, arrBufferPersistence, PERSISTENCY_BUFFER_SIZE);

		/* reset byte counter */
		dwByteCounter = 0;
	}
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvRestoreByte                                                */
/* DESCRIPT: add your code here to restore one byte                           */
/* RETURN:   returns the byte                                                 */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
LZSBYTE LzsEnvRestoreByte(void)
{
 	LZSBYTE b;

	/* read one byte from the persistency file */
	read(iecProgFd, &b, sizeof(b));

    return b;
}

#ifndef _LZS_NO_PERSISTENCE_
#ifdef _LZS_SAVESYSTEMCMD_

LZSSTATIC LZSBYTE bSaveSystemCmdResult_s = kLzsSuccess;	/* result of SaveSystemCmd */
LZSSTATIC LZSBYTE bRestoreSystemCmdResult_s = kLzsSuccess;	/* result of RestoreSystemCmd */

LZSPUBLIC32 LZSBOOL LZSPUBLIC LzsEnvGetActivateSaveSystem(void)
{
	return fActivateSaveSystem_g;
}

LZSPUBLIC32 LZSBOOL LZSPUBLIC LzsEnvGetActivateRestoreSystem(void)
{
	return fActivateRestoreSystem_g;
}

LZSPUBLIC32 void LZSPUBLIC LzsEnvResetActivateSaveSystem(void)
{
	fActivateSaveSystem_g = LZSFALSE;
}

LZSPUBLIC32 void LZSPUBLIC LzsEnvResetActivateRestoreSystem(void)
{
	fActivateRestoreSystem_g = LZSFALSE;
}

LZSWORD LzsEnvSaveSystemCmdCallback(LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p)
{
	LZSWORD wSize;
	LZSBYTE bResult = 0xFF;

	/* determine needed size in the communication buffer */
    wSize = 2 * LZS_SIZEOF_BYTE;

	/* check remaining buffer size against needed size */
	if (wSize > wBuffSize_p)
	{
		/* communication buffer is too small */
		return LZSINVALIDVALUE;
	}

	/* set progress value (0..99 during execution of save system, 100 when finished successfully, 0xFF on error) */
	if (dwCurrentSegCount_g == 0xFFFFFFFF)
	{
		if (bSaveSystemCmdResult_s == kLzsSuccess)
		{
			bResult = 100; /* finished successfully */
		}
		else
		{
			bResult = 0xFF; /* error */
		}
	}
	else
	{
		bResult = dwCurrentSegCount_g * 100 / dwPersistenceSegCount_g; /* percentage */
		if (bResult >= 100)
		{
			bResult = 99;
		}
	}

	LzsMemAbsSetByte(pBuff_p++, kLzsSaveSystemCmdFinished);
	LzsMemAbsSetByte(pBuff_p, bResult);

	return wSize;
}

LZSWORD LzsEnvRestoreSystemCmdCallback(LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p)
{
	LZSWORD wSize;
	LZSBYTE bResult = 0xFF;

	/* determine needed size in the communication buffer */
    wSize = 2 * LZS_SIZEOF_BYTE;

	/* check remaining buffer size against needed size */
	if (wSize > wBuffSize_p)
	{
		/* communication buffer is too small */
		return LZSINVALIDVALUE;
	}

	/* set progress value (0..99 during execution of restore system, 100 when finished successfully, 0xFF on error) */
	if (dwCurrentSegCount_g == 0xFFFFFFFF)
	{
		if (bRestoreSystemCmdResult_s == kLzsSuccess)
		{
			bResult = 100; /* finished successfully */
		}
		else
		{
			bResult = 0xFF; /* error */
		}
	}
	else
	{
		bResult = dwCurrentSegCount_g * 100 / dwPersistenceSegCount_g; /* percentage */
		if (bResult >= 100)
		{
			bResult = 99;
		}
	}

	LzsMemAbsSetByte(pBuff_p++, kLzsRestoreSystemCmdFinished);
	LzsMemAbsSetByte(pBuff_p, bResult);

	return wSize;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION:    LzsEnvSaveSystemCmd                                           */
/* DESCRIPTION: programming system requests that current resource             */
/*              is saved to persistant storage                                */
/* RETURN:      tLzsErrorCode error code                                      */
/*----------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsEnvSaveSystemCmd(void)
{
	/* do save system */
	bSaveSystemCmdResult_s = LzsSaveSystem(LzsEnvGetStorageName());
	dwCurrentSegCount_g = 0xFFFFFFFF;

	LzsDsvSignalEvent(LZS_CON_ID_PROGSYS, LzsEnvSaveSystemCmdCallback, bSaveSystemCmdEventHandle_g);

	return bSaveSystemCmdResult_s;	/* result of command execution */
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvRestoreSystemCmd                                           */
/* DESCRIPTION: programming system requests that the current resource         */
/*              is restored from persistent storage                           */
/* RETURN: tLzsErrorCode error code                                           */
/*----------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsEnvRestoreSystemCmd(void)
{
	/* do restore system */
	bRestoreSystemCmdResult_s = LzsRestoreSystem(LzsEnvGetStorageName());
	dwCurrentSegCount_g = 0xFFFFFFFF;

	LzsDsvSignalEvent(LZS_CON_ID_PROGSYS, LzsEnvRestoreSystemCmdCallback, bRestoreSystemCmdEventHandle_g);

	return bRestoreSystemCmdResult_s;	/* result of command execution */
}
#endif /* _LZS_SAVESYSTEMCMD_ */
#endif



/*#############################################################################*/
/*            RETAIN UNIT                                                      */
/*                                                                             */
/*    The following functions are for saving and restoring retain variables    */
/*    from the IEC program to a persistent storage (i.e. a file on the hard    */
/*    disk, battery-buffered RAM, ...)                                         */
/*#############################################################################*/

#ifdef _LZS_RETAIN_

#ifdef _LZS_NO_PERSISTENCE_
#error *** _LZS_RETAIN_ defined without any type of persistence being activated! ***
#endif

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvEnableRetain                                               */
/* DESCRIPT: add your code here to define how often retain data is written;   */
/*           this function is called at the end of each cycle of each task;   */
/*           (if you always return LZSTRUE here, retain data is written       */
/*            after every task cycle)                                         */
/* RETURN:     LZSTRUE or LZSFALSE                                              */
/* CALLED:   LzsIpRunTaskOnce()                                               */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvEnableRetain(void)
{
    /* TODO: add your code to define how often retain data is written */
    #error *** INSERT YOUR CODE HERE ***

    return LZSTRUE;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvWriteRetain                                                */
/* DESCRIPT: add your code here to save retain data                           */
/* RETURN:     LZSTRUE or LZSFALSE                                              */
/* CALLED:   LzsIpRunTaskOnce()                                               */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvWriteRetain(void)
{
    if (pRetainData_g == LZSNULL || dwRetainDataSize_g == 0)
    {
        return LZSFALSE;
    }

    LZSTRACE0("\n*****LzsEnvWriteRetain*****\n");

    /* TODO: write data */
    #error *** INSERT YOUR CODE HERE ***

    LZSTRACE0("write retain OK\n");
    return LZSTRUE;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvReadRetain                                                 */
/* DESCRIPT: add your code here to restore retain data                        */
/* RETURN:     LZSTRUE or LZSFALSE                                              */
/* CALLED:   main function                                                    */
/*----------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBOOL LZSPUBLIC LzsEnvReadRetain(void)
{
    LZSTRACE0("\n*****LzsEnvReadRetain*****\n");

    /* TODO: read data */
    #error *** INSERT YOUR CODE HERE ***

    /* restore the retain data into the data segments */
/*    LzsMemRestoreRetainData([pointer], [size]);*/

    LZSTRACE0("read retain OK\n");
    return LZSTRUE;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetRetainStorageName                                       */
/* DESCRIPT: returns a name to the storage, i.e. the filename                 */
/* CALLED:   LzsEnvWriteRetain(), LzsEnvReadRetain()                          */
/*----------------------------------------------------------------------------*/
LZSCONST LZSCHAR* LzsEnvGetRetainStorageName(LZSBYTE bParam)
{
    /* TODO: return storage name */
    #error *** INSERT YOUR CODE HERE ***

    return "";
}
#endif /* _LZS_RETAIN_ */



/*#############################################################################*/
/*            DYNAMIC RETAIN UNIT                                              */
/*                                                                             */
/*    The following functions are for saving and restoring retain variables    */
/*    from the IEC program to a persistent storage (i.e. a file on the hard    */
/*    disk, battery-buffered RAM, ...)                                         */
/*    Differences to the normal retain functions are:                          */
/*    - It works on individual variables, not by declared variables of a type  */
/*    - Variables are retained only on user request when setting values online */
/*#############################################################################*/
#ifdef _LZS_DYNAMIC_RETAIN_

#ifdef _LZS_NO_PERSISTENCE_
#error *** _LZS_DYNAMIC_RETAIN_ defined without any type of persistence being activated! ***
#endif

LZSSTATIC void LzsEnvSaveWord(LZSWORD w)
{
	LZSBYTE b1 = (LZSBYTE)(w & 0x00FF);
	LZSBYTE b2 = (LZSBYTE)((w >> 8) & 0x00FF);

	LzsEnvSaveByte(b1);
	LzsEnvSaveByte(b2);
}

LZSSTATIC LZSWORD LzsEnvRestoreWord(void)
{
	LZSBYTE b1 = LzsEnvRestoreByte();
	LZSBYTE b2 = LzsEnvRestoreByte();

	LZSWORD w = (LZSWORD)(b1 | (b2 << 8));

	return w;
}

LZSSTATIC void LzsEnvSaveDword(LZSDWORD d)
{
	LZSBYTE b1 = (LZSBYTE)(d & 0x000000FF);
	LZSBYTE b2 = (LZSBYTE)((d >> 8) & 0x000000FF);
	LZSBYTE b3 = (LZSBYTE)((d >> 16) & 0x000000FF);
	LZSBYTE b4 = (LZSBYTE)((d >> 24) & 0x000000FF);

	LzsEnvSaveByte(b1);
	LzsEnvSaveByte(b2);
	LzsEnvSaveByte(b3);
	LzsEnvSaveByte(b4);
}

LZSSTATIC LZSDWORD LzsEnvRestoreDword(void)
{
    LZSBYTE b1 = LzsEnvRestoreByte();
    LZSBYTE b2 = LzsEnvRestoreByte();
    LZSBYTE b3 = LzsEnvRestoreByte();
    LZSBYTE b4 = LzsEnvRestoreByte();

    LZSDWORD d = (LZSDWORD)b1;
    d |= ((LZSDWORD)b2) << 8;
    d |= ((LZSDWORD)b3) << 16;
    d |= ((LZSDWORD)b4) << 24;

    return d;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvSaveDynamicRetain                                          */
/* DESCRIPT: add your code here to save dynamic retain data                   */
/* RETURN:   LZSTRUE or LZSFALSE                                              */
/* CALLED:   LzsSetVariable()                                                 */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvSaveDynamicRetain(void)
{
	/* format of the data: */
	/* LZSDWORD resource version (for compatibility check) */
	/* LZSWORD number of entries */
	/* { <n> entries, each with: */
	/*   LZSWORD program number */
	/*   LZSWORD segment number */
	/*   LZSWORD offset number */
	/*   LZSWORD data size */
	/*   <m> bytes of data */
	/* } */

    LZSWORD i;
    LZSWORD k;
	tLzsRetainTableEntry* pCurrentEntry;
    tPlcTaskDefTable LZSFAR* pTaskDefTab = LzsTdtGetAddr();

	if (pDRTable_g == LZSNULL)
	{
		return LZSFALSE;
	}

    if (pTaskDefTab == LZSNULL)
    {
        return LZSFALSE;
    }

    if (wDRTableEntries_g == 0)
    {
        return LZSTRUE;
    }

	/* reset byte counter */
    dwByteCounter = 0;

	/* open/create persistency file */
	iecProgFd = open(LzsEnvGetDynamicRetainStorageName(), O_CREAT | O_RDWR, 0644);

	if (iecProgFd == ERROR)
	{
		LZSTRACE0("Dynamic retain: open file for save failed!\n");
		return LZSFALSE;
	}
	else
	{
		LZSTRACE0("Dynamic retain: open file for save success.\n");
	}

	/* --- WRITE DATA --- */

	/* write resource version (from application) */
	LzsEnvSaveDword(pTaskDefTab->m_PlcVer.m_TimeStamp);

	/* write number of entries */
	LzsEnvSaveWord(wDRTableEntries_g);

	/* go through the table */
	for (i = 0; i < wDRTableEntries_g; i++)
	{
		pCurrentEntry = pDRTable_g + i;

		/* write program number, segment number, offset number, data size (from table entry) */
		LzsEnvSaveWord(pCurrentEntry->m_wTaskNr);
		LzsEnvSaveWord(pCurrentEntry->m_wSegNr);
		LzsEnvSaveWord(pCurrentEntry->m_wOffset);
		LzsEnvSaveWord(pCurrentEntry->m_wSize);

		/* write data */
		for (k = 0; k < pCurrentEntry->m_wSize; k++)
		{
			LzsEnvSaveByte(*(pCurrentEntry->m_pData + k));
		}
	}

	/* --- END --- */

	/* write out the rest of the data contained in the buffer */
	if (dwByteCounter > 0)
	{
		write(iecProgFd, arrBufferPersistence, dwByteCounter);
	}

	/* close persistency file */
	close(iecProgFd);

    return LZSTRUE;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvLoadDynamicRetain                                          */
/* DESCRIPT: add your code here to restore dynamic retain data                */
/* RETURN:   LZSTRUE or LZSFALSE                                              */
/* CALLED:   main function                                                    */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvLoadDynamicRetain(void)
{
	/* format of the data: see LzsEnvSaveDynamicRetain */

	LZSWORD i;
	LZSWORD k;
	LZSWORD wDRTableEntries;
	tLzsRetainTableEntry currentEntry;
    tPlcTaskDefTable LZSFAR* pTaskDefTab = LzsTdtGetAddr();

    if (pTaskDefTab == LZSNULL)
    {
        return LZSFALSE;
    }

	/* open persistency file */
	iecProgFd = open(LzsEnvGetDynamicRetainStorageName(), O_RDONLY, 0644);

	if (iecProgFd == ERROR)
	{
		printf("Dynamic retain: open file for restore failed!\n");
		return LZSFALSE;
	}
	else
	{
		printf("Dynamic retain: open file for restore success.\n");
	}

	/* --- READ DATA --- */

	/* read resource version (from persistent dynamic retain data) */
	dwDRResVersion_g = LzsEnvRestoreDword();

	/* check if the resource version matches the application */
	if (dwDRResVersion_g != pTaskDefTab->m_PlcVer.m_TimeStamp)
	{
		close(iecProgFd);
		printf("Dynamic retain: File version mismatch!\n");
		LzsMemResetDynamicRetain();
		return FALSE;
	}

	/* read number of entries */
	wDRTableEntries = LzsEnvRestoreWord();

	/* go through the table */
	for (i = 0; i < wDRTableEntries; i++)
	{
		/* read program number, segment number, offset number, data size (from table entry in persistent storage) */
		currentEntry.m_wTaskNr = LzsEnvRestoreWord();
		currentEntry.m_wSegNr = LzsEnvRestoreWord();
		currentEntry.m_wOffset = LzsEnvRestoreWord();
		currentEntry.m_wSize = LzsEnvRestoreWord();

		/* allocate memory and read data */
		currentEntry.m_pData = LZSMALLOC(currentEntry.m_wSize);
		if (currentEntry.m_pData != LZSNULL)
		{
			for (k = 0; k < currentEntry.m_wSize; k++)
			{
				*(currentEntry.m_pData + k) = LzsEnvRestoreByte();
			}

			/* add to internal data structures */
			LzsMemAddDynamicRetainData(&currentEntry);

			/* free memory */
			LZSFREE(currentEntry.m_pData);
			currentEntry.m_pData = LZSNULL;
		}
		else
		{
			/* no memory, report error */
			LzsErrlogRegisterError(kLzsInternalError, kLzsNoMem, 0, 0, 0);
			LzsMemResetDynamicRetain();
			return LZSFALSE;
		}
	}

	/* --- END --- */

	/* close persistency file */
	close(iecProgFd);

    return LZSTRUE;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetDynamicRetainStorageName                                */
/* DESCRIPT: returns a name to the storage, i.e. the filename                 */
/* CALLED:   LzsEnvSaveDynamicRetain(), LzsEnvLoadDynamicRetain()             */
/*----------------------------------------------------------------------------*/
LZSCONST LZSCHAR* LzsEnvGetDynamicRetainStorageName()
{
    LZSSTATIC char *szName = DRDataFile;
    return (const char*)szName;
}
#endif /* _LZS_DYNAMIC_RETAIN_ */



/*#############################################################################*/
/*              TIME BASE                                                      */
/*                                                                             */
/*    the following function has to provide a time base for the runtime system */
/*    the values should have a resolution of 1 ms                              */
/*#############################################################################*/

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetTickCount                                               */
/* DESCRIPT: returns a LZSDWORD value of system time in ms                    */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
LZSDWORD LzsEnvGetTickCount(void)
{
    return G_dwTickCount; /* THIS IS ONLY CORRECT IF THE SYSTEM CLOCK IS SET TO 1000 TICKS PER SECOND */
    /*return (tickGet() * 1000 / sysClkRateGet());*/ /* THIS SHOULD WORK INDEPENDENT OF THE SYSTEM CLOCK SETTING (BUT ULONG IS ONLY 4 BYTES => BIGGER DATA TYPE NECESSARY FOR INTERMEDIATE RESULT!) */
	/*return getClockTicks() / 33333;*/ /* this uses the PowerPC time base registers; the update frequency seems to be 33 MHz */
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetPerformanceTickCount                                    */
/* DESCRIPT: returns a LZSDWORD value of a high performance counter           */
/* CALLED: performance monitoring                                             */
/*----------------------------------------------------------------------------*/
LZSDWORD LzsEnvGetPerformanceTickCount(void)
{
	unsigned long long tb;
	unsigned long tbl, tbu0, tbu1;

	do
	{
		__asm__ ("mftbu %0" : "=r" (tbu0));
		__asm__ ("mftb %0" : "=r" (tbl));
		__asm__ ("mftbu %0" : "=r" (tbu1));
	}
	while (tbu0 != tbu1);

	tb = tbu1;
	tb <<= 32;
	tb += tbl;

	return tbl; /* only the lower 32 bit (tbl) are used here - tb would be a 64 bit value */
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetPerformanceDiffTime                                     */
/* DESCRIPT: returns a positive time difference between two tick count values */
/*           from the high performance counter, in microseconds (us)          */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
float LzsEnvGetPerformanceDiffTime(LZSDWORD tick1, LZSDWORD tick2)
{
	if (tick2 < tick1)
	{
		/* overflow */
		return ((float)(0xFFFFFFFF - tick1 + tick2) * 0.03F);
	}

	return ((float)(tick2 - tick1) * 0.03F);
}

#ifdef ENABLE_PERFORMANCE_MONITORING
/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvStartPerformanceMeasurement                                */
/* DESCRIPT: starts a performance measurement for the specified data set      */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
void LzsEnvStartPerformanceMeasurement(tPerformanceData* pPerformanceData)
{
	pPerformanceData->dwStartTick = LzsEnvGetPerformanceTickCount();
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvStopPerformanceMeasurement                                 */
/* DESCRIPT: finishes a performance measurement for the specified data set    */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
void LzsEnvStopPerformanceMeasurement(tPerformanceData* pPerformanceData)
{
	float time = LzsEnvGetPerformanceDiffTime(pPerformanceData->dwStartTick, LzsEnvGetPerformanceTickCount());

	if (pPerformanceData->dwNumSamples > 0) /* skip calculation of min/max for the first sample in this set, because often the first cycle is much slower than following cycles */
	{
		if (time < pPerformanceData->executionTimeMin) pPerformanceData->executionTimeMin = time;
		if (time > pPerformanceData->executionTimeMax) pPerformanceData->executionTimeMax = time;
	}

	pPerformanceData->executionTimeLast = time;
	pPerformanceData->executionTimeSum += time;
	pPerformanceData->dwNumSamples++;
}
#endif

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvGetSysTime                                                 */
/* DESCRIPT: returns a system date value and a system time value              */
/* CALLED:   e.g. for error log timestamps                                    */
/*----------------------------------------------------------------------------*/
void LzsEnvGetSysTime(LZSDWORD* p_dwDate, LZSDWORD* p_dwTimeOfDay)
{
	/* if the platform has a realtime clock, this function must set: */
	/* - in p_dwDate: days since 1.1.0001 */
    /* - in p_dwTimeOfDay: milliseconds since 0:00 within 24 h */

	/* if the platform has no realtime clock, this function must set: */
	/* - in p_dwDate: 0x00000000 */
    /* - in p_dwTimeOfDay: current tick count (=> uptime of the PLC) */

	*p_dwDate = 0;
	*p_dwTimeOfDay = LzsEnvGetTickCount();
}



/*#############################################################################*/
/*             MEMORY MANAGEMENT                                               */
/*                                                                             */
/*    the following functions should provide memory management                 */
/*    there have to be two functions similar to the standard C functions       */
/*    malloc and free                                                          */
/*                                                                             */
/*    if you have no malloc on your system or you want to use a fixed area of  */
/*    memory for IEC programs you can use the code provided between the        */
/*    #define _LZS_SIMPLEMALLOC_ #endif blocks below                           */
/*#############################################################################*/

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvMemAlloc                                                   */
/* DESCRIPT: allocates dwMemSize bytes of memory in IECMEMORY (FAST!)         */
/* RETURN:   a pointer to the memory or LZSNULL if there is no memory         */
/*           available or on other errors                                     */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
void LZSFAR*  LzsEnvMemAlloc (LZSDWORD dwMemSize)
{
    void LZSFAR* pReturnMem = LZSNULL;    /* Pointer to usable mem */
    tMemHeader* pHeader = (tMemHeader*)IECMEMORY;
    LZSBOOL fMemFound = LZSFALSE;

    dwMemSize *= LZS_SIZEOF_BYTE;

#ifdef _LZS_DSALIGNMENT_2_
    dwMemSize = (dwMemSize + 0x0000001) & ~0x00000001;    /*force to 2-Byte-Alignment*/
#else
#ifdef _LZS_DSALIGNMENT_4_
    dwMemSize = (dwMemSize + 0x0000003) & ~0x00000003;    /* force to 4-Byte-Alignment */
#endif
#endif

#ifdef _LZS_32BITBYTES_
    dwMemSize = (dwMemSize + 0x0000003) & ~0x00000003;    /* force to 4-Byte-Alignment */
#endif

    while (!fMemFound && (LZSNULL != pHeader))
    {
		/* range check */
	    if (!IsInIecMemory(pHeader))
		{
			LzsErrlogRegisterError(kLzsInternalError, kLzsMemoryCorrupted, 0, 0, 0);
			return LZSNULL;
		}

        if (pHeader->fFree && (dwMemSize < pHeader->dSize))
        {
            pHeader->fFree = LZSFALSE;
            fMemFound = LZSTRUE;
            pReturnMem = ((LZSBYTE LZSFAR *)pHeader) + sizeof(tMemHeader);    /*return mem pointer behind header*/

            if (pHeader->dSize > dwMemSize + sizeof(tMemHeader) + 1)        /*enough room fo another block?*/
            {
                tMemHeader* pNewHeader = (tMemHeader*)((LZSBYTE LZSHUGE*)pReturnMem + dwMemSize);
                pNewHeader->fFree = LZSTRUE;
                pNewHeader->dSize = pHeader->dSize - dwMemSize - sizeof(tMemHeader);
                pNewHeader->pPrev = pHeader;
                pNewHeader->pNext = pHeader->pNext;
                if (pNewHeader->pNext) /*-fg- 20000119*/
                {
                    pNewHeader->pNext->pPrev = pNewHeader;
                }
                pHeader->pNext = pNewHeader;
                pHeader->dSize = dwMemSize;

                dwUsedMem_l += sizeof(tMemHeader);
            }

            dwUsedMem_l += pHeader->dSize;
        }
        else
        {
			/* check - pNext can be LZSNULL if there is no more free memory */
			if (pHeader->pNext != LZSNULL && !IsInIecMemory(pHeader->pNext))
			{
				LzsErrlogRegisterError(kLzsInternalError, kLzsMemoryCorrupted, 0, 0, 0);
				return LZSNULL;
			}

            pHeader = (tMemHeader *)pHeader->pNext;
		}
    }

	/* LZSTRACE2(" [Alloc pReturnMem=%p SIZE=%d]\n ", pReturnMem, dwMemSize);*/
    /* LzsEnvMemTrace(); */

    /*-fg- 20000119 memtest*/
#ifdef LZS_DEBUG_MEM
    MemPointer[iPointerIndex] = pReturnMem;
    iPointerIndex++;
#endif

    return pReturnMem;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvMemFree                                                    */
/* DESCRIPT: frees the memory block pointed to by pMem, previously allocated  */
/*           by LzsEnvMemAlloc or LzsEnvMemAlloc2                             */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
void  LzsEnvMemFree (void LZSFAR* pMem)
{
    LZSDWORD dwFreedSize = 0;
    tMemHeader *pHeader, *pNext, *pPrev;

	LZSBOOL fIsIecMemory = IsInIecMemory(pMem);
	/*LZSBOOL fIsIecMemory2 = IsInIecMemory2(pMem);*/

#ifdef LZS_DEBUG_MEM
    /*-fg- 20000119 memtest*/
    LZSBOOL fPointerOk;
    int i;
    fPointerOk = LZSFALSE;
#endif

	/* only free if non-null pointer */
    if (pMem != LZSNULL)
    {
		/* only free if within valid memory range */
	    if (fIsIecMemory == LZSFALSE /*&& fIsIecMemory2 == LZSFALSE*/)
		{
			return;
		}

#ifdef LZS_DEBUG_MEM        /* B.S. 17.10.00 */
    /*-fg- 20000119 memtest*/
        for (i = 0; i < iPointerIndex; i++)
        {
            if (pMem == MemPointer[i])
			{
                fPointerOk = LZSTRUE;
                MemPointer[i]=LZSNULL;
            }
        }
        if (LZSFALSE == fPointerOk)
        {
            return;
        }
        /*-fg- 20000119 END memtest*/
#endif

        pHeader = (tMemHeader *)(((LZSBYTE LZSFAR *)pMem) - sizeof(tMemHeader));

        /* skip double frees */
        if (pHeader->fFree)
        {
			return;
        }

        dwFreedSize = pHeader->dSize;
        pNext = pHeader->pNext;
        pPrev = pHeader->pPrev;
        pHeader->fFree = LZSTRUE;

		/*if (fIsIecMemory)*/ dwUsedMem_l -= dwFreedSize;
		/*if (fIsIecMemory2) dwUsedMem2_l -= dwFreedSize;*/

        if (pNext)
        {
			if (!IsInIecMemory(pNext) /*&& !IsInIecMemory2(pNext)*/)
			{
				LzsErrlogRegisterError(kLzsInternalError, kLzsMemoryCorrupted, 0, 0, 0);
				return;
			}

            if (pNext->fFree)
            {
				/* concatenate free blocks to one */
                pHeader->dSize += (pNext->dSize + sizeof(tMemHeader));
                pHeader->pNext = pNext->pNext;
                if (pHeader->pNext)
                {
                    pHeader->pNext->pPrev = pHeader;
                }

				/*if (fIsIecMemory)*/ dwUsedMem_l -= sizeof(tMemHeader);
				/*if (fIsIecMemory2) dwUsedMem2_l -= sizeof(tMemHeader);*/
            }
        }

        if (pPrev)
        {
			if (!IsInIecMemory(pPrev) /*&& !IsInIecMemory2(pPrev)*/)
			{
				LzsErrlogRegisterError(kLzsInternalError, kLzsMemoryCorrupted, 0, 0, 0);
				return;
			}

            if (pPrev->fFree)
            {
				/* concatenate free blocks to one */
                if (pHeader->pNext)
                {
                    pHeader->pNext->pPrev = pHeader->pPrev;
                }

				/*if (fIsIecMemory)*/ dwUsedMem_l -= sizeof(tMemHeader);
				/*if (fIsIecMemory2) dwUsedMem2_l -= sizeof(tMemHeader);*/

                pPrev->pNext = pHeader->pNext;
                pPrev->dSize += (pHeader->dSize  + sizeof(tMemHeader));
            }
        }
        else
        {
            LZSTRACE0("[FREE FIRST BLOCK]");
        }

        /* LZSTRACE2(" [Free pMem=%p SIZE=%d]\n ", pMem,dwFreedSize);*/
        /*LzsEnvMemTrace(); */
    }
}

LZSBOOL IsInIecMemory(void* pMem)
{
	if (((LZSBYTE*)pMem < IECMEMORY) || ((LZSBYTE*)pMem >= IECMEMORY + LZS_MAXMEM))
	{
		return LZSFALSE;
	}

	return LZSTRUE;
}

/********************************************************************/
/* FUNCTION: PUBLIC LzsEnvMemInitialize                             */
/* DESCRIPTION: Initializes memory management                       */
/* RETURN: PUBLIC32 void                                            */
/* CALLED: LzsEnvInitialize                                         */
/********************************************************************/
LZSPUBLIC32 void LZSPUBLIC LzsEnvMemInitialize(void)
{
	/* allocate IEC memory */
	/*IECMEMORY = malloc(LZS_MAXMEM);*/

	/* OR: allocate IEC memory (aligned) */
	/*IECMEMORY = memalign(4, LZS_MAXMEM);*/
       IECMEMORY = 230*1024*1024;
	if (IECMEMORY != LZSNULL)
	{
		/* clear memory */
		LzsEnvClearMemory();
	}

#ifdef LZS_DEBUG_MEM        /* B.S. 17.10.00 */
    iPointerIndex = 0;    /*-fg- 20000119 memtest*/
#endif
}

/********************************************************************/
/* FUNCTION: PUBLIC LzsEnvClearMemory                               */
/* DESCRIPTION: Reinitializes memory management                     */
/* RETURN: PUBLIC32 void                                            */
/* CALLED: LzsEnvMemInitialize                                      */
/********************************************************************/
LZSPUBLIC32 void LZSPUBLIC LzsEnvClearMemory(void)
{
	tMemHeader* pMemHeader;
	/* clear memory */
	memset(IECMEMORY, 0, LZS_MAXMEM);

	/* insert first memory header */
	pMemHeader = (tMemHeader*) IECMEMORY;
	dwUsedMem_l = sizeof(tMemHeader);

	pMemHeader->fFree = LZSTRUE;
	pMemHeader->dSize = LZS_MAXMEM - sizeof(tMemHeader);
	pMemHeader->pPrev = LZSNULL;
	pMemHeader->pNext = LZSNULL;
}

/********************************************************************/
/* FUNCTION: PUBLIC LzsEnvSharedMemInitialize                       */
/* DESCRIPTION: Initializes the shared memory                       */
/* RETURN: PUBLIC32 void                                            */
/* CALLED: LzsEnvInitialize                                         */
/********************************************************************/
#ifdef USE_SHARED_MEMORY
LZSPUBLIC32 void LZSPUBLIC LzsEnvSharedMemInitialize(void)
{
	int objType;
	#ifdef _MASTER_CPU_
	/* --------------------------------------------------------- */
	/* MASTER: must create the shared memory and initialize to 0 */
	/* --------------------------------------------------------- */
	SEM_ID shmSemId;

	/* *************************************************************** */
	/* create shared memory and semaphore for unbuffered shared memory */
	/* *************************************************************** */
	pShmBuff_g = (SHM_BUFFER*)smMemMalloc(sizeof(SHM_BUFFER));
	if ((shmSemId = semBSmCreate(SEM_Q_FIFO, SEM_EMPTY)) == NULL)
	{
		logMsg("Shared memory initialization: semaphore create error (MASTER)!\n",0,0,0,0,0,0);
		LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMInitError, 0, 0, 0);
		return;
	}

	semGive(shmSemId);
	pShmBuff_g->sm_semId = (SEM_ID)htonl((int)shmSemId);

	if (smNameAdd(SHM_BUFFER_NAME, (void*)smObjLocalToGlobal(pShmBuff_g), T_SM_BLOCK) == ERROR)
	{
		logMsg("Shared memory initialization: name add error (MASTER)!\n",0,0,0,0,0,0);
		LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMInitError, 0, 0, 0);
		return;
	}

	/* find (connect to) shared memory */
	smNameFind(SHM_BUFFER_NAME, (void**)&pShmBuff_g, &objType, WAIT_FOREVER);
	pShmBuff_g = (SHM_BUFFER*)smObjGlobalToLocal(pShmBuff_g);

	if (pShmBuff_g != LZSNULL)
	{
		/* clear memory */
		pShmBuff_g->dwShmChecksum = 0;
		memset(&pShmBuff_g->sm_buff[0], 0, SHM_BUFFER_SIZE);
	}

	/* ********************************************************************* */
	/* create shared memory and semaphore for shared memory data consistency */
	/* ********************************************************************* */
	#ifdef USE_DATA_CONSISTENCY_SHM
	pShmDCBuff_g = smMemMalloc(SHMDC_BUFFER_SIZE);

	/* INFO: binary semaphore can be FULL or EMPTY */
	/* if semTake() is called on a FULL semaphore, the calling task can continue and the semaphore is made EMPTY */
	/* if semTake() is called on an EMPTY semaphore, the calling task will be blocked */
	/* in that sense, semGive() makes the semaphore FULL and activates the next waiting task */
	if ((shmDCSemId_g = semBSmCreate(SEM_Q_FIFO, SEM_EMPTY)) == NULL)
	{
		logMsg("Shared memory initialization (DC): semaphore create error (MASTER)!\n",0,0,0,0,0,0);
		LzsErrlogRegisterError(kLzsInternalError, kLzsSHMInitError, 0, 0, 0);
		return; /* kLzsSHMInitError */
	}

	semGive(shmDCSemId_g);
	*((SEM_ID*)pShmDCBuff_g) = (SEM_ID)htonl((int)shmDCSemId_g);

	if (smNameAdd(SHMDC_NAME, (void*)smObjLocalToGlobal(pShmDCBuff_g), T_SM_BLOCK) == ERROR)
	{
		logMsg("Shared memory initialization (DC): name add error (MASTER)!\n",0,0,0,0,0,0);
		LzsErrlogRegisterError(kLzsInternalError, kLzsSHMInitError, 0, 0, 0);
		return; /* kLzsSHMInitError */
	}

	/* find (connect to) shared memory */
	smNameFind(SHMDC_NAME, (void**)&pShmDCBuff_g, &objType, WAIT_FOREVER);
	pShmDCBuff_g = smObjGlobalToLocal(pShmDCBuff_g);
	#endif

	/* *************************************************************** */
	/* create shared memory for hardware check and configuration       */
	/* *************************************************************** */
	#ifdef USE_STATION_HWCONFIG
	pShmHwBuff_g = (tSHMHWConfStation*)smMemMalloc(sizeof(tSHMHWConfStation));

	if (smNameAdd(SHMHW_NAME, (void*)smObjLocalToGlobal(pShmHwBuff_g), T_SM_BLOCK) == ERROR)
	{
		logMsg("Shared memory initialization (HW): name add error (MASTER)!\n",0,0,0,0,0,0);
		LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMInitError, 0, 0, 0);
		return;
	}

	/* find (connect to) shared memory */
	smNameFind(SHMHW_NAME, (void**)&pShmHwBuff_g, &objType, WAIT_FOREVER);
	pShmHwBuff_g = (tSHMHWConfStation*)smObjGlobalToLocal(pShmHwBuff_g);

	if (pShmHwBuff_g != LZSNULL)
	{
		/* clear memory */
		memset(pShmHwBuff_g, 0, sizeof(tSHMHWConfStation));
	}
	#endif

	#else /* _MASTER_CPU_ */
	/* ---------------------------------- */
	/* SLAVE: must find the shared memory */
	/* ---------------------------------- */

	/* find (connect to) shared memory (unbuffered) */
	smNameFind(SHM_BUFFER_NAME, (void**)&pShmBuff_g, &objType, WAIT_FOREVER);
	pShmBuff_g = (SHM_BUFFER*)smObjGlobalToLocal(pShmBuff_g);

	/* find (connect to) shared memory (data consistency) */
	#ifdef USE_DATA_CONSISTENCY_SHM
	smNameFind(SHMDC_NAME, (void**)&pShmDCBuff_g, &objType, WAIT_FOREVER);
	pShmDCBuff_g = smObjGlobalToLocal(pShmDCBuff_g);

	/* get semaphore for shared memory (data consistency) */
	shmDCSemId_g = (SEM_ID)ntohl((int)(*((SEM_ID*)pShmDCBuff_g)));
	#endif

	/* find (connect to) shared memory for hardware check and configuration */
	#ifdef USE_STATION_HWCONFIG
	smNameFind(SHMHW_NAME, (void**)&pShmHwBuff_g, &objType, WAIT_FOREVER);
	pShmHwBuff_g = (tSHMHWConfStation*)smObjGlobalToLocal(pShmHwBuff_g);
	#endif

	#endif /* _MASTER_CPU_ */

	/* ------------------------------------------------------------------ */
	/* ALL CPUs: find shared memory (data consistency) checksum and index */
	/* ------------------------------------------------------------------ */

	pShmChecksum_g = &(pShmBuff_g->dwShmChecksum);

	#ifdef USE_DATA_CONSISTENCY_SHM
	/* set pointer to index in shared memory */
	pShmDCIndex_g = pShmDCBuff_g + ALIGN_4_DW(sizeof(SEM_ID)) + sizeof(LZSDWORD);
	#endif

}
#endif

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvMemTrace                                                   */
/* DESCRIPT: traces memory allocation and free                                */
/*                                                                            */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/
void  LzsEnvMemTrace()
{
/*
#ifdef SMARTPLC_TRACE
    tMemHeader *pFirstHeader = (tMemHeader *)IECMEMORY;
    tMemHeader *pHeader=pFirstHeader;
    LZSDWORD dwFree=0,dwUsed=0,iFree=0,iUsed=0;
    LZSDWORD dwAll=0;

    LZSTRACE0 ("\n------------------------------------------------------------\nMEMSTATUS\n");

    while (pHeader){
        if ((pHeader != pFirstHeader) && (pHeader->pPrev == LZSNULL)){
            LZSTRACE0("\n\n****************ERROR ERROR****************\n\n");
        }
        */
        /*LZSTRACE1("\nBLOCK[%04X]",(LZSBYTE *)pHeader + sizeof(tMemHeader));*/
        /*
        if ( pHeader->fFree ){
            dwFree+=pHeader->dSize;
            LZSTRACE0("00|");
            iFree++;
        }else{
            LZSTRACE0("XX|");
            dwUsed+=pHeader->dSize;
            iUsed++;
        }
        */
        /*LZSTRACE1("<%ld> ",pHeader->dSize);*/
        /*
        pHeader = pHeader->pNext;
    }
    LZSTRACE4("\nUsed<%ld>,Free(%ld),Blocks F[%ld]U[%ld]\n",dwUsed,dwFree,iFree,iUsed);
    dwAll = (iFree * sizeof(tMemHeader)) + (iUsed * sizeof(tMemHeader)) + dwUsed + dwFree;

#ifdef LZS_DEBUG_MEM
    LZSTRACE2("ALL=%ld----------------------------------------%ld-----\n",dwAll,iPointerIndex);
#endif

#endif
*/
}

/********************************************************************/
/* FUNCTION:    LzsEnvMemGetInfo                                    */
/* DESCRIPTION: Get memory info for extended capability return      */
/* RETURN:      void                                                */
/* CALLED:      LzsInfoEvalCapabilities                             */
/********************************************************************/
void LzsEnvMemGetInfo(LZSDWORD *pdwMaxMem,LZSDWORD *pdwUsedMem)
{
    *pdwMaxMem = (LZSDWORD)LZS_MAXMEM;
    *pdwUsedMem = dwUsedMem_l;
}

/********************************************************************/
/* FUNCTION:    LzsEncSpecialMalloc                                 */
/* DESCRIPTION: this function may be used to put some internal      */
/*              segments to a specific place                        */
/* RETURN:      void LZSFAR*                                        */
/* CALLED:      LzsCreateInternalSegments                           */
/********************************************************************/
void LZSFAR* LzsEnvSpecialMalloc(LZSDWORD dwMemSize, tPlcSegType SegType)
{
    void LZSFAR* pMem = LZSNULL;

    switch (SegType)
    {
        case kPlcSegNI:
            /*
             *    Example:
             *             instead of using LzsMemAlloc you can say
             *        pMem = 0xF468AA00;
             *             this  may be a fixed address defined in a
             *             locator file
             *
             */
            pMem = LZSMALLOC(dwMemSize);
            break;

        case kPlcSegPI:
            pMem = LZSMALLOC(dwMemSize);
            break;

        case kPlcSegNcHelp:
            pMem = LZSMALLOC(dwMemSize);
            break;

		#ifdef _LZS_ERROR_LOG
		case kPlcSegErrorCtrl:
            pMem = EXCEPTION_MEM_ADDR;
            break;

        case kPlcSegErrorLog:
            pMem = EXCEPTION_MEM_ADDR + SIZEOF_ERRORLOG_CONTROL;
            break;

		case kPlcSegSystemErrorPanel:
            pMem = EXCEPTION_MEM_ADDR + SIZEOF_ERRORLOG_CONTROL + ERRORLOG_SEGMENT_SIZE;
            break;
		#endif

		#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
        case kPlcSegExceptionBuffer:
            pMem = EXCEPTION_MEM_ADDR + SIZEOF_ERRORLOG_CONTROL + ERRORLOG_SEGMENT_SIZE + SYSTEMERRORPANEL_SIZE;
            break;
		#endif

        default:
            pMem = LZSNULL;
            break;
    }

    return pMem;
}

/********************************************************************/
/* FUNCTION:    LzsEnvSpecialFree                                   */
/* DESCRIPTION:                                                     */
/* RETURN:      void                                                */
/* CALLED:                                                          */
/********************************************************************/
void LzsEnvSpecialFree(void LZSFAR* pMem,tPlcSegType SegType)
{
    switch (SegType)
    {
        case kPlcSegNI:
            /*
             *    Example:
             *            if you used a fixed address in LzsEnvSpecialMalloc
             *            normaly you do not free something here
             *
             */
            LZSFREE(pMem);
            break;

        #ifdef _LZS_PERSISTENCE_MIXED_
        case kPlcSegData:
            /* do not free data segment (moved to flash memory) */
            break;
        #endif

        case kPlcSegPI:
            LZSFREE(pMem);
            break;

        case kPlcSegNcHelp:
            LZSFREE(pMem);
            break;

        case kPlcSegErrorLog:
            break;

        case kPlcSegExceptionBuffer:
            break;

        default:
            break;
    }
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvMemDump                                                    */
/*----------------------------------------------------------------------------*/
void LzsEnvMemDump(void)
{
	int i = 0;
    tMemHeader* pHeader = (tMemHeader*)IECMEMORY;
    tSegHeader* pSeg = LZSNULL;

	logMsg("--------BEGIN MEMORY DUMP--------\n",0,0,0,0,0,0);

    while (LZSNULL != pHeader)
    {
		i++;
		logMsg("Block %d: memheader at 0x%x, free: 0x%x, size: 0x%x, previous at 0x%x, next at 0x%x\n",i,pHeader,pHeader->fFree,pHeader->dSize,pHeader->pPrev,pHeader->pNext);

		pSeg = (tSegHeader*)(((LZSBYTE LZSFAR*)pHeader) + sizeof(tMemHeader));
        logMsg("Segment: type 0x%x, size 0x%x\n",pSeg->m_SegType,pSeg->m_SegSize,0,0,0,0);

        pHeader = (tMemHeader *)pHeader->pNext;

        taskDelay(25);
    }

	logMsg("--------END MEMORY DUMP--------\n",0,0,0,0,0,0);
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvMemCheck                                                   */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvMemCheck(void)
{
	int i = 0;
    tMemHeader* pHeader = (tMemHeader*)IECMEMORY;
    tMemHeader* pLastHeader = LZSNULL;
    tSegHeader* pSeg = LZSNULL;

	int segNumber = 0;
	int mainCounter = 0;
	tLzsResourceSegmentTables *locProgData;

    while (LZSNULL != pHeader)
    {
		i++;

		/* checks */
		if (pHeader->pNext != LZSNULL)
		{
			if (!IsInIecMemory(pHeader->pNext))
			{
				logMsg("Block %d: pNext out of range (0x%x); header at 0x%x\n",i,pHeader->pNext,pHeader,0,0,0);

				if (pLastHeader != LZSNULL)
				{
					pSeg = ((tSegHeader*)((LZSBYTE LZSFAR*)pLastHeader) + sizeof(tMemHeader));
					logMsg("Previous block contains: segment type 0x%x, size 0x%x address 0x%x\n",pSeg->m_SegType,pSeg->m_SegSize,pSeg,0,0,0);

					/* find out segment number */
					for (mainCounter = 0; mainCounter < wNumberOfPrograms_g * NUM_TASKS; mainCounter++)
					{
						locProgData = &pSegmentTables2_l[mainCounter];
						for (segNumber = 0; segNumber < locProgData->wSegTabEntries; segNumber++)
						{
							if (locProgData->pSegTable[segNumber].m_pPrimarySeg == (tPlcMemPtr)pSeg)
							{
								logMsg("Previous block segment number: %d segment address: 0x%x mainCounter: %d\n", segNumber,pSeg,mainCounter,0,0,0);
								break;
							}
						}
					}
				}

				return LZSFALSE;
			}
		}

		if (pHeader->pPrev != LZSNULL)
		{
			if (!IsInIecMemory(pHeader->pPrev))
			{
				logMsg("Block %d: pPrev out of range (0x%x)\n",i,pHeader->pPrev,0,0,0,0);

				if (pLastHeader != LZSNULL)
				{
					pSeg = ((tSegHeader*)((LZSBYTE LZSFAR*)pLastHeader) + sizeof(tMemHeader));
					logMsg("Previous block contains: segment type 0x%x, size 0x%x\n",pSeg->m_SegType,pSeg->m_SegSize,0,0,0,0);
				}

				return LZSFALSE;
			}
		}

		if (pHeader->dSize > LZS_MAXMEM)
		{
			logMsg("Block %d: size too big (%d)\n",i,pHeader->dSize,0,0,0,0);

			if (pLastHeader != LZSNULL)
			{
				pSeg = ((tSegHeader*)((LZSBYTE LZSFAR*)pLastHeader) + sizeof(tMemHeader));
				logMsg("Previous block contains: segment type 0x%x, size 0x%x\n",pSeg->m_SegType,pSeg->m_SegSize,0,0,0,0);
			}

			return LZSFALSE;
		}

        pLastHeader = pHeader;
        pHeader = (tMemHeader *)pHeader->pNext;
    }

    return LZSTRUE;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvSegTblDump                                                 */
/*----------------------------------------------------------------------------*/
#if 0
char* LzsEnvGetSegTypeString(tSegHeader* pSeg)
{
	switch (pSeg->m_SegType)
	{
		case 0x00: return "kPlcSegCode";
		case 0x01: return "kPlcSegData";
		case 0x02: return "kPlcSegInit";
		case 0x03: return "kPlcSegSource";
		case 0x04: return "kPlcSegSource2";
		case 0x05: return "kPlcSegTD";
		case 0x06: return "kPlcSegPiAndMask";
		case 0x07: return "kPlcSegNiAndMask";
		case 0x10: return "kPlcSegIoTable";
		case 0x11: return "kPlcSegIoTable2";
		case 0x12: return "kPlcSegIoComplexTable";
		case 0x13: return "kPlcSegIoComplexTable2";
		case 0x14: return "kPlcSegInstanceTable";
		case 0x15: return "kPlcSegInstanceTable2";
		case 0x16: return "kPlcSegDownloadTable";
		case 0x17: return "kPlcSegDownloadTable2";
		case 0x18: return "kPlcSegNativeCode";
		case 0x19: return "kPlcSegInitSecond";
		case 0x20: return "kPlcSegIoSegment";
		case 0x21: return "kPlcSegIoInitSegment";
		case 0x22: return "kPlcSegIoOldSegment";
		case 0x23: return "kPlcSegParameter";
		case 0x24: return "kPlcSegHardwareConfig";
		case 0x25: return "kPlcSegDwlCopyTable";
		case 0x26: return "kPlcSegVarTable";
		case 0x27: return "kPlcOemVarInfoTable";
		case 0x28: return "kPlcSegNativeCode2";
		case 0x29: return "kPlcSegVarTable2";
		case 0x2a: return "kPlcSegSmartVartable";
		case 0x2b: return "kPlcSegSmartVartable2";
		case 0x2c: return "kPlcSegCopyVarList";
		case 0x30: return "kPlcSegErrorLog";
		case 0x31: return "kPlcSegCopyVarList2";
		case 0x32: return "kPlcSegExceptionBuffer";
		case 0x33: return "kPlcSegSystemErrorPanel";
		case 0x34: return "kPlcSegErrorCtrl";
		case 0x35: return "kPlcSegBLCodeSys";
		case 0x36: return "kPlcSegBLCodeNor";
		case 0x38: return "kPlcSegNcHelp";
		case 0x39: return "kPlcSegByRefInfo";
		case 0x40: return "kPlcSegNativeCode3";
		case 0x80: return "kPlcSegPI";
		case 0x81: return "kPlcSegNI";
		case 0x82: return "kPlcSegNVMap";
		case 0x83: return "kPlcSegInstStack";
		case 0x84: return "kPlcSegAEStack";
		case 0x85: return "kPlcSegExtAE";
		case 0x86: return "kPlcSegExtAEs";
		case 0x87: return "kPlcSegAETypeStck";
		case 0xE0: return "kPlcSegBufferI1";
		case 0xE1: return "kPlcSegBufferI2";
		case 0xE2: return "kPlcSegBufferI3";
		case 0xE3: return "kPlcSegBufferI4";
		case 0xE4: return "kPlcSegBufferI5";
		case 0xE5: return "kPlcSegBufferI6";
		case 0xE6: return "kPlcSegBufferI7";
		case 0xE7: return "kPlcSegBufferI8";
		case 0xE8: return "kPlcSegBufferT1";
		case 0xE9: return "kPlcSegBufferT2";
		case 0xEA: return "kPlcSegBufferT3";
		case 0xEB: return "kPlcSegBufferT4";
		case 0xEC: return "kPlcSegBufferT5";
		case 0xF0: return "kPlcSegModTab";
		case 0xF1: return "kPlcSegBinDcf";
		case 0xF2: return "kPlcSegOemSeg";
		case 0xF3: return "kPlcSegBinMemImg";
		case 0xF4: return "kPlcSegOpcSegment";
		case 0xF5: return "kPlcSegSneBinCode";
		case 0xF6: return "kPlcSegDcfAssignment";
		case 0xF7: return "kPlcSegHwConfig";
		case 0xF8: return "kPlcSegShmVars";
		case 0xF9: return "kPlcSegShmConfig";
		case 0xFA: return "kPlcSegShmDCVars";
		case 0xFB: return "kPlcSegStaticNull";
		case 0xFC: return "kPlcSegHwConfigStation";
	}

	return "<undefined>";
}

void LzsEnvSegTblDump (void)
{
	LZSWORD wSegNum;
	LZSWORD wProgramCount;
	LZSWORD wNumberOfPrograms = STRUCT_GET_PROGCNT(LzsTdtGetAddr());
	for (wProgramCount = 0; wProgramCount < wNumberOfPrograms; wProgramCount++)
	{
		for (wSegNum = 0; wSegNum < pSegmentTables_l[wProgramCount].wSegTabEntries; wSegNum++)
		{
			if (pSegmentTables_l[wProgramCount].pSegTable[wSegNum].m_pPrimarySeg != LZSNULL)
			{
				/*printf("Seg %d type: %s size: %d address: 0x%x\n",wSegNum,LzsEnvGetSegTypeString((tSegHeader*)pSegmentTables_l[wProgramCount].pSegTable[wSegNum].m_pPrimarySeg),((tSegHeader*)pSegmentTables_l[wProgramCount].pSegTable[wSegNum].m_pPrimarySeg)->m_SegSize, pSegmentTables_l[wProgramCount].pSegTable[wSegNum].m_pPrimarySeg);*/
			}
			else
			{
				/*printf("Seg %d empty\n",wSegNum);*/
			}
		}
	}
}
#endif

#ifdef _IP_BREAKPOINTS_
#ifdef _LZS_PRAGMAMESSAGE_
#pragma message("_IP_BREAKPOINTS_")
#endif

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvBreakPointReached                                          */
/* DESCRIPT: Called by LZS when a breakpoint was reached                      */
/*             It is used to disable the outputs, or to activate a special task.*/
/* CALLED:                                                                     */
/*----------------------------------------------------------------------------*/
void LzsEnvBreakPointReached(
    tIpBreakPoint LZSFAR* pBreakPoint_p    /* [i] Pointer to breakpoint struct */
    )
{
    LzsEnvDisableAllOutputs(LZS_DISABLE_OUTPUTS_BREAKSTOP);

    /* TODO: Insert OEM code here. Activate special task. */

}

#endif

/*#############################################################################*/
/*                                                                             */
/*            P0699-SPECIFIC FUNCTIONS                                         */
/*                                                                             */
/*#############################################################################*/

void LzsEnvHandleError(LZSDWORD dwCategory, LZSWORD wErrorCode, LZSWORD wParameter2, LZSWORD wParameter3, LZSWORD wParameter4)
{
	int i;
	LZSDWORD dwLedCode = dwCategory;

	if (dwCategory != kLzsUserError)
	{
		switch (wErrorCode)
		{
			/* this list contains all error codes from tLzsErrorCode in lzstypes.h, which must result in an error stop */
			/* additional code to execute on certain errors can also be placed here */

			case kLzsFatalCycleError:
				/* delete tasks with fatal cycle error, because otherwise the CPU will not respond to the programming system any more */
				switch (wParameter2)
				{
					case kT1Task:
						if (taskDelete(tidTask1_nor) == ERROR)
						{
							logMsg("Error deleting T1 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTask1_nor = 0;
							logMsg("T1 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kT2Task:
						if (taskDelete(tidTask2_nor) == ERROR)
						{
							logMsg("Error deleting T2 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTask2_nor = 0;
							logMsg("T2 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kT3Task:
						if (taskDelete(tidTask3_nor) == ERROR)
						{
							logMsg("Error deleting T3 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTask3_nor = 0;
							logMsg("T3 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kT4Task:
						if (taskDelete(tidTask4_nor) == ERROR)
						{
							logMsg("Error deleting T4 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTask4_nor = 0;
							logMsg("T4 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kT5Task:
						if (taskDelete(tidTask5_nor) == ERROR)
						{
							logMsg("Error deleting T5 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTask5_nor = 0;
							logMsg("T5 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kI1Task:
						if (taskDelete(tidTaskInt1) == ERROR)
						{
							logMsg("Error deleting I1 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTaskInt1 = 0;
							logMsg("I1 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kI2Task:
						if (taskDelete(tidTaskInt2) == ERROR)
						{
							logMsg("Error deleting I2 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTaskInt2 = 0;
							logMsg("I2 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kI3Task:
						if (taskDelete(tidTaskInt3) == ERROR)
						{
							logMsg("Error deleting I3 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTaskInt3 = 0;
							logMsg("I3 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kI4Task:
						if (taskDelete(tidTaskInt4) == ERROR)
						{
							logMsg("Error deleting I4 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTaskInt4 = 0;
							logMsg("I4 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kI5Task:
						if (taskDelete(tidTaskInt5) == ERROR)
						{
							logMsg("Error deleting I5 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTaskInt5 = 0;
							logMsg("I5 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kI6Task:
						if (taskDelete(tidTaskInt6) == ERROR)
						{
							logMsg("Error deleting I6 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTaskInt6 = 0;
							logMsg("I6 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kI7Task:
						if (taskDelete(tidTaskInt7) == ERROR)
						{
							logMsg("Error deleting I7 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTaskInt7 = 0;
							logMsg("I7 system task deleted\n",0,0,0,0,0,0);
						}
						break;
					case kI8Task:
						if (taskDelete(tidTaskInt8) == ERROR)
						{
							logMsg("Error deleting I8 system task\n",0,0,0,0,0,0);
						}
						else
						{
							tidTaskInt8 = 0;
							logMsg("I8 system task deleted\n",0,0,0,0,0,0);
						}
						break;
				}

				/* set program invalid to disable start/stop functions in the programming system; will be enabled again after a new download */
				LzsSysSetStatus(LZSSTAT_PROGRAM_VALID, LZSCLR);

				ERROR_STOP(wErrorCode);

				#ifdef _LZS_ERROR_LOG_LED_DISPLAY
				dwLedCode = PLCTASKERR_LEDCATEGORY;
				#endif
				break;

			#ifdef USE_T0_WATCHDOG
			case kLzsWatchdogTimeoutError:
				/* first record the current watchdog error */
				for (i = 0; i < NUM_WD_ERRORS_BEFORE_STOP; i++)
				{
					if (arrayWDErrors[i].fIsValid == LZSFALSE)
					{
						arrayWDErrors[i].fIsValid = LZSTRUE;
						arrayWDErrors[i].dwTimeStamp = LzsEnvGetTickCount();
						break;
					}
				}

				/* check if the maximum number of watchdog errors within the specified time span is reached */
				for (i = 0; i < NUM_WD_ERRORS_BEFORE_STOP; i++)
				{
					if (arrayWDErrors[i].fIsValid == LZSFALSE)
					{
						break;
					}
				}

				if (i == NUM_WD_ERRORS_BEFORE_STOP)
				{
					ERROR_STOP(wErrorCode);

					/* reset recorded data */
					for (i = 0; i < NUM_WD_ERRORS_BEFORE_STOP; i++)
					{
						arrayWDErrors[i].fIsValid = LZSFALSE;
					}
				}
				break;
			#endif

			/*case kLzsNoMem:
				ERROR_STOP(wParameter1);
				break;*/ /* due to use of this error code in various situations, error stop is handled outside of this function for this error code */

			case kLzsMemoryCorrupted:
				ERROR_STOP(wErrorCode);
				break;

			case kLzsIpExecError:
				ERROR_STOP(wErrorCode);
				break;

			case kLzsNcExecError:
				ERROR_STOP(wErrorCode);
				break;

			case kLzsIStackError:
				ERROR_STOP(wErrorCode);
				break;

			case kLzsIStackError2:
				ERROR_STOP(wErrorCode);
				break;

			case kLzsDCBufferError:
				ERROR_STOP(wErrorCode);
				break;

			case kLzsBLExecError:
				ERROR_STOP(wErrorCode);
				break;

			case kLzsSHMDCBufferError:
				ERROR_STOP(wErrorCode);
				break;

			case kLzsSHMChecksumError:
				ERROR_STOP(wErrorCode);
				break;

			case kLzsInitModeExecError:
				ERROR_STOP(wErrorCode);
				break;

			case kLzsHwConfChecksumError:
				ERROR_STOP(wErrorCode);
				break;

			default:
				/* no error stop */
				break;
		}
	}

	/* set LEDs */
	#ifdef _LZS_ERROR_LOG_LED_DISPLAY
	LzsSetLedDisplayMode(dwLedCode);
	#endif
}

void LzsEnvHandleException(LZSDWORD dwExceptionVector)
{
	switch (dwExceptionVector)
	{
		/* this list contains all exception vectors which must result in an error stop */
		/* additional code to execute on certain exceptions can also be placed here */

		default:
			/* stop the system */
			ERROR_STOP(kIpCPUException);

			/* set LEDs */
			#ifdef _LZS_ERROR_LOG_LED_DISPLAY
			LzsSetLedDisplayMode(EXCEPTION_LEDCATEGORY);
			#endif
			break;
	}
}

LZSDWORD GetSegmentChecksum(tPlcMemPtr pSeg, LZSWORD wSize)
{
	LZSDWORD dwCRCValue = 0;
	int i = 0;

    if (bCRCLookupInitialized == LZSFALSE)
    {
        LzsInitializeCRCLookup();
    }

	for (i = 0; i < wSize; i++)
	{
		dwCRCValue = (dwCRCValue<<8) ^ crcLookupTable[0xFF & ((dwCRCValue>>8) ^ *(pSeg + i))];
	}

	return dwCRCValue;
}

#ifdef USE_STATION_HWCONFIG
#ifdef USE_STATION_HWCONFIG_CRC_CHECK
LZSBOOL CheckHwConfigValid()
{
	#ifndef _MASTER_CPU_
	/* SLAVE CPUs: check if hardware configuration is the same as master */
	if (pShmHwBuff_g->dwChecksum != dwHwConfChecksum_g)
	{
		logMsg("HW configuration checksum error: project does not match the master CPU - STOP\n",0,0,0,0,0,0);
		LzsErrlogRegisterError(kLzsInternalError2, kLzsHwConfChecksumError, 0, 0, 0);
		return LZSFALSE;
	}
	#endif

	return LZSTRUE;
}
#endif

LZSBYTE LzsEnvDetectHwModule(LZSDWORD dwTypeID, LZSBYTE* pConfigData)
{
	/* get name of the own resource */
	LZSCHAR* pResName = ((LZSCHAR*)LzsTdtGetAddr()) + STRUCT_OFFSET_RESNAME;

	switch (dwTypeID)
	{
		/* detect presence of different module types here */

		/* the MASTER must do the following: */
		/* - for his own module (found by type ID and name): compare its own real slot number to the configured slot number */
		/* - for other CPU modules: check if the module is present, using pShmHwBuff_g->arrayCPUs[<slot number>].fIsPresent */
		/* - for other module types: check if the module is present, using custom code */
		/* - for submodules: check the "parent CPU" property to find out if the module belongs to this CPU; only if yes, check if the module is present, using custom code */

		/* a SLAVE must do the following: */
		/* - for his own module (found by type ID and name): compare its own real slot number to the configured slot number */
		/* - for other CPU modules: nothing (skip) */
		/* - for other module types: nothing (skip) */
		/* - for submodules: check the "parent CPU" property to find out if the module belongs to this CPU; only if yes, check if the module is present, using custom code */

		/* use the following calls for error handling: */
		/* - if the module was not found: */
		/*   call LzsErrlogRegisterError(kLzsInitialError, kLzsHwDetectError, 0, <slot number - 1 (0-based)>, (LZSWORD)dwTypeID); */
		/*   return kLzsHwDetectError */
		/* - if the module type is not supported (unknown): */
		/*   call LzsErrlogRegisterError(kLzsInitialError, kLzsHwDetectError, 1, 0, (LZSWORD)dwTypeID); */
		/*   return kLzsHwDetectError */

		/* hints: */
		/* - use "#ifdef _MASTER_CPU_" to encapsulate actions that only the master does, "#ifndef _MASTER_CPU_" to encapsulate actions that only slaves do */
		/* - use strcmp and pResName to compare the "parent CPU" property of submodules or the "name" property of CPU modules to the name of this CPU */

		/*case <ID>:
			break;*/

		/*case <ID>:
			break;*/

		/*case <ID>:
			break;*/

		/*case <ID>:
			break;*/

		/*case <ID>:
			break;*/

		default:
			/* unknown module type */
			/*LzsErrlogRegisterError(kLzsInitialError, kLzsHwDetectError, 1, 0, (LZSWORD)dwTypeID);
			return kLzsHwDetectError;*/
			/* TO DO: ACTIVATE THIS CODE AS SOON AS SOME MODULE TYPES ARE IMPLEMENTED!!! */
			break;
	}

	return kLzsSuccess;
}

LZSBYTE LzsEnvConfigureHwModule(LZSDWORD dwTypeID, LZSBYTE* pConfigData)
{
	/* get name of the own resource */
	LZSCHAR* pResName = ((LZSCHAR*)LzsTdtGetAddr()) + STRUCT_OFFSET_RESNAME;

	switch (dwTypeID)
	{
		/* apply configuration settings to different module types here */

		/* the MASTER must do the following: */
		/* - for his own module (found by type ID and name): apply settings */
		/* - for other CPU modules: nothing (skip) */
		/* - for other module types: apply settings */
		/* - for submodules: check the "parent CPU" property to find out if the module belongs to this CPU; only if yes, apply settings */

		/* a SLAVE must do the following: */
		/* - for his own module (found by type ID and name): apply settings */
		/* - for other CPU modules: nothing (skip) */
		/* - for other module types: nothing (skip) */
		/* - for submodules: check the "parent CPU" property to find out if the module belongs to this CPU; only if yes, apply settings */

		/* use the following calls for error handling: */
		/* - if any error happend during apply settings: */
		/*   call LzsErrlogRegisterError(kLzsInitialError, kLzsHwConfigureError, 0, <slot number - 1 (0-based)>, (LZSWORD)dwTypeID); */
		/*   return kLzsHwConfigureError */
		/* - if the module type is not supported (unknown): */
		/*   call LzsErrlogRegisterError(kLzsInitialError, kLzsHwConfigureError, 1, 0, (LZSWORD)dwTypeID); */
		/*   return kLzsHwConfigureError */

		/* hints: */
		/* - use "#ifdef _MASTER_CPU_" to encapsulate actions that only the master does, "#ifndef _MASTER_CPU_" to encapsulate actions that only slaves do */
		/* - use strcmp and pResName to compare the "parent CPU" property of submodules or the "name" property of CPU modules to the name of this CPU */

		/*case <ID>:
			break;*/

		/*case <ID>:
			break;*/

		/*case <ID>:
			break;*/

		/*case <ID>:
			break;*/

		/*case <ID>:
			break;*/

		default:
			/* unknown module type */
			/*LzsErrlogRegisterError(kLzsInitialError, kLzsHwConfigureError, 1, 0, (LZSWORD)dwTypeID);
			return kLzsHwConfigureError;*/
			/* TO DO: ACTIVATE THIS CODE AS SOON AS SOME MODULE TYPES ARE IMPLEMENTED!!! */
			break;
	}

	return kLzsSuccess;
}
#endif

LZSBYTE LzsEnvProcessHwConfig(LZSBOOL fOnlineEdit)
{
	LZSWORD i = 0;
	LZSWORD* pIndex = LZSNULL;
	LZSBYTE* pData = LZSNULL;
	LZSBYTE bRetCode = kLzsSuccess;
	LZSWORD wNumModules = 0;
	LZSWORD wNumRetries = 0;
	tSegHeader* pSegHeader = LZSNULL;
	tPlcMemPtr pHwConfigSeg = LzsSegGetHwConfig(); /* get hardware config segment containing the task configuration */
	tPlcMemPtr pStationConfigSeg = LzsSegGetHwConfigStation(); /* get hardware config segment containing the station (rack) configuration */

	/* ======== PART 1: PROCESS THE CPU CONFIGURATION SEGMENT ======== */

	pTaskConfig_g = LZSNULL;

	/* segment found? */
	if (pHwConfigSeg != NULL)
	{
		/* check the segment header */
		pSegHeader = (tSegHeader*)pHwConfigSeg;

		/* correct segment type? */
		if (pSegHeader->m_SegType == kPlcSegHwConfig)
		{
			/* set pointers */
			pTaskConfig_g = (tTaskConfig*)(pHwConfigSeg + pSegHeader->m_HeaderSize);
			pTargetConfig_g = (tTargetConfig*)(pHwConfigSeg + pSegHeader->m_HeaderSize + sizeof(tTaskConfig));
			pExecOrderConfig_g = (LZSWORD*)(pHwConfigSeg + pSegHeader->m_HeaderSize + sizeof(tTaskConfig) + sizeof(tTargetConfig));

			if (!fOnlineEdit)
			{
				/* debug trace */
				/*logMsg("\nTASK CONFIGURATION:\n-------------------\nT0 interval: %d us\nT1 = %d * T0\nT2 = %d * T0\nT3 = %d * T0\nT4 = %d * T0\nT5 = %d * T0\n", pTaskConfig_g->dwT0Interval, pTaskConfig_g->dwT1Factor, pTaskConfig_g->dwT2Factor, pTaskConfig_g->dwT3Factor, pTaskConfig_g->dwT4Factor, pTaskConfig_g->dwT5Factor);
				logMsg("I1 equivalent sampling time: %d 1/100 us\nI2 equivalent sampling time: %d 1/100 us\nI3 equivalent sampling time: %d 1/100 us\nI4 equivalent sampling time: %d 1/100 us\n", pTaskConfig_g->dwI1SamplingTime, pTaskConfig_g->dwI2SamplingTime, pTaskConfig_g->dwI3SamplingTime, pTaskConfig_g->dwI4SamplingTime, 0, 0);
				logMsg("I5 equivalent sampling time: %d 1/100 us\nI6 equivalent sampling time: %d 1/100 us\nI7 equivalent sampling time: %d 1/100 us\nI8 equivalent sampling time: %d 1/100 us\n", pTaskConfig_g->dwI5SamplingTime, pTaskConfig_g->dwI6SamplingTime, pTaskConfig_g->dwI7SamplingTime, pTaskConfig_g->dwI8SamplingTime, 0, 0);*/

				/* apply values to scheduler */
				dps_t0 = (float)pTaskConfig_g->dwT0Interval / 1000.0; /* dps_t0 is in milliseconds, dwT0Interval is in microseconds */
				dps_t0_us = pTaskConfig_g->dwT0Interval;

				Task1Para = pTaskConfig_g->dwT1Factor;
				Task2Para = pTaskConfig_g->dwT2Factor;
				Task3Para = pTaskConfig_g->dwT3Factor;
				Task4Para = pTaskConfig_g->dwT4Factor;
				Task5Para = pTaskConfig_g->dwT5Factor;

				dps_t1_ta = dps_t0 * (float)Task1Para;
				dps_t2_ta = dps_t0 * (float)Task2Para;
				dps_t3_ta = dps_t0 * (float)Task3Para;
				dps_t4_ta = dps_t0 * (float)Task4Para;
				dps_t5_ta = dps_t0 * (float)Task5Para;

				dps_i1_ta = (float)pTaskConfig_g->dwI1SamplingTime / 100000.0; /* dps_i1_ta is in milliseconds, dwI1SamplingTime is in 1/100 microseconds */
				dps_i2_ta = (float)pTaskConfig_g->dwI2SamplingTime / 100000.0; /* dps_i2_ta is in milliseconds, dwI2SamplingTime is in 1/100 microseconds */
				dps_i3_ta = (float)pTaskConfig_g->dwI3SamplingTime / 100000.0; /* dps_i3_ta is in milliseconds, dwI3SamplingTime is in 1/100 microseconds */
				dps_i4_ta = (float)pTaskConfig_g->dwI4SamplingTime / 100000.0; /* dps_i4_ta is in milliseconds, dwI4SamplingTime is in 1/100 microseconds */
				dps_i5_ta = (float)pTaskConfig_g->dwI5SamplingTime / 100000.0; /* dps_i5_ta is in milliseconds, dwI5SamplingTime is in 1/100 microseconds */
				dps_i6_ta = (float)pTaskConfig_g->dwI6SamplingTime / 100000.0; /* dps_i6_ta is in milliseconds, dwI6SamplingTime is in 1/100 microseconds */
				dps_i7_ta = (float)pTaskConfig_g->dwI7SamplingTime / 100000.0; /* dps_i7_ta is in milliseconds, dwI7SamplingTime is in 1/100 microseconds */
				dps_i8_ta = (float)pTaskConfig_g->dwI8SamplingTime / 100000.0; /* dps_i8_ta is in milliseconds, dwI8SamplingTime is in 1/100 microseconds */

				/* configure timer for cyclic tasks */
				if (dps_t0_us > 0)
				{
					taskScheduleInitTimer(dps_t0 / 1000.0); /* timer configuration expects a time value in seconds; dps_t0 is in milliseconds */
				}
			}
		}
	}

	if (pTaskConfig_g == LZSNULL)
	{
		/* return error */
		LzsErrlogRegisterError(kLzsInternalError, kLzsNoHWConfig, 0, 0, 0);
		return kLzsNoHWConfig;
	}

	/* ======== PART 2: PROCESS THE STATION (RACK) CONFIGURATION SEGMENT ======== */

	#ifdef USE_STATION_HWCONFIG
	if (!fOnlineEdit)
	{
		/* segment found? */
		if (pStationConfigSeg != NULL)
		{
			/* check the segment header */
			pSegHeader = (tSegHeader*)pStationConfigSeg;

			/* correct segment type? */
			if (pSegHeader->m_SegType == kPlcSegHwConfigStation)
			{
				/* calculate local checksum value from the configuration segment */
				dwHwConfChecksum_g = GetSegmentChecksum(pStationConfigSeg, pSegHeader->m_SegSize);

				/* read number of modules */
				wNumModules = *((LZSWORD*)(pStationConfigSeg + pSegHeader->m_HeaderSize));

				/* set pointer to index */
				pIndex = (LZSWORD*)(pStationConfigSeg + pSegHeader->m_HeaderSize + sizeof(LZSWORD));

				/* process all modules */
				for (i = 0; i < wNumModules; i++)
				{
					pData = pStationConfigSeg + pIndex[i];

					bRetCode = LzsEnvDetectHwModule(*((LZSDWORD*)pData), pData + sizeof(LZSDWORD));
					if (bRetCode != kLzsSuccess)
					{
						break;
					}

					bRetCode = LzsEnvConfigureHwModule(*((LZSDWORD*)pData), pData + sizeof(LZSDWORD));
					if (bRetCode != kLzsSuccess)
					{
						break;
					}
				}
			}
			else
			{
				pStationConfigSeg = LZSNULL;
			}
		}

		if (pStationConfigSeg == LZSNULL)
		{
			/* return error */
			/*LzsErrlogRegisterError(kLzsInternalError, kLzsNoHWConfig, 0, 0, 0);
			bRetCode = kLzsNoHWConfig;*/
			/* TO DO: ACTIVATE THIS CODE AS SOON AS THE STATION CONFIGURATION SEGMENT IS MANDATORY!!! CURRENTLY IT IS SILENTLY ACCEPTED IF IT IS MISSING! */
		}

		#ifdef _MASTER_CPU_
		/* --------------------------------------------------------- */
		/* MASTER ONLY: set checksum in shared memory                */
		/* --------------------------------------------------------- */

		pShmHwBuff_g->dwChecksum = dwHwConfChecksum_g;

		#else
		/* --------------------------------------------------------- */
		/* SLAVE ONLY: check result of the master                    */
		/* --------------------------------------------------------- */

		/* find the master */
		for (i = 0; i < MAX_SLOTS_IN_RACK; i++)
		{
			if (pShmHwBuff_g->arrayCPUs[i].fIsMaster == LZSTRUE)
			{
				/* check if master is finished - if not, wait some and retry */
				wNumRetries = 0;
				while (pShmHwBuff_g->arrayCPUs[i].fHWConfFinished == LZSFALSE)
				{
					wNumRetries++;
					if (wNumRetries > MAX_NUM_RETRIES)
					{
						LzsErrlogRegisterError(kLzsInitialError, kLzsHwMasterError, 0, 0, 0);
						bRetCode = kLzsHwMasterError;
						break;
					}
					else
					{
						logMsg("Hardware configuration: master is not yet ready - trying again\n",0,0,0,0,0,0);
						taskDelay(RETRY_WAITTIME_MS);
					}
				}

				/* check if master was successful */
				if (pShmHwBuff_g->arrayCPUs[i].fHWConfSuccess == LZSFALSE)
				{
					LzsErrlogRegisterError(kLzsInitialError, kLzsHwMasterError, 0, 0, 0);
					bRetCode = kLzsHwMasterError;
				}
			}
		}
		#endif

		/* check results and fill hardware config structure of this CPU in shared memory */
		if (bRetCode == kLzsSuccess)
		{
			pShmHwBuff_g->arrayCPUs[bSlotNumber_g - 1].fHWConfFinished = LZSTRUE;
			pShmHwBuff_g->arrayCPUs[bSlotNumber_g - 1].fHWConfSuccess = LZSTRUE;
		}
		else
		{
			pShmHwBuff_g->arrayCPUs[bSlotNumber_g - 1].fHWConfFinished = LZSTRUE;
			pShmHwBuff_g->arrayCPUs[bSlotNumber_g - 1].fHWConfSuccess = LZSFALSE;
		}
	}
	#endif

	return bRetCode;
}

LZSBYTE LzsEnvApplyExecutionOrder(LZSWORD* pStart, LZSBOOL fOnlineEdit)
{
	/* this function sorts the program lists from the auto-optimizer (AO) according to the downloaded data from the program execution order editor (PEO) */
	/* reason: PEO does not make a distinction between the different modes of each task; so it might send an execution order "2,4,3,1" for T1, but T1N might only use programs 1,2,3, T1S might only use programs 3,4 (as an example) */
	/* that's why everything is based on the data from the auto-optimizer - it will never happen that the number of programs per task/mode changes, only the order is based on the information from PEO */

	LZSWORD task = 0;
	LZSWORD mode = 0;
	LZSWORD temp = 0;
	LZSWORD countPEO = 0; /* number of entries in the lists from PEO */
	LZSWORD countAO = 0; /* number of entries in the lists from auto-optimizer */
	LZSWORD indexListPEO = 0; /* index in the lists from PEO */
	LZSWORD indexListAO = 0; /* index in the lists from auto-optimizer */
	LZSWORD valuePEO = 0;
	LZSWORD indexFoundAO = 0;
	/*LZSWORD indexTrace = 0;*/ /* only used for debug traces */
	LZSBOOL foundAO = LZSFALSE;

	/* NOTE: this must also be processed after online edit, because the program lists are recreated! */

	pStart++; /* jump over "total size" field */

	#ifdef _ONE_TASK_ONLY_T1_
	/* jump to T1 PEO list */
	for (task = 0; task < kT1Task; task++)
	{
		pStart += (*pStart + 1);
	}
	#endif

	/*logMsg("\nEXEC ORDER:\n-----------\n",0,0,0,0,0,0);*/

	for (task = 0; task < NUM_TASKS; task++) /* process all tasks */
	{
		countPEO = *pStart; /* get number of values in the current PEO list */

		for (mode = 0; mode < NUM_MODES; mode++) /* process all modes */
		{
			/* skip consistent import/export for interrupt tasks */
			if (task < kT1Task && (mode == kConsistentImport || mode == kConsistentExport))
			{
				continue;
			}

			countAO = arrayControlSets_g[task * NUM_MODES + mode].pProgramList[0];

			/* debug trace */
			/*logMsg("Task %d mode %d (list from auto-optimizer):\n",task,mode,0,0,0,0);
			for (indexTrace = 1; indexTrace <= countAO; indexTrace++)
			{
				logMsg("%d\n",array_pProgramList[task * NUM_MODES + mode][indexTrace],0,0,0,0,0);
			}*/

			/* debug trace */
			/*logMsg("Task %d mode %d (list from PEO):\n",task,mode,0,0,0,0);
			for (indexTrace = 1; indexTrace <= countPEO; indexTrace++)
			{
				logMsg("%d\n",*(pStart + indexTrace),0,0,0,0,0);
			}*/

			indexListPEO = 1;
			indexListAO = 1;

			while (indexListPEO <= countPEO && indexListAO <= countAO)
			{
				valuePEO = *(pStart + indexListPEO);

				if (valuePEO != arrayControlSets_g[task * NUM_MODES + mode].pProgramList[indexListAO]) /* compare program numbers coming from PEO and AO */
				{
					/* if unequal, search for the value from PEO in the list from AO */
					foundAO = LZSFALSE;
					for (indexFoundAO = 1; indexFoundAO <= countAO; indexFoundAO++)
					{
						if (arrayControlSets_g[task * NUM_MODES + mode].pProgramList[indexFoundAO] == valuePEO)
						{
							foundAO = LZSTRUE;
							break;
						}
					}

					if (foundAO == LZSTRUE)
					{
						/* if found: swap the values in the AO list to make it equal to the PEO list; go to next indices */
						temp = arrayControlSets_g[task * NUM_MODES + mode].pProgramList[indexListAO];
						arrayControlSets_g[task * NUM_MODES + mode].pProgramList[indexListAO] = arrayControlSets_g[task * NUM_MODES + mode].pProgramList[indexFoundAO];
						arrayControlSets_g[task * NUM_MODES + mode].pProgramList[indexFoundAO] = temp;

						indexListPEO++;
						indexListAO++;
					}
					else
					{
						/* not found; go to next index only in the PEO list (means: the task/mode is in fact not used) */
						indexListPEO++;
					}
				}
				else
				{
					/* no change necessary; go to next indices */
					indexListPEO++;
					indexListAO++;
				}
			}

			/* debug trace */
			/*logMsg("Task %d mode %d (final list, sorted by PEO info):\n",task,mode,0,0,0,0);
			for (indexTrace = 1; indexTrace <= countAO; indexTrace++)
			{
				logMsg("%d\n",array_pProgramList[task * NUM_MODES + mode][indexTrace],0,0,0,0,0);
			}*/
		}

		/* move pointer to the first value of the next PEO list*/
		pStart += (countPEO + 1); /* +1 because of the size field for the current list! */
	}

	return kLzsSuccess;
}

#ifdef USE_SHARED_MEMORY
LZSBOOL CheckSHMConfigValid()
{
	#ifndef _MASTER_CPU_
	/* SLAVE CPUs: check if shared memory configuration is the same as master */
	if (*pShmChecksum_g != dwShmChecksum_g)
	{
		logMsg("SHMDC checksum error: project does not match the master CPU - STOP\n",0,0,0,0,0,0);
		LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMChecksumError, 0, 0, 0);
		return LZSFALSE;
	}
	#endif

	return LZSTRUE;
}

LZSBYTE LzsEnvProcessSHMConfig(LZSBOOL fOnlineEdit)
{
	LZSBYTE bRetCode = kLzsSuccess;
	tSegHeader* pSegHeader = LZSNULL;
	tPlcMemPtr pSHMConfigSeg = LzsSegGetSHMConfig(); /* get shared memory config segment containing the buffer description */

	if (fOnlineEdit)
	{
		/* online edit: do NOT process again */
		return bRetCode;
	}

	#ifdef _MASTER_CPU_
	/* MASTER: first, always clear the shared memory */
	ClearSHMDCMemory();
	#endif

	/* NOTE: some other shared memory data consistency variables are cleared in LzsTdtDelTaskDefSeg()! */

	/* segment found? */
	if (pSHMConfigSeg != NULL)
	{
		/* check the segment header */
		pSegHeader = (tSegHeader*)pSHMConfigSeg;

		/* correct segment type? */
		if (pSegHeader->m_SegType == kPlcSegShmConfig)
		{
			/* ALL CPUs: get local checksum value from the configuration segment */
			dwShmChecksum_g = *(pSHMConfigSeg + pSegHeader->m_HeaderSize + sizeof(LZSDWORD));

			#ifdef _MASTER_CPU_
			/* MASTER: set checksum in shared memory */
			*pShmChecksum_g = dwShmChecksum_g;
			#endif

			#ifdef USE_DATA_CONSISTENCY_SHM
			/* ALL CPUs: get highest segment number used for shared memory data consistency buffers and set global variable */
			wLastSegNumSHMDCBuffers = GetLastSHMDCSegment((LZSWORD*)(pSHMConfigSeg + pSegHeader->m_HeaderSize));

			#ifdef _MASTER_CPU_
			/* ----------------------------------------------------------- */
			/* MASTER: must initialize checksum, index and management data */
			/* ----------------------------------------------------------- */

			/* calculate total size of the shared memory for data consistency buffers */
			dwSHMSize_g = CalcTotalSHMDCMemSize((LZSWORD*)(pSHMConfigSeg + pSegHeader->m_HeaderSize));

			if (dwSHMSize_g > 0)
			{
				/* size check */
				if (dwSHMSize_g <= SHMDC_BUFFER_SIZE)
				{
					/* initialize shared memory */
					bRetCode = InitSHMDCMemory((LZSWORD*)(pSHMConfigSeg + pSegHeader->m_HeaderSize));
				}
				else
				{
					LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMDCSizeError, 0, 0, 0);
					bRetCode = kLzsSHMDCSizeError;
				}
			}
			else
			{
				LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMConfigError, 0, 0, 0);
				bRetCode = kLzsSHMConfigError;
			}
			#endif

			/* ---------------------------------------------- */
			/* ALL CPUs: must initialize their own SHMDC info */
			/* ---------------------------------------------- */
			if (bRetCode == kLzsSuccess)
			{
				bRetCode = SetOwnCPUIndex((LZSWORD*)(pSHMConfigSeg + pSegHeader->m_HeaderSize));
			}

			if (bRetCode == kLzsSuccess)
			{
				bRetCode = SetOwnBuffers((LZSWORD*)(pSHMConfigSeg + pSegHeader->m_HeaderSize));
			}

			if (bRetCode == kLzsSuccess)
			{
				bRetCode = SetSourceBuffers((LZSWORD*)(pSHMConfigSeg + pSegHeader->m_HeaderSize));
			}

			if (bRetCode == kLzsSuccess)
			{
				bRetCode = SetBufferInfo();
			}
			#endif
		}
		else
		{
			LzsErrlogRegisterError(kLzsInternalError, kLzsNoSHMConfig, 0, 0, 0);
			bRetCode = kLzsNoSHMConfig;
		}
	}
	else
	{
		/* this is NOT an error - it is possible that there are no shared memory variables */
		/*LzsErrlogRegisterError(kLzsInternalError, kLzsNoSHMConfig, 0, 0, 0);
		bRetCode = kLzsNoSHMConfig;*/
	}

	return bRetCode;
}
#endif

#ifdef USE_DATA_CONSISTENCY_SHM
LZSWORD GetLastSHMDCSegment(LZSWORD* pStart)
{
	LZSDWORD dwNumCPUs = 0;
	LZSWORD i = 0;
	LZSWORD k = 0;
	LZSWORD wNumLastSeg = FIRST_SEG_NUM_SHM_DC_BUFFERS - 1;
	LZSWORD* pCurrent = pStart;
	LZSWORD* pNextCPU = LZSNULL;

	/* read number of CPUs and advance pointer to the position behind the number of CPUs and SHM checksum (2 DWORDs) */
	dwNumCPUs = *((LZSDWORD*)pCurrent);
	pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 2 * sizeof(LZSDWORD));

	/* for all CPUs: analyze configuration data */
	for (i = 0; i < dwNumCPUs; i++)
	{
		/* jump over resource name string (32 bytes) */
		pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 32);

		/* read size of this CPU's data and set pointer to the data of the next CPU (to be used later) */
		pNextCPU = (LZSWORD*)(((LZSBYTE*)pCurrent) + *pCurrent);
		pCurrent++;

		/* now read the section "owned segments" (next 13 words) to get the highest segment number from the current CPU */
		for (k = 0; k < 13; k++)
		{
			if (pCurrent[k] > wNumLastSeg)
			{
				wNumLastSeg = pCurrent[k];
			}
		}

		/* continue with next CPU */
		pCurrent = pNextCPU;
	}

	return wNumLastSeg;
}

LZSWORD GetNumClientsForSHMDCSegment(LZSWORD wSeg, LZSWORD* pStart)
{
#if 0
	/* fully dynamic solution: find out which other tasks (on all CPUs) are reading from the specified segment - NOT USED ANY MORE */
	LZSWORD dwNumCPUs = 0;
	LZSWORD i = 0;
	LZSWORD k = 0;
	LZSWORD m = 0;
	LZSWORD wNumEntries = 0;
	LZSWORD wNumClients = 0;
	LZSWORD* pCurrent = pStart;
	LZSWORD* pNextCPU = LZSNULL;

	/* read number of CPUs and advance pointer to the position behind the number of CPUs and SHM checksum (2 DWORDs) */
	dwNumCPUs = *((LZSDWORD*)pCurrent);
	pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 2 * sizeof(LZSDWORD));

	/* for all CPUs: analyze configuration data */
	for (i = 0; i < dwNumCPUs; i++)
	{
		/* jump over resource name string (32 bytes) */
		pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 32);

		/* read size of this CPU's data and set pointer to the data of the next CPU (to be used later) */
		pNextCPU = (LZSWORD*)(((LZSBYTE*)pCurrent) + *pCurrent);
		pCurrent++;

		/* jump over section "owned segments" (next 13 words) */
		pCurrent += 13;

		/* now read the section "used segments" (variable length) to get number of references to the specified segment from the current CPU */
		for (k = 0; k < 13; k++)
		{
			wNumEntries = *pCurrent;
			pCurrent++;

			for (m = 0; m < wNumEntries; m++)
			{
				if (pCurrent[m] == wSeg)
				{
					wNumClients++;
				}
			}

			pCurrent += wNumEntries;
		}

		/* continue with next CPU */
		pCurrent = pNextCPU;
	}

	return wNumClients + 2; /* plus 2, because: one extra buffer must be available for writing; one extra buffer must be available for latest consistent */

#else

	/* static solution: simply use the number of CPUs in the rack which participate in shared memory usage (from configuration segment) */
	return (*((LZSDWORD*)pStart) + 1); /* formula: "numCPUs - 1 + 2"; minus 1, because only other CPUs count (not the CPU owning the segment, it will not use it for reading); plus 2, because: one extra buffer must be available for writing; one extra buffer must be available for latest consistent */
#endif
}

/* NOTE: this function assumes that wLastSegNumSHMDCBuffers is already set when it is called! */
LZSDWORD CalcTotalSHMDCMemSize(LZSWORD* pStart)
{
	LZSWORD dwNumCPUs = 0;
	LZSWORD i = 0;
	LZSDWORD dwSize = 0;
	LZSWORD* pCurrent = pStart;
	LZSWORD wSegSize = 0;
	LZSWORD wNumClients = 0;

	/* read number of CPUs and advance pointer to the position behind the number of CPUs and SHM checksum (2 DWORDs) */
	dwNumCPUs = *((LZSDWORD*)pCurrent);
	pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 2 * sizeof(LZSDWORD));

	/* SIZE: add semaphore, with correct alignment */
	dwSize += sizeof(SEM_ID);
	dwSize = ALIGN_4_DW(dwSize);

	/* SIZE: add checksum */
	dwSize += sizeof(LZSDWORD);

	/* SIZE: add index with offsets to buffer blocks */
	dwSize += ((wLastSegNumSHMDCBuffers - wFirstSegNumSHMDCBuffers + 1) * sizeof(LZSDWORD));

	/* for all shared memory data consistency buffer segments: check number of clients and size */
	for (i = wFirstSegNumSHMDCBuffers; i <= wLastSegNumSHMDCBuffers; i++)
	{
		wSegSize = LzsSegGetSegSize(i);
		wNumClients = GetNumClientsForSHMDCSegment(i, pStart);

		if (wSegSize == 0)
		{
			/* error */
			return 0;
		}

		/* SIZE: add buffer management data for the current segment */
		/* this is:
		 * - number of buffer copies (1 word)
		 * - latest consistent buffer (number, 1 word)
		 * - buffer offsets (wNumClients * 1 dword)
		 * - buffer lock counters (wNumClients * 1 byte)
		 * - fill bytes for correct alignment
		 * */
		dwSize += sizeof(LZSWORD);
		dwSize += sizeof(LZSWORD);
		dwSize += wNumClients * sizeof(LZSDWORD);
		dwSize += dwNumCPUs * sizeof(LZSBYTE);
		dwSize = ALIGN_4_DW(dwSize);

		/* SIZE: add buffer copies, with correct alignment */
		dwSize += wNumClients * ALIGN_4_DW((LZSDWORD)wSegSize);
	}

	return dwSize;
}

/* NOTE: this function assumes that wLastSegNumSHMDCBuffers AND pShmDCBuff_g AND dwSHMSize_g AND dwShmDCChecksum_g are already set when it is called! */
/* NOTE: the term "buffer block" means (1) the buffer management data for one task (of one CPU) and (2) the buffer copies itself */
LZSBYTE InitSHMDCMemory(LZSWORD* pStart)
{
	LZSWORD dwNumCPUs = 0;
	LZSWORD i = 0;
	LZSWORD k = 0;
	LZSDWORD dwOffsetSem = 0;
	LZSDWORD dwOffsetIndex = 0;
	LZSDWORD dwOffsetBufferBlock = 0;
	LZSWORD* pCurrent = pStart;
	LZSWORD wSegSize = 0;
	LZSWORD wNumClients = 0;
	LZSBYTE* pShm = pShmDCBuff_g;
	LZSDWORD* pIndex = LZSNULL;
	LZSDWORD* pOffsets = LZSNULL;
	LZSBYTE* pReadFlags = LZSNULL;

	/* clear memory */
	memset(pShmDCBuff_g, 0, dwSHMSize_g);

	/* read number of CPUs and advance pointer to the position behind the number of CPUs and SHM checksum (2 DWORDs) */
	dwNumCPUs = *((LZSDWORD*)pCurrent);
	pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 2 * sizeof(LZSDWORD));

	/* OFFSET for INDEX: add semaphore, with correct alignment, and checksum */
	dwOffsetIndex = dwOffsetSem + sizeof(SEM_ID);
	dwOffsetIndex = ALIGN_4_DW(dwOffsetIndex);
	dwOffsetIndex += sizeof(LZSDWORD); /* checksum */
	pIndex = (LZSDWORD*)(pShm + dwOffsetIndex);

	/* OFFSET for first BUFFER BLOCK: add index with offsets to buffer blocks */
	dwOffsetBufferBlock = dwOffsetIndex + ((wLastSegNumSHMDCBuffers - wFirstSegNumSHMDCBuffers + 1) * sizeof(LZSDWORD));

	/* for all shared memory data consistency buffer segments: set offset in index; check number of clients and size to know the next index */
	for (i = wFirstSegNumSHMDCBuffers; i <= wLastSegNumSHMDCBuffers; i++)
	{
		/* set buffer block offset of current segment in index */
		*(pIndex + (i - wFirstSegNumSHMDCBuffers)) = dwOffsetBufferBlock;

		wSegSize = LzsSegGetSegSize(i);
		wNumClients = GetNumClientsForSHMDCSegment(i, pStart);

		if (wSegSize == 0)
		{
			/* error */
			LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMInitError, 0, 0, 0);
			return kLzsSHMInitError;
		}

		/* set number of buffer copies in buffer management data of current segment */
		*((LZSWORD*)(pShm + dwOffsetBufferBlock)) = wNumClients;

		/* OFFSET for next BUFFER BLOCK: add buffer management data for the current segment */
		/* this is:
		 * - number of buffer copies (1 word)
		 * - latest consistent buffer (number, 1 word)
		 * - buffer offsets (wNumClients * 1 dword)
		 * - buffer read flags (dwNumCPUs * 1 byte)
		 * - fill bytes for correct alignment
		 * */
		dwOffsetBufferBlock += sizeof(LZSWORD);
		dwOffsetBufferBlock += sizeof(LZSWORD);
		pOffsets = (LZSDWORD*)(pShm + dwOffsetBufferBlock);
		dwOffsetBufferBlock += wNumClients * sizeof(LZSDWORD);
		pReadFlags = (LZSBYTE*)(pShm + dwOffsetBufferBlock);
		dwOffsetBufferBlock += dwNumCPUs * sizeof(LZSBYTE);
		dwOffsetBufferBlock = ALIGN_4_DW(dwOffsetBufferBlock);

		/* set buffer offsets in buffer management data of current segment */
		for (k = 0; k < wNumClients; k++)
		{
			pOffsets[k] = dwOffsetBufferBlock + (k * ALIGN_4_DW((LZSDWORD)wSegSize));
		}

		/* initialize buffer read flags */
		for (k = 0; k < dwNumCPUs; k++)
		{
			pReadFlags[k] = 0xFF; /* 0xFF because 0 is a valid buffer number which can be in use */
		}

		/* OFFSET for next BUFFER BLOCK: add buffer copies, with correct alignment */
		dwOffsetBufferBlock += wNumClients * ALIGN_4_DW((LZSDWORD)wSegSize);
	}

	return kLzsSuccess;
}

void ClearSHMDCMemory()
{
	/* clear memory */
	memset(pShmDCBuff_g, 0, dwSHMSize_g);
}

LZSBYTE SetOwnCPUIndex(LZSWORD* pStart)
{
	LZSWORD i = 0;
	LZSWORD* pCurrent = pStart;
	LZSWORD* pNextCPU = LZSNULL;
	tPlcTaskDefTable* pTaskDefTab;
	LZSCHAR* pResName = LZSNULL;
	LZSBOOL fIsOwnResource = LZSFALSE;

	/* get name of the own resource */
	pTaskDefTab = LzsTdtGetAddr();
	if (pTaskDefTab != LZSNULL)
	{
		pResName = ((LZSCHAR*)pTaskDefTab) + STRUCT_OFFSET_RESNAME;
	}
	else
	{
		LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMInitErrorSetInfo, 0, 0, 0);
		return kLzsSHMInitErrorSetInfo;
	}

	/* read number of CPUs, set the respective global variable, and advance pointer to the position behind the number of CPUs and SHM checksum (2 DWORDs) */
	wSHMNumCPUs = (LZSWORD)(*((LZSDWORD*)pCurrent));
	pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 2 * sizeof(LZSDWORD));

	/* for all CPUs: find own resource and analyze configuration data */
	for (i = 0; i < wSHMNumCPUs; i++)
	{
		/* compare the resource name string to the own resource name */
		fIsOwnResource = (strcmp(pResName, (LZSCHAR*)pCurrent) == 0);

		/* jump over resource name string (32 bytes) */
		pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 32);

		/* read size of this CPU's data and set pointer to the data of the next CPU (to be used later) */
		pNextCPU = (LZSWORD*)(((LZSBYTE*)pCurrent) + *pCurrent);
		pCurrent++;

		/* check if the current CPU is the own resource */
		if (fIsOwnResource)
		{
			/* now set the CPU index */
			wSHMCPUIndex = i;
			logMsg("SHMCPUIndex: %d\n",wSHMCPUIndex,0,0,0,0,0);

			break;
		}

		/* continue with next CPU */
		pCurrent = pNextCPU;
	}

	#if 0
	if (fIsOwnResource == LZSFALSE)
	{
		/* error: own resource was not found */
		LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMInitErrorSetInfo, 0, 0, 0);
		return kLzsSHMInitErrorSetInfo;
	}
	#endif /* this error is deactivated, because there can be configurations where this CPU is not contained - e.g. if it does not use any SHM variable */

	return kLzsSuccess;
}

LZSBYTE SetOwnBuffers(LZSWORD* pStart)
{
	LZSWORD dwNumCPUs = 0;
	LZSWORD i = 0;
	LZSWORD k = 0;
	LZSWORD* pCurrent = pStart;
	LZSWORD* pNextCPU = LZSNULL;
	tPlcTaskDefTable* pTaskDefTab;
	LZSCHAR* pResName = LZSNULL;
	LZSBOOL fIsOwnResource = LZSFALSE;

	/* get name of the own resource */
	pTaskDefTab = LzsTdtGetAddr();
	if (pTaskDefTab != LZSNULL)
	{
		pResName = ((LZSCHAR*)pTaskDefTab) + STRUCT_OFFSET_RESNAME;
	}
	else
	{
		LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMInitErrorSetInfo, 0, 0, 0);
		return kLzsSHMInitErrorSetInfo;
	}

	/* read number of CPUs and advance pointer to the position behind the number of CPUs and SHM checksum (2 DWORDs) */
	dwNumCPUs = *((LZSDWORD*)pCurrent);
	pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 2 * sizeof(LZSDWORD));

	/* for all CPUs: find own resource and analyze configuration data */
	for (i = 0; i < dwNumCPUs; i++)
	{
		/* compare the resource name string to the own resource name */
		fIsOwnResource = (strcmp(pResName, (LZSCHAR*)pCurrent) == 0);

		/* jump over resource name string (32 bytes) */
		pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 32);

		/* read size of this CPU's data and set pointer to the data of the next CPU (to be used later) */
		pNextCPU = (LZSWORD*)(((LZSBYTE*)pCurrent) + *pCurrent);
		pCurrent++;

		/* check if the current CPU is the own resource */
		if (fIsOwnResource)
		{
			/* now read the section "owned segments" (next 13 words) to get the own segment numbers for all tasks of the current CPU */
			for (k = 0; k < NUM_TASKS; k++)
			{
				array_wSHMDCOwnBuffers[k] = pCurrent[k];
			}

			break;
		}

		/* continue with next CPU */
		pCurrent = pNextCPU;
	}

	#if 0
	if (fIsOwnResource == LZSFALSE)
	{
		/* error: own resource was not found */
		LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMInitErrorSetInfo, 0, 0, 0);
		return kLzsSHMInitErrorSetInfo;
	}
	#endif /* this error is deactivated, because there can be configurations where this CPU is not contained - e.g. if it does not use any SHM variable */

	return kLzsSuccess;
}

LZSBYTE SetSourceBuffers(LZSWORD* pStart)
{
	LZSWORD dwNumCPUs = 0;
	LZSWORD i = 0;
	LZSWORD k = 0;
	LZSWORD wNumEntries = 0;
	LZSWORD* pCurrent = pStart;
	LZSWORD* pNextCPU = LZSNULL;
	tPlcTaskDefTable* pTaskDefTab;
	LZSCHAR* pResName = LZSNULL;
	LZSBOOL fIsOwnResource = LZSFALSE;

	/* get name of the own resource */
	pTaskDefTab = LzsTdtGetAddr();
	if (pTaskDefTab != LZSNULL)
	{
		pResName = ((LZSCHAR*)pTaskDefTab) + STRUCT_OFFSET_RESNAME;
	}
	else
	{
		LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMInitErrorSetInfo, 0, 0, 0);
		return kLzsSHMInitErrorSetInfo;
	}

	/* read number of CPUs and advance pointer to the position behind the number of CPUs and SHM checksum (2 DWORDs) */
	dwNumCPUs = *((LZSDWORD*)pCurrent);
	pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 2 * sizeof(LZSDWORD));

	/* for all CPUs: find own resource and analyze configuration data */
	for (i = 0; i < dwNumCPUs; i++)
	{
		/* compare the resource name string to the own resource name */
		fIsOwnResource = (strcmp(pResName, (LZSCHAR*)pCurrent) == 0);

		/* jump over resource name string (32 bytes) */
		pCurrent = (LZSWORD*)(((LZSBYTE*)pCurrent) + 32);

		/* read size of this CPU's data and set pointer to the data of the next CPU (to be used later) */
		pNextCPU = (LZSWORD*)(((LZSBYTE*)pCurrent) + *pCurrent);
		pCurrent++;

		/* jump over section "owned segments" (next 13 words) */
		pCurrent += 13;

		/* check if the current CPU is the own resource */
		if (fIsOwnResource)
		{
			/* now read the section "used segments" (variable length) to get a list of source segment numbers for all tasks of the current CPU */
			for (k = 0; k < NUM_TASKS; k++)
			{
				wNumEntries = *pCurrent;

				if (wNumEntries > 0)
				{
					/* allocate and initialize list of source buffer numbers and pointers and list of locked source buffer numbers */
					array_pSHMDCSourceBuffers[k] = LZSMALLOC((wNumEntries + 1) * sizeof(LZSWORD));
					array_pSHMDCSourceBufferPointers[k] = LZSMALLOC((wNumEntries) * sizeof(LZSBYTE*));

					if (array_pSHMDCSourceBuffers[k] == LZSNULL || array_pSHMDCSourceBufferPointers[k] == LZSNULL)
					{
						LzsErrlogRegisterError(kLzsInternalError, kLzsNoMem, 0, 0, 0);
						return kLzsNoMem;
					}

					memcpy(array_pSHMDCSourceBuffers[k], pCurrent, (wNumEntries + 1) * sizeof(LZSWORD));
					memset(array_pSHMDCSourceBufferPointers[k], 0, (wNumEntries) * sizeof(LZSBYTE*));
				}
				else
				{
					array_pSHMDCSourceBuffers[k] = LZSNULL;
					array_pSHMDCSourceBufferPointers[k] = LZSNULL;
				}

				pCurrent += (wNumEntries + 1);
			}

			break;
		}

		/* continue with next CPU */
		pCurrent = pNextCPU;
	}

	#if 0
	if (fIsOwnResource == LZSFALSE)
	{
		/* error: own resource was not found */
		LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMInitErrorSetInfo, 0, 0, 0);
		return kLzsSHMInitErrorSetInfo;
	}
	#endif /* this error is deactivated, because there can be configurations where this CPU is not contained - e.g. if it does not use any SHM variable */

	return kLzsSuccess;
}

LZSBYTE SetBufferInfo()
{
	LZSBYTE* pData; /* pointer to buffer management data */
	LZSDWORD* pOffsets; /* pointer to buffer offsets list within buffer management data */
	tSHMDCBufferInfo* pBufferInfo;
	LZSWORD i;
	LZSWORD k;

	/* check if master is finished with initialization */
	if (CheckSHMConfigValid() == LZSTRUE)
	{
		/* allocate memory for buffer info structures */
		array_BufferInfo = LZSMALLOC((wLastSegNumSHMDCBuffers - FIRST_SEG_NUM_SHM_DC_BUFFERS + 1) * sizeof(tSHMDCBufferInfo));

		if (array_BufferInfo == LZSNULL)
		{
			LzsErrlogRegisterError(kLzsInternalError, kLzsNoMem, 0, 0, 0);
			return kLzsNoMem;
		}

		memset(array_BufferInfo, 0, (wLastSegNumSHMDCBuffers - FIRST_SEG_NUM_SHM_DC_BUFFERS + 1) * sizeof(tSHMDCBufferInfo));

		/* allocate memory for copies of read flags */
		pReadFlags_Copy = LZSMALLOC(wSHMNumCPUs * sizeof(LZSBYTE));

		if (pReadFlags_Copy == LZSNULL)
		{
			LzsErrlogRegisterError(kLzsInternalError, kLzsNoMem, 0, 0, 0);
			return kLzsNoMem;
		}

		memset(pReadFlags_Copy, 0xFF, wSHMNumCPUs * sizeof(LZSBYTE));

		/* set info for all buffers - this is done to speed up buffer management later, by avoiding shared memory accesses to fields which do not change after initialization */
		for (i = FIRST_SEG_NUM_SHM_DC_BUFFERS; i <= wLastSegNumSHMDCBuffers; i++)
		{
			pBufferInfo = &array_BufferInfo[i - FIRST_SEG_NUM_SHM_DC_BUFFERS];

			/* look up the management data for the current buffer */
			pData = pShmDCBuff_g + ((LZSDWORD*)pShmDCIndex_g)[i - FIRST_SEG_NUM_SHM_DC_BUFFERS]; /* get position of management data from index */
			pOffsets = (LZSDWORD*)(pData + (2 * sizeof(LZSWORD)));

			/* set values */
			pBufferInfo->wSegNum = i;
			pBufferInfo->wNumEntries = ((LZSWORD*)pData)[0];
			pBufferInfo->pLatestConsistent = &(((LZSWORD*)pData)[1]);
			pBufferInfo->pReadFlags = (LZSBYTE*)(pOffsets + pBufferInfo->wNumEntries); /* read flags are behind offsets, which are one pointer (DWORD size) each */
			pBufferInfo->pBuffers = LZSMALLOC(pBufferInfo->wNumEntries * sizeof(LZSBYTE*));
			pBufferInfo->wTaskFlags = 0;
			pBufferInfo->wUsedCopy = 0xFF;

			if (pBufferInfo->pBuffers == LZSNULL)
			{
				LzsErrlogRegisterError(kLzsInternalError, kLzsNoMem, 0, 0, 0);
				return kLzsNoMem;
			}

			memset(pBufferInfo->pBuffers, 0, pBufferInfo->wNumEntries * sizeof(LZSBYTE*));

			/* set buffer pointers */
			for (k = 0; k < pBufferInfo->wNumEntries; k++)
			{
				pBufferInfo->pBuffers[k] = pShmDCBuff_g + pOffsets[k];
			}
		}
	}
	else
	{
		/* error: master not ready or different project loaded */
		return kLzsSHMChecksumError;
	}

	return kLzsSuccess;
}

#ifdef SCHEDULER_DEBUG
LZSWORD check1 = 0;
LZSWORD check2 = 0;
#endif

#undef DEBUG_SHMDC_WRITEBUFFER
#undef DEBUG_SHMDC_READBUFFERS

void SetSHMDCWriteBuffer(LZSWORD wTask)
{
	/* variables are uninitialized for performance reasons; they are all set before use anyway */
	LZSWORD i, j;
	LZSBYTE* pBuffer;
	LZSWORD wOwnBuffer;
	LZSWORD wLatestConsistent;
	LZSBOOL fInUse;
	tSHMDCBufferInfo* pBufferInfo;

	#ifdef SCHEDULER_DEBUG
	if (check1 & (0x0001 << wTask))
	{
		logMsg("Task %d DOUBLE SetSHMDCWriteBuffer!!!\n",wTask,0,0,0,0,0);
	}
	check1 |= (0x0001 << wTask);
	#endif

	wOwnBuffer = array_wSHMDCOwnBuffers[wTask];

	/* check if the current task uses a shared memory data consistency write buffer at all (else: nothing to do) */
	if (wOwnBuffer != 0)
	{
		#ifdef ENABLE_PERFORMANCE_MONITORING_CUSTOM
		LzsEnvStartPerformanceMeasurement(pPerformanceDataCustom2);
		#endif

		pBufferInfo = &array_BufferInfo[wOwnBuffer - FIRST_SEG_NUM_SHM_DC_BUFFERS];
		pBuffer = LZSNULL;

		/* find a buffer copy which is not being used for reading and which is not the latest consistent */
		wLatestConsistent = array_wSHMDCWriteBuffer[wTask]; /* optimization: take LC value from local data to save one SHM read*/
		/* old code: wLatestConsistent = *(pBufferInfo->pLatestConsistent); */

		#ifdef DEBUG_SHMDC_WRITEBUFFER
		logMsg("==== Set write buffer: own=%d, lc=%d ====\n",wOwnBuffer,wLatestConsistent,0,0,0,0);
		#endif

		/* copy read flags to local memory (optimization) */
		memcpy(pReadFlags_Copy, pBufferInfo->pReadFlags, wSHMNumCPUs * sizeof(LZSBYTE));

		for (i = 0; i < pBufferInfo->wNumEntries; i++)
		{
			fInUse = LZSFALSE;

			if (i != wLatestConsistent)
			{
				#ifdef DEBUG_SHMDC_WRITEBUFFER
				logMsg("Flags for copy %d:\n",i,0,0,0,0,0);
				#endif

				/* check read flags to determine if buffer is in use */
				for (j = 0; j < wSHMNumCPUs; j++)
				{
					#ifdef DEBUG_SHMDC_WRITEBUFFER
					logMsg("%d\n",pReadFlags_Copy[j],0,0,0,0,0);
					#endif

					if (pReadFlags_Copy[j] == i)
					{
						/* buffer is in use */
						fInUse = LZSTRUE;
						break;
					}
				}
			}
			else
			{
				fInUse = LZSTRUE;
			}

			if (!fInUse)
			{
				#ifdef DEBUG_SHMDC_WRITEBUFFER
				logMsg("Using copy %d\n",i,0,0,0,0,0);
				#endif

				/* this buffer must be set */
				/* note: it is not necessary to lock the buffer, because readers will only use the latest consistent buffer; the owning task is the only task writing to the buffer; the owning task will not be started again before it is finished */
				pBuffer = pBufferInfo->pBuffers[i];

				/* the buffer number must be saved, so that "latest consistent" can be set after the cycle */
				array_wSHMDCWriteBuffer[wTask] = i;

				break;
			}
		}

		if (pBuffer == LZSNULL)
		{
			#ifdef SCHEDULER_DEBUG
			logMsg("Error getting SHM write buffer for task %d\n",wTask,0,0,0,0,0);
			for (i = 0; i < wNumEntries; i++)
			{
				logMsg("pLocks[%d]=%d, wLatestConsistent=%d\n",i,pLocks[i],wLatestConsistent,0,0,0);
			}
			#endif

			/* RUNTIME ERROR */
			LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMDCBufferError, wTask, 0, 0);
		}
		else
		{
			/* set the buffer by making the entry in the segment table(s) */
			if (pTargetConfig_g->dwUseBLCode != 0)
			{
				/* in case of BL code being executed, it is enough to set the pointer in the program 0 segment table */
				pSegmentTables_l[0].pSegTable[wOwnBuffer].m_pPrimarySeg = pBuffer; /* for watching */
				pSegmentTables2_l[wTask].pSegTable[wOwnBuffer].m_pPrimarySeg = pBuffer;
			}
			else
			{
				/* if not BL code is executed, pointers must be set in the segment tables of all programs from 0 to <n> */
				/* also in program 0 to enable correct watching; watch requests for data consistency variables always use program 0; see LzsWatchAddMulInstructionCont() */
				for (i = 0; i < wNumberOfPrograms_g; i++)
				{
					pSegmentTables_l[0].pSegTable[wOwnBuffer].m_pPrimarySeg = pBuffer; /* for watching */
					pSegmentTables2_l[i * NUM_TASKS + wTask].pSegTable[wOwnBuffer].m_pPrimarySeg = pBuffer;
				}
			}
		}

		#ifdef ENABLE_PERFORMANCE_MONITORING_CUSTOM
		LzsEnvStopPerformanceMeasurement(pPerformanceDataCustom2);
		#endif
	}
}

void SetSHMDCReadBuffers(LZSWORD wTask)
{
	/* variables are uninitialized for performance reasons; they are all set before use anyway */
	LZSWORD i;
	#ifdef DEBUG_SHMDC_READBUFFERS
	LZSWORD j;
	#endif
	LZSWORD k;
	LZSWORD* pSourceBuffers;
	LZSBYTE** pSourceBufferPointers;
	tSHMDCBufferInfo* pBufferInfo;
	volatile LZSWORD* pLatestConsistent;
	LZSWORD wLatestConsistent_Begin;
	LZSWORD wLatestConsistent_End;
	LZSWORD wNumRetries;

	#ifdef SCHEDULER_DEBUG
	if (check2 & (0x0001 << wTask))
	{
		logMsg("Task %d DOUBLE SetSHMDCReadBuffers!!!\n",wTask,0,0,0,0,0);
	}
	check2 |= (0x0001 << wTask);
	#endif

	pSourceBuffers = array_pSHMDCSourceBuffers[wTask];

	/* check if the current task uses shared memory data consistency read buffers at all (else: nothing to do) */
	if (pSourceBuffers != LZSNULL)
	{
		#ifdef ENABLE_PERFORMANCE_MONITORING_CUSTOM
		LzsEnvStartPerformanceMeasurement(pPerformanceDataCustom3);
		#endif

		pSourceBufferPointers = array_pSHMDCSourceBufferPointers[wTask];

		#ifdef DEBUG_SHMDC_READBUFFERS
		logMsg("---- Set read buffers: ----\n",0,0,0,0,0,0);
		#endif

		/* for all source buffers: find a buffer copy to use */
		for (i = 1; i <= pSourceBuffers[0]; i++)
		{
			pBufferInfo = &array_BufferInfo[pSourceBuffers[i] - FIRST_SEG_NUM_SHM_DC_BUFFERS];

			#ifdef DEBUG_SHMDC_READBUFFERS
			logMsg("Buffer %d:\n",pSourceBuffers[i],0,0,0,0,0);

			logMsg("Flags old:\n",0,0,0,0,0,0);
			for (j = 0; j < wSHMNumCPUs; j++)
			{
				logMsg("%d\n",pBufferInfo->pReadFlags[j],0,0,0,0,0);
			}
			#endif

			if (pBufferInfo->wUsedCopy == 0xFF)
			{
				/* no other task on this CPU is using the buffer - use latest consistent copy */

				/* get pointer to LC value */
				pLatestConsistent = pBufferInfo->pLatestConsistent;

				/* read LC value from shared memory */
				wLatestConsistent_Begin = *pLatestConsistent;

				/* loop as long as there is no valid selection of a buffer copy to use */
				wNumRetries = 0;
				while (1)
				{
					/* lock the buffer copy (in shared memory) */
					pBufferInfo->pReadFlags[wSHMCPUIndex] = wLatestConsistent_Begin;

					/* read LC value again to verify that the owning task of this buffer did not change it in the meantime (this could result in both reader and writer using the same buffer copy at the same time!) */
					wLatestConsistent_End = *pLatestConsistent;

					if (wLatestConsistent_Begin != wLatestConsistent_End)
					{
						wNumRetries++;

						/* log the error, if that happens more than once per cycle (but no error stop) */
						if (wNumRetries > 1)
						{
							LzsErrlogRegisterError(kLzsInternalError2, kLzsSHMDCLCError, wTask, pBufferInfo->wSegNum, 0);
						}

						/* prepare next try, using the last read LC value */
						wLatestConsistent_Begin = wLatestConsistent_End;
					}
					else
					{
						/* set used buffer copy in local data */
						pBufferInfo->wUsedCopy = wLatestConsistent_Begin;

						break;
					}
				}
			}
			/* else: another task on this CPU is already using this buffer - use the same copy; keep pBufferInfo->wUsedCopy unchanged; no need to lock the buffer again in shared memory */

			/* add task flag to buffer info */
			pBufferInfo->wTaskFlags |= (0x0001 << wTask);

			/* this buffer must be set */
			pSourceBufferPointers[i - 1] = pBufferInfo->pBuffers[pBufferInfo->wUsedCopy];

			#ifdef DEBUG_SHMDC_READBUFFERS
			logMsg("Using copy %d\n",pBufferInfo->wUsedCopy,0,0,0,0,0);

			logMsg("Flags new:\n",0,0,0,0,0,0);
			for (j = 0; j < wSHMNumCPUs; j++)
			{
				logMsg("%d\n",pBufferInfo->pReadFlags[j],0,0,0,0,0);
			}
			#endif
		}

		#ifdef ENABLE_PERFORMANCE_MONITORING_CUSTOM
		LzsEnvStopPerformanceMeasurement(pPerformanceDataCustom3);
		#endif

		/* for all source buffers: set selected buffer copy for use in application execution - this is done in a separate loop to minimize the bus lock times */
		for (i = 1; i <= pSourceBuffers[0]; i++)
		{
			/* set the buffer by making the entry in the segment table(s) */
			if (pTargetConfig_g->dwUseBLCode != 0)
			{
				/* in case of BL code being executed, it is enough to set the pointer in the program 0 segment table */
				pSegmentTables_l[0].pSegTable[pSourceBuffers[i]].m_pPrimarySeg = pSourceBufferPointers[i - 1]; /* for watching */
				pSegmentTables2_l[wTask].pSegTable[pSourceBuffers[i]].m_pPrimarySeg = pSourceBufferPointers[i - 1];
			}
			else
			{
				/* if not BL code is executed, pointers must be set in the segment tables of all programs from 0 to <n> */
				/* also in program 0 to enable correct watching; watch requests for data consistency variables always use program 0; see LzsWatchAddMulInstructionCont() */
				for (k = 0; k < wNumberOfPrograms_g; k++)
				{
					pSegmentTables_l[0].pSegTable[pSourceBuffers[k]].m_pPrimarySeg = pSourceBufferPointers[i - 1]; /* for watching */
					pSegmentTables2_l[k * NUM_TASKS + wTask].pSegTable[pSourceBuffers[k]].m_pPrimarySeg = pSourceBufferPointers[i - 1];
				}
			}
		}
	}
}

void PublishSHMDCWriteBuffer(LZSWORD wTask)
{
	/* variables are uninitialized for performance reasons; they are all set before use anyway */
	LZSWORD wOwnBuffer;
	tSHMDCBufferInfo* pBufferInfo;

	#ifdef SCHEDULER_DEBUG
	if (!(check1 & (0x0001 << wTask)))
	{
		logMsg("Task %d DOUBLE PublishSHMDCWriteBuffer!!!\n",wTask,0,0,0,0,0);

		logMsg("%dx SYS\t%dx T1S\t%dx T2S\t%dx T3S\t%dx T4S\t%dx T5S\n",SYSCounter,T1SCounter,T2SCounter,T3SCounter,T4SCounter,T5SCounter);
		logMsg("\t%dx T1N\t%dx T2N\t%dx T3N\t%dx T4N\t%dx T5N\t%d ticks\n",T1NCounter,T2NCounter,T3NCounter,T4NCounter,T5NCounter,TicksCounter);
		logMsg("task_Status_sys=0x%x, task_Status_nor=0x%x\n",task_Status_sys,task_Status_nor,0,0,0,0);
	}
	check1 &= ~(0x0001 << wTask);
	#endif

	wOwnBuffer = array_wSHMDCOwnBuffers[wTask];

	/* check if the current task uses a shared memory data consistency write buffer at all (else: nothing to do) */
	if (wOwnBuffer != 0)
	{
		#ifdef ENABLE_PERFORMANCE_MONITORING_CUSTOM
		LzsEnvStartPerformanceMeasurement(pPerformanceDataCustom4);
		#endif

		pBufferInfo = &array_BufferInfo[wOwnBuffer - FIRST_SEG_NUM_SHM_DC_BUFFERS];

		/* set latest consistent */
		*(pBufferInfo->pLatestConsistent) = array_wSHMDCWriteBuffer[wTask];

		#ifdef DEBUG_SHMDC_WRITEBUFFER
		logMsg("==== Publish write buffer: own=%d, lc_new=%d ====\n",wOwnBuffer,*(pBufferInfo->pLatestConsistent),0,0,0,0);
		#endif

		#ifdef ENABLE_PERFORMANCE_MONITORING_CUSTOM
		LzsEnvStopPerformanceMeasurement(pPerformanceDataCustom4);
		#endif
	}
}

void UnlockSHMDCReadBuffers(LZSWORD wTask)
{
	/* variables are uninitialized for performance reasons; they are all set before use anyway */
	LZSWORD i;
	#ifdef DEBUG_SHMDC_READBUFFERS
	LZSWORD j;
	#endif
	LZSWORD* pSourceBuffers;
	tSHMDCBufferInfo* pBufferInfo;

	#ifdef SCHEDULER_DEBUG
	if (!(check2 & (0x0001 << wTask)))
	{
		logMsg("Task %d DOUBLE UnlockSHMDCReadBuffers!!!\n",wTask,0,0,0,0,0);

		logMsg("%dx SYS\t%dx T1S\t%dx T2S\t%dx T3S\t%dx T4S\t%dx T5S\n",SYSCounter,T1SCounter,T2SCounter,T3SCounter,T4SCounter,T5SCounter);
		logMsg("\t%dx T1N\t%dx T2N\t%dx T3N\t%dx T4N\t%dx T5N\t%d ticks\n",T1NCounter,T2NCounter,T3NCounter,T4NCounter,T5NCounter,TicksCounter);
		logMsg("task_Status_sys=0x%x, task_Status_nor=0x%x\n",task_Status_sys,task_Status_nor,0,0,0,0);
	}
	check2 &= ~(0x0001 << wTask);
	#endif

	pSourceBuffers = array_pSHMDCSourceBuffers[wTask];

	/* check if the current task uses shared memory data consistency read buffers at all (else: nothing to do) */
	if (pSourceBuffers != LZSNULL)
	{
		#ifdef ENABLE_PERFORMANCE_MONITORING_CUSTOM
		LzsEnvStartPerformanceMeasurement(pPerformanceDataCustom5);
		#endif

		#ifdef DEBUG_SHMDC_READBUFFERS
		logMsg("---- Unlock read buffers: ----\n",0,0,0,0,0,0);
		#endif

		/* for all source buffers: unlock, if not used by another task on this CPU */
		for (i = 1; i <= pSourceBuffers[0]; i++)
		{
			pBufferInfo = &array_BufferInfo[pSourceBuffers[i] - FIRST_SEG_NUM_SHM_DC_BUFFERS];

			#ifdef DEBUG_SHMDC_READBUFFERS
			logMsg("Buffer %d:\n",pSourceBuffers[i],0,0,0,0,0);

			logMsg("Flags old:\n",0,0,0,0,0,0);
			for (j = 0; j < wSHMNumCPUs; j++)
			{
				logMsg("%d\n",pBufferInfo->pReadFlags[j],0,0,0,0,0);
			}
			#endif

			/* remove task flag from buffer info */
			pBufferInfo->wTaskFlags &= ~(0x0001 << wTask);

			if (pBufferInfo->wTaskFlags == 0)
			{
				/* this task is the last task on this CPUs using this buffer - set it to unused */
				pBufferInfo->wUsedCopy = 0xFF;

				/* unlock the buffer copy */
				pBufferInfo->pReadFlags[wSHMCPUIndex] = 0xFF; /* 0xFF because 0 is a valid buffer number which can be in use */
			}

			#ifdef DEBUG_SHMDC_READBUFFERS
			logMsg("Flags new:\n",0,0,0,0,0,0);
			for (j = 0; j < wSHMNumCPUs; j++)
			{
				logMsg("%d\n",pBufferInfo->pReadFlags[j],0,0,0,0,0);
			}
			#endif
		}

		#ifdef ENABLE_PERFORMANCE_MONITORING_CUSTOM
		LzsEnvStopPerformanceMeasurement(pPerformanceDataCustom5);
		#endif
	}
}
#endif

#ifdef USE_DATA_CONSISTENCY
void SetDCBuffers(LZSWORD wTask)
{
	/* variables are uninitialized for performance reasons; they are all set before use anyway */
	int i;
	int k;
	LZSBYTE* pBuffer = LZSNULL;

	if (fOnlyOneTaskUsed)
	{
		/* skip in case there is only one task used - optimization, mainly targeted at MS applications which usually have only one task, thus there are no transfers relevant for DC */
		return;
	}

	/* NOTE: no task lock used here, because this function is called from the system mode task, which has a task lock anyway */

	/* lock "latest consistent" buffers of all other tasks, save their numbers, and set the buffers */
	/* saving their numbers is necessary in order to know which buffers to unlock later; because: during the task cycle of the current task, on of the other tasks may interrupt and set another buffer as the latest consistent */
	for (i = 0; i < NUM_TASKS; i++)
	{
		if (i == wTask) continue;

		#ifdef SCHEDULER_DEBUG
		if (array_pBufferLocks[i][bLatestConsistent[i]] & (0x0001 << wTask))
		{
			logMsg("Task %d (task start) buffer %d already locked! value: 0x%x\n",wTask,i,array_pBufferLocks[i][bLatestConsistent[i]],0,0,0);
		}
		#endif

		array_pBufferLocks[i][bLatestConsistent[i]] |= (0x0001 << wTask);
		bLockedBuffers[wTask][i] = bLatestConsistent[i];

		/* set the buffer by making the entry in the segment table(s) */
		if (pTargetConfig_g->dwUseBLCode != 0)
		{
			/* in case of BL code being executed, it is enough to set the pointer in the program 0 segment table */
			pSegmentTables_l[0].pSegTable[FIRST_SEG_NUM_DC_BUFFERS + i].m_pPrimarySeg = array_pBuffers[i][bLatestConsistent[i]]; /* for watching */
			pSegmentTables2_l[wTask].pSegTable[FIRST_SEG_NUM_DC_BUFFERS + i].m_pPrimarySeg = array_pBuffers[i][bLatestConsistent[i]];
		}
		else
		{
			/* if not BL code is executed, pointers must be set in the segment tables of all programs from 0 to <n> */
			/* also in program 0 to enable correct watching; watch requests for data consistency variables always use program 0; see LzsWatchAddMulInstructionCont() */
			for (k = 0; k < wNumberOfPrograms_g; k++)
			{
				pSegmentTables_l[0].pSegTable[FIRST_SEG_NUM_DC_BUFFERS + i].m_pPrimarySeg = array_pBuffers[i][bLatestConsistent[i]]; /* for watching */
				pSegmentTables2_l[k * NUM_TASKS + wTask].pSegTable[FIRST_SEG_NUM_DC_BUFFERS + i].m_pPrimarySeg = array_pBuffers[i][bLatestConsistent[i]];
			}
		}
	}

	/* get write buffer for this task by finding a buffer copy which is not locked and not the latest consistent */
	for (i = 0; i < (NUM_TASKS + 1 - wTask); i++)
	{
		if (array_pBufferLocks[wTask][i] == 0 && i != bLatestConsistent[wTask])
		{
			/* this buffer must be set */
			/* note: it is not necessary to lock the buffer, because readers will only use the latest consistent buffer; the owning task is the only task writing to the buffer; the owning task will not be started again before it is finished */
			pBuffer = array_pBuffers[wTask][i];

			/* the buffer number must be saved, so that "latest consistent" can be set after the cycle */
			bWriteBuffer[wTask] = i;

			break;
		}
	}

	if (pBuffer == LZSNULL)
	{
		/* RUNTIME ERROR */
		LzsErrlogRegisterError(kLzsInternalError, kLzsDCBufferError, wTask, 0, 0);

		/* DUMP */
		/*logMsg("Task %d write buffer error\n",wTask,0,0,0,0,0);*/
		/*logMsg("bLatestConsistent[%d]=%d\n",wTask,bLatestConsistent[wTask],0,0,0,0);
		for (i = 0; i < (NUM_TASKS + 1 - wTask); i++)
		{
			logMsg("array_pBufferLocks[%d][%d]=%d; pointer: 0x%x\n",wTask,i,array_pBufferLocks[wTask][i],array_pBuffers[wTask][i],0,0);
		}*/
	}

	/* set the buffer by making the entry in the segment table(s) */
	if (pTargetConfig_g->dwUseBLCode != 0)
	{
		/* in case of BL code being executed, it is enough to set the pointer in the program 0 segment table */
		pSegmentTables_l[0].pSegTable[FIRST_SEG_NUM_DC_BUFFERS + wTask].m_pPrimarySeg = pBuffer; /* for watching */
		pSegmentTables2_l[wTask].pSegTable[FIRST_SEG_NUM_DC_BUFFERS + wTask].m_pPrimarySeg = pBuffer;
	}
	else
	{
		/* if not BL code is executed, pointers must be set in the segment tables of all programs from 0 to <n> */
		/* also in program 0 to enable correct watching; watch requests for data consistency variables always use program 0; see LzsWatchAddMulInstructionCont() */
		for (k = 0; k < wNumberOfPrograms_g; k++)
		{
			pSegmentTables_l[0].pSegTable[FIRST_SEG_NUM_DC_BUFFERS + wTask].m_pPrimarySeg = pBuffer; /* for watching */
			pSegmentTables2_l[k * NUM_TASKS + wTask].pSegTable[FIRST_SEG_NUM_DC_BUFFERS + wTask].m_pPrimarySeg = pBuffer;
		}
	}
}

void UnlockDCBuffers(LZSWORD wTask)
{
	/* variables are uninitialized for performance reasons; they are all set before use anyway */
	int i;

	if (fOnlyOneTaskUsed)
	{
		/* skip in case there is only one task used - optimization, mainly targeted at MS applications which usually have only one task, thus there are no transfers relevant for DC */
		return;
	}

	LOCK_TASK_SWITCH();

	/* set latest consistent buffer for the task */
	bLatestConsistent[wTask] = bWriteBuffer[wTask];

	/* unlock all locked read buffers for the task */
	for (i = 0; i < NUM_TASKS; i++)
	{
		if (i == wTask) continue;

		#ifdef SCHEDULER_DEBUG
		if (!(array_pBufferLocks[i][bLockedBuffers[wTask][i]] & (0x0001 << wTask)))
		{
			logMsg("Task %d (task end) buffer %d is not locked! value: 0x%x\n",wTask,i,array_pBufferLocks[i][bLockedBuffers[wTask][i]],0,0,0);
		}
		#endif

		array_pBufferLocks[i][bLockedBuffers[wTask][i]] &= ~(0x0001 << wTask);
	}

	UNLOCK_TASK_SWITCH();
}
#endif

/* EOF */
