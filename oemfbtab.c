
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
tLzsIecFB  LZSCONST  Oem1FBTab_g[] =
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
	LZSNULL,	/* Index=10 : *** UNUSED *** */
	LZSNULL,	/* Index=11 : *** UNUSED *** */
	LZSNULL,	/* Index=12 : *** UNUSED *** */
	LZSNULL,	/* Index=13 : *** UNUSED *** */
	LZSNULL,	/* Index=14 : *** UNUSED *** */
	LZSNULL,	/* Index=15 : *** UNUSED *** */
	LZSNULL,	/* Index=16 : *** UNUSED *** */
	LZSNULL,	/* Index=17 : *** UNUSED *** */
	LZSNULL,	/* Index=18 : *** UNUSED *** */
	LZSNULL,	/* Index=19 : *** UNUSED *** */
	LZSNULL,	/* Index=20 : *** UNUSED *** */
	LZSNULL,	/* Index=21 : *** UNUSED *** */
	LZSNULL,	/* Index=22 : *** UNUSED *** */
	LZSNULL,	/* Index=23 : *** UNUSED *** */
	LZSNULL,	/* Index=24 : *** UNUSED *** */
	LZSNULL,	/* Index=25 : *** UNUSED *** */
	LZSNULL,	/* Index=26 : *** UNUSED *** */
	LZSNULL,	/* Index=27 : *** UNUSED *** */
	LZSNULL,	/* Index=28 : *** UNUSED *** */
	LZSNULL,	/* Index=29 : *** UNUSED *** */
	LZSNULL,	/* Index=30 : *** UNUSED *** */
	LZSNULL,	/* Index=31 : *** UNUSED *** */
	LZSNULL,	/* Index=32 : *** UNUSED *** */
	LZSNULL,	/* Index=33 : *** UNUSED *** */
	LZSNULL,	/* Index=34 : *** UNUSED *** */
	LZSNULL,	/* Index=35 : *** UNUSED *** */
	LZSNULL,	/* Index=36 : *** UNUSED *** */
	LZSNULL,	/* Index=37 : *** UNUSED *** */
	LZSNULL,	/* Index=38 : *** UNUSED *** */
	LZSNULL,	/* Index=39 : *** UNUSED *** */
	LZSNULL,	/* Index=40 : *** UNUSED *** */
	LZSNULL,	/* Index=41 : *** UNUSED *** */
	LZSNULL,	/* Index=42 : *** UNUSED *** */
	LZSNULL,	/* Index=43 : *** UNUSED *** */
	LZSNULL,	/* Index=44 : *** UNUSED *** */
	LZSNULL,	/* Index=45 : *** UNUSED *** */
	LZSNULL,	/* Index=46 : *** UNUSED *** */
	LZSNULL,	/* Index=47 : *** UNUSED *** */
	LZSNULL,	/* Index=48 : *** UNUSED *** */
	LZSNULL,	/* Index=49 : *** UNUSED *** */
	LZSNULL,	/* Index=50 : *** UNUSED *** */
	LZSNULL,	/* Index=51 : *** UNUSED *** */
	LZSNULL,	/* Index=52 : *** UNUSED *** */
	LZSNULL,	/* Index=53 : *** UNUSED *** */
	LZSNULL,	/* Index=54 : *** UNUSED *** */
	LZSNULL,	/* Index=55 : *** UNUSED *** */
	LZSNULL,	/* Index=56 : *** UNUSED *** */
	LZSNULL,	/* Index=57 : *** UNUSED *** */
	LZSNULL,	/* Index=58 : *** UNUSED *** */
	LZSNULL,	/* Index=59 : *** UNUSED *** */
	LZSNULL,	/* Index=60 : *** UNUSED *** */
	LZSNULL,	/* Index=61 : *** UNUSED *** */
	LZSNULL,	/* Index=62 : *** UNUSED *** */
	LZSNULL,	/* Index=63 : *** UNUSED *** */
	LZSNULL,	/* Index=64 : *** UNUSED *** */
	LZSNULL,	/* Index=65 : *** UNUSED *** */
	LZSNULL,	/* Index=66 : *** UNUSED *** */
	LZSNULL,	/* Index=67 : *** UNUSED *** */
	LZSNULL,	/* Index=68 : *** UNUSED *** */
	LZSNULL,	/* Index=69 : *** UNUSED *** */
	LZSNULL,	/* Index=70 : *** UNUSED *** */
	LZSNULL,	/* Index=71 : *** UNUSED *** */
	LZSNULL,	/* Index=72 : *** UNUSED *** */
	LZSNULL,	/* Index=73 : *** UNUSED *** */
	LZSNULL,	/* Index=74 : *** UNUSED *** */
	LZSNULL,	/* Index=75 : *** UNUSED *** */
	LZSNULL,	/* Index=76 : *** UNUSED *** */
	LZSNULL,	/* Index=77 : *** UNUSED *** */
	LZSNULL,	/* Index=78 : *** UNUSED *** */
	LZSNULL,	/* Index=79 : *** UNUSED *** */
	LZSNULL,	/* Index=80 : *** UNUSED *** */
	LZSNULL,	/* Index=81 : *** UNUSED *** */
	LZSNULL,	/* Index=82 : *** UNUSED *** */
	LZSNULL,	/* Index=83 : *** UNUSED *** */
	LZSNULL,	/* Index=84 : *** UNUSED *** */
	LZSNULL,	/* Index=85 : *** UNUSED *** */
	LZSNULL,	/* Index=86 : *** UNUSED *** */
	LZSNULL,	/* Index=87 : *** UNUSED *** */
	LZSNULL,	/* Index=88 : *** UNUSED *** */
	LZSNULL,	/* Index=89 : *** UNUSED *** */
	LZSNULL,	/* Index=90 : *** UNUSED *** */
	LZSNULL,	/* Index=91 : *** UNUSED *** */
	LZSNULL,	/* Index=92 : *** UNUSED *** */
	LZSNULL,	/* Index=93 : *** UNUSED *** */
	LZSNULL,	/* Index=94 : *** UNUSED *** */
	LZSNULL,	/* Index=95 : *** UNUSED *** */
	LZSNULL,	/* Index=96 : *** UNUSED *** */
	LZSNULL,	/* Index=97 : *** UNUSED *** */
	LZSNULL,	/* Index=98 : *** UNUSED *** */
	LZSNULL,	/* Index=99 : *** UNUSED *** */
	LZSNULL,	/* Index=100: *** UNUSED *** */
	FB_DT10F,	/* Index=101: OEM-Standard DT10F*/
	FB_PC_3F,	/* Index=102: OEM-Standard PC_3F*/
	FB_PWM0F,	/* Index=103: OEM-Standard PWM0F*/
	FB_ADD8F,	/* Index=104: OEM-Standard ADD8F*/
	FB_ADDI4,	/* Index=105: OEM-Standard ADDI4*/
	FB_SUBI,	/* Index=106: OEM-Standard SUBI*/
	FB_MULI,	/* Index=107: OEM-Standard MULI*/
	FB_MULI4,	/* Index=108: OEM-Standard MULI4*/
	FB_DIVI,	/* Index=109: OEM-Standard DIVI*/
	FB_PLI2F,	/* Index=110: OEM-Standard PLI2F*/
	FB_COS0F,	/* Index=111: OEM-Standard COS0F*/
	FB_ACOSF,	/* Index=112: OEM-Standard ACOSF*/
	FB_TAN0F,	/* Index=113: OEM-Standard TAN0F*/
	FB_ATANF,	/* Index=114: OEM-Standard ATANF*/
	FB_OR_22,	/* Index=115: OEM-Standard OR_22*/
	FB_NOT02,	/* Index=116: OEM-Standard NOT02*/
	FB_PIN8,	/* Index=117: OEM-Standard PIN8*/
	FB_FUI,	/* Index=118: OEM-Standard FUI*/
	FB_UDI,	/* Index=119: OEM-Standard UDI*/
	FB_ANS0F,	/* Index=120: OEM-Standard ANS0F*/
	FB_DX_8F,	/* Index=121: OEM-Standard DX_8F*/
	FB_CNM0F,	/* Index=122: OEM-Standard CNM0F*/
	FB_DFR,	/* Index=123: OEM-Standard DFR*/
	FB_DFRV,	/* Index=124: OEM-Standard DFRV*/
	FB_SAV0F,	/* Index=125: OEM-Standard SAV0F*/
	FB_SBF0F,	/* Index=126: OEM-Standard SBF0F*/
	FB_CTB1,	/* Index=127: OEM-Standard CTB1*/
	FB_CTB2,	/* Index=128: OEM-Standard CTB2*/
	FB_CTBF,	/* Index=129: OEM-Standard CTBF*/
	FB_SWB,	/* Index=130: OEM-Standard SWB*/
	FB_WDC,	/* Index=131: OEM-Standard WDC*/
	FB_DWC04,	/* Index=132: OEM-Standard DWC04*/
	FB_DWR04,	/* Index=133: OEM-Standard DWR04*/
	LZSNULL,	/* Index=134: *** UNUSED *** */
	FB_N4NF,	/* Index=135: OEM-Standard N4NF*/
	FB_NFN4,	/* Index=136: OEM-Standard NFN4*/
	FB_CBR,	/* Index=137: OEM-Standard CBR*/
	FB_CBR04,	/* Index=138: OEM-Standard CBR04*/
	FB_CBRIF,	/* Index=139: OEM-Standard CBRIF*/
	FB_CBRQF,	/* Index=140: OEM-Standard CBRQF*/
	FB_BNR0F,	/* Index=141: OEM-Standard BNR0F*/
	FB_RGJ0F1,	/* Index=142: OEM-Standard RGJ0F1*/
	FB_ANS,	/* Index=143: OEM-Standard ANS*/
	FB_DX_8,	/* Index=144: OEM-Standard DX_8*/
	FB_CNM,	/* Index=145: OEM-Standard CNM*/
	FB_CNM04,	/* Index=146: OEM-Standard CNM04*/
	FB_SAV,	/* Index=147: OEM-Standard SAV*/
	FB_SAV01,	/* Index=148: OEM-Standard SAV01*/
	FB_SAV04,	/* Index=149: OEM-Standard SAV04*/
	FB_DLB0F,	/* Index=150: OEM-Standard DLB0F*/
	FB_DWS04,	/* Index=151: OEM-Standard DWS04*/
	LZSNULL,	/* Index=152: *** UNUSED *** */
	LZSNULL,	/* Index=153: *** UNUSED *** */
	LZSNULL,	/* Index=154: *** UNUSED *** */
	LZSNULL,	/* Index=155: *** UNUSED *** */
	LZSNULL,	/* Index=156: *** UNUSED *** */
	LZSNULL,	/* Index=157: *** UNUSED *** */
	LZSNULL,	/* Index=158: *** UNUSED *** */
	LZSNULL,	/* Index=159: *** UNUSED *** */
	LZSNULL,	/* Index=160: *** UNUSED *** */
	FB_ADK10,	/* Index=161: OEM-Standard ADK10*/
	FB_BMX8F,	/* Index=162: OEM-Standard BMX8F*/
	FB_BS16,	/* Index=163: OEM-Standard BS16*/
	FB_DSRW4,	/* Index=164: OEM-Standard DSRW4*/
	FB_DSWF,	/* Index=165: OEM-Standard DSWF*/
	FB_FSB,	/* Index=166: OEM-Standard FSB*/
	FB_FSS,	/* Index=167: OEM-Standard FSS*/
	FB_FTS8,	/* Index=168: OEM-Standard FTS8*/
	FB_MSAH0F,	/* Index=169: OEM-Standard MSAH0F*/
	FB_PETR,	/* Index=170: OEM-Standard PETR*/
	FB_SET2,	/* Index=171: OEM-Standard SET2*/
	FB_SET4,	/* Index=172: OEM-Standard SET4*/
	FB_SET0F,	/* Index=173: OEM-Standard SET0F*/
	FB_SEQ,	/* Index=174: OEM-Standard SEQ*/
	FB_ZWE8,	/* Index=175: OEM-Standard ZWE8*/
	FB_MRV2,	/* Index=176: OEM-Standard MRV2*/
	FB_MWV2,	/* Index=177: OEM-Standard MWV2*/
	FB_GMI,	/* Index=178: OEM-Standard GMI*/
	FB_GPB,	/* Index=179: OEM-Standard GPB*/
	FB_GSC,	/* Index=180: OEM-Standard GSC*/
	FB_MNCB,	/* Index=181: OEM-Standard MNCB*/
	FB_MOB3,	/* Index=182: OEM-Standard MOB3*/
	FB_MPB,	/* Index=183: OEM-Standard MPB*/
	LZSNULL,	/* Index=184: *** UNUSED *** */
	FB_PMA,	/* Index=185: OEM-Standard PMA*/
	FB_UDR,	/* Index=186: OEM-Standard UDR*/
	FB_UDW,	/* Index=187: OEM-Standard UDW*/
	FB_UMA,	/* Index=188: OEM-Standard UMA*/
	FB_B1V1,	/* Index=189: OEM-Standard B1V1*/
	FB_BCD,	/* Index=190: OEM-Standard BCD*/
	FB_BSCB,	/* Index=191: OEM-Standard BSCB*/
	FB_BSC8,	/* Index=192: OEM-Standard BSC8*/
	FB_NFV4,	/* Index=193: OEM-Standard NFV4*/
	FB_SBC8,	/* Index=194: OEM-Standard SBC8*/
	FB_TIC,	/* Index=195: OEM-Standard TIC*/
	FB_V1B1,	/* Index=196: OEM-Standard V1B1*/
	FB_V1V4,	/* Index=197: OEM-Standard V1V4*/
	FB_V2B1,	/* Index=198: OEM-Standard V2B1*/
	FB_V4NF,	/* Index=199: OEM-Standard V4NF*/
	FB_V4V1,	/* Index=200: OEM-Standard V4V1*/
	FB_TFI,	/* Index=201: OEM-Standard TFI*/
	FB_TFIS,	/* Index=202: OEM-Standard TFIS*/
	FB_TRC,	/* Index=203: OEM-Standard TRC*/
	FB_TTN,	/* Index=204: OEM-Standard TTN*/
	FB_MBSU,	/* Index=205: OEM-Standard MBSU*/
	LZSNULL,	/* Index=206: *** UNUSED *** */
	LZSNULL,	/* Index=207: *** UNUSED *** */
	LZSNULL,	/* Index=208: *** UNUSED *** */
	LZSNULL,	/* Index=209: *** UNUSED *** */
	LZSNULL,	/* Index=210: *** UNUSED *** */
	FB_BIOI,	/* Index=211: OEM-Standard BIOI*/
	FB_BII8,	/* Index=212: OEM-Standard BII8*/
	FB_BIQ8,	/* Index=213: OEM-Standard BIQ8*/
	FB_SBI,	/* Index=214: OEM-Standard SBI*/
	FB_SBQ,	/* Index=215: OEM-Standard SBQ*/
	FB_DORB,	/* Index=216: OEM-Standard DORB*/
	FB_BDAI,	/* Index=217: OEM-Standard BDAI*/
	FB_DAC0F,	/* Index=218: OEM-Standard DAC0F*/
	FB_IFCI,	/* Index=219: OEM-Standard IFCI*/
	FB_ICBI,	/* Index=220: OEM-Standard ICBI*/
	FB_ICBW2,	/* Index=221: OEM-Standard ICBW2*/
	FB_ICBS,	/* Index=222: OEM-Standard ICBS*/
	FB_ICBBD,	/* Index=223: OEM-Standard ICBBD*/
	FB_ICBR2,	/* Index=224: OEM-Standard ICBR2*/
	FB_TEST1_L,	/* Index=225: OEM-Standard TEST1_L*/
	LZSNULL,	/* Index=226: *** UNUSED *** */
	LZSNULL,	/* Index=227: *** UNUSED *** */
	LZSNULL,	/* Index=228: *** UNUSED *** */
	LZSNULL,	/* Index=229: *** UNUSED *** */
	LZSNULL,	/* Index=230: *** UNUSED *** */
	LZSNULL,	/* Index=231: *** UNUSED *** */
	LZSNULL,	/* Index=232: *** UNUSED *** */
	LZSNULL,	/* Index=233: *** UNUSED *** */
	LZSNULL,	/* Index=234: *** UNUSED *** */
	LZSNULL,	/* Index=235: *** UNUSED *** */
	FB_TSTART,	/* Index=236: OEM-Standard TSTART*/
	FB_TSTOP,	/* Index=237: OEM-Standard TSTOP*/
	FB_TASK_EXEC,	/* Index=238: OEM-Standard TASK_EXEC*/
	FB_TASK_LOCK,	/* Index=239: OEM-Standard TASK_LOCK*/
	FB_PRD_T,	/* Index=240: OEM-Standard PRD_T*/
	FB_PRD_I1,	/* Index=241: OEM-Standard PRD_I1*/
	FB_PSWT_T,	/* Index=242: OEM-Standard PSWT_T*/
	FB_PRD_S,	/* Index=243: OEM-Standard PRD_S*/
	FB_SHM_T,	/* Index=244: OEM-Standard SHM_T*/
	FB_P_TEMP,	/* Index=245: OEM-Standard P_TEMP*/
	FB_PAS1,	/* Index=246: OEM-Standard PAS1*/
};
tLzsIecFB  LZSCONST  Oem2FBTab_g[] =
{
	LZSNULL,	/* Index=0  : *** UNUSED *** */
	FB_DRW,	/* Index=1  : OEM-Standard DRW*/
	FB_DSW,	/* Index=2  : OEM-Standard DSW*/
	FB_HPN,	/* Index=3  : OEM-Standard HPN*/
	FB_KRST,	/* Index=4  : OEM-Standard KRST*/
	FB_MF32,	/* Index=5  : OEM-Standard MF32*/
	FB_MGF,	/* Index=6  : OEM-Standard MGF*/
	FB_SDW,	/* Index=7  : OEM-Standard SDW*/
	FB_SPGA,	/* Index=8  : OEM-Standard SPGA*/
	FB_UVD,	/* Index=9  : OEM-Standard UVD*/
	FB_MF128,	/* Index=10 : OEM-Standard MF128*/
	FB_SPG,	/* Index=11 : OEM-Standard SPG*/
	FB_NCM_W,	/* Index=12 : OEM-Standard NCM_W*/
	LZSNULL,	/* Index=13 : *** UNUSED *** */
	LZSNULL,	/* Index=14 : *** UNUSED *** */
	FB_I2N2,	/* Index=15 : OEM-Standard I2N2*/
	LZSNULL,	/* Index=16 : *** UNUSED *** */
	LZSNULL,	/* Index=17 : *** UNUSED *** */
	LZSNULL,	/* Index=18 : *** UNUSED *** */
	LZSNULL,	/* Index=19 : *** UNUSED *** */
	FB_BAB,	/* Index=20 : OEM-Standard BAB*/
	FB_KPW,	/* Index=21 : OEM-Standard KPW*/
	FB_PKW,	/* Index=22 : OEM-Standard PKW*/
	FB_PSUB,	/* Index=23 : OEM-Standard PSUB*/
	FB_XPQ,	/* Index=24 : OEM-Standard XPQ*/
	FB_VDV,	/* Index=25 : OEM-Standard VDV*/
	FB_VIX,	/* Index=26 : OEM-Standard VIX*/
	LZSNULL,	/* Index=27 : *** UNUSED *** */
	LZSNULL,	/* Index=28 : *** UNUSED *** */
	LZSNULL,	/* Index=29 : *** UNUSED *** */
	FB_AVGN,	/* Index=30 : OEM-Standard AVGN*/
	FB_IIR2,	/* Index=31 : OEM-Standard IIR2*/
	FB_PINT,	/* Index=32 : OEM-Standard PINT*/
	FB_PT1,	/* Index=33 : OEM-Standard PT1*/
	FB_PT1D,	/* Index=34 : OEM-Standard PT1D*/
	LZSNULL,	/* Index=35 : *** UNUSED *** */
	LZSNULL,	/* Index=36 : *** UNUSED *** */
	LZSNULL,	/* Index=37 : *** UNUSED *** */
	LZSNULL,	/* Index=38 : *** UNUSED *** */
	LZSNULL,	/* Index=39 : *** UNUSED *** */
	FB_CSB001,	/* Index=40 : OEM-Standard CSB001*/
	FB_HLG,	/* Index=41 : OEM-Standard HLG*/
	FB_INT_1,	/* Index=42 : OEM-Standard INT_1*/
	FB_LIM,	/* Index=43 : OEM-Standard LIM*/
	FB_PICH,	/* Index=44 : OEM-Standard PICH*/
	FB_DEZ,	/* Index=45 : OEM-Standard DEZ*/
	FB_DEL,	/* Index=46 : OEM-Standard DEL*/
	FB_PIC2F,	/* Index=47 : OEM-Standard PIC2F*/
	FB_RGE,	/* Index=48 : OEM-Standard RGE*/
	LZSNULL,	/* Index=49 : *** UNUSED *** */
	FB_ADD2,	/* Index=50 : OEM-Standard ADD2*/
	FB_ADD4,	/* Index=51 : OEM-Standard ADD4*/
	FB_ASTI,	/* Index=52 : OEM-Standard ASTI*/
	FB_AVA,	/* Index=53 : OEM-Standard AVA*/
	FB_DIV2,	/* Index=54 : OEM-Standard DIV2*/
	FB_MAS,	/* Index=55 : OEM-Standard MAS*/
	FB_MAS3,	/* Index=56 : OEM-Standard MAS3*/
	FB_MAXN,	/* Index=57 : OEM-Standard MAXN*/
	FB_MIS,	/* Index=58 : OEM-Standard MIS*/
	FB_MULD,	/* Index=59 : OEM-Standard MULD*/
	FB_MULE2,	/* Index=60 : OEM-Standard MULE2*/
	FB_MUL2,	/* Index=61 : OEM-Standard MUL2*/
	FB_PLI6,	/* Index=62 : OEM-Standard PLI6*/
	FB_SII,	/* Index=63 : OEM-Standard SII*/
	FB_SUB2,	/* Index=64 : OEM-Standard SUB2*/
	LZSNULL,	/* Index=65 : *** UNUSED *** */
	LZSNULL,	/* Index=66 : *** UNUSED *** */
	FB_ADD_I,	/* Index=67 : OEM-Standard ADD_I*/
	FB_ADD_DI,	/* Index=68 : OEM-Standard ADD_DI*/
	LZSNULL,	/* Index=69 : *** UNUSED *** */
	FB_SUB_I,	/* Index=70 : OEM-Standard SUB_I*/
	FB_SUB_DI,	/* Index=71 : OEM-Standard SUB_DI*/
	LZSNULL,	/* Index=72 : *** UNUSED *** */
	LZSNULL,	/* Index=73 : *** UNUSED *** */
	LZSNULL,	/* Index=74 : *** UNUSED *** */
	LZSNULL,	/* Index=75 : *** UNUSED *** */
	LZSNULL,	/* Index=76 : *** UNUSED *** */
	LZSNULL,	/* Index=77 : *** UNUSED *** */
	LZSNULL,	/* Index=78 : *** UNUSED *** */
	LZSNULL,	/* Index=79 : *** UNUSED *** */
	FB_AND2,	/* Index=80 : OEM-Standard AND2*/
	FB_AND3,	/* Index=81 : OEM-Standard AND3*/
	FB_AND4,	/* Index=82 : OEM-Standard AND4*/
	FB_AND8,	/* Index=83 : OEM-Standard AND8*/
	FB_ANDS,	/* Index=84 : OEM-Standard ANDS*/
	FB_BSC,	/* Index=85 : OEM-Standard BSC*/
	FB_LVM,	/* Index=86 : OEM-Standard LVM*/
	FB_LVX,	/* Index=87 : OEM-Standard LVX*/
	FB_MOF,	/* Index=88 : OEM-Standard MOF*/
	FB_MUX8,	/* Index=89 : OEM-Standard MUX8*/
	FB_NOT1,	/* Index=90 : OEM-Standard NOT1*/
	FB_NOTS,	/* Index=91 : OEM-Standard NOTS*/
	FB_NSW,	/* Index=92 : OEM-Standard NSW*/
	FB_NCM,	/* Index=93 : OEM-Standard NCM*/
	FB_OR_2,	/* Index=94 : OEM-Standard OR_2*/
	FB_OR_3,	/* Index=95 : OEM-Standard OR_3*/
	FB_OR_6,	/* Index=96 : OEM-Standard OR_6*/
	FB_OR_S,	/* Index=97 : OEM-Standard OR_S*/
	FB_OR_12,	/* Index=98 : OEM-Standard OR_12*/
	FB_PCL,	/* Index=99 : OEM-Standard PCL*/
	FB_PDE,	/* Index=100: OEM-Standard PDE*/
	FB_PDF,	/* Index=101: OEM-Standard PDF*/
	FB_RSR,	/* Index=102: OEM-Standard RSR*/
	FB_RSS,	/* Index=103: OEM-Standard RSS*/
	FB_SBC,	/* Index=104: OEM-Standard SBC*/
	FB_AND5,	/* Index=105: OEM-Standard AND5*/
	FB_AND6,	/* Index=106: OEM-Standard AND6*/
	FB_AND7,	/* Index=107: OEM-Standard AND7*/
	FB_BSW,	/* Index=108: OEM-Standard BSW*/
	LZSNULL,	/* Index=109: *** UNUSED *** */
	FB_OR_9,	/* Index=110: OEM-Standard OR_9*/
	FB_OR_B,	/* Index=111: OEM-Standard OR_B*/
	FB_XOR_2,	/* Index=112: OEM-Standard XOR_2*/
	FB_MFP,	/* Index=113: OEM-Standard MFP*/
	FB_PST,	/* Index=114: OEM-Standard PST*/
	FB_ETE,	/* Index=115: OEM-Standard ETE*/
	FB_SBW,	/* Index=116: OEM-Standard SBW*/
	FB_LVM2F,	/* Index=117: OEM-Standard LVM2F*/
	FB_NSWD,	/* Index=118: OEM-Standard NSWD*/
	FB_OR_4,	/* Index=119: OEM-Standard OR_4*/
	FB_OR_8,	/* Index=120: OEM-Standard OR_8*/
	LZSNULL,	/* Index=121: *** UNUSED *** */
	FB_MUX8_W,	/* Index=122: OEM-Standard MUX8_W*/
	FB_MUX8_DW,	/* Index=123: OEM-Standard MUX8_DW*/
	FB_MUX8_I,	/* Index=124: OEM-Standard MUX8_I*/
	FB_MUX8_DI,	/* Index=125: OEM-Standard MUX8_DI*/
	FB_NSW_W,	/* Index=126: OEM-Standard NSW_W*/
	FB_NSW_DW,	/* Index=127: OEM-Standard NSW_DW*/
	FB_NSW_I,	/* Index=128: OEM-Standard NSW_I*/
	FB_NSW_DI,	/* Index=129: OEM-Standard NSW_DI*/
	FB_BBF0F,	/* Index=130: OEM-Standard BBF0F*/
	FB_NOR2,	/* Index=131: OEM-Standard NOR2*/
	FB_NOR4,	/* Index=132: OEM-Standard NOR4*/
	FB_NOR8,	/* Index=133: OEM-Standard NOR8*/
	LZSNULL,	/* Index=134: *** UNUSED *** */
	LZSNULL,	/* Index=135: *** UNUSED *** */
	LZSNULL,	/* Index=136: *** UNUSED *** */
	LZSNULL,	/* Index=137: *** UNUSED *** */
	LZSNULL,	/* Index=138: *** UNUSED *** */
	LZSNULL,	/* Index=139: *** UNUSED *** */
	FB_DUMY_1F,	/* Index=140: OEM-Standard DUMY_1F*/
	FB_DUMY_2F,	/* Index=141: OEM-Standard DUMY_2F*/
	FB_DUMY_8F,	/* Index=142: OEM-Standard DUMY_8F*/
	FB_DUMY_1I,	/* Index=143: OEM-Standard DUMY_1I*/
	FB_DUMY_2I,	/* Index=144: OEM-Standard DUMY_2I*/
	FB_DUMY_8I,	/* Index=145: OEM-Standard DUMY_8I*/
	FB_DUMY_1DI,	/* Index=146: OEM-Standard DUMY_1DI*/
	FB_DUMY_2DI,	/* Index=147: OEM-Standard DUMY_2DI*/
	FB_DUMY_8DI,	/* Index=148: OEM-Standard DUMY_8DI*/
	FB_DUMY_1W,	/* Index=149: OEM-Standard DUMY_1W*/
	FB_DUMY_2W,	/* Index=150: OEM-Standard DUMY_2W*/
	FB_DUMY_8W,	/* Index=151: OEM-Standard DUMY_8W*/
	FB_DUMY_1DW,	/* Index=152: OEM-Standard DUMY_1DW*/
	FB_DUMY_2DW,	/* Index=153: OEM-Standard DUMY_2DW*/
	FB_DUMY_8DW,	/* Index=154: OEM-Standard DUMY_8DW*/
	FB_DUMY_1B,	/* Index=155: OEM-Standard DUMY_1B*/
	FB_DUMY_8B,	/* Index=156: OEM-Standard DUMY_8B*/
	FB_DUMY_1D,	/* Index=157: OEM-Standard DUMY_1D*/
	FB_DUMY_2D,	/* Index=158: OEM-Standard DUMY_2D*/
	LZSNULL,	/* Index=159: *** UNUSED *** */
	LZSNULL,	/* Index=160: *** UNUSED *** */
	LZSNULL,	/* Index=161: *** UNUSED *** */
	LZSNULL,	/* Index=162: *** UNUSED *** */
	FB_N2NF,	/* Index=163: OEM-Standard N2NF*/
	FB_NFN2,	/* Index=164: OEM-Standard NFN2*/
	FB_I_R,	/* Index=165: OEM-Standard I_R*/
	FB_DI_R,	/* Index=166: OEM-Standard DI_R*/
	FB_R_I,	/* Index=167: OEM-Standard R_I*/
	FB_R_DI,	/* Index=168: OEM-Standard R_DI*/
	FB_I_W,	/* Index=169: OEM-Standard I_W*/
	FB_DI_DW,	/* Index=170: OEM-Standard DI_DW*/
	FB_W_I,	/* Index=171: OEM-Standard W_I*/
	FB_DW_DI,	/* Index=172: OEM-Standard DW_DI*/
	FB_F_I,	/* Index=173: OEM-Standard F_I*/
	FB_I_F,	/* Index=174: OEM-Standard I_F*/
	FB_SET_R,	/* Index=175: OEM-Standard SET_R*/
	LZSNULL,	/* Index=176: *** UNUSED *** */
	LZSNULL,	/* Index=177: *** UNUSED *** */
	LZSNULL,	/* Index=178: *** UNUSED *** */
	LZSNULL,	/* Index=179: *** UNUSED *** */
	FB_N2V2,	/* Index=180: OEM-Standard N2V2*/
	FB_V2N2,	/* Index=181: OEM-Standard V2N2*/
	FB_N4V4,	/* Index=182: OEM-Standard N4V4*/
	FB_V4N4,	/* Index=183: OEM-Standard V4N4*/
	FB_AIN,	/* Index=184: OEM-Standard AIN*/
	FB_BSC2,	/* Index=185: OEM-Standard BSC2*/
	FB_DISA,	/* Index=186: OEM-Standard DISA*/
	FB_DIV0F1,	/* Index=187: OEM-Standard DIV0F1*/
	FB_EXP1,	/* Index=188: OEM-Standard EXP1*/
	FB_IIR2S,	/* Index=189: OEM-Standard IIR2S*/
	FB_LVH,	/* Index=190: OEM-Standard LVH*/
	FB_NOP16W,	/* Index=191: OEM-Standard NOP16W*/
	FB_PSL,	/* Index=192: OEM-Standard PSL*/
	FB_PT1S,	/* Index=193: OEM-Standard PT1S*/
	FB_RVM,	/* Index=194: OEM-Standard RVM*/
	LZSNULL,	/* Index=195: *** UNUSED *** */
	LZSNULL,	/* Index=196: *** UNUSED *** */
	LZSNULL,	/* Index=197: *** UNUSED *** */
	LZSNULL,	/* Index=198: *** UNUSED *** */
	LZSNULL,	/* Index=199: *** UNUSED *** */
	LZSNULL,	/* Index=200: *** UNUSED *** */
	FB_DIO_INIT,	/* Index=201: OEM-Standard DIO_INIT*/
	FB_DI1,	/* Index=202: OEM-Standard DI1*/
	FB_DI8,	/* Index=203: OEM-Standard DI8*/
	FB_DI16,	/* Index=204: OEM-Standard DI16*/
	FB_DI32,	/* Index=205: OEM-Standard DI32*/
	FB_DO1,	/* Index=206: OEM-Standard DO1*/
	FB_DO8,	/* Index=207: OEM-Standard DO8*/
	FB_DO16,	/* Index=208: OEM-Standard DO16*/
	FB_DO32,	/* Index=209: OEM-Standard DO32*/
	FB_DA_INIT,	/* Index=210: OEM-Standard DA_INIT*/
	FB_DA_1,	/* Index=211: OEM-Standard DA_1*/
	FB_DA_4,	/* Index=212: OEM-Standard DA_4*/
	FB_DA_8,	/* Index=213: OEM-Standard DA_8*/
	FB_DA_16,	/* Index=214: OEM-Standard DA_16*/
	FB_ETHI,	/* Index=215: OEM-Standard ETHI*/
	FB_TGT_P,	/* Index=216: OEM-Standard TGT_P*/
	FB_TGR_P,	/* Index=217: OEM-Standard TGR_P*/
	FB_TGH3,	/* Index=218: OEM-Standard TGH3*/
	FB_TCP,	/* Index=219: OEM-Standard TCP*/
	FB_CRV_P,	/* Index=220: OEM-Standard CRV_P*/
	FB_CTV_P,	/* Index=221: OEM-Standard CTV_P*/
	FB_PRODP,	/* Index=222: OEM-Standard PRODP*/
	FB_RSUD,	/* Index=223: OEM-Standard RSUD*/
	FB_WSUD,	/* Index=224: OEM-Standard WSUD*/
	FB_DSURD,	/* Index=225: OEM-Standard DSURD*/
	FB_DSUWR,	/* Index=226: OEM-Standard DSUWR*/
	FB_DRD,	/* Index=227: OEM-Standard DRD*/
	FB_DRD_I,	/* Index=228: OEM-Standard DRD_I*/
	FB_DRD_DI,	/* Index=229: OEM-Standard DRD_DI*/
	FB_DRD_UI,	/* Index=230: OEM-Standard DRD_UI*/
	FB_DRD_UDI,	/* Index=231: OEM-Standard DRD_UDI*/
	FB_DRD_W,	/* Index=232: OEM-Standard DRD_W*/
	FB_DRD_DW,	/* Index=233: OEM-Standard DRD_DW*/
	FB_DRD_BY,	/* Index=234: OEM-Standard DRD_BY*/
	FB_DWR,	/* Index=235: OEM-Standard DWR*/
	FB_DWR_I,	/* Index=236: OEM-Standard DWR_I*/
	FB_DWR_DI,	/* Index=237: OEM-Standard DWR_DI*/
	FB_DWR_UI,	/* Index=238: OEM-Standard DWR_UI*/
	FB_DWR_UDI,	/* Index=239: OEM-Standard DWR_UDI*/
	FB_DWR_W,	/* Index=240: OEM-Standard DWR_W*/
	FB_DWR_DW,	/* Index=241: OEM-Standard DWR_DW*/
	FB_DWR_BY,	/* Index=242: OEM-Standard DWR_BY*/
	FB_DRD_8,	/* Index=243: OEM-Standard DRD_8*/
	FB_DRD_8I,	/* Index=244: OEM-Standard DRD_8I*/
	FB_DRD_8DI,	/* Index=245: OEM-Standard DRD_8DI*/
	FB_DRD_8UI,	/* Index=246: OEM-Standard DRD_8UI*/
	FB_DRD_8UDI,	/* Index=247: OEM-Standard DRD_8UDI*/
	FB_DRD_8W,	/* Index=248: OEM-Standard DRD_8W*/
	FB_DRD_8DW,	/* Index=249: OEM-Standard DRD_8DW*/
	FB_DRD_8BY,	/* Index=250: OEM-Standard DRD_8BY*/
	FB_DWR_8,	/* Index=251: OEM-Standard DWR_8*/
	FB_DWR_8I,	/* Index=252: OEM-Standard DWR_8I*/
	FB_DWR_8DI,	/* Index=253: OEM-Standard DWR_8DI*/
	FB_DWR_8UI,	/* Index=254: OEM-Standard DWR_8UI*/
	FB_DWR_8UDI,	/* Index=255: OEM-Standard DWR_8UDI*/
	FB_DWR_8W,	/* Index=256: OEM-Standard DWR_8W*/
	FB_DWR_8DW,	/* Index=257: OEM-Standard DWR_8DW*/
	FB_DWR_8BY,	/* Index=258: OEM-Standard DWR_8BY*/
	LZSNULL,	/* Index=259: *** UNUSED *** */
	FB_COM,	/* Index=260: OEM-Standard COM*/
	FB_DSR2,	/* Index=261: OEM-Standard DSR2*/
	FB_DSR4,	/* Index=262: OEM-Standard DSR4*/
	FB_DSW2,	/* Index=263: OEM-Standard DSW2*/
	FB_DSW4,	/* Index=264: OEM-Standard DSW4*/
	LZSNULL,	/* Index=265: *** UNUSED *** */
	FB_THS,	/* Index=266: OEM-Standard THS*/
	FB_FIT,	/* Index=267: OEM-Standard FIT*/
	FB_MODSET,	/* Index=268: OEM-Standard MODSET*/
	FB_FIF,	/* Index=269: OEM-Standard FIF*/
	FB_MFREE,	/* Index=270: OEM-Standard MFREE*/
	FB_MBSU02,	/* Index=271: OEM-Standard MBSU02*/
	FB_RBSU,	/* Index=272: OEM-Standard RBSU*/
	FB_FMRS,	/* Index=273: OEM-Standard FMRS*/
	FB_MEBV2,	/* Index=274: OEM-Standard MEBV2*/
	FB_SWMT,	/* Index=275: OEM-Standard SWMT*/
	FB_ECM10,	/* Index=276: OEM-Standard ECM10*/
	FB_SUG,	/* Index=277: OEM-Standard SUG*/
	FB_HWCFG,	/* Index=278: OEM-Standard HWCFG*/
	LZSNULL,	/* Index=279: *** UNUSED *** */
	FB_MWSW,	/* Index=280: OEM-Standard MWSW*/
	FB_MWV4,	/* Index=281: OEM-Standard MWV4*/
	FB_MRSW,	/* Index=282: OEM-Standard MRSW*/
	FB_SOG,	/* Index=283: OEM-Standard SOG*/
	FB_DWR_10DW,	/* Index=284: OEM-Standard DWR_10DW*/
	FB_PROCM,	/* Index=285: OEM-Standard PROCM*/
	FB_CRV,	/* Index=286: OEM-Standard CRV*/
	FB_CTV,	/* Index=287: OEM-Standard CTV*/
	FB_RBSD,	/* Index=288: OEM-Standard RBSD*/
	FB_TBSD,	/* Index=289: OEM-Standard TBSD*/
	FB_CRV_P02,	/* Index=290: OEM-Standard CRV_P02*/
	FB_CTV_P02,	/* Index=291: OEM-Standard CTV_P02*/
	FB_CTV_MP,	/* Index=292: OEM-Standard CTV_MP*/
	FB_DUMY_MOD,	/* Index=293: OEM-Standard DUMY_MOD*/
	FB_WSUD02,	/* Index=294: OEM-Standard WSUD02*/
	LZSNULL,	/* Index=295: *** UNUSED *** */
	LZSNULL,	/* Index=296: *** UNUSED *** */
	LZSNULL,	/* Index=297: *** UNUSED *** */
	LZSNULL,	/* Index=298: *** UNUSED *** */
	LZSNULL,	/* Index=299: *** UNUSED *** */
	FB_V2V4,	/* Index=300: OEM-Standard V2V4*/
	FB_V4V2,	/* Index=301: OEM-Standard V4V2*/
	FB_V2V1,	/* Index=302: OEM-Standard V2V1*/
	FB_V1V2,	/* Index=303: OEM-Standard V1V2*/
	FB_BCD1,	/* Index=304: OEM-Standard BCD1*/
	LZSNULL,	/* Index=305: *** UNUSED *** */
	LZSNULL,	/* Index=306: *** UNUSED *** */
	LZSNULL,	/* Index=307: *** UNUSED *** */
	LZSNULL,	/* Index=308: *** UNUSED *** */
	LZSNULL,	/* Index=309: *** UNUSED *** */
	LZSNULL,	/* Index=310: *** UNUSED *** */
	LZSNULL,	/* Index=311: *** UNUSED *** */
	LZSNULL,	/* Index=312: *** UNUSED *** */
	LZSNULL,	/* Index=313: *** UNUSED *** */
	LZSNULL,	/* Index=314: *** UNUSED *** */
	LZSNULL,	/* Index=315: *** UNUSED *** */
	LZSNULL,	/* Index=316: *** UNUSED *** */
	LZSNULL,	/* Index=317: *** UNUSED *** */
	LZSNULL,	/* Index=318: *** UNUSED *** */
	LZSNULL,	/* Index=319: *** UNUSED *** */
	FB_RMR,	/* Index=320: OEM-Standard RMR*/
	FB_RAR2,	/* Index=321: OEM-Standard RAR2*/
	FB_RRG,	/* Index=322: OEM-Standard RRG*/
	FB_RAS,	/* Index=323: OEM-Standard RAS*/
	FB_RLA,	/* Index=324: OEM-Standard RLA*/
	FB_CBR2,	/* Index=325: OEM-Standard CBR2*/
	FB_CBR408,	/* Index=326: OEM-Standard CBR408*/
	FB_CBR208,	/* Index=327: OEM-Standard CBR208*/
	FB_CBR4,	/* Index=328: OEM-Standard CBR4*/
	FB_CTB108,	/* Index=329: OEM-Standard CTB108*/
	FB_CTB208,	/* Index=330: OEM-Standard CTB208*/
	LZSNULL,	/* Index=331: *** UNUSED *** */
	FB_PIB4,	/* Index=332: OEM-Standard PIB4*/
	FB_GIB,	/* Index=333: OEM-Standard GIB*/
	FB_SMMR,	/* Index=334: OEM-Standard SMMR*/
	FB_SUMR,	/* Index=335: OEM-Standard SUMR*/
	FB_HSUC02,	/* Index=336: OEM-Standard HSUC02*/
	FB_FRB,	/* Index=337: OEM-Standard FRB*/
	FB_TSBG2,	/* Index=338: OEM-Standard TSBG2*/
	FB_UMR,	/* Index=339: OEM-Standard UMR*/
	FB_FMR,	/* Index=340: OEM-Standard FMR*/
	FB_SSRD,	/* Index=341: OEM-Standard SSRD*/
	FB_MSIM,	/* Index=342: OEM-Standard MSIM*/
	FB_SSWR,	/* Index=343: OEM-Standard SSWR*/
	FB_MOB8,	/* Index=344: OEM-Standard MOB8*/
	FB_GSB,	/* Index=345: OEM-Standard GSB*/
	FB_TCO,	/* Index=346: OEM-Standard TCO*/
	FB_GRB,	/* Index=347: OEM-Standard GRB*/
	FB_DRB,	/* Index=348: OEM-Standard DRB*/
	FB_TSBM0,	/* Index=349: OEM-Standard TSBM0*/
	FB_TSBG0,	/* Index=350: OEM-Standard TSBG0*/
	FB_CBRF,	/* Index=351: OEM-Standard CBRF*/
	FB_CBRF08,	/* Index=352: OEM-Standard CBRF08*/
	FB_CTB408,	/* Index=353: OEM-Standard CTB408*/
	FB_CTBF08,	/* Index=354: OEM-Standard CTBF08*/
	FB_ASINF,	/* Index=355: OEM-Standard ASINF*/
	FB_DFA,	/* Index=356: OEM-Standard DFA*/
	FB_TGSY,	/* Index=357: OEM-Standard TGSY*/
	FB_TDMI,	/* Index=358: OEM-Standard TDMI*/
	FB_TDMR,	/* Index=359: OEM-Standard TDMR*/
	FB_COUNTER1,	/* Index=360: OEM-Standard COUNTER1*/
	FB_SIGGEN,	/* Index=361: OEM-Standard SIGGEN*/
	FB_SSB,	/* Index=362: OEM-Standard SSB*/
	FB_MTDMR,	/* Index=363: OEM-Standard MTDMR*/
	FB_MTDMI,	/* Index=364: OEM-Standard MTDMI*/
	FB_CVT,	/* Index=365: OEM-Standard CVT*/
	FB_TSBM1,	/* Index=366: OEM-Standard TSBM1*/
	FB_SERSW,	/* Index=367: OEM-Standard SERSW*/
	LZSNULL,	/* Index=368: *** UNUSED *** */
	LZSNULL,	/* Index=369: *** UNUSED *** */
	FB_RCB,	/* Index=370: OEM-Standard RCB*/
	FB_TSU,	/* Index=371: OEM-Standard TSU*/
	FB_TDF,	/* Index=372: OEM-Standard TDF*/
	FB_TGS,	/* Index=373: OEM-Standard TGS*/
	LZSNULL,	/* Index=374: *** UNUSED *** */
	LZSNULL,	/* Index=375: *** UNUSED *** */
	LZSNULL,	/* Index=376: *** UNUSED *** */
	LZSNULL,	/* Index=377: *** UNUSED *** */
	LZSNULL,	/* Index=378: *** UNUSED *** */
	LZSNULL,	/* Index=379: *** UNUSED *** */
	FB_SRTC,	/* Index=380: OEM-Standard SRTC*/
	FB_AND12,	/* Index=381: OEM-Standard AND12*/
	FB_BDK10,	/* Index=382: OEM-Standard BDK10*/
	FB_BMX8,	/* Index=383: OEM-Standard BMX8*/
	FB_CTR,	/* Index=384: OEM-Standard CTR*/
	FB_END,	/* Index=385: OEM-Standard END*/
	LZSNULL,	/* Index=386: *** UNUSED *** */
	FB_NAN4,	/* Index=387: OEM-Standard NAN4*/
	LZSNULL,	/* Index=388: *** UNUSED *** */
	FB_SET_1,	/* Index=389: OEM-Standard SET_1*/
	FB_SHD,	/* Index=390: OEM-Standard SHD*/
	FB_SQU,	/* Index=391: OEM-Standard SQU*/
	FB_TDS,	/* Index=392: OEM-Standard TDS*/
	FB_THEN_1,	/* Index=393: OEM-Standard THEN_1*/
	FB_XOR22,	/* Index=394: OEM-Standard XOR22*/
	FB_MRV4,	/* Index=395: OEM-Standard MRV4*/
	LZSNULL,	/* Index=396: *** UNUSED *** */
	LZSNULL,	/* Index=397: *** UNUSED *** */
	LZSNULL,	/* Index=398: *** UNUSED *** */
	LZSNULL,	/* Index=399: *** UNUSED *** */
	LZSNULL,	/* Index=400: *** UNUSED *** */
	FB_NAN2,	/* Index=401: OEM-Standard NAN2*/
	FB_PDF2F,	/* Index=402: OEM-Standard PDF2F*/
	FB_CTBV1,	/* Index=403: OEM-Standard CTBV1*/
	FB_CTX8,	/* Index=404: OEM-Standard CTX8*/
	FB_DTE8,	/* Index=405: OEM-Standard DTE8*/
	LZSNULL,	/* Index=406: *** UNUSED *** */
	LZSNULL,	/* Index=407: *** UNUSED *** */
	LZSNULL,	/* Index=408: *** UNUSED *** */
	LZSNULL,	/* Index=409: *** UNUSED *** */
	LZSNULL,	/* Index=410: *** UNUSED *** */
	LZSNULL,	/* Index=411: *** UNUSED *** */
	LZSNULL,	/* Index=412: *** UNUSED *** */
	LZSNULL,	/* Index=413: *** UNUSED *** */
	LZSNULL,	/* Index=414: *** UNUSED *** */
	LZSNULL,	/* Index=415: *** UNUSED *** */
	LZSNULL,	/* Index=416: *** UNUSED *** */
	LZSNULL,	/* Index=417: *** UNUSED *** */
	LZSNULL,	/* Index=418: *** UNUSED *** */
	LZSNULL,	/* Index=419: *** UNUSED *** */
	FB_EPI,	/* Index=420: OEM-Standard EPI*/
	FB_TGR_P1,	/* Index=421: OEM-Standard TGR_P1*/
	FB_TGT_P1,	/* Index=422: OEM-Standard TGT_P1*/
	LZSNULL,	/* Index=423: *** UNUSED *** */
	LZSNULL,	/* Index=424: *** UNUSED *** */
	LZSNULL,	/* Index=425: *** UNUSED *** */
	LZSNULL,	/* Index=426: *** UNUSED *** */
	LZSNULL,	/* Index=427: *** UNUSED *** */
	LZSNULL,	/* Index=428: *** UNUSED *** */
	LZSNULL,	/* Index=429: *** UNUSED *** */
	LZSNULL,	/* Index=430: *** UNUSED *** */
	LZSNULL,	/* Index=431: *** UNUSED *** */
	LZSNULL,	/* Index=432: *** UNUSED *** */
	LZSNULL,	/* Index=433: *** UNUSED *** */
	LZSNULL,	/* Index=434: *** UNUSED *** */
	LZSNULL,	/* Index=435: *** UNUSED *** */
	LZSNULL,	/* Index=436: *** UNUSED *** */
	LZSNULL,	/* Index=437: *** UNUSED *** */
	LZSNULL,	/* Index=438: *** UNUSED *** */
	LZSNULL,	/* Index=439: *** UNUSED *** */
	LZSNULL,	/* Index=440: *** UNUSED *** */
	LZSNULL,	/* Index=441: *** UNUSED *** */
	LZSNULL,	/* Index=442: *** UNUSED *** */
	LZSNULL,	/* Index=443: *** UNUSED *** */
	LZSNULL,	/* Index=444: *** UNUSED *** */
	LZSNULL,	/* Index=445: *** UNUSED *** */
	LZSNULL,	/* Index=446: *** UNUSED *** */
	FB_AD_RD,	/* Index=447: OEM-Standard AD_RD*/
	FB_AD_INIT,	/* Index=448: OEM-Standard AD_INIT*/
	FB_MEDV2,	/* Index=449: OEM-Standard MEDV2*/
	FB_RTC003,	/* Index=450: OEM-Standard RTC003*/
	FB_USF,	/* Index=451: OEM-Standard USF*/
	FB_B1V2,	/* Index=452: OEM-Standard B1V2*/
	LZSNULL,	/* Index=453: *** UNUSED *** */
	FB_RAR4,	/* Index=454: OEM-Standard RAR4*/
	FB_SIN0F,	/* Index=455: OEM-Standard SIN0F*/
	FB_SYF1,	/* Index=456: OEM-Standard SYF1*/
	FB_SYF4,	/* Index=457: OEM-Standard SYF4*/
	FB_TFI2,	/* Index=458: OEM-Standard TFI2*/
	FB_DFUR,	/* Index=459: OEM-Standard DFUR*/
	FB_DFUT,	/* Index=460: OEM-Standard DFUT*/
	FB_DFU,	/* Index=461: OEM-Standard DFU*/
	FB_C6MD,	/* Index=462: OEM-Standard C6MD*/
	FB_C6MDR,	/* Index=463: OEM-Standard C6MDR*/
	FB_C6MDT,	/* Index=464: OEM-Standard C6MDT*/
	FB_MI6MD,	/* Index=465: OEM-Standard MI6MD*/
	FB_TI6MD,	/* Index=466: OEM-Standard TI6MD*/
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
	{
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

#endif

}

