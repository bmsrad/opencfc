/*****************************************************************************
 *    (c) 2006 infoteam Software GmbH
 *    infoteam Software GmbH, Am Bauhof 9, 91088 Bubenreuth, Germany
 *    Tel. +49-9131-7800-0   EMail info@infoteam.de
 *****************************************************************************/

#ifndef __LZSEXTCTRLPROTOCOL_H_
#define __LZSEXTCTRLPROTOCOL_H_

/* generic handler for parsing ExtCtrl messages  */

typedef enum { /* type of message */
  kMsgRead,
  kMsgWrite,
  kMsgCommand,

  kMsgReadResponse,
  kMsgWriteResponse,
  kMsgCommandResponse,

  kMsgLast  /* dummy, dont use this one */

} eMsg;

typedef enum { /* result of ReadMsg() */
  eOk = 1,
  eErrorCom,
  eErrorProtocol,
  eErrorChecksum
} eResult;

typedef enum { /* command ids as passed into MsgDataCallbackCommand */
  kCmdStop,
  kCmdColdStart,
  kCmdHotStart,

  kCmdLast,    /* dummy, dont use this one */
  kCmdInvalid
} eCommand;



/*
ReadMsg will read in and verify a message, it will call several handlers to
pass the messages data to the application.
ReadMsg() returns the encountered message id through its nMsg_p parameter 
and the parsing result as return value. 

Handlers required by ReadMsg():

int ReadChar(unsigned char *p); 
  - read a single character from input stream. returns 0 on error or eof

Handlers for READ, WRITE and READ/WRITE-RESPONSE messages

void MsgDataCallbackBegin(int fIsWrite);
  - This function is called once at the beginning of a message.
    fIsWrite indicates that AddVariable will receive (name,value) pairs.
    It is false on READ messages only.

void MsgDataCallbackAddVariable(const char *pVarName, const char *pValue);
  - For each line in a messages body, AddVariable will receive the separated
    strings.     
    Basically (name,value) pairs are stored here somewhere and then later handled,
    when ReadMsg() returns.

void MsgDataCallbackEnd(int fSuccess);
  - at the end of the message body this function is called. 


void MsgDataCallbackCommand(eCommand nCmd);
  - Call when parsing a COMMAND message.
    nCmd is the requested command's id.
*/
extern eResult ReadMsg(eMsg *nMsg_p);

extern void ReadMsgInit(void);
extern void ReadMsgShutdown(void);

/* convert a command id to a human readable name */
extern const char *CommandIdToName(eCommand nCmd);

#endif
