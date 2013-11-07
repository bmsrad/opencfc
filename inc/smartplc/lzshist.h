/******************************************************************************
 *  (c) 2005 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 *  DESCRIPTION:    variable data history over multiple cycles
 *  
 *****************************************************************************/

#ifndef _LZSHIST_H_
#define _LZSHIST_H_

#include "oem/config.h"
#include "oem/datatype.h"
#include "smartplc/odk_bas.h"
#include "smartplc/lzstypes.h"

#ifdef _LZS_HISTDATA_

typedef packed struct 
{    
    LZSWORD        wPgmIndex;        /* program / task index in task def segment. i.e. == GetProgramIndex(wPgmNr) */
    tPlcSegNr    SegNr;            /* segment and offset of variable memory location (in pSegmentTables_l[wPgmIndex].pSegTable) */
    tPlcOffset    Offset;
    LZSWORD        wSize;            /* size of variable in bytes */    
    tLzsAccessType    AccessType;

    /* Ring buffer for historical data storage.
       the following entries are not used or modified by LzsHist*() functions.
       They can be freely modified to match the functionality implemented 
       through the LzsEnvHist*() functions 
     */
    tPlcMemPtr  pHist;  /* historical data buffer allocated via LzsEnvInitElemBuffer() */
    tPlcMemPtr  pWrite; /* write pointer into pHist buffer */
    tPlcMemPtr  pRead;  /* read pointer into pHist buffer */
    
} tHistElem;

/* 
    'histElems_g' is a sparse array.

    At first, entries are added sequentially. Later, if entries get deleted randomly, 
    unused entries result. Since the array index is used to identify a variable in 
    the communcation with the OnlineServer, other entries cannot be moved to fill 
    the resulting hole.

    Thus, when traversing the array care of the unused entries must be taken.
    'wNumHistElemsToExamine_g' is the number of array entries that must be looked 
    at to see all used entries. Whether an entry is in use can be checked through the 
    LZS_HIST_ELEMINUSE macro.

    Basically:
    for (LZSWORD i=0; i<wNumHistElemsToExamine_g; i++)
    {
        if ( LZS_HIST_ELEMINUSE(i) ) 
        {
            // histElems_g[i] is in use
        }
    }

    wNumHistElemsUsed_g holds the total number of entries in use.
*/    

extern tHistElem histElems_g[ LZS_MAXHIST ];
extern LZSWORD wNumHistElemsUsed_g;
extern LZSWORD wNumHistElemsToExamine_g;

#define LZS_HIST_ELEMINUSE( wIndex )  (histElems_g[(wIndex)].wSize)


void LzsHistInitHistTab(void);

void LzsHistOnCycleEnd(LZSWORD wPgmIndex_p);
void LzsHistOnDownloadComplete();

LZSBYTE LzsHistCmdAddElem(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsHistCmdDelElem(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsHistCmdGetRange(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsHistCmdGetRangeCont(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsHistCmdGetRangeResult(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsHistCmdClear(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsHistCmdUpdate(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE LzsHistCmdUpdateCont(tLzsPSCmd LZSFAR* pLzsPSCmd_p);

/* in LzsEnvHistGetRange, if a passed ID has this value, then 
    the Online Server did not have that variable in its hist table.    
    It is still part of the request, so that an error can be 
    returned to the calling application through the result returned 
    by LzsEnvHistGetRange */
#define LZSHIST_ID_VARNOTINTBL_ONLSVR    0xffff    
#endif  /* #ifdef _LZS_HISTDATA_ */
        
#endif
