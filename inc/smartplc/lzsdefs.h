#ifndef _LZSDEFS_H_
#define _LZSDEFS_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Di, 10 Nov  98                                                                */
/*                                                                               */
/* DESCRIPTION:  defines and macros for the runtime system                       */
/*********************************************************************************/


/*--------------------------------------------------------------------------- */
/* declaration of constants */
/*--------------------------------------------------------------------------- */
#define INITSIGNUM      "PlcVersion"        /* Signature string to distinguish */
                                            /* between new-/warm-restart */


/* */
/* constants to adapt RTS to different system enviroments */
/* */
/*---------------------------------------------------------------------------
    [SYSTEC 27.09.2004 -rs] definitions of <LZSMAXWATCH> and
    <LZSPFLOWBUFFSIZE> changed to allow configuring optionally in 
    target-specific file DevCfg.h
//--------------------------------------------------------------------------*/
#ifndef LZSMAXWATCH
    #define LZSMAXWATCH 64 /* watch table entries */
#endif

#ifndef LZSPFLOWBUFFSIZE
    #define LZSPFLOWBUFFSIZE 2048 /* buffer size powerflow */
#endif

#define LZSCMDBUFFSIZE 512                   /* receive buffer size for commands */
#define RECBUFFSIZE (128 + LZSPFLOWBUFFSIZE) /* send buffer size for receipts */
#define LZSMAXEVENTS 10                      /* max. number of callback functions registered at the data server */
#define LZSDATABUFFSIZE USHRT_MAX            /* receive buffer size for data -> taken from limits.h */
#define LZSINVALIDVALUE 0xFFFF               /* used as error value for the callback functions, if the communcation buffer is too small ((LZSWORD) -1) */

/* define for using a hardware run/stop switch */
#define LZSHW_RUN        1
#define LZSHW_STOP        0

/* constants for symbolic identification of attributes */
#define LZSCOLDSTART       0x00                /* identifier "New start" */
#define LZSWARMSTART       0xFF                /* identifier "warm start" */
#define LZSINITIALIZING    0x80                /* identifier "Boot-Phase" */
#define LZSSYSTEMHALTED    0x81                /* identifier "System Halted" */
#define LZSSET             1
#define LZSCLR             0
#define LZSPRIMARY         0                   /* "column index" for access */
#define LZSSECUNDARY       1                   /*  in segment table */

/* bit definitions to store (current) system properties */
#define LZSSTAT_OK                0x0001L       /* B0:  Controller OK */
#define LZSSTAT_LOGIN             0x0002L       /* B1:  Controller in Login-Mode */
#define LZSSTAT_DOWNLOADING       0x0004L       /* B2:  Download activ */
#define LZSSTAT_TASKDEFTAB_VALID  0x0008L       /* B3:  TaskDefTab present */
#define LZSSTAT_SEGTAB_CREATED    0x0010L       /* B4:  Segmenttabelle present */
#define LZSSTAT_PROGRAM_VALID     0x0020L       /* B5:  valid program present */
#define LZSSTAT_COMMAND_EXECUTED  0x0040L       /* B6:  command executed                             */
#define LZSSTAT_HW_STOP              0x0080L       /* B7:  state of hardware run/stop switch */
#define LZSSTAT_EXT_COMM_LOCKED   0x0100L       /* B8:  external Comm. stopped */
#define LZSSTAT_RECOVERING        0x0200L       /* B9:  Recover-Mode activ */
#define LZSSTAT_NIOERROR          0x0400L       /* B10: Networkerror Remote-IO */
/* [SYSTEC/CANopen: 11.10.2006 -rs]: staus bit <LZSSTAT_ENABLED> reused as <LZSSTAT_DOING_CFG_REMOTE> */
/* #define LZSSTAT_ENABLED           0x0800L */    /*  B11: 23.1.98 */
#define LZSSTAT_RUN_CFG_REMOTE    0x0800L       /* B11: PLC is configuring remote I/O nodes */
#define LZSSTAT_RUN_EVENT_TASK    0x1000L       /* B12: Execution of Start/Stop/Error-Task */
#define LZSSTAT_RUNNING           0x2000L       /* B13: program execution activ */
#define LZSSTAT_COMERROR          0x4000L       /* B14: Communication-Error with PC */
#define LZSSTAT_PLCERROR          0x8000L       /* B15: Stop after internal error */

#define LZSSTAT_ACCPT_DOWNLOAD    0x00010000L  /* B16: Download Resource possible */
#define LZSSTAT_ACCPT_SEGMENT     0x00020000L  /* B17: Download Segment allowed */
#define LZSSTAT_ACCPT_STOP_CMD    0x00040000L  /* B18: Stop-command allowed */
#define LZSSTAT_ACCPT_COLD_START  0x00080000L  /* B19: Cold-start possible/supported */
#define LZSSTAT_ACCPT_WARM_START  0x00100000L  /* B20: Warm-start possible/supported */
#define LZSSTAT_ACCPT_HOT_START   0x00200000L  /* B21: Continuation possible/supported */
#define LZSSTAT_ACCPT_POWERFLOW   0x00400000L  /* B22: Powerflow possible/supported */
#define LZSSTAT_ACCPT_FORCE_BIT   0x00800000L  /* B23: Force Bit possible/supported */
#define LZSSTAT_ACCPT_FORCE_BYTE  0x01000000L  /* B24: Force Byte possible/supported */

/* [SYSTEC/CANopen: 11.10.2006 -rs]: <LZSSTAT_ENABLED> redefined for compatibility reasons - is this really necessary ? */
#define  LZSSTAT_ENABLED    LZSSTAT_RUN_CFG_REMOTE
#define LZSSTAT_NETERROR    LZSSTAT_COMERROR

#define LZS_DISABLE_OUTPUTS_HWSTOP            0x01
#define LZS_DISABLE_OUTPUTS_SWSTOP            0x02
#define LZS_DISABLE_OUTPUTS_ERRORSTOP        0x04
#define LZS_DISABLE_OUTPUTS_BREAKSTOP        0x08

#define LZS_RSTART_CONTINUE     0               /* Reset with immediate reboot */
#define LZS_RSTART_WAIT_USER    1               /* Reset after user inputs */

#define LZS_FIRMWARETABS        4

#ifdef _IP_BREAKPOINTS_
/* B.S. 06.07.1998 */
#define IP_MAX_BREAKPOINTS        50
#endif

/* defines for capabilities */
#define LZSCAP_CAP_AVAILABLE             0x00000001    /* DWORD 0 */
#define LZSCAP_IP_FLOAT                  0x00000002  /* DWORD 0 */
#define LZSCAP_IP_8BYTEDATA              0x00000004  /* DWORD 0 */
#define LZSCAP_IP_STRING                 0x00000008  /* DWORD 0 */
#define LZSCAP_IP_PFLOW                  0x00000010    /* DWORD 0 */
#define LZSCAP_UPLOAD                    0x00000020  /* DWORD 0 */
#define LZSCAP_NATIVCODE                 0x00000040  /* DWORD 0 */
#define LZSCAP_WRAPPER_FB                0x00000080  /* DWORD 0 */
#define LZSCAP_PERSISTENCE_DISKLIKE      0x00000100    /* DWORD 0 */
#define LZSCAP_STATIC_PERSISTENCE        0x00000200  /* DWORD 0 */
#define LZSCAP_PERSISTENCE_POINTER       0x00000400  /* DWORD 0 */
#define LZSCAP_PERSISTENCE_SAVERAM       0x00000800  /* DWORD 0 */
#define LZSCAP_PERS_5                    0x00001000    /* DWORD 0 */
#define LZSCAP_PERS_6                    0x00002000  /* DWORD 0 */
#define LZSCAP_PERS_7                    0x00004000  /* DWORD 0 */
#define LZSCAP_PERS_8                    0x00008000  /* DWORD 0 */
#define LZSCAP_IP_BREAKPOINTS            0x00010000    /* DWORD 0 */
#define LZSCAP_PARAMETER                 0x00020000  /* DWORD 0 */
#define LZSCAP_TASKINFO                  0x00040000  /* DWORD 0 */
#define LZSCAP_SZM_INLINE                0x00080000  /* DWORD 0 */
#define LZSCAP_8BITBYTES                 0x00100000    /* DWORD 0 */
#define LZSCAP_16BITBYTES                0x00200000  /* DWORD 0 */
#define LZSCAP_32BITBYTES                0x00400000  /* DWORD 0 */
#define LZSCAP_64BITBYTES                0x00800000  /* DWORD 0 */
#define LZSCAP_DSALIGNMENT_1             0x01000000    /* DWORD 0 */
#define LZSCAP_DSALIGNMENT_2             0x02000000  /* DWORD 0 */
#define LZSCAP_DSALIGNMENT_4             0x04000000  /* DWORD 0 */
#define LZSCAP_DSALIGNMENT_DSP563        0x08000000  /* DWORD 0 */
#define LZSCAP_IPLOOP_TIMERTASK          0x10000000    /* DWORD 0 */
#define LZSCAP_DIRECT_BYREF              0x20000000  /* DWORD 0 */
#define LZSCAP_MULTIADDWATCH             0x40000000  /* DWORD 0 */
#define LZSCAP_MULTISEGDWL               0x80000000  /* DWORD 0 */

#define LZSCAP_SETVARLONG                0x00000001    /* DWORD 1 */
#define LZSCAP_DWLWITHOUTSTOP            0x00000002  /* DWORD 1 */
#define LZSCAP_HISTDATA                  0x00000004    /* DWORD 1 */
#define LZSCAP_DWLBINSEGM                0x00000008    /* DWORD 1 -  Download binary Segment for CANopen*/
#define LZSCAP_POINTER                   0x00000010    /* DWORD 1 */
#define LZSCAP_WSTRING                   0x00000020    /* DWORD 1 */
#define LZSCAP_ANYDATE                   0x00000040    /* DWORD 1 */
#define LZSCAP_DWLWITHOUTSTOP_FORCETAB   0x00000080    /* DWORD 1 - update of force table on OnlineEdit */
/* DWORD 2-9 (and rest of DWORD 1) not defined yet*/
#define LZSCAP_UPLOAD_ERRORLOG           0x00000100  /* DWORD 1 */
#define LZSCAP_SETVARMULTIPLE            0x00000200  /* DWORD 1 */
#define LZSCAP_SMARTVARTAB               0x00000400  /* DWORD 1 */
#define LZSCAP_NOTIFY_OPC_DWL            0x00000800  /* DWORD 1 */ 


/*********************************************************************************************************
 * DUMP_BUFFER_SIZE determines the number of nested function block calls to be supported by the          *
 * DumpBuffer. 12 is a fixed size that represents the minimum size when no nested call is made. For      *
 * every nested call another two words will be used. So on an 8bit-byte machine, the value 1024          *
 * supports up to 253 nested calls ((1024 - 12) / (2 * 2)) = 253                                         *
 * Decreasing this value will limit the amount of nested calls displayed in OpenPCS's call stack output! *
 *********************************************************************************************************/
#define DUMP_BUFFER_SIZE 1024

#if DUMP_BUFFER_SIZE < 12
	#error DUMP_BUFFER_SIZE has to be greater than 12
#endif

#define LZSCAP_PATCH_NC		             0x00001000  /* DWORD 1 */



/*--------------------------------------------------------------------------- */
/* Macrodefinitions */
/*--------------------------------------------------------------------------- */
#define LZSMALLOC_FAST(MemSize)  LzsEnvMemAlloc(MemSize)
#define LZSMALLOC(MemSize)  LzsEnvMemAlloc(MemSize)
#define LZSFREE(MemPtr)     LzsEnvMemFree(MemPtr)


#endif
