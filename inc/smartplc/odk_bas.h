#ifndef __ODK_BAS_H__
#define __ODK_BAS_H__
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 2001                                                                      */
/*                                                                               */
/*                                                                               */
/* DESCRIPTION:  typedefs needed by runtime system and compiler                  */
/*********************************************************************************/

#include "oem/datatype.h"
#include "oem/odk_prj.h"
#include "smartplc/lzscbe.h"

/*--------------------------------------------------------------------------- */
/* common typedefs */
/*--------------------------------------------------------------------------- */

typedef LZSWORD         tPlchInst;      /* Instance handle */
typedef LZSWORD         tPlcBitAdr;     /* Bit address (8k) */
typedef LZSWORD         tPlcOffset;     /* 16Bit offset */
typedef LZSWORD         tPlcPgmNr;      /* Program number */
typedef LZSWORD         tPlcSegNr;      /* Segment number */
typedef tPlcOffset      tPlcSegSize;    /* Segment size */
typedef tPlcOffset      tPlcByteCount;  /* size max 64k */
typedef LZSWORD         tPlcFrmwModNr;  /* Number of firmware function block*/
typedef LZSBYTE LZSFAR* tPlcMemPtr;     /* Ptr to a segment (LZSFAR Address) */
typedef LZSBYTE LZSFAR* tPlcExtAE;      /* Ptr to "exteral AE" (for ANY) */

typedef struct 
{
    tPlcMemPtr    pAddr;
    LZSBYTE        bBitAddr;
    tCbeType    bCbeType;
    LZSWORD        wSize;
} tPlcPointerInfo;

#endif  /* __ODK_BAS_H__*/
