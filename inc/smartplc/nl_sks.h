/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Di, 13 Apr  99                                                                 */
/*                                                                               */
/* DESCRIPTION:  Definitionsfile fuer SKS-Netzwerkschicht
   15.04.1997   -rs                                                              */
/*********************************************************************************/

#ifndef _NL_SKS_H_
#define _NL_SKS_H_


/*---------------------------------------------------------------------------*/
/*  Definition of constants*/
/*---------------------------------------------------------------------------*/

/* Definition of initialization modes*/
#define NET_COLDSTART       0x00        /* Init after system coldstart*/
#define NET_WARMSTART       0x01        /* Init after system warmstart*/
#define NET_ERROR_INIT      0x02        /* Init after network crash*/

/* The option <NET_RAW_MODE> has to be linked as optional flag to one of the */
/* initialization modes listed above (mode OR flag) and suppresses*/
/* additional safety mechanisms, like e.g internal Header-Frames for */
/* "knot arrangements" used by the SP3964R */
#define NET_RAW_MODE        0x80        /* no safety mechanisms*/

/* The option <NET_NO_HW_INIT> has to be linked as optional flag to one of the */
/* initialization modes listed above (mode OR flag) and suppresses the initialization*/
/* of the hardware, because e.g. not to influence the serial interface of the SP3964R,  */
/* initialized by the automatic baudrate detection of the C167 bootstrap-loader */
#define NET_NO_HW_INIT      0x40        /* no interface initialization */


/* Definition of shutdown modes*/
#define NET_SHUTDOWN        0xFF        /* shutdown network layer*/
#define NET_ERROR_DOWN      0xFE        /* shutdown after network crash*/


/* Definition of times*/
#define NET_RxTIMEOUT       5000        /* TimeOut for reception of data*/
#define NET_TxTIMEOUT       5000        /* TimeOut for sending data*/
#define NET_RECTIMEOUT      5000        /* TimeOut for reception of receipts*/


/* Definition of "TxTypes"*/
#define NET_CMD             0x01        /* DataType "COMMAND"*/
#define NET_DATA            0x02        /* DataType "DATA"*/
#define NET_REC             0x03        /* DataType "RECEIPT"*/
#ifdef _LZS_PMAC_
#define NET_PMAC_SAVE        0x04
#endif


/* Definition of Errorcodes*/
#define NET_SUCCESS         0x00        /* OK, Data available*/
#define NET_NO_LICENCE      0xFF        /* Network not lizensed*/
#define NET_LOCKED          0xFE        /* Network not enabled (yet)*/
#define NET_NODATA          0xFD        /* wait for data reception*/
#define NET_RX_SUCCESS      0xFC        /* data received successfull */
#define NET_TX_SUCCESS      0xFB        /* data sent successfull */
#define NET_ERROR           0xFA        /* general network error */
#define NET_TIMEOUT         0xF9        /* TimeOut while waiting for reception */
#define NET_INTDATA_ERROR   0xF8        /* Error in internal stack data */
#define NET_BUFFER_ERROR    0xF7        /* invalid receive buffer */
#define NET_RX_OVRFLW       0xF6        /* receive buffer too small */
#define NET_BAD_CRC         0xF5        /* CRC wrong */
#define NET_HW_ERROR        0xF4        /* Hardwareerror (Initialization) */
#define NET_INVALID_MODE    0xF3        /* invalid Init-/Shutdown-Mode */
#define NET_NETVAR_ERROR    0xF2        /* Error at creation of netvar. */
#define NET_BUS_OFF         0xF1        /* CAN Bus OFF */
#define NET_TX_OVRFLW       0xF0        /* send buffer too small */
#define NET_INVALID_PACKED  0xEF        /* wrong packet type */
#define NET_RESTART_COMM    0xEE        /* reset of network layer (e.g. CANopen-command "ResetNode" or "ResetCommunication") */


#define NET_RX_ERROR        NET_ERROR
#define NET_TX_ERROR        NET_ERROR
#define NET_RX_TIMEOUT      NET_TIMEOUT
#define NET_TX_TIMEOUT      NET_TIMEOUT
#define NET_ACK             0x00        /* positive receipt*/
#define NET_NACK            0xFF        /* negative receipt*/



#ifdef __cplusplus
extern "C" {
#endif

/* ==============================================================*/
/* Network interface functions*/
/* comment:   every network layer has to offer the network services
 *                ( PC and SPS part ). The configuration functions are optional
 *                and will only be used on the PC side ( DLL )
 *                
 *                the meaning of the configuration functions is as follows: 
 */
/* ==============================================================*/


/*----------------------------------------------------------------------------*/
/* FUNCTION: NetInitialize                                                    */
/* DESCRIPT: This function is called to initialize the communication interface*/
/*                                                                            */           
/* CALLED: Runtime System -> LzsEnvInitialize and LzsRestartNetAndSetNetError */
/*         SKS -> SksStart and SksReInit                                      */
/*----------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE LZSPUBLIC NetInitialize(LZSBYTE bInitMode_p,        /*[i] init mode*/
                                            LZSBYTE LZSFAR* pInitData_p, /*[o] information for sks (in plc not used)*/
                                            int nSlotNumber);

/*------------------------------------------------------------------------------*/
/* FUNCTION: NetShutDown                                                        */
/* DESCRIPT: This function is called to close the communication interface       */
/* CALLED:  RuntimeSystem -> LzsEnvShutDown    and LzsRestartNetAndSetNetError  */
/*          SKS           -> ~CSks, SksReInit and when an error occures on login*/
/*------------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE LZSPUBLIC NetShutDown(LZSBYTE bDownMode_p, /*[i] shutdown mode*/
                                          int nSlotNumber      /*[i] slot number for proxy*/
                                         );

/*------------------------------------------------------------------------------*/
/* FUNCTION: NetSendData                                                        */
/* DESCRIPT: function to transmit a number of bytes to the target               */
/* CALLED:                                                                      */
/*------------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE LZSPUBLIC NetSendData(LZSBYTE LZSFAR* pData_p, /*[i] pointer to the data that should be sent*/
                                          LZSWORD wDataSize_p,     /*[i] number of bytes to be sent*/
                                          LZSBYTE bDataType_p,     /*[i] kind of date :NET_CMD, NET_DATA, NET_REC*/
                                          LZSDWORD dTxTimeOut_p,   /*[i] timeout value for sending data*/
                                          int nSlotNumber          /*[i] slot number for proxy*/
                                         );

/*------------------------------------------------------------------------------*/
/* FUNCTION: NetRecData                                                         */
/* DESCRIPT: function to make the receiving of data possible. This routine      */
/*             should not receive the data itself, but tell the receiver where  */
/*             to put the recieved data                                         */
/* CALLED:                                                                      */
/*------------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE LZSPUBLIC NetRecData(LZSBYTE LZSFAR* pData_p, /*[i] pointer where the received data should be stored*/
                                         LZSDWORD dwDataSize_p,   /*[i] maximum size of data the buffer could store*/
                                         LZSBYTE bDataType_p,     /*[i] kind of data that is expected*/
                                         LZSDWORD dRxTimeOut_p,   /*[i] timeout for receiving data*/
                                         int nSlotNumber          /*[i] slot number for proxy*/
                                         #ifdef _LZS_DSALIGNMENT_DSP563_
                                         ,LZSBOOL fRec6ByteLayoutSegment_p /*[i] Expecting a 6Byte layout segment, align incoming data right away*/
                                         #endif
                                        );

/*------------------------------------------------------------------------------*/
/* FUNCTION: NetGetRxStatus                                                     */
/* DESCRIPT: this function looks for received data. When there is valid data in */
/*             the buffer ( NetRecData ) the state is NET_SUCCESS               */
/* CALLED:                                                                      */
/*------------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE LZSPUBLIC NetGetRxStatus(int nSlotNumber);

/*------------------------------------------------------------------------------*/
/* FUNCTION: NetRestartRxTimeOut                                                */
/* DESCRIPT: This function sets the timeout value for NetGetRxStatus. Reaching  */
/*             the timeout causes NetGetRxStatus to return with NET_TIMEOUT     */
/* CALLED:                                                                      */
/*------------------------------------------------------------------------------*/
LZSPUBLIC32 void  LZSPUBLIC  NetRestartRxTimeOut (LZSDWORD dRxTimeOut_p);

/*------------------------------------------------------------------------------*/
/* [SYSTEC: 30.04.2003 -rs]: Extension to non-blocking network functions        */
/*------------------------------------------------------------------------------*/
/* FUNCTION: NetSendStart                                                       */
/* DESCRIPT: function to start transmission of a number of bytes to the target  */
/*           non-blocking version version of <NetSendData>                      */
/* CALLED:                                                                      */
/*------------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE LZSPUBLIC NetSendStart(LZSBYTE LZSFAR* pData_p, /*[i] pointer to the data that should be sent*/
                                           LZSWORD wDataSize_p,     /*[i] number of bytes to be sent*/
                                           LZSBYTE bDataType_p,     /*[i] kind of date :NET_CMD, NET_DATA, NET_REC*/
                                           LZSDWORD dTxTimeOut_p    /*[i] timeout value for sending data*/
                                          );

/*------------------------------------------------------------------------------*/
/* [SYSTEC: 30.04.2003 -rs]: Extension to non-blocking network functions        */
/*------------------------------------------------------------------------------*/
/* FUNCTION: NetGetStatus                                                       */
/* DESCRIPT: This function looks for the state of transmitted and received      */
/*           data. When there is valid data in the buffer ( NetRecData )        */
/*           the state is NET_RX_SUCCESS                                        */
/* CALLED:                                                                      */
/*------------------------------------------------------------------------------*/
LZSPUBLIC32  LZSBYTE  LZSPUBLIC  NetGetStatus (void);

/* ==============================================================*/
/* Network interface functions from the PLC Side*/
/* this functions are the same as the net functions above*/
/* ==============================================================*/
LZSPUBLIC32 LZSBYTE LZSPUBLIC PlcNetInitialize(LZSBYTE bInitMode_p, LZSBYTE LZSFAR* pInitData_p);
LZSPUBLIC32 LZSBYTE LZSPUBLIC PlcNetShutDown(LZSBYTE bDownMode_p);
LZSPUBLIC32 LZSBYTE LZSPUBLIC PlcNetSendData(LZSBYTE LZSFAR* pData_p, LZSWORD wDataSize_p, LZSBYTE bDataType_p, LZSDWORD dTxTimeOut_p);
LZSPUBLIC32 LZSBYTE LZSPUBLIC PlcNetRecData(LZSBYTE LZSFAR* pData_p, LZSDWORD dwDataSize_p, LZSBYTE bDataType_p, LZSDWORD dRxTimeOut_p);
LZSPUBLIC32 LZSBYTE LZSPUBLIC PlcNetGetRxStatus(void);
LZSPUBLIC32 void LZSPUBLIC PlcNetRestartRxTimeOut(LZSDWORD dRxTimeOut_p);

/*-------------------------------------------------------------------------------*/
/* FUNCTION: NetSelectParams                                                     */
/* DESCRIPT: This function is called once after loading the                      */
/*            DLL ( and before calling < NetInitialize> ! ).                     */
/*            It tells the DLL the path of the INI file and the                  */
/*            name of the section. By doing this the properties,                 */
/*            set by <NetSelectNode> and <NetSelectProperty>, can                */
/*            be analysed and processed by the init function                     */
/*            (<NetInitialize>).                                                 */
/*    One can call the function <NetSelectParams> without calling <NetSelectNode>*/
/*    and <NetSelectProperty> before, so that <NetSelectParams> may not find any */
/*    entries in the INI file. In that case the function <NetSelectParams> either*/
/*    should generate an error message or should serve standard values           */
/*                                                                               */
/* CALLED:                                                                       */
/*-------------------------------------------------------------------------------*/
LZSBYTE LZSPUBLIC NetSelectParams(LZSCONST LZSCHAR LZSFAR* pszIniFile_p, LZSCONST LZSCHAR LZSFAR* pszNetName_p);

/*------------------------------------------------------------------------------*/
/* FUNCTION: NetSelectProperty                                                  */
/* DESCRIPT:    This function realizes the network specific part of             */
/*               the communication configurator ( this will be called           */
/*               as a reaction to the property button )                         */
/*                                                                              */
/* CALLED:                                                                      */
/*------------------------------------------------------------------------------*/
LZSBYTE LZSPUBLIC NetSelectProperty(LZSCONST LZSCHAR LZSFAR* pszIniFile_p, LZSCONST LZSCHAR LZSFAR* pszNetName_p);

/*----------------------------------------------------------------------------*/
/* FUNCTION: NetSelectNode                                                    */
/* DESCRIPT: This function realizes the selection of the target node          */
/*           (as reaction to button/menu "select target node")                */
/* CALLED:                                                                    */
/*----------------------------------------------------------------------------*/     
LZSBYTE  LZSPUBLIC  NetSelectNode     (LZSCONST LZSCHAR LZSFAR* pszIniFile_p, LZSCONST LZSCHAR LZSFAR* pszNetName_p);

/*---------------------------------------------------------------------------*/
/*  Definition of function pointers for SKS-DLL                              */
/*---------------------------------------------------------------------------*/
typedef LZSBYTE (LZSPUBLIC *tNetInitialize) (LZSBYTE bInitMode_p,  LZSBYTE LZSFAR* pInitData_p);
typedef LZSBYTE (LZSPUBLIC *tNetShutDown)   (LZSBYTE bDownMode_p);
typedef LZSBYTE (LZSPUBLIC *tNetSendData)   (LZSBYTE LZSFAR* pData_p, LZSWORD wDataSize_p, LZSBYTE bDataType_p, LZSDWORD dTxTimeOut_p);
typedef LZSBYTE (LZSPUBLIC *tNetRecData)    (LZSBYTE LZSFAR* pData_p, LZSDWORD dwDataSize_p, LZSBYTE bDataType_p, LZSDWORD dRxTimeOut_p);
typedef LZSBYTE (LZSPUBLIC *tNetGetRxStatus)(void);
typedef void (LZSPUBLIC *tNetRestartRxTimeOut)(LZSDWORD dRxTimeOut_p);

typedef LZSBYTE (LZSPUBLIC *tNetSelectParams)   (LZSCONST LZSCHAR LZSFAR* pszIniFile_p, LZSCONST LZSCHAR LZSFAR* pszNetName_p);
typedef void (LZSPUBLIC *tNetSelectProperty) (LZSCONST LZSCHAR LZSFAR* pszIniFile_p, LZSCONST LZSCHAR LZSFAR* pszNetName_p);
typedef void (LZSPUBLIC *tNetSelectNode)     (LZSCONST LZSCHAR LZSFAR* pszIniFile_p, LZSCONST LZSCHAR LZSFAR* pszNetName_p);

#ifdef __cplusplus
}
#endif

/* the folowing structure is used only by SKS.DLL and contains the 
 * pointers to functions of the network services. The functions
 * selecting configuration will be linked only when neccessary
 */
typedef struct
{
   tNetInitialize           fpNetInitialize;
   tNetShutDown             fpNetShutDown;
   tNetSendData             fpNetSendData;
   tNetRecData              fpNetRecData;
   tNetGetRxStatus          fpNetGetRxStatus;
   tNetRestartRxTimeOut     fpNetRestartRxTimeOut;

} tNetDll;

/* the following structure should be made in a network DLL. It will
 * be used by SKS.DLL to display network properties and parameters
 * in a message box. When calling the function <NetInitialize> 
 * of a network layer the SKS.DLL will pass the address of a pointer to the
 * struct <tNetInf> (pointer to pointer). Therefore the second parameter
 * of <NetInitialize>, which is defined as <LZSBYTE LZSFAR* pInitData_p>, will be
 * casted to a pointer to a struct-pointer of type <tNetInf>
 * If a network DLL does not support the information structure, the struct pointer
 * ( which is pointed to by the passed pointer ) has to be leaved unchanged.
 * ( this pointer will be initialized as LZSNULL pointer by SKS.DLL )
 */
typedef struct
{
   LZSCHAR LZSFAR*  m_pszNetName;               /* Network-Name (for display)*/
   LZSCHAR LZSFAR*  m_pszNetString;             /* arbitrary string (for display)*/
   LZSWORD       m_wErrors;                  /* number of network errors*/
   LZSWORD       m_wTransferRate;            /* Transmission rate [cps]*/
   LZSDWORD      m_dSessionStartTime;        /* Systemtime at net-start [ms]*/
   LZSDWORD      m_dConnectStartTime;         /* Systemtime at creation of connection [ms]*/

} tNetInf;

/* Struct with segment pointers
 The address of this struct is handed out to the function <NetProcessIoData> as
 parameter <pPList_p> if called while in mode <kPidCreateIoData>.*/
typedef struct
{
    LZSBYTE LZSFAR*   m_pNetImgSegment;       /* Ptr to NetImage-Segment (RTS)*/
    LZSWORD        m_wNetImgSegmentSize;   /* Size NetImage-Segment (RTS)*/
    LZSBYTE LZSFAR*   m_pNetImgCache;         /* Ptr to NetImage-Cache (Netmodul)*/
    LZSWORD        m_wNetImgCacheSize;     /* Size NetImage-Cache (Netmodul)*/
    LZSBYTE LZSFAR*   m_pNetCtlSegment;       /* Ptr to control informat. (z.B. DCF)*/
    LZSWORD        m_wNetCtlSegmentSize;   /* Size control informat. (z.B. DCF)*/

} tNetVarDscrpt;

/* Calling mode of function <NetProcessIoData> for processing of process data*/
typedef enum                  
{                             
    kPidInitCold        =  0,             /* Initialization Coldstart-Mode*/
    kPidInitWarm        =  1,             /* Initialization Warmstart-Mode*/
    kPidReInitNodeCtrl  =  2,             /* Re-Initialization Knot-Control */
    kPidCreateIoData    =  3,             /* Generate network process data*/
    kPidStartIoDataCold =  4,             /* start process data with cold start */ 
    kPidStartIoDataWarm =  5,             /* start process data with Warmstart*/ 
    kPidExchangeIoData  =  6,             /* Evaluation of process data*/    
    kPidStopIoData      =  7,             /* Stop Verarbeitung Prozessdaten*/   
    kPidDestroyIoData   =  8,             /* Verwerfen Netzwerk-Prozessdaten*/  
    kPidErrorHandler    =  9,             /* Reinitialisierung nach Fehler*/    
    kPidShutDown        = 10              /* Beenden Netzwerkkommunikation*/    
                                                                                
} tPioMode;                   
/*---------------------------------------------------------------------------*/
/* Prototypes*/
/*---------------------------------------------------------------------------*/

/* Mode_p:      Mode corresponding <tPioMode>*/
/* pPList_p:    additional calling parameters, depends on mode*/
/* Return:      Errorcode <NET_Xxx> corresponding to NETMODUL.H*/

LZSBYTE       LZSPUBLIC NetProcessIoData    ( tPioMode    Mode_p,
                                       LZSBYTE LZSFAR*   pPList_p );

#endif  /* _NL_SKS_H_*/
