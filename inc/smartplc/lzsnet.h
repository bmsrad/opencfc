#ifndef _LZSNETVAR_H_
#define _LZSNETVAR_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 9 , D-91088 Bubenreuth                     */
/* (C) 1996-2002                                                                 */
/*                                                                 */
/*                                                                               */
/* DESCRIPTION:                   */
/*********************************************************************************/

LZSBYTE LzsNetVarStart(LZSBYTE bMode_p);
LZSBYTE LzsNetVarStop(void);
LZSBYTE LzsNetVarSend(void);


LZSBYTE LzsNetVarIsMaster(void);

LZSDWORD LzsNetVarGetMasterAddress(void);

void LzsNetVarSetReceived(LZSBOOL fSet);
LZSBYTE LzsNetVarReceive(void);

void LzsNetVarSetExecuted(LZSBOOL fSet);

LZSBOOL LzsNetVarGetReceived(void);

LZSBOOL LzsNetVarGetExecuted(void);

LZSBOOL LzsNetVarRTS(void);

#endif
