#ifndef _BSTR_H_
#define _BSTR_H_


/*----------------------------------------------------------------------------*/
/* FUNCTION: BstrSendDataToServer                                             */
/* DESCRIPT: this function should send data to a bytestream server            */
/* CALLED:   NetByteStream interface                                          */
/*----------------------------------------------------------------------------*/
LZSBYTE BstrSendDataToServer(
        const LZSBYTE * pClientData_p,        /* [i] Data for Server */
        LZSDWORD dwMessageSize_p             /* [i] Number of bytes in this message */
        );
#endif
