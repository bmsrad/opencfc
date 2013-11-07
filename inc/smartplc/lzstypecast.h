#ifndef _LZSTYPECAST_H_
#define _LZSTYPECAST_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/*                                                                               */
/* DESCRIPTION:    command routines for the IEC1131 runtime kernel                 */
/*********************************************************************************/

#include    "oem/config.h"           /* configuration defines */
#include    "oem/odk_prj.h"            /* P158 global */
#include    "smartplc/odk_plc.h"       /* P158 global */
#include    "p163ip/ip_def.h"

 
#ifdef _IP_FLOAT_
LZSBYTE lzs_ftostr(float fValue, LZSCHAR LZSFAR* pszNum);
#endif

#ifdef _IP_8BYTEDATA_
LZSBYTE lzs_dtostr(double dValue, LZSCHAR LZSFAR* pszNum);
#endif

LZSBYTE lzs_typecast_numeric(LZSBYTE bCastFrom, LZSBYTE bCastTo, tIpAE in, tIpAE *out);

#ifdef USE_BL_CODE
LZSBYTE lzs_typecast_numeric_BL(LZSBYTE bCastFrom, LZSBYTE bCastTo, void* pSource, void* pDestination);
#endif

#ifdef _IP_STRING_ 
LZSBYTE lzs_typecast_tostring(LZSBYTE bCastFrom, tIpAE in, LZSCHAR* out);
LZSBYTE lzs_typecast_fromstring(LZSBYTE bCastTo, LZSCHAR* in, tIpAE* out);
#endif

#endif /* _LZSTYPECAST_H_ */

