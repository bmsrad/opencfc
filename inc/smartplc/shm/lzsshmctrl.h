/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: shared memory data-exchange / control interface 
 *                (RTS control)
 *  
 *****************************************************************************/

#ifndef _LZSSHMCTRL_H_
#define _LZSSHMCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _LZS_SHM_INTERFACE_
/* default value for cycle time limit in ms
   value for shared memory, before the UI is started */
#define LZSSHMCTRL_DEFAULT_CYCLE_TIME_LIMIT 1000 
#endif

#ifndef _LZS_SHM_INTERFACE_
    #define LZSSHMCTRL_INITIALIZE
    #define LZSSHMCTRL_SHUTDOWN
    #define LZSSHMCTRL_WRITE_TASKINFO
    #define LZSSHMCTRL_WRITE_TASKCOUNT(x)
    #define LZSSHMCTRL_CHECK_CMD
    #define LZSSHMCTRL_WRITE_ERROR(x)
    #define LZSSHMCTRL_WRITE_MEM_INFO
    #define LZSSHMCTRL_UPDATE_STATUS
    #define LZSSHMCTRL_CHECK_CYCLE_LENGTH(x)
    #define LZSSHMCTRL_UPDATE_RESOURCE_NAME
    #define LZSSHMCTRL_RESET_RESOURCE_NAME
    #define LZSSHMCTRL_ON_DWL_COMPLETE
    #define LZSSHMCTRL_ON_CYCLE_FINISHED
#else
    #define LZSSHMCTRL_INITIALIZE            LzsShmCtrlInitialize();
    #define LZSSHMCTRL_SHUTDOWN                LzsShmCtrlShutdown();
    #define LZSSHMCTRL_WRITE_TASKINFO        LzsShmCtrlWriteTaskInfo();
    #define LZSSHMCTRL_WRITE_TASKCOUNT(x)    LzsShmCtrlWriteTaskCount(x);
    #define LZSSHMCTRL_CHECK_CMD            LzsShmCtrlCheckCommand();
    #define LZSSHMCTRL_WRITE_ERROR(x)        LzsShmCtrlWriteErrorLog(x);
    #define LZSSHMCTRL_WRITE_MEM_INFO        LzsShmCtrlWriteMemInfo();
    #define LZSSHMCTRL_UPDATE_STATUS        LzsShmCtrlUpdateStatus();
    #define LZSSHMCTRL_CHECK_CYCLE_LENGTH(x)    LzsShmCtrlCheckCycleLength(x);
    #define LZSSHMCTRL_UPDATE_RESOURCE_NAME  LzsShmCtrlUpdateResourceName();
    #define LZSSHMCTRL_RESET_RESOURCE_NAME LzsShmCtrlResetResourceName(); 
    #define LZSSHMCTRL_ON_DWL_COMPLETE        LzsShmCtrlOnDwlComplete();
    #define LZSSHMCTRL_ON_CYCLE_FINISHED    LzsShmCtrlOnCycleFinished();
#endif /* _LZS_SHM_INTERFACE_ */

#ifdef _LZS_SHM_INTERFACE_
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmCtrlInitialize (void);
LZSPUBLIC32 void    LZSPUBLIC LzsShmCtrlShutdown (void);
LZSPUBLIC32 LZSDWORD LZSPUBLIC LzsShmCtrlGetPointer(void);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmCtrlWriteTaskInfo (void);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmCtrlWriteTaskCount (LZSWORD wTaskCount_i);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmCtrlCheckCommand (void);
LZSPUBLIC32 LZSBYTE    LZSPUBLIC LzsShmCtrlWriteErrorLog(LZSCONST LZSCHAR* psMessage);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmCtrlUpdateResourceName(void);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmCtrlResetResourceName(void);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmCtrlWriteMemInfo(void);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmCtrlUpdateStatus(void);
LZSPUBLIC32 LZSBOOL LZSPUBLIC LzsShmCtrlCheckCycleLength (LZSDWORD dwLastCycleTime_i);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsShmCtrlOnDwlComplete(void);
LZSPUBLIC32 void    LZSPUBLIC LzsShmCtrlOnCycleFinished(void);
#endif

#ifdef __cplusplus
}    /* extern "C" */
#endif

#endif /* _LZSSHMCTRL_H_ */

