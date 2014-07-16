#ifndef _ERRORLOG_H_
#define _ERRORLOG_H_

/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                */
/*                                                                               */
/* DESCRIPTION:     Interface of error-log                                       */
/*                                                                               */
/*********************************************************************************/

#include "tskScheduler/userConfig.h"

/* ACFAIL and SYSFAIL signals are treated as exceptions; the following "pseudo-vectors" are used instead of error codes to identify them */
#define ACFAIL_VECTOR 0x2000
#define SYSFAIL_VECTOR 0x2100

typedef struct
{
	LZSDWORD dwMagic;
	LZSDWORD dwMagic2;
	
	tPlcMemPtr pErrorLogSegment;       /* pointer to the beginning of the error log segment (header) */
	tPlcMemPtr pNextFreeErrorLogEntry; /* pointer to the next free error log entry */
	LZSBOOL fErrorLogInit;             /* flag showing if error log is initialized */
	tPlcMemPtr pSystemErrorPanel;      /* pointer to the beginning of the system error panel (first field) */

	tPlcMemPtr pExceptionBufferSegment;       /* pointer to the beginning of the exception buffer segment (header) */
	tPlcMemPtr pNextFreeExceptionBufferEntry; /* pointer to the next free exception buffer entry */
	LZSBOOL fExceptionBufferInit;             /* flag showing if exception buffer is initialized */

} tErrorLogControl;

#define SIZEOF_ERRORLOG_CONTROL ((sizeof(tErrorLogControl) + 0x0000003) & ~0x00000003) /* 4-aligned size */

typedef struct
{
    LZSDWORD dwTimestamp_hi;
    LZSDWORD dwTimestamp_lo;
	LZSDWORD dwCategory;
    LZSWORD  wParameter1;
    LZSWORD  wParameter2;
    LZSWORD  wParameter3;
    LZSWORD  wParameter4;

} tErrorLogEntry;

typedef struct
{
    LZSDWORD dwTimestamp_hi;
    LZSDWORD dwTimestamp_lo;
    LZSDWORD dwVector;
	LZSDWORD dwTask;
	LZSCHAR  strLastExecutedFB[32];
	LZSDWORD array_dwRegisters[NUM_REGS_EXCEPTIONBUFFER];

} tExceptionBufferEntry;

typedef struct
{
    LZSWORD wFaultMemory[4];

} tSystemErrorPanelField;

#define ERRORLOG_SEGMENT_SIZE (NUM_ERRORLOG_ENTRIES * sizeof(tErrorLogEntry) + LZS_SIZEOF_DATASEGHDR) /* maximum segment size is 0xFFFF */
#define EXCEPTIONBUFFER_SEGMENT_SIZE (NUM_EXCEPTIONBUFFER_ENTRIES * sizeof(tExceptionBufferEntry) + LZS_SIZEOF_DATASEGHDR) /* maximum segment size is 0xFFFF */
#define SYSTEMERRORPANEL_SIZE (NUM_ERROR_CATEGORIES * sizeof(tSystemErrorPanelField) + LZS_SIZEOF_DATASEGHDR) /* maximum segment size is 0xFFFF */

#ifdef _LZS_ERROR_LOG
/* interface of error log */
LZSBYTE LzsErrlogInitErrorlog(void);
tErrorLogEntry* LzsErrlogWriteErrorlog(LZSDWORD dwCategory, LZSWORD wParameter1, LZSWORD wParameter2, LZSWORD wParameter3, LZSWORD wParameter4);
LZSBYTE LzsErrlogRegisterError(LZSDWORD dwCategory, LZSWORD wParameter1, LZSWORD wParameter2, LZSWORD wParameter3, LZSWORD wParameter4);

/* interface of system error panel */
LZSBYTE LzsErrlogSetSysErrPanel(LZSDWORD dwCategory, LZSWORD wErrorCode);
LZSWORD LzsErrlogGetSysErrPanel(LZSDWORD dwNo, LZSWORD wIndex);
LZSBYTE LzsErrlogClearSysErrPanel(LZSDWORD dwNo, LZSWORD wNumWords);

/* clear functions */
LZSBYTE LzsErrlogClearErrorLog();
LZSBYTE LzsErrlogClearSystemErrorPanel();
#endif

#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
/* interface of exception buffer */
LZSBYTE LzsErrlogInitExceptionBuffer(void);
tExceptionBufferEntry* LzsErrlogWriteException(LZSDWORD dwVector, LZSDWORD dwTask, LZSCHAR* strLastExecutedFB, LZSDWORD* pRegs, LZSWORD wNumRegs);
LZSBYTE LzsErrlogRegisterException(LZSDWORD dwVector, LZSDWORD* pRegs, LZSWORD wNumRegs);
LZSBYTE LzsErrlogGetLastExecutedInstanceName(LZSCHAR LZSFAR* szPath, LZSWORD wLen);

/* clear function */
LZSBYTE LzsErrlogClearExceptionBuffer();
#endif

void LzsErrWriteFlash(void);

#define ERROR_STOP(x)\
			{\
				LzsInfRegisterError(LZS_CON_ID_PROGSYS, x);\
				LzsSysSetStatus(LZSSTAT_PLCERROR, LZSSET);\
				LzsStop();\
				globalError++;\
				task_Status_sys = 0;\
				task_Status_nor = 0;\
				LzsEnvDisableAllOutputs(LZS_DISABLE_OUTPUTS_ERRORSTOP);\
				LzsErrWriteFlash();\
			}

#endif
