
/******************************************************************************
 *  (c) 2003 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *
 *  PROJECT: OpenPCS runtime system
 *
 *  DESCRIPTION:    table of funtion pointer of firmware FB
 *
 *****************************************************************************/
/*#define SMARTPLC_TRACE         */

#include    "oem/config.h"        /* configuration defines */
#include    "oem/odk_prj.h"
#include    "smartplc/odk_plc.h"
#include    "smartplc/lzs.h"
#include    "smartplc/iec_fb.h"    /* infoteam firmware */
#include    "oem/oem_fb.h"        /* OEM firmware*/
#include    "smartplc/external.h"





/*--------------------------------------------------------------------------- */
/*  tables with function pointers to firmware fb                             */
/*--------------------------------------------------------------------------- */


/* Hint:        The position of a fb address in the table corresponds
                with the index entry in hardware description file.
                The entry group tells the compiler which table should be
                used
                    0    = StandardFBTab_g
                    1    = InfoteamFBTab_g
                    2    = Oem1FBTab_g
                    3    = Oem2FBTab_g
                Table 0 and 1 should not be modified by the OEM. The OEM
                should place its firmware FBs to the Table 2 and 3. This
                ensures that the OEM has not to rearrange his FB index, when
                a new version of the runtime system is deliverd
*/
/*
 *    tLzsIecFB  LZSCONST  StandardFBTab_g[] =
 *
 * see stdfbtab.c
 */

/*
 *    tLzsIecFB  LZSCONST  InfoteamFBTab_g[] =
 *
 * see stdfbtab.c
 */
#if 1
static tLzsIecFB  LZSCONST  Oem1FBTab_g[] =
{
	FB_GETSYSTEMDATEANDTIME,	/* Index=0  : OEM-Standard GETSYSTEMDATEANDTIME*/
	FB_SETSYSTEMDATEANDTIME,	/* Index=1  : OEM-Standard SETSYSTEMDATEANDTIME*/
	LZSNULL,	/* Index=2  : *** UNUSED *** */
	LZSNULL,	/* Index=3  : *** UNUSED *** */
	LZSNULL,	/* Index=4  : *** UNUSED *** */
	LZSNULL,	/* Index=5  : *** UNUSED *** */
	LZSNULL,	/* Index=6  : *** UNUSED *** */
	LZSNULL,	/* Index=7  : *** UNUSED *** */
	LZSNULL,	/* Index=8  : *** UNUSED *** */
	LZSNULL,	/* Index=9  : *** UNUSED *** */

};
static tLzsIecFB  LZSCONST  Oem2FBTab_g[] =
{
	LZSNULL,	/* Index=0  : *** UNUSED *** */

};
#endif
extern tLzsIecFB LZSCONST* sysBKLoadOemFBTable(int* size);
extern tLzsIecFB LZSCONST* sysBKLoadAppFBTable(int* size);

void  LzsSetOEMFBTable (void)
{
	int setOk=0;
/* This function will be called on startup to initialize firmware function
   block jump table.
*/
#if 1

	if(sysBKLoadOemFBTable)
	{
		int size=0;
		tLzsIecFB * p=(tLzsIecFB *)sysBKLoadOemFBTable(&size);
		if(p&&size>0)
		{
			LZSWORD sz=(LZSWORD)size;
			  wFBTabEntrys_l[2] = sz;  /* determine number of table entries */
			  fpIecFBTab_l[2]   = p;
			  setOk=1;
		}
	}
/*如果没有正确安装则使用默认的*/
	if(setOk==0)
	{     logMsg("USE OLD GRP 2\n");
		  wFBTabEntrys_l[2]    = sizeof(Oem1FBTab_g) / sizeof(tLzsIecFB);  /* determine number of table entries */
		   fpIecFBTab_l[2]   = (tLzsIecFB LZSCONST*)&Oem1FBTab_g;
	}

#endif
}

void LzsSetOEMFBTable2(void)
{
	int setOk=0;
/* This function will be called on startup to initialize firmware function
   block jump table.
*/
#if 1

	if(sysBKLoadAppFBTable)
	{
		int size=0;
		tLzsIecFB * p=(tLzsIecFB *)sysBKLoadAppFBTable(&size);
		if(p&&size>0)
		{
			LZSWORD sz=(LZSWORD)size;
			  wFBTabEntrys_l[3] = sz;  /* determine number of table entries */
			  fpIecFBTab_l[3]   = p;
			  setOk=1;
		}
	}
/*如果没有正确安装则使用默认的*/
	if(setOk==0)
	{
		  wFBTabEntrys_l[3]    = sizeof(Oem2FBTab_g) / sizeof(tLzsIecFB);  /* determine number of table entries */
		   fpIecFBTab_l[3]   = (tLzsIecFB LZSCONST*)&Oem2FBTab_g;
	}
	{
		int i=0;
	for(i=0;i<4;i++)
	{
		logMsg("Grp %d (begin:0x%08x): %03d FBs\n",i,fpIecFBTab_l[i],wFBTabEntrys_l[i],4,5,6);
	}
	}
#endif

}

