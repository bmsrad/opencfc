/****************************************************************************

   definitions for IEC1131 interpreter

   18.08.1997   -tdl (from rs)

 **********************************************************************/

#ifndef _IP_DEF_H_
#define _IP_DEF_H_

#define packed

/*--------------------------------------------------------------------------- */
/* version number of Interpreter */
/*--------------------------------------------------------------------------- */
#define IP_DOMAIN   7               /* version of interpreter  (1.*) */
#define IP_REVISION 3               /* revision of interpreter(*.00) */
                                    /* revision 1 : with wrapper fbs for ladder editor */
                                    /* revision 2 : 4 tables of firmware fbs */
#define IP_TYPE     2               /* language */



/*--------------------------------------------------------------------------- */
/* constants */
/*--------------------------------------------------------------------------- */

/* errorcodes of the interpreter ( returncode of IpCycle to LZS ) */
typedef enum
{
    kIpOK                    = 0x00, /* no error */
    kIpTaskCmdInvalid        = 0x9F, /* unknown control command */
    kIpOpcodeInvalid         = 0x9E, /* unused (free) opcode */
    kIpOpcodeNotSupported    = 0x9D, /* opcode not implemented */
    kIpExtensionInvalid      = 0x9C, /* unused (free) extension */
    kIpDivisionByZero        = 0x9B, /* division by zero */
    kIpArrayIndexInvalid     = 0x9A, /* invalid index for array */
    kIpFirmwareExecError     = 0x99, /* error executing firmware function block */
    kIpPflowNotAvailable     = 0x98, /* Powerflow not available */
    kIpInvalidBitRef         = 0x97, /* invalid bit reference*/
    kIpErrorRestoreData      = 0x96, /* error in restore data*/
    kIpNoValidArrElementSize = 0x95, /* select array index wrong element size*/
    kIpInvalidStructSize     = 0x94, /* length in struct header invalid */
    kIpModuloZero            = 0x93, /* second operand to mod was zero, result undefined */
    kIpArrElemNotSupported   = 0x92, /* array elements of unknown type */
    kIpNoMem                 = 0x91, /* out of memory */
    kIpInvalidTypecast       = 0x90, /* unsupported typecast */
    kIpCPUException          = 0x8F  /* CPU exception */

	/* until 0x80: reserved for future runtime error codes */
	/* see also tLzsErrorCode in lzstypes.h! */

} tIpErrorCode;

/* bitmask for state of interpreter */
typedef enum
{
    kIpCycleEnd     = 0x01, /* end of cycle, exchange process image */
    kIpRecBrkReq    = 0x02, /* set break flag recognized */
    kIpExecBrkCmd   = 0x04, /* opcode <IP_OP_BREAK> executed */
    kIpStopNow      = 0x08, /* request of immediate stop */
    kIpTimerTaskNow = 0x10  /* timer task waiting to be executed */

} tIpStatus;

/* control code for calling interpreter */
typedef enum
{
    kIpInitTask    = 0x00, /* initialize */
    kIpSaveTask    = 0x01, /* save task state */
    kIpRestoreTask = 0x02, /* restore task state */
    kIpRunTask     = 0x03, /* start program execution */
	kIpProgramListsInit = 0x04, /* initialize program lists */
	kIpProgramListsCreate = 0x05, /* detect used tasks and modes and create program lists */
	kIpControlSetsInit = 0x06 /* initialize task control structures */

} tIpTaskCmds;

/* current type of AE and AE' */
typedef packed enum
{
    kIpUndef       = 0x00,
    kIpBit         = 0x01,
    kIpByte        = 0x02,
    kIpWord        = 0x03,
    kIpDword       = 0x04,
    kIpAny         = 0x05,
    kIp64Bit       = 0x06,
    kIp48Bit       = 0x07,
    kIp24Bit       = 0x08,
    kIpAETypeDummy = 0x101

} tIpAEType;



/*--------------------------------------------------------------------------- */
/* for BL code                                                                */
/*--------------------------------------------------------------------------- */
/* NOTE: all structures used for BL code are designed to have a size divisible by 4 */
/* This is to avoid alignment problems. Some structure elements have a bigger data type than actually necessary. */
#ifdef USE_BL_CODE
typedef enum
{
	kBL_NOP = 0x00000000,
    kBL_C = 0x00000001,
    kBL_TDD1 = 0x00000002,
    kBL_TDD2 = 0x00000003,
    kBL_TDD4 = 0x00000004,
    kBL_TDD8 = 0x00000005,
    kBL_TID1 = 0x00000006,
    kBL_TID2 = 0x00000007,
    kBL_TID4 = 0x00000008,
    kBL_TID8 = 0x00000009,
    kBL_TDI1 = 0x0000000A,
    kBL_TDI2 = 0x0000000B,
    kBL_TDI4 = 0x0000000C,
    kBL_TDI8 = 0x0000000D,
	kBL_TDDC = 0x0000000E,
	kBL_TIDC = 0x0000000F,
	kBL_TDIC = 0x00000010,
	kBL_N = 0x00000011,
	kBL_UC = 0x00000012,
	kBL_TDDS = 0x00000013,
	kBL_TIDS = 0x00000014,
	kBL_TDIS = 0x00000015,
	kBL_UCBL = 0x00000016,
    kBL_R = 0x000000FF

} tBLCodeInstruction;

typedef struct
{
	LZSDWORD dwInstruction;

} tBL_NOP_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	LZSBYTE* pDS;
	LZSBYTE (*pFunction)(void);

} tBL_C_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void* pDestination;
	void* pSource;

} tBL_TDD_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void* pDestination;
	void* pSource;

} tBL_TDDS_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void* pDestination;
	void** ppSourceSegment; /* includes one indirection: points to segment table entry, which contains the pointer to the segment */
	LZSDWORD dwSourceOffset;

} tBL_TID_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void* pDestination;
	void** ppSourceSegment; /* includes one indirection: points to segment table entry, which contains the pointer to the segment */
	LZSDWORD dwSourceOffset;

} tBL_TIDS_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void** ppDestinationSegment; /* includes one indirection: points to segment table entry, which contains the pointer to the segment */
	LZSDWORD dwDestinationOffset;
	void* pSource;

} tBL_TDI_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void** ppDestinationSegment; /* includes one indirection: points to segment table entry, which contains the pointer to the segment */
	LZSDWORD dwDestinationOffset;
	void* pSource;

} tBL_TDIS_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void* pDestination;
	void* pSource;
	LZSWORD wFromType;
	LZSWORD wToType;

} tBL_TDDC_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void* pDestination;
	void** ppSourceSegment; /* includes one indirection: points to segment table entry, which contains the pointer to the segment */
	LZSDWORD dwSourceOffset;
	LZSWORD wFromType;
	LZSWORD wToType;

} tBL_TIDC_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void** ppDestinationSegment; /* includes one indirection: points to segment table entry, which contains the pointer to the segment */
	LZSDWORD dwDestinationOffset;
	void* pSource;
	LZSWORD wFromType;
	LZSWORD wToType;

} tBL_TDIC_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	LZSBOOL* pTarget;

} tBL_N_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void* pProgramData;
	LZSDWORD dwInstance;

} tBL_UC_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;
	void* pBLCode;

} tBL_UCBL_Instruction;

typedef struct
{
	LZSDWORD dwInstruction;

} tBL_R_Instruction;
#endif



/*--------------------------------------------------------------------------- */
/* type definitions */
/*--------------------------------------------------------------------------- */

/* Type definition for AE and AE' of the interpreter */
typedef packed struct
{
    LZSDWORD dw1;
    LZSDWORD dw2;

} tIp64Bit;

typedef union
{
    LZSBOOL f;  /* Bit-AE */
    LZSBYTE b;  /* Byte-AE */
    LZSWORD w;  /* Word-AE */
    LZSDWORD d; /* Dword-AE */
    tIp64Bit l; /* 64 bit AE */
#ifdef _LZS_PMAC_
    /* P448*/
#ifdef _IP_REAL48_
    LZSINT48 i48; /* DSP563 INT48 (REAL48) */
#endif
#ifdef _IP_INT24_
    LZSINT24 i24; /* DSP563 INT24 */
#endif
#endif
} tIpAE;

typedef packed struct
{
    tPlchInst hInst;  /* instance handle of POE */
    tPlcOffset wOffs; /* 16Bit offset */

} tIpRef;
                                              
/* The following structure is for data exchange between interpreter and LZS  */
/* (runtime system) and has the purpose to store all task specific data  */
/* ( state of the task ). When calling the interpreter a pointer to this struct */
/* has to be provided as parameter. If there where multiple instances of this */
/* structure the interpreter is able to execute different programs in  */
/* multitasking mode. This is done by passing the pointer to the instance of this struct, */
/* which belongs to the current program, from the LZS to the interpreter */
typedef packed struct
{   
    /* initializiation data from LZS to interpreter */
    /* ( this values may be modifed by the interpreter ) */
    tPlchInst   m_MainInst;          /* handle to main instanz ( CS / DS ) */
    tPlcSegNr   m_SegInstStack;      /* number of segment instance stack */
    tPlcSegNr   m_SegAEStack;        /* number of segment  AE stack */
    tPlcSegNr   m_SegExtAE;          /* number of segment  external AE  (for ANY) */
    tPlcSegNr   m_SegExtAEs;         /* number of segment  external AEs (for ANY) */

   /* current state of interpreter */
    tPlchInst   m_CurrInst;          /* handle to current instance */
    LZSDWORD    m_CurrNsOffset;      /* offset of not completed native code segment  -cd- 80x86 ncc */
    tIpStatus   m_Status;            /* return state of interpreter */

    /* buffer for save / restore of task state of the interpreter */
	tIpAE       m_CurrAE;            /* current value of AE */
	tIpAE       m_CurrAEs;           /* current value of AEs */
    tIpAEType   m_TypeAE;            /* current type of AE */
    tIpAEType   m_TypeAEs;           /* current type of AEs */
    
    tPlcMemPtr  m_CurrCS;            /* base address of current CS of this instance */
    tPlcMemPtr  m_CurrDS;            /* base address of current DS of this instance */
    tPlcMemPtr  m_CurrIP;            /* current IP of this instance */
    tPlcMemPtr  m_CurrInstSP;        /* current SP InstStack of this instance */
    tPlcMemPtr  m_CurrAESP;          /* current SP AEStack of the instance */
    tPlcMemPtr  m_CurrExtAE;         /* base address of external AE  (for ANY) */
    tPlcMemPtr  m_CurrExtAEs;        /* base address of external AEs (for ANY) */
    
    tPlcPgmNr m_PgmNr;                /* program number */
    
    LZSWORD        m_UsedIStackEntrys;  /* used stack entries */
    LZSWORD        m_MaxIStackEntrys;   /* max. stack entries */
    LZSWORD        m_UsedAStackEntrys;  /* used stack entries for AE stack */
    LZSWORD        m_MaxAStackEntrys;   /* max. stack entries AE stack */

	LZSWORD m_wMaxAeLen;
	LZSBYTE m_bLzsIpErr;

	LZSBOOL m_fAltExecScheme; /* marks a CFC program with code for multiple tasks (P0699-specific) */

} tIpTaskData;



/*--------------------------------------------------*/
/* P0699-specific types                             */
/*--------------------------------------------------*/

/* structure for performance monitoring */
typedef struct
{
	LZSDWORD dwStartTick;
	LZSDWORD dwNumSamples;
	float executionTimeMin;
	float executionTimeLast;
	float executionTimeMax;
	float executionTimeSum;

} tPerformanceData;

/* structure for task control */
typedef struct
{
	LZSDWORD dwSystemTask;   /* one of the values from tSystemTasks (0..12, for I1..I8 and T1..T5) */
	LZSDWORD dwMode;         /* one of the values from tFBModes (0..6, init/system/normal/FI/CI/CE/FE mode) */
	LZSDWORD dwExecOffset;   /* execution start offset for UCode */
	LZSDWORD dwExecOffsetNC; /* execution start offset for native code */
	LZSWORD* pProgramList;   /* list of programs (and their order) to be executed in this task/mode */
	LZSBYTE* pBLCode;        /* BL code for this task/mode */
	LZSDWORD dwBLSize;       /* size of BL code for this task/mode (used during BL code generation) */

	#ifdef ENABLE_PERFORMANCE_MONITORING
	tPerformanceData* pPerformanceData; /* performance data for this task/mode */
	#endif

} tTaskControl;



#define _IPTASKDATA_                /* for use in ODK_SZM.H */

/* the folowing defines are for carrying typeinformation of AE and AEs or not */

#ifdef _IP_PFLOW_

   #define SAVE_AE_TYPE();      LzsMemCrPushAEType(pCurrentProgramData_g->TaskData.m_TypeAE);
   #define RESTORE_AE_TYPE();  {pCurrentProgramData_g->TaskData.m_TypeAEs=pCurrentProgramData_g->TaskData.m_TypeAE; pCurrentProgramData_g->TaskData.m_TypeAE=LzsMemCrPopAEType();}

#else

   #define SAVE_AE_TYPE();
   #define RESTORE_AE_TYPE();

#endif

/* The following structure is only for debug version of the interpreter */
/* and holds the clear text description of the current interpreter command */
/* ( output in DebugWindow ) */

#ifdef _LZS_GENERATE_IP_DEBUG_INFO_

typedef packed struct
{
    LZSBYTE   m_bIpOpcDef;          /* Opcode (#define) */
    LZSBYTE   m_bIpOpcLen;          /* Opcodelength in Bytes */
    LZSCHAR   m_szIpOpcStr[19];     /* plain text for Opcode */

} tIpOpcodeStrTab;

#endif

/* Execution steps for Powerflow and Reassembler */
#define STEP1   1
#define STEP2   2



/*--------------------------------------------------------------------------- */
/* Prototypes */
/*--------------------------------------------------------------------------- */

tIpErrorCode LZSPUBLIC IpPflowStart (tPlcPgmNr wPflowPgmNr_p,
                                     tPlchInst  hPflowInst_p,
                                     tPlcOffset StartOffs_p,
                                     tPlcOffset EndOffs_p,
                                     LZSWORD wDataBuffSize_p);

tIpErrorCode LZSPUBLIC IpPflowStop (void);

tIpErrorCode LZSPUBLIC IpCycle (tIpTaskData LZSFAR *pIpTaskData_p,
                                tIpTaskCmds IpTaskCmd_p, LZSDWORD dwExecOffset);

/* BL code */
#ifdef USE_BL_CODE
void GenBL_NOP(LZSBYTE** ppBLCodePos);
void GenBL_C(LZSBYTE** ppBLCodePos, LZSBYTE* pDS, LZSBYTE (*pFunction)(void), tTaskControl* pControlSet);
void GenBL_TDD1(LZSBYTE** ppBLCodePos, void* pDestination, void* pSource);
void GenBL_TDD2(LZSBYTE** ppBLCodePos, void* pDestination, void* pSource);
void GenBL_TDD4(LZSBYTE** ppBLCodePos, void* pDestination, void* pSource);
void GenBL_TDD8(LZSBYTE** ppBLCodePos, void* pDestination, void* pSource);
void GenBL_TID1(LZSBYTE** ppBLCodePos, void* pDestination, void** ppSourceSegment, LZSDWORD dwSourceOffset);
void GenBL_TID2(LZSBYTE** ppBLCodePos, void* pDestination, void** ppSourceSegment, LZSDWORD dwSourceOffset);
void GenBL_TID4(LZSBYTE** ppBLCodePos, void* pDestination, void** ppSourceSegment, LZSDWORD dwSourceOffset);
void GenBL_TID8(LZSBYTE** ppBLCodePos, void* pDestination, void** ppSourceSegment, LZSDWORD dwSourceOffset);
void GenBL_TDI1(LZSBYTE** ppBLCodePos, void** ppDestinationSegment, LZSDWORD dwDestinationOffset, void* pSource);
void GenBL_TDI2(LZSBYTE** ppBLCodePos, void** ppDestinationSegment, LZSDWORD dwDestinationOffset, void* pSource);
void GenBL_TDI4(LZSBYTE** ppBLCodePos, void** ppDestinationSegment, LZSDWORD dwDestinationOffset, void* pSource);
void GenBL_TDI8(LZSBYTE** ppBLCodePos, void** ppDestinationSegment, LZSDWORD dwDestinationOffset, void* pSource);
void GenBL_TDDC(LZSBYTE** ppBLCodePos, void* pDestination, void* pSource, LZSWORD wFromType, LZSWORD wToType);
void GenBL_TIDC(LZSBYTE** ppBLCodePos, void* pDestination, void** ppSourceSegment, LZSDWORD dwSourceOffset, LZSWORD wFromType, LZSWORD wToType);
void GenBL_TDIC(LZSBYTE** ppBLCodePos, void** ppDestinationSegment, LZSDWORD dwDestinationOffset, void* pSource, LZSWORD wFromType, LZSWORD wToType);
void GenBL_N(LZSBYTE** ppBLCodePos, LZSBOOL* pTarget);
void GenBL_UC(LZSBYTE** ppBLCodePos, void* pProgramData, LZSDWORD dwInstance);
void GenBL_UCBL(LZSBYTE** ppBLCodePos, void* pBLCode);
void GenBL_R(LZSBYTE** ppBLCodePos);
void GenBL_TDDS(LZSBYTE** ppBLCodePos, void* pDestination, void* pSource);
LZSDWORD GetBL_R_Size();
LZSBYTE GenBLCode(tTaskControl* pControlSet, LZSBOOL fFirstPass, LZSBYTE** ppBLCodePos, LZSBYTE* pUCodeSeg, LZSBYTE* pDataSeg);
tIpErrorCode IpRunBLCode(LZSBYTE* pBLCode);
#endif

void IpPflowDepositStartSequence (void);
LZSBOOL IpPflowDepositDataRecord (LZSWORD wIPOffs_p);
void IpPflowDepositStopSequence (void);
LZSWORD IpPflowGetAvailableBufferSize (void);

#define LZS_SET_ERROR(n)	(Error_g = n)
#define LZS_OR_STATUS(n)	(pCurrentProgramData_g->TaskData.m_Status |= n)

#endif  /* ifndef _IP_DEF_H_ */
