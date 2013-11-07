/*********************************************************************

  (c) 1999 infoteam Software GmbH, D-91088 Bubenreuth, Am Bauhof 4

  PROJECT:        WINLZS.DLL

  SWC[i]         lzsbstr.h    

 ----------------------------------------------------------------------

  DESCRIPTION:    Bytestream interface for networkprotokoll

---------------------------------------------------------------------*/

#ifndef _LZS_BSTR_H_
#define _LZS_BSTR_H_

/* ------------------------------------------------------------------- *
    DESCRIPTION:    
    RETURN VALUE:   
--------------------------------------------------------------------- */
typedef struct tBstrBuffer
{
    LZSBOOL    fStatus;
    LZSDWORD    dwDataLen;
    LZSBYTE    bDataType;
    LZSDWORD    dwCurrentPos;
};


LZSPUBLIC32    LZSBYTE  LZSPUBLIC  BstrSendDataToClient(
        LZSBYTE * pClientData_p,            /* [o] Data to client */
        LZSDWORD dwMessageSize_p            /* [i] Number of bytes in this message */
        );

#endif

