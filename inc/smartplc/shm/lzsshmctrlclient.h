/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: shared memory data-exchange / control interface 
 *                (RTS control; client side)
 *  
 *****************************************************************************/

#ifndef _LZSSHMCTRLCLIENT_H_
#define _LZSSHMCTRLCLIENT_H_ 

#ifdef __cplusplus
extern "C"{
#endif

#include "oem/odk_prj.h"
#include "smartplc/shm/lzsshmstructs.h"

/***************************************************************************
* GENERAL PREFACE
****************************************************************************
* This library contains access logic for the shared memory between the
* SmartPLC/OPC runtime system and the user interface.
*
* The structure of the shared memory is defined by a C struct in file
* \inc\smartplc\sharedmemui.h
* Each function in this library takes a pointer to this global shared
* memory ares as its first parameter.
*
* The library is implemented for the SmartPLC/OPC runtime system with 
* account for a later SmartPLC/RTX port. So, no operation system depended
* code is used for implementation.
* NOTE: Because of the OS independency, the synchronisation of access has 
* to be handled outside the library using OS mechanisms like mutexes or 
* semaphores. 
****************************************************************************/

/***************************************************************************
* Global defines used by this library
****************************************************************************/
#define SMARTPLC_CMD_HANDSHAKE_EMPTY 0
#define SMARTPLC_CMD_HANDSHAKE_PENDING 1
#define SMARTPLC_CMD_HANDSHAKE_COMPLETE_SUCCESS 2
#define SMARTPLC_CMD_HANDSHAKE_COMPLETE_FAILURE 3

#define SMARTPLC_CMD_COLDSTART        0
#define SMARTPLC_CMD_HOTSTART        1    /* was _RUN before */
#define SMARTPLC_CMD_STOP            2
#define SMARTPLC_CMD_RESET            3
#define SMARTPLC_CMD_ERASE            4
#define SMARTPLC_CMD_SET_PROGRAM_MODE        5
#define SMARTPLC_CMD_CLEAR_PROGRAM_MODE        6

/***************************************************************************
* Functions for reading from and writing to the message circular buffer
****************************************************************************
* These function provide access to the message circular buffer in a
* controlled way. Two main actions are allowed:
* - Read a single message from the buffer
* - Write a single message to the buffer
* Write access is always allowed, since writing to a full buffer results
* in overwriting the oldest message in the buffer.
* Read access fails, if there is no more message to read, i.e. the buffer
* is empty. A read access consumes the message, that means it is removed
* from the buffer.
****************************************************************************/

/* tests if there is a message pending in the buffer */
LZSBOOL SmartPlcUiIsMessagePending(tShmCtrl* pSharedMem);

/* reads the oldest available message from the buffer */
/* returns FALSE, if buffer is empty                                    */
/* results are only valid on return value == TRUE            */
LZSBOOL SmartPlcUiReadActualMessage(tShmCtrl* pSharedMem,
    LZSSHMTSTAMP* plwTimeStamp,LZSSHMCHAR* psMessage, LZSDWORD bufLen);

/* writes a new message to the buffer, potentially overwriting the oldest one */
/*  in the buffer */
void SmartPlcUiWriteNewMessage(tShmCtrl* pSharedMem, LZSSHMTSTAMP lwTimeStamp, LZSCONST LZSSHMCHAR* psMessage);

/***************************************************************************
* Command handling functions
****************************************************************************
* Useful functions for command handling between user interface and RTS
* The user interface can use the following functions:
*    SmartPlcUiIssueCommand
*    SmartPlcUiTestCmdCompletion
* For the use cases of the RTS there are two other functions:
*    SmartPlcUiIsCmdPending
*    SmartPlcUiSetCmdFinished
***************************************************************************/

/* Issue new command towards the runtime system */
/* This might not be successfull, if there is already a command pending for */
/* execution or the result of the previous command was not queried yet. */
/* result: 0 means success, !=0 means issuing command not possible, the value */
/*  indicates the reason: */
/*  SMARTPLC_CMD_HANDSHAKE_PENDING: the previous command is still waiting for execution */
/*    SMARTPLC_CMD_HANDSHAKE_COMPLETE_SUCCESS or */
/*  SMARTPLC_CMD_HANDSHAKE_COMPLETE_FAILURE: last result was not queried yet */
/* Call SmartPlcUiTestCmdCompletion in the latter case to query the result */
LZSWORD SmartPlcUiIssueCommand(tShmCtrl* pSharedMem,LZSWORD Cmd);

/* Queries the result of the previously issued command */
/* Provide a LZSDWORD pointer to pdwCmdResult to get additional result information */
/* The result may be one of the following values: */
/*    SMARTPLC_CMD_HANDSHAKE_EMPTY: no command was issed before */
/*    SMARTPLC_CMD_HANDSHAKE_PENDING: command execution not completed yet */
/*    SMARTPLC_CMD_HANDSHAKE_COMPLETE_SUCCESS: command successfully completed */
/*    SMARTPLC_CMD_HANDSHAKE_COMPLETE_FAILURE: command not executed */
/* In the latter two cases the command handshake is set to empty at the same time */
LZSWORD SmartPlcUiTestCmdCompletion(tShmCtrl* pSharedMem, LZSDWORD* pdwCmdResult /*=NULL*/);

/* Tests, if a command from the user interface is pending */
/* Returns TRUE, if a command is pending, otherwise FALSE */
/* When a LZSWORD pointer is provided for pwCmd, the command value is also returned. */
LZSBOOL SmartPlcUiIsCmdPending(tShmCtrl* pSharedMem, LZSWORD* pwCmd /*= NULL*/);

/* Allows the runtime system to set the response of a received command. */
/* dwCmdResult is for additional result information. */
/* with success==TRUE you signal that the command execution was successfull, */
/* success==FALSE means that the command was received but not executed (e.g. due to */
/* an unknown command code or an error) */
void SmartPlcUiSetCmdFinished(tShmCtrl* pSharedMem,LZSDWORD dwCmdResult /*=0*/, LZSBOOL success /*= true*/);

/* Set used mem in shared memory */
void SmartPlcUiWriteMemInfo(tShmCtrl* pSharedMem, LZSDWORD dwMemInfo, LZSDWORD dwMaxMem);

/* Checks, if a valid program is loaded */
LZSBOOL SmartPlcUiIsPgmLoaded(tShmCtrl* pSharedMem);

/* Returns the segment-length of the shared memory. */
LZSDWORD GetSegmentLen(void * pSharedMem);

/* Copies the shared memory from source to destination */
LZSBOOL CopySharedMem(void * pDestSharedMem, void * pSourceSharedMem);

/* writes a new debug-message, potentially overwriting the oldest one  */
/* in the buffer */
void SmartPlcWriteNewDebugMessage(tShmDebug* pSharedMem,
    LZSSHMTSTAMP lwTimeStamp,LZSCONST LZSSHMCHAR* psMessage, LZSBYTE bMsgLevel);
    
/* tests if there is a message pending in the buffer */
LZSBOOL SmartPlcIsDebugMessagePending(tShmDebug* pSharedMem);

/* reads the oldest available message from the buffer */
/* returns FALSE, if buffer is empty */
/* results are only valid on return value == TRUE */
LZSBOOL SmartPlcReadActualDebugMessage(tShmDebug* pSharedMem,
    LZSSHMTSTAMP* plwTimeStamp,LZSSHMCHAR* psMessage, LZSDWORD bufLen, LZSBYTE* pbDebugLevel, LZSDWORD* pdwNumber);

/* write new debug message into the shared memory for debug */
LZSBOOL SmartPlcShmWriteDebugMessage(tShmDebug* pSharedMemory2Debug, LZSCONST LZSSHMCHAR* psMessage, LZSBYTE bMsgLevel);

#ifdef __cplusplus
};
#endif

#endif

