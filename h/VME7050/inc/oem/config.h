#ifndef _CONFIG_H_
#define _CONFIG_H_

/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Do, 11 Mrz  99                                                                */
/*                                                                               */
/* DESCRIPTION: in this header all defines should be set to configure your       */
/*                runtime system                                                 */
/*********************************************************************************/

#define _IP_FLOAT_         /* use functions to implement real arithmetic */
                           /* if this is not defined REALs are not supported */
#define _IP_8BYTEDATA_     /* suppport of 8-byte-datatypes */
#define _IP_STRING_        /* use functions to support STRING variables */
#define _IP_WSTRING_       /* double-byte string support */
#undef _IP_ANYDATE_        /* ANY_DATE (DATE, DATE_AND_TIME, TIME_OF_DAY) and RTC support */

#define _IP_PFLOW_          /* supporting the status display in the online editor */
#undef  _IP_REAL48_         /* supporting 48Bit floating point */
#undef  _IP_INT24_          /* supporting 24Bit integer */
#undef  _IP_POINTER_        /* POINTER data type support */

#define _IP_BREAKPOINTS_    /* supporting breakpoints for debugging */
#define _LZS_UPLOAD_        /* support upload of programs */
#define _LZS_NATIVCODE_     /* support for nativ code */
#define _WRAPPER_FB_        /* Wrapper Function Blocks for Ladder Editor */
#define _LZS_MOTOROLA_        /* platforms with motorola alignment */
#define _PASCAL_CALLING_CONVENTION /* for extended STRING support, INSERT, DELETE, etc. */
#define _IP_ENABLE_ACCU_ANY_OPTIMIZE_  /* for extended STRING support, INSERT, DELETE, etc. */

#undef _FORCE_VARIABLES_ /* undefine this to reduce the memory footprint of SmartPLC */
#define _PFLOW_FUNCTION_ /* undefine this to reduce the memory footprint of SmartPLC */
#define _VARIABLE_TABLE_ /* undefine this to reduce the memory footprint of SmartPLC */
#define _DUMP_FUNCTION_ /* undefine this to reduce the memory footprint of SmartPLC */

#define _ENABLE_UCODE_ /* undefine this to reduce the memory footprint of SmartPLC */
#undef _ONE_TASK_ONLY_T1_ /* define this to reduce the memory footprint of SmartPLC */

#undef _USE_L2MEM_FOR_FBS_ /* optimization for MS platform */

#undef ENABLE_PERFORMANCE_MONITORING /* collect performance data; select ONE OF the following defines to activate different kinds of measurements */
#undef ENABLE_PERFORMANCE_MONITORING_TASKS
#undef ENABLE_PERFORMANCE_MONITORING_MODES
#undef ENABLE_PERFORMANCE_MONITORING_CUSTOM

#undef SCHEDULER_DEBUG

/*---------------------*/
/* kind of persistence */
/* only one of the     */
/* following           */
/*---------------------*/
#undef   _LZS_NO_PERSISTENCE_
#define  _LZS_PERSISTENCE_DISKLIKE_
#undef   _LZS_STATIC_PERSISTENCE_
#undef   _LZS_PERSISTENCE_POINTER_
#undef   _LZS_PERSISTENCE_SAVERAM_
#undef   _LZS_PERSISTENCE_MIXED_

#ifndef _LZS_NO_PERSISTENCE_
#define _LZS_SAVESYSTEMCMD_ /* save current resource to persistent storage on request from programming system */
                            /* _LZS_DIRECT_BYREF_ cannot be used together with this option! */
#endif

/*----------------------------------------------*/
/* retain variables                             */
/* only useful in combination with persistence! */
/*----------------------------------------------*/
#undef _LZS_RETAIN_

/*----------------------------------------------*/
/* dynamic retain variables (user-defined when  */
/* setting variables online)                    */
/* only useful in combination with persistence! */
/*----------------------------------------------*/
#undef _LZS_DYNAMIC_RETAIN_
#define NUM_DR_ENTRIES 32

/*----------------------*/
/* define the size in   */
/* bits that one char   */
/* has                  */
/*----------------------*/
#define _LZS_8BITBYTES_
#undef  _LZS_16BITBYTES_
#undef  _LZS_32BITBYTES_

#undef  _LZS_DSALIGNMENT_1_
#undef  _LZS_DSALIGNMENT_2_
#define _LZS_DSALIGNMENT_4_
#undef  _LZS_DSALIGNMENT_DSP563_

#undef _LZS_TASKINFO_    /* using firmware function block to get task information */
#undef _LZS_OEMVERSINFO_ /* check extended OEM version info */

#undef _LZS_SZM_INLINE_ /* if defined inline memory access is used instead of functions */
                        /* alignment is important */

/*define this for UCODE TRACE only*/
#undef _LZS_GENERATE_IP_DEBUG_INFO_

#undef _LZS_IPLOOP_TIMERTASK_    /* runnimg the runtime system in own system TIMER-threads */
#undef _LZS_DIRECT_BYREF_

#define _LZS_DWLWITHOUTSTOP_  /* async dwl of resource with replace after cycle. see lzsdwlws.c */
#define _LZS_DWLWS_RUN_INIT_MODE_ /* run init mode once after applying online changes */

#undef _LZS_DATASEGDESTRUCTOR_  /* LzsEnvPreFreeDataSegment() is called before freeing a data segment */

#undef _LZS_HISTDATA_      /* previous data: collect variable values on cycle end */
#define _LZS_DWL_RAWFILE_   /* download of files via OpenPCS onto the runtime system platform */
#define DWL_RAWFILE_MAX_PATH 64
#define DWL_RAWFILE_MAX_FILENAME 32

#define LZSMAXWATCH 200   /* number of entries in watch table */

#undef _LZS_EXTCTRL_    /* external control interface */
#ifdef _LZS_EXTCTRL_
#define _LZS_SHM_INTERFACE_    /* extctrl requires shared memory data-exchange/control interface */
#endif

#undef _LZS_SUPPORT_OPC_CONNECT

/* activate this define here or in preprocessor definitions of your compiler */
#ifdef _LZS_SUPPORT_OPC_CONNECT /* OPC-Server can connect simultaneously to progr. system */
#define _LZS_MAX_NUMBER_OPC_CONNECTIONS 1  /* currently one connection is supported */
#else
#define _LZS_MAX_NUMBER_OPC_CONNECTIONS 0
#endif

/*------------------------------*/
/* error log, exception buffers */
/*------------------------------*/
#define _LZS_ERROR_LOG
#undef _LZS_ERROR_LOG_CPUEXCEPTIONS
#undef _LZS_ERROR_LOG_LED_DISPLAY
#undef _LZS_ERROR_LOG_WRITE_FLASH

#ifdef _LZS_ERROR_LOG
#define NUM_ERRORLOG_ENTRIES 2048
#endif

#ifdef _LZS_ERROR_LOG_CPUEXCEPTIONS
#define NUM_EXCEPTIONBUFFER_ENTRIES 8
#endif

/*------------------------------------*/
/* shared memory and data consistency */
/*------------------------------------*/
/* configure if this platform uses data consistency extensions (P0699-specific) */
#undef USE_DATA_CONSISTENCY

/* configure if this platform uses a multi-CPU shared memory (P0699-specific) */
#undef USE_SHARED_MEMORY

#ifdef USE_SHARED_MEMORY
/* configure if this platform uses data consistency extensions for shared memory variables (P0699-specific) */
#undef USE_DATA_CONSISTENCY_SHM
#endif

/*---------*/
/* BL code */
/*---------*/
#define USE_BL_CODE

#ifdef USE_BL_CODE
#define USE_BL_NATIVE_CODE
#endif

/*-------------------------------*/
/* communication proxy for racks */
/*-------------------------------*/
#undef USE_COMMUNICATION_PROXY

/*-----------------------*/
/* clock synchronization */
/*-----------------------*/
#undef CLOCK_SYNCHRONIZATION

/*-------------*/
/* T0 watchdog */
/*-------------*/
#undef USE_T0_WATCHDOG

#ifdef USE_T0_WATCHDOG
#define NUM_WD_EVENTS_BEFORE_REINIT 4
#define NUM_WD_ERRORS_BEFORE_STOP 2
#define WD_TIMESPAN_MS 10000
#endif

/*------------------------------*/
/* station (rack) configuration */
/*------------------------------*/
#undef USE_STATION_HWCONFIG
#define MAX_SLOTS_IN_RACK 21
#define RETRY_WAITTIME_MS 2000
#define MAX_NUM_RETRIES 5

#ifdef USE_STATION_HWCONFIG
#undef USE_STATION_HWCONFIG_CRC_CHECK
#endif

/*--------------------------*/
/* firmware library manager */
/*--------------------------*/
#undef USE_FIRMWARE_LIBRARY_MANAGER
/* NOTE: if this is defined, linker will report undefined symbol LzsSetOEMFBTable2 */
/* this is normal, because it comes from file oemfbtab2.c, generated by firmware library manager */
/* when defining USE_FIRMWARE_LIBRARY_MANAGER, object files must be taken to the engineering tool and firmware library manager must build and link SmartPLC! */

#endif
