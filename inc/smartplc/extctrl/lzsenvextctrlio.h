/******************************************************************************
 *  (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 *  DESCRIPTION:    extern control I/O functions, LZS side
 *  
 *****************************************************************************/

#ifndef _LZSENVEXTCTRLIO_H_
#define _LZSENVEXTCTRLIO_H_

#include "oem/config.h"
#include "oem/datatype.h"
#include "smartplc/odk_bas.h"
#include "smartplc/lzstypes.h"

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvReportErrorString                          */
/* DESCRIPT: error logging; printf-style calling                              */
/*----------------------------------------------------------------------------*/
void LzsEnvReportErrorString(LZSCHAR LZSFAR *pszFormatString, ...);

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvExtCtrlIOInitialize                          */
/* DESCRIPT: initialize IO functionality                          */
/* CALLED: once on startup                                                    */
/* RETURNS: LZSTRUE if initialization was completed successfully. LZSFALSE on error  */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvExtCtrlIOInitialize(void);

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvExtCtrlIOShutdown                          */
/* DESCRIPT: free any resources allocated in LzsEnvExtCtrlIOInitialize        */
/* CALLED: once on shutdown                                                   */
/*----------------------------------------------------------------------------*/
void LzsEnvExtCtrlIOShutdown(void);

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvExtCtrlIOShutdownRequest                      */
/* DESCRIPT: async shutdown notification.                                     */
/* CALLED: once, before LzsEnvExtCtrlIOShutdown gets called                   */
/*----------------------------------------------------------------------------*/
void LzsEnvExtCtrlIOShutdownRequest(void);

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvExtCtrlIOOpenConnection                      */
/* DESCRIPT: open a new connection.                                           */
/* RETURNS: LZSTRUE if connection was opened successfully. LZSFALSE on error  */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvExtCtrlIOOpenConnection(void);

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvExtCtrlIOCloseConnection                      */
/* DESCRIPT: close an open connection.                                        */
/* CALLED: if a communication error occurs, the connection needs to be reset. 
   For this, the connection is closed and a new connection is opened. This 
   is done, so that the client on the other end of the connection can detect 
   the reset.                                                                 */
/*----------------------------------------------------------------------------*/
void LzsEnvExtCtrlIOCloseConnection(void);

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvExtCtrlIOWrite                              */
/* DESCRIPT: send the passed data buffer over the opened connection.          */
/* RETURNS: LZSTRUE, if data was sent. LZSFALSE on error                      */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvExtCtrlIOWrite(LZSCONST LZSBYTE *pData_p, LZSDWORD dwSize_p);

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvExtCtrlIODataAvailable                      */
/* DESCRIPT: checks if incoming data is available for reading via 
             LzsEnvExtCtrlIOReadByte()                                        */
/* RETURNS:
     1, if data is available
     0, if no data is availble
    -1, on error                                                              */
/*----------------------------------------------------------------------------*/
int LzsEnvExtCtrlIODataAvailable(LZSDWORD dwTimeoutSec, LZSDWORD dwTimeoutUSec);

/*----------------------------------------------------------------------------*/
/* FUNCTION: LzsEnvExtCtrlIOReadByte                              */
/* DESCRIPT: reads a single byte from the opened connection.                  */
/* RETURNS: LZSTRUE, if a byte was read. LZSFALSE on error                    */
/*----------------------------------------------------------------------------*/
LZSBOOL LzsEnvExtCtrlIOReadByte(LZSBYTE *pbResult_p);

#endif
