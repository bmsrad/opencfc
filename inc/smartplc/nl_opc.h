/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Di, 13 Apr  99                                                                */
/*                                                                               */
/* DESCRIPTION:  Definitionsfile fuer Netzwerkschicht (Kommunikation zu OPC)     */
/* 05.10.2006    hle                                                             */
/*********************************************************************************/

#ifndef _NL_OPC_H_
#define _NL_OPC_H_


#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* FUNCTION: NetInitializeOPC                                                  */
/* DESCRIPT: This function is called to initialize the communication interface*/
/*                                                                              */           
/* CALLED: Runtime System -> LzsEnvInitialize and LzsRestartNetAndSetNetError */
/*                                                                            */
/*----------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE  LZSPUBLIC  NetInitializeOPC (LZSBYTE bConnectionId_p, 
                                                  LZSBYTE bInitMode_p, 
                                                  LZSBYTE LZSFAR* pInitData_p);

/*------------------------------------------------------------------------------*/
/* FUNCTION: NetShutDownOPC                                                        */
/* DESCRIPT: This function is called to close all open connections to           */
/*           OPC-Servers                                                        */
/* CALLED:  RuntimeSystem -> LzsEnvShutDown    and LzsRestartNetAndSetNetError        */
/*                                                                                */
/*------------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE  LZSPUBLIC NetShutDownOPC (LZSBYTE bConnectionId_p,
                                               LZSBYTE bDownMode_p);

/*------------------------------------------------------------------------------*/
/* FUNCTION: NetRecDataOPC                                                        */
/* DESCRIPT: Function to initialize the receiving of data of specified          */
/*           connection. This routine should not receive the data itself,       */
/*           but tell the receiver where to put the recieved data                */                              
/* CALLED:                                                                      */
/*------------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE  LZSPUBLIC NetRecDataOPC (LZSBYTE bConnectionId_p, LZSBYTE LZSFAR* pData_p, 
                                                LZSDWORD dwRecDataSize_p, LZSDWORD dwRxTimeOut_p);

/*------------------------------------------------------------------------------*/
/* FUNCTION: NetGetRxStatusOPC                                                    */
/* DESCRIPT: This function looks for received data of specified connection.     */
/*           When there is valid data in the buffer ( NetRecDataOPC ) the state */
/*           is NET_SUCCESS                                                        */
/* CALLED:                                                                         */
/*------------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE  LZSPUBLIC NetGetRxStatusOPC (LZSBYTE bConnectionId_p);


/*------------------------------------------------------------------------------*/
/* FUNCTION: NetSendDataOPC                                                        */
/* DESCRIPT: function to transmit a number of bytes to the specified connection    */
/* CALLED:                                                                         */
/*------------------------------------------------------------------------------*/
LZSPUBLIC32 LZSBYTE  LZSPUBLIC   NetSendDataOPC (LZSBYTE bConnectionId_p, LZSBYTE LZSFAR* pData_p, LZSWORD wDataSize_p,
                           LZSBYTE bDataType_p, LZSDWORD dTxTimeOut_p);

#ifdef __cplusplus
}
#endif



#endif  /* _NL_OPC_H_*/
