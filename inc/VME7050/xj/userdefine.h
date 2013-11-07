#ifndef _USER_DEFINE_H_
#define _USER_DEFINE_H_

/*
 * #include	"vme7050/xj/pci9030.h"
 * */
/*******************************************************
 *  HW parameter
 * *****************************************************/

#define MAX_SLOTS 					10
#define MAX_RECEIVE_DATA			27




/*#define  pi 3.1415926*/

/*#define OutValueLimit( Out, P_limit, N_limit)  ((Out) > (N_limit) ? (Out) :( N_limit)) < (P_limit)? ((Out) > (N_limit) ? (Out) :( N_limit)): (P_limit)*/

int RECEIVE_DATA[270];    /*最大就是10*27*/

#define ENDIAN_BIG2LITTLE(VAL)     VAL /*(((VAL&0xff)<<8) | ((VAL&0xff00)>>8))*/

/**************************************************************
 * hardware definations
 * 
 * ************************************************************/
#define		TDM_NUM							0
#define		TDM_BAR							2
#define		TDM_DIVIDER_OFFSET				4
#define		TDM_FIFO_OFFSET					0
#define		TDM_LENTH_OFFSET				12
#define		TDM_REEN_OFFSET					0x24

#define		ETS_NUM							0
#define		ETS_BAR							3
#define		ETS_INNERPHASE_OFFSET			16
#define		ETS_PHASESTEP_OFFSET			0
#define		ETS_TRIGGERSET_OFFSET			12

/*****************************************************************
 * open some define 
 * **************************************************************/
/*#undef  _OPEN_PCI_DRIVE_*/
#define  _OPEN_PCI_DRIVE_
#define  _MODE_













#endif
