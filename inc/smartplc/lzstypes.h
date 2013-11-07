#ifndef _LZSTYPES_H_
#define _LZSTYPES_H_

/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

/*--------------------------------------------------*/
/* TYPE:tIpBreakPointType                           */
/*--------------------------------------------------*/
/* Action to be performed */
#define		kIpBreakPointStop		0x0000		/* Stop execution of this task until user command */
#define		kIpBreakPointSignal		0x0001		/* Signal Breakpoint was reached but don't stop execution */
#define     kIpBreakPointStopAll	0x0002		/* Stop execution of all tasks until user command */

/* Scope of Breakpoint */
#define		kIpBreakPointInst		0x0100		/* Instance specific Breakpoint -> Stops only in this Instance */
#define		kIpBreakPointType		0x0200		/* Type specific Breakpoint 	-> Stops in all Instances */
	
typedef LZSWORD tIpBreakPointType;



/*--------------------------------------------------*/
/* TYPE:tIpBreakPointEntry                          */
/*       STRUCT to control breakpoints				*/
/*--------------------------------------------------*/
typedef packed struct
{
	tPlcPgmNr			wPgmNr;		/* Program of breakpoint */
	tPlchInst			wInst;		/* Inst of breakpoint */
	tPlcOffset			wIPOffset;	/* Offset of breakpoint */
	tIpBreakPointType   Type;		/* Type of breakpoint */
	LZSWORD				wID;		/* ID to reference this breakpoint */
	tPlcSegNr			wCode;		/* code segment number */
	
} tIpBreakPointEntry;

typedef packed struct
{
    tIpBreakPointEntry BreakPoint;     /* breakpoint */
    LZSBYTE            bOriginalCode;  /* previous code */
    LZSBYTE LZSFAR*    RegCS;          /* base address of code segment */
    LZSBYTE LZSFAR*    RegDS;          /* base address of data segment */
    
    LZSDWORD           dwCount;        /* Count how often breakpoint was reached */
    LZSDWORD           dwTime;         /* Time in OEM defined units, when breakpoint was reached last time */
    
    LZSBYTE            fGo;            /* don't stop, proceed */    
    LZSBYTE            fTuiNotified;   /* Callback was send */

} tIpBreakPoint;



/*--------------------------------------------------------------------------- */
/* Type definitions */
/*--------------------------------------------------------------------------- */

/* Marker for RTS status */
typedef LZSDWORD  tLzsStatus;

/* Definition of error categories */
typedef enum
{
	kLzsInitialError            = 0x00,
	kLzsTaskAdministrationError = 0x01,
	kLzsHardwareMonitoringError = 0x02,
	kLzsUserError               = 0x03,
	kLzsCommunicationError      = 0x04,
	kLzsRuntimeError            = 0x05,
	kLzsInternalError           = 0x06

} tLzsErrorCategory;

/* This definition must be adapted, if tLzsErrorCategory is changed! */
#define NUM_ERROR_CATEGORIES 7

/* Definition of error codes */
typedef enum
{
	kLzsSuccess                 = 0x00, /* everything OK */
	
	/* INTERNAL ERRORS - 0xA0..0xFF */
	kLzsGeneralError            = 0xFF, /* general error */
	kLzsUnknownCmd              = 0xFE, /* invalid control command (sent by OpenPCS) */
	kLzsModeErr                 = 0xFD, /* operation not allowed in current mode */
	kLzsNoMem                   = 0xFC, /* out of memory */
	kLzsNetError                = 0xFB, /* general network error */
	kLzsNetRecSizeError         = 0xFA, /* network: accepted receipt shipment too small */
	kLzsNoWatchTabEntry         = 0xF9, /* no free watch ID available */
	kLzsModeConflict            = 0xF8, /* mode conflict (command not allowed in current mode - run/stop switch) */
	kLzsNetErrorLastSession     = 0xF7, /* network error (last connection) */
	kLzsInvalidPgm              = 0xF6, /* no valid program available */
	kLzsInvalidPgmNr            = 0xF5, /* program number invalid */
	kLzsInvalidSegNr            = 0xF4, /* segment number invalid */
	kLzsInvalidSegType          = 0xF3, /* segment type invalid */
	kLzsSegDuplicate            = 0xF2, /* segment exists already  */
	kLzsDwnldError              = 0xF1, /* download incomlete/logical error */
	kLzsConfigError             = 0xF0, /* configuration error/wrong program */
	kLzsUplErrorNotEnabled      = 0xEF, /* segment not found on upload */
	kLzsMemoryCorrupted         = 0xEE, /* pointers in IECMEMORY out of the valid range */
	kLzsIpExecError             = 0xED, /* error at call of interpreter */
	kLzsNcExecError             = 0xEC, /* error at execution of native code */
	kLzsInvalidFilePath         = 0xEB, /* invalid file path when downloading raw files */
	kLzsNotValidInRunState      = 0xEA, /* action not valid in running state of LZS */
	kLzsHistNoFreeEntry         = 0xE9, /* no free hist table entry available */
	kLzsHistInvalidID           = 0xE8, /* invalid hist table ID on delete or get */
	kLzsNoBreakpointError       = 0xE7,
	kLzsMaxBreakpointsError     = 0xE6,
	kLzsBreakpointNotFoundError = 0xE5,
	kLzsDwlTDTError             = 0xE4,
	kLzsMoveSegmentError        = 0xE3,
	kLzsDwlNoLinkerTableError   = 0xE2,
	kLzsDwlAlignmentError       = 0xE1,
	kLzsDwlDSSizeError          = 0xE0,
	kLzsDwlReadSegAddrError     = 0xDF,
	kLzsDwlResourceReplaceError = 0xDE,
	kLzsDwlNoSegTabError        = 0xDD,
	kLzsDwlProcDataError        = 0xDC,
	kLzsDwlNoCopyTableError     = 0xDB,
	kLzsHistMaxHistError        = 0xDA,
	kLzsHistSizeError           = 0xD9,
	kLzsHistMutexError          = 0xD8,
	kLzsHistMaxHistSettingError = 0xD7,
	kLzsRawFileWriteError       = 0xD6, /* writing of raw file failed (disk full, write protected, etc.) */
	kLzsRawFileReadError        = 0xD5, /* reading of raw file failed (file does not exist, no permission, etc.) */
	kLzsRawFileDeleteError      = 0xD4, /* error deleting raw file */
	kLzsForceTypeError          = 0xD3,
	kLzsWatchTypeError          = 0xD2,
	kLzsWatchDeleteError        = 0xD1,
	kLzsProcImgError            = 0xD0,
	kLzsLoginStatusError        = 0xCF,
	kLzsLogoutStatusError       = 0xCE,
	kLzsWriteSegAddrError       = 0xCD,
	kLzsSaveTempSegError        = 0xCC,
	kLzsIStackError             = 0xCB,
	kLzsIStackError2            = 0xCA,
	kLzsPersCRCFailed           = 0xC9,
	kLzsPersVersionMismatch     = 0xC8,
	kLzsPersSaveError           = 0xC7,

	/* error code for data consistency buffer management */
	kLzsDCBufferError           = 0xC6, /* error getting write buffer */

	/* error code for no hardware configuration segment */
	kLzsNoHWConfig              = 0xC5,
	
	/* error codes for BL code */
	kLzsBLCodeGenError1         = 0xC4, /* unsupported UCode instruction */
	kLzsBLCodeGenError2         = 0xC3, /* invalid FB call */
	kLzsBLCodeGenError3         = 0xC2, /* unsupported combination of UCode instructions */
	kLzsBLExecError             = 0xC1, /* runtime error during execution */
	
	/* error codes for shared memory data consistency */
	kLzsNoSHMConfig             = 0xC0, /* configuation segment not found */
	kLzsSHMConfigError          = 0xBF, /* error in configuration, e.g. segments not found, ... */
	kLzsSHMInitError            = 0xBE, /* error during creation or initialization of the memory (master) */
	kLzsSHMInitErrorSlave       = 0xBD, /* error connecting to the memory (slave) */
	kLzsSHMInitErrorSetInfo     = 0xBC, /* error setting up CPU-local information */
	kLzsSHMDCBufferError        = 0xBB, /* error getting write buffer */
	kLzsSHMDCSizeError          = 0xBA, /* size of shared memory is too small */
	kLzsSHMDCChecksumError      = 0xB9, /* shared memory configuration from master and slave(s) is different */

	kLzsInitModeExecError       = 0xB8, /* error when executing init mode */
	kLzsWaitTasksError          = 0xB7, /* operation not possible because tasks are still running */
	
	/* until 0xA0: reserved for future internal error codes */

	/* RUNTIME ERRORS - 0x80..0x9F - defined in tIpErrorCode, ip_def.h */

	/* COMMUNICATION ERRORS - 0x70..0x7F */
	kLzsCommunicationError1     = 0x7F,
	kLzsCommunicationError2     = 0x7E,
	kLzsCommunicationError3     = 0x7D,
	kLzsCommunicationError4     = 0x7C,
	kLzsCommunicationError5     = 0x7B,
	kLzsCommunicationError6     = 0x7A,
	kLzsCommunicationError7     = 0x79,
	kLzsCommunicationError8     = 0x78,
	kLzsCommunicationError9     = 0x77,
	kLzsCommunicationError10    = 0x76,
	kLzsCommunicationError11    = 0x75,
	kLzsCommunicationError12    = 0x74,
	kLzsCommunicationError13    = 0x73,
	kLzsCommunicationError14    = 0x72,
	kLzsCommunicationError15    = 0x71,
	kLzsCommunicationError16    = 0x70,

	/* USER ERRORS have a separate number range, only defined on user application level */

	/* HARDWARE MONITORING ERRORS - 0x60..0x6F */
	/* to do later */

	/* TASK ADMINISTRATION ERRORS - 0x50..0x5F */
	kLzsFatalCycleError         = 0x5F, /* fatal cycle error (task cycle length exceeded in <n> consecutive cycles) */
	kLzsSingleCycleError        = 0x5E, /* single cycle error (task cycle length exceeded once) */

	/* INITIAL ERRORS - 0x40..0x4F */
	kLzsInitMemoryError         = 0x4F, /* application memory not allocated */
	kLzsInitSHMError            = 0x4E, /* shared memory not allocated/connected */
	kLzsInitCommError           = 0x4D, /* communication not initialized */
	kLzsInitTasksError          = 0x4C, /* tasks and/or background services not started */
	kLzsInitErrLogError         = 0x4B, /* error log not initialized */
	kLzsInitRestoreError        = 0x4A  /* persistent application not restored */

} tLzsErrorCode;

/* NOTE: if tLzsErrorCode is changed, the switch block in errlog.c, function LzsErrlogRegisterError() must be checked for completeness! */

/* control commands of the IDE for the PLC */
typedef enum
{
   kLzsCmdLogin         = 0x01,     /* command "Login" */
   kLzsCmdLogout        = 0x02,     /* command "Logout" */
   kLzsCmdReset         = 0x03,     /* command "Reset" */
   kLzsCmdDwlResource   = 0x04,     /* command "Download Resource" */
   kLzsCmdDwlProgram    = 0x05,     /* command "Download Program" */
   kLzsCmdDwlSegment    = 0x06,     /* command "Download Segment" */
   kLzsCmdSetState      = 0x07,     /* command "Set State" */
   kLzsCmdGetResVer     = 0x08,     /* command "Get Resource Version" */
   kLzsCmdGetPlcVer     = 0x09,     /* command "Get Firmware Version" */
   kLzsCmdDiscradWatch  = 0x0A,     /* command "Discard Watch Table" */
   kLzsCmdEnableWatch   = 0x0B,     /* command "Enable Watching" */
   kLzsCmdAddWatchInstr = 0x0C,     /* command "Add Watch Instruction" */
   kLzsCmdSetVariable   = 0x0D,     /* command "Set Variable" */
   kLzsCmdGetErrorInf   = 0x0E,     /* command "Get Error Information" */
   kLzsCmdUplGetSegInf  = 0x0F,     /* command "Get Segment Information" */
   kLzsCmdUplGetSegData = 0x10,     /* command "Get Segment Data" */
   kLzsCmdStartPflow    = 0x11,     /* command "Start Powerflow" */
   kLzsCmdStopPflow     = 0x12,     /* command "Stop  Powerflow" */
   kLzsCmdDwlSingleSegment = 0x13,    /* command   "download configuration data"*/
   kLzsCmdForceVariable   = 0x14,     /* command "Force Variable" */
   kLzsCmdDisableForceVariable   = 0x15,     /* command "Force Variable" */
   kLzsCmdDelWatchInstr = 0x16,     /* command "Del Watch Instruction" */   
   kLzsCmdAddMulWatchInstr = 0x17,  /* command "Add Multiple Watch Instruction" */
   kLzsCmdDwlMultiSegment = 0x18,   /* download multiple segments at once*/
   
   kLzsCmdRequestData   = 0x20,     /* command "Request Data" (to Watch) */
   kLzsCmdDwlWithoutStop = 0x21,    /* command "Download data (Resource/Program/Segments) while PLC is running */
   
   kLzsCmdHistAddElem    = 0x22,        /* command "Variable History - add element"        */
   kLzsCmdHistDelElem    = 0x23,        /* command "Variable History - delete element"    */
   kLzsCmdHistGetRange    = 0x24,        /* command "Variable History - get data"    */
   kLzsCmdHistGetRangeCont    = 0x25,    /* command "Variable History - get data", input data */
   kLzsCmdHistGetRangeResult    = 0x26,    /* command "Variable History - get data, result data" */
   kLzsCmdHistClear        = 0x27,        /* command "Variable History - clear" */
   kLzsCmdHistUpdate    = 0x28,        /* command "Variable History - update" */
   kLzsCmdHistUpdateCont    = 0x29,    /* command "Variable History - update, data part" */

   kLzsCmdUplGetSegInfNoError    = 0x2A,    /* command "Get Segment Information - return error code as data" */
   kLzsCmdSaveSystem            = 0x2B, /* put Resource to persistent storage */
   kLzsCmdCheckResVer           = 0x2C, /* check resource version */
   kLzsCmdDwlRawFile        = 0x30,    /* command "Download RAWFile */
   kLzsCmdDwlRawFileSegment     = 0x31, /* command "Download RAW File Segment" for larger RAWFiles*/
   kLzsCmdDwlRawFileLastSegment = 0x32, /* command "Download RAW File Last Segment" for last RAWFile Segment*/
   kLzsCmdUplRawFile        = 0x33,    /* command "Upload RAWFile */
   kLzsCmdUplRawFileSegment     = 0x34, /* command "Upload RAW File Continue" for larger RAWFiles*/
   kLzsCmdUplRawFileLastSegment = 0x35, /* command "Upload RAW File Last Segment" for last RAWFile Segment*/
   kLzsCmdGetRawFileInfo     = 0x36,    /* command "GetRAWFileInfo" to be able to compare the up-to-dateness of the file */
   kLzsCmdContDwlRawFileSegment = 0x37, /* continue "download rawfile segment" */

   kLzsCmdDwlDcfFilesFinished   = 0x38, /* command "download binary Dcf segment files finshied" */

   kLzsCmdContDwlRes    = 0x83,     /* Continue "Download Resource" */
   kLzsCmdContDwlSeg    = 0x85,      /* Continue "Download Segment" */
   kLzsCmdContDwlSingleSeg = 0x86,  /* download config data*/

   kLzsCmdDwlCompletion = 0x87,     /* Postprocessing finish download */
   kLzsCmdAddMulWatchInstrCont = 0x88,  /*get data for multiple watch instr */
   kLzsCmdContDwlMultiSeg  = 0x89,  /* get the data for multiple segments*/
   kLzsCmdDwlWithoutStopCont = 0x8A,    /* Continue kLzsCmdDwlWithoutStop */ 
   kLzsCmdReboot = 0x8B,	/* reboot PLC */

/* Breakpoints */
   kLzsCmdBrPtAdd        = 0xA0,     /* Breakpoint Command */
   kLzsCmdBrPtRemove    = 0xA1,     /* Breakpoint Command */
   kLzsCmdBrPtRemoveAll    = 0xA2,     /* Breakpoint Command */
   kLzsCmdBrPtSleepAll    = 0xA3,     /* Breakpoint Command */
   kLzsCmdBrPtAwakeAll    = 0xA4,     /* Breakpoint Command */

   kLzsCmdBrPtCtrlGo        = 0xA5,     /* Breakpoint Ctrl Command */
   kLzsCmdBrPtCtrlStepIn    = 0xA6,     /* Breakpoint Ctrl Command */
   kLzsCmdBrPtCtrlStepOut    = 0xA7,     /* Breakpoint Ctrl Command */
   kLzsCmdBrPtCtrlStepOver    = 0xA8,     /* Breakpoint Ctrl Command */

/* Parameters B.S. 7.3.99 */
    kLzsCmdSetParameter    = 0xB0,        /* Set a Parameter */

/* Commands with long parameter data, resulting in messages of more than 255 bytes size */
/* In those messages, the parameter size is given in the WORD at bytes [1] to [2] of the message (treated in LzsCsvCheckCmdReceipt()) */
    kLzsCmdSetVariableLong   = 0xB1,    /* command "Set Variable (long data)" */
    kLzsCmdForceVariableLong = 0xB2,    /* command "Force Variable (long data)" */
    kLzsCmdMultiSetVariable     = 0xB3,  /* command set multiple variable */ 
    kLzsCmdMultiSetVariableCont = 0xB4,  /* continue command set multiple variable */ 

/* OEM Functions */
   kLzsCmdOEMSendCmd    = 0xC8,     /* OEM Command */

/* Functions for 32Bit Online Server B.S. 20.04.2000 */
    kLzsCmdTerminate                        = 0xF0,        /* Terminate Signal */
    kLzsDownloadResourceCollection            = 0xF1,        /* Resource Collection for download */
    kLzsNewAkkuStatusCollection                = 0xF2,        /* New Akku Status download */
    kLzsNewVariableStatusCollection            = 0xF3,        /* New Variable Status download */
    kLzsLoginCollection                        = 0xF4,        /* Login Collection (login and Resourceinformation */
    kLzsSetSleepTime                        = 0xF5,        /* Change the sleeptime of the queue */
    kLzsDownloadResourceUpdateCollection    = 0xF6,        /* Collection for Update download */
    kLzsCheckResourceVersion                = 0xF7,        /* Check the Version of the PLC Version against the PCD */
    kLzsDownloadUserSegmentCollection        = 0xF8,           /* Download configuration segment. -ae- 2000/08/31 */
    kLzsUploadResourceCollection            = 0xF9,        /* Upload of a resource on the plc -ae- 2000/09/06 */
    kLzsCompareVersions                        = 0xFA,        /* Compare the the OemId and the HW-/FW-/Kernel-Versions of the resource and the plc -ae- 2000/09/14*/
    kLzsDownloadResourceIncCollection        = 0xFB,        /* Resource Collection for incremental download */
    kLzsUploadVarTabCollection                = 0xFC        /* Upload of VarTab segments */

} tLzsCmdLst;
   
/* sub commands of kLzsCmdDwlWithoutStop(Cont) */
typedef enum {
    kLzsDwlWsTaskDef    = 0x01,
    kLzsDwlWsProgram    = 0x02,
    kLzsDwlWsCopyTab    = 0x03,
    kLzsDwlWsSegment    = 0x04,
    kLzsDwlWsDone        = 0x05,
    kLzsDwlWsForceTabUpdate    = 0x06,
    kLzsDwlWsVarCopyTab    = 0x07

} tDwlWithoutStopLst;

/* local control commands of control elemets of the PLC */
typedef enum
{
   kLzsBtnRun           = 0x01,     /* Run/Stop-Switch to RUN */
   kLzsBtnStop          = 0x02,     /* Run/Stop-Switch to STOP */
   kLzsBtnMRes          = 0x03      /* Run/Stop-Switch to MRES */

} tLzsBtnLst;
   
/* parameters for control command <SetState> */
typedef enum
{
   kLzsCtrStop          = 0x00,     /* Runcommand "Stop" */
   kLzsCtrColdStart     = 0x01,     /* Runcommand "coldstart" */
   kLzsCtrWarmStart     = 0x02,     /* Runcommand "Warmstart" */
   kLzsCtrHotStart      = 0x03,     /* Runcommand "continue" */
   kLzsCtrSingleCycle   = 0x04,     /* Runcommand "SingleCycle" */
   /* NOTE: kLzsCtrClearSystem must be 0x05 B.S. 23.01.98 */
   kLzsCtrClearSystem   = 0x05,     /* Runcommand "ClearSystem" */
   kLzsCtrRestoreDS     = 0xFF      /* Runcommand "Restore DS" */

} tLzsCtrLst;

/* struct to administrate the commands of the IDE */
typedef struct
{
   LZSBYTE          m_bCommand;        /* current command */
   LZSWORD          m_wParamSize;      /* size of parameter list */
   tPlcMemPtr    m_pParamLst;       /* Pointer to parameter list */
   LZSBOOL          m_fSendRec;        /* Flag "send receipt" */

} tLzsPSCmd;

typedef struct
{
    LZSBYTE  LZSFAR  bCmdBuff[LZSCMDBUFFSIZE]; /* Input buffer for commands */
    LZSBYTE  LZSFAR  bRecBuff[RECBUFFSIZE];     /* Sendbuffer for receipts */
    LZSWORD       wUsedRecSize;              /* Level of Receiptpuffer */
    LZSWORD       wMaxRecSize;               /* max. possible size of receipt */
    LZSBOOL       fPrestCmd;                 /* LZSTRUE -> "internal command" */
    LZSBOOL       fRecEnabled;               /* LZSTRUE -> Inputbuffer enabled */
    
    #ifdef _NET_USE_NONBLOCKING_API_
    LZSBOOL   fNetSendRunning;           /* LZSTRUE -> sending of data is currently in process */
    #endif
} tLzsCmdBuffer;

/* inserted for function <LzsCsvPresetCmd> */
/* Parameter to enable/disable external communicaton */
/* of function <LzsCsvPresetCmd> */
typedef enum
{
   kLzsEnableExtrnComm  = 0x00,
   kLzsDisableExtrnComm = 0xFF

} tLzsPresetCmdMode;

/* Definition of events */
typedef enum
{
   kLzsNoChange         = 0x00,     /* no change */
   kLzsStateChg         = 0x01,     /* updated status of controller*/
   kLzsError            = 0x02,     /* error occured (request GetErrInf) */
   kLzsPflowData        = 0x03,     /* new powerflow data available */
/*   kLzsWarning          = 0x04,   // Error/Warning (request GetErrInf) */

   kLzsWatchID          = 0x05,     /* Watch-ID in receipt buffer */
   kLzsWatchData        = 0x06,     /* Watch-Data in receipt buffer */
   kLzsResVer           = 0x07,     /* ResourceVersion in receipt buffer */
   kLzsPlcVer           = 0x08,     /* FirmwareVersion in receipt buffer */
   kLzsErrInf           = 0x09,     /* Errorstring in receipt buffer */
   kLzsSegInf           = 0x0A,      /* Segment informationen in receipt buffer */

   kLzsBreakPointReached    = 0x0B,      /* Breakpoint reached */
   kLzsBreakPointData        = 0x0C,     /* Breakpoint data for signaled breakpoints */
   kLzsSysID            = 0x0D,     /* LZS-ID in receipt buffer */
   kLzsLockTime         = 0x0E,     /* specification of lock time in receipt buffer */
   kLzsDump                            = 0x0F,            /* stack,Reg for errors */
    kLzsWatchIDList        = 0x10,
    kLzsExtCap            = 0x11,        /* extendet capabilities */
    kLzsOEMVers            = 0x12,     /* OEM Version info */
    kLzsOnlineEditChangesApplied = 0x13,    /* old resource has been replaced */
    kLzsSaveSystemCmdFinished     = 0x14,    /* LzsEnvSaveSystemCmd has finished */

/* OEM Events ==================================== */
   kLzsOEMData            = 0xA0,     /*  B.S. 10.11.98 */

   kLzsRemovedWatchID   = 0xA5,     /* Watch-ID in receipt buffer */
   kLzsRawFileInf        = 0xA6        /* Raw file information in receipt buffer */
   
} tLzsEvent;

/* definitions of call modes for the CallBack-Functions at the data server */
typedef enum
{
   tLzsRecMode          = 0x00,     /* send data piggyback with receipt */
   tLzsDataMode         = 0x01      /* Request to send data */

} tLzsSendMode;

/* struct to request for version of current resource */
typedef struct
{
   LZSCHAR          m_szPrjName[32];       /* Projectname */
   LZSCHAR          m_szResName[32];       /* Resourcename */
   tPlcVersion      m_PlcVer;              /* Versionnumber of Resource  */
   LZSDWORD         m_dwBuildDate;        /* Creation date of Resource     -ae- 01/15/1999 */
   LZSDWORD         m_dwLoadDate;        /* Download date of Resource    -ae- 01/15/1999 */

} tLzsResVersion;

/* struct to request firmware version */
typedef struct
{
   LZSWORD          m_HwVersion;       /* Version of Hardware        // 0 */
   LZSWORD          m_FwVersion;       /* Version of Firmware        // 2 */
   tPlcIpVer     m_IpVer;           /* Version of Interpreter        // 4 */
   /* -fg-  19990325 DeviceName reduced and OemId insertet             */
   LZSCHAR          m_szDevName[62];   /* Identifier of the hardware        // 8 */
   LZSWORD             m_wOemIdent;        /* OEM Identification Number    // 70 */
      /* 2006-11-23 cbo, get the hardware byte aligment motorola or intel PLC in hw file */
   LZSWORD          m_wByteOrder;   /* byte order Motorola or Intel*/
} tLzsPlcVersion;

/* Struct for version comparison. -ae- 2000/09/14 */
typedef struct
{
    tLzsPlcVersion        m_PlcVersionFromCRD;
    tLzsPlcVersion        m_PlcVersionFromPLC;
} tLzsVersionInfo;

/* struct for definition of one entry in the segment table */
typedef struct
{
   tPlcMemPtr    m_pPrimarySeg;
   tPlcMemPtr    m_pSecundarySeg;

} tLzsSegTabEntry;

/* struct to manage RTS-internal additional segments */
typedef struct
{
   LZSWORD          m_nSegInstStack;
   LZSWORD          m_nSegAEStack;
   LZSWORD          m_nSegExtAE;
   LZSWORD          m_nSegExtAEs;

} tLzsExtraSeg;

/* struct to store size and pointer to a process image */
typedef struct
{
    tPlcMemPtr   m_pSeg;          /* Pointer to Segment with Processimage */
    tPlcSegNr    m_SegNum;        /* Segmentnumber of Processimage Segment */
    LZSWORD      m_wSegSize;      /* Size of the Segment */

} tLzsClassProcessImage;

typedef struct             
{
    tLzsSegTabEntry    LZSFAR*        pSegTable;
    LZSWORD                      cSegTabEntrys;
    tIpTaskData             TaskData;
    tLzsClassProcessImage    ProcImg;
    tPlcPgmNr                nPgmNum;
    
    /* +++ */
    LZSBYTE   LZSFAR*             RegCS;
    LZSBYTE   LZSFAR*             RegDS;
    tLzsMemTask                MemTask;

    LZSBYTE   LZSFAR* RegIP;                      /* current IP */
    LZSDWORD  LZSFAR* RegInstSP;                  /* current SP Inst-Stack (RetStack) */
    LZSDWORD  LZSFAR* RegAESP;                    /* current SP AE-Stack */
    LZSBYTE   LZSFAR* RegExtAE;                   /* Baseaddr. external AE */
    LZSBYTE   LZSFAR* RegExtAEs;                  /* Baseaddr. external AEs */
    
    /* B.S. FHL 98/314 */
    LZSWORD   SegAEStack;                      
            
    /* B.S. 18.05.98 */
    tPlcTaskType            TaskType;        /* Tasktype */
    LZSDWORD                    dTimeSpec;        /* Cycletime */
    LZSDWORD                    dLastTime;        /* Last time this task was run (timertasks only) */
    LZSWORD                    wPriority;        /* Task priority */
    
    /* -fg- 19990511 for sceduling*/
    LZSWORD                    wCurrentPrio;
    tPlcTaskState            wTaskState;        

    /* -cd- 011114 CRQ 2001/562 */
    LZSBYTE   LZSFAR*             RegNS;
    tIpRef RegRef;

} tLzsResourceSegmentTables;

/* Function-Pointer to Firmware-FB */
typedef LZSBYTE (*tLzsIecFB)(void);

/* Struct for administration of the jump table for FB calls */
typedef struct
{
   LZSWORD              wFBTabEntrys;  /* Number of enries in jump table */
   tLzsIecFB LZSCONST*  fpIecFBTab;    /* Pointer to jump table */

} tLzsIecFBTab;

/* struct to watch and set varaiables */
typedef enum
{
   kLzsAccessUndef      = 0x00,     /* Watchentry unused */
   kLzsAccessBitByAdr   = 0x01,     /* Watch or set Bit */
   kLzsAccessBitByRef   = 0x02,     /* Watch or set Bit */
   kLzsAccessByteByAdr  = 0x03,     /* Watch or set Byte(sequence) */
   kLzsAccessByteByRef  = 0x04      /* Watch or set Byte(sequence) */

} tLzsAccessType;

/* structure to add  a watch item */
typedef struct
{
   LZSBYTE          m_Type;            /* Unused/Bit/Byte(folge) */
   tPlcPgmNr     m_Pgm;             /* Programnumber */
   tPlcSegNr     m_Seg;             /* Segmentnumber */
   tPlcOffset    m_Offs;            /* LZSBYTE-Offset within the segment */
   tPlcByteCount m_Size;            /* Anzahl Bytes */
   tLzsSegTabEntry LZSFAR* m_pSegTab;        /* Segmenttable of Task to watch */

} tLzsDataAdr;

/* structure to hold watch data for one connection */
typedef struct
{
    tLzsDataAdr     WatchLst[LZSMAXWATCH];      /* table of watch items */
    LZSDWORD        dwWatchEntriesUsed;
    LZSWORD         wCurrWatchId;            /* next watch item to process */
    LZSBOOL         fWatchEnable;            /* watching activ */
    LZSBOOL         fDataAvailable;            /* (new) data available */
    LZSBYTE         bWatchMode;              /* watch modes (Single/All) */
    LZSBOOL         fDataRequestsLocked;     /* data requests locked */
    tPlcMemPtr         pMulSetVariableInstr;
} tLzsWatchTable;

/* structure to add  a watch item */
typedef struct
{
   LZSWORD         m_WatchID;         /* watch ID */
} tLzsRemoveWatchItem;

/* Definition of watch mode */
typedef enum
{
   kLzsWatchSingle  = 0x00,         /* only one variable/cycle */
   kLzsWatchAll     = 0x01          /* all variables/cycle */

} tLzsWatchMode;

/* struct to set one variable */
typedef struct
{
   LZSBYTE          m_Type;            /* Unused/Bit/Byte(sequence) */
   tPlcPgmNr     m_Pgm;             /* Programnumber */
   tPlcSegNr     m_Seg;             /* Segmentnumber */
   tPlcOffset    m_Offs;            /* LZSBYTE-Offset within the segment */
   tPlcByteCount m_Size;            /* Number of bytes to be set */
   LZSBYTE          m_Data[LZS_SIZEOF_SETDATA];

} tLzsSetData;

/* struct to force a variable */
typedef struct
{
   LZSBYTE          m_Type;            /* Unused/Bit/Byte(folge) */
   tPlcPgmNr     m_Pgm;             /* Programbnumber */
   tPlcSegNr     m_Seg;             /* Segmentnumber */
   tPlcOffset    m_Offs;            /* LZSBYTE-Offset within the segment */
   tPlcByteCount m_Size;            /* number of bytes */
   LZSBYTE       m_Data[LZS_SIZEOF_SETDATA];
} tLzsForceItem;

typedef struct
{
   LZSBYTE          m_Type;            /* Unused/Bit/Byte(folge) */
   tPlcPgmNr     m_Pgm;             /* Programnumber */
   tPlcSegNr     m_Seg;             /* Segmentnumber */
   tPlcOffset    m_Offs;            /* LZSBYTE-Offset within the segment */
} tLzsUnForceItem;

/* Struct to define a powerflow-area */
typedef struct
{
   tPlcPgmNr     m_Pgm;             /* Programnumber */
   tPlchInst     m_hPflowInst;      /* Handle of selected instance */
   tPlcOffset    m_StartOffs;       /* Start within the instance */
   tPlcOffset    m_EndOffs;         /* End within the instance */

} tLzsPflowRange;

/* struct to manage error messages */
typedef struct
{

   LZSBYTE   m_bErrCode;
   LZSDWORD  m_dErrNum;
   LZSCONST LZSCHAR  *m_pErrStr;

} tLzsErrTabEntry;

/* struct for entries in the retain table */
typedef struct
{
   LZSWORD    m_wTaskNr; /* number of the task that the retain data belongs to */
   tPlcMemPtr m_pData;   /* pointer to the retain data */
   LZSWORD    m_wSegNr;  /* number of the data segment where the retain data area is located */
   LZSWORD    m_wOffset; /* offset in the data segment to the retain data area */
   LZSWORD    m_wSize;   /* size in bytes of the retain data */

} tLzsRetainTableEntry;

/* Callbackfunktion for passing asynchonous data to the IDE */
typedef  LZSWORD (*tEventCallback) (LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);

typedef struct
{
    tPlcMemPtr    m_pGlobalsSeg;            /* Pointer to Segment with Global Vars */
    LZSWORD        m_wGlobalSegNum;          
    
    tPlcMemPtr    m_pDirectGlobalsSeg;    /* Pointer to Segment with Direct Global Vars */
    LZSWORD        m_wDirectGlobalSegNum;        
    
    
    /* B.S. HardwareConfigSegment 08.04.99 */
    tPlcMemPtr    m_pHardwareConfigSeg;    /* Pointer to Segment with Hardwareconfiguration */
    LZSWORD        m_wHardwareConfigSegNum;        

/* As a workaround, we handle the processimage resourceglobal */
    tPlcMemPtr    m_pProcImage;
    tPlcMemPtr    m_pNetImage;
    
} tLzsResourceGlobData;

#ifdef _LZS_STATIC_PERSISTENCE_

struct PlcSegment{
    LZSBYTE    m_bSegType;                    /* Segmenttype*/
    LZSWORD    m_wSegSize;                  /* Segmentsize*/
    struct     PlcSegment * m_pNextSegment;  /* Pointer to the following segment*/
    LZSBYTE     m_bSegContents[];            /* Contents of the segment */
};
 
#ifdef _LZS_PRAGMAMESSAGE_
#pragma message ("Typedef tPlcSegment")
#endif
typedef struct PlcSegment tPlcSegment;

#endif /* _STATIC_PERSISTENCE_*/

typedef struct 
{
    tPlcSegNr    m_nTempSegNumber;            /* Segment number of new segment */
    tPlcPgmNr   m_nTempPrgNumber;            /* program number of new segment */
    tPlcMemPtr    m_pTempSeg;                    /* pointer to the new segment    */
    LZSBOOL        m_fTempSegToExchange;        /* flag to tell the kernel there is segment to exchange */
    LZSBOOL        m_fChangeVersionInfo;        /* do we have to change the version info */
    LZSDWORD    m_dwResVersion;                /* Resource version */
    LZSDWORD    m_dwPrgVersion;                /* version of Program */
    LZSDWORD    m_dwBuildDate;                /* date of build */
    LZSDWORD    m_dwLoadDate;                /* date of load */

} tSegmentChangeInfo;

typedef struct
{
    LZSUINT wTyp;
    LZSUINT wSize;
    LZSUINT wProg;
    LZSUINT wSeg;
    LZSUINT wOff;
    LZSUINT wBit;
    LZSUINT wScope;

} tVarDes;


#ifdef _LZS_TASKINFO_
typedef struct {
    LZSDWORD    dwCount;
    LZSDWORD    dwLastCT;
    LZSDWORD    dwAverageCT;
    LZSDWORD    dwMinCT;
    LZSDWORD    dwMaxCT;
    LZSDWORD    dwState;
    LZSDWORD    dwLastStart;
    LZSDWORD    dwLastStart2;
    LZSDWORD    dwTotalCTCount;
    LZSDWORD    dwTotalCT;

} tTaskInfo;
#endif

typedef struct {
    LZSWORD    wOemVerMajor;
    LZSWORD    wOemVerMinor;
    LZSWORD    wOemVerRevision;
    LZSWORD    wOemVerBuild;

} tOemVersion;

typedef struct {
    LZSBYTE    bVerMajor;
    LZSBYTE    bVerMinor;
    LZSBYTE    bVerRevision;

} tProgSysVersion;

typedef struct 
{
    tLzsPlcVersion m_PlcVer;
    tOemVersion    m_OemVer;

} tCompleteVersion;

typedef enum
{
    kLzsStateLogin       = 0x01,    /* Systemstatus "Login" */
    kLzsStateLogout      = 0x02,    /* Systemstatus "Logout" */
    kLzsStateReset       = 0x03,    /* Systemstatus "Reset" */

    /*----------------------------------------------------------*/
    /* [SYSTEC 10.06.2003 -rs]:                                 */
    /* - kLzsStateHardStop renamed to kLzsStateHardStopReq    */
    /* - kLzsStateSoftStop renamed to kLzsStateSoftStopReq    */
    /* - kLzsStateHardStopped inserted                     */
    /* - kLzsStateSoftStopped inserted                     */
    /* - all following enums until kLzsStateSingleCycle      */
    /*   new serial numbered                                    */
    /*----------------------------------------------------------*/
    kLzsStateHardStopReq = 0x04,    /* Systemstatus "Stop-Request" (by Hardware) */
    kLzsStateSoftStopReq = 0x05,    /* Systemstatus "Stop-Request" (by Software) */
    kLzsStateHardStopped = 0x06,    /* Systemstatus "Stop reached" (by Hardware) */
    kLzsStateSoftStopped = 0x07,    /* Systemstatus "Stop reached" (by Software) */
    kLzsStateColdStart   = 0x08,    /* Systemstatus "Coldstart" */
    kLzsStateWarmStart   = 0x09,    /* Systemstatus "Warmstart" */
    kLzsStateHotStart    = 0x10,    /* Systemstatus "Continue" */
    kLzsStateSingleCycle = 0x11,    /* Systemstatus "SingleCycle" */
    /* 20040505mm  windows shutdown task implemented */
    kLzsStateWinShutdownReq = 0x12,    /* Systemstatus "Shutdown-Request" (i.e. by RTX subsystem) */
    kLzsStateBlueScreenReq    = 0x13,    /* Systemstatus "Bluescreen-Request" (i.e. by RTX subsystem) */
    kLzsStateIecCycleReq    = 0x14,    /* system status when a IEC cyclic task exceeded a limit */
       kLzsStateRtxBaseTimerReq    = 0x15,    /* system status when the IEC application period exceeds the Rtx base Timer duration */
   kLzsStateColdRestart = 0x81,     /* Restart with "Coldstart"*/
   kLzsStateWarmRestart = 0x82,     /* Restart with "Warmstart"*/
   kLzsStateDwlPrepare  = 0x83,     /* prepare Program download */
   kLzsStateDwlLastSeg  = 0x84,     /* all segments available*/
   kLzsStateDwlComplete = 0x85,     /* Program download finished*/
   kLzsStateOnlChangePrepare  = 0x87, /* before applying online changes */
   kLzsStateOnlChangeComplete = 0x88, /* after online changes applied */

   /*----------------------------------------------------------*/
   /* [SYSTEC/CANopen 2006/10/06 -rs]:                         */
   /* new state <kLzsStateDwlFinished> inserted                */
   /*----------------------------------------------------------*/
   kLzsStateDwlFinished        = 0x86,     /* download of PLC program and RawFiles finished (incl. network configuration files like DCF) */
   kLzsStateStartupTaskFinished = 0x89,
   kLzsStateRestoreDS   = 0xFF      /* Systemstatus "Restore DS"*/

} tLzsSysState;



/*---------------------------------------------------------------------------------*/
/* [SYSTEC/CANopen: 2006/10/04 -rs]: structure <tDcfDescription> new inserted      */
/*---------------------------------------------------------------------------------*/

typedef struct
{
    LZSCHAR     m_szFileName[64];       /* name of DCF RawFile */
    LZSDWORD    m_dwFileSize;           /* size of DCF RawFile */
    LZSBYTE     m_bNodeNumber;          /* node number */
    LZSBYTE     m_bNetNumber;           /* network number */
    LZSBOOL     m_fIsLocalPlcDcf;       /* TRUE: DCF is for local PLC, FALSE: DCF is for remote node */
    LZSBYTE     m_bReserved;

} tDcfDscrpt;



/*---------------------------------------------------------------------------------*/
/* [SYSTEC: 2006/09/04 -rs]: typdef for structure <tLzsFileTime> new inserted      */
/*---------------------------------------------------------------------------------*/
#ifdef _LZS_DWL_RAWFILE_

typedef struct
{
    LZSDWORD  m_dwLowDateTime;
    LZSDWORD  m_dwHighDateTime;

} tLzsFileTime;

#endif  /* #ifdef _LZS_DWL_RAWFILE_ */



/*--------------------------------------------------*/
/* P0699-specific types                             */
/*--------------------------------------------------*/

/* structure to access the task configuration part of the hardware configuration segment */
typedef struct
{
    LZSDWORD dwT0Interval; /* T0 interval in microseconds */
    LZSDWORD dwT1Factor;   /* T1 multiplication factor */
    LZSDWORD dwT2Factor;   /* T2 multiplication factor */
    LZSDWORD dwT3Factor;   /* T3 multiplication factor */
    LZSDWORD dwT4Factor;   /* T4 multiplication factor */
    LZSDWORD dwT5Factor;   /* T5 multiplication factor */
    
    LZSDWORD dwI1SamplingTime; /* I1 equivalent sampling time in microseconds */
    LZSDWORD dwI2SamplingTime; /* I2 equivalent sampling time in microseconds */
    LZSDWORD dwI3SamplingTime; /* I3 equivalent sampling time in microseconds */
    LZSDWORD dwI4SamplingTime; /* I4 equivalent sampling time in microseconds */
    LZSDWORD dwI5SamplingTime; /* I5 equivalent sampling time in microseconds */
    LZSDWORD dwI6SamplingTime; /* I6 equivalent sampling time in microseconds */
    LZSDWORD dwI7SamplingTime; /* I7 equivalent sampling time in microseconds */
    LZSDWORD dwI8SamplingTime; /* I8 equivalent sampling time in microseconds */

    LZSBYTE bI1Source; /* I1 source */
    LZSBYTE bI2Source; /* I2 source */
    LZSBYTE bI3Source; /* I3 source */
    LZSBYTE bI4Source; /* I4 source */
    LZSBYTE bI5Source; /* I5 source */
    LZSBYTE bI6Source; /* I6 source */
    LZSBYTE bI7Source; /* I7 source */
    LZSBYTE bI8Source; /* I8 source */

} tTaskConfig;

/* structure to access the target configuration part of the hardware configuration segment */
typedef struct
{
	LZSDWORD dwUseBLCode; /* "target-side optimized code generation" */
	
	/* TO DO: other future configuration settings */

} tTargetConfig;

/* structure for shared memory data consistency buffer management */
typedef struct
{
	LZSWORD wSegNum;            /* segment number, for easier debugging - LOCAL DATA, to be set on initialization */
    LZSWORD wNumEntries;        /* number of buffer copies for the segment - LOCAL DATA, to be read from shared memory on initialization */
    LZSWORD* pLatestConsistent; /* pointer to number of latest consistent buffer copy for the segment - points into SHARED MEMORY */
    LZSWORD* pLocks;            /* pointer to array of lock counters for the buffer copies of the segment (has wNumEntries fields) - points into SHARED MEMORY */
    LZSBYTE** pBuffers;         /* pointer to array of pointers to the buffer copies of the segment (has wNumEntries fields) - array is LOCAL DATA, pointers in array point into SHARED MEMORY */

} tSHMDCBufferInfo;

#endif  /* #ifndef _LZSTYPES_H_ */
