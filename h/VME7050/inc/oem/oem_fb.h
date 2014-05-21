/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 9 , D-91088 Bubenreuth                     */
/* (C) 2003-                                                                     */
/*                                                                               */
/*                                                                               */
/* DESCRIPTION:  Header for OEM Firmware Function Blocks Prototypes              */
/*********************************************************************************/

#ifndef _OEM_FB_H_
#define _OEM_FB_H_

#ifdef __cplusplus
   extern "C" {
#endif

/*-----------removed here by yuhai from oemfb.c--------20100819----*/
#include    "oem/config.h"
#include    "oem/odk_prj.h"
#include    "smartplc/odk_plc.h"
#include    "smartplc/iec_fb.h"
#include    "oem/oem_fb.h"
#include    "smartplc/lzs.h"
#include    "smartplc/odk_szm.h"
#include    "smartplc/external.h"
#include    "smartplc/stdfct.h"
#include    "oem/xjvme7050config.h"

#include    "tskScheduler/userConfig.h"
#include    "tskScheduler/tskConfig.h"
#include    "tskScheduler/tskScheduler.h"

#ifndef _LZS_NOSTDLIB_
#include    <stdlib.h>
#define      MAX_SLOTS 10
#endif
/*-------------------------------------------------------------------*/



LZSBYTE Test1(void);



#ifdef __cplusplus
   }
#endif

#endif /*_OEM_FB_H_*/
