#ifndef _LZSPRIMG_H_
#define _LZSPRIMG_H_
/*********************************************************************************/
/* infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth                     */
/* (C) 1996-1998                                                                 */
/* Mo, 09 Nov  98                                                                 */
/*                                                                               */
/* DESCRIPTION:                                                                  */
/*********************************************************************************/

/* */
/* functions to manage the process image */
/*  */


LZSBYTE        LzsPImgWriteProcImg   (void);
LZSBYTE        LzsPImgReadProcImg    (void);
tPlcSegNr   LzsPImgGetProcImgSeg  (void);
tPlcMemPtr  LzsPImgGetProcImgPtr  (void);

LZSBYTE        LzsPImgSetProcImgSeg  (tPlcMemPtr pProcImgSeg_p, tPlcSegNr PISegNum_p);


#endif
