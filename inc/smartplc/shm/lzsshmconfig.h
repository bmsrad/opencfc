/******************************************************************************
 * (c) 2006 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 * DESCRIPTION: configuration file for shared memory interface
 *  
 *****************************************************************************/
 
#ifndef _LZSSHMCONFIG_H_
#define _LZSSHMCONFIG_H_

/* allow only global variables */
#undef LZS_SHM_FILTER_GLOBALVARS_VARTAB

/* prog-nr needed to identify the data segments task specific */
#define LZS_SHM_USE_PROG_NR

#ifndef LZS_SHM_USE_PROG_NR
/* without using prog-nr, only global variables can be supported */
#define LZS_SHM_FILTER_GLOBALVARS_VARTAB
#endif

/* support for arrays ? */
#define LZS_SHM_SUPPORT_ARRAYS

/* support for multi-VarTab */
#define LZS_SHM_SUPPORT_MULTI_VARTAB

/* support for optimized write requests in separate shmem */
#define LZS_SHM_SUPPORT_OPTIMIZED_WRITE

/* return the datatype in shmem LZS-out*/
#define LZS_SHM_SET_DATATYPE_SHMOUT

#endif