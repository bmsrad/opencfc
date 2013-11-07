#ifndef _LZSVAR_H_
#define _LZSVAR_H_


LZSPUBLIC32 LZSBOOL LzsVarGetVarInfo(LZSCHAR LZSFAR*szPath,tVarDes LZSFAR*sVarDes);
LZSPUBLIC32 tPlcMemPtr LzsVarGetVarAddress(LZSCHAR LZSFAR*szPath);


/* the variable table is in segment 8 of program 0*/
#define LZSVARTABLESEGMENT 8
#define LZSVARTABLESEGMENTTABLE 0

#endif
