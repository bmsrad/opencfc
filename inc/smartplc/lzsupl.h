#ifndef _LZSUPL_H_
#define _LZSUPL_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

/* */
/* Functions to realize and control the upload */
/* */
void  LzsUplInitUpload     (void);
LZSBYTE  LzsUplGetSegInfo (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p, LZSBOOL fFailOnError_p);
LZSBYTE  LzsUplGetSegData     (LZSBYTE bConnectionId_p, tLzsPSCmd LZSFAR* pLzsPSCmd_p);
                                  



#endif
