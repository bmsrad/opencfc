#ifndef _STDFCT_H_
#define _STDFCT_H_

typedef struct {
    LZSLONG quot;
    LZSLONG rem;
}
LZSLDIV_T;

#ifdef _LZS_NOSTDLIB_
#ifndef _SIZE_T_DEFINED
/* already defined in rmos */
#ifndef _IMC1000_
#if !defined _SIZE_T_DEFINED && !defined _SIZE_T
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
/* [SYSTEC: 17.09.2001 -rs]: #define _SIZE_T inserted because of C166; should better be moved to OEM-branch!!! */
#define _SIZE_T
#endif
#endif
#endif
#else /* _LZS_NOSTDLIB_ */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* #include <memory.h> */
#include <ctype.h>
#endif /* _LZS_NOSTDLIB_ */

LZSINT lzs_abs(LZSINT iValue);
LZSLONG lzs_labs(LZSLONG lValue);
void LZSFAR* lzs_memcpy (void LZSFAR* pDst, LZSCONST void LZSFAR* pSrc, size_t wLen);
void LZSFAR* lzs_memset (void LZSFAR* pDst, LZSINT iSet, size_t wLen);
void LZSFAR* lzs_memmove (void LZSFAR* pDst, LZSCONST void LZSFAR *pSrc, size_t wLen);

/* [SYSTEC: 11.06.2004 -rs]: Function <memcmp> newly inserted */
int lzs_memcmp (LZSCONST void LZSFAR* pBuff1_p, LZSCONST void LZSFAR *pBuff2_p, size_t wLen_p);
LZSCHAR LZSFAR *lzs_strcpy(LZSCHAR LZSFAR *pDst,  LZSCONST LZSCHAR LZSFAR *pSrc);
size_t lzs_strlen(LZSCONST LZSCHAR LZSFAR* pStr);

LZSCHAR LZSFAR *lzs_strcat(LZSCHAR LZSFAR *s, LZSCONST LZSCHAR LZSFAR  *a);
LZSCHAR LZSFAR *lzs_strncat(LZSCHAR LZSFAR *pDst, LZSCONST LZSCHAR LZSFAR *pApp, size_t n);
LZSCHAR LZSFAR *lzs_strncpy(LZSCHAR LZSFAR *pDst, LZSCONST LZSCHAR LZSFAR *pSrc, size_t n);
LZSINT lzs_strcmp(LZSCONST LZSCHAR LZSFAR *s,LZSCONST LZSCHAR LZSFAR *t);
LZSINT lzs_strncmp(LZSCONST LZSCHAR LZSFAR *s,LZSCONST LZSCHAR LZSFAR *t,size_t n);
LZSINT lzs_stricmp(LZSCONST LZSCHAR LZSFAR *s,LZSCONST LZSCHAR LZSFAR *t);
LZSINT lzs_strnicmp(LZSCONST LZSCHAR LZSFAR *s,LZSCONST LZSCHAR LZSFAR *t,size_t n);

LZSCHAR LZSFAR *lzs_strstr(LZSCONST LZSCHAR LZSFAR *s, LZSCONST LZSCHAR LZSFAR *find);
LZSCHAR LZSFAR *lzs_itoa( LZSINT n,LZSCHAR LZSFAR *s, LZSINT b);
LZSCHAR LZSFAR *lzs_ultoa(LZSDWORD N, LZSCHAR LZSFAR *str, LZSINT base);

LZSINT lzs_isspace(LZSINT c);
LZSINT lzs_isascii(LZSINT c);
LZSINT lzs_isdigit(LZSINT c);
LZSINT lzs_isxdigit(LZSINT c);
LZSINT lzs_isalpha(LZSINT c);
LZSINT lzs_isupper(LZSINT c);
LZSINT lzs_islower(LZSINT c);
LZSINT lzs_tolower(LZSINT c);
LZSINT lzs_toupper(LZSINT c);
LZSLDIV_T lzs_ldiv(LZSLONG num, LZSLONG denom);
LZSLONG lzs_strtol(LZSCONST LZSCHAR LZSFAR* p, LZSCHAR LZSFAR** pEnd, LZSINT base);
LZSLONG lzs_strtoul(LZSCONST LZSCHAR LZSFAR* p, LZSCHAR LZSFAR** pEnd, LZSINT base);
LZSDOUBLE lzs_strtod(LZSCONST LZSCHAR LZSFAR* pString, LZSCHAR LZSFAR** pEnd);
LZSDOUBLE lzs_atof(LZSCONST LZSCHAR LZSFAR* pString);
LZSLONG lzs_atol(LZSCONST LZSCHAR LZSFAR* str);
LZSINT lzs_atoi(LZSCONST LZSCHAR LZSFAR* str);
LZSCHAR LZSFAR* lzs_ltoa(LZSLONG N, LZSCHAR LZSFAR*str, LZSINT base);

#ifdef _LZS_NOSTDLIB_
/*types*/
#define        ldiv_t    LZSLDIV_T

/*functions*/
#define        memcpy    lzs_memcpy
#define        memmove lzs_memmove
#define     memcmp  lzs_memcmp
#define        memset    lzs_memset
#define        strcpy    lzs_strcpy
#define        strncpy    lzs_strncpy
#define        strcmp    lzs_strcmp
#define        strncmp    lzs_strncmp
#define        stricmp    lzs_stricmp
#define        strnicmp    lzs_strnicmp
#define        strcat    lzs_strcat
#define        strncat    lzs_strncat
#define        strstr    lzs_strstr
#define        strlen    lzs_strlen
#define        ldiv    lzs_ldiv
#define        atol    lzs_atol
#define        atoi    lzs_atoi
#define        strtol    lzs_strtol
#define        strtoul    lzs_strtoul
#define        strtod    lzs_strtod
#define        atof    lzs_atof
#define        isspace    lzs_isspace
#define        isascii    lzs_isascii
#define        isdigit    lzs_isdigit
#define        isxdigit lzs_isxdigit
#define        isalpha    lzs_isalpha
#define        isupper    lzs_isupper
#define        islower    lzs_islower
#define        tolower    lzs_tolower
#define        toupper    lzs_toupper
#define        memcpy    lzs_memcpy
#define        Abs        lzs_abs /*do not use abs; conflict with math.h*/
#define        labs    lzs_labs
#define        ltoa    lzs_ltoa
#define        ultoa    lzs_ultoa
#define        itoa    lzs_itoa
#define        itoab    lzs_itoab
#else                  
#ifdef _WIN32
#define itoa _itoa
#define ltoa _ltoa
#define ultoa _ultoa
#define stricmp _stricmp
#define strnicmp _strnicmp
#else    /* not _WIN32 */
/* since itoa, ultoa and stricmp are not part of the ansi C stdlib */
/* these will be mapped to the lzs_ -versions */
#define        itoa    lzs_itoa
#define        ltoa    lzs_ltoa
#define        ultoa    lzs_ultoa
#define        stricmp    lzs_stricmp
#define        strnicmp    lzs_strnicmp
#endif    /* _WIN32 */
#define        Abs        abs
#endif

#endif /*_STDFCT_H_*/
