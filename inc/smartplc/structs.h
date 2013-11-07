/*
    struct.h - use this header file to work around compiler weaknesses 
    in properly aligning structures

    M. Sperber, 11.12.1998

*/


/* de-comment the following to use work-arounds */
#define USE_OFFSET_ADDRESSING


/* Local Helper Definitions */
#ifdef USE_OFFSET_ADDRESSING

    /*using offsets for PLC version structure*/

    #define STRUCT_PLCVER_HWVERSION        0        /*word*/
    #define STRUCT_PLCVER_FWVERSION        2        /*word*/
    #define STRUCT_PLCVER_IPVERSION        4        /*byte*/
    #define STRUCT_PLCVER_OEMID_OLD        5        /*byte*/
    #define STRUCT_PLCVER_IPTYPE        6        /*byte*/
    #define STRUCT_PLCVER_IPREVISION    7        /*byte*/
    #define STRUCT_PLCVER_NAME            8        /*62char*/
    #define STRUCT_PLCVER_OEMID            70        /*word*/
    

    #define STRUCT_PGMINFOSTART    128    /* offset of first TaskDefEntry within TaskDefTable */
    #define STRUCT_PGMINFOSIZE    106    /* size of TaskDefEntry */
    #define STRUCT_TASKDEFSIZE    234    /* size of Task Def Table (#pgm==1) */

    /* Offsets relative to Task Defintion Table */
    #define STRUCT_OFFSET_PRJNAME        0
    #define STRUCT_OFFSET_RESNAME        32
    #define STRUCT_OFFSET_IPVER            (64+0)
    #define    STRUCT_OFFSET_IPREV            (64+3)
    #define STRUCT_OFFSET_IPOEM            (64+1)
    #define STRUCT_OFFSET_IPTYPE        (64+2)
    #define STRUCT_OFFSET_PLCVER        68
    #define STRUCT_OFFSET_PROGCNT        72
    #define STRUCT_OFFSET_MAXSEGNR        76
    #define STRUCT_OFFSET_FLAGS            78
    #define STRUCT_OFFSET_PI            82
    #define STRUCT_OFFSET_NI            90

    #define STRUCT_OFFSET_BUILDDATE 96        /* _PI + 8 + 8(NI) */
    #define STRUCT_OFFSET_LOADDATE    100

#ifdef _LZS_OEMVERSINFO_
    #define STRUCT_OFFSET_OEMVER_MAJOR        116
    #define STRUCT_OFFSET_OEMVER_MINOR        118
    #define STRUCT_OFFSET_OEMVER_REVISION    120
    #define STRUCT_OFFSET_OEMVER_BUILD        122
#endif
    /* Offsets relative to start of Program Definition Entry */
    #define STRUCT_OFFSET_NAME                0
    #define STRUCT_OFFSET_PGMNR                32
    #define STRUCT_OFFSET_TASKTYPE            34
    #define STRUCT_OFFSET_TIMESPEC            36
    #define STRUCT_OFFSET_NWDEP                40
    #define STRUCT_OFFSET_PRGPROP            44
    #define STRUCT_OFFSET_MAININST            48
    #define STRUCT_OFFSET_ISTACKSIZE        (54+0)
    #define STRUCT_OFFSET_AESTACKENTRIES    (54+2)
    #define STRUCT_OFFSET_AESTACKSIZE        (54+4)
    #define STRUCT_OFFSET_EXTAESIZE            (54+6)
    #define STRUCT_OFFSET_PISEG                62
    #define STRUCT_OFFSET_NISEG                66
    #define STRUCT_OFFSET_PRGVERSION        70
    #define STRUCT_OFFSET_SEGCOUNT            74
    #define STRUCT_OFFSET_MAXSEGNR            76
    #define STRUCT_OFFSET_PRIO                78

    /* Offsets relative to tLzsResVersion */
    #define STRUCT_SIZE_RESVERSION    76
    #define STRUCT_OFFSET_RES_PRJNAME    0
    #define STRUCT_OFFSET_RES_RESNAME    32
    #define STRUCT_OFFSET_RES_PLCVER    64
    #define STRUCT_OFFSET_RES_BUILDDATE    68
    #define STRUCT_OFFSET_RES_LOADDATE    72

    /* Offset relative to tLzsDataAdr */
    #define STRUCT_OFFSET_WATCH_TYPE    0
    #define STRUCT_OFFSET_WATCH_PGMNR    1
    #define STRUCT_OFFSET_WATCH_SEGNR    3
    #define STRUCT_OFFSET_WATCH_OFFSET     5
    #define STRUCT_OFFSET_WATCH_SIZE    7
    #define STRUCT_OFFSET_WATCH_SEGTAB    9

    /* Offset relative to tLzsSetData */
    #define STRUCT_OFFSET_SETDATA_TYPE    0
    #define STRUCT_OFFSET_SETDATA_PGMNR    1
    #define STRUCT_OFFSET_SETDATA_SEGNR    3
    #define STRUCT_OFFSET_SETDATA_OFFSET     5
    #define STRUCT_OFFSET_SETDATA_SIZE    7
    #define STRUCT_OFFSET_SETDATA_DATA    9

    /* Offset relative to tLzsSetData */
    #define STRUCT_OFFSET_FORCE_WATCHID    0
    #define STRUCT_OFFSET_FORCE_VALUE    2
    #define STRUCT_OFFSET_FORCE_ACTIVE    6

    /* Offset relative to tLzsRemoveWatchItem */
    #define STRUCT_OFFSET_REMOVE_WATCH_ID 0
    
    /* Offsets relative to tIpBreakPointEntry */
    #define STRUCT_OFFSET_BREAKPOINT_PGMNR        0
    #define STRUCT_OFFSET_BREAKPOINT_INST        2
    #define STRUCT_OFFSET_BREAKPOINT_IPOFFSET    4
    #define STRUCT_OFFSET_BREAKPOINT_TYPE        6
    #define STRUCT_OFFSET_BREAKPOINT_ID            8

#else
    #define STRUCT_PGMINFOSIZE    sizeof(tPlcTaskDefEntry)
    #define STRUCT_TASKDEFSIZE    sizeof(tPlcTaskDefTable)
#endif

#ifdef USE_OFFSET_ADDRESSING
    #ifdef _LZS_DSALIGNMENT_DSP563_
    /* === PMAC 6Byte layout*/
        #define STRUCT_GET_PLCVER(TDT) LzsMemAbsGetDword_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PLCVER) 
        #define STRUCT_GET_PROGCNT(TDT) LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PROGCNT) 
        #define STRUCT_GET_IPVER(TDT) LzsMemAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPVER) 
        #define STRUCT_GET_IPREV(TDT) LzsMemAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPREV) 
        #define STRUCT_GET_IPOEM(TDT) LzsMemAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPOEM) 
        #define STRUCT_GET_IPTYPE(TDT) LzsMemAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPTYPE) 
        
        /* -fg- BUILD LOAD DATE */
        #define STRUCT_GET_BUILDDATE(TDT) LzsMemAbsGetDword_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_BUILDDATE) 
        #define STRUCT_GET_LOADDATE(TDT) LzsMemAbsGetDword_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_LOADDATE) 

#ifdef _LZS_OEMVERSINFO_
        #define STRUCT_GET_OEMVERMAJOR(TDT)        LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_MAJOR) 
        #define STRUCT_GET_OEMVERMINOR(TDT)        LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_MINOR) 
        #define STRUCT_GET_OEMVERREVISION(TDT)    LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_REVISION) 
        #define STRUCT_GET_OEMVERBUILD(TDT)        LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_BUILD) 
#endif


        #define STRUCT_GET_PISIZE(TDT) LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PI+0) 
        #define STRUCT_GET_NISIZE(TDT) LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_NI+0) 

        #define STRUCT_SET_PISIZE(TDT,WVAL) LzsMemAbsSetWord_1(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PI+0,WVAL)

        #define STRUCT_GET_PGM_MAXSEGNR(TDT,PROG)     LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_MAXSEGNR       +(PROG)*STRUCT_PGMINFOSIZE)

        #define STRUCT_GET_PGM_PISEG(TDT,PROG)      LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PISEG          +(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_NISEG(TDT,PROG)      LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_NISEG          +(PROG)*STRUCT_PGMINFOSIZE)

        #define STRUCT_SET_PGM_PISEG(TDT,PROG,VAL)      LzsMemAbsSetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PISEG          +(PROG)*STRUCT_PGMINFOSIZE , VAL)
        #define STRUCT_SET_PGM_NISEG(TDT,PROG,VAL)      LzsMemAbsSetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_NISEG          +(PROG)*STRUCT_PGMINFOSIZE ,VAL)

        #define STRUCT_GET_PGM_PGMNR(TDT,PROG)      LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PGMNR          +(PROG)*STRUCT_PGMINFOSIZE)


        #define STRUCT_GET_PGM_TASKTYPE(TDT,PROG)     LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_TASKTYPE       +(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_TIMESPEC(TDT,PROG)     LzsMemAbsGetDword_1(((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_TIMESPEC       +(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_PRIO(TDT,PROG)         LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PRIO           +(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_MAININST(TDT,PROG)     LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_MAININST       +(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_SEGCOUNT(TDT,PROG)     LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_SEGCOUNT       +(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_ISTACKSIZE(TDT,PROG)     LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_ISTACKSIZE     +(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_AESTACKSIZE(TDT,PROG)     LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_AESTACKSIZE    +(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_EXTAESIZE(TDT,PROG)     LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_EXTAESIZE      +(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_AESTACKENTRIES(TDT,PROG) LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_AESTACKENTRIES +(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_NAME(TDT,PROG) (((LZSBYTE LZSFAR *) TDT)+STRUCT_PGMINFOSTART+(PROG)*STRUCT_PGMINFOSIZE)
        #define STRUCT_GET_PGM_PRGVERSION(TDT,PROG)     LzsMemAbsGetDword_1(((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PRGVERSION       +(PROG)*STRUCT_PGMINFOSIZE)

    #else
        
        #ifndef _LZS_8BITBYTES_
            #define STRUCT_GET_PLCVER(TDT) LzsNetAbsGetDword(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PLCVER) 
            #define STRUCT_GET_PROGCNT(TDT) LzsNetAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PROGCNT) 
            #define STRUCT_GET_IPVER(TDT) LzsNetAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPVER) 
            #define STRUCT_GET_IPREV(TDT) LzsNetAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPREV) 
            #define STRUCT_GET_IPOEM(TDT) LzsNetAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPOEM) 
            #define STRUCT_GET_IPTYPE(TDT) LzsNetAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPTYPE) 
        #else
            #define STRUCT_GET_PLCVER(TDT) LzsMemAbsGetDword(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PLCVER) 
            #define STRUCT_GET_PROGCNT(TDT) LzsMemAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PROGCNT) 
            #define STRUCT_GET_IPVER(TDT) LzsMemAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPVER) 
            #define STRUCT_GET_IPREV(TDT) LzsMemAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPREV) 
            #define STRUCT_GET_IPOEM(TDT) LzsMemAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPOEM) 
            #define STRUCT_GET_IPTYPE(TDT) LzsMemAbsGetByte(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_IPTYPE) 
        #endif
    
        /* -fg- BUILD LOAD DATE */
        #ifndef _LZS_8BITBYTES_
            #define STRUCT_GET_BUILDDATE(TDT) LzsNetAbsGetDword(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_BUILDDATE) 
            #define STRUCT_GET_LOADDATE(TDT) LzsNetAbsGetDword(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_LOADDATE) 

#ifdef _LZS_OEMVERSINFO_
            #define STRUCT_GET_OEMVERMAJOR(TDT)        LzsNetAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_MAJOR) 
            #define STRUCT_GET_OEMVERMINOR(TDT)        LzsNetAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_MINOR) 
            #define STRUCT_GET_OEMVERREVISION(TDT)    LzsNetAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_REVISION) 
            #define STRUCT_GET_OEMVERBUILD(TDT)        LzsNetAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_BUILD) 
#endif

            #define STRUCT_GET_PISIZE(TDT) LzsNetAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PI+0) 
            #define STRUCT_GET_NISIZE(TDT) LzsNetAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_NI+0) 

            #define STRUCT_SET_PISIZE(TDT,WVAL) LzsNetAbsSetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PI+0,WVAL)

            #define STRUCT_GET_PGM_MAXSEGNR(TDT,PROG)     LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_MAXSEGNR       +(PROG)*STRUCT_PGMINFOSIZE)

            #define STRUCT_GET_PGM_PISEG(TDT,PROG)      LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PISEG          +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_NISEG(TDT,PROG)      LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_NISEG          +(PROG)*STRUCT_PGMINFOSIZE)

            #define STRUCT_SET_PGM_PISEG(TDT,PROG,VAL)      LzsNetAbsSetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PISEG          +(PROG)*STRUCT_PGMINFOSIZE , VAL)
            #define STRUCT_SET_PGM_NISEG(TDT,PROG,VAL)      LzsNetAbsSetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_NISEG          +(PROG)*STRUCT_PGMINFOSIZE ,VAL)

            #define STRUCT_GET_PGM_PGMNR(TDT,PROG)      LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PGMNR          +(PROG)*STRUCT_PGMINFOSIZE)
        #else
            #define STRUCT_GET_BUILDDATE(TDT) LzsMemAbsGetDword(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_BUILDDATE) 
            #define STRUCT_GET_LOADDATE(TDT) LzsMemAbsGetDword(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_LOADDATE) 

#ifdef _LZS_OEMVERSINFO_
            #define STRUCT_GET_OEMVERMAJOR(TDT)        LzsMemAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_MAJOR) 
            #define STRUCT_GET_OEMVERMINOR(TDT)        LzsMemAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_MINOR) 
            #define STRUCT_GET_OEMVERREVISION(TDT)    LzsMemAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_REVISION) 
            #define STRUCT_GET_OEMVERBUILD(TDT)        LzsMemAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_OEMVER_BUILD) 
#endif

            #define STRUCT_GET_PISIZE(TDT) LzsMemAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PI+0) 
            #define STRUCT_GET_NISIZE(TDT) LzsMemAbsGetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_NI+0) 

            #define STRUCT_SET_PISIZE(TDT,WVAL) LzsMemAbsSetWord(((LZSBYTE LZSFAR *) TDT)+STRUCT_OFFSET_PI+0,WVAL)

            #define STRUCT_GET_PGM_MAXSEGNR(TDT,PROG)     LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_MAXSEGNR       +(PROG)*STRUCT_PGMINFOSIZE)

            #define STRUCT_GET_PGM_PISEG(TDT,PROG)      LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PISEG          +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_NISEG(TDT,PROG)      LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_NISEG          +(PROG)*STRUCT_PGMINFOSIZE)

            #define STRUCT_SET_PGM_PISEG(TDT,PROG,VAL)      LzsMemAbsSetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PISEG          +(PROG)*STRUCT_PGMINFOSIZE , VAL)
            #define STRUCT_SET_PGM_NISEG(TDT,PROG,VAL)      LzsMemAbsSetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_NISEG          +(PROG)*STRUCT_PGMINFOSIZE ,VAL)

            #define STRUCT_GET_PGM_PGMNR(TDT,PROG)      LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PGMNR          +(PROG)*STRUCT_PGMINFOSIZE)
        #endif    

        #ifndef _LZS_8BITBYTES_
            #define STRUCT_GET_PGM_TASKTYPE(TDT,PROG)     LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_TASKTYPE       +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_TIMESPEC(TDT,PROG)     LzsNetAbsGetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_TIMESPEC       +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_PRIO(TDT,PROG)         LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PRIO           +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_MAININST(TDT,PROG)     LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_MAININST       +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_SEGCOUNT(TDT,PROG)     LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_SEGCOUNT       +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_ISTACKSIZE(TDT,PROG)     LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_ISTACKSIZE     +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_AESTACKSIZE(TDT,PROG)     LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_AESTACKSIZE    +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_EXTAESIZE(TDT,PROG)     LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_EXTAESIZE      +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_AESTACKENTRIES(TDT,PROG) LzsNetAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_AESTACKENTRIES +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_NAME(TDT,PROG) (((LZSBYTE LZSFAR *) TDT)+STRUCT_PGMINFOSTART+(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_PRGVERSION(TDT,PROG)     LzsNetAbsGetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PRGVERSION       +(PROG)*STRUCT_PGMINFOSIZE)
        #else
            #define STRUCT_GET_PGM_TASKTYPE(TDT,PROG)     LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_TASKTYPE       +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_TIMESPEC(TDT,PROG)     LzsMemAbsGetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_TIMESPEC       +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_PRIO(TDT,PROG)         LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PRIO           +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_MAININST(TDT,PROG)     LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_MAININST       +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_SEGCOUNT(TDT,PROG)     LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_SEGCOUNT       +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_ISTACKSIZE(TDT,PROG)     LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_ISTACKSIZE     +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_AESTACKSIZE(TDT,PROG)     LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_AESTACKSIZE    +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_EXTAESIZE(TDT,PROG)     LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_EXTAESIZE      +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_AESTACKENTRIES(TDT,PROG) LzsMemAbsGetWord (((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_AESTACKENTRIES +(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_NAME(TDT,PROG) (((LZSBYTE LZSFAR *) TDT)+STRUCT_PGMINFOSTART+(PROG)*STRUCT_PGMINFOSIZE)
            #define STRUCT_GET_PGM_PRGVERSION(TDT,PROG)     LzsMemAbsGetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PRGVERSION       +(PROG)*STRUCT_PGMINFOSIZE)
        #endif

    #endif

    #ifdef _LZS_DSALIGNMENT_DSP563_
        /* Macros to access tLzsResVersion */
        #define STRUCT_PUT_PLCVER(PRESVER,VAL) LzsMemAbsSetDword_1(((LZSBYTE LZSFAR *) PRESVER)+STRUCT_OFFSET_RES_PLCVER, VAL)
        /* -fg- BUILD LOAD DATE */
        #define STRUCT_PUT_LOADDATE(PRESVER,VAL) LzsMemAbsSetDword_1(((LZSBYTE LZSFAR *) PRESVER)+STRUCT_OFFSET_RES_LOADDATE, VAL)
        #define STRUCT_PUT_BUILDDATE(PRESVER,VAL) LzsMemAbsSetDword_1(((LZSBYTE LZSFAR *) PRESVER)+STRUCT_OFFSET_RES_BUILDDATE, VAL)

        #define STRUCT_SET_PGM_PRGVERSION(TDT,PROG,VAL) LzsMemAbsSetDword_1(((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PRGVERSION + (PROG)*STRUCT_PGMINFOSIZE , VAL)
        #define STRUCT_SET_PLCVER(TDT,VAL)                 LzsMemAbsSetDword_1(((LZSBYTE LZSFAR *) TDT) + STRUCT_OFFSET_PLCVER , VAL)
        #define STRUCT_SET_BUILDDATE(TDT,VAL)         LzsMemAbsSetDword_1(((LZSBYTE LZSFAR *) TDT) + STRUCT_OFFSET_BUILDDATE , VAL )
        #define STRUCT_SET_LOADDATE(TDT,VAL)         LzsMemAbsSetDword_1(((LZSBYTE LZSFAR *) TDT) + STRUCT_OFFSET_LOADDATE , VAL )
    #else
    /* Macros to access tLzsResVersion */

        #ifndef _LZS_8BITBYTES_
            #define STRUCT_PUT_PLCVER(PRESVER,VAL) LzsNetAbsSetDword(((LZSBYTE LZSFAR *) PRESVER)+STRUCT_OFFSET_RES_PLCVER, VAL)
            /* -fg- BUILD LOAD DATE */
            #define STRUCT_PUT_LOADDATE(PRESVER,VAL) LzsNetAbsSetDword(((LZSBYTE LZSFAR *) PRESVER)+STRUCT_OFFSET_RES_LOADDATE, VAL)
            #define STRUCT_PUT_BUILDDATE(PRESVER,VAL) LzsNetAbsSetDword(((LZSBYTE LZSFAR *) PRESVER)+STRUCT_OFFSET_RES_BUILDDATE, VAL)

            #define STRUCT_SET_PGM_PRGVERSION(TDT,PROG,VAL) LzsNetAbsSetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PRGVERSION + (PROG)*STRUCT_PGMINFOSIZE , VAL)
            #define STRUCT_SET_PLCVER(TDT,VAL)                 LzsNetAbsSetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_OFFSET_PLCVER , VAL)
            #define STRUCT_SET_BUILDDATE(TDT,VAL)         LzsNetAbsSetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_OFFSET_BUILDDATE , VAL )
            #define STRUCT_SET_LOADDATE(TDT,VAL)         LzsNetAbsSetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_OFFSET_LOADDATE , VAL )
        #else
            #define STRUCT_PUT_PLCVER(PRESVER,VAL) LzsMemAbsSetDword(((LZSBYTE LZSFAR *) PRESVER)+STRUCT_OFFSET_RES_PLCVER, VAL)
            /* -fg- BUILD LOAD DATE */
            #define STRUCT_PUT_LOADDATE(PRESVER,VAL) LzsMemAbsSetDword(((LZSBYTE LZSFAR *) PRESVER)+STRUCT_OFFSET_RES_LOADDATE, VAL)
            #define STRUCT_PUT_BUILDDATE(PRESVER,VAL) LzsMemAbsSetDword(((LZSBYTE LZSFAR *) PRESVER)+STRUCT_OFFSET_RES_BUILDDATE, VAL)

            #define STRUCT_SET_PGM_PRGVERSION(TDT,PROG,VAL) LzsMemAbsSetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_PGMINFOSTART + STRUCT_OFFSET_PRGVERSION + (PROG)*STRUCT_PGMINFOSIZE , VAL)
            #define STRUCT_SET_PLCVER(TDT,VAL)                 LzsMemAbsSetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_OFFSET_PLCVER , VAL)
            #define STRUCT_SET_BUILDDATE(TDT,VAL)         LzsMemAbsSetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_OFFSET_BUILDDATE , VAL )
            #define STRUCT_SET_LOADDATE(TDT,VAL)         LzsMemAbsSetDword(((LZSBYTE LZSFAR *) TDT) + STRUCT_OFFSET_LOADDATE , VAL )
        #endif

    #endif

    /* Macros to access tLzsDataAdr */
    #ifdef _LZS_DSALIGNMENT_DSP563_
        #define STRUCT_GET_WATCH_TYPE(DATA)        LzsMemAbsGetByte(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_TYPE)
        #define STRUCT_GET_WATCH_PGMNR(DATA)    LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_PGMNR)
        #define STRUCT_GET_WATCH_SEGNR(DATA)    LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_SEGNR)
        #define STRUCT_GET_WATCH_OFFSET(DATA)    LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_OFFSET)
        #define STRUCT_GET_WATCH_SIZE(DATA)        LzsMemAbsGetWord_1(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_SIZE)
    #else

        #ifndef _LZS_8BITBYTES_
            #define STRUCT_GET_WATCH_TYPE(DATA)    LzsNetAbsGetByte(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_TYPE)
            #define STRUCT_GET_WATCH_PGMNR(DATA)    LzsNetAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_PGMNR)
            #define STRUCT_GET_WATCH_SEGNR(DATA)    LzsNetAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_SEGNR)
            #define STRUCT_GET_WATCH_OFFSET(DATA)    LzsNetAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_OFFSET)
            #define STRUCT_GET_WATCH_SIZE(DATA)    LzsNetAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_SIZE)
        #else
            #define STRUCT_GET_WATCH_TYPE(DATA)    LzsMemAbsGetByte(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_TYPE)
            #define STRUCT_GET_WATCH_PGMNR(DATA)    LzsMemAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_PGMNR)
            #define STRUCT_GET_WATCH_SEGNR(DATA)    LzsMemAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_SEGNR)
            #define STRUCT_GET_WATCH_OFFSET(DATA)    LzsMemAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_OFFSET)
            #define STRUCT_GET_WATCH_SIZE(DATA)    LzsMemAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_WATCH_SIZE)
        #endif

    #endif

    #ifdef _LZS_DSALIGNMENT_DSP563_
        /* Macros to access tLzsSetData */
        #define STRUCT_GET_SETDATA_TYPE(LZSSETDATA)    LzsMemAbsGetByte (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_TYPE)
        #define STRUCT_GET_SETDATA_PGMNR(LZSSETDATA)    LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_PGMNR)
        #define STRUCT_GET_SETDATA_SEGNR(LZSSETDATA)    LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_SEGNR)
        #define STRUCT_GET_SETDATA_OFFSET(LZSSETDATA)    LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_OFFSET)
        #define STRUCT_GET_SETDATA_SIZE(LZSSETDATA)    LzsMemAbsGetWord_1 (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_SIZE)
        #define STRUCT_GET_SETDATA_DATA(LZSSETDATA)    LzsMemAbsGetByte (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_DATA)
    #else
    /* Macros to access tLzsSetData */

        #ifndef _LZS_8BITBYTES_
            #define STRUCT_GET_SETDATA_TYPE(LZSSETDATA)    LzsNetAbsGetByte (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_TYPE)
            #define STRUCT_GET_SETDATA_PGMNR(LZSSETDATA)    LzsNetAbsGetWord (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_PGMNR)
            #define STRUCT_GET_SETDATA_SEGNR(LZSSETDATA)    LzsNetAbsGetWord (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_SEGNR)
            #define STRUCT_GET_SETDATA_OFFSET(LZSSETDATA)    LzsNetAbsGetWord (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_OFFSET)
            #define STRUCT_GET_SETDATA_SIZE(LZSSETDATA)    LzsNetAbsGetWord (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_SIZE)
            #define STRUCT_GET_SETDATA_DATA(LZSSETDATA)    LzsNetAbsGetByte (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_DATA)
            #define STRUCT_GETW_SETDATA_DATA(LZSSETDATA)    LzsNetAbsGetWord (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_DATA)
            #define STRUCT_GETDW_SETDATA_DATA(LZSSETDATA)    LzsNetAbsGetDword (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_DATA)
        #else
            #define STRUCT_GET_SETDATA_TYPE(LZSSETDATA)    LzsMemAbsGetByte (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_TYPE)
            #define STRUCT_GET_SETDATA_PGMNR(LZSSETDATA)    LzsMemAbsGetWord (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_PGMNR)
            #define STRUCT_GET_SETDATA_SEGNR(LZSSETDATA)    LzsMemAbsGetWord (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_SEGNR)
            #define STRUCT_GET_SETDATA_OFFSET(LZSSETDATA)    LzsMemAbsGetWord (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_OFFSET)
            #define STRUCT_GET_SETDATA_SIZE(LZSSETDATA)    LzsMemAbsGetWord (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_SIZE)
            #define STRUCT_GET_SETDATA_DATA(LZSSETDATA)    LzsMemAbsGetByte (((LZSBYTE LZSFAR *) LZSSETDATA) + STRUCT_OFFSET_SETDATA_DATA)
        #endif
    #endif
    
    /* Macros to access tLzsForceData */
    #ifndef _LZS_8BITBYTES_
        #define STRUCT_GET_FORCE_WATCHID(DATA)    LzsNetAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_FORCE_WATCHID)
        #define STRUCT_GET_FORCE_VALUE(DATA)    LzsNetAbsGetDword(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_FORCE_VALUE)
        #define STRUCT_GET_FORCE_ACTIVE(DATA)    LzsNetAbsGetByte(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_FORCE_ACTIVE)
    #else
        #define STRUCT_GET_FORCE_WATCHID(DATA)    LzsMemAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_FORCE_WATCHID)
        #define STRUCT_GET_FORCE_VALUE(DATA)    LzsMemAbsGetDword(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_FORCE_VALUE)
        #define STRUCT_GET_FORCE_ACTIVE(DATA)    LzsMemAbsGetByte(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_FORCE_ACTIVE)
    #endif

    /* Macros to access tLzsRemoveWatchItem */
    #ifndef _LZS_8BITBYTES_
        #define STRUCT_GET_REMOVE_WATCH_ID(DATA)        LzsNetAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_REMOVE_WATCH_ID)
    #else
        #define STRUCT_GET_REMOVE_WATCH_ID(DATA)        LzsMemAbsGetWord(((LZSBYTE LZSFAR *) DATA)+STRUCT_OFFSET_REMOVE_WATCH_ID)
    #endif

    /* Macros to access breakpointentries */
    /* -ae- 2001/06/07 */
    #ifndef _LZS_8BITBYTES_
        #define STRUCT_GET_BREAKPOINT_PGMNR(DATA)        LzsNetAbsGetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_PGMNR)
        #define STRUCT_GET_BREAKPOINT_INST(DATA)        LzsNetAbsGetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_INST)
        #define STRUCT_GET_BREAKPOINT_IPOFFSET(DATA)    LzsNetAbsGetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_IPOFFSET)
        #define STRUCT_GET_BREAKPOINT_TYPE(DATA)        LzsNetAbsGetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_TYPE)
        #define STRUCT_GET_BREAKPOINT_ID(DATA)            LzsNetAbsGetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_ID)
        
        #define STRUCT_SET_BREAKPOINT_PGMNR(DATA,VAL)        LzsNetAbsSetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_PGMNR,VAL)
        #define STRUCT_SET_BREAKPOINT_INST(DATA,VAL)        LzsNetAbsSetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_INST,VAL)
        #define STRUCT_SET_BREAKPOINT_IPOFFSET(DATA,VAL)    LzsNetAbsSetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_IPOFFSET,VAL)
        #define STRUCT_SET_BREAKPOINT_TYPE(DATA,VAL)        LzsNetAbsSetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_TYPE,VAL)
        #define STRUCT_SET_BREAKPOINT_ID(DATA,VAL)            LzsNetAbsSetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_ID,VAL)
    #else
        #define STRUCT_GET_BREAKPOINT_PGMNR(DATA)        LzsMemAbsGetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_PGMNR)
        #define STRUCT_GET_BREAKPOINT_INST(DATA)        LzsMemAbsGetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_INST)
        #define STRUCT_GET_BREAKPOINT_IPOFFSET(DATA)    LzsMemAbsGetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_IPOFFSET)
        #define STRUCT_GET_BREAKPOINT_TYPE(DATA)        LzsMemAbsGetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_TYPE)
        #define STRUCT_GET_BREAKPOINT_ID(DATA)            LzsMemAbsGetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_ID)
        
        #define STRUCT_SET_BREAKPOINT_PGMNR(DATA,VAL)        LzsMemAbsSetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_PGMNR,VAL)
        #define STRUCT_SET_BREAKPOINT_INST(DATA,VAL)        LzsMemAbsSetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_INST,VAL)
        #define STRUCT_SET_BREAKPOINT_IPOFFSET(DATA,VAL)    LzsMemAbsSetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_IPOFFSET,VAL)
        #define STRUCT_SET_BREAKPOINT_TYPE(DATA,VAL)        LzsMemAbsSetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_TYPE,VAL)
        #define STRUCT_SET_BREAKPOINT_ID(DATA,VAL)            LzsMemAbsSetWord(((LZSBYTE LZSFAR* ) DATA) + STRUCT_OFFSET_BREAKPOINT_ID,VAL)
    #endif

#else
    #ifndef _LZS_8BITBYTES_
        #define STRUCT_GET_PLCVER(TDT) TDT->m_PlcVer.m_TimeStamp
        #define STRUCT_GET_PISIZE(TDT) LzsNetAbsGetWord(&TDT->m_PI.m_cSize)
        #define STRUCT_SET_PISIZE(TDT,WVAL) LzsNetAbsSetWord(&TDT->m_PI.m_cSize,WVAL)

        #define STRUCT_GET_PGM_MAXSEGNR(TDT,PROG) LzsNetAbsGetWord(&TDT->m_Pgm[PROG].m_MaxSegNr)
        #define STRUCT_GET_PGM_PISEG(TDT,PROG)  (TDT->m_Pgm[PROG].m_PISegments.m_Seg)
        #define STRUCT_GET_PGM_PGMNR(TDT,PROG) LzsNetAbsGetWord(&TDT->m_Pgm[PROG].m_nPrg)
        #define STRUCT_GET_PGM_TASKTYPE(TDT,PROG) LzsNetAbsGetWord(&TDT->m_Pgm[PROG].m_TaskType)
        #define STRUCT_GET_PGM_TIMESPEC(TDT,PROG) LzsNetAbsGetDword(&TDT->m_Pgm[PROG].m_dTimeSpec)
        #define STRUCT_GET_PGM_PRIO(TDT,PROG) LzsNetAbsGetWord(&TDT->m_Pgm[PROG].m_wPriority)
        #define STRUCT_GET_PGM_MAININST(TDT,PROG) TDT->m_Pgm[PROG].m_MainInst
        #define STRUCT_GET_PGM_SEGCOUNT(TDT,PROG) LzsNetAbsGetWord(&TDT->m_Pgm[PROG].m_cSegs)
        #define STRUCT_GET_PGM_ISTACKSIZE(TDT,PROG) TDT->m_Pgm[PROG].m_StackSizes.m_cInstStackSize
        #define STRUCT_GET_PGM_AESTACKSIZE(TDT,PROG) TDT->m_Pgm[PROG].m_StackSizes.m_cAEStackSize
        #define STRUCT_GET_PGM_EXTAESIZE(TDT,PROG) TDT->m_Pgm[PROG].m_StackSizes.m_cExtAESize
        #define STRUCT_GET_PGM_AESTACKENTRIES(TDT,PROG) TDT->m_Pgm[PROG].m_StackSizes.m_cAEStackEntrys
        #define STRUCT_GET_PGM_NAME(TDT,PROG) TDT->m_Pgm[PROG].m_szPgmName

#ifdef _LZS_OEMVERSINFO_
        #define STRUCT_GET_OEMVERMAJOR(TDT)        LzsNetAbsGetWord(TDT->m_wOemVerMajor) 
        #define STRUCT_GET_OEMVERMINOR(TDT)        LzsNetAbsGetWord(TDT->m_wOemVerMinor) 
        #define STRUCT_GET_OEMVERREVISION(TDT)    LzsNetAbsGetWord(TDT->m_wOemVerRevision) 
        #define STRUCT_GET_OEMVERBUILD(TDT)        LzsNetAbsGetWord(TDT->m_wOemVerBuild) 
#endif
    #else
        #define STRUCT_GET_PLCVER(TDT) TDT->m_PlcVer.m_TimeStamp
        #define STRUCT_GET_PISIZE(TDT) LzsMemAbsGetWord(&TDT->m_PI.m_cSize)
        #define STRUCT_SET_PISIZE(TDT,WVAL) LzsMemAbsSetWord(&TDT->m_PI.m_cSize,WVAL)

        #define STRUCT_GET_PGM_MAXSEGNR(TDT,PROG) LzsMemAbsGetWord(&TDT->m_Pgm[PROG].m_MaxSegNr)
        #define STRUCT_GET_PGM_PISEG(TDT,PROG)  (TDT->m_Pgm[PROG].m_PISegments.m_Seg)
        #define STRUCT_GET_PGM_PGMNR(TDT,PROG) LzsMemAbsGetWord(&TDT->m_Pgm[PROG].m_nPrg)
        #define STRUCT_GET_PGM_TASKTYPE(TDT,PROG) LzsMemAbsGetWord(&TDT->m_Pgm[PROG].m_TaskType)
        #define STRUCT_GET_PGM_TIMESPEC(TDT,PROG) LzsMemAbsGetDword(&TDT->m_Pgm[PROG].m_dTimeSpec)
        #define STRUCT_GET_PGM_PRIO(TDT,PROG) LzsMemAbsGetWord(&TDT->m_Pgm[PROG].m_wPriority)
        #define STRUCT_GET_PGM_MAININST(TDT,PROG) TDT->m_Pgm[PROG].m_MainInst
        #define STRUCT_GET_PGM_SEGCOUNT(TDT,PROG) LzsMemAbsGetWord(&TDT->m_Pgm[PROG].m_cSegs)
        #define STRUCT_GET_PGM_ISTACKSIZE(TDT,PROG) TDT->m_Pgm[PROG].m_StackSizes.m_cInstStackSize
        #define STRUCT_GET_PGM_AESTACKSIZE(TDT,PROG) TDT->m_Pgm[PROG].m_StackSizes.m_cAEStackSize
        #define STRUCT_GET_PGM_EXTAESIZE(TDT,PROG) TDT->m_Pgm[PROG].m_StackSizes.m_cExtAESize
        #define STRUCT_GET_PGM_AESTACKENTRIES(TDT,PROG) TDT->m_Pgm[PROG].m_StackSizes.m_cAEStackEntrys
        #define STRUCT_GET_PGM_NAME(TDT,PROG) TDT->m_Pgm[PROG].m_szPgmName

#ifdef _LZS_OEMVERSINFO_
        #define STRUCT_GET_OEMVERMAJOR(TDT)        LzsMemAbsGetWord(TDT->m_wOemVerMajor) 
        #define STRUCT_GET_OEMVERMINOR(TDT)        LzsMemAbsGetWord(TDT->m_wOemVerMinor) 
        #define STRUCT_GET_OEMVERREVISION(TDT)    LzsMemAbsGetWord(TDT->m_wOemVerRevision) 
        #define STRUCT_GET_OEMVERBUILD(TDT)        LzsMemAbsGetWord(TDT->m_wOemVerBuild) 
#endif

    #endif

    /* Macros to access tLzsResVersion */
    #define STRUCT_PUT_PLCVER(RESVER,VAL) RESVER->m_PlcVer.m_TimeStamp = VAL

    /* Macros to access tLzsDataAdr */
    #ifndef _LZS_8BITBYTES_
        #define STRUCT_GET_WATCH_TYPE(DATA)    LzsNetAbsGetByte(&DATA->m_Type)
        #define STRUCT_GET_WATCH_PGMNR(DATA)    LzsNetAbsGetWord(&DATA->m_Pgm)
        #define STRUCT_GET_WATCH_SEGNR(DATA)    LzsNetAbsGetWord(&DATA->m_Seg)
        #define STRUCT_GET_WATCH_OFFSET(DATA)    LzsNetAbsGetWord(&DATA->m_Offs)
        #define STRUCT_GET_WATCH_SIZE(DATA)    LzsNetAbsGetWord(&DATA->m_Size)
    #else
        #define STRUCT_GET_WATCH_TYPE(DATA)    LzsMemAbsGetByte(&DATA->m_Type)
        #define STRUCT_GET_WATCH_PGMNR(DATA)    LzsMemAbsGetWord(&DATA->m_Pgm)
        #define STRUCT_GET_WATCH_SEGNR(DATA)    LzsMemAbsGetWord(&DATA->m_Seg)
        #define STRUCT_GET_WATCH_OFFSET(DATA)    LzsMemAbsGetWord(&DATA->m_Offs)
        #define STRUCT_GET_WATCH_SIZE(DATA)    LzsMemAbsGetWord(&DATA->m_Size)
    #endif

    /* Macros to access tLzsSetData */
    #ifndef _LZS_8BITBYTES_
        #define STRUCT_GET_SETDATA_TYPE(LZSSETDATA)    LzsNetAbsGetByte(&pLzsSetData->m_Type)
        #define STRUCT_GET_SETDATA_PGMNR(LZSSETDATA)    LzsNetAbsGetWord(&pLzsSetData->m_Pgm)
        #define STRUCT_GET_SETDATA_SEGNR(LZSSETDATA)    LzsNetAbsGetWord(&pLzsSetData->m_Seg)
        #define STRUCT_GET_SETDATA_OFFSET(LZSSETDATA)    LzsNetAbsGetWord(&pLzsSetData->m_Offs)
        #define STRUCT_GET_SETDATA_SIZE(LZSSETDATA)    LzsNetAbsGetWord(&pLzsSetData->m_Size)
        #define STRUCT_GET_SETDATA_DATA(LZSSETDATA)    LzsNetAbsGetByte(&pLzsSetData->m_Data)
    #else
        #define STRUCT_GET_SETDATA_TYPE(LZSSETDATA)    LzsMemAbsGetByte(&pLzsSetData->m_Type)
        #define STRUCT_GET_SETDATA_PGMNR(LZSSETDATA)    LzsMemAbsGetWord(&pLzsSetData->m_Pgm)
        #define STRUCT_GET_SETDATA_SEGNR(LZSSETDATA)    LzsMemAbsGetWord(&pLzsSetData->m_Seg)
        #define STRUCT_GET_SETDATA_OFFSET(LZSSETDATA)    LzsMemAbsGetWord(&pLzsSetData->m_Offs)
        #define STRUCT_GET_SETDATA_SIZE(LZSSETDATA)    LzsMemAbsGetWord(&pLzsSetData->m_Size)
        #define STRUCT_GET_SETDATA_DATA(LZSSETDATA)    LzsMemAbsGetByte(&pLzsSetData->m_Data)
    #endif

#endif

#if 0
    CHECK_ANY(m_Pgm[0].m_szPgmName, 32);    /* 32 char */

#endif