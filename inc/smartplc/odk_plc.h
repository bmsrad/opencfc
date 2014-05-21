/****************************************************************************

   Definition file to define project-global types and constants
   for data transfer between Codecreation/T&I/SKS/RTS/Interpreter

* 
****************************************************************************/



#ifndef _PLC_DEF_H_
#define _PLC_DEF_H_

#include "smartplc\odk_bas.h"

/* remove this define if your compiler knows the keyword to 
 * make structs one byte aligned 
 */
#define packed



/* ----------------------------------------------------------------------- */
/*                                                                         */
/*  Definition of Base-Types                                             */
/*                                                                         */
/* ----------------------------------------------------------------------- */



#define LZSTRUE  0xFF

#define LZSFALSE 0x00

#define LZSNULL 0



/* ----------------------------------------------------------------------- */
/*                                                                         */
/*  Definition of project specific types                                   */
/*                                                                         */
/* ----------------------------------------------------------------------- */

/*--------------------------------------------------------------------------- */
/* Segmenttypes */
/*--------------------------------------------------------------------------- */

/* This definition substitutes tLzsSegType */
typedef enum
{
   kPlcSegCode             = 0x00,       /* Codesegment */
   kPlcSegData             = 0x01,       /* Data segment of an instance */
   kPlcSegInit             = 0x02,       /* Initialization-data-segment */
   kPlcSegSource           = 0x03,       /* Programsource-Segment */
   kPlcSegSource2          = 0x04,       /* Programsource-Segment (continue) */
   kPlcSegTD               = 0x05,       /* Segment with Task Definition Table */
   kPlcSegPiAndMask        = 0x06,       /* Segment with AND-Mask process image */
   kPlcSegNiAndMask        = 0x07,       /* Segment with AND-Mask net image */
   kPlcSegIoTable          = 0x10,  /* <- new (RP2 Table) */
   kPlcSegIoTable2         = 0x11,  /* <- new (RP2 Table) continue */

   kPlcSegIoComplexTable   = 0x12,  /* <- the more complex table */
   kPlcSegIoComplexTable2  = 0x13,  /* <- the more complex table (continue) */

   kPlcSegInstanceTable    = 0x14,  /* instance table */
   kPlcSegInstanceTable2   = 0x15,  /* instance table (continue) */

   kPlcSegDownloadTable    = 0x16,  /* download table */
   kPlcSegDownloadTable2   = 0x17,  /* download table (continue) */
 
   kPlcSegNativeCode       = 0x18 , /* native code segment (new MR 230398) */
   kPlcSegInitSecond       = 0x19 , /* new section INPUT/OUTPUT-retain (MR 230398)    */
   
   kPlcSegIoSegment        = 0x20 ,      
   kPlcSegIoInitSegment    = 0x21 ,
   kPlcSegIoOldSegment     = 0x22 ,

   kPlcSegParameter        = 0x23,
   kPlcSegHardwareConfig   = 0x24,   

   kPlcSegDwlCopyTable     = 0x25, /* copy table for incremental download */    
   kPlcSegVarTable		     = 0x26, /* VarTable */
    
   /* ef 20040505 */
   kPlcOemVarInfoTable     = 0x27, /* additional Oem variables */

   kPlcSegNativeCode2      = 0x28, /* native code following segment */
   kPlcSegVarTable2	       = 0x29, /* VarTable */
   
   /*smart var table*/
   kPlcSegSmartVartable	   = 0x2a,
   kPlcSegSmartVartable2   = 0x2b,
   kPlcSegCopyVarList	   = 0x2c,
   
   /* error log/exception buffer/system error panel */
   kPlcSegErrorLog         = 0x30, /* pseudo-segment/identifier for error log information */
   kPlcSegExceptionBuffer  = 0x32, /* pseudo-segment/identifier for exception buffer information */
   kPlcSegSystemErrorPanel = 0x33, /* pseudo-segment/identifier for system error panel */
   kPlcSegErrorCtrl        = 0x34, /* pseudo-segment/identifier for error log control structure */
   
   kPlcSegCopyVarList2	   = 0x31,
    
   kPlcSegBLCodeSys        = 0x35, /* P0699-specific; for BL code of user function blocks */
   kPlcSegBLCodeNor        = 0x36, /* P0699-specific; for BL code of user function blocks */

   kPlcSegNcHelp           = 0x38,
   kPlcSegByRefInfo        = 0x39, /* link info for external variables */
   kPlcSegNativeCode3	   = 0x40, /* segment with patch table for far-access and call optimization */

   kPlcSegPI               = 0x80, /* Segment with Process Image */
   kPlcSegNI               = 0x81, /* Segment with Net Image */
   kPlcSegNVMap            = 0x82, /* Segment with Var. Mapping Table */
   kPlcSegInstStack        = 0x83, /* Instance-Stacksegment (Returnstack) */
   kPlcSegAEStack          = 0x84, /* AE Stacksegment */
   kPlcSegExtAE            = 0x85, /* Segment of external AE */
   kPlcSegExtAEs           = 0x86, /* Segment of external AEs */
   kPlcSegAETypeStck       = 0x87, /* optional Stack for AE-Type */

   kPlcSegBufferI1	 = 0xE0,		/* P0699-specific, buffer segments for data consistency */
   kPlcSegBufferI2	 = 0xE1,
   kPlcSegBufferI3	 = 0xE2,
   kPlcSegBufferI4	 = 0xE3,
   kPlcSegBufferI5	 = 0xE4,
   kPlcSegBufferI6	 = 0xE5,
   kPlcSegBufferI7	 = 0xE6,
   kPlcSegBufferI8	 = 0xE7,
   kPlcSegBufferT1	 = 0xE8,
   kPlcSegBufferT2	 = 0xE9,
   kPlcSegBufferT3	 = 0xEA,
   kPlcSegBufferT4	 = 0xEB,
   kPlcSegBufferT5	 = 0xEC,
  
   kPlcSegModTab           = 0xF0, /* table of hardware IO-modules (only for non-compact PLCs) */
   kPlcSegBinDcf           = 0xF1, /* binary DCF segment (only for CANopen extension) */
   kPlcSegOemSeg           = 0xF2, /* special OEM segments */

   kPlcSegBinMemImg = 0xF3,        /* segments with binary memory image for the CPU (e.g. Hex-File with maschine code) */
   kPlcSegOpcSegment = 0xF4,       /* segment Var2OpcItems for SmartOPC */
   /* [SYSTEC 09.05.2005 -rs] renamed <kPlcSegReserved5> in <kPlcSegSneBinCode> */
   kPlcSegSneBinCode = 0xF5,       /* segments with system native extension code for the CPU (native maschine code) */
   kPlcSegDcfAssignment  = 0xF6,   /* Powermap DCF assignment segment */

/*--------------------------------------------------------------------------- */
/* OEM-Segmenttypes */
/*--------------------------------------------------------------------------- */
   
   kPlcSegHwConfig   = 0xF7,        /* P0699-specific; for hardware configuration information */
   kPlcSegShmVars    = 0xF8,        /* P0699-specific; for rack-global shared memory variables */
   kPlcSegShmConfig  = 0xF9,        /* P0699-specific; for rack-global shared memory configuration (data consistency) */
   kPlcSegShmDCVars  = 0xFA,        /* P0699-specific; for all segments containing shared memory data consistency buffers */
   kPlcSegStaticNull = 0xFB,        /* P0699-specific; static null area for unresolved shared memory variables */
   kPlcSegHwConfigStation = 0xFC,   /* P0699-specific; for hardware configuration information */

   kPlcSegUndef      = 0xFF         /* Error detection */

} tPlcSegType;

/* structs to access segment header */
typedef packed struct
{
   tPlcOffset m_Length;               /* total length of the segment */
   LZSBYTE    m_SegType;              /* segment type */
   LZSBYTE    m_HeaderLength;         /* length of the header */
   tPlcSegNr  m_CorrespondingSegment; /* corresponding segment */

} tPlcHeaderDef;

typedef packed struct
{
   LZSWORD m_SegSize;      /* segment size */
   LZSBYTE m_SegType;      /* segment type */
   LZSBYTE m_HeaderSize;   /* header size */
   LZSWORD m_SecundarySeg; /* corresponding segment */

} tSegHeader;

typedef enum
{
    kPouTypeUndef = 0,
    kPouTypePrg = 1,   /* program POU */
    kPouTypeFb =2,     /* function block POU */
    kPouTypeFun = 3,   /* function POU */
    kPouTypeStdFb = 4, /* system function block (data already on PLC) */
    kPouTypeStdFun = 5 /* system function (data already on PLC) */

} tPouType;

typedef packed struct 
{
	/* see also LzsMemGetLinkerTableEntry in szm.c and 
		LzsInstantiateDataSegments in lzwdwl.c */
    LZSWORD m_wEntrySize;
    LZSWORD m_wDataSegNr;
    LZSWORD m_wIniSegNr;

} tSegLinkerTableEntry;

typedef packed struct 
{
    LZSWORD m_wInOutSize;
    LZSWORD m_wRetainInOutSize;
    LZSWORD m_wSpecialBytesSize;
    LZSWORD m_wOtherBytesSize;
    LZSWORD m_wRetainOtherBytesSize;
    
} tSegInitSegSections;


/*--------------------------------------------------------------------------- */
/* Typdefinitions to describe the TaskDefinitionSegment */
/*--------------------------------------------------------------------------- */

/* tLzsTaskType is replaced by this definition*/
/* See also tBrwTaskType in Odk_plc.h */
typedef packed enum
{
    kTaskUndef      = 0x00,
    kTaskCyclic     = 0x01,           /* cyclic program execution */
    kTaskTimer      = 0x02,           /* program start by timer */
    kTaskInterrupt  = 0x03,           /* program start by interrupt  */
/* =========== Additional OEM Task Types     */
    
    kTaskTypeOEM1   = 0x04,           /*  (1ms)  (Periodic) */
    kTaskTypeOEM2   = 0x05,           /*  (1..50ms) */
    kTaskTypeOEM3   = 0x06,           /*  (1..50ms) */
    kTaskTypeOEM4   = 0x07,           /*  (Operatingsystem) */
    kTaskMax        = 0x08,           
    kTaskGlobals    = 0x50,           /* global deklaration POU's are compiled as Tasks   //s.a. 28101998 */
    kTaskDirectGlobals  = 0x51,       /* direct global deklaration POU's are compiled as Tasks //s.a. 28101998 */
       
    kTaskDummy      = 0x101           /* Dummy value to force 2 byte enum */

} tPlcTaskType;

typedef enum
{
    kTaskStateWait          = 0x00,
    kTaskStateSleep         = 0x01,
    kTaskStateRun           = 0x02,
    kTaskStateInterrupted   = 0x04

} tPlcTaskState;

/* tSksVersion and tLzsVersion are replaced by this definition*/
typedef packed struct
{
   LZSDWORD        m_TimeStamp;        /* Timestamp */

} tPlcVersion;

typedef packed struct
{
    LZSBYTE        m_IpVariante;       /* Interpreterversion (1.*) */
    LZSBYTE        m_IpOem;            /* OEM of Ip;  = 1 */
    LZSBYTE        m_IpUmfang;         /* command scope, defined by OEM */
    LZSBYTE        m_IpRevision;       /* Revision of Interpreter (*.0) */

} tPlcIpVer;

typedef packed struct
{
   LZSWORD         m_cInstStackSize;   /* Number of entries in InstanceStack */
   LZSWORD         m_cAEStackEntrys;   /* Number of entries in AE-Stack */
   LZSWORD         m_cAEStackSize;     /* Segmentsize AE-Stack */
   LZSWORD         m_cExtAESize;       /* Segmentsize external AE */

} tPlcStackSizes;

typedef packed struct   
{
   LZSWORD         m_cSize;            /* Segmentsize process image */
   tPlcOffset   m_StartInput;       /* StartOffset of input */
   tPlcOffset   m_StartOutput;      /* StartOffset of output */
   tPlcOffset   m_StartMarker;      /* StartOffset of Marker */
 
} tPlcPIValues;

typedef packed struct
{
   LZSWORD         m_cSize;            /* Segmentsize net image */
   tPlcOffset   m_StartInput;       /* StartOffset input net image */
   tPlcOffset   m_StartOutput;      /* StartOffset output net image */

} tPlcNIValues;

typedef packed struct
{
   tPlcSegNr    m_Seg;              /* Segmentnumber for net image */
   tPlcSegNr    m_AndMask;          /* AndMask for PA SegmentNo    */

} tPlcImageSegments;

/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*      DO NOT USE THE FOLLOWING STRUCTURES IN THE RUNTIME SYSTEM                   */
/*                                                                                  */
/*      STRUCTURE ALIGNMENT MAY BE INCORRECT ON YOUR PLC                            */
/*                                                                                  */
/*      USE MACROS FROM STRUCT.H  INSTEAD                                           */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*                                                                                  */
/*      tPlcTaskDefSegment                                                          */
/*          tPlcHeaderDef                                                           */
/*          tPlcTaskDefTable                                                        */
/*              tPlcTaskDefEntry                                                    */
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*                                                                                  */
/*          tPlcDownloadTableSegHeader                                              */
/*          tPlcDownloadTableEntry                                                  */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

/* tLzsTaskDefEntry is replaced by this definition*/
typedef packed struct
{
    LZSCHAR            m_szPgmName[32];  /* Program name                    0   +32*/
    tPlcPgmNr          m_nPrg;           /* program number                  32  +2*/
    
    /* -fg- 19990310 use LZSWORD for mTaskType because enum is platform depended */
    /*tPlcTaskType       m_TaskType;      // Program type */
    LZSWORD            m_TaskType;       /* Program type                    34  +2*/
    LZSDWORD              m_dTimeSpec;      /* at TimerTask: timeintervall 36  +4*/
    LZSDWORD              m_ulPrgNWDependencies;  /*                        40  +4*/
    LZSDWORD              m_ulPrgProperties;/*                              44  +4*/
    tPlchInst          m_MainInst;       /* Handle of Main-POE              48  +2*/
    LZSDWORD              m_Flags;          /* general Flags, must be 0  50  +4*/
    tPlcStackSizes     m_StackSizes;     /* sizes of the stacks             54  +8*/
    tPlcImageSegments  m_PISegments;     /* semgent no of PI                62  +4*/
    tPlcImageSegments  m_NISegments;     /* segment no of NI                66  +4*/
    tPlcVersion        m_PrgVersion;     /* program version                 70  +4*/

    /* B.S. 30.1.98 */
    LZSWORD               m_cSegs;          /* number of segments           74  +2*/
    tPlcSegNr          m_MaxSegNr;       /* max segment number              76  +2*/
    
    /* B.S. 18.05.98 */
    LZSWORD             m_wPriority;        /* Priority                     78  +2*/

    /* -fg- 19990511 for sceduling */
    LZSWORD             m_wCurrentPrio;     /* dynamic proiority for sceduling  80 +2*/
    LZSWORD             m_wTaskState;       /* state of task i.e. sleeping,waiting,running  82 +2*/

    /* ======= infoteam Adds Here */
    LZSBYTE               m_dummy1[4];
          
/* ============================================================================================= */
/* OEM Specific Section */
/* */
/* In order to reintegrate code to and from the customer, it is necessary to divide the code */
/* in infoteam and OEM sections in such a way that the OEM part can be distinguished and */
/* removed. Furthermore, to give infoteam and the customer the ability to add code independent. */
/* ============================================================================================= */
    LZSDWORD              m_tHandle;        /* task handle for MK2 (fake type, resolved within lzs)     88  +4*/
    LZSDWORD              m_Trigger;        /* trigger (semaphore) for interupt task                    92  +4*/
    LZSBYTE               m_bRunMode;       /* Run mode set to task (see LzsIp)                         96  +1*/
    LZSBYTE               m_bConnected;     /* Set LZSTRUE when MK2 variables have been connected           97  +1*/
    
    /* ======= OEM Adds Here */
    LZSBYTE               m_dummy2[8];       /*                                                         98  +8*/
   
   
   
} tPlcTaskDefEntry; /*size 106*/

/* DtPlcTaskDefTable is replaced by this definition*/
typedef packed struct
{
    LZSCHAR               m_szPrjName[32];  /* Projectname                      0   +32*/
    LZSCHAR               m_szResName[32];  /* Resourcename                     32  +32 */
    tPlcIpVer          m_IpVer;          /* neccessary Interpreter version      64  +4*/
    tPlcVersion        m_PlcVer;         /* Versionnumber of Resource           68  +4*/
    LZSWORD               m_cProgs;         /* Number of programs               72  +2*/
    
    LZSWORD               m_cSegs;          /* number of segments               74  +2*/
    tPlcSegNr          m_MaxSegNr;       /* max segnr                           76  +2*/
    
    LZSDWORD              m_Flags;          /* common Flags                     78  +4*/
    
    tPlcPIValues       m_PI;             /* description of the process image    82  +8*/
    tPlcNIValues       m_NI;             /* description of the net image        90  +6*/
    
    LZSDWORD               m_dwBuildDate;    /* Creatin date of Resource        96  +4  -ae- 01/15/1999 */
    LZSDWORD               m_dwLoadDate;     /* Download date of Resource     100 +4  -ae- 01/15/1999 */
    
    LZSBYTE             m_bAlignment;     /* Alignment used in data segments    104 +1*/
    
    /* ======= infoteam Adds Here */
    LZSBYTE               m_dummy2[11];      /* space for further flags         105 +11 / Array verkleinert von 20 auf 12 Bytes -ae- 01/15/1999              */

/* ============================================================================================= */
/* OEM Specific Section */
/* */
/* In order to reintegrate code to and from the customer, it is necessary to divide the code */
/* in infoteam and OEM sections in such a way that the OEM part can be distinguished and */
/* removed. Furthermore, to give infoteam and the customer the ability to add code independent. */
/* ============================================================================================= */
    /* ======= OEM Adds Here */
#ifdef _LZS_OEMVERSINFO_
	LZSWORD				  m_wOemVerMajor;		/*OEM version info 116 + 2*/
	LZSWORD				  m_wOemVerMinor;		/*OEM version info 118 + 2*/
	LZSWORD				  m_wOemVerRevision;	/*OEM version info 120 + 2*/
	LZSWORD				  m_wOemVerBuild;		/*OEM version info 122 + 2*/
    LZSBYTE               m_dummy3[4];			/* space for further flags         124 + 4*/
#else
    LZSBYTE               m_dummy3[12];      /* space for further flags         116 +12          */
#endif

    tPlcTaskDefEntry   m_Pgm[1];         /* description of the Tasks            128 +*/

} tPlcTaskDefTable;     /*size 234 for one program*/


/* MR 221196 - Definition of task definition segment */
typedef packed struct
{
   tPlcHeaderDef    m_DefHeader;      /* header */
   tPlcTaskDefTable m_DefTable;       /* table */

} tPlcTaskDefSegment;

/* struct for entries in the retain table */
typedef struct
{
   LZSWORD    m_wTaskNr; /* number of the program that the retain data belongs to */
   tPlcMemPtr m_pData;   /* pointer to the retain data */
   LZSWORD    m_wSegNr;  /* number of the data segment where the retain data area is located */
   LZSWORD    m_wOffset; /* offset in the data segment to the retain data area */
   LZSWORD    m_wSize;   /* size in bytes of the retain data */

} tLzsRetainTableEntry;

#define tLzsProjectData tPlcTaskDefTable /* Compatibility */

/* ae 1999/04/30: entries of the IO-configuration table */
typedef struct
{
    LZSDWORD                dwHardwareAddress;          /* Node ID or busaddress */
    LZSWORD             wInputs;                    /* Number of input bytes */
    LZSWORD             wInputOffset;               /* Input Offset in Bytes */
    LZSWORD             wOutputs;                   /* Number of output bytes */
    LZSWORD                 wOutputOffset;              /* OutputOffset in bytes */
    LZSCHAR             szModuleName[33];           /* Name of the module */
    
} tLzsHardwareModuleTableEntry;

/* ----------------------------------------------------------------------- */
/*                                                                         */
/*  DownloadTableSegment                                                   */
/*                                                                         */
/* ----------------------------------------------------------------------- */
typedef packed struct
{
    LZSWORD m_wLength;              /*length of the table*/
    LZSBYTE m_bSegId;               /*id of the segment*/
    LZSBYTE m_bLengthOfHeader;      /*length of header*/
    LZSWORD m_wNextSegment;			/*next segment of table (0 if last)*/
    LZSWORD m_wNoOfPOUs;			/*number of different POUs*/
    
} tPlcDownloadTableSegHeader;

typedef packed struct
{	
	LZSDWORD	m_dwIniSegChecksum;		/* initial data segment check sum  */
	LZSDWORD	m_dwCodeSegChecksum;	/* code segment check sum */

	LZSWORD     m_wIniSegNr;		/* initial data segment id */
	LZSWORD     m_wDataSegNr;		/* data segment id */
	LZSWORD     m_wCodeSegNr;		/* code segment id */
	LZSWORD     m_wNcSegNr;			/* native code segment id, or 0 if not available */

	/* additional data is appended to the above members:

	LZSBYTE		m_bPouNameLength;
	LZSCHAR		m_szPouName[ m_wPouNameLength ]   (without \0)

	if (m_wDataSegNr == 0)  // -> there are multiple instances of POU 
	{
		LZSWORD		m_wNumInstances;	
		// foreach instance
		LZSWORD		m_wInstDataSegNr;	// the instance's data segment nr
		LZSBYTE		m_bInstNameLen;	// Version 1
		LZSWORD		m_wInstNameLen;	// Version 2
		LZSCHAR		m_szInstName[ m_bInstNameLen ]	(without \0)		
	} else {
		// there is only one instance, its data segment number is m_wDataSegNr 
	}
	*/
} tPlcDownloadTableEntry;


/* ----------------------------------------------------------------------- */
/*                                                                         */
/*  Network variables tables                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */

typedef enum {
    kNWVBit, kNWVByte, kNWVWord, kNWVDWord /* can be extended */
} tPlcNetVarType;

typedef enum {
    kNWVI, kNWVO, kNWVIO
} tPlcNetDir;

typedef enum {
    kNWVAbs, kNWVDIAnet
} tPlcNetAdrType;

typedef packed struct {
    LZSWORD         m_ID;           /* Entry identifier */
    tPlcNetVarType  m_VarType;      /* variable format */
    tPlcNetDir      m_Dir;          /* data direction */
    LZSWORD         m_NodeId;       /* node id */
    LZSBYTE         m_PDONr;        /*  */
    LZSWORD         m_ObjectId;     /* identifier in object dictionary */
    LZSBYTE         m_SubId;        /* subidentifier in object dictionary */
    LZSWORD         m_CobId;        /* COB identifier from the CiA specification */
    tPlcNetAdrType  m_AdrType;      /* type of address */
} tPlcNetVarTab;


typedef tPlcOffset tPlcOffs16;
typedef tPlcByteCount tSksByteCount;


typedef LZSDWORD tPlcHandle;




/* [SYSTEC/CANopen 2006/11/17] definition of LZS_SEG_HEADER_SIZE new inserted */
#if defined (_LZS_DSALIGNMENT_1_)
    /* 1-Byte-Alignment */
    #define LZS_SEG_HEADER_SIZE     ((sizeof(tSegHeader)))
#elif defined (_LZS_DSALIGNMENT_2_)
    /* 2-Byte-Alignment */
    #define LZS_SEG_HEADER_SIZE     ((sizeof(tSegHeader) + 0x0000001) & ~0x00000001)
#elif defined (_LZS_DSALIGNMENT_4_)
    /* 4-Byte-Alignment */
    #define LZS_SEG_HEADER_SIZE     ((sizeof(tSegHeader) + 0x0000003) & ~0x00000003)
#else
    #error "No or unknown Alignment defined"
#endif

#endif  /* ifndef _PLC_DEF_H_ */
