#ifndef _DATATYPE_H_
#define _DATATYPE_H_

#ifndef _CONFIG_H_
#include "oem/config.h"
#endif

#ifdef __STDC__
    #include <limits.h>

    #define BYTE_MAX  UCHAR_MAX
    #define SINT_MAX  SHRT_MAX
    #define SINT_MIN  SHRT_MIN
    #define WORD_MAX  USHRT_MAX
    #define DWORD_MAX ULONG_MAX

    /* LD-specific */
    #define AWL_INT      signed short int
    #define AWL_INT_MAX  SHRT_MAX
    #define AWL_INT_MIN  SHRT_MIN
    #define AWL_UINT     unsigned short int
    #define AWL_UINT_MAX USHRT_MAX
    #if AWL_INT_MAX != 32767 || ( !(AWL_INT_MIN == (-32768) || AWL_INT_MIN == (-32767)) )
        #error ("AWL_INT has to be 16 bit")
    #endif
    #if AWL_UINT_MAX != 0xffff
        #error ("AWL_UINT has to be 16 bit")
    #endif
#else
    #define BYTE_MAX  255
    #define SINT_MAX  32767
    #define SINT_MIN  -32768
    #define WORD_MAX  65535
    #define DWORD_MAX 4294967295

    /* LD-specific */
    #define AWL_INT      signed short int
    #define AWL_INT_MAX  SINT_MAX
    #define AWL_INT_MIN  SINT_MIN
    #define AWL_UINT     unsigned short int
    #define AWL_UINT_MAX WORD_MAX
    #if AWL_INT_MAX != 32767 || ( !(AWL_INT_MIN == (-32768) || AWL_INT_MIN == (-32767)) )
        #error ("AWL_INT has to be 16 bit")
    #endif
    #if AWL_UINT_MAX != 0xffff
        #error ("AWL_UINT has to be 16 bit")
    #endif
#endif


/* 1 byte */
#define LZSCHAR char

/* this is for IEC-Type sint; 
    define it as "signed char" if your compiler interprets "char" as unsigned */
#define LZSSHORT signed char

/* 1 byte */
#define LZSBYTE unsigned char

/* 2 bytes */
#define LZSSINT signed short int
/* 2 bytes */ 
#define LZSINT signed short int
/* 2 bytes */
#define LZSUINT unsigned short int
/* 2 bytes */
#define LZSWORD unsigned short int

/* 4 bytes */
#define LZSLONG signed long int
/* 4 bytes */
#define LZSDWORD unsigned long int

/* 8 byte */
#define LZSLONGLONG    signed long long
/* 8 byte */
#define LZSQWORD unsigned long long

/* 1 LZSBYTE */
#define LZSBOOL unsigned char

/* 8 bytes */
#define LZSDOUBLE double


#ifdef _LZS_PMAC_
    #define PMAC_FLOAT long /*6Bytes*/
    #ifdef _IP_REAL48_
        #define LZSINT48 long
    #endif
    #ifdef _IP_INT24_
        #define LZSINT24 int
    #endif
#else 
    #ifdef _WIN32/*_WIN32*/
    /* === SmartSIM (Winlzs32.dll)*/
        /* FLOAT*/
        #define PMAC_FLOAT    double

        /* INTEGER*/
        #ifdef _IP_INT24_
            #define LZSINT24 __int32
        #endif
        #ifdef _IP_REAL48_
            #define LZSINT48 __int64
        #endif
    #else
        #ifdef _LZS_PRAGMAMESSAGE_
        #pragma message("INT24 and REAL48 not valid for this system")
        #endif
    #endif
#endif


#ifdef _LZS_32BITBYTES_
    #define LZS_SIZEOF_BYTE 1
    #define LZS_SIZEOF_CHAR 1

    #define LZS_SIZEOF_INT 1
    #define LZS_SIZEOF_SINT 1
    #define LZS_SIZEOF_WORD 1

    #define LZS_SIZEOF_DWORD 1
    #define LZS_SIZEOF_LONG 1
    #define LZS_SIZEOF_DOUBLE 2
#else
    #ifdef _LZS_16BITBYTES_
        #define LZS_SIZEOF_BYTE 1
        #define LZS_SIZEOF_CHAR 1

        #define LZS_SIZEOF_INT 1
        #define LZS_SIZEOF_SINT 1
        #define LZS_SIZEOF_WORD 1

        #define LZS_SIZEOF_DWORD 2
        #define LZS_SIZEOF_LONG 2
        #define LZS_SIZEOF_DOUBLE 4
    #else
        #define LZS_SIZEOF_BYTE 1
        #define LZS_SIZEOF_CHAR 1

        #define LZS_SIZEOF_INT 2
        #define LZS_SIZEOF_SINT 2
        #define LZS_SIZEOF_WORD 2

        #define LZS_SIZEOF_DWORD 4
        #define LZS_SIZEOF_LONG 4
        #define LZS_SIZEOF_DOUBLE 8
    #endif
#endif


#define LZS_NET_SIZEOF_BYTE 1
#define LZS_NET_SIZEOF_WORD 2
#define LZS_NET_SIZEOF_DWORD 4
#define LZS_NET_SIZEOF_DOUBLE 8


#ifndef _LZS_8BITBYTES_
    #define LZS_SIZEOF_LENGTHHEADER 2
#else
    #define LZS_SIZEOF_LENGTHHEADER sizeof(LZSWORD)
#endif


#ifdef _LZS_DSALIGNMENT_1_
    #ifdef _LZS_32BITBYTES_
        #define LZS_SIZEOF_DATASEGHDR 16
    #else
        #ifdef _LZS_16BITBYTES_
            #define LZS_SIZEOF_DATASEGHDR 8
        #else
            #define LZS_SIZEOF_DATASEGHDR 6
        #endif
    #endif
#else
    #ifdef _LZS_DSALIGNMENT_2_
        #define LZS_SIZEOF_DATASEGHDR 6
    #else
        #ifdef _LZS_DSALIGNMENT_4_
            #define LZS_SIZEOF_DATASEGHDR 8
        #else
            #define LZS_SIZEOF_DATASEGHDR 6
            /*#error no data segment alignment defined*/
        #endif
    #endif
#endif    


#define LZS_SIZEOF_SETDATA 64

#ifdef _LZS_32BITBYTES_
  #define MINUS_ONE      -1
#else
  #define MINUS_ONE      0xFFFF
#endif


#endif
