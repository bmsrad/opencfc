/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Do, 20 Aug 98                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

/****************************************************************************

   Definitionsdatei zur Einbindung von Funktionsbausteinen nach IEC1131-3

   30.04.1997   -rs

****************************************************************************/

#ifndef _IEC_FB_H_
#define _IEC_FB_H_



/*---------------------------------------------------------------------------
 *  Macrodefinitions
 *---------------------------------------------------------------------------*/
/*
#define     GETBIT(addr)            LzsMemNearGetBit (addr)
#define     GETINT(addr)            (LZSSINT)LzsMemNearGetWord(addr)
#define     GETWORD(addr)           (LZSWORD)LzsMemNearGetWord(addr)
#define     GETTIME(addr)           LzsMemNearGetDword(addr)
#define     GETDINT(addr)           (LZSLONG)LzsMemNearGetDword(addr)
#define     GETUDINT(addr)          LzsMemNearGetDword(addr)
#define     GETDWORD(addr)          LzsMemNearGetDword(addr)
#define     GETBYTE(addr)            (LZSBYTE)LzsMemNearGetByte(addr)

#define     SETBIT(addr, val)       LzsMemNearSetBit((tPlcBitAdr)addr, val)
#define     SETINT(addr, val)       LzsMemNearSetWord(addr, LZSWORDCAST(val))
#define     SETWORD(addr, val)      LzsMemNearSetWord(addr, LZSWORDCAST(val))
#define     SETTIME(addr, val)      LzsMemNearSetDword(addr,(LZSDWORD)val)
#define     SETDINT(addr, val)      LzsMemNearSetDword(addr, (LZSDWORD)val)
#define     SETUDINT(addr, val)     LzsMemNearSetDword(addr,(LZSDWORD)val)
#define     SETDWORD(addr, val)     LzsMemNearSetDword(addr,(LZSDWORD)val)
#define     SETBYTE(addr, val)        LzsMemNearSetByte(addr,LZSBYTECAST(val))
*/

#if 1

/* these macros do not use byte-wise access, so it is assumed that everything is aligned properly! */
#define     GETREAL(addr)           *((float*)(pCurrentProgramData_g->RegDS + addr))
#define     GETBIT(addr)            (*(pCurrentProgramData_g->RegDS + addr) & 0x01 ? LZSTRUE : LZSFALSE)
#define     GETDWORD(addr)          *((LZSDWORD*)(pCurrentProgramData_g->RegDS + addr))
#define     GETUDINT(addr)          *((LZSDWORD*)(pCurrentProgramData_g->RegDS + addr))
#define     GETDINT(addr)           *((LZSLONG*)(pCurrentProgramData_g->RegDS + addr))
#define     GETTIME(addr)           *((LZSDWORD*)(pCurrentProgramData_g->RegDS + addr))
#define     GETUINT(addr)           *((LZSINT*)(pCurrentProgramData_g->RegDS + addr))
#define     GETWORD(addr)           *((LZSWORD*)(pCurrentProgramData_g->RegDS + addr))
#define     GETINT(addr)            *((LZSINT*)(pCurrentProgramData_g->RegDS + addr))
#define     GETBYTE(addr)           *((LZSBYTE*)(pCurrentProgramData_g->RegDS + addr))

/* unchanged */
#define     GETSTRING(addr)            (tPlcMemPtr)LZS_MEM_NEAR_GET_STRING(addr)
#define        GETPARAMADDR(addr)        (tPlcMemPtr)LZS_MEM_NEAR_GET_PARAM_ADDR(addr)
#define        GETPOINTER(addr, pointer)    LZS_MEM_NEAR_GET_POINTER(addr, pointer)
#define        GETDATE(addr)            LZS_MEM_NEAR_GET_DWORD(addr)
#define        GETTOD(addr)            LZS_MEM_NEAR_GET_DWORD(addr)    /* TIME_OF_DAY */
#ifdef _IP_8BYTEDATA_
#define        GETDT(addr)                LZS_MEM_NEAR_GET_QWORD(addr)    /* DATE_AND_TIME */
#endif

/* changed */
#define     SETREAL(addr, val)      {*((float*)(pCurrentProgramData_g->RegDS + addr)) = val;}
#define     SETBIT(addr, val)       {*(pCurrentProgramData_g->RegDS + addr) = val;}
#define     SETDWORD(addr, val)     {*((LZSDWORD*)(pCurrentProgramData_g->RegDS + addr)) = val;}
#define     SETUDINT(addr, val)     {*((LZSDWORD*)(pCurrentProgramData_g->RegDS + addr)) = val;}
#define     SETDINT(addr, val)      {*((LZSLONG*)(pCurrentProgramData_g->RegDS + addr)) = val;}
#define     SETTIME(addr, val)      {*((LZSDWORD*)(pCurrentProgramData_g->RegDS + addr)) = val;}
#define     SETUINT(addr, val)      {*((LZSINT*)(pCurrentProgramData_g->RegDS + addr)) = val;}
#define     SETWORD(addr, val)      {*((LZSWORD*)(pCurrentProgramData_g->RegDS + addr)) = val;}
#define     SETINT(addr, val)       {*((LZSINT*)(pCurrentProgramData_g->RegDS + addr)) = val;}
#define     SETBYTE(addr, val)      {*((LZSBYTE*)(pCurrentProgramData_g->RegDS + addr)) = val;}

/* unchanged */
#define     SETSTRING_EXTAE(addr)    LzsMemNearSetString(addr)
#define     SETSTRING(pStr, pDstNearOffs_p, wCount)    LzsMemNearSetStringParam(pStr, pDstNearOffs_p, wCount)
#define        SETDATE(addr, val)        LZS_MEM_NEAR_SET_DWORD(addr, val)
#define        SETTOD(addr, val)        LZS_MEM_NEAR_SET_DWORD(addr, val)
#ifdef _IP_8BYTEDATA_
#define        SETDT(addr, val)        LZS_MEM_NEAR_SET_QWORD(addr, val)
#endif

#else

/* original macros */
#define     GETREAL(addr)           LzsMemNearGetFloat(addr)
#define     GETBIT(addr)            LzsMemNearGetBit(addr)
#define     GETINT(addr)            (LZSINT)LZS_MEM_NEAR_GET_WORD(addr)
#define     GETUINT(addr)           (LZSINT)LZS_MEM_NEAR_GET_WORD(addr)
#define     GETWORD(addr)           (LZSWORD)LZS_MEM_NEAR_GET_WORD(addr)
#define     GETTIME(addr)           LZS_MEM_NEAR_GET_DWORD(addr)
#define     GETDINT(addr)           (LZSLONG)LZS_MEM_NEAR_GET_DWORD(addr)
#define     GETUDINT(addr)          LZS_MEM_NEAR_GET_DWORD(addr)
#define     GETDWORD(addr)          LZS_MEM_NEAR_GET_DWORD(addr)
#define     GETBYTE(addr)            (LZSBYTE)LZS_MEM_NEAR_GET_BYTE(addr)
#define     GETSTRING(addr)            (tPlcMemPtr)LZS_MEM_NEAR_GET_STRING(addr)
#define        GETPARAMADDR(addr)        (tPlcMemPtr)LZS_MEM_NEAR_GET_PARAM_ADDR(addr)
#define        GETPOINTER(addr, pointer)    LZS_MEM_NEAR_GET_POINTER(addr, pointer)
#define        GETDATE(addr)            LZS_MEM_NEAR_GET_DWORD(addr)
#define        GETTOD(addr)            LZS_MEM_NEAR_GET_DWORD(addr)    /* TIME_OF_DAY */
#ifdef _IP_8BYTEDATA_
#define        GETDT(addr)                LZS_MEM_NEAR_GET_QWORD(addr)    /* DATE_AND_TIME */
#endif
#define     SETREAL(addr, val)      LzsMemNearSetFloat(addr, val)
#define     SETBIT(addr, val)       LzsMemNearSetBit((tPlcBitAdr)addr, val)
#define     SETINT(addr, val)       LZS_MEM_NEAR_SET_WORD(addr, LZSWORDCAST(val))
#define     SETUINT(addr, val)      LZS_MEM_NEAR_SET_WORD(addr, LZSWORDCAST(val))
#define     SETWORD(addr, val)      LZS_MEM_NEAR_SET_WORD(addr, LZSWORDCAST(val))
#define     SETTIME(addr, val)      LZS_MEM_NEAR_SET_DWORD(addr,(LZSDWORD)val)
#define     SETDINT(addr, val)      LZS_MEM_NEAR_SET_DWORD(addr, (LZSDWORD)val)
#define     SETUDINT(addr, val)     LZS_MEM_NEAR_SET_DWORD(addr,(LZSDWORD)val)
#define     SETDWORD(addr, val)     LZS_MEM_NEAR_SET_DWORD(addr,(LZSDWORD)val)
#define     SETBYTE(addr, val)        LZS_MEM_NEAR_SET_BYTE(addr,LZSBYTECAST(val))
#define     SETSTRING_EXTAE(addr)    LzsMemNearSetString(addr)
#define     SETSTRING(pStr, pDstNearOffs_p, wCount)    LzsMemNearSetStringParam(pStr, pDstNearOffs_p, wCount)
#define        SETDATE(addr, val)        LZS_MEM_NEAR_SET_DWORD(addr, val)
#define        SETTOD(addr, val)        LZS_MEM_NEAR_SET_DWORD(addr, val)
#ifdef _IP_8BYTEDATA_
#define        SETDT(addr, val)        LZS_MEM_NEAR_SET_QWORD(addr, val)
#endif

#endif



/*---------------------------------------------------------------------------
 * Typedefinitions
 *---------------------------------------------------------------------------*/

/* Definition of ErrorCodes*/
typedef enum
{
   kIecOK               = 0x00,     /* everything is fine */

   kIecGeneralError     = 0xFF,     /* general error */
   kIecFBNotSupported   = 0xFE,     /* FB is not implemented */
   kIecHardwareError    = 0xFD,     /* Error accessing hardware */


/* [SYSTEC: 25.06.2003 -rs]: user-specific errorcode newly inserted */
   kIecOemError01       = 0x7F,     /* OEM specific error */
   kIecOemError02       = 0x7E,     /* OEM specific error */
   kIecOemError03       = 0x7D,     /* OEM specific error */
   kIecOemError04       = 0x7C,     /* OEM specific error */
   kIecOemError05       = 0x7B,     /* OEM specific error */
   kIecOemError06       = 0x7A,     /* OEM specific error */
   kIecOemError07       = 0x79,     /* OEM specific error */
   kIecOemError08       = 0x78,     /* OEM specific error */
   kIecOemError09       = 0x77,     /* OEM specific error */
   kIecOemError10       = 0x76,     /* OEM specific error */
   kIecOemError11       = 0x75,     /* OEM specific error */
   kIecOemError12       = 0x74,     /* OEM specific error */
   kIecOemError13       = 0x73,     /* OEM specific error */
   kIecOemError14       = 0x72,     /* OEM specific error */
   kIecOemError15       = 0x71,     /* OEM specific error */
   kIecOemError16       = 0x70,     /* OEM specific error */
   kIecOemError17       = 0x6F,     /* OEM specific error */
   kIecOemError18       = 0x6E,     /* OEM specific error */
   kIecOemError19       = 0x6D,     /* OEM specific error */
   kIecOemError20       = 0x6C      /* OEM specific error */

} tIecErrorCode;


/*---------------------------------------------------------------------------
 * Constants
 *---------------------------------------------------------------------------*/
#ifndef _CC_2000_
#define FLOAT_POS_INFINITE 2139095040UL
#define FLOAT_NEG_INFINITE 4286578688UL
#else
#define FLOAT_POS_INFINITE 2139095039UL
#define FLOAT_NEG_INFINITE 4286578687UL
#endif

/*---------------------------------------------------------------------------
 * Prototypes
 *---------------------------------------------------------------------------
 */

#ifdef __cplusplus
   extern "C" {
#endif 

/*
 * Functions for realizing of standard FB's
 */
LZSBYTE  IecFB_SR     (void);
LZSBYTE  IecFB_RS     (void);
LZSBYTE  IecFB_R_TRIG (void);
LZSBYTE  IecFB_F_TRIG (void);
LZSBYTE  IecFB_CTU    (void);
LZSBYTE  IecFB_CTD    (void);
LZSBYTE  IecFB_CTUD   (void);
LZSBYTE  IecFB_TP     (void);
LZSBYTE  IecFB_TON    (void);
LZSBYTE  IecFB_TOF    (void);
LZSBYTE  IecFB_RTC    (void);

/*
 *    firmware functions
 */
LZSBYTE  IT_Fun_Time_To_Dint    (void);
LZSBYTE  IT_Fun_Dint_To_Time    (void);
LZSBYTE  IT_Fun_GetTime            (void);
LZSBYTE  IT_Fun_GetTimeCS        (void);
LZSBYTE  IT_FB_String2Int        (void);
LZSBYTE  IT_FB_GetVarData        (void);
LZSBYTE  IT_FB_GetVarAddress    (void);
LZSBYTE     IT_FB_GetTaskInfo        (void);
LZSBYTE  IT_FB_GetError            (void);
LZSBYTE     ExtFB_ETRC                (void);    /* 20040505mm for tests only; maybe the name have to be changed */
LZSBYTE  IT_FB_Resume_RTS        (void);
LZSBYTE  IT_Fun_Time_To_Real    (void);
LZSBYTE     IT_FB_HexDump            (void);
LZSBYTE     Test_FB_TEST_EXC            (void);

#ifdef _FB_COP_
    void     CopFB_LibInitialize         (void);
    void     CopFB_LibClose              (void);    /* [SYSTEC/CANopen: 2006/08/23 -rs]: function inserted */
    void     CopFB_LibStart              (void);    /* [SYSTEC/CANopen: 2006/11/17 -rs]: function inserted */
    void     CopFB_LibStop               (void);    /* [SYSTEC/CANopen: 2006/11/17 -rs]: function inserted */

/*    LZSBYTE  CopFB_Init                  (void); */
    LZSBYTE  CopFB_GetLocalNodeID        (void);
    LZSBYTE  CopFB_GetCanopenKernelState (void);
    LZSBYTE  CopFB_RegisterCobID         (void);
    LZSBYTE  CopFB_PDORead8              (void);
    LZSBYTE  CopFB_PDOWrite8             (void);
    LZSBYTE  CopFB_SDORead8              (void);
    LZSBYTE  CopFB_SDOWrite8             (void);
    LZSBYTE  CopFB_SDOReadStr            (void);
    LZSBYTE  CopFB_SDOWriteStr           (void);
/*    LZSBYTE  CopFB_SDOReadBin            (void); */
/*   LZSBYTE  CopFB_SDOWriteBin           (void); */
    LZSBYTE  CopFB_GetState              (void);
    LZSBYTE  CopFB_NMT                   (void);
    LZSBYTE  CopFB_RecvEmcyDev           (void);
    LZSBYTE  CopFB_RecvEmcy              (void);
    LZSBYTE  CopFB_WriteEmcy             (void);
    LZSBYTE  CopFB_RecvBootupDev         (void);
    LZSBYTE  CopFB_RecvBootup            (void);
    LZSBYTE  CopFB_EnableCyclicSync      (void);
    LZSBYTE  CopFB_SendSync              (void);
#else
/* [SYSTEC: 22.08.2006 -rs]: #define NULL for all CANopen FB's inserted */
/*    #define  CopFB_Init                  LZSNULL */
    #define  CopFB_GetLocalNodeID        LZSNULL
    #define  CopFB_GetCanopenKernelState LZSNULL
    #define  CopFB_RegisterCobID         LZSNULL
    #define  CopFB_PDORead8              LZSNULL
    #define  CopFB_PDOWrite8             LZSNULL
    #define  CopFB_SDORead8              LZSNULL
    #define  CopFB_SDOWrite8             LZSNULL
    #define  CopFB_SDOReadStr            LZSNULL
    #define  CopFB_SDOWriteStr           LZSNULL
/*    #define  CopFB_SDOReadBin            LZSNULL */
/*    #define  CopFB_SDOWriteBin           LZSNULL */
    #define  CopFB_GetState              LZSNULL
    #define  CopFB_NMT                   LZSNULL
    #define  CopFB_RecvEmcyDev           LZSNULL
    #define  CopFB_RecvEmcy              LZSNULL
    #define  CopFB_WriteEmcy             LZSNULL
    #define  CopFB_RecvBootupDev         LZSNULL
    #define  CopFB_RecvBootup            LZSNULL
    #define  CopFB_EnableCyclicSync      LZSNULL
    #define  CopFB_SendSync              LZSNULL
#endif

/*----------------------------------------------------------------------------*/
/*  Prototypes of EN-controlled FBs                                           */
/*----------------------------------------------------------------------------*/
LZSBYTE     Wrapper_Limit_Uint    (void);    
LZSBYTE  Wrapper_Move_Int    (void);
LZSBYTE  Wrapper_Add_Int    (void);
LZSBYTE  Wrapper_Sub_Int    (void);
LZSBYTE  Wrapper_Mul_Int    (void);
LZSBYTE  Wrapper_Div_Int    (void);
LZSBYTE  Wrapper_Mod_Int    (void);
LZSBYTE  Wrapper_Limit_Int    (void);
LZSBYTE  Wrapper_Max_Int    (void);
LZSBYTE  Wrapper_Int_To_Uint(void);
LZSBYTE  Wrapper_Uint_To_Int(void);
LZSBYTE  Wrapper_Move_Uint    (void);
LZSBYTE  Wrapper_Add_Uint    (void);
LZSBYTE  Wrapper_Sub_Uint    (void);
LZSBYTE  Wrapper_Mul_Uint    (void);
LZSBYTE  Wrapper_Div_Uint    (void);
LZSBYTE  Wrapper_Mod_Uint    (void);
LZSBYTE  Wrapper_Add_Sint(void);
LZSBYTE  Wrapper_Add_Dint(void);
LZSBYTE  Wrapper_Add_Usint(void);
LZSBYTE  Wrapper_Add_Udint(void);
LZSBYTE  Wrapper_Add_Real(void);
LZSBYTE  Wrapper_Mul_Sint(void);
LZSBYTE  Wrapper_Mul_Dint(void);
LZSBYTE  Wrapper_Mul_Usint(void);
LZSBYTE  Wrapper_Mul_Udint(void);
LZSBYTE  Wrapper_Mul_Real(void);
LZSBYTE  Wrapper_Sub_Sint(void);
LZSBYTE  Wrapper_Sub_Dint(void);
LZSBYTE  Wrapper_Sub_Usint(void);
LZSBYTE  Wrapper_Sub_Udint(void);
LZSBYTE  Wrapper_Sub_Real(void);
LZSBYTE  Wrapper_Div_Sint(void);
LZSBYTE  Wrapper_Div_Dint(void);
LZSBYTE  Wrapper_Div_Usint(void);
LZSBYTE  Wrapper_Div_Udint(void);
LZSBYTE  Wrapper_Div_Real(void);
LZSBYTE  Wrapper_Mod_Sint(void);
LZSBYTE  Wrapper_Mod_Dint(void);
LZSBYTE  Wrapper_Mod_Usint(void);
LZSBYTE  Wrapper_Mod_Udint(void);
LZSBYTE  Wrapper_Move_Sint(void);
LZSBYTE  Wrapper_Move_Dint(void);
LZSBYTE  Wrapper_Move_Usint(void);
LZSBYTE  Wrapper_Move_Udint(void);
LZSBYTE  Wrapper_Move_Real(void);
LZSBYTE  Wrapper_Expt_Int(void);
LZSBYTE  Wrapper_Expt_Sint(void);
LZSBYTE  Wrapper_Expt_Dint(void);
LZSBYTE  Wrapper_Expt_Uint(void);
LZSBYTE  Wrapper_Expt_Usint(void);
LZSBYTE  Wrapper_Expt_Udint(void);
LZSBYTE  Wrapper_Expt_Real(void);
LZSBYTE  Wrapper_Shl_Bool(void);
LZSBYTE  Wrapper_Shl_Byte(void);
LZSBYTE  Wrapper_Shl_Word(void);
LZSBYTE  Wrapper_Shl_Dword(void);
LZSBYTE  Wrapper_Shr_Bool(void);
LZSBYTE  Wrapper_Shr_Byte(void);
LZSBYTE  Wrapper_Shr_Word(void);
LZSBYTE  Wrapper_Shr_Dword(void);
LZSBYTE  Wrapper_Rol_Bool(void);
LZSBYTE  Wrapper_Rol_Byte(void);
LZSBYTE  Wrapper_Rol_Word(void);
LZSBYTE  Wrapper_Rol_Dword(void);
LZSBYTE  Wrapper_Ror_Bool(void);
LZSBYTE  Wrapper_Ror_Byte(void);
LZSBYTE  Wrapper_Ror_Word(void);
LZSBYTE  Wrapper_Ror_Dword(void);
LZSBYTE  Wrapper_Max_Bool(void);
LZSBYTE  Wrapper_Max_Byte(void);
LZSBYTE  Wrapper_Max_Word(void);
LZSBYTE  Wrapper_Max_Dword(void);
LZSBYTE  Wrapper_Max_Int(void);
LZSBYTE  Wrapper_Max_Sint(void);
LZSBYTE  Wrapper_Max_Dint(void);
LZSBYTE  Wrapper_Max_Uint(void);
LZSBYTE  Wrapper_Max_Usint(void);
LZSBYTE  Wrapper_Max_Udint(void);
LZSBYTE  Wrapper_Max_Real(void);
LZSBYTE  Wrapper_Max_Time(void);
LZSBYTE  Wrapper_Max_String(void);
LZSBYTE  Wrapper_Min_Bool(void);
LZSBYTE  Wrapper_Min_Byte(void);
LZSBYTE  Wrapper_Min_Word(void);
LZSBYTE  Wrapper_Min_Dword(void);
LZSBYTE  Wrapper_Min_Int(void);
LZSBYTE  Wrapper_Min_Sint(void);
LZSBYTE  Wrapper_Min_Dint(void);
LZSBYTE  Wrapper_Min_Uint(void);
LZSBYTE  Wrapper_Min_Usint(void);
LZSBYTE  Wrapper_Min_Udint(void);
LZSBYTE  Wrapper_Min_Real(void);
LZSBYTE  Wrapper_Min_Time(void);
LZSBYTE  Wrapper_Min_String(void);
LZSBYTE  Wrapper_Limit_Bool(void);
LZSBYTE  Wrapper_Limit_Byte(void);
LZSBYTE  Wrapper_Limit_Word(void);
LZSBYTE  Wrapper_Limit_Dword(void);
LZSBYTE  Wrapper_Limit_Sint(void);
LZSBYTE  Wrapper_Limit_Dint(void);
LZSBYTE  Wrapper_Limit_Usint(void);
LZSBYTE  Wrapper_Limit_Udint(void);
LZSBYTE  Wrapper_Limit_Real(void);
LZSBYTE  Wrapper_Limit_Time(void);
LZSBYTE  Wrapper_Limit_String(void);
LZSBYTE  Wrapper_Len_String(void);
LZSBYTE  Wrapper_Left_Int(void);
LZSBYTE  Wrapper_Left_Sint(void);
LZSBYTE  Wrapper_Left_Dint(void);
LZSBYTE  Wrapper_Left_Uint(void);
LZSBYTE  Wrapper_Left_Usint(void);
LZSBYTE  Wrapper_Left_Udint(void);
LZSBYTE  Wrapper_Right_Int(void);
LZSBYTE  Wrapper_Right_Sint(void);
LZSBYTE  Wrapper_Right_Dint(void);
LZSBYTE  Wrapper_Right_Uint(void);
LZSBYTE  Wrapper_Right_Usint(void);
LZSBYTE  Wrapper_Right_Udint(void);
LZSBYTE  Wrapper_Concat_String(void);
LZSBYTE  Wrapper_Find_String(void);
LZSBYTE  Wrapper_Add_Time(void);
LZSBYTE  Wrapper_Sub_Time(void);
LZSBYTE  Wrapper_Abs_Int(void);
LZSBYTE  Wrapper_Abs_Sint(void);
LZSBYTE  Wrapper_Abs_Dint(void);
LZSBYTE  Wrapper_Abs_Real(void);
LZSBYTE  Wrapper_Sqrt_Real(void);
LZSBYTE  Wrapper_Ln_Real(void);
LZSBYTE  Wrapper_Log_Real(void);
LZSBYTE  Wrapper_Exp_Real(void);
LZSBYTE  Wrapper_Sin_Real(void);
LZSBYTE  Wrapper_Cos_Real(void);
LZSBYTE  Wrapper_Tan_Real(void);
LZSBYTE  Wrapper_Asin_Real(void);
LZSBYTE  Wrapper_Acos_Real(void);
LZSBYTE  Wrapper_Atan_Real(void);
LZSBYTE  Wrapper_Bool_To_Byte(void);
LZSBYTE  Wrapper_Bool_To_Word(void);
LZSBYTE  Wrapper_Bool_To_Dword(void);
LZSBYTE  Wrapper_Bool_To_Int(void);
LZSBYTE  Wrapper_Bool_To_Sint(void);
LZSBYTE  Wrapper_Bool_To_Dint(void);
LZSBYTE  Wrapper_Bool_To_Uint(void);
LZSBYTE  Wrapper_Bool_To_Usint(void);
LZSBYTE  Wrapper_Bool_To_Udint(void);
LZSBYTE  Wrapper_Bool_To_Real(void);
LZSBYTE  Wrapper_Bool_To_Time(void);
LZSBYTE  Wrapper_Bool_To_String(void);
LZSBYTE  Wrapper_Byte_To_Bool(void);
LZSBYTE  Wrapper_Byte_To_Word(void);
LZSBYTE  Wrapper_Byte_To_Dword(void);
LZSBYTE  Wrapper_Byte_To_Int(void);
LZSBYTE  Wrapper_Byte_To_Sint(void);
LZSBYTE  Wrapper_Byte_To_Dint(void);
LZSBYTE  Wrapper_Byte_To_Uint(void);
LZSBYTE  Wrapper_Byte_To_Usint(void);
LZSBYTE  Wrapper_Byte_To_Udint(void);
LZSBYTE  Wrapper_Byte_To_Real(void);
LZSBYTE  Wrapper_Byte_To_Time(void);
LZSBYTE  Wrapper_Byte_To_String(void);
LZSBYTE  Wrapper_Word_To_Bool(void);
LZSBYTE  Wrapper_Word_To_Byte(void);
LZSBYTE  Wrapper_Word_To_Dword(void);
LZSBYTE  Wrapper_Word_To_Int(void);
LZSBYTE  Wrapper_Word_To_Sint(void);
LZSBYTE  Wrapper_Word_To_Dint(void);
LZSBYTE  Wrapper_Word_To_Uint(void);
LZSBYTE  Wrapper_Word_To_Usint(void);
LZSBYTE  Wrapper_Word_To_Udint(void);
LZSBYTE  Wrapper_Word_To_Real(void);
LZSBYTE  Wrapper_Word_To_Time(void);
LZSBYTE  Wrapper_Word_To_String(void);
LZSBYTE  Wrapper_Dword_To_Bool(void);
LZSBYTE  Wrapper_Dword_To_Byte(void);
LZSBYTE  Wrapper_Dword_To_Word(void);
LZSBYTE  Wrapper_Dword_To_Int(void);
LZSBYTE  Wrapper_Dword_To_Sint(void);
LZSBYTE  Wrapper_Dword_To_Dint(void);
LZSBYTE  Wrapper_Dword_To_Uint(void);
LZSBYTE  Wrapper_Dword_To_Usint(void);
LZSBYTE  Wrapper_Dword_To_Udint(void);
LZSBYTE  Wrapper_Dword_To_Real(void);
LZSBYTE  Wrapper_Dword_To_Time(void);
LZSBYTE  Wrapper_Dword_To_String(void);
LZSBYTE  Wrapper_Int_To_Bool(void);
LZSBYTE  Wrapper_Int_To_Byte(void);
LZSBYTE  Wrapper_Int_To_Word(void);
LZSBYTE  Wrapper_Int_To_Dword(void);
LZSBYTE  Wrapper_Int_To_Sint(void);
LZSBYTE  Wrapper_Int_To_Dint(void);
LZSBYTE  Wrapper_Int_To_Uint(void);
LZSBYTE  Wrapper_Int_To_Usint(void);
LZSBYTE  Wrapper_Int_To_Udint(void);
LZSBYTE  Wrapper_Int_To_Real(void);
LZSBYTE  Wrapper_Int_To_Time(void);
LZSBYTE  Wrapper_Int_To_String(void);
LZSBYTE  Wrapper_Sint_To_Bool(void);
LZSBYTE  Wrapper_Sint_To_Byte(void);
LZSBYTE  Wrapper_Sint_To_Word(void);
LZSBYTE  Wrapper_Sint_To_Dword(void);
LZSBYTE  Wrapper_Sint_To_Int(void);
LZSBYTE  Wrapper_Sint_To_Dint(void);
LZSBYTE  Wrapper_Sint_To_Uint(void);
LZSBYTE  Wrapper_Sint_To_Usint(void);
LZSBYTE  Wrapper_Sint_To_Udint(void);
LZSBYTE  Wrapper_Sint_To_Real(void);
LZSBYTE  Wrapper_Sint_To_Time(void);
LZSBYTE  Wrapper_Sint_To_String(void);
LZSBYTE  Wrapper_Dint_To_Bool(void);
LZSBYTE  Wrapper_Dint_To_Byte(void);
LZSBYTE  Wrapper_Dint_To_Word(void);
LZSBYTE  Wrapper_Dint_To_Dword(void);
LZSBYTE  Wrapper_Dint_To_Int(void);
LZSBYTE  Wrapper_Dint_To_Sint(void);
LZSBYTE  Wrapper_Dint_To_Uint(void);
LZSBYTE  Wrapper_Dint_To_Usint(void);
LZSBYTE  Wrapper_Dint_To_Udint(void);
LZSBYTE  Wrapper_Dint_To_Real(void);
LZSBYTE  Wrapper_Dint_To_Time(void);
LZSBYTE  Wrapper_Dint_To_String(void);
LZSBYTE  Wrapper_Uint_To_Bool(void);
LZSBYTE  Wrapper_Uint_To_Byte(void);
LZSBYTE  Wrapper_Uint_To_Word(void);
LZSBYTE  Wrapper_Uint_To_Dword(void);
LZSBYTE  Wrapper_Uint_To_Int(void);
LZSBYTE  Wrapper_Uint_To_Sint(void);
LZSBYTE  Wrapper_Uint_To_Dint(void);
LZSBYTE  Wrapper_Uint_To_Usint(void);
LZSBYTE  Wrapper_Uint_To_Udint(void);
LZSBYTE  Wrapper_Uint_To_Real(void);
LZSBYTE  Wrapper_Uint_To_Time(void);
LZSBYTE  Wrapper_Uint_To_String(void);
LZSBYTE  Wrapper_Usint_To_Bool(void);
LZSBYTE  Wrapper_Usint_To_Byte(void);
LZSBYTE  Wrapper_Usint_To_Word(void);
LZSBYTE  Wrapper_Usint_To_Dword(void);
LZSBYTE  Wrapper_Usint_To_Int(void);
LZSBYTE  Wrapper_Usint_To_Sint(void);
LZSBYTE  Wrapper_Usint_To_Dint(void);
LZSBYTE  Wrapper_Usint_To_Uint(void);
LZSBYTE  Wrapper_Usint_To_Udint(void);
LZSBYTE  Wrapper_Usint_To_Real(void);
LZSBYTE  Wrapper_Usint_To_Time(void);
LZSBYTE  Wrapper_Usint_To_String(void);
LZSBYTE  Wrapper_Udint_To_Bool(void);
LZSBYTE  Wrapper_Udint_To_Byte(void);
LZSBYTE  Wrapper_Udint_To_Word(void);
LZSBYTE  Wrapper_Udint_To_Dword(void);
LZSBYTE  Wrapper_Udint_To_Int(void);
LZSBYTE  Wrapper_Udint_To_Sint(void);
LZSBYTE  Wrapper_Udint_To_Dint(void);
LZSBYTE  Wrapper_Udint_To_Uint(void);
LZSBYTE  Wrapper_Udint_To_Usint(void);
LZSBYTE  Wrapper_Udint_To_Real(void);
LZSBYTE  Wrapper_Udint_To_Time(void);
LZSBYTE  Wrapper_Udint_To_String(void);
LZSBYTE  Wrapper_Real_To_Bool(void);
LZSBYTE  Wrapper_Real_To_Byte(void);
LZSBYTE  Wrapper_Real_To_Word(void);
LZSBYTE  Wrapper_Real_To_Dword(void);
LZSBYTE  Wrapper_Real_To_Int(void);
LZSBYTE  Wrapper_Real_To_Sint(void);
LZSBYTE  Wrapper_Real_To_Dint(void);
LZSBYTE  Wrapper_Real_To_Uint(void);
LZSBYTE  Wrapper_Real_To_Usint(void);
LZSBYTE  Wrapper_Real_To_Udint(void);
LZSBYTE  Wrapper_Real_To_Time(void);
LZSBYTE  Wrapper_Real_To_String(void);
LZSBYTE  Wrapper_Time_To_Bool(void);
LZSBYTE  Wrapper_Time_To_Byte(void);
LZSBYTE  Wrapper_Time_To_Word(void);
LZSBYTE  Wrapper_Time_To_Dword(void);
LZSBYTE  Wrapper_Time_To_Int(void);
LZSBYTE  Wrapper_Time_To_Sint(void);
LZSBYTE  Wrapper_Time_To_Dint(void);
LZSBYTE  Wrapper_Time_To_Uint(void);
LZSBYTE  Wrapper_Time_To_Usint(void);
LZSBYTE  Wrapper_Time_To_Udint(void);
LZSBYTE  Wrapper_Time_To_Real(void);
LZSBYTE  Wrapper_Time_To_String(void);
LZSBYTE  Wrapper_String_To_Bool(void);
LZSBYTE  Wrapper_String_To_Byte(void);
LZSBYTE  Wrapper_String_To_Word(void);
LZSBYTE  Wrapper_String_To_Dword(void);
LZSBYTE  Wrapper_String_To_Int(void);
LZSBYTE  Wrapper_String_To_Sint(void);
LZSBYTE  Wrapper_String_To_Dint(void);
LZSBYTE  Wrapper_String_To_Uint(void);
LZSBYTE  Wrapper_String_To_Usint(void);
LZSBYTE  Wrapper_String_To_Udint(void);
LZSBYTE  Wrapper_String_To_Real(void);
LZSBYTE  Wrapper_String_To_Time(void);
LZSBYTE     OEM_Alarm        (void);
void     WrapperCheckForMathError(float* out, LZSBOOL* eno, LZSDWORD tmp); /* helper function */

LZSBYTE Wrapper_And_Bool(void);
LZSBYTE Wrapper_And_Byte(void);
LZSBYTE Wrapper_And_Word(void);
LZSBYTE Wrapper_And_Dword(void);
LZSBYTE Wrapper_Or_Bool(void);
LZSBYTE Wrapper_Or_Byte(void);
LZSBYTE Wrapper_Or_Word(void);
LZSBYTE Wrapper_Or_Dword(void);
LZSBYTE Wrapper_Xor_Bool(void);
LZSBYTE Wrapper_Xor_Byte(void);
LZSBYTE Wrapper_Xor_Word(void);
LZSBYTE Wrapper_Xor_Dword(void);


#ifdef __cplusplus
   }
#endif 



LZSBOOL  IecRisingEdgeDetect  (LZSBOOL fSignal_p, LZSWORD wOffsCompSignal_p);
LZSBOOL  IecFallingEdgeDetect (LZSBOOL fSignal_p, LZSWORD wOffsCompSignal_p);
#endif  
/* ifndef _IEC_FB_H_*/


