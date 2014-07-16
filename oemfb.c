
/******************************************************************************
 *  (c) 2003 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *
 *  PROJECT: OpenPCS runtime system
 *
 *  DESCRIPTION:    table of funtion pointer of firmware FB
 *
 *
 ******************************************************************************
 *
 *  $Log:   O:/infoteam/pvcs/archives/infoteam/v400/Smart.PLC/OEM/oemfbtab.c-arc  $
 *
 *    Rev 1.1   Dec 23 2003 16:15:18   Magg
 * german comments translated
 *
 *    Rev 1.0   18 Aug 2003 12:23:36   Gumbmann
 * Initial revision.
 *
 *****************************************************************************/

/*#define SMARTPLC_TRACE         */
#include    "oem/config.h"        /* configuration defines */
#include    "oem/odk_prj.h"
#include    "smartplc/odk_plc.h"
#include    "smartplc/lzs.h"
#include    "smartplc/iec_fb.h"    /* infoteam firmware */
#include    "smartplc/external.h"



const char* bkcfcIdent(){
	static char version[]="Made on " __DATE__ " " __TIME__ ;
	return version;
	};
#define TESTFUNCTION_IINPUT1	0xc
#define TESTFUNCTION_IINPUT2	0xe
#define TESTFUNCTION_IOUT1	0x8

LZSBYTE FB_ADD_I(void)/*对新声明的功能块进行定义*/
{
	int in1, in2;
	int out1, out2;
	in1 = GETINT(TESTFUNCTION_IINPUT1);
	in2 = GETINT(TESTFUNCTION_IINPUT2);
	out1 = in1 + in2;
	SETINT(TESTFUNCTION_IOUT1, out1);
	return (kIecOK);
}
#if 1
LZSBYTE FB_GETSYSTEMDATEANDTIME(void)/*group:2 index:000*/
{
	logMsg("FB_GETSYSTEMDATEANDTIME\n",1,2,3,4,5,6);
	return (kIecOK);
}
LZSBYTE FB_SETSYSTEMDATEANDTIME(void)/*group:2 index:001*/
{
	return (kIecOK);
}

#endif

