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
#if 1
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


/*#include    "userinc/dps_inc.h"*/

#include    "tskScheduler/userConfig.h"
#include    "tskScheduler/tskConfig.h"
#include    "tskScheduler/tskScheduler.h"

#ifndef _LZS_NOSTDLIB_
#include    <stdlib.h>
#define      MAX_SLOTS 10
#endif
/*-------------------------------------------------------------------*/


#include	"vme7050/xj/userdefine.h"

/* firmware function block prototypes */
#if 1 /*group 2 declare*/
LZSBYTE FB_GETSYSTEMDATEANDTIME(void);/*group:2 index:000*/
LZSBYTE FB_SETSYSTEMDATEANDTIME(void);/*group:2 index:001*/
LZSBYTE FB_DT10F(void);/*group:2 index:101*/
LZSBYTE FB_PC_3F(void);/*group:2 index:102*/
LZSBYTE FB_PWM0F(void);/*group:2 index:103*/
LZSBYTE FB_ADD8F(void);/*group:2 index:104*/
LZSBYTE FB_ADDI4(void);/*group:2 index:105*/
LZSBYTE FB_SUBI(void);/*group:2 index:106*/
LZSBYTE FB_MULI(void);/*group:2 index:107*/
LZSBYTE FB_MULI4(void);/*group:2 index:108*/
LZSBYTE FB_DIVI(void);/*group:2 index:109*/
LZSBYTE FB_PLI2F(void);/*group:2 index:110*/
LZSBYTE FB_COS0F(void);/*group:2 index:111*/
LZSBYTE FB_ACOSF(void);/*group:2 index:112*/
LZSBYTE FB_TAN0F(void);/*group:2 index:113*/
LZSBYTE FB_ATANF(void);/*group:2 index:114*/
LZSBYTE FB_OR_22(void);/*group:2 index:115*/
LZSBYTE FB_NOT02(void);/*group:2 index:116*/
LZSBYTE FB_PIN8(void);/*group:2 index:117*/
LZSBYTE FB_FUI(void);/*group:2 index:118*/
LZSBYTE FB_UDI(void);/*group:2 index:119*/
LZSBYTE FB_ANS0F(void);/*group:2 index:120*/
LZSBYTE FB_DX_8F(void);/*group:2 index:121*/
LZSBYTE FB_CNM0F(void);/*group:2 index:122*/
LZSBYTE FB_DFR(void);/*group:2 index:123*/
LZSBYTE FB_DFRV(void);/*group:2 index:124*/
LZSBYTE FB_SAV0F(void);/*group:2 index:125*/
LZSBYTE FB_SBF0F(void);/*group:2 index:126*/
LZSBYTE FB_CTB1(void);/*group:2 index:127*/
LZSBYTE FB_CTB2(void);/*group:2 index:128*/
LZSBYTE FB_CTBF(void);/*group:2 index:129*/
LZSBYTE FB_SWB(void);/*group:2 index:130*/
LZSBYTE FB_WDC(void);/*group:2 index:131*/
LZSBYTE FB_DWC04(void);/*group:2 index:132*/
LZSBYTE FB_DWR04(void);/*group:2 index:133*/
LZSBYTE FB_N4NF(void);/*group:2 index:135*/
LZSBYTE FB_NFN4(void);/*group:2 index:136*/
LZSBYTE FB_CBR(void);/*group:2 index:137*/
LZSBYTE FB_CBR04(void);/*group:2 index:138*/
LZSBYTE FB_CBRIF(void);/*group:2 index:139*/
LZSBYTE FB_CBRQF(void);/*group:2 index:140*/
LZSBYTE FB_BNR0F(void);/*group:2 index:141*/
LZSBYTE FB_RGJ0F1(void);/*group:2 index:142*/
LZSBYTE FB_ANS(void);/*group:2 index:143*/
LZSBYTE FB_DX_8(void);/*group:2 index:144*/
LZSBYTE FB_CNM(void);/*group:2 index:145*/
LZSBYTE FB_CNM04(void);/*group:2 index:146*/
LZSBYTE FB_SAV(void);/*group:2 index:147*/
LZSBYTE FB_SAV01(void);/*group:2 index:148*/
LZSBYTE FB_SAV04(void);/*group:2 index:149*/
LZSBYTE FB_DLB0F(void);/*group:2 index:150*/
LZSBYTE FB_DWS04(void);/*group:2 index:151*/
LZSBYTE FB_ADK10(void);/*group:2 index:161*/
LZSBYTE FB_BMX8F(void);/*group:2 index:162*/
LZSBYTE FB_BS16(void);/*group:2 index:163*/
LZSBYTE FB_DSRW4(void);/*group:2 index:164*/
LZSBYTE FB_DSWF(void);/*group:2 index:165*/
LZSBYTE FB_FSB(void);/*group:2 index:166*/
LZSBYTE FB_FSS(void);/*group:2 index:167*/
LZSBYTE FB_FTS8(void);/*group:2 index:168*/
LZSBYTE FB_MSAH0F(void);/*group:2 index:169*/
LZSBYTE FB_PETR(void);/*group:2 index:170*/
LZSBYTE FB_SET2(void);/*group:2 index:171*/
LZSBYTE FB_SET4(void);/*group:2 index:172*/
LZSBYTE FB_SET0F(void);/*group:2 index:173*/
LZSBYTE FB_SEQ(void);/*group:2 index:174*/
LZSBYTE FB_ZWE8(void);/*group:2 index:175*/
LZSBYTE FB_MRV2(void);/*group:2 index:176*/
LZSBYTE FB_MWV2(void);/*group:2 index:177*/
LZSBYTE FB_GMI(void);/*group:2 index:178*/
LZSBYTE FB_GPB(void);/*group:2 index:179*/
LZSBYTE FB_GSC(void);/*group:2 index:180*/
LZSBYTE FB_MNCB(void);/*group:2 index:181*/
LZSBYTE FB_MOB3(void);/*group:2 index:182*/
LZSBYTE FB_MPB(void);/*group:2 index:183*/
LZSBYTE FB_PMA(void);/*group:2 index:185*/
LZSBYTE FB_UDR(void);/*group:2 index:186*/
LZSBYTE FB_UDW(void);/*group:2 index:187*/
LZSBYTE FB_UMA(void);/*group:2 index:188*/
LZSBYTE FB_B1V1(void);/*group:2 index:189*/
LZSBYTE FB_BCD(void);/*group:2 index:190*/
LZSBYTE FB_BSCB(void);/*group:2 index:191*/
LZSBYTE FB_BSC8(void);/*group:2 index:192*/
LZSBYTE FB_NFV4(void);/*group:2 index:193*/
LZSBYTE FB_SBC8(void);/*group:2 index:194*/
LZSBYTE FB_TIC(void);/*group:2 index:195*/
LZSBYTE FB_V1B1(void);/*group:2 index:196*/
LZSBYTE FB_V1V4(void);/*group:2 index:197*/
LZSBYTE FB_V2B1(void);/*group:2 index:198*/
LZSBYTE FB_V4NF(void);/*group:2 index:199*/
LZSBYTE FB_V4V1(void);/*group:2 index:200*/
LZSBYTE FB_TFI(void);/*group:2 index:201*/
LZSBYTE FB_TFIS(void);/*group:2 index:202*/
LZSBYTE FB_TRC(void);/*group:2 index:203*/
LZSBYTE FB_TTN(void);/*group:2 index:204*/
LZSBYTE FB_MBSU(void);/*group:2 index:205*/
LZSBYTE FB_BIOI(void);/*group:2 index:211*/
LZSBYTE FB_BII8(void);/*group:2 index:212*/
LZSBYTE FB_BIQ8(void);/*group:2 index:213*/
LZSBYTE FB_SBI(void);/*group:2 index:214*/
LZSBYTE FB_SBQ(void);/*group:2 index:215*/
LZSBYTE FB_DORB(void);/*group:2 index:216*/
LZSBYTE FB_BDAI(void);/*group:2 index:217*/
LZSBYTE FB_DAC0F(void);/*group:2 index:218*/
LZSBYTE FB_IFCI(void);/*group:2 index:219*/
LZSBYTE FB_ICBI(void);/*group:2 index:220*/
LZSBYTE FB_ICBW2(void);/*group:2 index:221*/
LZSBYTE FB_ICBS(void);/*group:2 index:222*/
LZSBYTE FB_ICBBD(void);/*group:2 index:223*/
LZSBYTE FB_ICBR2(void);/*group:2 index:224*/
LZSBYTE FB_TEST1_L(void);/*group:2 index:225*/
LZSBYTE FB_TSTART(void);/*group:2 index:236*/
LZSBYTE FB_TSTOP(void);/*group:2 index:237*/
LZSBYTE FB_TASK_EXEC(void);/*group:2 index:238*/
LZSBYTE FB_TASK_LOCK(void);/*group:2 index:239*/
LZSBYTE FB_PRD_T(void);/*group:2 index:240*/
LZSBYTE FB_PRD_I1(void);/*group:2 index:241*/
LZSBYTE FB_PSWT_T(void);/*group:2 index:242*/
LZSBYTE FB_PRD_S(void);/*group:2 index:243*/
LZSBYTE FB_SHM_T(void);/*group:2 index:244*/
LZSBYTE FB_P_TEMP(void);/*group:2 index:245*/
LZSBYTE FB_PAS1(void);/*group:2 index:246*/
#endif /*group -1000504385 declare end*/
#if 1 /*group 3 declare*/
LZSBYTE FB_DRW(void);/*group:3 index:001*/
LZSBYTE FB_DSW(void);/*group:3 index:002*/
LZSBYTE FB_HPN(void);/*group:3 index:003*/
LZSBYTE FB_KRST(void);/*group:3 index:004*/
LZSBYTE FB_MF32(void);/*group:3 index:005*/
LZSBYTE FB_MGF(void);/*group:3 index:006*/
LZSBYTE FB_SDW(void);/*group:3 index:007*/
LZSBYTE FB_SPGA(void);/*group:3 index:008*/
LZSBYTE FB_UVD(void);/*group:3 index:009*/
LZSBYTE FB_MF128(void);/*group:3 index:010*/
LZSBYTE FB_SPG(void);/*group:3 index:011*/
LZSBYTE FB_NCM_W(void);/*group:3 index:012*/
LZSBYTE FB_I2N2(void);/*group:3 index:015*/
LZSBYTE FB_BAB(void);/*group:3 index:020*/
LZSBYTE FB_KPW(void);/*group:3 index:021*/
LZSBYTE FB_PKW(void);/*group:3 index:022*/
LZSBYTE FB_PSUB(void);/*group:3 index:023*/
LZSBYTE FB_XPQ(void);/*group:3 index:024*/
LZSBYTE FB_VDV(void);/*group:3 index:025*/
LZSBYTE FB_VIX(void);/*group:3 index:026*/
LZSBYTE FB_AVGN(void);/*group:3 index:030*/
LZSBYTE FB_IIR2(void);/*group:3 index:031*/
LZSBYTE FB_PINT(void);/*group:3 index:032*/
LZSBYTE FB_PT1(void);/*group:3 index:033*/
LZSBYTE FB_PT1D(void);/*group:3 index:034*/
LZSBYTE FB_CSB001(void);/*group:3 index:040*/
LZSBYTE FB_HLG(void);/*group:3 index:041*/
LZSBYTE FB_INT_1(void);/*group:3 index:042*/
LZSBYTE FB_LIM(void);/*group:3 index:043*/
LZSBYTE FB_PICH(void);/*group:3 index:044*/
LZSBYTE FB_DEZ(void);/*group:3 index:045*/
LZSBYTE FB_DEL(void);/*group:3 index:046*/
LZSBYTE FB_PIC2F(void);/*group:3 index:047*/
LZSBYTE FB_RGE(void);/*group:3 index:048*/
LZSBYTE FB_ADD2(void);/*group:3 index:050*/
LZSBYTE FB_ADD4(void);/*group:3 index:051*/
LZSBYTE FB_ASTI(void);/*group:3 index:052*/
LZSBYTE FB_AVA(void);/*group:3 index:053*/
LZSBYTE FB_DIV2(void);/*group:3 index:054*/
LZSBYTE FB_MAS(void);/*group:3 index:055*/
LZSBYTE FB_MAS3(void);/*group:3 index:056*/
LZSBYTE FB_MAXN(void);/*group:3 index:057*/
LZSBYTE FB_MIS(void);/*group:3 index:058*/
LZSBYTE FB_MULD(void);/*group:3 index:059*/
LZSBYTE FB_MULE2(void);/*group:3 index:060*/
LZSBYTE FB_MUL2(void);/*group:3 index:061*/
LZSBYTE FB_PLI6(void);/*group:3 index:062*/
LZSBYTE FB_SII(void);/*group:3 index:063*/
LZSBYTE FB_SUB2(void);/*group:3 index:064*/
LZSBYTE FB_ADD_I(void);/*group:3 index:067*/
LZSBYTE FB_ADD_DI(void);/*group:3 index:068*/
LZSBYTE FB_SUB_I(void);/*group:3 index:070*/
LZSBYTE FB_SUB_DI(void);/*group:3 index:071*/
LZSBYTE FB_AND2(void);/*group:3 index:080*/
LZSBYTE FB_AND3(void);/*group:3 index:081*/
LZSBYTE FB_AND4(void);/*group:3 index:082*/
LZSBYTE FB_AND8(void);/*group:3 index:083*/
LZSBYTE FB_ANDS(void);/*group:3 index:084*/
LZSBYTE FB_BSC(void);/*group:3 index:085*/
LZSBYTE FB_LVM(void);/*group:3 index:086*/
LZSBYTE FB_LVX(void);/*group:3 index:087*/
LZSBYTE FB_MOF(void);/*group:3 index:088*/
LZSBYTE FB_MUX8(void);/*group:3 index:089*/
LZSBYTE FB_NOT1(void);/*group:3 index:090*/
LZSBYTE FB_NOTS(void);/*group:3 index:091*/
LZSBYTE FB_NSW(void);/*group:3 index:092*/
LZSBYTE FB_NCM(void);/*group:3 index:093*/
LZSBYTE FB_OR_2(void);/*group:3 index:094*/
LZSBYTE FB_OR_3(void);/*group:3 index:095*/
LZSBYTE FB_OR_6(void);/*group:3 index:096*/
LZSBYTE FB_OR_S(void);/*group:3 index:097*/
LZSBYTE FB_OR_12(void);/*group:3 index:098*/
LZSBYTE FB_PCL(void);/*group:3 index:099*/
LZSBYTE FB_PDE(void);/*group:3 index:100*/
LZSBYTE FB_PDF(void);/*group:3 index:101*/
LZSBYTE FB_RSR(void);/*group:3 index:102*/
LZSBYTE FB_RSS(void);/*group:3 index:103*/
LZSBYTE FB_SBC(void);/*group:3 index:104*/
LZSBYTE FB_AND5(void);/*group:3 index:105*/
LZSBYTE FB_AND6(void);/*group:3 index:106*/
LZSBYTE FB_AND7(void);/*group:3 index:107*/
LZSBYTE FB_BSW(void);/*group:3 index:108*/
LZSBYTE FB_OR_9(void);/*group:3 index:110*/
LZSBYTE FB_OR_B(void);/*group:3 index:111*/
LZSBYTE FB_XOR_2(void);/*group:3 index:112*/
LZSBYTE FB_MFP(void);/*group:3 index:113*/
LZSBYTE FB_PST(void);/*group:3 index:114*/
LZSBYTE FB_ETE(void);/*group:3 index:115*/
LZSBYTE FB_SBW(void);/*group:3 index:116*/
LZSBYTE FB_LVM2F(void);/*group:3 index:117*/
LZSBYTE FB_NSWD(void);/*group:3 index:118*/
LZSBYTE FB_OR_4(void);/*group:3 index:119*/
LZSBYTE FB_OR_8(void);/*group:3 index:120*/
LZSBYTE FB_MUX8_W(void);/*group:3 index:122*/
LZSBYTE FB_MUX8_DW(void);/*group:3 index:123*/
LZSBYTE FB_MUX8_I(void);/*group:3 index:124*/
LZSBYTE FB_MUX8_DI(void);/*group:3 index:125*/
LZSBYTE FB_NSW_W(void);/*group:3 index:126*/
LZSBYTE FB_NSW_DW(void);/*group:3 index:127*/
LZSBYTE FB_NSW_I(void);/*group:3 index:128*/
LZSBYTE FB_NSW_DI(void);/*group:3 index:129*/
LZSBYTE FB_BBF0F(void);/*group:3 index:130*/
LZSBYTE FB_NOR2(void);/*group:3 index:131*/
LZSBYTE FB_NOR4(void);/*group:3 index:132*/
LZSBYTE FB_NOR8(void);/*group:3 index:133*/
LZSBYTE FB_DUMY_1F(void);/*group:3 index:140*/
LZSBYTE FB_DUMY_2F(void);/*group:3 index:141*/
LZSBYTE FB_DUMY_8F(void);/*group:3 index:142*/
LZSBYTE FB_DUMY_1I(void);/*group:3 index:143*/
LZSBYTE FB_DUMY_2I(void);/*group:3 index:144*/
LZSBYTE FB_DUMY_8I(void);/*group:3 index:145*/
LZSBYTE FB_DUMY_1DI(void);/*group:3 index:146*/
LZSBYTE FB_DUMY_2DI(void);/*group:3 index:147*/
LZSBYTE FB_DUMY_8DI(void);/*group:3 index:148*/
LZSBYTE FB_DUMY_1W(void);/*group:3 index:149*/
LZSBYTE FB_DUMY_2W(void);/*group:3 index:150*/
LZSBYTE FB_DUMY_8W(void);/*group:3 index:151*/
LZSBYTE FB_DUMY_1DW(void);/*group:3 index:152*/
LZSBYTE FB_DUMY_2DW(void);/*group:3 index:153*/
LZSBYTE FB_DUMY_8DW(void);/*group:3 index:154*/
LZSBYTE FB_DUMY_1B(void);/*group:3 index:155*/
LZSBYTE FB_DUMY_8B(void);/*group:3 index:156*/
LZSBYTE FB_DUMY_1D(void);/*group:3 index:157*/
LZSBYTE FB_DUMY_2D(void);/*group:3 index:158*/
LZSBYTE FB_N2NF(void);/*group:3 index:163*/
LZSBYTE FB_NFN2(void);/*group:3 index:164*/
LZSBYTE FB_I_R(void);/*group:3 index:165*/
LZSBYTE FB_DI_R(void);/*group:3 index:166*/
LZSBYTE FB_R_I(void);/*group:3 index:167*/
LZSBYTE FB_R_DI(void);/*group:3 index:168*/
LZSBYTE FB_I_W(void);/*group:3 index:169*/
LZSBYTE FB_DI_DW(void);/*group:3 index:170*/
LZSBYTE FB_W_I(void);/*group:3 index:171*/
LZSBYTE FB_DW_DI(void);/*group:3 index:172*/
LZSBYTE FB_F_I(void);/*group:3 index:173*/
LZSBYTE FB_I_F(void);/*group:3 index:174*/
LZSBYTE FB_SET_R(void);/*group:3 index:175*/
LZSBYTE FB_N2V2(void);/*group:3 index:180*/
LZSBYTE FB_V2N2(void);/*group:3 index:181*/
LZSBYTE FB_N4V4(void);/*group:3 index:182*/
LZSBYTE FB_V4N4(void);/*group:3 index:183*/
LZSBYTE FB_AIN(void);/*group:3 index:184*/
LZSBYTE FB_BSC2(void);/*group:3 index:185*/
LZSBYTE FB_DISA(void);/*group:3 index:186*/
LZSBYTE FB_DIV0F1(void);/*group:3 index:187*/
LZSBYTE FB_EXP1(void);/*group:3 index:188*/
LZSBYTE FB_IIR2S(void);/*group:3 index:189*/
LZSBYTE FB_LVH(void);/*group:3 index:190*/
LZSBYTE FB_NOP16W(void);/*group:3 index:191*/
LZSBYTE FB_PSL(void);/*group:3 index:192*/
LZSBYTE FB_PT1S(void);/*group:3 index:193*/
LZSBYTE FB_RVM(void);/*group:3 index:194*/
LZSBYTE FB_DIO_INIT(void);/*group:3 index:201*/
LZSBYTE FB_DI1(void);/*group:3 index:202*/
LZSBYTE FB_DI8(void);/*group:3 index:203*/
LZSBYTE FB_DI16(void);/*group:3 index:204*/
LZSBYTE FB_DI32(void);/*group:3 index:205*/
LZSBYTE FB_DO1(void);/*group:3 index:206*/
LZSBYTE FB_DO8(void);/*group:3 index:207*/
LZSBYTE FB_DO16(void);/*group:3 index:208*/
LZSBYTE FB_DO32(void);/*group:3 index:209*/
LZSBYTE FB_DA_INIT(void);/*group:3 index:210*/
LZSBYTE FB_DA_1(void);/*group:3 index:211*/
LZSBYTE FB_DA_4(void);/*group:3 index:212*/
LZSBYTE FB_DA_8(void);/*group:3 index:213*/
LZSBYTE FB_DA_16(void);/*group:3 index:214*/
LZSBYTE FB_ETHI(void);/*group:3 index:215*/
LZSBYTE FB_TGT_P(void);/*group:3 index:216*/
LZSBYTE FB_TGR_P(void);/*group:3 index:217*/
LZSBYTE FB_TGH3(void);/*group:3 index:218*/
LZSBYTE FB_TCP(void);/*group:3 index:219*/
LZSBYTE FB_CRV_P(void);/*group:3 index:220*/
LZSBYTE FB_CTV_P(void);/*group:3 index:221*/
LZSBYTE FB_PRODP(void);/*group:3 index:222*/
LZSBYTE FB_RSUD(void);/*group:3 index:223*/
LZSBYTE FB_WSUD(void);/*group:3 index:224*/
LZSBYTE FB_DSURD(void);/*group:3 index:225*/
LZSBYTE FB_DSUWR(void);/*group:3 index:226*/
LZSBYTE FB_DRD(void);/*group:3 index:227*/
LZSBYTE FB_DRD_I(void);/*group:3 index:228*/
LZSBYTE FB_DRD_DI(void);/*group:3 index:229*/
LZSBYTE FB_DRD_UI(void);/*group:3 index:230*/
LZSBYTE FB_DRD_UDI(void);/*group:3 index:231*/
LZSBYTE FB_DRD_W(void);/*group:3 index:232*/
LZSBYTE FB_DRD_DW(void);/*group:3 index:233*/
LZSBYTE FB_DRD_BY(void);/*group:3 index:234*/
LZSBYTE FB_DWR(void);/*group:3 index:235*/
LZSBYTE FB_DWR_I(void);/*group:3 index:236*/
LZSBYTE FB_DWR_DI(void);/*group:3 index:237*/
LZSBYTE FB_DWR_UI(void);/*group:3 index:238*/
LZSBYTE FB_DWR_UDI(void);/*group:3 index:239*/
LZSBYTE FB_DWR_W(void);/*group:3 index:240*/
LZSBYTE FB_DWR_DW(void);/*group:3 index:241*/
LZSBYTE FB_DWR_BY(void);/*group:3 index:242*/
LZSBYTE FB_DRD_8(void);/*group:3 index:243*/
LZSBYTE FB_DRD_8I(void);/*group:3 index:244*/
LZSBYTE FB_DRD_8DI(void);/*group:3 index:245*/
LZSBYTE FB_DRD_8UI(void);/*group:3 index:246*/
LZSBYTE FB_DRD_8UDI(void);/*group:3 index:247*/
LZSBYTE FB_DRD_8W(void);/*group:3 index:248*/
LZSBYTE FB_DRD_8DW(void);/*group:3 index:249*/
LZSBYTE FB_DRD_8BY(void);/*group:3 index:250*/
LZSBYTE FB_DWR_8(void);/*group:3 index:251*/
LZSBYTE FB_DWR_8I(void);/*group:3 index:252*/
LZSBYTE FB_DWR_8DI(void);/*group:3 index:253*/
LZSBYTE FB_DWR_8UI(void);/*group:3 index:254*/
LZSBYTE FB_DWR_8UDI(void);/*group:3 index:255*/
LZSBYTE FB_DWR_8W(void);/*group:3 index:256*/
LZSBYTE FB_DWR_8DW(void);/*group:3 index:257*/
LZSBYTE FB_DWR_8BY(void);/*group:3 index:258*/
LZSBYTE FB_COM(void);/*group:3 index:260*/
LZSBYTE FB_DSR2(void);/*group:3 index:261*/
LZSBYTE FB_DSR4(void);/*group:3 index:262*/
LZSBYTE FB_DSW2(void);/*group:3 index:263*/
LZSBYTE FB_DSW4(void);/*group:3 index:264*/
LZSBYTE FB_THS(void);/*group:3 index:266*/
LZSBYTE FB_FIT(void);/*group:3 index:267*/
LZSBYTE FB_MODSET(void);/*group:3 index:268*/
LZSBYTE FB_FIF(void);/*group:3 index:269*/
LZSBYTE FB_MFREE(void);/*group:3 index:270*/
LZSBYTE FB_MBSU02(void);/*group:3 index:271*/
LZSBYTE FB_RBSU(void);/*group:3 index:272*/
LZSBYTE FB_FMRS(void);/*group:3 index:273*/
LZSBYTE FB_MEBV2(void);/*group:3 index:274*/
LZSBYTE FB_SWMT(void);/*group:3 index:275*/
LZSBYTE FB_ECM10(void);/*group:3 index:276*/
LZSBYTE FB_SUG(void);/*group:3 index:277*/
LZSBYTE FB_HWCFG(void);/*group:3 index:278*/
LZSBYTE FB_MWSW(void);/*group:3 index:280*/
LZSBYTE FB_MWV4(void);/*group:3 index:281*/
LZSBYTE FB_MRSW(void);/*group:3 index:282*/
LZSBYTE FB_SOG(void);/*group:3 index:283*/
LZSBYTE FB_DWR_10DW(void);/*group:3 index:284*/
LZSBYTE FB_PROCM(void);/*group:3 index:285*/
LZSBYTE FB_CRV(void);/*group:3 index:286*/
LZSBYTE FB_CTV(void);/*group:3 index:287*/
LZSBYTE FB_RBSD(void);/*group:3 index:288*/
LZSBYTE FB_TBSD(void);/*group:3 index:289*/
LZSBYTE FB_CRV_P02(void);/*group:3 index:290*/
LZSBYTE FB_CTV_P02(void);/*group:3 index:291*/
LZSBYTE FB_CTV_MP(void);/*group:3 index:292*/
LZSBYTE FB_DUMY_MOD(void);/*group:3 index:293*/
LZSBYTE FB_WSUD02(void);/*group:3 index:294*/
LZSBYTE FB_V2V4(void);/*group:3 index:300*/
LZSBYTE FB_V4V2(void);/*group:3 index:301*/
LZSBYTE FB_V2V1(void);/*group:3 index:302*/
LZSBYTE FB_V1V2(void);/*group:3 index:303*/
LZSBYTE FB_BCD1(void);/*group:3 index:304*/
LZSBYTE FB_RMR(void);/*group:3 index:320*/
LZSBYTE FB_RAR2(void);/*group:3 index:321*/
LZSBYTE FB_RRG(void);/*group:3 index:322*/
LZSBYTE FB_RAS(void);/*group:3 index:323*/
LZSBYTE FB_RLA(void);/*group:3 index:324*/
LZSBYTE FB_CBR2(void);/*group:3 index:325*/
LZSBYTE FB_CBR408(void);/*group:3 index:326*/
LZSBYTE FB_CBR208(void);/*group:3 index:327*/
LZSBYTE FB_CBR4(void);/*group:3 index:328*/
LZSBYTE FB_CTB108(void);/*group:3 index:329*/
LZSBYTE FB_CTB208(void);/*group:3 index:330*/
LZSBYTE FB_PIB4(void);/*group:3 index:332*/
LZSBYTE FB_GIB(void);/*group:3 index:333*/
LZSBYTE FB_SMMR(void);/*group:3 index:334*/
LZSBYTE FB_SUMR(void);/*group:3 index:335*/
LZSBYTE FB_HSUC02(void);/*group:3 index:336*/
LZSBYTE FB_FRB(void);/*group:3 index:337*/
LZSBYTE FB_TSBG2(void);/*group:3 index:338*/
LZSBYTE FB_UMR(void);/*group:3 index:339*/
LZSBYTE FB_FMR(void);/*group:3 index:340*/
LZSBYTE FB_SSRD(void);/*group:3 index:341*/
LZSBYTE FB_MSIM(void);/*group:3 index:342*/
LZSBYTE FB_SSWR(void);/*group:3 index:343*/
LZSBYTE FB_MOB8(void);/*group:3 index:344*/
LZSBYTE FB_GSB(void);/*group:3 index:345*/
LZSBYTE FB_TCO(void);/*group:3 index:346*/
LZSBYTE FB_GRB(void);/*group:3 index:347*/
LZSBYTE FB_DRB(void);/*group:3 index:348*/
LZSBYTE FB_TSBM0(void);/*group:3 index:349*/
LZSBYTE FB_TSBG0(void);/*group:3 index:350*/
LZSBYTE FB_CBRF(void);/*group:3 index:351*/
LZSBYTE FB_CBRF08(void);/*group:3 index:352*/
LZSBYTE FB_CTB408(void);/*group:3 index:353*/
LZSBYTE FB_CTBF08(void);/*group:3 index:354*/
LZSBYTE FB_ASINF(void);/*group:3 index:355*/
LZSBYTE FB_DFA(void);/*group:3 index:356*/
LZSBYTE FB_TGSY(void);/*group:3 index:357*/
LZSBYTE FB_TDMI(void);/*group:3 index:358*/
LZSBYTE FB_TDMR(void);/*group:3 index:359*/
LZSBYTE FB_COUNTER1(void);/*group:3 index:360*/
LZSBYTE FB_SIGGEN(void);/*group:3 index:361*/
LZSBYTE FB_SSB(void);/*group:3 index:362*/
LZSBYTE FB_MTDMR(void);/*group:3 index:363*/
LZSBYTE FB_MTDMI(void);/*group:3 index:364*/
LZSBYTE FB_CVT(void);/*group:3 index:365*/
LZSBYTE FB_TSBM1(void);/*group:3 index:366*/
LZSBYTE FB_SERSW(void);/*group:3 index:367*/
LZSBYTE FB_RCB(void);/*group:3 index:370*/
LZSBYTE FB_TSU(void);/*group:3 index:371*/
LZSBYTE FB_TDF(void);/*group:3 index:372*/
LZSBYTE FB_TGS(void);/*group:3 index:373*/
LZSBYTE FB_SRTC(void);/*group:3 index:380*/
LZSBYTE FB_AND12(void);/*group:3 index:381*/
LZSBYTE FB_BDK10(void);/*group:3 index:382*/
LZSBYTE FB_BMX8(void);/*group:3 index:383*/
LZSBYTE FB_CTR(void);/*group:3 index:384*/
LZSBYTE FB_END(void);/*group:3 index:385*/
LZSBYTE FB_NAN4(void);/*group:3 index:387*/
LZSBYTE FB_SET_1(void);/*group:3 index:389*/
LZSBYTE FB_SHD(void);/*group:3 index:390*/
LZSBYTE FB_SQU(void);/*group:3 index:391*/
LZSBYTE FB_TDS(void);/*group:3 index:392*/
LZSBYTE FB_THEN_1(void);/*group:3 index:393*/
LZSBYTE FB_XOR22(void);/*group:3 index:394*/
LZSBYTE FB_MRV4(void);/*group:3 index:395*/
LZSBYTE FB_NAN2(void);/*group:3 index:401*/
LZSBYTE FB_PDF2F(void);/*group:3 index:402*/
LZSBYTE FB_CTBV1(void);/*group:3 index:403*/
LZSBYTE FB_CTX8(void);/*group:3 index:404*/
LZSBYTE FB_DTE8(void);/*group:3 index:405*/
LZSBYTE FB_EPI(void);/*group:3 index:420*/
LZSBYTE FB_TGR_P1(void);/*group:3 index:421*/
LZSBYTE FB_TGT_P1(void);/*group:3 index:422*/
LZSBYTE FB_AD_RD(void);/*group:3 index:447*/
LZSBYTE FB_AD_INIT(void);/*group:3 index:448*/
LZSBYTE FB_MEDV2(void);/*group:3 index:449*/
LZSBYTE FB_RTC003(void);/*group:3 index:450*/
LZSBYTE FB_USF(void);/*group:3 index:451*/
LZSBYTE FB_B1V2(void);/*group:3 index:452*/
LZSBYTE FB_RAR4(void);/*group:3 index:454*/
LZSBYTE FB_SIN0F(void);/*group:3 index:455*/
LZSBYTE FB_SYF1(void);/*group:3 index:456*/
LZSBYTE FB_SYF4(void);/*group:3 index:457*/
LZSBYTE FB_TFI2(void);/*group:3 index:458*/
LZSBYTE FB_DFUR(void);/*group:3 index:459*/
LZSBYTE FB_DFUT(void);/*group:3 index:460*/
LZSBYTE FB_DFU(void);/*group:3 index:461*/
LZSBYTE FB_C6MD(void);/*group:3 index:462*/
LZSBYTE FB_C6MDR(void);/*group:3 index:463*/
LZSBYTE FB_C6MDT(void);/*group:3 index:464*/
LZSBYTE FB_MI6MD(void);/*group:3 index:465*/
LZSBYTE FB_TI6MD(void);/*group:3 index:466*/
#endif
#endif
#ifdef __cplusplus
   }
#endif

#endif /*_OEM_FB_H_*/
