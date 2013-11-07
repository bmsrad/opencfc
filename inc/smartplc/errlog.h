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

#define ERRORLOG_SEGMENT_SIZE (NUM_ERRORLOG_ENTRIES * sizeof(tErrorLogEntry) + LZS_SIZEOF_DATASEGHDR) /* maximum segment size is 0xFFFF */

#ifdef _LZS_ERROR_LOG
/* interface of error log */
LZSBYTE LzsErrlogInitErrorlog(void);
tErrorLogEntry* LzsErrlogWriteErrorlog(LZSDWORD dwCategory, LZSWORD wParameter1, LZSWORD wParameter2, LZSWORD wParameter3, LZSWORD wParameter4);
LZSBYTE LzsErrlogRegisterError(LZSDWORD dwCategory, LZSWORD wParameter1, LZSWORD wParameter2, LZSWORD wParameter3, LZSWORD wParameter4);
LZSBYTE LzsErrlogGetLastError(LZSDWORD dwCategory, LZSWORD* wParameter1, LZSWORD* wParameter2, LZSWORD* wParameter3, LZSWORD* wParameter4);
LZSBYTE LzsErrlogClearLastError(LZSDWORD dwCategory);
#endif

#define ERROR_STOP(x) \
			{ \
				LzsInfRegisterError(LZS_CON_ID_PROGSYS, x); \
				LzsEnvDisableAllOutputs(LZS_DISABLE_OUTPUTS_ERRORSTOP); \
				LzsEnvRegisterSysState(LZS_CON_ID_PROGSYS, kLzsStateSoftStopReq); \
				LzsSysSetStatus(LZSSTAT_RUNNING, LZSCLR); \
				LzsSysSetStatus(LZSSTAT_PLCERROR, LZSSET); \
				LzsSysUpdateMode(); \
				globalError++; \
				task_Status_sys = 0; \
				task_Status_nor = 0; \
			}

#endif
