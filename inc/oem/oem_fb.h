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
/*LZSBYTE FB_Asinf(void);
LZSBYTE FB_Mux8(void);*/
LZSBYTE FB_I2N2(void);
LZSBYTE FB_MTDMR(void);
/*LZSBYTE FB_DFA(void);*/
LZSBYTE FB_MTDMI(void);
/*LZSBYTE FB_TGSY(void);
LZSBYTE FB_MTDMR_1(void);*/


LZSBYTE FB_NOR2(void);
LZSBYTE FB_NOR4(void);
LZSBYTE FB_NOR8(void);
LZSBYTE FB_Asinf(void);
LZSBYTE FB_DFA(void);
LZSBYTE FB_TGSY(void);
LZSBYTE FB_TDMI(void) ;
LZSBYTE FB_TDMR(void) ;
LZSBYTE FB_SSB(void);

LZSBYTE FB_COUNTER1(void) ;
LZSBYTE FB_SIGGEN(void) ;

/*------------------------   LINAN   ---------  13  ---------*/
LZSBYTE FB_V2V4(void);
LZSBYTE FB_V4V2(void);
LZSBYTE FB_COM(void);
LZSBYTE FB_DSR2(void);
LZSBYTE FB_DSR4(void);
LZSBYTE FB_DSW2(void);
LZSBYTE FB_DSW4(void);
LZSBYTE FB_CBR2(void);
LZSBYTE FB_CBR208(void);
LZSBYTE FB_CBR4(void);
LZSBYTE FB_CBR408(void);
LZSBYTE FB_CTB108(void);
LZSBYTE FB_CTB208(void);

LZSBYTE FB_CBRF(void);
LZSBYTE FB_CBRF08(void);
LZSBYTE FB_CTB408(void);
LZSBYTE FB_CTBF08(void);


/*------------------------   LINAN   ------------------*/



/*------------------------   LINAN   ---------  51  ---------*/
LZSBYTE FB_DSW(void) ;
LZSBYTE FB_MF32(void) ;
LZSBYTE FB_MGF(void) ;
LZSBYTE FB_SPGA(void) ;
LZSBYTE FB_PINT(void) ;
LZSBYTE FB_HLG(void) ;
LZSBYTE FB_ADD4(void) ;
LZSBYTE FB_MAS3(void) ;
LZSBYTE FB_MAXN(void) ;
LZSBYTE FB_MULE2(void) ;
LZSBYTE FB_CSB001(void) ;
LZSBYTE FB_PICH(void) ;
LZSBYTE FB_AND3(void) ;
LZSBYTE FB_AND8(void) ;
LZSBYTE FB_ANDS(void) ;
LZSBYTE FB_LVM(void) ;
LZSBYTE FB_NCM(void) ;
LZSBYTE FB_OR_6(void) ;
LZSBYTE FB_PCL(void) ;
LZSBYTE FB_AND5(void) ;
LZSBYTE FB_AND6(void) ;
LZSBYTE FB_AND7(void) ;
LZSBYTE FB_BSW(void) ;
LZSBYTE FB_OR_8(void) ;
LZSBYTE FB_OR_9(void) ;
LZSBYTE FB_OR_B(void) ;
LZSBYTE FB_XOR_2(void) ;
LZSBYTE FB_LVM2F(void) ;
LZSBYTE FB_MFP(void) ;
LZSBYTE FB_PST(void) ;
LZSBYTE FB_ETE(void) ;
LZSBYTE FB_NSWD(void) ;
LZSBYTE FB_DUMY_1F(void) ;
LZSBYTE FB_DUMY_2F(void) ;
LZSBYTE FB_DUMY_8F(void) ;
LZSBYTE FB_DUMY_1I(void) ;
LZSBYTE FB_DUMY_2I(void) ;
LZSBYTE FB_DUMY_8I(void) ;
LZSBYTE FB_DUMY_1DI(void) ;
LZSBYTE FB_DUMY_2DI(void) ;
LZSBYTE FB_DUMY_8DI(void) ;
LZSBYTE FB_DUMY_1W(void) ;
LZSBYTE FB_DUMY_2W(void) ;
LZSBYTE FB_DUMY_8W(void) ;
LZSBYTE FB_DUMY_1DW(void) ;
LZSBYTE FB_DUMY_2DW(void) ;
LZSBYTE FB_DUMY_8DW(void) ;
LZSBYTE FB_DUMY_1B(void) ;
LZSBYTE FB_DUMY_8B(void) ;
LZSBYTE FB_DUMY_1D(void) ;
LZSBYTE FB_DUMY_2D(void) ;
LZSBYTE FB_OR_4(void) ;


/*---------------  Added by yuhai  ---------53----------*/

LZSBYTE FB_DIV2(void);

LZSBYTE FB_IIR2(void);
LZSBYTE FB_KPW(void);/**/
LZSBYTE FB_KRST(void);
LZSBYTE FB_MUL2(void);
LZSBYTE FB_MUX8(void);
LZSBYTE FB_MAS(void);
LZSBYTE FB_DRW(void);/**/
LZSBYTE FB_PT1D(void);
LZSBYTE FB_SUB2(void);
LZSBYTE FB_MF128(void);/**/

LZSBYTE FB_AND2(void);
LZSBYTE FB_AND4(void);
LZSBYTE FB_LVX(void);
LZSBYTE FB_SBC(void);
LZSBYTE FB_BSC(void);
LZSBYTE FB_PDE(void);
LZSBYTE FB_RSR(void);
LZSBYTE FB_NSW(void);
LZSBYTE FB_PDF(void);
LZSBYTE FB_BAB(void);
LZSBYTE FB_SDW(void);
LZSBYTE FB_UVD(void);
LZSBYTE FB_SPG(void);
LZSBYTE FB_HPN(void);
LZSBYTE FB_NOT1(void);
LZSBYTE FB_OR_2(void);
LZSBYTE FB_OR_3(void);
LZSBYTE FB_VIX(void);

LZSBYTE FB_VDV(void);
LZSBYTE FB_LIM(void);
LZSBYTE FB_ADD2(void);
LZSBYTE FB_XPQ(void);
LZSBYTE FB_NOTS(void);
LZSBYTE FB_OR_S(void);
LZSBYTE FB_RSS(void);
LZSBYTE FB_MOF(void);
LZSBYTE FB_PKW(void);
LZSBYTE FB_PSUB(void);
LZSBYTE FB_OR_12(void);
LZSBYTE FB_INT_1(void);
LZSBYTE FB_SII(void);

LZSBYTE FB_AVGN(void);
LZSBYTE FB_ASTI(void);
LZSBYTE FB_AVA(void);
LZSBYTE FB_MIS(void);
LZSBYTE FB_MULD(void);
LZSBYTE FB_PT1(void);
LZSBYTE FB_PLI6(void);
LZSBYTE FB_PIC2F(void);
LZSBYTE FB_RGE(void);
LZSBYTE FB_DEZ(void);
LZSBYTE FB_DEL(void);
LZSBYTE FB_NFN2(void);
LZSBYTE FB_N2NF(void);
LZSBYTE FB_SBW(void);


/*--------------     yyp add comm function block  ------------*/
LZSBYTE FB_PIB4(void);
LZSBYTE FB_GIB(void);
LZSBYTE FB_SMMR(void);
LZSBYTE FB_SUMR(void);
LZSBYTE FB_HSUC02(void);
LZSBYTE FB_FRB(void);
LZSBYTE FB_TSBG2(void);
LZSBYTE FB_UMR(void);
LZSBYTE FB_FMR(void);
LZSBYTE FB_SSRD(void);
LZSBYTE FB_MSIM(void);
LZSBYTE FB_SSWR(void);
LZSBYTE FB_MOB8(void);
LZSBYTE FB_GSB(void);
LZSBYTE FB_TCO(void);
LZSBYTE FB_GRB(void);
LZSBYTE FB_DRB(void);
LZSBYTE FB_TSBM0(void);
LZSBYTE FB_TSBG0(void);


LZSBYTE FB_MODSET(void);
LZSBYTE FB_FIF(void);
LZSBYTE FB_MBSU02(void);
LZSBYTE FB_RBSU(void);
LZSBYTE FB_FMRS(void);
LZSBYTE FB_MEBV2(void);
LZSBYTE FB_SWMT(void);
LZSBYTE FB_MFREE(void);

LZSBYTE FB_DWR_10DW(void);
LZSBYTE FB_TSBM1(void);
LZSBYTE FB_SERSW(void);


/*--------------   huhuan      ------------*/
LZSBYTE FB_MUX8_W(void);
LZSBYTE FB_MUX8_DW(void);
LZSBYTE FB_MUX8_I(void);
LZSBYTE FB_MUX8_DI(void);
LZSBYTE FB_NSW_W(void) ;
LZSBYTE FB_NSW_DW(void);
LZSBYTE FB_NSW_I(void);
LZSBYTE FB_NSW_DI(void);
LZSBYTE FB_BBF0F(void);
LZSBYTE FB_ADD_I(void);

LZSBYTE FB_ADD_DI(void);
/*LZSBYTE FB_ADD_LR(void);*/
LZSBYTE FB_SUB_I(void) ;
LZSBYTE FB_SUB_DI(void);
/*LZSBYTE FB_SUB_LR(void);//325*/
LZSBYTE FB_I_R(void);
LZSBYTE FB_R_I(void);
LZSBYTE FB_DI_R(void);
LZSBYTE FB_R_DI(void);
LZSBYTE FB_I_W(void) ;
LZSBYTE FB_DI_DW(void);
LZSBYTE FB_W_I(void) ;
LZSBYTE FB_DW_DI(void);

LZSBYTE FB_RMR(void);
LZSBYTE FB_RAR2(void);
LZSBYTE FB_RRG(void);
LZSBYTE FB_RAS(void);
LZSBYTE FB_RLA(void);

/*--------------   SUYUN      ------------*/
LZSBYTE FB_THS(void);
LZSBYTE FB_FIT(void);
LZSBYTE FB_MWSW(void);
LZSBYTE FB_MWV4(void);
LZSBYTE FB_MRSW(void);
LZSBYTE FB_SOG(void);
LZSBYTE FB_V2V1(void);
LZSBYTE FB_V1V2(void);
LZSBYTE FB_BCD1(void);

LZSBYTE FB_RCB(void);

LZSBYTE FB_TSU(void);
LZSBYTE FB_TDF(void);
LZSBYTE FB_TGS(void);



/******************************************
 *  SKK TEST
 * ***************************************/
LZSBYTE FB_CVT(void);
LZSBYTE FB_CRV_P(void);
LZSBYTE FB_CTV_P(void);
LZSBYTE FB_PRODP(void);
LZSBYTE FB_RSUD(void);
LZSBYTE FB_WSUD(void);

LZSBYTE FB_ETHI(void);
LZSBYTE FB_TGT_P(void);
LZSBYTE FB_TGR_P(void);
LZSBYTE FB_SRTC(void);/*Index = 380, SKK insert 2010-04-13*/

/******************************************
 *  SUE 19
 * ***************************************/
/*LZSBYTE FB_UMR_UDI(void);/*SUE FOR TEST*/
LZSBYTE FB_NCM_W(void);/*YUHAI FOR TEST*/
/*LZSBYTE FB_NFV2(void);*//*YUHAI FOR TEST*//*
LZSBYTE FB_V2NF(void);*//*YUHAI FOR TEST*/


LZSBYTE FB_DSURD(void);
LZSBYTE FB_DSUWR(void);

LZSBYTE FB_DRD(void);
LZSBYTE FB_DRD_I(void);
LZSBYTE FB_DRD_DI(void);
LZSBYTE FB_DRD_UI(void);
LZSBYTE FB_DRD_UDI(void);
LZSBYTE FB_DRD_W(void);
LZSBYTE FB_DRD_DW(void);
LZSBYTE FB_DRD_BY(void);

LZSBYTE FB_DWR(void);
LZSBYTE FB_DWR_I(void);
LZSBYTE FB_DWR_DI(void);
LZSBYTE FB_DWR_UI(void);
LZSBYTE FB_DWR_UDI(void);
LZSBYTE FB_DWR_W(void);
LZSBYTE FB_DWR_DW(void);
LZSBYTE FB_DWR_BY(void);

/******************************************
 * HUHUAN 16
 * ***************************************/
LZSBYTE FB_DRD_8(void);
LZSBYTE FB_DRD_8I(void);
LZSBYTE FB_DRD_8DI(void);
LZSBYTE FB_DRD_8UI(void);
LZSBYTE FB_DRD_8UDI(void);
LZSBYTE FB_DRD_8W(void);
LZSBYTE FB_DRD_8DW(void);
LZSBYTE FB_DRD_8BY(void);

LZSBYTE FB_DWR_8(void);
LZSBYTE FB_DWR_8I(void);
LZSBYTE FB_DWR_8DI(void);
LZSBYTE FB_DWR_8UI(void);
LZSBYTE FB_DWR_8UDI(void);
LZSBYTE FB_DWR_8W(void);
LZSBYTE FB_DWR_8DW(void);
LZSBYTE FB_DWR_8BY(void);


/******************************************
 * LINAN
 * ***************************************/
LZSBYTE FB_TGH3(void);
LZSBYTE FB_TCP(void);

LZSBYTE FB_DIO_INIT(void);
LZSBYTE FB_DI1(void);
LZSBYTE FB_DI8(void);
LZSBYTE FB_DI16(void);
LZSBYTE FB_DI32(void);

LZSBYTE FB_DO1(void);
LZSBYTE FB_DO8(void);
LZSBYTE FB_DO16(void);
LZSBYTE FB_DO32(void);

LZSBYTE FB_DA_INIT(void);
LZSBYTE FB_DA_1(void);
LZSBYTE FB_DA_4(void);
LZSBYTE FB_DA_8(void);
LZSBYTE FB_DA_16(void);




/*================================= ADD BY ZLL FOR TASK RUNNING TIME TEST 20100319 =============*/

LZSBYTE FB_TASK_LOCK(void);  /*G2 238*/
LZSBYTE FB_TASK_EXEC(void);  /*G2 239*/

LZSBYTE FB_PRD_T(void);  /*G2 240*/
LZSBYTE FB_PRD_I1(void); /*G2 241*/
LZSBYTE FB_PSWT_T(void); /*G2 242*/
LZSBYTE FB_PRD_S(void);  /*G2 243*/
LZSBYTE FB_SHM_T(void);  /*G2 244*/
LZSBYTE FB_P_TEMP(void); /*G2 245*/



/*************************************************************/
/*add by yuhai 20100705*/
/*************************************************************/
LZSBYTE FB_AND12(void); 	/*Index = 381*/
LZSBYTE FB_BDK10(void); 	/*Index = 382*/
LZSBYTE FB_BMX8(void); 	/*Index = 383*/
LZSBYTE FB_CTR(void); 	/*Index = 384*/
LZSBYTE FB_END(void); 	/*Index = 385*/
/*LZSBYTE FB_I2NF(void); 	*//*Index = 386*/
LZSBYTE FB_NAN4(void); 	/*Index = 387*/
/*LZSBYTE FB_NFI2(void); 	*//*Index = 388*/
LZSBYTE FB_SET_1(void); 	/*Index = 389*/
LZSBYTE FB_SHD(void); 	/*Index = 390*/
LZSBYTE FB_SQU(void); 	/*Index = 391*/
LZSBYTE FB_TDS(void); 	/*Index = 392*/
LZSBYTE FB_THEN_1(void); 	/*Index = 393*/
LZSBYTE FB_XOR22(void); 	/*Index = 394*/
LZSBYTE FB_MRV4(void);/*Index = 395*/


/*************************************************************/
/*add by huhuan 20100701*/
/*************************************************************/
  LZSBYTE FB_USF(void);		/*Index = 451*/
  LZSBYTE  FB_B1V2(void);		/*Index = 452*/
  LZSBYTE  FB_PSL(void);		/*Index = 453*/
  LZSBYTE  FB_RAR4(void);	/*Index = 454*/
  LZSBYTE  FB_SIN0F(void);		/*Index = 455*/
  LZSBYTE  FB_SYF1(void);		/*Index = 456*/
  LZSBYTE  FB_SYF4(void);	/*Index = 457*/
  LZSBYTE  FB_TFI2(void);		/*Index = 458*/



/*************************************************************/
/*add by yyp 20100701*/
/*************************************************************/
LZSBYTE FB_RTC003(void);
LZSBYTE FB_MEDV2(void);


/*************************************************************/
/*add by NEW B2B 20101203*/
/*************************************************************/
LZSBYTE FB_NAN2(void);
LZSBYTE FB_PDF2F(void);
LZSBYTE FB_AD_INIT(void);
LZSBYTE FB_AD_RD(void);

LZSBYTE FB_CTBV1(void);/*Index = 403*/

LZSBYTE FB_F_I(void); /*Index = 173*/
LZSBYTE FB_I_F(void); /*Index = 174*/
LZSBYTE FB_SET_R(void); /*Index = 175*/
/**********************************************************
*20101216 SKK RED ETH FB
***********************************************************/
LZSBYTE FB_EPI(void);
LZSBYTE FB_TGR_P1(void);
LZSBYTE FB_TGT_P1(void);
LZSBYTE FB_MYTESTFB1(void);

/***************************************************
 * 20110315 Simadyn D datatype conversion fb
 * ************************************************/
 LZSBYTE FB_N2V2(void);
 LZSBYTE FB_V2N2(void);
 LZSBYTE FB_N4V4(void);
 LZSBYTE FB_V4N4(void);

#endif
#ifdef __cplusplus
   }
#endif

#endif /*_OEM_FB_H_*/
