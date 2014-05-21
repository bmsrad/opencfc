#ifndef _LZSFORCE_H_
#define _LZSFORCE_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 2002                                                                 */
/*                                                                              */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

#ifdef _FORCE_VARIABLES_
void  LzsForceInitForceTab (void);
LZSBYTE  LzsForceAddItem (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsForceDeleteItem (tLzsPSCmd LZSFAR* pLzsPSCmd_p);
LZSBYTE  LzsForceVariable (tLzsForceItem LZSFAR* pLzsForceItem_p);
LZSBYTE LzsForce(void);

extern tLzsForceItem  ForceLst_l[LZSMAXWATCH];
#endif

#endif
