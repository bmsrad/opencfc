/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 24 Aug  99                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

#ifndef _LZSNCC_H_
#define _LZSNCC_H_

#define NATIVECODE_HELPSEG_SIZE 76 /* size of help segment */
#define NATIVECODE_HELPSEG_NR 3 /* number of help segment */

/*layout of help segment is platform specific
 see the according lzsncc.c file
*/

LZSBOOL LzsNccUpdateInstInHelpSeg(LZSINT currInst);    /*this is the only thing that changes within a task*/
                                                    /*and we should keep it up to date*/
LZSBOOL LzsNccInitHelpSeg(void);    /* initialize the constant part of nc help segment, called after download */

LZSBOOL LzsNccInitializeHelpSeg(void);    /* initialize the dynamic part of nc help segment */
                    /* needs to be called before execution of a task */            

LZSBYTE LzsNccCallNc(tPlchInst hChildInst_p,LZSDWORD dOffset_p);

#endif
