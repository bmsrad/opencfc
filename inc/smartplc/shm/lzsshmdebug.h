/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: shared memory data-exchange / control interface (debug messages)
 *  
 *****************************************************************************/

#ifndef _LZSSHMDEBUG_H_
#define _LZSSHMDEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include    "smartplc/shm/lzsshmstructs.h"

typedef enum
{
    kLzsShmDebugLevel0 = 0x00,    /* highest priority */
    kLzsShmDebugLevel1 = 0x01,
    kLzsShmDebugLevel2 = 0x02,
    kLzsShmDebugLevel3 = 0x03,
    kLzsShmDebugLevel4 = 0x04,
    kLzsShmDebugLevel5 = 0x05,
    kLzsShmDebugLevel6 = 0x06,
    kLzsShmDebugLevel7 = 0x07    /* lowest priority */
} tLzsShmDebugLevel;

#define LZSSHMDEBUG_DEFAULT_MSG_LEVEL_LOG_FILE        kLzsShmDebugLevel0
#define LZSSHMDEBUG_DEFAULT_MSG_LEVEL_DEBUG_FILE    kLzsShmDebugLevel0

#define LZSSHMDEBUG_MAX_LIMIT_SIZE_DEBUG_FILE                1048576 /* = 1 MByte */
#define LZSSHMDEBUG_MAX_LIMIT_SIZE_LOG_FILE                 1048576 /* = 1 MByte */


#ifndef _LZS_SHM_INTERFACE_

#define TRACE_TO_DEBUG_SHM

#define LZSSHMDEBUG_INITIALIZE

#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_0(x)    
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_1(x)    
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_2(x)    
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_3(x)    
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_4(x)
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_5(x)
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_6(x)    
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_7(x)

#else    /* else if _LZS_SHM_INTERFACE_ is defined */

LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmTraceDebug(LZSBYTE bTraceLevel, const char* pszFormat, ...);

#define TRACE_TO_DEBUG_SHM LzsShmTraceDebug

#define LZSSHMDEBUG_INITIALIZE                LzsShmDebugInitialize();
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_0(x)    LzsShmDebugWriteMessage(x, kLzsShmDebugLevel0);     
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_1(x)    LzsShmDebugWriteMessage(x, kLzsShmDebugLevel1);
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_2(x)    LzsShmDebugWriteMessage(x, kLzsShmDebugLevel2);
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_3(x)    LzsShmDebugWriteMessage(x, kLzsShmDebugLevel3);
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_4(x)    LzsShmDebugWriteMessage(x, kLzsShmDebugLevel4);
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_5(x)    LzsShmDebugWriteMessage(x, kLzsShmDebugLevel5);
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_6(x)    LzsShmDebugWriteMessage(x, kLzsShmDebugLevel6);
#define LZSSHMDEBUG_WRITE_MESSAGE_LEV_7(x)    LzsShmDebugWriteMessage(x, kLzsShmDebugLevel7);

LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmDebugInitialize (void);
LZSPUBLIC32 LZSBYTE    LZSPUBLIC LzsShmDebugWriteMessage(const LZSSHMCHAR* psMessage, tLzsShmDebugLevel bDebugLevelMsg);

#endif /* _LZS_SHM_INTERFACE_ */

#define TRACE_TO_DEBUG_SHM_0(TraceLevel, p0)                              TRACE_TO_DEBUG_SHM(TraceLevel, p0)
#define TRACE_TO_DEBUG_SHM_1(TraceLevel, p0, p1)                        TRACE_TO_DEBUG_SHM(TraceLevel, p0, p1)
#define TRACE_TO_DEBUG_SHM_2(TraceLevel, p0, p1, p2)                  TRACE_TO_DEBUG_SHM(TraceLevel, p0, p1, p2)
#define TRACE_TO_DEBUG_SHM_3(TraceLevel, p0, p1, p2, p3)              TRACE_TO_DEBUG_SHM(TraceLevel, p0, p1, p2, p3)
#define TRACE_TO_DEBUG_SHM_4(TraceLevel, p0, p1, p2, p3, p4)        TRACE_TO_DEBUG_SHM(TraceLevel, p0, p1, p2, p3, p4)
#define TRACE_TO_DEBUG_SHM_5(TraceLevel, p0, p1, p2, p3, p4, p5)    TRACE_TO_DEBUG_SHM(TraceLevel, p0, p1, p2, p3, p4, p5)

/* no parameter */
#define LZSSHMDEBUG0_LEVEL0(p0)          LZSTRACE0(p0); TRACE_TO_DEBUG_SHM_0(kLzsShmDebugLevel0, p0)
#define LZSSHMDEBUG0_LEVEL1(p0)          LZSTRACE0(p0); TRACE_TO_DEBUG_SHM_0(kLzsShmDebugLevel1, p0)
#define LZSSHMDEBUG0_LEVEL2(p0)          LZSTRACE0(p0); TRACE_TO_DEBUG_SHM_0(kLzsShmDebugLevel2, p0)
#define LZSSHMDEBUG0_LEVEL3(p0)          LZSTRACE0(p0); TRACE_TO_DEBUG_SHM_0(kLzsShmDebugLevel3, p0)
#define LZSSHMDEBUG0_LEVEL4(p0)          LZSTRACE0(p0); TRACE_TO_DEBUG_SHM_0(kLzsShmDebugLevel4, p0)
#define LZSSHMDEBUG0_LEVEL5(p0)          LZSTRACE0(p0); TRACE_TO_DEBUG_SHM_0(kLzsShmDebugLevel5, p0)
#define LZSSHMDEBUG0_LEVEL6(p0)          LZSTRACE0(p0); TRACE_TO_DEBUG_SHM_0(kLzsShmDebugLevel6, p0)
#define LZSSHMDEBUG0_LEVEL7(p0)          LZSTRACE0(p0); TRACE_TO_DEBUG_SHM_0(kLzsShmDebugLevel7, p0)

/* one parameter */
#define LZSSHMDEBUG1_LEVEL0(p0, p1)          LZSTRACE1(p0, p1); TRACE_TO_DEBUG_SHM_1(kLzsShmDebugLevel0, p0, p1)
#define LZSSHMDEBUG1_LEVEL1(p0, p1)          LZSTRACE1(p0, p1); TRACE_TO_DEBUG_SHM_1(kLzsShmDebugLevel1, p0, p1)
#define LZSSHMDEBUG1_LEVEL2(p0, p1)          LZSTRACE1(p0, p1); TRACE_TO_DEBUG_SHM_1(kLzsShmDebugLevel2, p0, p1)
#define LZSSHMDEBUG1_LEVEL3(p0, p1)          LZSTRACE1(p0, p1); TRACE_TO_DEBUG_SHM_1(kLzsShmDebugLevel3, p0, p1)
#define LZSSHMDEBUG1_LEVEL4(p0, p1)          LZSTRACE1(p0, p1); TRACE_TO_DEBUG_SHM_1(kLzsShmDebugLevel4, p0, p1)
#define LZSSHMDEBUG1_LEVEL5(p0, p1)          LZSTRACE1(p0, p1); TRACE_TO_DEBUG_SHM_1(kLzsShmDebugLevel5, p0, p1)
#define LZSSHMDEBUG1_LEVEL6(p0, p1)          LZSTRACE1(p0, p1); TRACE_TO_DEBUG_SHM_1(kLzsShmDebugLevel6, p0, p1)
#define LZSSHMDEBUG1_LEVEL7(p0, p1)          LZSTRACE1(p0, p1); TRACE_TO_DEBUG_SHM_1(kLzsShmDebugLevel7, p0, p1)

/* two parameters */
#define LZSSHMDEBUG2_LEVEL0(p0, p1, p2)          LZSTRACE2(p0, p1, p2); TRACE_TO_DEBUG_SHM_2(kLzsShmDebugLevel0, p0, p1, p2)
#define LZSSHMDEBUG2_LEVEL1(p0, p1, p2)          LZSTRACE2(p0, p1, p2); TRACE_TO_DEBUG_SHM_2(kLzsShmDebugLevel1, p0, p1, p2)
#define LZSSHMDEBUG2_LEVEL2(p0, p1, p2)          LZSTRACE2(p0, p1, p2); TRACE_TO_DEBUG_SHM_2(kLzsShmDebugLevel2, p0, p1, p2)
#define LZSSHMDEBUG2_LEVEL3(p0, p1, p2)          LZSTRACE2(p0, p1, p2); TRACE_TO_DEBUG_SHM_2(kLzsShmDebugLevel3, p0, p1, p2)
#define LZSSHMDEBUG2_LEVEL4(p0, p1, p2)          LZSTRACE2(p0, p1, p2); TRACE_TO_DEBUG_SHM_2(kLzsShmDebugLevel4, p0, p1, p2)
#define LZSSHMDEBUG2_LEVEL5(p0, p1, p2)          LZSTRACE2(p0, p1, p2); TRACE_TO_DEBUG_SHM_2(kLzsShmDebugLevel5, p0, p1, p2)
#define LZSSHMDEBUG2_LEVEL6(p0, p1, p2)          LZSTRACE2(p0, p1, p2); TRACE_TO_DEBUG_SHM_2(kLzsShmDebugLevel6, p0, p1, p2)
#define LZSSHMDEBUG2_LEVEL7(p0, p1, p2)          LZSTRACE2(p0, p1, p2); TRACE_TO_DEBUG_SHM_2(kLzsShmDebugLevel7, p0, p1, p2)

/* three parameters */
#define LZSSHMDEBUG3_LEVEL0(p0, p1, p2, p3)          LZSTRACE3(p0, p1, p2, p3); TRACE_TO_DEBUG_SHM_3(kLzsShmDebugLevel0, p0, p1, p2, p3)
#define LZSSHMDEBUG3_LEVEL1(p0, p1, p2, p3)          LZSTRACE3(p0, p1, p2, p3); TRACE_TO_DEBUG_SHM_3(kLzsShmDebugLevel1, p0, p1, p2, p3)
#define LZSSHMDEBUG3_LEVEL2(p0, p1, p2, p3)          LZSTRACE3(p0, p1, p2, p3); TRACE_TO_DEBUG_SHM_3(kLzsShmDebugLevel2, p0, p1, p2, p3)
#define LZSSHMDEBUG3_LEVEL3(p0, p1, p2, p3)          LZSTRACE3(p0, p1, p2, p3); TRACE_TO_DEBUG_SHM_3(kLzsShmDebugLevel3, p0, p1, p2, p3)
#define LZSSHMDEBUG3_LEVEL4(p0, p1, p2, p3)          LZSTRACE3(p0, p1, p2, p3); TRACE_TO_DEBUG_SHM_3(kLzsShmDebugLevel4, p0, p1, p2, p3)
#define LZSSHMDEBUG3_LEVEL5(p0, p1, p2, p3)          LZSTRACE3(p0, p1, p2, p3); TRACE_TO_DEBUG_SHM_3(kLzsShmDebugLevel5, p0, p1, p2, p3)
#define LZSSHMDEBUG3_LEVEL6(p0, p1, p2, p3)          LZSTRACE3(p0, p1, p2, p3); TRACE_TO_DEBUG_SHM_3(kLzsShmDebugLevel6, p0, p1, p2, p3)
#define LZSSHMDEBUG3_LEVEL7(p0, p1, p2, p3)          LZSTRACE3(p0, p1, p2, p3); TRACE_TO_DEBUG_SHM_3(kLzsShmDebugLevel7, p0, p1, p2, p3)

/* four parameters */
#define LZSSHMDEBUG4_LEVEL0(p0, p1, p2, p3, p4)          LZSTRACE4(p0, p1, p2, p3, p4); TRACE_TO_DEBUG_SHM_4(kLzsShmDebugLevel0, p0, p1, p2, p3, p4)
#define LZSSHMDEBUG4_LEVEL1(p0, p1, p2, p3, p4)          LZSTRACE4(p0, p1, p2, p3, p4); TRACE_TO_DEBUG_SHM_4(kLzsShmDebugLevel1, p0, p1, p2, p3, p4)
#define LZSSHMDEBUG4_LEVEL2(p0, p1, p2, p3, p4)          LZSTRACE4(p0, p1, p2, p3, p4); TRACE_TO_DEBUG_SHM_4(kLzsShmDebugLevel2, p0, p1, p2, p3, p4)
#define LZSSHMDEBUG4_LEVEL3(p0, p1, p2, p3, p4)          LZSTRACE4(p0, p1, p2, p3, p4); TRACE_TO_DEBUG_SHM_4(kLzsShmDebugLevel3, p0, p1, p2, p3, p4)
#define LZSSHMDEBUG4_LEVEL4(p0, p1, p2, p3, p4)          LZSTRACE4(p0, p1, p2, p3, p4); TRACE_TO_DEBUG_SHM_4(kLzsShmDebugLevel4, p0, p1, p2, p3, p4)
#define LZSSHMDEBUG4_LEVEL5(p0, p1, p2, p3, p4)          LZSTRACE4(p0, p1, p2, p3, p4); TRACE_TO_DEBUG_SHM_4(kLzsShmDebugLevel5, p0, p1, p2, p3, p4)
#define LZSSHMDEBUG4_LEVEL6(p0, p1, p2, p3, p4)          LZSTRACE4(p0, p1, p2, p3, p4); TRACE_TO_DEBUG_SHM_4(kLzsShmDebugLevel6, p0, p1, p2, p3, p4)
#define LZSSHMDEBUG4_LEVEL7(p0, p1, p2, p3, p4)          LZSTRACE4(p0, p1, p2, p3, p4); TRACE_TO_DEBUG_SHM_4(kLzsShmDebugLevel7, p0, p1, p2, p3, p4)

#ifdef __cplusplus
}    /* extern "C" */
#endif

#endif /* LZS_SHM_DEBUG_H */
