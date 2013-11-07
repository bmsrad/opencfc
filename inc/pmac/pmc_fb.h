#ifndef _PMC_FB_H_
#define _PMC_FB_H_

#ifdef __cplusplus
   extern "C" {
#endif 
/*
//  PMAC Functions & LD Function Blocks
*/
#ifdef _WIN32
/* === SmartSIM (Winlzs32.dll) */

    #define OPCS_SIZE_HDR       6       /* Start of IEC Function Data */

/*  #define PMAC_SIZE_INT24     2 */    /* Currently as a workaround it is INT = 2Byte */
    #define PMAC_SIZE_INT24     3       /* once we introduced the new datatypes */
/*  #define PMAC_SIZE_REAL48    4 */    /* Currently as a workaround it is DINT = 4Byte */
    #define PMAC_SIZE_REAL48    6       /* once we introduced the new datatypes */


    #define READ_LNO    OPCS_SIZE_HDR               /* Out INT24 */
    #define READ_N      READ_LNO + PMAC_SIZE_INT24  /* INP INT24 */

    #define WRITE_LNO   OPCS_SIZE_HDR               /* Out INT24 */
    #define WRITE_N     WRITE_LNO + PMAC_SIZE_INT24 /* INP INT24 */
    #define WRITE_LNI   WRITE_N + PMAC_SIZE_INT24   /* INP INT24 */

    #define READ_MNO    OPCS_SIZE_HDR                /* Out REAL48 */
    #define READ_MN     READ_MNO + PMAC_SIZE_REAL48  /* INP REAL48 */

    #define WRITE_MNO   OPCS_SIZE_HDR                /* Out REAL48 */
    #define WRITE_MN    WRITE_MNO + PMAC_SIZE_REAL48 /* INP INT24 */
    #define WRITE_MNI   WRITE_MN + PMAC_SIZE_INT24   /* INP REAL48 */


    #define INT24_C     OPCS_SIZE_HDR               /* Out INT24 */
    #define INT24_A     INT24_C + PMAC_SIZE_INT24   /* INP INT24 */
    #define INT24_B     INT24_A + PMAC_SIZE_INT24   /* INP INT24 */

    #define BOOL_C      OPCS_SIZE_HDR               /* OUT BOOL CMP INT24 */
    #define CMP24_A     BOOL_C + LZS_SIZEOF_BYTE    /* INP INT24 */
    #define CMP24_B     CMP24_A + PMAC_SIZE_INT24   /* INP INT24 */
    #define CMP48_A     BOOL_C + LZS_SIZEOF_BYTE    /* INP REAL48 */
    #define CMP48_B     CMP48_A + PMAC_SIZE_REAL48  /* INP REAL48 */

    #define REAL48_C    OPCS_SIZE_HDR               /* Out REAL48 */
    #define REAL48_A    REAL48_C + PMAC_SIZE_REAL48 /* INP REAL48 */
    #define REAL48_B    REAL48_A + PMAC_SIZE_REAL48 /* INP REAL48 */

    #define REAL48_OUT  OPCS_SIZE_HDR                    /* Out REAL48 */
    #define REAL48_IN   OPCS_SIZE_HDR + PMAC_SIZE_REAL48 /* INP REAL48 */
    #define CINT24_IN   OPCS_SIZE_HDR + PMAC_SIZE_REAL48 /* INP INT24 */

    #define INT24_OUT   OPCS_SIZE_HDR                    /* Out INT24 */
    #define CREAL48_IN  OPCS_SIZE_HDR + PMAC_SIZE_INT24  /* INP REAL48 */
    #define INT_IN      OPCS_SIZE_HDR + PMAC_SIZE_INT24
    #define INT24_IN    OPCS_SIZE_HDR + PMAC_SIZE_INT24

    #define INT_OUT     OPCS_SIZE_HDR                    /* Out INT */
    #define CINT24I_IN  OPCS_SIZE_HDR + LZS_SIZEOF_INT /* INP INT24 */

    #define LD_READ_EN      OPCS_SIZE_HDR                 /* IN BOOL */
    #define LD_READ_ENO     LD_READ_EN + LZS_SIZEOF_BYTE  /* OUT BOOL */
    #define LD_READ_LNO     LD_READ_ENO + LZS_SIZEOF_BYTE /* OUT INT24 */
    #define LD_READ_N       LD_READ_LNO + PMAC_SIZE_INT24 /* INP INT24 */

    #define LD_READ_MNO     LD_READ_ENO + LZS_SIZEOF_BYTE  /* OUT REAL48 */
    #define LD_READ_MN      LD_READ_MNO + PMAC_SIZE_REAL48 /* INP INT24 */

    #define LD_WRITE_EN     OPCS_SIZE_HDR                  /* IN BOOL */
    #define LD_WRITE_ENO    LD_WRITE_EN + LZS_SIZEOF_BYTE  /* OUT BOOL */
    #define LD_WRITE_LNO    LD_WRITE_ENO + LZS_SIZEOF_BYTE /* OUT INT24 */
    #define LD_WRITE_N      LD_WRITE_LNO + PMAC_SIZE_INT24 /* INP INT24 */
    #define LD_WRITE_LNI    LD_WRITE_N + PMAC_SIZE_INT24   /* INP INT24 */

    #define LD_WRITE_MNO    LD_WRITE_ENO + LZS_SIZEOF_BYTE   /* OUT REAL48 */
    #define LD_WRITE_MN     LD_WRITE_MNO + PMAC_SIZE_REAL48  /* INP INT24 */
    #define LD_WRITE_MNI    LD_WRITE_MN + PMAC_SIZE_INT24    /* INP REAL48 */

    #define LD_INT24_EN   OPCS_SIZE_HDR                   /* IN BOOL */
    #define LD_INT24_ENO  LD_INT24_EN + LZS_SIZEOF_BYTE   /* OUT BOOL */
    #define LD_INT24_C    LD_INT24_ENO + LZS_SIZEOF_BYTE  /* OUT INT24 */
    #define LD_INT24_A    LD_INT24_C + PMAC_SIZE_INT24    /* INP INT24 */
    #define LD_INT24_B    LD_INT24_A + PMAC_SIZE_INT24    /* INP INT24 */

    #define LD_REAL48_EN  OPCS_SIZE_HDR                    /* IN BOOL */
    #define LD_REAL48_ENO LD_REAL48_EN + LZS_SIZEOF_BYTE   /* OUT BOOL */
    #define LD_REAL48_C   LD_REAL48_ENO + LZS_SIZEOF_BYTE /* OUT REAL48 */
    #define LD_REAL48_A   LD_REAL48_C + PMAC_SIZE_REAL48   /* INP REAL48 */
    #define LD_REAL48_B   LD_REAL48_A + PMAC_SIZE_REAL48   /* INP REAL48 */

    /* #define LD_REAL48_EN   OPCS_SIZE_HDR                  */   /* IN BOOL */
    /* #define LD_REAL48_ENO  LD_REAL48_EN + LZS_SIZEOF_BYTE */  /* OUT BOOL */
    #define LD_REAL48_OUT LD_REAL48_ENO + LZS_SIZEOF_BYTE /* OUT REAL48 */
    #define LD_REAL48_IN  LD_REAL48_OUT + PMAC_SIZE_REAL48 /* INP REAL48 */
    #define LD_CINT24_IN  LD_REAL48_OUT  + PMAC_SIZE_REAL48 /* INP INT24 */

    #define LD_INT24_OUT  LD_INT24_ENO + LZS_SIZEOF_BYTE  /* Out INT24 */
    #define LD_CREAL48_IN LD_INT24_OUT + PMAC_SIZE_INT24  /* INP REAL48 */
    #define LD_INT_IN     LD_INT24_OUT + PMAC_SIZE_INT24  /* INP INT */
    #define LD_INT24_IN   LD_INT24_OUT + PMAC_SIZE_INT24  /* INP INT24 */

    #define LD_INT_OUT    LD_INT24_ENO + LZS_SIZEOF_BYTE  /* Out INT */
    #define LD_CINT24I_IN LD_INT_OUT + LZS_SIZEOF_INT     /* INP INT24 */



#else

/* === PMAC (pmac.cld) */
#pragma asm

OPCS_SIZE_HDR   EQU     6
        extern FRegDS
        DEFINE  L_DEF_ERROR     '#8,X:6'
; ****** PMAC ASM FUNCTION OFFSETS for INT24 & REAL48 *******

READ_LNO   EQU      OPCS_SIZE_HDR   ; OUT INT24
READ_N     EQU      7       ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR

READ_MNO   EQU      OPCS_SIZE_HDR   ; OUT REAL48
READ_MN    EQU      7      ; INP INT24 change on PMAC_SIZE_REAL48 or OPCS_SIZE_HDR


WRITE_LNO  EQU      OPCS_SIZE_HDR   ; OUT INT24
WRITE_N    EQU      7       ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR
WRITE_LNI  EQU      8       ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR

WRITE_MNO  EQU      OPCS_SIZE_HDR   ; OUT INT24
WRITE_MN   EQU      7       ; INP INT24 change on PMAC_SIZE_REAL48 or OPCS_SIZE_HDR
WRITE_MNI  EQU      8       ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR

INT24_C    EQU      OPCS_SIZE_HDR   ; OUT INT24
INT24_A    EQU      7       ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR
INT24_B    EQU      8       ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR

BOOL_C     EQU      OPCS_SIZE_HDR   ; OUT BOOL for CMP compare
CMP24_A    EQU      7       ; INP INT24 change on PMAC_SIZE_BOOL or OPCS_SIZE_HDR
CMP24_B    EQU      8       ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR
CMP48_A    EQU      7       ; INP REAL48 change on PMAC_SIZE_BOOL or OPCS_SIZE_HDR
CMP48_B    EQU      8       ; INP REAL48 change on PMAC_SIZE_REAL48 or OPCS_SIZE_HDR


REAL48_C   EQU      OPCS_SIZE_HDR   ; OUT REAL48 coded as -1 to REAL_A
REAL48_A   EQU      7       ; INP REAL48 change on OPCS_SIZE_HDR
REAL48_B   EQU      8       ; INP REAL48 coded as +1 to REAL_A

REAL48_OUT EQU      OPCS_SIZE_HDR   ;OUT REAL48
REAL48_IN  EQU      7       ; INP REAL48 coded as +1 to REAL48_OUT
CINT24_IN  EQU      7       ; INP INT24

INT24_OUT  EQU      OPCS_SIZE_HDR ; Out INT24
CREAL48_IN EQU      7       ; INP REAL48
INT_IN     EQU      7       ; INP INT
INT24_IN   EQU      7       ; INP INT24

INT_OUT    EQU      OPCS_SIZE_HDR ; Out INT
CINT24I_IN EQU      7       ; INP INT24

LD_READ_EN  EQU     OPCS_SIZE_HDR   ; IN BOOL
LD_READ_ENO EQU     7       ; OUT BOOL change on OPCS_SIZE_HDR
LD_READ_LNO EQU     8       ; OUT INT24 change on OPCS_SIZE_HDR
LD_READ_N   EQU     9       ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR

LD_READ_MNO EQU     8       ; OUT REAL48 ?? change on OPCS_SIZE_HDR
LD_READ_MN  EQU     9       ; INP INT24 ?? change on PMAC_SIZE_REAL48 or OPCS_SIZE_HDR

LD_WRITE_EN   EQU   OPCS_SIZE_HDR   ; IN BOOL
LD_WRITE_ENO  EQU   7       ; OUT BOOL change on OPCS_SIZE_HDR
LD_WRITE_LNO  EQU   8       ; OUT INT24 change on OPCS_SIZE_HDR
LD_WRITE_N    EQU   9       ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR
LD_WRITE_LNI  EQU   10      ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR

LD_WRITE_MNO  EQU   8       ; OUT REAL48 ?? change on OPCS_SIZE_HDR
LD_WRITE_MN   EQU   9       ; INP INT24 ?? change on PMAC_SIZE_REAL48 or OPCS_SIZE_HDR
LD_WRITE_MNI  EQU   10      ; INP REAL48 ?? change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR


LD_INT24_EN   EQU   OPCS_SIZE_HDR   ; IN BOOL
LD_INT24_ENO  EQU   7       ; OUT BOOL change on OPCS_SIZE_HDR
LD_INT24_C    EQU   8       ; OUT INT24
LD_INT24_A    EQU   9       ; INP INT24 change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR
LD_INT24_B    EQU   10      ; INP INT24 ?? change on PMAC_SIZE_INT24 or OPCS_SIZE_HDR

LD_REAL48_EN  EQU   OPCS_SIZE_HDR   ; IN BOOL
LD_REAL48_ENO EQU   7       ; OUT BOOL  change on OPCS_SIZE_HDR
LD_REAL48_C   EQU   8       ; OUT REAL48 coded as -1 to REAL_A
LD_REAL48_A   EQU   9       ; INP REAL48 change on OPCS_SIZE_HDR
LD_REAL48_B   EQU   10      ; INP REAL48 coded as +1 to REAL_A

;;LD_REAL48_EN   EQU   OPCS_SIZE_HDR   ; IN BOOL
;;LD_REAL48_ENO  EQU   7    ; OUT BOOL ?? change on OPCS_SIZE_HDR
LD_REAL48_OUT EQU  8        ; OUT REAL48
LD_REAL48_IN  EQU  9        ; INP REAL48 coded as +1 to REAL48_OUT
LD_CINT24_IN  EQU  9        ; /* INP INT24 */

LD_INT24_OUT  EQU  8        ; Out INT24
LD_CREAL48_IN EQU  9        ; INP REAL48
LD_INT_IN     EQU  9        ; INP INT
LD_INT24_IN   EQU  9        ; INP INT24

LD_INT_OUT    EQU  8        ; /* Out INT */
LD_CINT24I_IN EQU  9        ; /* INP REAL24 */


#pragma endasm

#endif


/* PMAC IL useable INT24 & REAL48 & STRING Functions/FB's */
/* and Ladder useable FB's */
  LZSBYTE  PMC_Fun_NEG_INT24(void);     /* Index=15 PMAC   */
  LZSBYTE  PMC_Fun_NEG_INT24_LD(void);  /* Index=16 PMAC   */
  LZSBYTE  PMC_Fun_NEG_REAL48(void);    /* Index=17 PMAC   */
  LZSBYTE  PMC_Fun_NEG_REAL48_LD(void); /* Index=18 PMAC   */
  LZSBYTE  PMC_Fun_ADD_INT24(void);     /* Index=19 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_ADD_INT24_LD(void);  /* Index=20 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_SUB_INT24(void);     /* Index=21 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_SUB_INT24_LD(void);  /* Index=22 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_MPY_INT24(void);     /* Index=23 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_MPY_INT24_LD(void);  /* Index=24 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_DIV_INT24(void);     /* Index=25 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_DIV_INT24_LD(void);  /* Index=26 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_MOD_INT24(void);     /* Index=27 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_MOD_INT24_LD(void);  /* Index=28 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_AND_INT24(void);     /* Index=29 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_AND_INT24_LD(void);  /* Index=30 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_OR_INT24(void);      /* Index=31 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_OR_INT24_LD(void);   /* Index=32 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_XOR_INT24(void);     /* Index=33 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_XOR_INT24_LD(void);  /* Index=34 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_ADD_REAL48(void);    /* Index=35 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ADD_REAL48_LD(void); /* Index=36 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_SUB_REAL48(void);    /* Index=37 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_SUB_REAL48_LD(void); /* Index=38 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_MPY_REAL48(void);    /* Index=39 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_MPY_REAL48_LD(void); /* Index=40 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_DIV_REAL48(void);    /* Index=41 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_DIV_REAL48_LD(void); /* Index=42 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_MOD_REAL48(void);    /* Index=43 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_MOD_REAL48_LD(void); /* Index=44 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_AND_REAL48(void);    /* Index=45 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_AND_REAL48_LD(void); /* Index=46 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_OR_REAL48(void);     /* Index=47 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_OR_REAL48_LD(void);  /* Index=48 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_XOR_REAL48(void);    /* Index=49 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_XOR_REAL48_LD(void); /* Index=50 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_SIN_REAL48(void);    /* Index=51 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_SIN_REAL48_LD(void); /* Index=52 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_COS_REAL48(void);    /* Index=53 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_COS_REAL48_LD(void); /* Index=54 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_TAN_REAL48(void);    /* Index=55 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_TAN_REAL48_LD(void); /* Index=56 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ABS_REAL48(void);    /* Index=57 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ABS_REAL48_LD(void); /* Index=58 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ASIN_REAL48(void);   /* Index=59 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ASIN_REAL48_LD(void);/* Index=60 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ACOS_REAL48(void);   /* Index=61 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ACOS_REAL48_LD(void);/* Index=62 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ATAN_REAL48(void);   /* Index=63 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ATAN_REAL48_LD(void);/* Index=64 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_SQRT_REAL48(void);   /* Index=65 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_SQRT_REAL48_LD(void);/* Index=66 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_EXP_REAL48(void);    /* Index=67 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_EXP_REAL48_LD(void); /* Index=68 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_LOGN_REAL48(void);    /* Index=69 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_LOGN_REAL48_LD(void); /* Index=70 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_GT_INT24(void);      /* Index=71 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_GE_INT24(void);      /* Index=72 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_EQ_INT24(void);      /* Index=73 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_NE_INT24(void);      /* Index=74 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_LE_INT24(void);      /* Index=75 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_LT_INT24(void);      /* Index=76 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_NOT_INT24(void);     /* Index=77 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_NOT_INT24_LD(void);  /* Index=78 PMAC    24 Bit Int Function */
  LZSBYTE  PMC_Fun_GT_REAL48(void);     /* Index=79 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_GE_REAL48(void);     /* Index=80 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_EQ_REAL48(void);     /* Index=81 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_NE_REAL48(void);     /* Index=82 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_LE_REAL48(void);     /* Index=83 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_LT_REAL48(void);     /* Index=84 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ATAN2_REAL48(void);  /* Index=85 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_ATAN2_REAL48_LD(void);/* Index=86 PMAC    48 Bit Flt Function */
  LZSBYTE  PMC_Fun_CMD_STR(void);       /* Index=87 PMAC    String Command */
  
  LZSBYTE  PMC_Fun_DISP_STR(void);      /* Index=88 PMAC    Variable DISPLAY */
  LZSBYTE  PMC_Fun_DISP_VAR(void);      /* Index=89 PMAC    Variable DISPLAY */

  LZSBYTE  PMC_Fun_LOCK(void);          /* Index=90 PMAC    LOCK */
  LZSBYTE  PMC_Fun_UNLOCK(void);        /* Index=91 PMAC    UNLOCK */
  LZSBYTE  PMC_Fun_SET_PHASE(void);     /* Index=92 PMAC    SET_PHASE */
  LZSBYTE  PMC_Fun_INT24_TO_REAL48(void); /* Index=93 PMAC */
  LZSBYTE  PMC_Fun_REAL48_TO_INT24(void); /* Index=94 PMAC */
  LZSBYTE  PMC_Fun_INT24_TO_INT(void);    /* Index=95 PMAC */
  LZSBYTE  PMC_Fun_INT_TO_INT24(void);    /* Index=96 PMAC */
  LZSBYTE  PMC_Fun_INT24_TO_REAL48_LD(void); /* Index=97 PMAC */
  LZSBYTE  PMC_Fun_REAL48_TO_INT24_LD(void); /* Index=98 PMAC */
  LZSBYTE  PMC_Fun_INT24_TO_INT_LD(void);    /* Index=99 PMAC */
  LZSBYTE  PMC_Fun_INT_TO_INT24_LD(void);    /* Index=100 PMAC */
  LZSBYTE  PMC_Fun_GREY4_TO_INT24(void);     /* Index=101 PMAC */
  LZSBYTE  PMC_Fun_GREY4_TO_INT24_LD(void);  /* Index=102 PMAC */
  LZSBYTE  PMC_Fun_SET_INT24_LD(void);  /* Index=103 PMAC   */
  LZSBYTE  PMC_Fun_SET_REAL48_LD(void); /* Index=104 PMAC   */
  LZSBYTE  PMC_Fun_ABS_INT24(void);     /* Index=105 PMAC   */
  LZSBYTE  PMC_Fun_ABS_INT24_LD(void);  /* Index=106 PMAC   */
  LZSBYTE  PMC_Fun_SHL_INT24(void);     /* Index=107 PMAC   */
  LZSBYTE  PMC_Fun_SHL_INT24_LD(void);  /* Index=108 PMAC   */
  LZSBYTE  PMC_Fun_SHR_INT24(void);     /* Index=109 PMAC   */
  LZSBYTE  PMC_Fun_SHR_INT24_LD(void);  /* Index=110 PMAC   */
  LZSBYTE  PMC_Fun_ROL_INT24(void);     /* Index=111 PMAC   */
  LZSBYTE  PMC_Fun_ROL_INT24_LD(void);  /* Index=112 PMAC   */
  LZSBYTE  PMC_Fun_ROR_INT24(void);     /* Index=113 PMAC   */
  LZSBYTE  PMC_Fun_ROR_INT24_LD(void);  /* Index=114 PMAC   */
  LZSBYTE  PMC_Fun_MAX_INT24(void);     /* Index=115 PMAC   */
  LZSBYTE  PMC_Fun_MAX_INT24_LD(void);  /* Index=116 PMAC   */
  LZSBYTE  PMC_Fun_MIN_INT24(void);     /* Index=117 PMAC   */
  LZSBYTE  PMC_Fun_MIN_INT24_LD(void);  /* Index=118 PMAC   */
  LZSBYTE  PMC_Fun_CYCLE_TIME(void);    /* Index=119 PMAC   */
  LZSBYTE  PMC_Fun_CMDL_STR(void);      /* Index=120 PMAC   */
  LZSBYTE  PMC_Fun_LOG_REAL48(void);    /* Index=121 PMAC  LOG10  48 Bit Flt Function */
  LZSBYTE  PMC_Fun_LOG_REAL48_LD(void); /* Index=122 PMAC  LOG10  48 Bit Flt Function */
  LZSBYTE  PMC_Fun_MAX_REAL48(void);    /* Index=123 PMAC   */
  LZSBYTE  PMC_Fun_MAX_REAL48_LD(void); /* Index=124 PMAC   */
  LZSBYTE  PMC_Fun_MIN_REAL48(void);    /* Index=125 PMAC   */
  LZSBYTE  PMC_Fun_MIN_REAL48_LD(void); /* Index=126 PMAC   */
  LZSBYTE  PMC_Fun_GetTimeREAL48(void); /* Index=127 PMAC   */
  LZSBYTE  PMC_Fun_GetTimeREAL48_LD(void); /* Index=128 PMAC   */
  LZSBYTE  PMC_Fun_TRUNC_REAL48(void);  /* Index=129    PMAC   */
  LZSBYTE  PMC_Fun_TRUNC_REAL48_LD(void); /* Index=130    PMAC   */

  LZSBYTE  PMC_Fun_BUS_WRITE(void);   /* Index=131 PMAC    String DISPLAY */

#ifdef __cplusplus
   }
#endif 

  
#endif