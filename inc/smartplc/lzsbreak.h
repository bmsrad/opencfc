#ifndef _LZSBREAK_H_
#define _LZSBREAK_H_

#ifdef _IP_BREAKPOINTS_

    tIpBreakPoint LZSFAR* LzsBreakPointFindCurrentEntry(void);

  LZSBOOL LzsBreakPointSetPatch(
       tIpBreakPoint * pBreakPoint_p,    /* [i] Breakpoint to set */
       LZSBYTE            bPatch_p
       );

    LZSBYTE LzsBreakPointCtrlGo(tLzsPSCmd LZSFAR* pLzsPSCmd_p, LZSBOOL f_DelTmpBp_p);
    LZSBYTE LzsBreakPointCtrlStepOver(tLzsPSCmd LZSFAR* pLzsPSCmd_p);

    LZSBYTE LzsBreakPointCtrlStepIn(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
    
    LZSBYTE LzsBreakPointCtrlStepOut(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
    LZSBYTE LzsBreakPointSetTemp(LZSWORD wPgmNr_p,LZSWORD wInst_p,LZSWORD wOff_p);
    LZSBYTE LzsBreakPointClearTemp(void);

    tIpBreakPoint * LzsBreakPointFindEntry(LZSWORD wID_p,LZSWORD * pCount_p);
    tIpBreakPoint * LzsBreakPointFindEntryByOffset(LZSWORD wOffset_p,LZSWORD * pCount_p);
    tIpBreakPoint * LzsBreakPointFindEntryByOffsetCodeAndPrg(LZSWORD wProg_p,LZSWORD wCodeSeg_p,LZSWORD wOffset_p);

    void LzsBreakPointInitialize(void);

    LZSBYTE LzsBreakPointAdd(tLzsPSCmd LZSFAR* pLzsPSCmd_p, LZSBYTE needToCorrect);

    LZSBYTE LzsBreakPointRemove   (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
    LZSBYTE LzsBreakPointRemoveAll(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
    
    LZSBYTE LzsBreakPointSleepAll(tLzsPSCmd LZSFAR* pLzsPSCmd_p);
    LZSBYTE LzsBreakPointAwakeAll(tLzsPSCmd LZSFAR* pLzsPSCmd_p);

    LZSWORD  LzsBreakPointCallback(LZSBYTE bConnectionId_p, tPlcMemPtr pBuff_p, LZSWORD wBuffSize_p, LZSBYTE bMode_p);
    
    LZSBYTE     LzsBreakPointOnBreakEvent(void);

#endif /* #ifdef _IP_BREAKPOINTS_ */


#endif
