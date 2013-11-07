#ifndef _LZSTABLE_H_
#define _LZSTABLE_H_

/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

/* */
/* functions to manage and access the segment table */
/* */


void LzsSegInitSegTab(void);
void LzsSegDeleteSegTables(void);

tLzsSegTabEntry* LzsSegCreateSegTab(LZSWORD cSegTabEntrys_p);
LZSBOOL LzsSegCheckSegNum(tPlcSegNr nSegNum_p);
LZSBOOL LzsSegCheckSegNumInPrg(tPlcSegNr nSegNum_p,LZSDWORD wPrgNum);
LZSBYTE LzsSegGetSegType(tPlcSegNr nSegNum_p);
tPlcSegNr LzsSegGetSegNum(LZSBYTE bSegType_p);
LZSBYTE LzsSegWriteSegAddr(tPlcSegNr nSegNum_p, LZSBYTE Kind_p, tPlcMemPtr pSeg_p);

tPlcMemPtr LzsSegReadSegAddr(tPlcSegNr nSegNum_p, LZSBYTE Kind_p);
tPlcMemPtr LzsSegGetAddr(tPlchInst hInst_p, LZSBYTE bSegType_p);                         

tPlcMemPtr LzsSegGetAddrSeg(tPlchInst hInst_p,tLzsSegTabEntry LZSFAR* pSetTab_p,LZSBYTE bSegType_p);
tPlcMemPtr LzsSegGetSegFromTable(tLzsResourceSegmentTables LZSFAR* pSegTables, LZSWORD wPrgNum, tPlcSegNr SegNum_p);

tPlcMemPtr LzsSegGetIOMap1(void);
tPlcMemPtr LzsSegGetIOMap2(void);

/* P0699-specific */
tPlcMemPtr LzsSegGetHwConfig(void);
tPlcMemPtr LzsSegGetSHMConfig(void);
LZSWORD LzsSegGetSegSize(LZSWORD wSeg);

/* */
/* function to manage the TaskDefinitionTable */
/* */
void  LzsTdtInitTaskDefTab (void);
void  LzsTdtDelTaskDefSeg  (void);
LZSBYTE  LzsTdtSetTaskDefSeg  (tPlcMemPtr pSeg_p);
LZSPUBLIC32 tPlcTaskDefTable  LZSFAR*  LZSPUBLIC LzsTdtGetAddr (void); 
LZSPUBLIC32 tPlcMemPtr LZSPUBLIC LzsTdtSegGetAddr (void);

LZSBYTE	LzsSegSaveSegTables(void);
LZSPUBLIC32 LZSBOOL LzsTblCopyOldSegments(tPlcMemPtr pCopyTbl_p, LZSWORD *wExpectedSegmentNumber, LZSBOOL fDeleteTable_p);
void LzsSegDeleteTableOfSegmentTables(tLzsResourceSegmentTables LZSFAR* pSegmentTables);

/* 
 *functions to save a tmp segment for relink to segmenttable
 */
LZSBYTE  LzsSegSaveTempSeg (tPlcPgmNr nPgm_p, tPlcSegNr nSegNum_p, LZSBYTE Kind_p, tPlcMemPtr pSeg_p);
void LzsSegResetTempSeg(void);
LZSBYTE LzsSaveVersionInfo(LZSDWORD dwResVer, LZSDWORD dwPrgVer, LZSDWORD dwBuildDate, LZSDWORD dwLoadDate);
void LzsUpdateTDT(void);

LZSPUBLIC32 LZSBOOL LzsUpdateSegmentTable(LZSWORD wTaskIndex_p,    /*i:tasknumber*/
                                          LZSBYTE bKind_p,        /*i:primary or secundary*/
                                          tPlcMemPtr pOldSeg_p,    /*i:old segment pointer*/
                                          tPlcMemPtr pNewSeg_p);    /*i:new  segment pointer*/



LZSBYTE  LzsSegWriteSegAddrPrg (tPlcSegNr nSegNum_p, LZSBYTE Kind_p, tPlcMemPtr pSeg_p,  LZSWORD wPgmIndex_p);

tPlcMemPtr  LzsSegGetSegFromPrgAndNum(LZSWORD wPrgNum,tPlcSegNr SegNum_p);
tPlcSegNr  LzsSegGetSegFromPrgAndType(LZSWORD wPrgNum,LZSBYTE bType);

void LzsSegDeleteSpecSegTable(tLzsResourceSegmentTables LZSFAR* pSegTables_p, LZSWORD wPgmIndex_p);
void LzsSegDeleteSegFromTable(tLzsResourceSegmentTables LZSFAR* pSegTables, LZSWORD wPrgNum, tPlcSegNr SegNum_p);

#ifdef _LZS_OEMVERSINFO_
LZSPUBLIC32 LZSBOOL LzsGetOemVersion(tOemVersion* pOemVersion);
#endif

LZSPUBLIC32 LZSBOOL LzsGetResVersion(tLzsResVersion* pResVersion);
LZSPUBLIC32 LZSBOOL LzsCheckResVersion(tLzsResVersion* pResVersion);


/***************************************************************************/
/* [SYSTEC: 18.05.2004 -rs]: functions newly inserted                      */
/***************************************************************************/
#ifdef _LZS_GENERATE_TBL_DEBUG_INFO_

    void  LzsTblDbgEvaluateTaskDefTable  (void);
    void  LzsTblDbgEvaluateTaskDefEntry  (tPlcTaskDefTable LZSFAR* pTaskDefTable_p, LZSWORD nIdx_p);
    void  LzsTblDbgEvaluateSegTabTable   (void);
    void  LzsTblDbgEvaluateSegTabEntries (tLzsResourceSegmentTables LZSFAR* pResSegTable_p, LZSWORD nIdx_p);

#endif  /* #ifndef _LZS_GENERATE_TBL_DEBUG_INFO_ */



#endif

