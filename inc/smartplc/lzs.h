/****************************************************************************

   Definitionfile for system independed RTS

   18.08.1997   -rs

****************************************************************************/

#ifndef _LZS_H_
#define _LZS_H_



#include "p163ip/ip_def.h"                    /* typedefs of the ip */
#include "smartplc/odk_szm.h"                        /* function prototypes, typedefs and macros for memory access */

#include "smartplc/lzsdefs.h"                              /* defines and macros for the runtime system */
#include "smartplc/lzstypes.h"                            /* structs, enums and typedefs */
#include "smartplc/stdfct.h"                            

#ifdef __cplusplus
   extern "C" {
#endif 
#include "smartplc/lzscom.h"                                /* controling the RT and handling CSV and DSV */
#include "smartplc/lzsbreak.h"                            /* functions to implement breakpoints*/
#include "smartplc/lzsenv.h"                                /* functions provided by the environment */
#include "smartplc/lzsstate.h"                            /* functions to control program flow */
#include "smartplc/lzsinf.h"                                /* functions to provide information */
#include "smartplc/lzsip.h"                                  /* functions to control the IP */
#include "smartplc/lzsdwl.h"                                /* functions to manage the download */
#include "smartplc/lzsupl.h"                                /* functions to manage the upload */
#include "smartplc/lzstable.h"                            /* functions for handling the segment and task definition tables */
#include "smartplc/lzswatch.h"                            /* functions providing watch data */
#include "smartplc/lzspflow.h"                            /* functions providing powerflow data */
#include "smartplc/lzsprimg.h"                            /* functions to access the process image */
#include "smartplc/lzsfirm.h"                              /* functions to access firmware FBs and functions */
#include "smartplc/lzspers.h"                              /* functions to make IEC program persistent */
#include "smartplc/lzsncc.h"                                /* functions for native code */
#include "smartplc/lzsvar.h"                                /* functions for accessing var table */
#include "smartplc/lzsforce.h"                            /* functions for forcing vars */
#include "smartplc/lzsnet.h"                                /* functions for network variables */
#include "smartplc/errlog.h"                 /* functions for error-log */
/* */
/* functions to adapt to different expansion stages of the firmware */
/* */

#ifdef __cplusplus
   }
#endif 


#define _LZS_RELEASE_VERSION 610


#endif  /* ifndef _LZS_H_ */


