/*-----------------------------------------------------------
    5136-PFB PFBPROFI Shared Memory Interface Definitions

    Copyright (c) 1995-1997 S-S Technologies Inc.

------------------------------------------------------
 Revision History
------------------------------------------------------

 REV        DATE		  Description
------------------------------------------------------

 1.00  	6/18/96 10:59AM
 1.01  	1/13/97 02:43PM		definitions related to lay2sCntCfg,
							lay2mCntCfg, pfbEvtEna, pfbOptions,
							pfbMasCntrlCfg, slvCntCfg, lay2Cntrl,
                        	masCntCfg expressed as bit numbers removed
 1.02  	2/25/97 12:27PM  	changed all c++ comments to regular c comments
                        	added masExtErrInfo to MAS_CNTRL structure
 1.03  	4/17/97 9:53AM   	changed pfbWdTick to pfbWdKick
                        	moved pfbMasMinIoCycTme from 2d to 106
 1.04	8/9/98	12:03PM		Added errLay2MsgProcOvrn to PROFI_USR
 1.05	8/10/98 10;19PM		Added definition of the file
 	
----------------------------------------------------------*/

#ifndef _H__PROFICTL
#define _H__PROFICTL

#ifdef  __I960_CODE__
#pragma pack    1
#pragma align   1
#endif

#ifndef _H__PBMCTL
#ifndef __I960_CODE__
#define BCR port+0  /* Board Control Register       */
#define MCR port+1  /* Memory Control Register      */
#define MPR port+2  /* Memory Page Register         */
#define ICR port+3  /* Interrupt Control Register   */

/* BCR Equates */
#define I960_RUN        0x00    /* i960 reset signal not asserted         */
#define I960_RESET      0x01    /* set to assert i960 reset signal        */
#define I960_INT        0x02    /* set to assert interrupt to i960        */
#define I960_FAIL       0x40    /* if set, i960 fail signal is asserted   */
#define WD_BITE         0x80    /* if set, card watchdog has bitten       */

/* MCR Equates */
#define MEM_ENA         0x80    /* enable card memory in host address space */

/* ICR Equates */
#define INT_PEND        0x80    /* an interrupt is pending from the PFB card                            */
#define INT_CHN_PEND    0x40    /* an interrupt is pending on at least one card in the interrupt chain  */

#define PFB_MEM_PAGE_SIZE   16384   /* size of 5136-PFB shared memory page              */
#define PFB_MEM_NUM_PAGES   16      /* number of 5136-PFB shared memory pages (256k)    */

#ifndef SS_TYPES
#define SS_TYPES
/* data type definitions */
typedef unsigned char   uchr;   /*  8 bits */
typedef unsigned short  ushrt;  /* 16 bits */
typedef unsigned int    uint;   /* 16(pc)/32(i960) bits */
typedef unsigned long   ulng;   /* 32 bits */
#ifndef WIN32
typedef enum {False,True} bool;
#endif 							/* WIN32 */

#endif 							/* SS_TYPES */

#endif 							/* __I960_CODE__ */
#endif 							/* _H__PBMCTL */

/* layer 2 SAP (unsolicited message) control block */
typedef struct tagLAY2S_CNTRL
{
    volatile uchr   lay2sType;      /* 00 type of SAP (DP slave, Layer 2, or FMS)                           */
    volatile uchr   lay2sStn;       /* 01 if strict station, accept updates only from this station          */
    volatile uchr   lay2sSap;       /* 02 if strict SAP, accept updates only from this SAP                  */

    volatile uchr   lay2sSrcSap;    /* 03 source SAP from request                                           */

    volatile ushrt  lay2sCntCfg;    /* 04 Control and configuration register                                */

    volatile uchr   lay2sStatus;    /* 06 Status register (Host Reads Only)                                 */
    volatile uchr   lay2sError;     /* 07 Error register                                                    */
    volatile uchr   lay2sEvent;     /* 08 Events                                                            */

    volatile uchr   lay2sSrcStn;    /* 09 source station from request                                       */

    volatile ushrt  lay2sTimeOut;   /* 0a timeout for SAP * 10ms (1-8190, 0=disable)                        */

    volatile uchr   lay2sFrmCntrl;  /* 0c if strict FC, accept updates only specified Frame Control values  */
    volatile uchr   lay2sRspStatus; /* 0d Response Status if NOT_OK                                         */

             uchr   Res3;           /* 0e reserved - do not use                                             */

    volatile uchr   lay2sRxLen;     /* 0f actual receive data length in bytes                               */
    volatile uchr   lay2sRxMaxLen;  /* 10 receive data (from request) max length in bytes                   */
    volatile uchr   lay2sTxLen;     /* 11 transmit data (response) length in bytes                          */

    volatile ushrt  lay2sRxDataOfs; /* 12 receive data (from request) offset within mem page                */
    volatile ushrt  lay2sTxDataOfs; /* 14 transmit data (response) offset within mem page                   */

    volatile uchr   lay2sRxDataPage;/* 16 receive data (from request) data mem page                         */
    volatile uchr   lay2sTxDataPage;/* 17 transmit data (response) data mem page                            */

    volatile uchr   lay2sTxMaxLen;  /* 18 max transmit data (response) length in bytes                      */
    volatile uchr   lay2sNumAcyBufs;

             uchr   Res4[6];        /* 19-1f reserved - do not use                                          */
} LAY2S_CNTRL;
/* definitions related to lay2sType */
#define LAY2S_TYP_NOT_DEF         0x00
#define LAY2S_TYP_DP_SLAVE        0x01
#define LAY2S_TYP_LAYER2_SAP      0x02
#define LAY2S_TYP_FMS             0x03
#define LAY2S_TYP_MPI_SAP		  0x04
#define LAY2S_TYP_DP_MAS_MC2      0x05

/* definitions related to lay2sCntCfg */
#define LAY2S_CTL_RX_BYTE_SWAP    0x0004    /* swap hi and low bytes of rx data to this SAP                 */
#define LAY2S_CTL_EVT_RX_CHG      0x0008    /* generate event (intr) when rx data to this SAP changes       */
#define LAY2S_CTL_IGNORE_STS      0x0010    /* ignore status of this SAP block (all_ok flag, LED and event) */
#define LAY2S_CTL_EVT_UPDTE       0x0020    /* generate event (intr) when this SAP is updated (Indication)  */

/* definitions related to lay2sStatus */
#define LAY2S_STS_OK              0x80

/* definitions related to lay2sError */
#define LAY2S_ERR_NOT_OK          0x01
#define LAY2S_ERR_TIME_OUT        0x02
#define LAY2S_ERR_RX_LEN          0x03
#define LAY2S_ERR_TX_LEN          0x04
#define LAY2S_ERR_BAD_PARAM       0x05

/* definitions related to lay2sEvent */
#define LAY2S_EVT_UPDATE          0x01
#define LAY2S_EVT_RX_DATA_CHG     0x02

/* definitions related to lay2sFrmCntrl */
#define LAY2S_FC_ALL              0x00      /* accept all requests                                          */
#define LAY2S_FC_SDN_LO           0x01      /* accept only SDN lo priority                                  */
#define LAY2S_FC_SDN_HI           0x02      /* accept only SDN hi priority                                  */
#define LAY2S_FC_SDN_LO_HI        0x03      /* accept only SDN hi or lo priority                            */

#define LAY2S_FC_SDA_LO           0x05      /* accept only SDA lo priority                                  */
#define LAY2S_FC_SDA_HI           0x06      /* accept only SDA hi priority                                  */
#define LAY2S_FC_SDA_LO_HI        0x07      /* accept only SDA hi or lo priority                            */

#define LAY2S_FC_SRD_LO           0x09      /* accept only SRD lo priority                                  */
#define LAY2S_FC_SRD_HI           0x0a      /* accept only SRD hi priority                                  */
#define LAY2S_FC_SRD_LO_HI        0x0b      /* accept only SRD hi or lo priority                            */

#define LAY2S_FC_DDB_REQ          0x0c
#define LAY2S_FC_DDB_REQ_LO       0x0d
#define LAY2S_FC_DDB_REQ_HI       0x0e
#define LAY2S_FC_DDB_REQ_LO_HI    0x0f

/* layer 2 message control block */
typedef struct tagLAY2M_CNTRL
{
    volatile uchr   lay2mCntCfg;    /* 00 Control and configuration register                                */
    volatile uchr   lay2mState;     /* 01 Current state of message block                                    */
    volatile uchr   lay2mStatus;    /* 02 Status register (Host only Reads)                                 */
    volatile uchr   lay2mError;     /* 03 Error register                                                    */
    volatile uchr   lay2mEvent;     /* 04 Events                                                            */

             uchr   Res1;           /* 05 reserved - do not use                                             */

    volatile ushrt  lay2mUpdTime;   /* 06 update interval for periodic * 1ms (1-16380)                      */
    volatile ushrt  lay2mErrTime;   /* 08 retry interval for periodic if error occurs * 1ms                 */

    volatile uchr   lay2mDstStn;    /* 0a destination station address                                       */
    volatile uchr   lay2mDstSap;    /* 0b destination SAP (0xff to disable)                                 */
    volatile uchr   lay2mSrcSap;    /* 0c source SAP      (0xff to disable)                                 */
    volatile uchr   lay2mFrmCntrl;  /* 0d frame control byte                                                */
    volatile uchr   lay2mRspStatus; /* 0e Response Status if not OK                                         */

    volatile uchr   lay2mRxLen;     /* 0f actual receive data length in bytes                               */
    volatile uchr   lay2mRxMaxLen;  /* 10 max receive data (from response) max length in bytes              */
    volatile uchr   lay2mTxLen;     /* 11 transmit data (request) length in bytes                           */

    volatile ushrt  lay2mRxDataOfs; /* 12 receive data (from response) offset within layer 2 data mem page  */
    volatile ushrt  lay2mTxDataOfs; /* 14 transmit data (request) offset within layer 2 data mem page       */

    volatile uchr   lay2mRxDataPage;/* 16 receive data (from response) data mem page                        */
    volatile uchr   lay2mTxDataPage;/* 17 transmit data (request) data mem page                             */

    volatile uchr   lay2mTxMaxLen;  /* 18 max transmit data (request) length in bytes                       */

             uchr   Res3[7];        /* 19-1f reserved - do not use                                          */
} LAY2M_CNTRL;
/* definitions related to lay2mCntCfg */
#define LAY2M_CTL_PERIODIC        0x01
#define LAY2M_CTL_RETRY_PERIODIC  0x02
#define LAY2M_CTL_HI_PRI          0x04
#define LAY2M_CTL_EVT_RX_CHG      0x08  /* generate event (intr) when rx data to this message changes       */
#define LAY2M_CTL_IGNORE_STS      0x10  /* ignore status of this message block (all_ok, LED, and event)     */
#define LAY2M_CTL_EVT_CONFIRM     0x20  /* generate event (intr) when this message is confirmed             */
#define LAY2M_CTL_RX_BYTE_SWAP    0x40

/* definitions related to lay2mState */
#define LAY2M_STE_DISABLE         0x00
#define LAY2M_STE_IN_CONFIGURE    0x01
#define LAY2M_STE_ENABLE          0x02
#define LAY2M_STE_ACTIVE          0x03
#define LAY2M_STE_DONE            0xff

/* definitions related to lay2mStatus */
#define LAY2M_STS_OK              0x80

/* definitions related to lay2mError */
#define LAY2M_ERR_NOT_OK          0x01
#define LAY2M_ERR_RX_LEN          0x02
#define LAY2M_ERR_TX_LEN          0x03

/* definitions related to lay2mEvent */
#define LAY2M_EVT_CONFIRM         0x01
#define LAY2M_EVT_RX_DATA_CHG     0x02

/* definitions related to lay2mFrmCntrl */
#define FC_SDAl          0x03
#define FC_SDAh          0x05
#define FC_SDNl          0x04
#define FC_SDNh          0x06
#define FC_SRDl          0x0C
#define FC_SRDh          0x0D
#define FC_SmTime1       0x00
#define FC_SmTime2       0x80
#define FC_SmSDN         0x02
#define FC_SmSRD         0x01
#define FC_SmSRDSltDel   0x0A
#define FC_SmSRDSltKeep  0x0B
#define FC_DdbSRD        0x07
#define FC_DiagSRD       0x08
#define FC_ReqFDL        0x09
#define FC_ReqId         0x0E
#define FC_ReqLSAPSts    0x0F

/* definitions related to lay2mRspStatus */
#define RSP_STS_ACK      0x00
#define RSP_STS_DL       0x08
#define RSP_STS_DH       0x0a



#ifndef __I960_CODE__

/* general PFB control structure */
typedef struct tagPROFI_USR
{
/* 5136-PFB Basic Control/Status registers */
    volatile uchr   pfbCommand;         /* 00 Card command register                                         */
    volatile uchr   pfbStatus;          /* 01 Card status register                                          */

/* 5136-PFB Card and Module Identification registers */
    volatile ushrt  pfbCardId;          /* 02 5136-PFB Card ID (0xaad0)                                     */
    volatile ushrt  pfbModId;           /* 04 PFBPROFI Module ID     (0xbb01)                               */
    volatile ushrt  pfbModVer;          /* 06 PFBPROFI Module Version (ex. 0x0102 = 1.02)                   */

/* 5136-PFB --> Host Event and Interrupt control registers */
    volatile ushrt  pfbEvtEna;          /* 08 Event enable mask                                             */
    volatile ushrt  pfbIntEna;          /* 0a Event interrupt enable mask                                   */
    volatile uchr   pfbEvtHead;         /* 0c Event queue head pointer (changed by card)                    */
    volatile uchr   pfbEvtTail;         /* 0d Event queue tail pointer (changed by host)                    */

/* ASPC2 Profibus controller Basic Parameters */
    volatile uchr   pfbStnAddr;         /* 0e PFB Local station address                                     */
    volatile uchr   pfbHiStnAddr;       /* 0f highest station address on network                            */
    volatile uchr   pfbActive;          /* 10 1=active station, 0=passive station                           */
    volatile uchr   pfbBaud;            /* 11 network baud rate                                             */
    volatile ushrt  pfbOptions;         /* 12 network options                                               */

/* ASPC2 Profibus controller Bus Parameters (PFB will put in defaults if left unchanged) */
    volatile ulng   pfbTokRotTime;      /* 14 Target token rotation time                                    */
    volatile ushrt  pfbSlotTime;        /* 18 Slot time                                                     */
    volatile ushrt  pfbIdleTime1;       /* 1a Idle time 1                                                   */
    volatile ushrt  pfbIdleTime2;       /* 1c Idle time 2                                                   */
    volatile ushrt  pfbReadyTime;       /* 1e Ready time   (MinTsr)                                         */
    volatile uchr   pfbGapUpdFact;      /* 20 Gap update factor                                             */
    volatile uchr   pfbQuiTime;         /* 21 Tqui                                                          */

/* ASPC2 Profibus controller Error Handling Parameters */
    volatile uchr   pfbTokRetryLimit;   /* 22 Token retry limit                                             */
    volatile uchr   pfbMsgRetryLimit;   /* 23 Message retry limit                                           */
    volatile uchr   pfbTokErrLimit;     /* 24 Token error limit                                             */
    volatile uchr   pfbRespErrLimit;    /* 25 Response error limit                                          */

/* 5136-PFB --> Host Trigger Queue control */
    volatile uchr   pfbTrgHead;         /* 26 pfb function trigger event head pointer (changed by host)     */
    volatile uchr   pfbTrgTail;         /* 27 pfb function trigger event tail pointer (changed by card)     */

/* DP Master global status and control table pointer */
    volatile uchr   pfbMasCntrlCfg;     /* 28 Global control for all master blocks                          */
    volatile uchr   pfbMasSts;          /* 29 Global status for all master blocks                           */
    volatile uchr   pfbMasCntrlPage;    /* 2a Memory page which contains master block control table         */
    volatile uchr   pfbMasRxPage;       /* 2b Memory page which contains master Rx data (from slaves)       */
    volatile uchr   pfbMasTxPage;       /* 2c Memory page which contains master Tx data (to slaves)         */
    volatile uchr   pfbMasCoherFlags;   /* 2d Master tx and rx coherent data flags                          */
    volatile ushrt  pfbMasMaxIoCycTme;  /* 2e Maximum I/O cycle time in 10ms increments (0.01-655.35s)      */

/* FMS global status and control table pointer  */
    volatile uchr   pfbFmsCntrlCfg;     /* 30                                                               */
    volatile uchr   pfbFmsSts;          /* 31 Global status for all FMS blocks             (NI)             */
    volatile uchr   pfbFmsCrlPage;      /* 32 FMS Comm Rel List (CRL) Page                                  */

/* MPI global status and control table pointer  */
    volatile uchr   pfbMpiCntrlCfg;     /* 33                                                               */
    volatile uchr   pfbMpiSts;          /* 34 Global status for all MPI blocks             (NI)             */
    volatile uchr   pfbMpiCrlPage;      /* 35 MPI User Interface Page                                       */
	volatile uchr   pfbMpiReqTime;      /* 36 Last Request Execution time									*/

             uchr   Res3[0x40-0x37];    /* 39-3f Reserved, DO NOT USE                                       */

/* Diagnostic Counters and control */
    volatile uchr   pfbInitCtrs;        /* 40 if non-zero PFB will init counters then set back to 0         */

  /* General Statistics */
    volatile uchr   errLanOffline;      /* 41 Lan encountered errors and went into off-line state           */
    volatile ushrt  diagConf;           /* 42 Total confirmations (to requests from us)     (MAS,LAY2,FMS)  */
    volatile ushrt  diagInd;            /* 44 Total indications   (requests to us)          (MAS,LAY2,FMS)  */
    volatile ushrt  errNotOk;           /* 46 Total Not OK confirmations and/or indications (MAS,LAY2,FMS)  */
    volatile ulng   diagTokHldTime;     /* 48 Actual Instantaneous token hold time in Tbit                  */
    volatile ulng   diagMinTokHldTime;  /* 4c Minimum Actual token hold time in Tbit                        */

  /* DP Master Block Statistics */
    volatile ushrt  diagMasterUpdate;   /* 50 Master I/O update cycles completed                            */
    volatile uchr   errMasErr;          /* 52 Master->DP slave communication errors                         */
    volatile uchr   errReConfig;        /* 53 Master->DP went offline and had to be reconfigured            */
    volatile ulng   diagMasScanTime;    /* 54 Instantaneous master scan time in microseconds                */
    volatile ulng   diagMasMaxScanTime; /* 58 Maximum master scan time in microseconds                      */

  /* DP Slave Statistics */
    volatile ushrt  diagSlaveUpdate;    /* 5c Slave updates                                                 */
    volatile uchr   errSlvErr;          /* 5e Slave configuration failures                                  */
    volatile uchr   errSlvTout;         /* 5f Slave watchdog timeouts                                       */

  /* Layer 2 Message Statistics  */
    volatile ushrt  diagLay2MsgOk;      /* 60 Layer 2 messages sent ok                                      */
    volatile uchr   errLay2MsgNotOk;    /* 62 Layer 2 message errors                                        */
    volatile uchr   errLay2MsgProcOvrn; /* 63 Layer 2 message over run                                      */

  /* Layer 2 SAP Statistics  */
    volatile ushrt  diagLay2SapOk;      /* 64 Layer 2 SAP requests processed ok                             */
    volatile uchr   errLay2SapNotOk;    /* 66 Layer 2 SAP errors                                            */
    volatile uchr   errLay2SapTout;     /* 67 Layer 2 SAP update timeouts                                   */

             uchr   Res5[0x70-0x68];    /* 68-6f Reserved, DO NOT USE                                       */

  /* ASPC2 Profibus controller Statistics */
    volatile uchr   errInvReqLen;       /* 70 invalid request length errors                                 */
    volatile uchr   errFifo;            /* 71 FIFO overflow errors                                          */
    volatile uchr   errRxOverun;        /* 72 receive overrun errors                                        */
    volatile uchr   errDblTok;          /* 73 double token errors (bad wiring or hardware)                  */
    volatile uchr   errRespErr;         /* 74 response errors (bad wiring or hardware)                      */
    volatile uchr   errSyniErr;         /* 75 syni errors (bad wiring or hardware)                          */
    volatile uchr   errNetTout;         /* 76 network timeout errors                                        */
    volatile uchr   errHsa;             /* 77 Station higher than HSA was heard                             */
    volatile uchr   errStn;             /* 78 Duplicate Station Detected                                    */
    volatile uchr   errPasTok;          /* 79 Unable to Pass Token (bad wiring or hardware)                 */
    volatile uchr   errLasBad;          /* 7a active station list invalid (bad wiring or hardware)          */

    volatile uchr   errInternal;        /* 7b */
    volatile uchr   errArg;             /* 7c */
    volatile uchr   errEventOverun;     /* 7d a new event occurred before the last one was cleared          */

/* Active Station List */
    volatile uchr   pfbAckLasChnge;     /* 7e bit 0=1 to acknowledge station list change (card clears)      */
    volatile uchr   pfbUpdPasv;         /* 7f bit 0=1 to update status of passive stations (card clears)    */
    volatile uchr   pfbActStnList[128]; /* 80-ff Active Station list, 1 byte per station                    */

    volatile uchr   pfbBinCfgPage;      /* 100 master binary configuration memory page (filled in by PFB)   */
    volatile uchr   pfbBinCfgOfs;       /* 101 master binary config block offset (in 16k pages)             */
    volatile ushrt  pfbBinCfgLen;       /* 102 master binary configuration length of data in current page   */

    volatile ushrt  pfbMc2PollTout;     /* 104-105 poll time out for reception of master class 2 commands   */
    volatile ushrt  pfbMasMinIoCycTme;  /* 106 Minimum I/O cycle time in 100us increments (0-6.3535s)       */

    volatile ushrt  pfbWdTime;          /* 108 Host Watchdog Time in ms. Non-Zero to enable                 */
    volatile ushrt  pfbWdKick;          /* 10a Host Watchdog Kick card writes 1, host writes 0 to kick wdog */

    volatile uchr   pfbMasGlbEvt;       /* 10c dp master global event                                       */
    volatile uchr   pfbMasNumBlks;      /* 10d dp master - number of master blocks configured               */

    volatile ushrt  pfbMasCntrlExtFree; /* 10e                                                              */

    volatile uchr   pfbLocIdUsrStr[112];/* 110-17f Text for the 4 fields to return in the ID response       */

/* DP Slave controls */
    volatile ushrt  slvCntCfg;          /* 180 Control/config for dp slave function                         */
    volatile uchr   slvStatus;          /* 182 Status for dp slave function (Host Read Only)                */
    volatile uchr   slvError;           /* 183 Error indication for dp slave function                       */
    volatile uchr   slvEvent;           /* 184 Event Flags for dp slave function                            */
    volatile uchr   slvDiagEvent;       /* 185 Diagnostic Event Flags for dp slave function                 */

             uchr   Res9[2];            /* 186-187 Reserved, DO NOT USE                                     */

    volatile uchr   slvRxDataLen;       /* 188 Receive data len (data from master)                          */
    volatile uchr   slvReqRxDataLen;    /* 189 Receive data len requested by master                         */

             uchr   Res10[2];           /* 18a-18b Reserved, DO NOT USE                                     */

    volatile uchr   slvTxDataLen;       /* 18c Transmit data len (data to master)                           */
    volatile uchr   slvReqTxDataLen;    /* 18d Transmit data len requested by master                        */

    volatile uchr   slvChkLen;          /* 18e length of configuration check data                           */
    volatile uchr   slvParmLen;         /* 18f length of parameters from master                             */
    volatile uchr   slvGlbCntrl[2];     /* 190 global controls from master                                  */

             uchr   Res11[14];          /* 192-19f Reserved, DO NOT USE                                     */

    volatile uchr   slvSts1;            /* 1a0 status byte 1 to master                                      */
    volatile uchr   slvSts2;            /* 1a1 status byte 2 to master                                      */
    volatile uchr   slvSts3;            /* 1a2 status byte 3 to master                                      */
    volatile uchr   slvMasStn;          /* 1a3 Station that configured Slave                                */
    volatile uchr   slvID_hi;           /* 1a4 ID value to master hi byte (default 0x67)                    */
    volatile uchr   slvID_lo;           /* 1a5 ID value to master lo byte (default 0x15)                    */
    volatile uchr   slvDiagLen;         /* 1a6 Length of diagnostics to master                              */
    volatile uchr   slvDiag[25];        /* 1a7-1bf Diagnostics to master                                    */

    volatile uchr   slvMasSts;          /* 1c0 status byte from master                                      */
    volatile uchr   slvWdFact1;         /* 1c1 Watchdog factor 1 from master                                */
    volatile uchr   slvWdFact2;         /* 1c2 Watchdog factor 2 from master                                */
    volatile uchr   slvReadyTime;       /* 1c3 Response delay time (tbit) from master                       */
    volatile uchr   slvMasID_hi;        /* 1c4 ID value from master (hi byte)                               */
    volatile uchr   slvMasID_lo;        /* 1c5 ID value from master (lo byte)                               */
    volatile uchr   slvGrpId;           /* 1c6 Group ID value from master                                   */
    volatile uchr   slvParm[25];        /* 1c7-1df parameters from master                                   */
    volatile uchr   slvChk[32];         /* 1e0-1ff Configuration Check values from master                   */
    volatile uchr   slvRxData[256];     /* 200-2ff Slave data received from master                          */
    volatile uchr   slvTxData[256];     /* 300-3ff Slave data to be sent to master                          */

    volatile ushrt  pfbEventQueue[256]; /* 400-5ff event queue                                              */
    volatile ushrt  pfbTrigQueue[256];  /* 600-7ff trigger queue                                            */

    volatile uchr   pfbIdReq;           /* 800 bit 0=1 to request ID for station in pfbIdStn (card clears)  */
    volatile uchr   pfbIdStn;           /* 801 station to send ID request */
    volatile uchr   pfbIdRspSts;        /* 802 if non-zero, error getting ID                                */
    volatile uchr   pfbIdRspLen;        /* 803 total length of ID response                                  */

    volatile uchr   pfbIdFldLen[4];     /* 804-807 Length of the 4 fields returned in the ID response       */
    volatile uchr   pfbIdText[242];     /* 808-8f9 Text for the 4 fields returned in the ID response        */

             uchr   Res12[6];           /* 8fa-8ff Reserved, DO NOT USE                                     */

    volatile ushrt  pfbMasStsTab[128];  /* 900-9ff Master status/xref table arranged by station number      */

    volatile uchr   mc2CntCfg;          /* a00 */
    volatile uchr   mc2State;           /* a01 */
    volatile uchr   mc2Status;          /* a02 */
    volatile uchr   mc2Error;           /* a03 */
    volatile uchr   mc2Event;           /* a04 */
    volatile uchr   mc2RspSts;          /* a05 */
    volatile uchr   mc2TxLen;           /* a06 */
    volatile uchr   mc2RxLen;           /* a07 */
    volatile ushrt  mc2PollTime;        /* a08 */
    volatile ushrt  mc2PollLimit;       /* a0a */
    volatile uchr   mc2DstStn;          /* a0c */

             uchr   Res13[3];           /* a0d-a0f Reserved, DO NOT USE                                     */

    volatile uchr   mc2TxData[244];     /* a10-b03 */
    volatile uchr   mc2RxData[244];     /* b04-bf7 */

             uchr   Res14[0xfe0-0xbf8]; /* bf8-fdf Reserved, DO NOT USE                                     */

/* Layer 2 global status and control table pointer */
    volatile ushrt  lay2Cntrl;          /* fe0 Global control for all Layer 2 SAP's and MSG's               */
    volatile ushrt  lay2Status;         /* fe2 Global status  for all Layer 2 SAP's and MSG's               */

             uchr   Res15[0x1000-0xfe4];/* fea-fff Reserved, DO NOT USE                                     */

    LAY2M_CNTRL     Lay2mCntrl[128];    /* 1000-1fff Layer 2 Message control blocks                         */
    LAY2S_CNTRL     Lay2sCntrl[64];     /* 2000-27ff Layer 2 SAP control blocks                             */
} PROFI_USR;
#endif


/* definitions related to pfbCommand */
#define CMD_OFF             0xe0        /* PFB  - card offline ready to take commands                       */
#define CMD_ON              0xe1        /* PFB  - card is online ready to take offline command              */
#define CMD_COM_CFG         0xe2        /* PFB  - card is being configured from serial port                 */
#define CMD_ERROR           0xef        /* PFB  - card is in error, status contains error code              */

#define CMD_GO_ON           0x01        /* HOST - card should now go on line                                */
#define CMD_GO_OFF          0x02        /* HOST - card should now go off line, or abort config              */
#define CMD_REINIT          0x03        /* HOST - card should reinitialize memory and all parameters        */
#define CMD_CLR_CFG_BUF     0x04        /* HOST - card should clear pfbBinCfgPage                           */
#define CMD_CHK_NET_CFG     0x05        /* HOST - card should check network parameters, and assign defaults */
#define CMD_CPY_MAS_CFG     0x06        /* HOST - card should copy a page of cfg from pfbBinCfgPage         */
#define CMD_AUTO_BAUD_DET   0x07        /* HOST - card should do an automatic baud detect                   */
#define CMD_MAS_ASIGN_ADDR  0x08        /* HOST - assign and fill in data addr (page/offset) for dp master  */

#define CMD_CFG_ABF_SHRAM   0x0f        /* HOST - configure dp master from ABF   binary previously copied   */
#define CMD_CFG_2BF_SHRAM   0x10        /* HOST - configure dp master from ET200 binary previously copied   */
#define CMD_CFG_FROM_FLASH  0x11        /* HOST - configure card from configuration in flash                */
#define CMD_CFG_FLASH_GO_ON 0x14        /* HOST - configure card from flash then on line                    */

#define CMD_PGM_TO_FLASH    0x21        /* HOST - burn card configuration into flash                        */

#define CMD_CFG_ABF_FLASH   0x30        /*Configure module with config.bss file in flash					*/

#define CMD_CFG_2BF_FLASH   0x31        /*Configure module with config.2bf file in flash					*/

#define CMD_CFG_ABF_FLASH_GO_ON 0x32    /*Configure module with config.bss file in flash, then go online	*/

#define CMD_CFG_2BF_FLASH_GO_ON 0x33    /*Configure module with config.2bf file in flash, then go online    */

#define CMD_ERR_ACK         0xff        /* HOST - acknowledge offline error (online errors cannot be acked) */


/* definitions related to pfbStatus */
#define STS_NO_ERROR                    0x00
#define STS_BAD_CMD                     0x01
#define STS_BAD_BAUD                    0x02
#define STS_BAD_STN_ADR                 0x03
#define STS_BAD_HI_STN_ADR              0x04
#define STS_BAD_TOK_ROT                 0x05
#define STS_BAD_SLOT_TME                0x06
#define STS_BAD_IDLE_1                  0x07
#define STS_BAD_IDLE_2                  0x08
#define STS_BAD_RDY_TME                 0x09
#define STS_BAD_QUI_TME                 0x0a
#define STS_BAD_GAP_UPD                 0x0b
#define STS_BAD_TOK_RETRY               0x0c
#define STS_BAD_MSG_RETRY               0x0d
#define STS_BAD_TOK_ERR_LIM             0x0e
#define STS_BAD_RSP_ERR_LIM             0x0f
#define STS_BAUD_DET_ERROR              0x10    /* unable to detect baud rate (no activity detected)        */

#define STS_CFG_BAD_CHK_PATTERN         0x20    /* COM ET200 binary file corrupted                          */
#define STS_CFG_BIN_TOO_SHORT           0x21    /* COM ET200 binary file corrupted                          */
#define STS_CFG_BIN_TOO_LONG            0x22    /* COM ET200 binary file corrupted                          */
#define STS_CFG_BAD_CHKSUM              0x23    /* COM ET200 binary file corrupted                          */
#define STS_CFG_INVALID_CPU_HDR         0x24    /* COM ET200 binary file corrupted                          */
#define STS_CFG_INVALID_SLV_REC_TYP     0x25    /* COM ET200 binary file corrupted                          */
#define STS_CFG_RX_OVERFLOW             0x26    /* too much Master Rx data has been configured (16k max)    */
#define STS_CFG_TX_OVERFLOW             0x27    /* too much Master Tx data has been configured (16k max)    */

#define STS_CFG_DESIG_NAME_TOO_LONG     0x28    /* Nm= parameter, name too long (12 chars max)              */
#define STS_CFG_DESIG_BAD_ARG           0x29    /* unrecognized argument (Nm=, Tx=, Rx=, Ch)                */
#define STS_CFG_INV_RX_OFS              0x2a    /* Rx= parameter, invalid offset (0000-3ff8)                */
#define STS_CFG_INV_TX_OFS              0x2b    /* Tx= parameter, invalid offset (0000-3ff8)                */
#define STS_CFG_DESIG_OFS_NOT_SPEC      0x2c    /* Rx,Tx Ofs have been spec'd for one, but not all slaves   */
#define STS_CFG_RX_OVERLAP              0x2d    /* Rx data of one block overlaps another                    */
#define STS_CFG_TX_OVERLAP              0x2e    /* Tx data of one block overlaps another                    */
#define STS_CFG_INV_LEN                 0x2f    /* invalid parameter or check data length                  */
#define STS_CFG_MAS_EXT_ALLOC_ERR       0x35    /* out of master extension memory                           */
#define STS_CFG_ADDR_OUT_OF_RANGE       0x37    /* out of master extension memory                           */
#define STS_CFG_COPY_TABLE_OVERUN       0x38    /* not enough room in copy table                            */

#define STS_CFG_NO_CONFIG               0x30    /* no configuration present to program into flash           */
#define STS_FLASH_BAD_ID                0x31    /* internal flash error                                     */
#define STS_FLASH_ERASE_ERR             0x32    /* internal flash error                                     */
#define STS_FLASH_PROG_ERR              0x33    /* internal flash error                                     */
#define STS_FLASH_VRFY_ERR              0x34    /* internal flash error                                     */
#define STS_LAY2M_INV_MAX_LEN           0x36


/* the following are fatal errors. the card must be rerun (PFBRUN), or reloaded (PFBINST) */
#define STS_CFG_INTERNAL_ERROR          0x80
#define STS_OUT_OF_APBS                 0x81
#define STS_HOST_WD_BITE                0x82    /* host did not kick PFB watchdog within watchdog period    */
#define STS_HEAP_ALLOC_FAIL             0x83
#define STS_SH_HEAP_ALLOC_FAIL          0x84

#define STS_NET_ERROR                   0x90    /* net error, OPTION_STAY_OFF_ERR set, card is offline      */

/* definitions related to pfbCardId */
#define CRD_5136_PFB        0xaad0     /* applications can use this to verify that 5136-PFB card is present */

/* definitions related to pfbModId */
#define MOD_PROFI           0xbb01     /* apps can use this to verify that PFBPROFI module is present       */

/* definitions related to pfbEvtEna */
#define EVT_ENA_LAS_CHANGE  0x0001    /* active station list change                                        */
#define EVT_ENA_BUS_ERROR   0x0002    /* profibus error                                                    */

/* definitions related to pfbIntEna */
#define INT_ENA_LAS_CHANGE   0x0001   /* active station list change                                        */
#define INT_ENA_BUS_ERROR    0x0002   /* profibus error                                                    */
#define INT_ENA_DP_MAS_EVENT 0x0004   /* DP master event has occurred                                      */
#define INT_ENA_DP_SLV_EVENT 0x0008   /* DP slave  event has occurred                                      */
#define INT_ENA_LY2M_EVENT   0x0010   /* Layer 2 message event has occurred                                */
#define INT_ENA_LY2S_EVENT   0x0020   /* Layer 2 SAP event has occurred                                    */
#define INT_ENA_FMS_EVENT    0x0040
#define INT_ENA_MPI_EVENT    0x0080

/* definitions related to pfbBaud */
#define BAUD_9k6        0
#define BAUD_19k2       1
#define BAUD_93k75      2
#define BAUD_187k5      3
#define BAUD_500k       4
#define BAUD_750k       5
#define BAUD_1m5        6
#define BAUD_3m         7
#define BAUD_6m         8
#define BAUD_12m        9


/* definitions related to pfbOptions */
#define OPTION_REPEATER     0x0001      /* 1=repeater on network, 0=no repeater on network                  */
#define OPTION_FMS          0x0002      /* 1=fms devices on network, 0=dp only on network                   */
#define OPTION_STAY_OFF_ERR 0x0004      /* stay offline if token error limit or msg error limit exceeded    */

/* definitions related to pfbMasCntrlCfg */
#define PFB_MAS_CTRL_SYNC_SCAN     0x01 /* enable syncronized scan                                          */
#define PFB_MAS_CTRL_RUN_MODE      0x02 /* scan i/o in RUN mode                                             */
#define PFB_MAS_CTRL_USR_OFS       0x04 /* user defined rx and tx data offsets (no pfb auto assign)         */
#define PFB_MAS_CTRL_ENABLE        0x08 /* enable master mode on PFB card                                   */
#define PFB_MAS_CTRL_DIS_LED       0x10 /* disable status led for dp master function                        */
#define PFB_MAS_CTRL_HOLD_INTR     0x20 /* hold dp master event interrupt(s) until end of scan              */
#define PFB_MAS_CTRL_EVT_SCAN_DONE 0x40 /* generate event (intr) at end of scan                             */
#define PFB_MAS_CTRL_ADDR_ASIGNED  0x80 /* dp master data addresses have been assigned                      */

/* definitions related to pfbMasGlbEvt */
#define PFB_MAS_SCAN_DONE           0x01

/* definitions related to pfbMasSts */
#define PFB_MAS_STS_ALL_OK      0x01    /* all i/o configured for master to scan is being scanned ok        */

/* definitions related to pfbMasCoherFlags                                                                  */
#define PFB_MAS_TXPG_UPDATE     0x01    /* The tx data for at least one mas block has been updated          */
#define PFB_MAS_RXPG_LOCK       0x02    /* The host is currently reading the at least one mas block's rx pg */
#define PFB_MAS_COHER_ENA       0x80    /* Enable the master block data coherency option                    */

/* definitions related to pfbFmsCntrlCfg */
#define PFB_FMS_CNTRL_ENABLE    0x80    /* enable FMS on the PFB card                                       */

/* definitions related to pfbFmsSts 	*/
#define PFB_FMS_STS_CRL_ALL_OK  0x01    /* no errors on any CRL entries        								*/

/* definitions related to pfbMpiCntrlCfg */
#define PFB_MPI_CNTRL_ENABLE    0x80    /* enable MPI on the PFB card                                       */

/* definitions related to pfbMpiSts 	*/
#define PFB_MPI_STS_ALL_OK		0x01	/* no errors on any MPI blocks										*/

/* definitions related to pfbActStnList */
#define LAS_PASSIVE             0x01    /* this station is passive                                          */
#define LAS_ACTIVE              0x04    /* this station is active                                           */
#define LAS_CHANGED             0x08    /* status of this station has changed                               */

/* definitions related to slvCntCfg */
#define SLV_CTL_DIAG_UPD         0x0001 /* request diagnostic read from master                              */
#define SLV_CTL_EVT_RX_CHG       0x0002 /* generate event (intr) when rx data to slave changes              */
#define SLV_CTL_FORCE_READY_TIME 0x0004 /* force resp time (pfbReadyTime), and ignore what the master sends */
#define SLV_CTL_IGN_SYNC_FRZ_ERR 0x0008 /* don't generate error if master request sync and/or freeze        */
#define SLV_CTL_RX_BYTE_SWAP     0x0010 /* swap upper and lower bytes of rx data                            */
#define SLV_CTL_EVT_UPDTE        0x0020 /* generate event (intr) when slave is updated                      */
#define SLV_CTL_EVT_MODE_CHANGE  0x0040 /* generate event (intr) when slave mode changes (master RUN/STOP)  */
#define SLV_CTL_IGNORE_STS       0x0080 /* ignore status of slave (no event)                                */
#define SLV_CTL_DIS_LED          0x4000 /* disable status led for dp slave function                         */
#define SLV_CTL_ENABLE           0x8000 /* enable PFB to act as dp slave                                    */

/* definitions related to slvStatus */
#define SLV_STS_RUN_MODE        0x40    /* we're being scanned in run mode                                  */
#define SLV_STS_OK              0x80    /* current slave status is OK                                       */

/* definitions related to slvError */
#define SLV_ERR_ID_MISM         0x01    /* ID from master does not match configured ID                      */
#define SLV_ERR_READY_TIME_MISM 0x02    /* pfbReadyTime does not match what master sent                     */
#define SLV_ERR_UNSUP_REQ       0x03    /* pfb is requesting Freeze or Sync, which is not supported         */
#define SLV_ERR_RX_LEN_MISM     0x04    /* length of data from master to us incorrect                       */
#define SLV_ERR_TX_LEN_MISM     0x05    /* length of data from us to master incorrect                       */
#define SLV_ERR_WD_FACT_INV     0x06    /* slvWdFact1 or slvWdFact2 from master was 0                       */
#define SLV_ERR_TIME_OUT        0x07    /* slave watchdog time out (check response timeout)                 */
#define SLV_ERR_WARN_WD_DIS     0x08    /* slave timeout watch dog disabled from master                     */

/* definitions related to slvEvent */
#define SLV_EVT_UPD             0x01    /* master has updated us                                            */
#define SLV_EVT_RX_DATA_CHG     0x02    /* rx data from master has changed                                  */

/* definitions related to slvDiagEvent */
#define SLV_DEVT_DIAG_UPD       0x01    /* master has read diagnostic info                                  */

/* definitions related to pbfEventQueue */
#define EVT_PFB                 0x0
#define EVT_PFB_FAT_RUN_ERR     0x0100
#define EVT_PFB_OFFLINE_STAY    0x0200
#define EVT_PFB_FATAL_INTERNAL  0x0300

#define EVT_LAN                 0x1
#define EVT_LAN_INV_REQ_LEN     0x1000
#define EVT_LAN_FIFO_ERR        0x1100
#define EVT_LAN_RX_OVERUN       0x1200
#define EVT_LAN_DBL_TOK         0x1300
#define EVT_LAN_RSP_ERR         0x1400
#define EVT_LAN_SYNI_ERR        0x1500
#define EVT_LAN_NET_TOUT        0x1600
#define EVT_LAN_BAD_HSA         0x1700
#define EVT_LAN_BAD_STN         0x1800
#define EVT_LAN_TOK_PASS_ERR    0x1900
#define EVT_LAN_LAS_BAD         0x1a00
#define EVT_LAN_OFFLINE         0x1b00

#define EVT_LAS                 0x2
#define EVT_LAS_ACT_STN_ON      0x2000
#define EVT_LAS_ACT_STN_OFF     0x2100
#define EVT_LAS_PSV_STN_ON      0x2200
#define EVT_LAS_PSV_STN_OFF     0x2300

#define EVT_MAS                 0x3
#define EVT_MAS_RX_DATA_CHG     0x3000
#define EVT_MAS_UPDTE           0x3100
#define EVT_MAS_SCAN_DONE       0x3200
#define EVT_MAS_OK              0x3300
#define EVT_MAS_ERROR           0x3400

#define EVT_SLV                 0x4
#define EVT_SLV_RX_DATA_CHG     0x4000
#define EVT_SLV_UPDTE           0x4100
#define EVT_SLV_OK              0x4200
#define EVT_SLV_ERROR           0x4300
#define EVT_SLV_CHG_TO_RUN      0x4400
#define EVT_SLV_CHG_TO_STOP     0x4500

#define EVT_LY2M                0x5
#define EVT_LY2M_RX_DATA_CHG    0x5000
#define EVT_LY2M_CONFIRM        0x5100
#define EVT_LY2M_ERROR          0x5200
#define EVT_LY2M_BAD_MSG_NUM    0x5300
#define EVT_MC2_CONFIRM         0x5400
#define EVT_MC2_ERROR           0x5500

#define EVT_LY2S                0x6
#define EVT_LY2S_RX_DATA_CHG    0x6000
#define EVT_LY2S_UPDATE         0x6100
#define EVT_LY2S_ERROR          0x6200

#define EVT_FMS					0x7
#define EVT_FMS_CON_CHG			0x7000
#define EVT_FMS_RX_DATA_CHG		0x7100
#define EVT_FMS_UPDATE			0x7200
#define EVT_FMS_ERROR			0x7300

#define EVT_MPI					0x8
#define EVT_MPI_CON_CHG			0x8000
#define EVT_MPI_RX_DATA_CHG		0x8100
#define EVT_MPI_UPDATE			0x8200
#define EVT_MPI_ERROR			0x8300

#define EVT_QUE                 0xf
#define EVT_QUE_OVERUN          0xf000
#define EVT_QUE_BAD_TRIG        0xf100


/* definitions related to pfbTrigQueue */
#define TRG_LAY2M               0x1000
#define TRG_MAS_CLSS2           0x1100
#define TRG_SAP_ACYC_ACK        0x1200
#define TRG_SAP_UPDATE          0x1800
#define TRG_FMS_CRL_OPEN        0x2000
#define TRG_FMS_CRL_INIT        0x2100
#define TRG_FMS_CRL_ABORT       0x2200
#define TRG_FMS_PROC_REQ        0x3000
#define TRG_MPI_PROC_REQ		0x4000

/* definitions related to pfbMasStsTab */
#define MAS_STS_TAB_OK          0x8000  /* current status of slave OK                                       */

/* definitions related to lay2Cntrl */
#define LAY2_CTL_SAP_DIS_LED    0x1000  /* disable status led for layer 2 SAP function                      */
#define LAY2_CTL_MSG_DIS_LED    0x2000  /* disable status led for layer 2 MSG function                      */
#define LAY2_CTL_SAP_ENABLE     0x4000  /* enable PFB Layer 2 SAP service                                   */
#define LAY2_CTL_MSG_ENABLE     0x8000  /* enable PFB Layer 2 Message service                               */

/* definitions related to lay2Status */
#define LAY2_STS_ALL_SAP_OK      0x4000 /* all configured layer 2 saps are ok                               */
#define LAY2_STS_ALL_MSG_OK      0x8000 /* all configured layer 2 messages are ok                           */

/* definitions related to mc2CntCfg */
#define MC2_CTL_UNCONF          0x01
#define MC2_CTL_HI_PRI          0x04
#define MC2_CTL_EVT_CONFIRM     0x20  /* generate event (intr) when this message is confirmed             */

/* definitions related to mc2State */
#define MC2_STE_DISABLE         0x00
#define MC2_STE_BUSY            0x01
#define MC2_STE_ENABLE          0x02
#define MC2_STE_ACTIVE          0x03
#define MC2_STE_DONE            0xff

/* definitions related to mc2Status */
#define MC2_STS_OK              0x80

/* definitions related to mc2Error */
#define MC2_ERR_NOT_OK          0x01
#define MC2_ERR_RX_LEN          0x02
#define MC2_ERR_TX_LEN          0x03
#define MC2_ERR_POLL_TOUT       0x04

/* definitions related to mc2Event */
#define MC2_EVT_CONFIRM         0x01



/* DP Master control structure */
typedef struct tagMAS_CNTRL
{
    volatile uchr  masStn;          /* 00 station address of slave                                          */

    volatile uchr  masCntCfg;       /* 01 Control and configuration register                                */
    volatile uchr  masStatus;       /* 02 Status Register (Host only Reads)                                 */
    volatile uchr  masError;        /* 03 Error indication                                                  */
    volatile uchr  masEvent;        /* 04 Event Flags                                                       */
    volatile uchr  masDiagEvent;    /* 05 Diagnostic Event Flags                                            */

    volatile uchr  masParmLen;      /* 06 Parameters to slave length in bytes                               */
    volatile uchr  masChkLen;       /* 07 Configuration check to slave length in bytes                      */

    volatile ushrt masRxDataOfs;    /* 08 Data received from slave offset within memory page                */
    volatile ushrt masTxDataOfs;    /* 0a Data to be sent to slave offset within memory page                */

    volatile uchr  masRxDataLen;    /* 0c Data received from slave length in bytes                          */
    volatile uchr  masTxDataLen;    /* 0d Data to be sent to slave length in bytes                          */

    volatile uchr  masSiemType;     /* 0e Siemens Device Type                                               */

             uchr  masExtErrInfo;   /* 0f Extended error info                                               */

             char  masDesig[13];    /* 10-1c slave designation (text)                                       */

             uchr  Res2[1];         /* 1d Reserved, DO NOT USE                                              */

    volatile uchr  masDiagMaxLen;   /* 1e Maximum length of diag status response                            */
    volatile uchr  masDiagLen;      /* 1f Diagnostic from slave length in bytes                             */

    volatile uchr  masDiagSts1;     /* 20 status byte 1 from slave                                          */
    volatile uchr  masDiagSts2;     /* 21 status byte 2 from slave                                          */
    volatile uchr  masDiagSts3;     /* 22 status byte 3 from slave                                          */
    volatile uchr  masDiagMasStn;   /* 23 Station that configured Slave                                     */
    volatile uchr  masDiagID_hi;    /* 24 ID hi byte sent back from slave                                   */
    volatile uchr  masDiagID_lo;    /* 25 ID lo byte sent back from slave                                   */
    volatile uchr  masDiagData[24]; /* 26-3d vendor defined diagnostic info from slave                      */
    volatile ushrt masDiagExtOfs;   /* 3e offset within extension area if greater than 26 bytes             */

    volatile uchr  masParmMasSts;   /* 40 status byte to slave                                              */
    volatile uchr  masParmWdFact1;  /* 41 Watchdog factor 1 to slave                                        */
    volatile uchr  masParmWdFact2;  /* 42 Watchdog factor 2 to slave                                        */
    volatile uchr  masParmRdyTme;   /* 43 Response delay time (tbit) to slave                               */
    volatile uchr  masParmID_hi;    /* 44 ID value to slave hi                                              */
    volatile uchr  masParmID_lo;    /* 45 ID value to slave lo                                              */
    volatile uchr  masParmGrpId;    /* 46 Group ID value for slave (not supported, always 0)                */
    volatile uchr  masParmData[23]; /* 47-5d parameters to slave                                            */
    volatile ushrt masParmExtOfs;   /* 5e offset within extension area if greater than 25 bytes             */

    volatile uchr  masChkData[30];  /* 60-7d Configuration check values to slave                            */
    volatile ushrt masChkDataExtOfs;/* 7e offset within extension area if greater than 32 bytes             */
} MAS_CNTRL;

/* definitions related to masCntCfg */
#define MAS_CTL_IGNORE_STS              0x01  /* ignore status of this master block                         */
#define MAS_CTL_EVT_RX_CHG              0x02  /* generate event (intr) when rx data from slave changes      */
#define MAS_CTL_RX_BYTE_SWAP            0x04
#define MAS_CTL_EVT_UPDTE               0x08  /* generate event (intr) when slave update is complete        */
#define MAS_CTL_FAIL_SAFE               0x10  /* slave is a fail safe slave                                 */
#define MAS_CTL_TX_BYTE_SWAP            0x40  /* reserved */
#define MAS_CTL_ENABLE                  0x80

/* definitions related to masStatus */
#define MAS_STS_OK                      0x80  /* current status of this master block is OK                  */

/* definitions related to masError */
#define MAS_ERR_CFG_FAILURE             0x01  /* failure while trying to configure slave                    */
#define MAS_ERR_SLV_ID_MISMATCH         0x02  /* slave real ID does not match slave's configured ID         */
#define MAS_ERR_DATA_UPD_FAILURE        0x03  /* frame delivery problem while updating slave data           */
#define MAS_ERR_CFG_DIAG_READ_FAILURE   0x04  /* frame delivery problem while reading slave diags           */
#define MAS_ERR_CFG_DIAG_STS1_ERR       0x05  /* error in diagnostic status byte #1 during configure        */
#define MAS_ERR_CFG_DIAG_STS2_ERR       0x06  /* error in diagnostic status byte #2 during configure        */
#define MAS_ERR_UPD_DIAG_STS1_ERR       0x07  /* error in diagnostic status byte #1 during diag read        */
#define MAS_ERR_UPD_DIAG_STS2_ERR       0x08  /* error in diagnostic status byte #2 during diag read        */
#define MAS_ERR_CFG_STN_MISMATCH        0x09  /* station address from diag read does not match              */
#define MAS_ERR_IO_CYC_TOUT             0x0a  /* timeout waiting for i/o update                             */
#define MAS_ERR_SLV_WD_OFF              0x0b  /* **warning slave watchdog is not enabled                    */

/* definitions related to masEvent */
#define MAS_EVT_UPD                     0x01  /* slave has been updated                                     */
#define MAS_EVT_RX_DATA_CHG             0x02  /* rx data has changed                                        */

/* definitions related to masDiagEvent */
#define MAS_DEVT_DIAG_UPD               0x01  /* slave diagnostics have been updated                        */

/* definitions related to masSiemType */
#define MAS_SIEM_TYP_OLD_DP             0x80

#ifdef __I960_CODE__
#pragma pack    0
#pragma align   0
#endif

#endif 											/* _H__PROFICTL */