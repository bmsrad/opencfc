#ifndef _LZSDWL_H_
#define _LZSDWL_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                */
/*                                                                               */
/* DESCRIPTION: functions to control the downlowd                                */
/*********************************************************************************/

void  LzsDwlInitDownload   (void);
LZSBYTE  LzsDwlResource       (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsDwlResourceCont   (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsDwlResourceProcData (tPlcMemPtr pSeg_p);
LZSBYTE  LzsDwlProgram        (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsDwlProgramProcData  (tPlcPgmNr nPgmNum_p);
LZSBYTE  LzsDwlSegment        (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsDwlSegmentCont    (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsDwlSegmentProcData (tPlcMemPtr pSeg_p, tPlcSegNr nSegNum_p);
LZSBYTE  LzsDwlMultiSegments        (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsDwlMultiSegmentsCont    (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsDwlMultiSegmentsProcData (tPlcMemPtr pSeg_p, LZSWORD nSegNum_p, LZSWORD nSize);
LZSBYTE  LzsDwlSingleSegment        (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsDwlSingleSegmentCont    (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsDwlFinishDownLoad ( LZSBOOL fRestoreSystem);
/* RGV+ */
LZSBYTE LzsDwlFinishResource(void);
/* RGV- */
/*-----------------------------------------------------------------
  [SYSTEC/CANopen: 2003/10/06 -rs]: Function new inserted
-----------------------------------------------------------------*/
LZSBYTE  LzsDwlDcfFilesFinished      (void);

/*-----------------------------------------------------------------
  [SYSTEC: 21.05.2003 -rs]: Changed return value of function <LzsCreateInternalSegments> from void to LZSBYTE
                            otherwise no configuration errors will be reported to the IDE
  void LzsCreateInternalSegments(
      LZSWORD wProgramIndex_p,        // [i] Index into the ProgramTable
      tLzsExtraSeg* ExtraSegLst_p    // [i] ExtraSegmentNumbers 
    )
-----------------------------------------------------------------*/
LZSBYTE  LzsCreateInternalSegments(
    LZSWORD wProgramIndex_p,        /* [i] Index into the ProgramTable */
    tLzsExtraSeg* ExtraSegLst_p    /* [i] ExtraSegmentNumbers */
    );

LZSBYTE LzsCreatePISegment(void);
/*-----------------------------------------------------------------*/

LZSBYTE LzsInstantiateDataSegments(tPlcMemPtr pLinkerTable_p);
LZSWORD LzsGetProgramIndex(tPlcPgmNr nPgmNum_p);
LZSWORD LzsGetProgramIndexFromTable(tPlcPgmNr nPgmNum_p,tPlcTaskDefTable LZSFAR* pTDTab_p);

LZSBYTE  LzsDwlStartResource      (void);
LZSBYTE  LzsDwlDownloadCompletion (void);
LZSBYTE  LzsDwlAttachResourceGlobalSegments(void);
void  LzsDwlSetupPISegment(tPlcTaskDefTable LZSFAR* pTDTab_p);

/* [SYSTEC: 16.04.2002 -rs]: moved function from LzsPers.c to LzsDwl.c */
/* and corresponding prototype inserted */
LZSBYTE LzsCheckConfiguration (void);
#endif /*_LZSDWL_H_*/
