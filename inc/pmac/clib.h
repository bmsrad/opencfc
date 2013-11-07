
#ifndef _PMAC_CLIB_H_
#define _PMAC_CLIB_H_

#ifdef _WIN32
  LZSBOOL int24_test( LZSINT24 a );

#else

int abs(int a);
long int labs( long int a);

int div_iii(int q,int d);
unsigned int div_uiuiui(unsigned int q,unsigned int d);
long div_lll(long q,long d);
unsigned long div_ululul(unsigned long q,unsigned long d);
int mod_iii(int q,int d);
unsigned int mod_uiuiui(unsigned int q,unsigned int d);
long mod_lll(long q,long d);
unsigned long mod_ululul(unsigned long q,unsigned long d);

PMAC_FLOAT fpaddf2(PMAC_FLOAT a,PMAC_FLOAT b);
PMAC_FLOAT fpsubf2(PMAC_FLOAT a,PMAC_FLOAT b);
PMAC_FLOAT fpmulf2(PMAC_FLOAT a,PMAC_FLOAT b);
PMAC_FLOAT fpdivf2(PMAC_FLOAT a,PMAC_FLOAT b);
PMAC_FLOAT fabs_pmac(PMAC_FLOAT a);
int fpcmpf2(PMAC_FLOAT a,PMAC_FLOAT b);
PMAC_FLOAT exp_pmac(PMAC_FLOAT a);
PMAC_FLOAT sqrt_pmac(PMAC_FLOAT a);
PMAC_FLOAT log_pmac(PMAC_FLOAT a);
PMAC_FLOAT sin_pmac(PMAC_FLOAT a);
PMAC_FLOAT cos_pmac(PMAC_FLOAT a);
PMAC_FLOAT tan_pmac(PMAC_FLOAT a);
PMAC_FLOAT asin_pmac(PMAC_FLOAT a);
PMAC_FLOAT acos_pmac(PMAC_FLOAT a);
PMAC_FLOAT atan_pmac(PMAC_FLOAT a);
LZSDWORD fpcfu22(PMAC_FLOAT a);
PMAC_FLOAT fpcuf22(LZSDWORD a);
PMAC_FLOAT pow_pmac(PMAC_FLOAT a,PMAC_FLOAT b);
#endif
#endif
