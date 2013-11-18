
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
	return (kIecOK);
}
LZSBYTE FB_SETSYSTEMDATEANDTIME(void)/*group:2 index:001*/
{
	return (kIecOK);
}
LZSBYTE FB_DT10F(void)/*group:2 index:101*/
{
	return (kIecOK);
}
LZSBYTE FB_PC_3F(void)/*group:2 index:102*/
{
	return (kIecOK);
}
LZSBYTE FB_PWM0F(void)/*group:2 index:103*/
{
	return (kIecOK);
}
LZSBYTE FB_ADD8F(void)/*group:2 index:104*/
{
	return (kIecOK);
}
LZSBYTE FB_ADDI4(void)/*group:2 index:105*/
{
	return (kIecOK);
}
LZSBYTE FB_SUBI(void)/*group:2 index:106*/
{
	return (kIecOK);
}
LZSBYTE FB_MULI(void)/*group:2 index:107*/
{
	return (kIecOK);
}
LZSBYTE FB_MULI4(void)/*group:2 index:108*/
{
	return (kIecOK);
}
LZSBYTE FB_DIVI(void)/*group:2 index:109*/
{
	return (kIecOK);
}
LZSBYTE FB_PLI2F(void)/*group:2 index:110*/
{
	return (kIecOK);
}
LZSBYTE FB_COS0F(void)/*group:2 index:111*/
{
	return (kIecOK);
}
LZSBYTE FB_ACOSF(void)/*group:2 index:112*/
{
	return (kIecOK);
}
LZSBYTE FB_TAN0F(void)/*group:2 index:113*/
{
	return (kIecOK);
}
LZSBYTE FB_ATANF(void)/*group:2 index:114*/
{
	return (kIecOK);
}
LZSBYTE FB_OR_22(void)/*group:2 index:115*/
{
	return (kIecOK);
}
LZSBYTE FB_NOT02(void)/*group:2 index:116*/
{
	return (kIecOK);
}
LZSBYTE FB_PIN8(void)/*group:2 index:117*/
{
	return (kIecOK);
}
LZSBYTE FB_FUI(void)/*group:2 index:118*/
{
	return (kIecOK);
}
LZSBYTE FB_UDI(void)/*group:2 index:119*/
{
	return (kIecOK);
}
LZSBYTE FB_ANS0F(void)/*group:2 index:120*/
{
	return (kIecOK);
}
LZSBYTE FB_DX_8F(void)/*group:2 index:121*/
{
	return (kIecOK);
}
LZSBYTE FB_CNM0F(void)/*group:2 index:122*/
{
	return (kIecOK);
}
LZSBYTE FB_DFR(void)/*group:2 index:123*/
{
	return (kIecOK);
}
LZSBYTE FB_DFRV(void)/*group:2 index:124*/
{
	return (kIecOK);
}
LZSBYTE FB_SAV0F(void)/*group:2 index:125*/
{
	return (kIecOK);
}
LZSBYTE FB_SBF0F(void)/*group:2 index:126*/
{
	return (kIecOK);
}
LZSBYTE FB_CTB1(void)/*group:2 index:127*/
{
	return (kIecOK);
}
LZSBYTE FB_CTB2(void)/*group:2 index:128*/
{
	return (kIecOK);
}
LZSBYTE FB_CTBF(void)/*group:2 index:129*/
{
	return (kIecOK);
}
LZSBYTE FB_SWB(void)/*group:2 index:130*/
{
	return (kIecOK);
}
LZSBYTE FB_WDC(void)/*group:2 index:131*/
{
	return (kIecOK);
}
LZSBYTE FB_DWC04(void)/*group:2 index:132*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR04(void)/*group:2 index:133*/
{
	return (kIecOK);
}
LZSBYTE FB_N4NF(void)/*group:2 index:135*/
{
	return (kIecOK);
}
LZSBYTE FB_NFN4(void)/*group:2 index:136*/
{
	return (kIecOK);
}
LZSBYTE FB_CBR(void)/*group:2 index:137*/
{
	return (kIecOK);
}
LZSBYTE FB_CBR04(void)/*group:2 index:138*/
{
	return (kIecOK);
}
LZSBYTE FB_CBRIF(void)/*group:2 index:139*/
{
	return (kIecOK);
}
LZSBYTE FB_CBRQF(void)/*group:2 index:140*/
{
	return (kIecOK);
}
LZSBYTE FB_BNR0F(void)/*group:2 index:141*/
{
	return (kIecOK);
}
LZSBYTE FB_RGJ0F1(void)/*group:2 index:142*/
{
	return (kIecOK);
}
LZSBYTE FB_ANS(void)/*group:2 index:143*/
{
	return (kIecOK);
}
LZSBYTE FB_DX_8(void)/*group:2 index:144*/
{
	return (kIecOK);
}
LZSBYTE FB_CNM(void)/*group:2 index:145*/
{
	return (kIecOK);
}
LZSBYTE FB_CNM04(void)/*group:2 index:146*/
{
	return (kIecOK);
}
LZSBYTE FB_SAV(void)/*group:2 index:147*/
{
	return (kIecOK);
}
LZSBYTE FB_SAV01(void)/*group:2 index:148*/
{
	return (kIecOK);
}
LZSBYTE FB_SAV04(void)/*group:2 index:149*/
{
	return (kIecOK);
}
LZSBYTE FB_DLB0F(void)/*group:2 index:150*/
{
	return (kIecOK);
}
LZSBYTE FB_DWS04(void)/*group:2 index:151*/
{
	return (kIecOK);
}
LZSBYTE FB_ADK10(void)/*group:2 index:161*/
{
	return (kIecOK);
}
LZSBYTE FB_BMX8F(void)/*group:2 index:162*/
{
	return (kIecOK);
}
LZSBYTE FB_BS16(void)/*group:2 index:163*/
{
	return (kIecOK);
}
LZSBYTE FB_DSRW4(void)/*group:2 index:164*/
{
	return (kIecOK);
}
LZSBYTE FB_DSWF(void)/*group:2 index:165*/
{
	return (kIecOK);
}
LZSBYTE FB_FSB(void)/*group:2 index:166*/
{
	return (kIecOK);
}
LZSBYTE FB_FSS(void)/*group:2 index:167*/
{
	return (kIecOK);
}
LZSBYTE FB_FTS8(void)/*group:2 index:168*/
{
	return (kIecOK);
}
LZSBYTE FB_MSAH0F(void)/*group:2 index:169*/
{
	return (kIecOK);
}
LZSBYTE FB_PETR(void)/*group:2 index:170*/
{
	return (kIecOK);
}
LZSBYTE FB_SET2(void)/*group:2 index:171*/
{
	return (kIecOK);
}
LZSBYTE FB_SET4(void)/*group:2 index:172*/
{
	return (kIecOK);
}
LZSBYTE FB_SET0F(void)/*group:2 index:173*/
{
	return (kIecOK);
}
LZSBYTE FB_SEQ(void)/*group:2 index:174*/
{
	return (kIecOK);
}
LZSBYTE FB_ZWE8(void)/*group:2 index:175*/
{
	return (kIecOK);
}
LZSBYTE FB_MRV2(void)/*group:2 index:176*/
{
	return (kIecOK);
}
LZSBYTE FB_MWV2(void)/*group:2 index:177*/
{
	return (kIecOK);
}
LZSBYTE FB_GMI(void)/*group:2 index:178*/
{
	return (kIecOK);
}
LZSBYTE FB_GPB(void)/*group:2 index:179*/
{
	return (kIecOK);
}
LZSBYTE FB_GSC(void)/*group:2 index:180*/
{
	return (kIecOK);
}
LZSBYTE FB_MNCB(void)/*group:2 index:181*/
{
	return (kIecOK);
}
LZSBYTE FB_MOB3(void)/*group:2 index:182*/
{
	return (kIecOK);
}
LZSBYTE FB_MPB(void)/*group:2 index:183*/
{
	return (kIecOK);
}
LZSBYTE FB_PMA(void)/*group:2 index:185*/
{
	return (kIecOK);
}
LZSBYTE FB_UDR(void)/*group:2 index:186*/
{
	return (kIecOK);
}
LZSBYTE FB_UDW(void)/*group:2 index:187*/
{
	return (kIecOK);
}
LZSBYTE FB_UMA(void)/*group:2 index:188*/
{
	return (kIecOK);
}
LZSBYTE FB_B1V1(void)/*group:2 index:189*/
{
	return (kIecOK);
}
LZSBYTE FB_BCD(void)/*group:2 index:190*/
{
	return (kIecOK);
}
LZSBYTE FB_BSCB(void)/*group:2 index:191*/
{
	return (kIecOK);
}
LZSBYTE FB_BSC8(void)/*group:2 index:192*/
{
	return (kIecOK);
}
LZSBYTE FB_NFV4(void)/*group:2 index:193*/
{
	return (kIecOK);
}
LZSBYTE FB_SBC8(void)/*group:2 index:194*/
{
	return (kIecOK);
}
LZSBYTE FB_TIC(void)/*group:2 index:195*/
{
	return (kIecOK);
}
LZSBYTE FB_V1B1(void)/*group:2 index:196*/
{
	return (kIecOK);
}
LZSBYTE FB_V1V4(void)/*group:2 index:197*/
{
	return (kIecOK);
}
LZSBYTE FB_V2B1(void)/*group:2 index:198*/
{
	return (kIecOK);
}
LZSBYTE FB_V4NF(void)/*group:2 index:199*/
{
	return (kIecOK);
}
LZSBYTE FB_V4V1(void)/*group:2 index:200*/
{
	return (kIecOK);
}
LZSBYTE FB_TFI(void)/*group:2 index:201*/
{
	return (kIecOK);
}
LZSBYTE FB_TFIS(void)/*group:2 index:202*/
{
	return (kIecOK);
}
LZSBYTE FB_TRC(void)/*group:2 index:203*/
{
	return (kIecOK);
}
LZSBYTE FB_TTN(void)/*group:2 index:204*/
{
	return (kIecOK);
}
LZSBYTE FB_MBSU(void)/*group:2 index:205*/
{
	return (kIecOK);
}
LZSBYTE FB_BIOI(void)/*group:2 index:211*/
{
	return (kIecOK);
}
LZSBYTE FB_BII8(void)/*group:2 index:212*/
{
	return (kIecOK);
}
LZSBYTE FB_BIQ8(void)/*group:2 index:213*/
{
	return (kIecOK);
}
LZSBYTE FB_SBI(void)/*group:2 index:214*/
{
	return (kIecOK);
}
LZSBYTE FB_SBQ(void)/*group:2 index:215*/
{
	return (kIecOK);
}
LZSBYTE FB_DORB(void)/*group:2 index:216*/
{
	return (kIecOK);
}
LZSBYTE FB_BDAI(void)/*group:2 index:217*/
{
	return (kIecOK);
}
LZSBYTE FB_DAC0F(void)/*group:2 index:218*/
{
	return (kIecOK);
}
LZSBYTE FB_IFCI(void)/*group:2 index:219*/
{
	return (kIecOK);
}
LZSBYTE FB_ICBI(void)/*group:2 index:220*/
{
	return (kIecOK);
}
LZSBYTE FB_ICBW2(void)/*group:2 index:221*/
{
	return (kIecOK);
}
LZSBYTE FB_ICBS(void)/*group:2 index:222*/
{
	return (kIecOK);
}
LZSBYTE FB_ICBBD(void)/*group:2 index:223*/
{
	return (kIecOK);
}
LZSBYTE FB_ICBR2(void)/*group:2 index:224*/
{
	return (kIecOK);
}
LZSBYTE FB_TEST1_L(void)/*group:2 index:225*/
{
	return (kIecOK);
}
LZSBYTE FB_TSTART(void)/*group:2 index:236*/
{
	return (kIecOK);
}
LZSBYTE FB_TSTOP(void)/*group:2 index:237*/
{
	return (kIecOK);
}
LZSBYTE FB_TASK_EXEC(void)/*group:2 index:238*/
{
	return (kIecOK);
}
LZSBYTE FB_TASK_LOCK(void)/*group:2 index:239*/
{
	return (kIecOK);
}
LZSBYTE FB_PRD_T(void)/*group:2 index:240*/
{
	return (kIecOK);
}
LZSBYTE FB_PRD_I1(void)/*group:2 index:241*/
{
	return (kIecOK);
}
LZSBYTE FB_PSWT_T(void)/*group:2 index:242*/
{
	return (kIecOK);
}
LZSBYTE FB_PRD_S(void)/*group:2 index:243*/
{
	return (kIecOK);
}
LZSBYTE FB_SHM_T(void)/*group:2 index:244*/
{
	return (kIecOK);
}
LZSBYTE FB_P_TEMP(void)/*group:2 index:245*/
{
	return (kIecOK);
}
LZSBYTE FB_PAS1(void)/*group:2 index:246*/
{
	return (kIecOK);
}
#endif
#if 1
LZSBYTE FB_DRW(void)/*group:3 index:001*/
{
	return (kIecOK);
}
LZSBYTE FB_DSW(void)/*group:3 index:002*/
{
	return (kIecOK);
}
LZSBYTE FB_HPN(void)/*group:3 index:003*/
{
	return (kIecOK);
}
LZSBYTE FB_KRST(void)/*group:3 index:004*/
{
	return (kIecOK);
}
LZSBYTE FB_MF32(void)/*group:3 index:005*/
{
	return (kIecOK);
}
LZSBYTE FB_MGF(void)/*group:3 index:006*/
{
	return (kIecOK);
}
LZSBYTE FB_SDW(void)/*group:3 index:007*/
{
	return (kIecOK);
}
LZSBYTE FB_SPGA(void)/*group:3 index:008*/
{
	return (kIecOK);
}
LZSBYTE FB_UVD(void)/*group:3 index:009*/
{
	return (kIecOK);
}
LZSBYTE FB_MF128(void)/*group:3 index:010*/
{
	return (kIecOK);
}
LZSBYTE FB_SPG(void)/*group:3 index:011*/
{
	return (kIecOK);
}
LZSBYTE FB_NCM_W(void)/*group:3 index:012*/
{
	return (kIecOK);
}
LZSBYTE FB_I2N2(void)/*group:3 index:015*/
{
	return (kIecOK);
}
LZSBYTE FB_BAB(void)/*group:3 index:020*/
{
	return (kIecOK);
}
LZSBYTE FB_KPW(void)/*group:3 index:021*/
{
	return (kIecOK);
}
LZSBYTE FB_PKW(void)/*group:3 index:022*/
{
	return (kIecOK);
}
LZSBYTE FB_PSUB(void)/*group:3 index:023*/
{
	return (kIecOK);
}
LZSBYTE FB_XPQ(void)/*group:3 index:024*/
{
	return (kIecOK);
}
LZSBYTE FB_VDV(void)/*group:3 index:025*/
{
	return (kIecOK);
}
LZSBYTE FB_VIX(void)/*group:3 index:026*/
{
	return (kIecOK);
}
LZSBYTE FB_AVGN(void)/*group:3 index:030*/
{
	return (kIecOK);
}
LZSBYTE FB_IIR2(void)/*group:3 index:031*/
{
	return (kIecOK);
}
LZSBYTE FB_PINT(void)/*group:3 index:032*/
{
	return (kIecOK);
}
LZSBYTE FB_PT1(void)/*group:3 index:033*/
{
	return (kIecOK);
}
LZSBYTE FB_PT1D(void)/*group:3 index:034*/
{
	return (kIecOK);
}
LZSBYTE FB_CSB001(void)/*group:3 index:040*/
{
	return (kIecOK);
}
LZSBYTE FB_HLG(void)/*group:3 index:041*/
{
	return (kIecOK);
}
LZSBYTE FB_INT_1(void)/*group:3 index:042*/
{
	return (kIecOK);
}
LZSBYTE FB_LIM(void)/*group:3 index:043*/
{
	return (kIecOK);
}
LZSBYTE FB_PICH(void)/*group:3 index:044*/
{
	return (kIecOK);
}
LZSBYTE FB_DEZ(void)/*group:3 index:045*/
{
	return (kIecOK);
}
LZSBYTE FB_DEL(void)/*group:3 index:046*/
{
	return (kIecOK);
}
LZSBYTE FB_PIC2F(void)/*group:3 index:047*/
{
	return (kIecOK);
}
LZSBYTE FB_RGE(void)/*group:3 index:048*/
{
	return (kIecOK);
}
LZSBYTE FB_ADD2(void)/*group:3 index:050*/
{
	return (kIecOK);
}
LZSBYTE FB_ADD4(void)/*group:3 index:051*/
{
	return (kIecOK);
}
LZSBYTE FB_ASTI(void)/*group:3 index:052*/
{
	return (kIecOK);
}
LZSBYTE FB_AVA(void)/*group:3 index:053*/
{
	return (kIecOK);
}
LZSBYTE FB_DIV2(void)/*group:3 index:054*/
{
	return (kIecOK);
}
LZSBYTE FB_MAS(void)/*group:3 index:055*/
{
	return (kIecOK);
}
LZSBYTE FB_MAS3(void)/*group:3 index:056*/
{
	return (kIecOK);
}
LZSBYTE FB_MAXN(void)/*group:3 index:057*/
{
	return (kIecOK);
}
LZSBYTE FB_MIS(void)/*group:3 index:058*/
{
	return (kIecOK);
}
LZSBYTE FB_MULD(void)/*group:3 index:059*/
{
	return (kIecOK);
}
LZSBYTE FB_MULE2(void)/*group:3 index:060*/
{
	return (kIecOK);
}
LZSBYTE FB_MUL2(void)/*group:3 index:061*/
{
	return (kIecOK);
}
LZSBYTE FB_PLI6(void)/*group:3 index:062*/
{
	return (kIecOK);
}
LZSBYTE FB_SII(void)/*group:3 index:063*/
{
	return (kIecOK);
}
LZSBYTE FB_SUB2(void)/*group:3 index:064*/
{
	return (kIecOK);
}

LZSBYTE FB_ADD_DI(void)/*group:3 index:068*/
{
	return (kIecOK);
}
LZSBYTE FB_SUB_I(void)/*group:3 index:070*/
{
	return (kIecOK);
}
LZSBYTE FB_SUB_DI(void)/*group:3 index:071*/
{
	return (kIecOK);
}
LZSBYTE FB_AND2(void)/*group:3 index:080*/
{
	return (kIecOK);
}
LZSBYTE FB_AND3(void)/*group:3 index:081*/
{
	return (kIecOK);
}
LZSBYTE FB_AND4(void)/*group:3 index:082*/
{
	return (kIecOK);
}
LZSBYTE FB_AND8(void)/*group:3 index:083*/
{
	return (kIecOK);
}
LZSBYTE FB_ANDS(void)/*group:3 index:084*/
{
	return (kIecOK);
}
LZSBYTE FB_BSC(void)/*group:3 index:085*/
{
	return (kIecOK);
}
LZSBYTE FB_LVM(void)/*group:3 index:086*/
{
	return (kIecOK);
}
LZSBYTE FB_LVX(void)/*group:3 index:087*/
{
	return (kIecOK);
}
LZSBYTE FB_MOF(void)/*group:3 index:088*/
{
	return (kIecOK);
}
LZSBYTE FB_MUX8(void)/*group:3 index:089*/
{
	return (kIecOK);
}
LZSBYTE FB_NOT1(void)/*group:3 index:090*/
{
	return (kIecOK);
}
LZSBYTE FB_NOTS(void)/*group:3 index:091*/
{
	return (kIecOK);
}
LZSBYTE FB_NSW(void)/*group:3 index:092*/
{
	return (kIecOK);
}
LZSBYTE FB_NCM(void)/*group:3 index:093*/
{
	return (kIecOK);
}
LZSBYTE FB_OR_2(void)/*group:3 index:094*/
{
	return (kIecOK);
}
LZSBYTE FB_OR_3(void)/*group:3 index:095*/
{
	return (kIecOK);
}
LZSBYTE FB_OR_6(void)/*group:3 index:096*/
{
	return (kIecOK);
}
LZSBYTE FB_OR_S(void)/*group:3 index:097*/
{
	return (kIecOK);
}
LZSBYTE FB_OR_12(void)/*group:3 index:098*/
{
	return (kIecOK);
}
LZSBYTE FB_PCL(void)/*group:3 index:099*/
{
	return (kIecOK);
}
LZSBYTE FB_PDE(void)/*group:3 index:100*/
{
	return (kIecOK);
}
LZSBYTE FB_PDF(void)/*group:3 index:101*/
{
	return (kIecOK);
}
LZSBYTE FB_RSR(void)/*group:3 index:102*/
{
	return (kIecOK);
}
LZSBYTE FB_RSS(void)/*group:3 index:103*/
{
	return (kIecOK);
}
LZSBYTE FB_SBC(void)/*group:3 index:104*/
{
	return (kIecOK);
}
LZSBYTE FB_AND5(void)/*group:3 index:105*/
{
	return (kIecOK);
}
LZSBYTE FB_AND6(void)/*group:3 index:106*/
{
	return (kIecOK);
}
LZSBYTE FB_AND7(void)/*group:3 index:107*/
{
	return (kIecOK);
}
LZSBYTE FB_BSW(void)/*group:3 index:108*/
{
	return (kIecOK);
}
LZSBYTE FB_OR_9(void)/*group:3 index:110*/
{
	return (kIecOK);
}
LZSBYTE FB_OR_B(void)/*group:3 index:111*/
{
	return (kIecOK);
}
LZSBYTE FB_XOR_2(void)/*group:3 index:112*/
{
	return (kIecOK);
}
LZSBYTE FB_MFP(void)/*group:3 index:113*/
{
	return (kIecOK);
}
LZSBYTE FB_PST(void)/*group:3 index:114*/
{
	return (kIecOK);
}
LZSBYTE FB_ETE(void)/*group:3 index:115*/
{
	return (kIecOK);
}
LZSBYTE FB_SBW(void)/*group:3 index:116*/
{
	return (kIecOK);
}
LZSBYTE FB_LVM2F(void)/*group:3 index:117*/
{
	return (kIecOK);
}
LZSBYTE FB_NSWD(void)/*group:3 index:118*/
{
	return (kIecOK);
}
LZSBYTE FB_OR_4(void)/*group:3 index:119*/
{
	return (kIecOK);
}
LZSBYTE FB_OR_8(void)/*group:3 index:120*/
{
	return (kIecOK);
}
LZSBYTE FB_MUX8_W(void)/*group:3 index:122*/
{
	return (kIecOK);
}
LZSBYTE FB_MUX8_DW(void)/*group:3 index:123*/
{
	return (kIecOK);
}
LZSBYTE FB_MUX8_I(void)/*group:3 index:124*/
{
	return (kIecOK);
}
LZSBYTE FB_MUX8_DI(void)/*group:3 index:125*/
{
	return (kIecOK);
}
LZSBYTE FB_NSW_W(void)/*group:3 index:126*/
{
	return (kIecOK);
}
LZSBYTE FB_NSW_DW(void)/*group:3 index:127*/
{
	return (kIecOK);
}
LZSBYTE FB_NSW_I(void)/*group:3 index:128*/
{
	return (kIecOK);
}
LZSBYTE FB_NSW_DI(void)/*group:3 index:129*/
{
	return (kIecOK);
}
LZSBYTE FB_BBF0F(void)/*group:3 index:130*/
{
	return (kIecOK);
}
LZSBYTE FB_NOR2(void)/*group:3 index:131*/
{
	return (kIecOK);
}
LZSBYTE FB_NOR4(void)/*group:3 index:132*/
{
	return (kIecOK);
}
LZSBYTE FB_NOR8(void)/*group:3 index:133*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_1F(void)/*group:3 index:140*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_2F(void)/*group:3 index:141*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_8F(void)/*group:3 index:142*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_1I(void)/*group:3 index:143*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_2I(void)/*group:3 index:144*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_8I(void)/*group:3 index:145*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_1DI(void)/*group:3 index:146*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_2DI(void)/*group:3 index:147*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_8DI(void)/*group:3 index:148*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_1W(void)/*group:3 index:149*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_2W(void)/*group:3 index:150*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_8W(void)/*group:3 index:151*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_1DW(void)/*group:3 index:152*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_2DW(void)/*group:3 index:153*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_8DW(void)/*group:3 index:154*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_1B(void)/*group:3 index:155*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_8B(void)/*group:3 index:156*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_1D(void)/*group:3 index:157*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_2D(void)/*group:3 index:158*/
{
	return (kIecOK);
}
LZSBYTE FB_N2NF(void)/*group:3 index:163*/
{
	return (kIecOK);
}
LZSBYTE FB_NFN2(void)/*group:3 index:164*/
{
	return (kIecOK);
}
LZSBYTE FB_I_R(void)/*group:3 index:165*/
{
	return (kIecOK);
}
LZSBYTE FB_DI_R(void)/*group:3 index:166*/
{
	return (kIecOK);
}
LZSBYTE FB_R_I(void)/*group:3 index:167*/
{
	return (kIecOK);
}
LZSBYTE FB_R_DI(void)/*group:3 index:168*/
{
	return (kIecOK);
}
LZSBYTE FB_I_W(void)/*group:3 index:169*/
{
	return (kIecOK);
}
LZSBYTE FB_DI_DW(void)/*group:3 index:170*/
{
	return (kIecOK);
}
LZSBYTE FB_W_I(void)/*group:3 index:171*/
{
	return (kIecOK);
}
LZSBYTE FB_DW_DI(void)/*group:3 index:172*/
{
	return (kIecOK);
}
LZSBYTE FB_F_I(void)/*group:3 index:173*/
{
	return (kIecOK);
}
LZSBYTE FB_I_F(void)/*group:3 index:174*/
{
	return (kIecOK);
}
LZSBYTE FB_SET_R(void)/*group:3 index:175*/
{
	return (kIecOK);
}
LZSBYTE FB_N2V2(void)/*group:3 index:180*/
{
	return (kIecOK);
}
LZSBYTE FB_V2N2(void)/*group:3 index:181*/
{
	return (kIecOK);
}
LZSBYTE FB_N4V4(void)/*group:3 index:182*/
{
	return (kIecOK);
}
LZSBYTE FB_V4N4(void)/*group:3 index:183*/
{
	return (kIecOK);
}
LZSBYTE FB_AIN(void)/*group:3 index:184*/
{
	return (kIecOK);
}
LZSBYTE FB_BSC2(void)/*group:3 index:185*/
{
	return (kIecOK);
}
LZSBYTE FB_DISA(void)/*group:3 index:186*/
{
	return (kIecOK);
}
LZSBYTE FB_DIV0F1(void)/*group:3 index:187*/
{
	return (kIecOK);
}
LZSBYTE FB_EXP1(void)/*group:3 index:188*/
{
	return (kIecOK);
}
LZSBYTE FB_IIR2S(void)/*group:3 index:189*/
{
	return (kIecOK);
}
LZSBYTE FB_LVH(void)/*group:3 index:190*/
{
	return (kIecOK);
}
LZSBYTE FB_NOP16W(void)/*group:3 index:191*/
{
	return (kIecOK);
}
LZSBYTE FB_PSL(void)/*group:3 index:192*/
{
	return (kIecOK);
}
LZSBYTE FB_PT1S(void)/*group:3 index:193*/
{
	return (kIecOK);
}
LZSBYTE FB_RVM(void)/*group:3 index:194*/
{
	return (kIecOK);
}
LZSBYTE FB_DIO_INIT(void)/*group:3 index:201*/
{
	return (kIecOK);
}
LZSBYTE FB_DI1(void)/*group:3 index:202*/
{
	return (kIecOK);
}
LZSBYTE FB_DI8(void)/*group:3 index:203*/
{
	return (kIecOK);
}
LZSBYTE FB_DI16(void)/*group:3 index:204*/
{
	return (kIecOK);
}
LZSBYTE FB_DI32(void)/*group:3 index:205*/
{
	return (kIecOK);
}
LZSBYTE FB_DO1(void)/*group:3 index:206*/
{
	return (kIecOK);
}
LZSBYTE FB_DO8(void)/*group:3 index:207*/
{
	return (kIecOK);
}
LZSBYTE FB_DO16(void)/*group:3 index:208*/
{
	return (kIecOK);
}
LZSBYTE FB_DO32(void)/*group:3 index:209*/
{
	return (kIecOK);
}
LZSBYTE FB_DA_INIT(void)/*group:3 index:210*/
{
	return (kIecOK);
}
LZSBYTE FB_DA_1(void)/*group:3 index:211*/
{
	return (kIecOK);
}
LZSBYTE FB_DA_4(void)/*group:3 index:212*/
{
	return (kIecOK);
}
LZSBYTE FB_DA_8(void)/*group:3 index:213*/
{
	return (kIecOK);
}
LZSBYTE FB_DA_16(void)/*group:3 index:214*/
{
	return (kIecOK);
}
LZSBYTE FB_ETHI(void)/*group:3 index:215*/
{
	return (kIecOK);
}
LZSBYTE FB_TGT_P(void)/*group:3 index:216*/
{
	return (kIecOK);
}
LZSBYTE FB_TGR_P(void)/*group:3 index:217*/
{
	return (kIecOK);
}
LZSBYTE FB_TGH3(void)/*group:3 index:218*/
{
	return (kIecOK);
}
LZSBYTE FB_TCP(void)/*group:3 index:219*/
{
	return (kIecOK);
}
LZSBYTE FB_CRV_P(void)/*group:3 index:220*/
{
	return (kIecOK);
}
LZSBYTE FB_CTV_P(void)/*group:3 index:221*/
{
	return (kIecOK);
}
LZSBYTE FB_PRODP(void)/*group:3 index:222*/
{
	return (kIecOK);
}
LZSBYTE FB_RSUD(void)/*group:3 index:223*/
{
	return (kIecOK);
}
LZSBYTE FB_WSUD(void)/*group:3 index:224*/
{
	return (kIecOK);
}
LZSBYTE FB_DSURD(void)/*group:3 index:225*/
{
	return (kIecOK);
}
LZSBYTE FB_DSUWR(void)/*group:3 index:226*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD(void)/*group:3 index:227*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_I(void)/*group:3 index:228*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_DI(void)/*group:3 index:229*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_UI(void)/*group:3 index:230*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_UDI(void)/*group:3 index:231*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_W(void)/*group:3 index:232*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_DW(void)/*group:3 index:233*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_BY(void)/*group:3 index:234*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR(void)/*group:3 index:235*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_I(void)/*group:3 index:236*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_DI(void)/*group:3 index:237*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_UI(void)/*group:3 index:238*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_UDI(void)/*group:3 index:239*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_W(void)/*group:3 index:240*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_DW(void)/*group:3 index:241*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_BY(void)/*group:3 index:242*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_8(void)/*group:3 index:243*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_8I(void)/*group:3 index:244*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_8DI(void)/*group:3 index:245*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_8UI(void)/*group:3 index:246*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_8UDI(void)/*group:3 index:247*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_8W(void)/*group:3 index:248*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_8DW(void)/*group:3 index:249*/
{
	return (kIecOK);
}
LZSBYTE FB_DRD_8BY(void)/*group:3 index:250*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_8(void)/*group:3 index:251*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_8I(void)/*group:3 index:252*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_8DI(void)/*group:3 index:253*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_8UI(void)/*group:3 index:254*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_8UDI(void)/*group:3 index:255*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_8W(void)/*group:3 index:256*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_8DW(void)/*group:3 index:257*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_8BY(void)/*group:3 index:258*/
{
	return (kIecOK);
}
LZSBYTE FB_COM(void)/*group:3 index:260*/
{
	return (kIecOK);
}
LZSBYTE FB_DSR2(void)/*group:3 index:261*/
{
	return (kIecOK);
}
LZSBYTE FB_DSR4(void)/*group:3 index:262*/
{
	return (kIecOK);
}
LZSBYTE FB_DSW2(void)/*group:3 index:263*/
{
	return (kIecOK);
}
LZSBYTE FB_DSW4(void)/*group:3 index:264*/
{
	return (kIecOK);
}
LZSBYTE FB_THS(void)/*group:3 index:266*/
{
	return (kIecOK);
}
LZSBYTE FB_FIT(void)/*group:3 index:267*/
{
	return (kIecOK);
}
LZSBYTE FB_MODSET(void)/*group:3 index:268*/
{
	return (kIecOK);
}
LZSBYTE FB_FIF(void)/*group:3 index:269*/
{
	return (kIecOK);
}
LZSBYTE FB_MFREE(void)/*group:3 index:270*/
{
	return (kIecOK);
}
LZSBYTE FB_MBSU02(void)/*group:3 index:271*/
{
	return (kIecOK);
}
LZSBYTE FB_RBSU(void)/*group:3 index:272*/
{
	return (kIecOK);
}
LZSBYTE FB_FMRS(void)/*group:3 index:273*/
{
	return (kIecOK);
}
LZSBYTE FB_MEBV2(void)/*group:3 index:274*/
{
	return (kIecOK);
}
LZSBYTE FB_SWMT(void)/*group:3 index:275*/
{
	return (kIecOK);
}
LZSBYTE FB_ECM10(void)/*group:3 index:276*/
{
	return (kIecOK);
}
LZSBYTE FB_SUG(void)/*group:3 index:277*/
{
	return (kIecOK);
}
LZSBYTE FB_HWCFG(void)/*group:3 index:278*/
{
	return (kIecOK);
}
LZSBYTE FB_MWSW(void)/*group:3 index:280*/
{
	return (kIecOK);
}
LZSBYTE FB_MWV4(void)/*group:3 index:281*/
{
	return (kIecOK);
}
LZSBYTE FB_MRSW(void)/*group:3 index:282*/
{
	return (kIecOK);
}
LZSBYTE FB_SOG(void)/*group:3 index:283*/
{
	return (kIecOK);
}
LZSBYTE FB_DWR_10DW(void)/*group:3 index:284*/
{
	return (kIecOK);
}
LZSBYTE FB_PROCM(void)/*group:3 index:285*/
{
	return (kIecOK);
}
LZSBYTE FB_CRV(void)/*group:3 index:286*/
{
	return (kIecOK);
}
LZSBYTE FB_CTV(void)/*group:3 index:287*/
{
	return (kIecOK);
}
LZSBYTE FB_RBSD(void)/*group:3 index:288*/
{
	return (kIecOK);
}
LZSBYTE FB_TBSD(void)/*group:3 index:289*/
{
	return (kIecOK);
}
LZSBYTE FB_CRV_P02(void)/*group:3 index:290*/
{
	return (kIecOK);
}
LZSBYTE FB_CTV_P02(void)/*group:3 index:291*/
{
	return (kIecOK);
}
LZSBYTE FB_CTV_MP(void)/*group:3 index:292*/
{
	return (kIecOK);
}
LZSBYTE FB_DUMY_MOD(void)/*group:3 index:293*/
{
	return (kIecOK);
}
LZSBYTE FB_WSUD02(void)/*group:3 index:294*/
{
	return (kIecOK);
}
LZSBYTE FB_V2V4(void)/*group:3 index:300*/
{
	return (kIecOK);
}
LZSBYTE FB_V4V2(void)/*group:3 index:301*/
{
	return (kIecOK);
}
LZSBYTE FB_V2V1(void)/*group:3 index:302*/
{
	return (kIecOK);
}
LZSBYTE FB_V1V2(void)/*group:3 index:303*/
{
	return (kIecOK);
}
LZSBYTE FB_BCD1(void)/*group:3 index:304*/
{
	return (kIecOK);
}
LZSBYTE FB_RMR(void)/*group:3 index:320*/
{
	return (kIecOK);
}
LZSBYTE FB_RAR2(void)/*group:3 index:321*/
{
	return (kIecOK);
}
LZSBYTE FB_RRG(void)/*group:3 index:322*/
{
	return (kIecOK);
}
LZSBYTE FB_RAS(void)/*group:3 index:323*/
{
	return (kIecOK);
}
LZSBYTE FB_RLA(void)/*group:3 index:324*/
{
	return (kIecOK);
}
LZSBYTE FB_CBR2(void)/*group:3 index:325*/
{
	return (kIecOK);
}
LZSBYTE FB_CBR408(void)/*group:3 index:326*/
{
	return (kIecOK);
}
LZSBYTE FB_CBR208(void)/*group:3 index:327*/
{
	return (kIecOK);
}
LZSBYTE FB_CBR4(void)/*group:3 index:328*/
{
	return (kIecOK);
}
LZSBYTE FB_CTB108(void)/*group:3 index:329*/
{
	return (kIecOK);
}
LZSBYTE FB_CTB208(void)/*group:3 index:330*/
{
	return (kIecOK);
}
LZSBYTE FB_PIB4(void)/*group:3 index:332*/
{
	return (kIecOK);
}
LZSBYTE FB_GIB(void)/*group:3 index:333*/
{
	return (kIecOK);
}
LZSBYTE FB_SMMR(void)/*group:3 index:334*/
{
	return (kIecOK);
}
LZSBYTE FB_SUMR(void)/*group:3 index:335*/
{
	return (kIecOK);
}
LZSBYTE FB_HSUC02(void)/*group:3 index:336*/
{
	return (kIecOK);
}
LZSBYTE FB_FRB(void)/*group:3 index:337*/
{
	return (kIecOK);
}
LZSBYTE FB_TSBG2(void)/*group:3 index:338*/
{
	return (kIecOK);
}
LZSBYTE FB_UMR(void)/*group:3 index:339*/
{
	return (kIecOK);
}
LZSBYTE FB_FMR(void)/*group:3 index:340*/
{
	return (kIecOK);
}
LZSBYTE FB_SSRD(void)/*group:3 index:341*/
{
	return (kIecOK);
}
LZSBYTE FB_MSIM(void)/*group:3 index:342*/
{
	return (kIecOK);
}
LZSBYTE FB_SSWR(void)/*group:3 index:343*/
{
	return (kIecOK);
}
LZSBYTE FB_MOB8(void)/*group:3 index:344*/
{
	return (kIecOK);
}
LZSBYTE FB_GSB(void)/*group:3 index:345*/
{
	return (kIecOK);
}
LZSBYTE FB_TCO(void)/*group:3 index:346*/
{
	return (kIecOK);
}
LZSBYTE FB_GRB(void)/*group:3 index:347*/
{
	return (kIecOK);
}
LZSBYTE FB_DRB(void)/*group:3 index:348*/
{
	return (kIecOK);
}
LZSBYTE FB_TSBM0(void)/*group:3 index:349*/
{
	return (kIecOK);
}
LZSBYTE FB_TSBG0(void)/*group:3 index:350*/
{
	return (kIecOK);
}
LZSBYTE FB_CBRF(void)/*group:3 index:351*/
{
	return (kIecOK);
}
LZSBYTE FB_CBRF08(void)/*group:3 index:352*/
{
	return (kIecOK);
}
LZSBYTE FB_CTB408(void)/*group:3 index:353*/
{
	return (kIecOK);
}
LZSBYTE FB_CTBF08(void)/*group:3 index:354*/
{
	return (kIecOK);
}
LZSBYTE FB_ASINF(void)/*group:3 index:355*/
{
	return (kIecOK);
}
LZSBYTE FB_DFA(void)/*group:3 index:356*/
{
	return (kIecOK);
}
LZSBYTE FB_TGSY(void)/*group:3 index:357*/
{
	return (kIecOK);
}
LZSBYTE FB_TDMI(void)/*group:3 index:358*/
{
	return (kIecOK);
}
LZSBYTE FB_TDMR(void)/*group:3 index:359*/
{
	return (kIecOK);
}
LZSBYTE FB_COUNTER1(void)/*group:3 index:360*/
{
	return (kIecOK);
}
LZSBYTE FB_SIGGEN(void)/*group:3 index:361*/
{
	return (kIecOK);
}
LZSBYTE FB_SSB(void)/*group:3 index:362*/
{
	return (kIecOK);
}
LZSBYTE FB_MTDMR(void)/*group:3 index:363*/
{
	return (kIecOK);
}
LZSBYTE FB_MTDMI(void)/*group:3 index:364*/
{
	return (kIecOK);
}
LZSBYTE FB_CVT(void)/*group:3 index:365*/
{
	return (kIecOK);
}
LZSBYTE FB_TSBM1(void)/*group:3 index:366*/
{
	return (kIecOK);
}
LZSBYTE FB_SERSW(void)/*group:3 index:367*/
{
	return (kIecOK);
}
LZSBYTE FB_RCB(void)/*group:3 index:370*/
{
	return (kIecOK);
}
LZSBYTE FB_TSU(void)/*group:3 index:371*/
{
	return (kIecOK);
}
LZSBYTE FB_TDF(void)/*group:3 index:372*/
{
	return (kIecOK);
}
LZSBYTE FB_TGS(void)/*group:3 index:373*/
{
	return (kIecOK);
}
LZSBYTE FB_SRTC(void)/*group:3 index:380*/
{
	return (kIecOK);
}
LZSBYTE FB_AND12(void)/*group:3 index:381*/
{
	return (kIecOK);
}
LZSBYTE FB_BDK10(void)/*group:3 index:382*/
{
	return (kIecOK);
}
LZSBYTE FB_BMX8(void)/*group:3 index:383*/
{
	return (kIecOK);
}
LZSBYTE FB_CTR(void)/*group:3 index:384*/
{
	return (kIecOK);
}
LZSBYTE FB_END(void)/*group:3 index:385*/
{
	return (kIecOK);
}
LZSBYTE FB_NAN4(void)/*group:3 index:387*/
{
	return (kIecOK);
}
LZSBYTE FB_SET_1(void)/*group:3 index:389*/
{
	return (kIecOK);
}
LZSBYTE FB_SHD(void)/*group:3 index:390*/
{
	return (kIecOK);
}
LZSBYTE FB_SQU(void)/*group:3 index:391*/
{
	return (kIecOK);
}
LZSBYTE FB_TDS(void)/*group:3 index:392*/
{
	return (kIecOK);
}
LZSBYTE FB_THEN_1(void)/*group:3 index:393*/
{
	return (kIecOK);
}
LZSBYTE FB_XOR22(void)/*group:3 index:394*/
{
	return (kIecOK);
}
LZSBYTE FB_MRV4(void)/*group:3 index:395*/
{
	return (kIecOK);
}
LZSBYTE FB_NAN2(void)/*group:3 index:401*/
{
	return (kIecOK);
}
LZSBYTE FB_PDF2F(void)/*group:3 index:402*/
{
	return (kIecOK);
}
LZSBYTE FB_CTBV1(void)/*group:3 index:403*/
{
	return (kIecOK);
}
LZSBYTE FB_CTX8(void)/*group:3 index:404*/
{
	return (kIecOK);
}
LZSBYTE FB_DTE8(void)/*group:3 index:405*/
{
	return (kIecOK);
}
LZSBYTE FB_EPI(void)/*group:3 index:420*/
{
	return (kIecOK);
}
LZSBYTE FB_TGR_P1(void)/*group:3 index:421*/
{
	return (kIecOK);
}
LZSBYTE FB_TGT_P1(void)/*group:3 index:422*/
{
	return (kIecOK);
}
LZSBYTE FB_AD_RD(void)/*group:3 index:447*/
{
	return (kIecOK);
}
LZSBYTE FB_AD_INIT(void)/*group:3 index:448*/
{
	return (kIecOK);
}
LZSBYTE FB_MEDV2(void)/*group:3 index:449*/
{
	return (kIecOK);
}
LZSBYTE FB_RTC003(void)/*group:3 index:450*/
{
	return (kIecOK);
}
LZSBYTE FB_USF(void)/*group:3 index:451*/
{
	return (kIecOK);
}
LZSBYTE FB_B1V2(void)/*group:3 index:452*/
{
	return (kIecOK);
}
LZSBYTE FB_RAR4(void)/*group:3 index:454*/
{
	return (kIecOK);
}
LZSBYTE FB_SIN0F(void)/*group:3 index:455*/
{
	return (kIecOK);
}
LZSBYTE FB_SYF1(void)/*group:3 index:456*/
{
	return (kIecOK);
}
LZSBYTE FB_SYF4(void)/*group:3 index:457*/
{
	return (kIecOK);
}
LZSBYTE FB_TFI2(void)/*group:3 index:458*/
{
	return (kIecOK);
}
LZSBYTE FB_DFUR(void)/*group:3 index:459*/
{
	return (kIecOK);
}
LZSBYTE FB_DFUT(void)/*group:3 index:460*/
{
	return (kIecOK);
}
LZSBYTE FB_DFU(void)/*group:3 index:461*/
{
	return (kIecOK);
}
LZSBYTE FB_C6MD(void)/*group:3 index:462*/
{
	return (kIecOK);
}
LZSBYTE FB_C6MDR(void)/*group:3 index:463*/
{
	return (kIecOK);
}
LZSBYTE FB_C6MDT(void)/*group:3 index:464*/
{
	return (kIecOK);
}
LZSBYTE FB_MI6MD(void)/*group:3 index:465*/
{
	return (kIecOK);
}
LZSBYTE FB_TI6MD(void)/*group:3 index:466*/
{
	return (kIecOK);
}
#endif

