/**********************************************************************

  (c) 1998 infoteam Software GmbH, D-91088 Bubenreuth, Am Bauhof 4


 ----------------------------------------------------------------------


   Definition file memory access modul

   27.01.1997   -rs


 **********************************************************************/

#ifndef _ODK_SZM_H_
#define _ODK_SZM_H_

#define packed

LZSBYTE LzsGetSegHeaderSize(tPlcMemPtr pSeg_p);

/*--------------------------------------------------------------------------- */
/* Macros                                                                     */
/*--------------------------------------------------------------------------- */
    
#define LZSLOBYTE(w)                    ((LZSBYTE)((w) & 0x00FF))
#define LZSHIBYTE(w)                  ((LZSBYTE)(((LZSSINT)(w) >> 8) & 0x00FF))

#define LZSLOWORD(l)                       ((LZSWORD)(LZSDWORD)(l) & 0xFFFF)
#define LZSHIWORD(l)                       ((LZSWORD)((((LZSDWORD)(l)) >> 16) & 0xFFFF))

#ifdef _LZS_8BITBYTES_
#define LZSBYTECAST(arg)            (LZSBYTE)(arg)
#define LZSWORDCAST(arg)            (LZSWORD)(arg)
#else
#define LZSBYTECAST(arg)            ((LZSBYTE)((arg) & 0xFF))
#define LZSWORDCAST(arg)            ((LZSWORD)((arg) & 0xFFFF))
#endif

#define LZSMIN(arg1, arg2)            (((arg1) < (arg2)) ? (arg1) : (arg2))
#define LZSMAX(arg1, arg2)            (((arg1) > (arg2)) ? (arg1) : (arg2))                    


/*--------------------------------------------------------------------------- */
/* Definitions */
/*--------------------------------------------------------------------------- */

/*
#define SEGSIZE(pSeg)     (*(LZSWORD LZSFAR *)(pSeg))
#define HEADERSIZE(pSeg)  ((LZSWORD) *((LZSBYTE LZSFAR *)pSeg+3))
*/

/*20050801MSc: */
/*
#define HEADERSIZE(pSeg)  ((LZSWORD) *((LZSBYTE LZSFAR *)pSeg+3))
*/

#ifdef _LZS_16BITBYTES_
    #define HEADERSIZE(pSeg)  (LzsGetSegHeaderSize((LZSBYTE*)pSeg) >> 1) /* get the right size for TMS */
    #define CORRECT_SIZE(s)      (s = s>>1) 
    #define DE_CORRECT_SIZE(s) (s = s<<1) 
    #define SEGSIZE(pSeg)     (*(LZSWORD LZSFAR *)(pSeg))
    #define LZS_REFOFFSET        2
#else
    #ifdef _LZS_32BITBYTES_
        #define HEADERSIZE(pSeg)  (LzsGetSegHeaderSize((LZSBYTE*)pSeg) >> 2) /* get the right size for TMS */
        #define CORRECT_SIZE(s)      (s = s>>2) 
        #define DE_CORRECT_SIZE(s) (s = s<<2) 
        #define SEGSIZE(pSeg)     (*(LZSDWORD LZSFAR *)(pSeg))
        #define LZS_REFOFFSET 4
    #else
        #define HEADERSIZE(pSeg)  (LzsGetSegHeaderSize(pSeg))  /*((LZSWORD) *((LZSBYTE LZSFAR *)pSeg+3)) */
        #define CORRECT_SIZE(s)
        #define DE_CORRECT_SIZE(s)
        #define SEGSIZE(pSeg)     (*(LZSWORD LZSFAR *)(pSeg))
        #define LZS_REFOFFSET 2
    #endif
#endif

#define SIZE_OF_AE LZS_SIZEOF_DWORD /* size of an entry in the AE-stack */

#define SIZE_OF_IS_ENTRY (3 * LZS_SIZEOF_DWORD) /* size of an entry in the instance stack */



/*--------------------------------------------------------------------------- */
/* Type definitions */
/*--------------------------------------------------------------------------- */

/* the following structure is used for data exchange between interpreter */
/* and memory access module. It is used: */
/* - Initialization of memory access module */
/* - saving task state before interruption of interpreter */
/* - restoring of task state after interruption of interpreter  */
/* This structure contains data from the struct <tIpTaskData> that is  */
/* relevant to the memory access module. This structure is a extarct of */
/* <tIpTaskData>. For exchanging data between these structures ( <tIpTaskData> */
/* and <tLzsMemTask> ) there are responsible conversion functions of SZM. */

typedef packed struct
{
   /* Initialization data (to be passed by IP) */
   tPlchInst   m_MainInst;          /* Handle Main-Instance ( CS / DS ) */
   tPlcSegNr   m_SegInstStack;      /* Segment-No. Instance-Stack */
   tPlcSegNr   m_SegAEStack;        /* Segment-No. AE-Stack */
   tPlcSegNr   m_SegExtAE;          /* Segment-No. external AE  (for ANY) */
   tPlcSegNr   m_SegExtAEs;         /* Segment-No. external AEs (for ANY) */

   /* buffer area for Save-/Restore */
   tPlcMemPtr  m_CurrCS;            /* Baseaddress current CS of instance */
   tPlcMemPtr  m_CurrDS;            /* Baseaddress current DS of instance */
   tPlcMemPtr  m_CurrIP;            /* current IP of instance */
   tPlcMemPtr  m_CurrInstSP;        /* current SP InstStack of instance */
   tPlcMemPtr  m_CurrAESP;          /* current SP AEStack of instance */
   tPlcMemPtr  m_CurrExtAE;         /* Baseaddress external AE  (for ANY) */
   tPlcMemPtr  m_CurrExtAEs;        /* Baseaddress external AEs (for ANY) */

   LZSWORD        m_UsedIStackEntrys;  /* current Stackdepth Instance-Stack */
   LZSWORD        m_MaxIStackEntrys;   /* max. Stackdepth Instance-Stack */
   LZSWORD        m_UsedAStackEntrys;  /* current Stackdepth AE-Stack */
   LZSWORD        m_MaxAStackEntrys;   /* max. Stackdepth AE-Stack */

} tLzsMemTask;


/* Definition if initialization modes */
typedef enum
{
   kLzsInitCold     = 0x00,         /* Restore incl. Retain */
   kLzsInitWarm     = 0x01          /* Restor besides of Retain */

} tLzsInitMode;


/* definition of choice for external AE (for LzsMemXxxGetAny) */
typedef enum
{
   kLzsExtAE        = 0x00,         /* Target = ExtAE */
   kLzsExtAEs       = 0x01          /* Target = ExtAEs */

} tLzsExtAESel;


/*--------------------------------------------------------------------------- */
/* Prototyps of functions used by the interpreter */
/*--------------------------------------------------------------------------- */

#ifdef _IPTASKDATA_
   /* these functions of SZM are also used by other modules, */
   /* which know nothing about <tIpTaskData> ! */
   void  LZSPUBLIC  LzsMemInitTask     (tIpTaskData LZSFAR *pIpTaskData_p);
   void  LZSPUBLIC  LzsMemSaveTask     (tIpTaskData LZSFAR *pIpTaskData_p);
   void  LZSPUBLIC  LzsMemRestoreTask  (tIpTaskData LZSFAR *pIpTaskData_p);
#endif

void  LZSPUBLIC  LzsMemSetInstSeg   (tPlchInst  hInst_p);


/***************************/
/*	SZM NEAR DATA ACCESS   */
/***************************/

void  LZSPUBLIC  LzsMemNearSetBit   (tPlcBitAdr Addr_p, LZSBOOL  BitVal_p);
void  LZSPUBLIC  LzsMemNearSetAny   (tPlcOffset Addr_p);
void  LZSPUBLIC  LzsMemNearSetString   (tPlcOffset Addr_p);
void  LZSPUBLIC  LzsMemNearSetArray   (tPlcOffset Addr_p);
void  LZSPUBLIC  LzsMemNearSetStringParam (LZSCONST LZSCHAR LZSFAR* pStr, tPlcOffset pDstNearOffs_p, LZSWORD wCount);
tPlcMemPtr  LZSPUBLIC LzsMemNearGetString   (tPlcOffset Addr_p);
tPlcMemPtr  LZSPUBLIC LzsMemNearGetParamAddr  (tPlcOffset Addr_p);
LZSBOOL        LZSPUBLIC LzsMemNearGetBit  (tPlcBitAdr Addr_p);
void  LZSPUBLIC LzsMemNearGetAny  (tPlcOffset Addr_p, LZSBYTE Sel_p);
void  LZSPUBLIC LzsMemNearGetPointer  (tPlcOffset Addr_p, tPlcPointerInfo LZSFAR *pPointer_p);
float LZSPUBLIC LzsMemNearGetFloat(tPlcOffset Addr_p);
void LZSPUBLIC LzsMemNearSetFloat(tPlcOffset Addr_p, float FloatVal_p);

#define LZS_MEM_NEAR_SET_STRING(Addr_p) LzsMemNearSetString(Addr_p)
#define LZS_MEM_NEAR_GET_STRING(Addr_p) LzsMemNearGetString(Addr_p)
#define LZS_MEM_NEAR_GET_PARAM_ADDR(Addr_p) LzsMemNearGetParamAddr(Addr_p);
#define LZS_MEM_NEAR_GET_POINTER(addr,pointer)    LzsMemNearGetPointer(addr, pointer)

#ifndef _LZS_SZM_INLINE_
    void  LZSPUBLIC  LzsMemNearSetByte  (tPlcOffset Addr_p, LZSBYTE  ByteVal_p);
    void  LZSPUBLIC  LzsMemNearSetWord  (tPlcOffset Addr_p, LZSWORD  WordVal_p);
    void  LZSPUBLIC  LzsMemNearSetDword (tPlcOffset Addr_p, LZSDWORD DwordVal_p) LZSLARGE;
#ifdef _IP_8BYTEDATA_
    void  LZSPUBLIC  LzsMemNearSetQword (tPlcOffset Addr_p, LZSQWORD QwordVal_p) LZSLARGE;
#endif
    LZSBYTE  LZSPUBLIC  LzsMemNearGetByte  (tPlcOffset Addr_p);
    LZSWORD  LZSPUBLIC  LzsMemNearGetWord  (tPlcOffset Addr_p);    
    LZSDWORD LZSPUBLIC  LzsMemNearGetDword (tPlcOffset Addr_p);
#ifdef _IP_8BYTEDATA_
    LZSQWORD LZSPUBLIC  LzsMemNearGetQword  (tPlcOffset Addr_p);    
#endif
#ifdef _LZS_DSALIGNMENT_DSP563_
    void LzsMemNearGetHandle (tPlcOffset Addr_p,LZSWORD * pwChildInstance_p,LZSWORD * pwExtension_p);
#endif    

    #define LZS_MEM_NEAR_SET_BYTE(Addr_p,ByteVal_p) LzsMemNearSetByte(Addr_p,ByteVal_p)
    #define LZS_MEM_NEAR_SET_WORD(Addr_p,WordVal_p) LzsMemNearSetWord(Addr_p,WordVal_p)
    #define LZS_MEM_NEAR_SET_DWORD(Addr_p,DwordVal_p) LzsMemNearSetDword(Addr_p,DwordVal_p)
#ifdef _IP_8BYTEDATA_
    #define LZS_MEM_NEAR_SET_QWORD(Addr_p,QwordVal_p) LzsMemNearSetQword(Addr_p,QwordVal_p)
#endif
    #define LZS_MEM_NEAR_GET_BYTE(Addr_p) LzsMemNearGetByte(Addr_p)
    #define LZS_MEM_NEAR_GET_WORD(Addr_p) LzsMemNearGetWord(Addr_p)
    #define LZS_MEM_NEAR_GET_DWORD(Addr_p) LzsMemNearGetDword(Addr_p)
#ifdef _IP_8BYTEDATA_
    #define LZS_MEM_NEAR_GET_QWORD(Addr_p) LzsMemNearGetQword(Addr_p)
#endif
#else
    #define LZS_MEM_NEAR_SET_BYTE(Addr_p,ByteVal_p) {*(LZSBYTE LZSFAR*)(RegDS + (LZSDWORD)(Addr_p)) = ByteVal_p;}
    #define LZS_MEM_NEAR_SET_WORD(Addr_p,WordVal_p) {*(LZSWORD LZSFAR*) (RegDS + (LZSDWORD)(Addr_p)) = WordVal_p;}
    #define LZS_MEM_NEAR_SET_DWORD(Addr_p,DwordVal_p) {*(LZSDWORD LZSFAR*) (RegDS + (LZSDWORD)(Addr_p)) = DwordVal_p;}
#ifdef _IP_8BYTEDATA_
    #define LZS_MEM_NEAR_SET_QWORD(Addr_p,QwordVal_p) {*(LZSQWORD LZSFAR*) (RegDS + (LZSQWORD)(Addr_p)) = QwordVal_p;}
#endif
    #define LZS_MEM_NEAR_GET_BYTE(Addr_p)  *(LZSBYTE LZSFAR*)(RegDS + (LZSDWORD)(Addr_p))
    #define LZS_MEM_NEAR_GET_WORD(Addr_p)  *(LZSWORD LZSFAR*)(RegDS + (LZSDWORD)(Addr_p))
    #define LZS_MEM_NEAR_GET_DWORD(Addr_p)  *(LZSDWORD LZSFAR*)(RegDS + (LZSDWORD)(Addr_p))
#ifdef _IP_8BYTEDATA_
    #define LZS_MEM_NEAR_GET_QWORD(Addr_p)  *(LZSQWORD LZSFAR*)(RegDS + (LZSDWORD)(Addr_p))
#endif
#endif


/***************************/
/*	SZM FAR DATA ACCESS    */
/***************************/

void  LZSPUBLIC  LzsMemFarSetString (tPlchInst hInst_p, tPlcOffset Addr_p);
void  LZSPUBLIC  LzsMemFarSetBit    (tPlchInst hInst_p, tPlcBitAdr Addr_p, LZSBOOL  BitVal_p);
void  LZSPUBLIC  LzsMemFarSetAny    (tPlchInst hInst_p, tPlcOffset Addr_p);
void  LZSPUBLIC  LzsMemFarSetArray  (tPlchInst hInst_p, tPlcOffset Addr_p);

LZSBOOL  LZSPUBLIC  LzsMemFarGetBit    (tPlchInst hInst_p, tPlcBitAdr Addr_p);


#ifndef _LZS_SZM_INLINE_
    void  LZSPUBLIC  LzsMemFarSetByte   (tPlchInst hInst_p, tPlcOffset Addr_p, LZSBYTE  ByteVal_p);
    void  LZSPUBLIC  LzsMemFarSetWord   (tPlchInst hInst_p, tPlcOffset Addr_p, LZSWORD  WordVal_p);
    void  LZSPUBLIC  LzsMemFarSetDword  (tPlchInst hInst_p, tPlcOffset Addr_p, LZSDWORD DwordVal_p) LZSLARGE;
    LZSBYTE  LZSPUBLIC  LzsMemFarGetByte   (tPlchInst hInst_p, tPlcOffset Addr_p);
    LZSWORD  LZSPUBLIC  LzsMemFarGetWord   (tPlchInst hInst_p, tPlcOffset Addr_p);
    LZSDWORD LZSPUBLIC  LzsMemFarGetDword  (tPlchInst hInst_p, tPlcOffset Addr_p);

    #define LZS_MEM_FAR_SET_BYTE(hInst_p,Addr_p,ByteVal_p) LzsMemFarSetByte(hInst_p,Addr_p,ByteVal_p)
    #define LZS_MEM_FAR_SET_WORD(hInst_p,Addr_p,WordVal_p) LzsMemFarSetWord(hInst_p,Addr_p,WordVal_p)
    #define LZS_MEM_FAR_SET_DWORD(hInst_p,Addr_p,DwordVal_p) LzsMemFarSetDword(hInst_p,Addr_p,DwordVal_p)
    #define LZS_MEM_FAR_GET_BYTE(hInst_p,Addr_p) LzsMemFarGetByte(hInst_p,Addr_p)
    #define LZS_MEM_FAR_GET_WORD(hInst_p,Addr_p) LzsMemFarGetWord(hInst_p,Addr_p)
    #define LZS_MEM_FAR_GET_DWORD(hInst_p,Addr_p) LzsMemFarGetDword(hInst_p,Addr_p)    
#else
    #define LZS_MEM_FAR_SET_BYTE(hInst_p,Addr_p,ByteVal_p) {*(LZSBYTE LZSFAR*)(LzsSegGetAddr (hInst_p, kPlcSegData) + (LZSDWORD)(Addr_p)) = ByteVal_p;}
    #define LZS_MEM_FAR_SET_WORD(hInst_p,Addr_p,WordVal_p) {*(LZSWORD LZSFAR*)(LzsSegGetAddr (hInst_p, kPlcSegData) + (LZSDWORD)(Addr_p)) = WordVal_p;}
    #define LZS_MEM_FAR_SET_DWORD(hInst_p,Addr_p,DwordVal_p) {*(LZSDWORD LZSFAR*)(LzsSegGetAddr (hInst_p, kPlcSegData) + (LZSDWORD)(Addr_p)) = DwordVal_p;}
    #define LZS_MEM_FAR_GET_BYTE(hInst_p,Addr_p)  *(LZSBYTE LZSFAR*)(LzsSegGetAddr (hInst_p, kPlcSegData) + (LZSDWORD)(Addr_p))
    #define LZS_MEM_FAR_GET_WORD(hInst_p,Addr_p)  *(LZSWORD LZSFAR*)(LzsSegGetAddr (hInst_p, kPlcSegData) + (LZSDWORD)(Addr_p))
    #define LZS_MEM_FAR_GET_DWORD(hInst_p,Addr_p)  *(LZSDWORD LZSFAR*)(LzsSegGetAddr (hInst_p, kPlcSegData) + (LZSDWORD)(Addr_p))
#endif

/*******************************/
/*	SZM SEG FAR DATA ACCESS    */
/*******************************/
extern LZSWORD LzsGetSegSegmentSize(tPlcMemPtr pSeg_p);
extern LZSDWORD  LZSPUBLIC  LzsMemSegFarGetDword (tPlchInst hInst_p,void LZSFAR * pSegTab_p, tPlcOffset Addr_p);

void  LZSPUBLIC  LzsMemSegFarSetBit (tPlchInst hInst_p,void LZSFAR * pSegTab_p, tPlcBitAdr Addr_p, LZSBOOL BitVal_p);

LZSBOOL  LZSPUBLIC  LzsMemSegFarGetBit (tPlchInst hInst_p,void LZSFAR *pSegTab_p, tPlcBitAdr Addr_p);
void  LZSPUBLIC  LzsMemFarGetAny    (tPlchInst hInst_p, tPlcOffset Addr_p, LZSBYTE Sel_p);



#ifndef _LZS_SZM_INLINE_
    void  LZSPUBLIC  LzsMemSegFarSetByte (tPlchInst hInst_p,void LZSFAR * pSegTab_p,  tPlcOffset Addr_p, LZSBYTE ByteVal_p);
    LZSBYTE  LZSPUBLIC  LzsMemSegFarGetByte (tPlchInst hInst_p,void LZSFAR* pSegTab_p, tPlcOffset Addr_p);
    LZSWORD  LZSPUBLIC  LzsMemSegFarGetWord (tPlchInst hInst_p,void LZSFAR* pSegTab_p, tPlcOffset Addr_p);

    #define LZS_MEM_SEG_FAR_SET_BYTE(hInst_p,pSegTab_p,Addr_p,ByteVal_p) LzsMemSegFarSetByte(hInst_p,pSegTab_p,Addr_p,ByteVal_p)
    #define LZS_MEM_SEG_FAR_SET_DWORD(hInst_p,pSegTab_p,Addr_p,DwordVal_p) LzsMemSegFarSetDword(hInst_p,pSegTab_p,Addr_p,DwordVal_p)
    #define LZS_MEM_SEG_FAR_GET_BYTE(hInst_p,pSegTab_p,Addr_p) LzsMemSegFarGetByte(hInst_p,pSegTab_p,Addr_p)
    #define LZS_MEM_SEG_FAR_GET_WORD(hInst_p,pSegTab_p,Addr_p) LzsMemSegFarGetWord(hInst_p,pSegTab_p,Addr_p)
#else
    #define LZS_MEM_SEG_FAR_SET_BYTE(hInst_p,pSegTab_p,Addr_p,ByteVal_p) {*(LZSBYTE LZSFAR*)(LzsSegGetAddrSeg (hInst_p,(void LZSFAR *)pSegTab_p, kPlcSegData) + (LZSDWORD)(Addr_p)) = ByteVal_p;}
    #define LZS_MEM_SEG_FAR_GET_BYTE(hInst_p,pSegTab_p,Addr_p)  *(LZSBYTE LZSFAR*)(LzsSegGetAddrSeg (hInst_p,(void LZSFAR *)pSegTab_p, kPlcSegData) + (LZSDWORD)(Addr_p))
    #define LZS_MEM_SEG_FAR_GET_WORD(hInst_p,pSegTab_p,Addr_p)  *(LZSWORD LZSFAR*)(LzsSegGetAddrSeg (hInst_p,(void LZSFAR *)pSegTab_p, kPlcSegData) + (LZSDWORD)(Addr_p)) 
    #define LZS_MEM_SEG_FAR_SET_DWORD(hInst_p,pSegTab_p,Addr_p,DwordVal_p) {*(LZSDWORD LZSFAR*)(LzsSegGetAddrSeg (hInst_p,(void LZSFAR *)pSegTab_p, kPlcSegData) + (LZSDWORD)(Addr_p)) = DwordVal_p;}
#endif



/***************************/
/*	SZM CODE DATA ACCESS   */
/***************************/

void  LZSPUBLIC  LzsMemCodeSetPos   (tPlcOffset IPAddr_p);
LZSWORD  LZSPUBLIC  LzsMemCodeGetPos   (void);
LZSBYTE  LZSPUBLIC LzsMemCodePrefetchInstr (void);
LZSBYTE  LZSPUBLIC  LzsMemCodeGetInstr (void);    /* All accesses correspond to the */
LZSBYTE  LZSPUBLIC  LzsMemCodeGetByte  (void);    /* internal "Cache-Register" of the RTS! */
LZSWORD  LZSPUBLIC  LzsMemCodeGetWord  (void);    /* The interpreter doesn't know the current */
LZSDWORD LZSPUBLIC  LzsMemCodeGetDword (void);    /* address in CS! */
void  LZSPUBLIC  LzsMemCodeGetAny   (LZSBYTE Sel_p);
LZSBYTE  LZSPUBLIC  LzsMemCodeDump     (LZSWORD CodeOffs_p);

#ifdef _IP_BREAKPOINTS_
void  LzsMemCodeSegFarSetByte (tPlchInst hCodeSeg_p,void LZSFAR * pSegTab_p,  tPlcOffset Addr_p, LZSBYTE ByteVal_p);
LZSBYTE  LzsMemCodeSegFarGetByte (tPlchInst hCodeSeg_p,void LZSFAR * pSegTab_p, tPlcOffset Addr_p);

#endif

LZSBOOL  LZSPUBLIC  LzsMemRestoreDataSeg (tPlchInst hInst_p);
LZSBOOL  LZSPUBLIC  LzsMemCallFrmwMod    (tPlcFrmwModNr FrmwModNr_p);


/*-cd- 19990824  ncc  - added NsOffset in instance stack */
void LZSPUBLIC LzsMemGetParentInst(tPlchInst *pwInst_p,LZSWORD *pwOff,LZSDWORD *pwNCOff);
void      LZSPUBLIC  LzsMemRetPushInst  (tPlchInst hInst_p, LZSDWORD dNsOffset);
tPlchInst LZSPUBLIC  LzsMemRetPopInst   (LZSDWORD * dNsOffset);
void      LZSPUBLIC  LzsMemCrPushAE     (LZSDWORD AEVal_p);
LZSDWORD     LZSPUBLIC  LzsMemCrPopAE      (void);
void      LZSPUBLIC  LzsMemCrPushExtAE  (void);
void      LZSPUBLIC  LzsMemCrPopExtAE   (void);
void      LZSPUBLIC  LzsMemCrPushAEType (LZSBYTE AEType_p);
LZSBYTE      LZSPUBLIC  LzsMemCrPopAEType  (void);


tPlcMemPtr  LZSPUBLIC  LzsPflowOpenBuffer  (void);
void        LZSPUBLIC  LzsPflowCloseBuffer (LZSWORD wUsedBuffSize_p);



/*--------------------------------------------------------------------------- */
/* Prototypes of generally used functions                                     */
/*--------------------------------------------------------------------------- */

void  LZSPUBLIC  LzsMemAbsSetByte   (LZSBYTE LZSFAR* pAddr_p, LZSBYTE ByteVal_p);
void  LZSPUBLIC  LzsMemAbsSetWord   (LZSBYTE LZSFAR* pAddr_p, LZSWORD WordVal_p);

#ifdef _LZS_DSALIGNMENT_DSP563_
    void  LZSPUBLIC  LzsMemAbsSetWord_1   (LZSBYTE LZSFAR* pAddr_p, LZSWORD WordVal_p);
#endif

#ifdef _IP_REAL438_
void LzsMemAbsSetInt48 (LZSBYTE LZSFAR* Addr_p, LZSINT48 Val_p);
#endif
#ifdef _IP_INT24_
void LzsMemAbsSetInt24 (LZSBYTE LZSFAR* Addr_p, LZSINT24 Val_p);
#endif

#ifdef _LZS_DSALIGNMENT_DSP563_
#ifdef _IP_REAL48_
    void LzsMemAbsSetInt48_1 (LZSBYTE LZSFAR* Addr_p, LZSINT48 Val_p);
/* === New Datatypes for PMAC*/
    /* REAL48 (PMAC_FLOAT)*/
    LZSINT48 LzsMemNearGetInt48(tPlcOffset Addr_p);
    void LzsMemNearSetInt48(tPlcOffset Addr_p, LZSINT48 Val_p);
    LZSINT48 LzsMemFarGetInt48(tPlchInst hInst_p, tPlcOffset Addr_p);
    void LzsMemFarSetInt48(tPlchInst hInst_p, tPlcOffset Addr_p, LZSINT48 Val_p);
    LZSINT48 LzsMemCodeGetInt48(void);

    PMAC_FLOAT LzsMemNearGetReal48(tPlcOffset Addr_p);
    void LzsMemNearSetReal48(tPlcOffset Addr_p, PMAC_FLOAT Val_p);

#endif
#ifdef _IP_INT24_
    void LzsMemAbsSetInt24_1 (LZSBYTE LZSFAR* Addr_p, LZSINT24 Val_p);
    /* INT24*/
    LZSINT24 LzsMemNearGetInt24(tPlcOffset Addr_p);
    void LzsMemNearSetInt24(tPlcOffset Addr_p, LZSINT24 Val_p);
    LZSINT24 LzsMemFarGetInt24(tPlchInst hInst_p, tPlcOffset Addr_p);
    LZSINT24 LzsMemCodeGetInt24(void);
    void LzsMemFarSetInt24(tPlchInst hInst_p, tPlcOffset Addr_p, LZSINT24 Val_p);
#endif
    LZSDWORD LZSPUBLIC  LzsMemAbsGetDword_1(LZSBYTE LZSFAR* pAddr_p);
    void  LZSPUBLIC  LzsMemAbsSetDword_1  (LZSBYTE LZSFAR* pAddr_p, LZSDWORD DwordVal_p) LZSLARGE;
    LZSWORD  LZSPUBLIC  LzsMemAbsGetWord_1   (LZSBYTE LZSFAR* pAddr_p);
#endif

void  LZSPUBLIC  LzsMemAbsSetDword  (LZSBYTE LZSFAR* pAddr_p, LZSDWORD DwordVal_p) LZSLARGE;
LZSBYTE  LZSPUBLIC  LzsMemAbsGetByte   (LZSBYTE LZSFAR* pAddr_p);
LZSWORD  LZSPUBLIC  LzsMemAbsGetWord   (LZSBYTE LZSFAR* pAddr_p);
LZSDWORD LZSPUBLIC  LzsMemAbsGetDword  (LZSBYTE LZSFAR* pAddr_p);

void  LZSPUBLIC  LzsNetAbsSetByte   (LZSBYTE LZSFAR* pAddr_p, LZSBYTE ByteVal_p);
void  LZSPUBLIC  LzsNetAbsSetWord   (LZSBYTE LZSFAR* pAddr_p, LZSWORD WordVal_p);
void  LZSPUBLIC  LzsNetAbsSetDword  (LZSBYTE LZSFAR* pAddr_p, LZSDWORD DwordVal_p) LZSLARGE;
LZSBYTE  LZSPUBLIC  LzsNetAbsGetByte   (LZSBYTE LZSFAR* pAddr_p);
LZSWORD  LZSPUBLIC  LzsNetAbsGetWord   (LZSBYTE LZSFAR* pAddr_p);
LZSWORD  LZSPUBLIC  LzsNetAbsGetWordMot (LZSBYTE LZSFAR* pAddr_p);
LZSDWORD LZSPUBLIC  LzsNetAbsGetDword  (LZSBYTE LZSFAR* pAddr_p);

#ifdef _LZS_RETAIN_
LZSBOOL LzsMemBuildRetainTable(void);
LZSBOOL LzsMemProvideRetainData(void);
LZSBOOL LzsMemRestoreRetainData(tPlcMemPtr pRestoreData_p, LZSDWORD dwDataSize_p);
LZSBOOL LzsMemDeleteRetainTable(void);
LZSBOOL LzsMemDeleteRetainData(void);
#endif

#ifndef _LZS_8BITBYTES_
LZSBYTE LZSPUBLIC LzsMemAssemble32BitByte (LZSBYTE bByte1_p, LZSBYTE bByte2_p, LZSBYTE bByte3_p, LZSBYTE bByte4_p);
#endif
#ifdef _LZS_16BITBYTES_
LZSDWORD LZSPUBLIC LzsMemAssemble32BitDword (LZSBYTE bByte1_p, LZSBYTE bByte2_p, LZSBYTE bByte3_p, LZSBYTE bByte4_p);
#endif

/*--------------------------------------------------------------------------- */
/* Prototypes of functions used by LZS/SZM                                    */
/*--------------------------------------------------------------------------- */

void  LzsMemInitRegister    (tLzsMemTask LZSFAR *pMemTask_p);
void  LzsMemSaveRegister    (tLzsMemTask LZSFAR *pMemTask_p);
void  LzsMemRestoreRegister (tLzsMemTask LZSFAR *pMemTask_p);

void  LzsMemGetSegHeader    (LZSBYTE LZSFAR* pSeg_p, tSegHeader* pSegHeaderInf_p);
void  LzsMemSetSegHeader    (LZSBYTE LZSFAR* pSeg_p, tSegHeader* pSegHeaderInf_p);
#ifndef _LZS_8BITBYTES_
void  LzsNetGetSegHeader    (LZSBYTE LZSFAR* pSeg_p, tSegHeader* pSegHeaderInf_p);
void  LzsNetGetSegHeader1   (LZSBYTE LZSFAR* pSeg_p, tSegHeader* pSegHeaderInf_p);
#endif

/* return DWORD segment length from extented NC header */
LZSDWORD LzsMemGetNCSegSizeFromHeader(LZSBYTE LZSFAR* pSeg_p);
LZSDWORD LzsNetGetNCSegSizeFromHeader(LZSBYTE LZSFAR* pSeg_p);

#ifdef _IP_8BYTEDATA_
void LZSPUBLIC LzsMemSwitchRegAEDW(void);
void LZSPUBLIC LzsMemSwitchRegAEsDW(void);
#ifdef LZSSWITCHREGDW
#define LZS_SWITCH_REGAE_DW() LzsMemSwitchRegAEDW()
#define LZS_SWITCH_REGAES_DW() LzsMemSwitchRegAEsDW()
#else
#define LZS_SWITCH_REGAE_DW()
#define LZS_SWITCH_REGAES_DW()
#endif
#endif	

LZSWORD LzsSwapWord(LZSWORD WordVal_p);
LZSDWORD LzsSwapDword(LZSDWORD DwordVal_p);

#define LZS_SWAP_WORD(WordVal_p) LzsSwapWord(WordVal_p)
#define LZS_SWAP_DWORD(DwordVal_p) LzsSwapDword(DwordVal_p)

#ifndef _LZS_MOTOROLA_
#define LZS_SWAP_WORD_TO_BIGENDIAN(WordVal_p) WordVal_p
#define LZS_SWAP_DWORD_TO_BIGENDIAN(DwordVal_p) DwordVal_p
#define LZS_SWAP_WORD_TO_LITTLEENDIAN(WordVal_p) WordVal_p
#define LZS_SWAP_DWORD_TO_LITTLEENDIAN(DwordVal_p) DwordVal_p
#else
#define LZS_SWAP_WORD_TO_BIGENDIAN(WordVal_p) LZS_SWAP_WORD(WordVal_p)
#define LZS_SWAP_DWORD_TO_BIGENDIAN(DwordVal_p) LZS_SWAP_DWORD(DwordVal_p)
#define LZS_SWAP_WORD_TO_LITTLEENDIAN(WordVal_p) LZS_SWAP_WORD(WordVal_p)
#define LZS_SWAP_DWORD_TO_LITTLEENDIAN(DwordVal_p) LZS_SWAP_DWORD(DwordVal_p)
#endif

LZSBOOL  LzsMemRestoreData     (LZSBYTE bRestoreMode_p);
LZSBOOL  LzsMemInitSegment     (tPlcSegNr nSegNum_p, LZSBYTE bRestoreMode_p);


void LzsMemGetLinkerTableEntry(
    tPlcMemPtr pLinkerTableEntry_p,        /* [i] Pointer to entry in Linkertable */
    tSegLinkerTableEntry * pEntry_p        /* [o] Entry struct */
    );
    
void LzsMemGetInitSegSections(
    tPlcMemPtr pInitSeg_p,                /* [i] Pointer to InitSegment (ReferenceSegment) */
    tSegInitSegSections * pSections_p    /* [o] Sections struct */
    );
    
     
    LZSCHAR * LzsMemNearGetStringPtr(tPlcOffset Addr_p);

LZSBOOL  LZSPUBLIC LzsMemFarGetSpecificBit (tPlchInst hInst_p, tPlcBitAdr Addr_p);
void  LZSPUBLIC LzsMemFarSetSpecificBit (tPlchInst hInst_p, tPlcBitAdr Addr_p, LZSBOOL BitVal_p);

void LZSPUBLIC LzsMemGetParentInst(tPlchInst *pwInst_p,LZSWORD *pwOff,LZSDWORD *pdwNCOff);
LZSBYTE LzsMemPatchByrefAddress(void);    

void  LZSPUBLIC  LzsMemDirByrefSetString (tPlcMemPtr pAddr_p);

void  LZSPUBLIC LzsMemDirByrefGetAny (tPlcMemPtr pAddr_p, LZSBYTE Sel_p);
void  LZSPUBLIC LzsMemDirByrefSetAny (tPlcMemPtr Addr_p);

void  LZSPUBLIC LzsMemCommonSetWString (LZSBYTE  LZSFAR* pDst);
void  LZSPUBLIC LzsMemFarSetWString (tPlchInst hInst_p, tPlcOffset Addr_p);

#endif  /* ifndef _ODK_SZM_H_ */
