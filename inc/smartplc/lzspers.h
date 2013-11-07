#ifndef _LZSPERS_H_
#define _LZSPERS_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mi, 27 Jan  99                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsSaveSystem(LZSCONST LZSCHAR * pszStorageName_p);
LZSPUBLIC32 LZSBYTE LZSPUBLIC LzsRestoreSystem (LZSCONST LZSCHAR * pszStorageName_p);
unsigned long LzsGetPersistenceLength(void);

void LzsInitializeCRCLookup();

#endif
