/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: shared memory data-exchange / control interface
 *                (global data structures and definitions)
 *  
 *****************************************************************************/

#ifndef _LZSSHMSTRUCTS_H_
#define _LZSSHMSTRUCTS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "oem/datatype.h"

/* IDs of exported shared memory areas */
#define LZSSHM_SHMID_VARTAB        604040820
#define LZSSHM_SHMID_LZSIN        604040821
#define LZSSHM_SHMID_LZSOUT        604040822
#define LZSSHM_SHMID_CTRL        604040823
#define LZSSHM_SHMID_DEBUG        604040824
#define LZSSHM_SHMID_LZSWRITE    604040825

/* mutex IDs for shared memories */
#define LZSSHM_MUTEXID_VARTAB    604040900
#define LZSSHM_MUTEXID_LZSIN    604040901
#define LZSSHM_MUTEXID_LZSOUT    604040902
#define LZSSHM_MUTEXID_CTRL        604040903
#define LZSSHM_MUTEXID_DEBUG    604040904
#define LZSSHM_MUTEXID_LZSWRITE    604040905

/* event IDs */
#define LZSSHM_EVENTID_READCOMPLETE 604041000
#define LZSSHM_EVENTID_WRITECOMPLETE 604041001

#ifndef _OPC
#define LZSSHM_SHM_SIZE_MAX                65536
#else
#define LZSSHM_SHM_SIZE_MAX                65536
#endif

#define LZSSHM_SHM_SIZE_HEADER            12
#define LZSSHM_SHM_SIZE_REQUEST_ENTRY    8

/* segment types of the shared memories */
typedef enum
{
    kShmSegTypeUnknown        = 0x00,
    kShmSegTypeCtrl            = 0x01,
    kShmSegTypeLzs            = 0x02,
    kShmSegTypeDebug        = 0x03
}tShmSegType;

/* tShmSegHeader.m_SegTypeVersion */
#define LZSSHM_VERSION_LZS        1    /* VARTAB, LZSIN, LZSOUT    */
#define LZSSHM_VERSION_CTRL        1
#define LZSSHM_VERSION_DEBUG    1

/* tShmSegHeader.m_ConfigVersion */
#define LZSSHM_CONFIG_VERSION    1

typedef struct
{
   LZSDWORD    m_SegLen;            /* Segmentsize */
   LZSWORD    m_SegType;            /* Segmenttype */
   LZSWORD    m_SegTypeVersion;    /* version number of segment structure */
   LZSDWORD    m_ConfigVersion;    /* version identifier of configuration*/
} tShmSegHeaderLzs;

/* variable value quality (OPC) */
#define LZSSHMDATA_QUALITY_GOOD                0
#define LZSSHMDATA_QUALITY_BAD                0xFFFF
#define LZSSHMDATA_QUALITY_CONFIG_ERROR        0x04


#ifndef UNDER_CE /* long long not supported under winCE */

typedef unsigned long long    LZSSHMTSTAMP;    /* 64bit unsigned */

/* message string character */
typedef    char    LZSSHMCHAR;

typedef struct
{
    /*/////////////////////////////////
    // Segment Header
    /////////////////////////////////*/
    LZSDWORD    SegLen;
    LZSWORD        SegType;
    LZSWORD        SegTypeVersion;

    /*/////////////////////////////////
    // State information (RTS-->UI)
    /////////////////////////////////*/
    LZSDWORD    Status;
    LZSDWORD    MaxMem;
    LZSDWORD    UsedMem;
    LZSDWORD    TotalCycleTimeLimit;
    LZSDWORD    TotalCycleTime;
    LZSBYTE        MaintenanceMode;
    LZSBYTE        Initialized;
    LZSWORD        Reserved2;
    LZSDWORD    Reserved3;
    LZSWORD        TaskCount;

    /*/////////////////////////////////
    // Task data (RTS-->UI)
    /////////////////////////////////*/
    LZSCHAR        Taskname1[64];
    LZSDWORD    LastCycleTime1;
    LZSDWORD    MinCycleTime1;
    LZSDWORD    MaxCycleTime1;
    LZSDWORD    AvgCycleTime1;
    LZSSHMTSTAMP        LastExecTime1;
    LZSDWORD    Cycles1;
    LZSCHAR        Taskname2[64];
    LZSDWORD    LastCycleTime2;
    LZSDWORD    MinCycleTime2;
    LZSDWORD    MaxCycleTime2;
    LZSDWORD    AvgCycleTime2;
    LZSSHMTSTAMP        LastExecTime2;
    LZSDWORD    Cycles2;
    LZSCHAR        Taskname3[64];
    LZSDWORD    LastCycleTime3;
    LZSDWORD    MinCycleTime3;
    LZSDWORD    MaxCycleTime3;
    LZSDWORD    AvgCycleTime3;
    LZSSHMTSTAMP        LastExecTime3;
    LZSDWORD    Cycles3;
    LZSCHAR        Taskname4[64];
    LZSDWORD    LastCycleTime4;
    LZSDWORD    MinCycleTime4;
    LZSDWORD    MaxCycleTime4;
    LZSDWORD    AvgCycleTime4;
    LZSSHMTSTAMP        LastExecTime4;
    LZSDWORD    Cycles4;
    LZSCHAR        Taskname5[64];
    LZSDWORD    LastCycleTime5;
    LZSDWORD    MinCycleTime5;
    LZSDWORD    MaxCycleTime5;
    LZSDWORD    AvgCycleTime5;
    LZSSHMTSTAMP        LastExecTime5;
    LZSDWORD    Cycles5;
    LZSCHAR        Taskname6[64];
    LZSDWORD    LastCycleTime6;
    LZSDWORD    MinCycleTime6;
    LZSDWORD    MaxCycleTime6;
    LZSDWORD    AvgCycleTime6;
    LZSSHMTSTAMP        LastExecTime6;
    LZSDWORD    Cycles6;
    LZSCHAR        Taskname7[64];
    LZSDWORD    LastCycleTime7;
    LZSDWORD    MinCycleTime7;
    LZSDWORD    MaxCycleTime7;
    LZSDWORD    AvgCycleTime7;
    LZSSHMTSTAMP        LastExecTime7;
    LZSDWORD    Cycles7;
    LZSCHAR        Taskname8[64];
    LZSDWORD    LastCycleTime8;
    LZSDWORD    MinCycleTime8;
    LZSDWORD    MaxCycleTime8;
    LZSDWORD    AvgCycleTime8;
    LZSSHMTSTAMP        LastExecTime8;
    LZSDWORD    Cycles8;

    /*/////////////////////////////////
    // Message transfer queue (RTS-->UI)
    /////////////////////////////////*/
    LZSWORD    ReadIndex;
    LZSWORD    WriteIndex;
    LZSSHMTSTAMP    TimeStamp1;
    LZSSHMCHAR    Msg1[128];
    LZSSHMTSTAMP    TimeStamp2;
    LZSSHMCHAR    Msg2[128];
    LZSSHMTSTAMP    TimeStamp3;
    LZSSHMCHAR    Msg3[128];
    LZSSHMTSTAMP    TimeStamp4;
    LZSSHMCHAR    Msg4[128];
    LZSSHMTSTAMP    TimeStamp5;
    LZSSHMCHAR    Msg5[128];
    LZSSHMTSTAMP    TimeStamp6;
    LZSSHMCHAR    Msg6[128];
    LZSSHMTSTAMP    TimeStamp7;
    LZSSHMCHAR    Msg7[128];
    LZSSHMTSTAMP    TimeStamp8;
    LZSSHMCHAR    Msg8[128];

    /*/////////////////////////////////
    // Command area
    /////////////////////////////////*/
    LZSWORD        CmdHandShake;    /* (RTS<->client) */
    LZSWORD        Cmd;            /* (RTS<--client) */
    LZSDWORD    CmdResult;        /* (RTS<--client) */

    /*/////////////////////////////////
    // Licence information
    /////////////////////////////////*/
    LZSDWORD    LicenceMode;        /* (RTS-->client)    */
    LZSCHAR        SerialNumber[21];    /* (RTS-->client) */

    /*/////////////////////////////////
    // Resource information
    /////////////////////////////////*/
    LZSCHAR        ResourceName[32];
    LZSCHAR        ProjectName[32];    
    LZSDWORD    ResourceVersion;

    /*/////////////////////////////////
    error code of last error occured
    /////////////////////////////////*/
    LZSWORD        LzsErrorCode;

    /*/////////////////////////////////
    Target System version information
    /////////////////////////////////*/
    LZSWORD        LzsVersion, LzsType, LzsRevision;
    LZSWORD        LzsOemId;    
    
} tShmCtrl;

typedef struct
{
    LZSSHMTSTAMP    TimeStamp;
    LZSSHMCHAR        Msg[128];
    LZSBYTE            MsgDebugLevel;
    LZSDWORD        MsgNumber;
} tShmDebugEntry;

#define LZS_SHM_DBG_BUFFER_SIZE 128

typedef struct
{
    /*/////////////////////////////////
    // Segment Header
    /////////////////////////////////*/
    LZSDWORD    SegLen;
    LZSWORD        SegType;
    LZSWORD        SegTypeVersion;
    
    /*/////////////////////////////////
    // Configuration information
    /////////////////////////////////*/
    LZSCHAR        PathToLogFile[1024];
    LZSCHAR        PathToDebugFile[1024];
    LZSBYTE     MsgLevelDebugFile;
    
    /*/////////////////////////////////
    // Message transfer queue (RTS-->Debug output)
    /////////////////////////////////*/
    LZSWORD     ReadIndex;
    LZSWORD        WriteIndex;
    
    tShmDebugEntry Messages[LZS_SHM_DBG_BUFFER_SIZE];

} tShmDebug;

#endif /* UNDER_CE */

typedef struct
{
    LZSWORD wRecSize;

    LZSWORD wType;

    LZSWORD wSize;

    LZSWORD wProg;

    LZSWORD wSegment;

    LZSWORD wOffset;

    LZSWORD wBit;

    LZSWORD wScope;

} tShmVarInfo;

#ifdef __cplusplus
};
#endif

#endif /* _LZSSHMSTRUCTS_H_ */
