/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Do, 11 Mrz  99                                                                */
/*    13.11.1996   -rs                                                           */
/* DESCRIPTION:  OS specific and compiler dependend defines                      */
/*********************************************************************************/

   
#ifndef _ODK_PRJ_H_
#define _ODK_PRJ_H_

#ifndef _CONFIG_H_
#include "oem/config.h"
#endif

/* define this to use the standard functions delivered with the runtime system */
#undef _LZS_NOSTDLIB_

/* define this if the platform does not support errno.h */
#undef _LZS_NO_ERRNO_

/* define this if using Code Composer Studio 2000 compiler*/
#undef _CC_2000_
    
    #define LZSNEAR
    #define LZSFAR
    #define LZSCONST const
    #define LZSSTATIC static
    #define LZSPUBLIC
    #define LZSPUBLIC32
    #define LZSHUGE
    #define LZSLARGE
    #define _LDIV_SUPPORTED_
      
/* trace definitions */
#include "oem/trace.h"

#endif  /* ifndef _ODK_PRJ_H_ */
