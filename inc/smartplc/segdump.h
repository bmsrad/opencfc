/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Do, 20 Aug 98                                                                 */
/*                                                                               */
/* DESCRIPTION:LZS DEBUG Functions oendk                                         */
/*********************************************************************************/

#ifndef _SEG_DUMP_H_
#define _SEG_DUMP_H_


#include    "oem/odk_prj.h"
#include    "smartplc/odk_plc.h"

#include    "smartplc/odk_szm.h"

#include <stdio.h>        /* because we should know what FILE is */

void LzsDebugDumpSegment(LZSWORD wSegNum_p,tPlcMemPtr pSeg_p);
void LzsDebugDisplayDump(void);
void LzsDebugDumpSegContent(char * pszBuf_p,FILE * pDumpFilep,tPlcMemPtr pSeg_p,LZSWORD wSegSize_p,LZSBOOL fIsHex_p);
void LzsDebugResetDump(void);
void LzsDebugDumpProgNum(LZSWORD wProgNum_p);

#endif
