/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: shared memory data-exchange / control interface 
 *                (inter-process-communication wrapper)
 *  
 *****************************************************************************/
 
#ifndef _LZSSHMIPC_H_
#define _LZSSHMIPC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include    "smartplc/odk_plc.h"

/* platform specific */
#ifdef _WINDOWS

/* these defines are intended to be used with the supplied lzsshmipc_windows.c implemenation */
#include <windows.h>

typedef HANDLE    tHMutex;    /* mutex handle */
typedef HANDLE    tHShm;        /* shared memory handle */
typedef HANDLE  tHEvent;    /* event handle */

#define LZSSHM_HMUTEX_INITIAL        NULL
#define LZSSHM_HSHM_INITIAL            NULL
#define LZSSHM_HEVENT_INITIAL       NULL

#else

#ifdef __LINUX_GCC__

/* these defines are intended to be used with the supplied lzsshmipc_linux.c implemenation */
typedef int        tHMutex;    /* mutex handle */
typedef int        tHShm;        /* shared memory handle */

#define LZSSHM_HMUTEX_INITIAL        -1
#define LZSSHM_HSHM_INITIAL            -1

#else

/* declare these as suitable for your platform */
typedef int        tHMutex;    /* mutex handle */
typedef int        tHShm;        /* shared memory handle */

#define LZSSHM_HMUTEX_INITIAL        -1
#define LZSSHM_HSHM_INITIAL            -1

#endif

#endif

/* ------------------------------------------------------------ */

/* mutexes
   usable from different processes
*/

LZSBOOL MutexCreate(int nMutexId, tHMutex* hMutex);    /* create a new mutex */  
void MutexDestroy(tHMutex *hMutex);                    /* remove a mutex create with CreateMutex() */

#ifndef UNDER_CE
LZSBOOL MutexOpen(int nMutexId, tHMutex* hMutex);    /* attach to an already existant mutex */
#endif

void MutexClose(tHMutex *hMutex);                    /* detach from a mutex */

LZSBOOL MutexRequest(tHMutex hMutex, LZSDWORD dwTimeoutMs);    /* try locking the mutex (blocks until available, or timeout is reached). Does not block if timeout is 0 */
LZSBOOL MutexRequestNonBlocking(tHMutex hMutex);


LZSBOOL    MutexRelease(tHMutex hMutex);    /* try releasing the mutex (blocks until available) */

/* ------------------------------------------------------------ */

/* -------------------------------------------------------------- */
/* events 
   usable from different processes
*/
LZSBOOL EventCreate(int nEventId, tHEvent* hEvent);
void EventDestroy(tHEvent *hEvent);
LZSBOOL IsEventSignalled(tHEvent hEvent, LZSDWORD dwTimeoutMs);    
LZSBOOL SignalEvent(tHEvent hEvent);
/* -------------------------------------------------------------- */
/* shared memory wrapper */

LZSBOOL SharedMemCreate(int nId, unsigned long lSize, tHShm *phShm, void **pMem);    /* create and attach new shared mem segment */
void SharedMemDestroy(tHShm *phShm, void **pAddr);            /* detach and remove a shared mem segment created with CreateSharedMem() */

#ifndef UNDER_CE
LZSBOOL SharedMemOpen(int nId, unsigned long lSize, tHShm *phShm, void **pMem);    /* attach to an already existant shared mem segment */
#endif

void SharedMemClose(tHShm *phShm, void **pAddr);            /* detach from a segment */

/* ------------------------------------------------------------ */

#ifdef __cplusplus
};
#endif

#endif
