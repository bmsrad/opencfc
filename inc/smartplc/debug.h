/*////////////////////////////////////////////////////////////////////////////////////////////////// */
/*        infoteam software GmbH , Am bauhof 4 , 91088 Bubenreuth */
/*        Embedded Controller Debugging Support */
/* */

/* Macro LOGCHAR will log individual characters into a cyclic ringbuffer, */
/* starting over at the beginning when hitting the end */
#define LOGCHAR(data, buffer, index) {buffer[index++]=data;if (index>=sizeof(buffer)) {index=0;}}

/* Macro LOGSTRING will log string messages into a cyclic ringbuffer */
#define LOGSTRING(str,buffer,index) {int i; for (i=0;i<strlen(str);i++) {LOGCHAR(str[i], buffer, index);} buffer[index]='\0';}


/* output one character */
extern void DbgLogChar(LZSCHAR c_p);
/* output string */
extern void DbgLogString(LZSCONST LZSCHAR LZSFAR * psz_p);
/* output one byte in hex notation */
extern void DbgLogHexByte(LZSBYTE b_p);
/* output one word in hex notation */
extern void DbgLogHexWord(LZSWORD b_p);
/* output one double word */
extern void DbgLogHexDword(LZSDWORD dw_p);
/* enable/disable logging */
extern void DbgLogEnable (LZSBOOL b_p);
/* dump memory region */
extern void DbgLogHexDump (LZSCONST LZSCHAR LZSFAR * psz_p, LZSBYTE LZSFAR * pb_b, LZSWORD Len_p);
/* dump memory region to memory */
extern void DbgLogHexDumpToMem (LZSCONST LZSCHAR LZSFAR * psz_p, LZSBYTE LZSFAR * pb_b, LZSWORD DumpLen_p, LZSBYTE LZSFAR * pBuffer, LZSWORD BufLen_p);
/* dump pointer */
extern void DbgLogHexPointer (LZSCONST LZSCHAR LZSFAR * psz_p, void LZSFAR * ptr_p);

/* EOF */
