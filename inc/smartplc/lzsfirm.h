#ifndef _LZSFIRM_H_
#define _LZSFIRM_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

/* */
/* functions to manage and execute firmware functions */
/* */
void  LzsExecInitFrmwBlcks (void);
void     LzsExecCloseFrmwBlcks (void);      /* [SYSTEC/CANopen: 23.08.2006 -rs]: function inserted */
LZSBYTE  LzsExecGetIecErrCode (void);
LZSBOOL  LzsExecFrmwFnct      (tPlcFrmwModNr FrmwModNr_p);

#endif /*_LZSFIRM_H_*/
