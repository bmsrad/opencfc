/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Do, 11 Mrz  99                                                                */
/*    13.11.1996   -rs                                                           */
/* DESCRIPTION:  OS specific and compiler dependend defines                      */
/*********************************************************************************/

/* ================================================= */
/* NOTE:    Please copy the correct OEM_DEF.H. */
/*             from the OEM Directory */
/*            or create a new one out of this template */
/* ================================================= */
    

#ifndef _OEM_DEF_H_
#define _OEM_DEF_H_



/*    special ID to identifie the OEM */
/*  you will get this number from infoteam */
#define     OEM_ID_NR    699            

/*  here you can specifie a hardware version and revision number */
#define     HARDWARE_VERSION       1
#define     HARDWARE_REVISION      0
/*  here you can set an identification string for your hardware */
/*  max 60 characters                                             */
extern LZSCHAR g_hardware_name[]; /* this is defined in lzsenv.c*/
#define     HARDWARE_DESCRIPTION    g_hardware_name

/*--------------------------------------------------------------------------- */
/* version number of firmware */
/*--------------------------------------------------------------------------- */
#define FW_VERSION      9                   /* FW-Version  (1.*) */
#define FW_REVISION     0                  /* FW-Revision (*.00) */


#endif  /* ifndef _OEM_DEF_H_ */
