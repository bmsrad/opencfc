/****************************************************************************

   definition of commands for IEC1131 interpreter

   12.12.1996   -rs
   11.04.2001   ms: checked with documentation

****************************************************************************/

/*

    This is the definition of UCODE instructions available with OpenPCS
    For documentation, see the Developer's Manual.

    *************************************************************************    
    IMPORTANT: Do not modify this file (add instructions, remove instructions)
               without giving notice to sperber@infoteam.de
    *************************************************************************    

*/

#ifndef _IP_OPC_H_
#define _IP_OPC_H_

/****************************************************************************
*                                                                           *
*           I N T E R P R E T E R - O P C O D E S                           *
*                                                                            *
* ATTENTION: If you make changes in the following OpCode-definitions or        *
*             if new OpCodes are appended, please check if the string tables *
*             used to dissassemble the OpCodes have to be changed too.        *
*             They are located in IpDisTbl.h in the same directory as this   *
*             file.                                                            *
*                                                                           *
****************************************************************************/

/*--------------------------------------------------------------------------- */
/* NOP */
/*--------------------------------------------------------------------------- */

#define IP_OP_NOP                 0



/*--------------------------------------------------------------------------- */
/* program branching */
/*--------------------------------------------------------------------------- */

#define IP_OP_JMP                 1
#define IP_OP_JMPC                2
#define IP_OP_JMPCN               3

#define IP_OP_CAL                 4
#define IP_OP_CALC                5
#define IP_OP_CALCN               6

#define IP_OP_RET                 7
#define IP_OP_RETC                8
#define IP_OP_RETCN               9



/*--------------------------------------------------------------------------- */
/* access to variables */
/*--------------------------------------------------------------------------- */

#define IP_OP_LD_NEAR_BIT         10
#define IP_OP_LD_NEAR_1           11
#define IP_OP_LD_NEAR_2           12
#define IP_OP_LD_NEAR_4           13
#define IP_OP_LD_NEAR_ANY         14
#define IP_OP_LD_FAR_BIT          15
#define IP_OP_LD_FAR_1            16
#define IP_OP_LD_FAR_2            17
#define IP_OP_LD_FAR_4            18
#define IP_OP_LD_FAR_ANY          19
#define IP_OP_LD_BYREF_BIT        20
#define IP_OP_LD_BYREF_1          21
#define IP_OP_LD_BYREF_2          22
#define IP_OP_LD_BYREF_4          23
#define IP_OP_LD_BYREF_ANY        24
#define IP_OP_LD_IND_BIT          25
#define IP_OP_LD_IND_1            26
#define IP_OP_LD_IND_2            27
#define IP_OP_LD_IND_4            28
#define IP_OP_LD_IND_ANY          29

#define IP_OP_LD_CONST_TRUE       30
#define IP_OP_LD_CONST_FALSE      31
#define IP_OP_LD_CONST_1          32
#define IP_OP_LD_CONST_2          33
#define IP_OP_LD_CONST_4          34
#define IP_OP_LD_CONST_ANY        35

#define IP_OP_LDN_NEAR_BIT        36
#define IP_OP_LDN_NEAR_1          37
#define IP_OP_LDN_NEAR_2          38
#define IP_OP_LDN_NEAR_4          39
#define IP_OP_LDN_FAR_BIT         40
#define IP_OP_LDN_FAR_1           41
#define IP_OP_LDN_FAR_2           42
#define IP_OP_LDN_FAR_4           43
#define IP_OP_LDN_BYREF_BIT       44
#define IP_OP_LDN_BYREF_1         45
#define IP_OP_LDN_BYREF_2         46
#define IP_OP_LDN_BYREF_4         47
#define IP_OP_LDN_IND_BIT         48
#define IP_OP_LDN_IND_1           49
#define IP_OP_LDN_IND_2           50
#define IP_OP_LDN_IND_4           51

#define IP_OP_ST_NEAR_BIT         52
#define IP_OP_ST_NEAR_1           53
#define IP_OP_ST_NEAR_2           54
#define IP_OP_ST_NEAR_4           55
#define IP_OP_ST_NEAR_ANY         56
#define IP_OP_ST_FAR_BIT          57
#define IP_OP_ST_FAR_1            58
#define IP_OP_ST_FAR_2            59
#define IP_OP_ST_FAR_4            60
#define IP_OP_ST_FAR_ANY          61
#define IP_OP_ST_BYREF_BIT        62
#define IP_OP_ST_BYREF_1          63
#define IP_OP_ST_BYREF_2          64
#define IP_OP_ST_BYREF_4          65
#define IP_OP_ST_BYREF_ANY        66
#define IP_OP_ST_IND_BIT          67
#define IP_OP_ST_IND_1            68
#define IP_OP_ST_IND_2            69
#define IP_OP_ST_IND_4            70
#define IP_OP_ST_IND_ANY          71

#define IP_OP_STN_NEAR_BIT        72
#define IP_OP_STN_NEAR_1          73
#define IP_OP_STN_NEAR_2          74
#define IP_OP_STN_NEAR_4          75
#define IP_OP_STN_FAR_BIT         76
#define IP_OP_STN_FAR_1           77
#define IP_OP_STN_FAR_2           78
#define IP_OP_STN_FAR_4           79
#define IP_OP_STN_BYREF_BIT       80
#define IP_OP_STN_BYREF_1         81
#define IP_OP_STN_BYREF_2         82
#define IP_OP_STN_BYREF_4         83
#define IP_OP_STN_IND_BIT         84
#define IP_OP_STN_IND_1           85
#define IP_OP_STN_IND_2           86
#define IP_OP_STN_IND_4           87


#define IP_OP_S_NEAR_BIT          88
#define IP_OP_S_FAR_BIT           89
#define IP_OP_S_BYREF_BIT         90
#define IP_OP_S_IND_BIT           91
#define IP_OP_R_NEAR_BIT          92
#define IP_OP_R_FAR_BIT           93
#define IP_OP_R_BYREF_BIT         94
#define IP_OP_R_IND_BIT           95

#define IP_OP_CREATE_REFERENCE    96
#define IP_OP_LD_REFERENCE        97
#define IP_OP_ST_REFERENCE        98
#define IP_OP_ADD_OFFSET          99

#define IP_OP_LD_INSTANCE_DATA    100
#define IP_OP_ST_INSTANCE_DATA    101


#define IP_OP_LDS_NEAR_BIT        102
#define IP_OP_LDS_NEAR_1          103
#define IP_OP_LDS_NEAR_2          104
#define IP_OP_LDS_NEAR_4          105
#define IP_OP_LDS_NEAR_ANY        106
#define IP_OP_LDS_FAR_BIT         107
#define IP_OP_LDS_FAR_1           108
#define IP_OP_LDS_FAR_2           109
#define IP_OP_LDS_FAR_4           110
#define IP_OP_LDS_FAR_ANY         111
#define IP_OP_LDS_BYREF_BIT       112
#define IP_OP_LDS_BYREF_1         113
#define IP_OP_LDS_BYREF_2         114
#define IP_OP_LDS_BYREF_4         115
#define IP_OP_LDS_BYREF_ANY       116
#define IP_OP_LDS_IND_BIT         117
#define IP_OP_LDS_IND_1           118
#define IP_OP_LDS_IND_2           119
#define IP_OP_LDS_IND_4           120
#define IP_OP_LDS_IND_ANY         121

#define IP_OP_LDS_CONST_TRUE      122
#define IP_OP_LDS_CONST_FALSE     123
#define IP_OP_LDS_CONST_1         124
#define IP_OP_LDS_CONST_2         125
#define IP_OP_LDS_CONST_4         126
#define IP_OP_LDS_CONST_ANY       127

#define IP_OP_LDNS_NEAR_BIT       128
#define IP_OP_LDNS_NEAR_1         129
#define IP_OP_LDNS_NEAR_2         130
#define IP_OP_LDNS_NEAR_4         131
#define IP_OP_LDNS_FAR_BIT        132
#define IP_OP_LDNS_FAR_1          133
#define IP_OP_LDNS_FAR_2          134
#define IP_OP_LDNS_FAR_4          135
#define IP_OP_LDNS_BYREF_BIT      136
#define IP_OP_LDNS_BYREF_1        137
#define IP_OP_LDNS_BYREF_2        138
#define IP_OP_LDNS_BYREF_4        139
#define IP_OP_LDNS_IND_BIT        140
#define IP_OP_LDNS_IND_1          141
#define IP_OP_LDNS_IND_2          142
#define IP_OP_LDNS_IND_4          143

#define IP_OP_PUSH_AE             144
#define IP_OP_POP_AE              145
#define IP_OP_PUSH_REF            146
#define IP_OP_POP_REF             147
#define IP_OP_PUSH_AE_ANY         148
#define IP_OP_POP_AE_ANY          149

#define IP_OP_RESTORE_DATA        150



/*--------------------------------------------------------------------------- */
/* operators */
/*--------------------------------------------------------------------------- */

#define IP_OP_AND_BIT             151
#define IP_OP_AND_1               152
#define IP_OP_AND_2               153
#define IP_OP_AND_4               154

#define IP_OP_OR_BIT              155
#define IP_OP_OR_1                156
#define IP_OP_OR_2                157
#define IP_OP_OR_4                158

#define IP_OP_XOR_BIT             159
#define IP_OP_XOR_1               160
#define IP_OP_XOR_2               161
#define IP_OP_XOR_4               162

#define IP_OP_ADD_1               163
#define IP_OP_ADD_1_SGN           164
#define IP_OP_ADD_2               165
#define IP_OP_ADD_2_SGN           166
#define IP_OP_ADD_4               167
#define IP_OP_ADD_4_SGN           168
#define IP_OP_ADD_FLOAT           169

#define IP_OP_SUB_1               170
#define IP_OP_SUB_1_SGN           171
#define IP_OP_SUB_2               172
#define IP_OP_SUB_2_SGN           173
#define IP_OP_SUB_4               174
#define IP_OP_SUB_4_SGN           175
#define IP_OP_SUB_FLOAT           176

#define IP_OP_MUL_1               177
#define IP_OP_MUL_1_SGN           178
#define IP_OP_MUL_2               179
#define IP_OP_MUL_2_SGN           180
#define IP_OP_MUL_4               181
#define IP_OP_MUL_4_SGN           182
#define IP_OP_MUL_FLOAT           183

#define IP_OP_DIV_1               184
#define IP_OP_DIV_1_SGN           185
#define IP_OP_DIV_2               186
#define IP_OP_DIV_2_SGN           187
#define IP_OP_DIV_4               188
#define IP_OP_DIV_4_SGN           189
#define IP_OP_DIV_FLOAT           190

#define IP_OP_GT_BIT              191
#define IP_OP_GT_1                192
#define IP_OP_GT_1_SGN            193
#define IP_OP_GT_2                194
#define IP_OP_GT_2_SGN            195
#define IP_OP_GT_4                196
#define IP_OP_GT_4_SGN            197
#define IP_OP_GT_FLOAT            198

#define IP_OP_GE_BIT              199
#define IP_OP_GE_1                200
#define IP_OP_GE_1_SGN            201
#define IP_OP_GE_2                202
#define IP_OP_GE_2_SGN            203
#define IP_OP_GE_4                204
#define IP_OP_GE_4_SGN            205
#define IP_OP_GE_FLOAT            206

#define IP_OP_LE_BIT              207
#define IP_OP_LE_1                208
#define IP_OP_LE_1_SGN            209
#define IP_OP_LE_2                210
#define IP_OP_LE_2_SGN            211
#define IP_OP_LE_4                212
#define IP_OP_LE_4_SGN            213
#define IP_OP_LE_FLOAT            214

#define IP_OP_LT_BIT              215
#define IP_OP_LT_1                216
#define IP_OP_LT_1_SGN            217
#define IP_OP_LT_2                218
#define IP_OP_LT_2_SGN            219
#define IP_OP_LT_4                220
#define IP_OP_LT_4_SGN            221
#define IP_OP_LT_FLOAT            222

#define IP_OP_EQ_BIT              223
#define IP_OP_EQ_1                224
#define IP_OP_EQ_2                225
#define IP_OP_EQ_4                226

#define IP_OP_NE_BIT              227
#define IP_OP_NE_1                228
#define IP_OP_NE_2                229
#define IP_OP_NE_4                230




/*--------------------------------------------------------------------------- */
/* typecast / handling of arrays */
/*--------------------------------------------------------------------------- */


#define IP_OP_TYPECAST            231 
/* trunc has 239 */

#define IP_OP_SELCT_ARRAY_IND     235

/* new mr 20.03.98 */
#define IP_OP_EQ_ANY  232
#define IP_OP_NE_ANY  233
#define IP_OP_GT_ANY  234

#define IP_OP_GE_ANY  236
#define IP_OP_LT_ANY  237
#define IP_OP_LE_ANY  238
                           
#define IP_OP_TRUNC               239  /* (MR: Mo, 01 Jun 98) */
                         

#define IP_OP_CREATE_BITREF_NEAR    240
#define IP_OP_CREATE_BITREF_FAR     241
#define IP_OP_CREATE_BITREF_BYREF   242
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* DO NEVER USE */
#define IP_OP_CREATE_BITREF_IND     243
/* DO NEVER USE */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */


/* String Stores  */
#define IP_OP_ST_NEAR_STRING        244
#define IP_OP_ST_FAR_STRING         245
#define IP_OP_ST_BYREF_STRING       246
#define IP_OP_ST_IND_STRING         247

/* Creation of reference (far access) (MR: Mo, 01 Jun 98) */
#define IP_OP_CREATE_REFERENCE_FAR   248
#define IP_OP_CALCEN                 249    /* <--------- CFE/CBE DO NOT NEED IT ANY MORE [OP-02.03.2001].*/

/*--------------------------------------------------------------------------- */
/* extensions / contrl commands */
/*--------------------------------------------------------------------------- */

#define IP_OP_EXT1                252
    #define IP_OP_EXT2                253   /* B.S. 24.10.00*/
#define IP_OP_BREAK               254




/****************************************************************************
*                                                                           *
*           I N T E R P R E T E R - E X T E N S I O N S                     *
*                                                                           *
****************************************************************************/

/*--------------------------------------------------------------------------- */
/* extensions negation */
/*--------------------------------------------------------------------------- */
/* #define IP_EX_                      0 */
#define IP_EX_NOT_BIT             1
#define IP_EX_NOT_1               2
#define IP_EX_NOT_2               3
#define IP_EX_NOT_4               4



/*--------------------------------------------------------------------------- */
/* extensions shift/rotate */
/*--------------------------------------------------------------------------- */

#define IP_EX_SHL_1               5
#define IP_EX_SHL_2               6
#define IP_EX_SHL_4               7
#define IP_EX_SHR_1               8
#define IP_EX_SHR_2               9
#define IP_EX_SHR_4               10

#define IP_EX_ROL_1               11
#define IP_EX_ROL_2               12
#define IP_EX_ROL_4               13
#define IP_EX_ROR_1               14
#define IP_EX_ROR_2               15
#define IP_EX_ROR_4               16

/* abs MR 200398 */
/*   for unsigned no command is generated */
#define IP_EX_ABS_1_SGN     17
#define IP_EX_ABS_2_SGN     18
#define IP_EX_ABS_4_SGN     19
#define IP_EX_ABS_FLOAT 20

/* float */
/* MR: Do, 19 Mrz 98 */
#define IP_EX_EXP       21
#define IP_EX_SQRT      22
#define IP_EX_LN        23
#define IP_EX_LOG       24
#define IP_EX_SIN       25
#define IP_EX_COS       26
#define IP_EX_TAN       27
#define IP_EX_ASIN      28   
#define IP_EX_ACOS      29
#define IP_EX_ATAN      30

#define IP_EX_CREATE_BITREF_DIR_BYREF 31

/* expt */
#define IP_EX_EXPT_1        32
#define IP_EX_EXPT_1_SGN    33
#define IP_EX_EXPT_2        34
#define IP_EX_EXPT_2_SGN    35
#define IP_EX_EXPT_4        36
#define IP_EX_EXPT_4_SGN    37
#define IP_EX_EXPT_FLOAT    38

/* mod */
#define IP_EX_MOD_1         39
#define IP_EX_MOD_1_SGN     40
#define IP_EX_MOD_2         41
#define IP_EX_MOD_2_SGN     42
#define IP_EX_MOD_4         43
#define IP_EX_MOD_4_SGN     44
#define IP_EX_MOD_FLOAT     45

/* move */
#define IP_EX_MOVE_1        46
#define IP_EX_MOVE_2        47
#define IP_EX_MOVE_4        48 
/*float and signed are not needed cause its a simple copy */

/* MIN */
#define IP_EX_MIN_1         49
#define IP_EX_MIN_1_SGN     50
#define IP_EX_MIN_2         51
#define IP_EX_MIN_2_SGN     52
#define IP_EX_MIN_4         53
#define IP_EX_MIN_4_SGN     54
#define IP_EX_MIN_FLOAT     55

/* MAX */
#define IP_EX_MAX_1         56
#define IP_EX_MAX_1_SGN     57
#define IP_EX_MAX_2         58
#define IP_EX_MAX_2_SGN     59
#define IP_EX_MAX_4         60
#define IP_EX_MAX_4_SGN     61
#define IP_EX_MAX_FLOAT     62

/* LIMIT */
#define IP_EX_LIMIT_1           63
#define IP_EX_LIMIT_1_SGN       64
#define IP_EX_LIMIT_2           65
#define IP_EX_LIMIT_2_SGN       66
#define IP_EX_LIMIT_4           67
#define IP_EX_LIMIT_4_SGN       68
#define IP_EX_LIMIT_FLOAT       69


/* string fkt */
#define IP_EX_LEN       70
#define IP_EX_LEFT      71
#define IP_EX_RIGHT     72
#define IP_EX_MID       73
#define IP_EX_CONCAT    74
#define IP_EX_INSERT    75
#define IP_EX_DELETE    76
#define IP_EX_REPLACE   77
#define IP_EX_FIND      78

/* MR: SA, 30 Mai 98 */
/*  only for customer P169 */
#define IP_EX_EXCHANGE_IO_WRITE 79   
#define IP_EX_EXCHANGE_IO_READ  80


/* MR: Sa, 30 Mai 98  */
/*      any for strings */
#define IP_EX_MIN_ANY   81
#define IP_EX_MAX_ANY   82 

/* Select MR: Sa, 30 Mai 98 */
#define IP_EX_SEL_BIT    83   /* not supported by cbe and ip */
#define IP_EX_SEL_1      84
#define IP_EX_SEL_2      85
#define IP_EX_SEL_4      86
#define IP_EX_SEL_ANY    87
#define IP_EX_SEL_FLOAT  88

#define IP_EX_ST_DIR_BYREF_STRING    89

/* EF: Fr, 21. Januar 2000
   instruction codes for 8-Byte operators */
#define IP_EX_LD_NEAR_8         90
#define IP_EX_LD_FAR_8          91
#define IP_EX_LD_BYREF_8        92
#define IP_EX_LD_IND_8          93
#define IP_EX_LD_CONST_8        94

#define IP_EX_LDN_NEAR_8        95   
#define IP_EX_LDN_FAR_8         96
#define IP_EX_LDN_BYREF_8       97
#define IP_EX_LDN_IND_8         98

#define IP_EX_LDS_NEAR_8        99
#define IP_EX_LDS_FAR_8         100
#define IP_EX_LDS_BYREF_8       101
#define IP_EX_LDS_IND_8         102
#define IP_EX_LDS_CONST_8       103

#define IP_EX_LDNS_NEAR_8       104
#define IP_EX_LDNS_FAR_8        105
#define IP_EX_LDNS_BYREF_8      106
#define IP_EX_LDNS_IND_8        107

#define IP_EX_ST_NEAR_8         108
#define IP_EX_ST_FAR_8          109
#define IP_EX_ST_BYREF_8        110
#define IP_EX_ST_IND_8          111

#define IP_EX_STN_NEAR_8        112
#define IP_EX_STN_FAR_8         113
#define IP_EX_STN_BYREF_8       114
#define IP_EX_STN_IND_8         115

#define IP_EX_PUSH_AE_8         116
#define IP_EX_POP_AE_8          117

#define IP_EX_AND_8             118
#define IP_EX_OR_8              119
#define IP_EX_XOR_8             120

#define IP_EX_ADD_8             121
#define IP_EX_ADD_8_SGN         122
#define IP_EX_ADD_DOUBLE        123
#define IP_EX_SUB_8             124
#define IP_EX_SUB_8_SGN         125
#define IP_EX_SUB_DOUBLE        126
#define IP_EX_MUL_8             127
#define IP_EX_MUL_8_SGN         128
#define IP_EX_MUL_DOUBLE        129
#define IP_EX_DIV_8             130
#define IP_EX_DIV_8_SGN         131
#define IP_EX_DIV_DOUBLE        132

#define IP_EX_GT_8              133
#define IP_EX_GT_8_SGN          134
#define IP_EX_GT_DOUBLE         135
#define IP_EX_GE_8              136
#define IP_EX_GE_8_SGN          137
#define IP_EX_GE_DOUBLE         138
#define IP_EX_LE_8              139
#define IP_EX_LE_8_SGN          140
#define IP_EX_LE_DOUBLE         141
#define IP_EX_LT_8              142
#define IP_EX_LT_8_SGN          143
#define IP_EX_LT_DOUBLE         144
#define IP_EX_EQ_8              145
#define IP_EX_NE_8              146

#define IP_EX_NOT_8             147
#define IP_EX_SHL_8             148
#define IP_EX_SHR_8             149
#define IP_EX_ROL_8             150
#define IP_EX_ROR_8             151

#define IP_EX_ABS_8             152
#define IP_EX_ABS_8_SGN         153
#define IP_EX_ABS_DOUBLE        154
#define IP_EX_MOD_8             155
#define IP_EX_MOD_8_SGN         156
#define IP_EX_MOD_DOUBLE        157
#define IP_EX_EXPT_8            158
#define IP_EX_EXPT_8_SGN        159
#define IP_EX_EXPT_DOUBLE       160

#define IP_EX_MOVE_8            161

#define IP_EX_MIN_8             162
#define IP_EX_MIN_8_SGN         163
#define IP_EX_MIN_DOUBLE        164
#define IP_EX_MAX_8             165
#define IP_EX_MAX_8_SGN         166
#define IP_EX_MAX_DOUBLE        167
#define IP_EX_LIMIT_8           168
#define IP_EX_LIMIT_8_SGN       169
#define IP_EX_LIMIT_DOUBLE      170
#define IP_EX_SEL_8             171
#define IP_EX_SEL_8_SGN         172
#define IP_EX_SEL_DOUBLE        173

#define IP_EX_EXP_DOUBLE        174
#define IP_EX_SQRT_DOUBLE       175
#define IP_EX_LN_DOUBLE         176
#define IP_EX_LOG_DOUBLE        177
#define IP_EX_SIN_DOUBLE        178
#define IP_EX_COS_DOUBLE        179
#define IP_EX_TAN_DOUBLE        180
#define IP_EX_ASIN_DOUBLE       181  
#define IP_EX_ACOS_DOUBLE       182
#define IP_EX_ATAN_DOUBLE       183

#define IP_EX_NEG_BIT           184
#define IP_EX_NEG_1             185
#define IP_EX_NEG_2             186
#define IP_EX_NEG_4             187
#define IP_EX_NEG_8             188
#define IP_EX_NEG_FLOAT         189
#define IP_EX_NEG_DOUBLE        190    

#define IP_EX_ADD_DT            191        /* correct is IP_EX_ADD_DT_TIME */
#define IP_EX_SUB_DT_TIME       192
#define IP_EX_SUB_DT_DT         193

#define IP_EX_INPUT_PARA_C      194
#define IP_EX_OUTPUT_PARA_C     195
#define IP_EX_END_PARA          196

#define IP_EX_EXPT_REAL48       197

#define IP_EX_LD_DIR_BYREF_BIT    198
#define IP_EX_LD_DIR_BYREF_1    199
#define IP_EX_LD_DIR_BYREF_2    200
#define IP_EX_LD_DIR_BYREF_4    201
#define IP_EX_LD_DIR_BYREF_8    202
#define IP_EX_LD_DIR_BYREF_ANY    203
#define IP_EX_LDN_DIR_BYREF_BIT    204
#define IP_EX_LDN_DIR_BYREF_1    205
#define IP_EX_LDN_DIR_BYREF_2    206
#define IP_EX_LDN_DIR_BYREF_4    207
#define IP_EX_LDN_DIR_BYREF_8    208
#define IP_EX_ST_DIR_BYREF_BIT    209
#define IP_EX_ST_DIR_BYREF_1    210
#define IP_EX_ST_DIR_BYREF_2    211
#define IP_EX_ST_DIR_BYREF_4    212
#define IP_EX_ST_DIR_BYREF_8    213
#define IP_EX_ST_DIR_BYREF_ANY    214
#define IP_EX_STN_DIR_BYREF_BIT    215
#define IP_EX_STN_DIR_BYREF_1    216
#define IP_EX_STN_DIR_BYREF_2    217
#define IP_EX_STN_DIR_BYREF_4    218
#define IP_EX_STN_DIR_BYREF_8    219

#define IP_EX_EXPT_DOUBLE_1_SGN        220     /* DOUBLE = DOUBLE ^ SINT */
#define IP_EX_EXPT_DOUBLE_1            221     /* DOUBLE = DOUBLE ^ USINT*/
#define IP_EX_EXPT_DOUBLE_2_SGN        222     /* DOUBLE = DOUBLE ^ INT*/
#define IP_EX_EXPT_DOUBLE_2            223     /* DOUBLE = DOUBLE ^ UINT*/
#define IP_EX_EXPT_DOUBLE_3_SGN        224     /* DOUBLE = DOUBLE ^ INT24*/
#define IP_EX_EXPT_DOUBLE_3            225     /* DOUBLE = DOUBLE ^ UINT24*/
#define IP_EX_EXPT_DOUBLE_4_SGN        226     /* DOUBLE = DOUBLE ^ DINT*/
#define IP_EX_EXPT_DOUBLE_4            227     /* DOUBLE = DOUBLE ^ UDINT*/
#define IP_EX_EXPT_DOUBLE_8_SGN        228     /* DOUBLE = DOUBLE ^ LINT*/
#define IP_EX_EXPT_DOUBLE_8            229     /* DOUBLE = DOUBLE ^ ULINT*/
#define IP_EX_EXPT_DOUBLE_FLOAT        230     /* DOUBLE = DOUBLE ^ REAL*/
#define IP_EX_EXPT_DOUBLE_REAL48       231     /* DOUBLE = DOUBLE ^ REAL48*/
#define IP_EX_EXPT_DOUBLE_DOUBLE       232     /* DOUBLE = DOUBLE ^ DOUBLE*/

#define IP_EX_S_DIR_BYREF_BIT         233
#define IP_EX_R_DIR_BYREF_BIT         234
#define IP_EX_LDS_DIR_BYREF_BIT       235
#define IP_EX_LDS_DIR_BYREF_1         236
#define IP_EX_LDS_DIR_BYREF_2         237
#define IP_EX_LDS_DIR_BYREF_4         238
#define IP_EX_LDS_DIR_BYREF_8         239
#define IP_EX_LDS_DIR_BYREF_ANY       240
#define IP_EX_LDNS_DIR_BYREF_BIT      241
#define IP_EX_LDNS_DIR_BYREF_1        242
#define IP_EX_LDNS_DIR_BYREF_2        243
#define IP_EX_LDNS_DIR_BYREF_4        244
#define IP_EX_LDNS_DIR_BYREF_8        245
#define IP_EX_CREATE_DIR_REFERENCE    246
#define IP_EX_CREATE_DIR_REFERENCE_FAR 247
#define IP_EX_LD_DIR_REFERENCE        248
#define IP_EX_ST_DIR_REFERENCE        249

/* ADD and SUB for ANY_DATE and TIME datatypes 
    see also IP_EX_ADD_DT, IP_EX_SUB_DT_TIME, IP_EX_SUB_DT_DT */
#define IP_EX_ADD_TOD_TIME              250
#define IP_EX_SUB_DATE_DATE              251
#define IP_EX_SUB_TOD_TIME              252
#define IP_EX_SUB_TOD_TOD              253

/* #define IP_EX_                      254 */

#define IP_EX_NOP                     255


/* ========================================================================*/
/* === REAL48 and 6 Byte datatypes (P448) B.S. 27.10.00*/
/* ========================================================================*/
#define IP_EX2_NOP               0

#define IP_EX2_LDA_NEAR          1
#define IP_EX2_LDA_BYREF         2
#define IP_EX2_LDA_FAR           3
#define IP_EX2_LDAS_NEAR         4
#define IP_EX2_LDAS_BYREF        5
#define IP_EX2_LDAS_FAR          6
/* #define IP_EX2_                     7 */
/* #define IP_EX2_                     8 */
/* #define IP_EX2_                     9 */

#define IP_EX2_LD_NEAR_6         10
#define IP_EX2_LD_FAR_6          11
#define IP_EX2_LD_BYREF_6        12
#define IP_EX2_LD_IND_6          13
#define IP_EX2_LD_CONST_6        14

#define IP_EX2_LDN_NEAR_6        15   
#define IP_EX2_LDN_FAR_6         16
#define IP_EX2_LDN_BYREF_6       17
#define IP_EX2_LDN_IND_6         18

#define IP_EX2_LDS_NEAR_6        19
#define IP_EX2_LDS_FAR_6         20
#define IP_EX2_LDS_BYREF_6       21
#define IP_EX2_LDS_IND_6         22
#define IP_EX2_LDS_CONST_6       23

#define IP_EX2_LDNS_NEAR_6       24
#define IP_EX2_LDNS_FAR_6        25
#define IP_EX2_LDNS_BYREF_6      26
#define IP_EX2_LDNS_IND_6        27

#define IP_EX2_ST_NEAR_6         28
#define IP_EX2_ST_FAR_6          29
#define IP_EX2_ST_BYREF_6        30
#define IP_EX2_ST_IND_6          31

#define IP_EX2_STN_NEAR_6        32
#define IP_EX2_STN_FAR_6         33
#define IP_EX2_STN_BYREF_6       34
#define IP_EX2_STN_IND_6         35

#define IP_EX2_PUSH_AE_6         36
#define IP_EX2_POP_AE_6          37

#define IP_EX2_AND_6             38
#define IP_EX2_OR_6              39
#define IP_EX2_XOR_6             40

#define IP_EX2_ADD_6             41
#define IP_EX2_ADD_6_SGN         42
#define IP_EX2_ADD_REAL48        43
#define IP_EX2_SUB_6             44
#define IP_EX2_SUB_6_SGN         45
#define IP_EX2_SUB_REAL48        46
#define IP_EX2_MUL_6             47
#define IP_EX2_MUL_6_SGN         48
#define IP_EX2_MUL_REAL48        49
#define IP_EX2_DIV_6             50
#define IP_EX2_DIV_6_SGN         51
#define IP_EX2_DIV_REAL48        52

#define IP_EX2_GT_6              53
#define IP_EX2_GT_6_SGN          54
#define IP_EX2_GT_REAL48         55
#define IP_EX2_GE_6              56
#define IP_EX2_GE_6_SGN          57
#define IP_EX2_GE_REAL48         58
#define IP_EX2_LE_6              59
#define IP_EX2_LE_6_SGN          60
#define IP_EX2_LE_REAL48         61
#define IP_EX2_LT_6              62
#define IP_EX2_LT_6_SGN          63
#define IP_EX2_LT_REAL48         64
#define IP_EX2_EQ_6              65
#define IP_EX2_NE_6              66

#define IP_EX2_NOT_6             67
#define IP_EX2_SHL_6             68
#define IP_EX2_SHR_6             69
#define IP_EX2_ROL_6             70
#define IP_EX2_ROR_6             71
#define IP_EX2_ABS_6             72
#define IP_EX2_ABS_6_SGN         73
#define IP_EX2_ABS_REAL48        74
#define IP_EX2_MOD_6             75
#define IP_EX2_MOD_6_SGN         76
#define IP_EX2_MOD_REAL48        77

/* #define IP_EX2_                     78 */
/* #define IP_EX2_                     79 */

#define IP_EX2_EXPT_3           80     /* REAL48 = REAL ^ INT24*/
#define IP_EX2_EXPT_3_SGN       81     /* REAL48 = REAL ^ INT24*/
#define IP_EX2_EXPT_6           82     /* REAL48 = REAL ^ INT*/
#define IP_EX2_EXPT_6_SGN       83     /* REAL48 = REAL ^ INT*/

#define IP_EX2_EXPT_REAL48_1_SGN       84     /* REAL48 = REAL48 ^ SINT*/
#define IP_EX2_EXPT_REAL48_1       85         /* REAL48 = REAL48 ^ USINT*/
#define IP_EX2_EXPT_REAL48_2_SGN       86     /* REAL48 = REAL48 ^ INT*/
#define IP_EX2_EXPT_REAL48_2       87     /* REAL48 = REAL48 ^ UINT*/
#define IP_EX2_EXPT_REAL48_3_SGN       88     /* REAL48 = REAL48 ^ INT24*/
#define IP_EX2_EXPT_REAL48_3       89     /* REAL48 = REAL48 ^ UINT24*/
#define IP_EX2_EXPT_REAL48_4_SGN       90     /* REAL48 = REAL48 ^ DINT*/
#define IP_EX2_EXPT_REAL48_4       91     /* REAL48 = REAL48 ^ UDINT*/
#define IP_EX2_EXPT_REAL48_8_SGN       92     /* REAL48 = REAL48 ^ LINT*/
#define IP_EX2_EXPT_REAL48_8       93     /* REAL48 = REAL48 ^ ULINT*/
#define IP_EX2_EXPT_REAL48_FLOAT       94      /* REAL48 = REAL48 ^ REAL*/
#define IP_EX2_EXPT_REAL48_REAL48       95        /* REAL48 = REAL48 ^ REAL48*/
#define IP_EX2_EXPT_REAL48_DOUBLE       96        /* REAL48 = REAL48 ^ DOUBLE*/

/* #define IP_EX2_                     97 */
/* #define IP_EX2_                     98 */
/* #define IP_EX2_                     99 */

#define IP_EX2_MIN_6             100
#define IP_EX2_MIN_6_SGN         101
#define IP_EX2_MIN_REAL48        102
#define IP_EX2_MAX_6             103
#define IP_EX2_MAX_6_SGN         104
#define IP_EX2_MAX_REAL48        105
#define IP_EX2_LIMIT_6           106
#define IP_EX2_LIMIT_6_SGN       107
#define IP_EX2_LIMIT_REAL48      108
#define IP_EX2_SEL_6             109
#define IP_EX2_SEL_6_SGN         110
#define IP_EX2_SEL_REAL48        111

/*#define IP_EX2_EXP_REAL48        112*/
/*#define IP_EX2_SQRT_REAL48       113*/
/*#define IP_EX2_LN_REAL48         114*/
/*#define IP_EX2_LOG_REAL48        115*/
/*#define IP_EX2_SIN_REAL48        116*/
/*#define IP_EX2_COS_REAL48        117*/
/*#define IP_EX2_TAN_REAL48        118*/
/*#define IP_EX2_ASIN_REAL48       119  */
/*#define IP_EX2_ACOS_REAL48       120*/
/*#define IP_EX2_ATAN_REAL48       121*/

#define IP_EX2_NEG_REAL48        122
#define IP_EX2_NEG_6             123

/* #define IP_EX2_                     124 */
/* #define IP_EX2_                     125 */
/* #define IP_EX2_                     126 */
/* #define IP_EX2_                     127 */
/* #define IP_EX2_                     128 */
/* #define IP_EX2_                     129 */
/* #define IP_EX2_                     130 */
/* #define IP_EX2_                     131 */
/* #define IP_EX2_                     132 */
/* #define IP_EX2_                     133 */
/* #define IP_EX2_                     134 */
/* #define IP_EX2_                     135 */
/* #define IP_EX2_                     136 */
/* #define IP_EX2_                     137 */
/* #define IP_EX2_                     138 */
/* #define IP_EX2_                     139 */
/* #define IP_EX2_                     140 */
/* #define IP_EX2_                     141 */
/* #define IP_EX2_                     142 */
/* #define IP_EX2_                     143 */
/* #define IP_EX2_                     144 */
/* #define IP_EX2_                     145 */
/* #define IP_EX2_                     146 */
/* #define IP_EX2_                     147 */
/* #define IP_EX2_                     148 */
/* #define IP_EX2_                     149 */

/* ========================================================================*/
/* === INT24 (3Byte) Datatypes (P448) B.S. 27.10.00*/
/* ========================================================================*/
#define IP_EX2_LD_NEAR_3         150
#define IP_EX2_LD_FAR_3          151
#define IP_EX2_LD_BYREF_3        152
#define IP_EX2_LD_IND_3          153
#define IP_EX2_LD_CONST_3        154

#define IP_EX2_LDN_NEAR_3        155   
#define IP_EX2_LDN_FAR_3         156
#define IP_EX2_LDN_BYREF_3       157
#define IP_EX2_LDN_IND_3         158

#define IP_EX2_LDS_NEAR_3        159
#define IP_EX2_LDS_FAR_3         160
#define IP_EX2_LDS_BYREF_3       161
#define IP_EX2_LDS_IND_3         162
#define IP_EX2_LDS_CONST_3       163

#define IP_EX2_LDNS_NEAR_3       164
#define IP_EX2_LDNS_FAR_3        165
#define IP_EX2_LDNS_BYREF_3      166
#define IP_EX2_LDNS_IND_3        167

#define IP_EX2_ST_NEAR_3         168
#define IP_EX2_ST_FAR_3          169
#define IP_EX2_ST_BYREF_3        170
#define IP_EX2_ST_IND_3          171

#define IP_EX2_STN_NEAR_3        172
#define IP_EX2_STN_FAR_3         173
#define IP_EX2_STN_BYREF_3       174
#define IP_EX2_STN_IND_3         175

#define IP_EX2_PUSH_AE_3         176
#define IP_EX2_POP_AE_3          177

#define IP_EX2_AND_3             178
#define IP_EX2_OR_3              179
#define IP_EX2_XOR_3             180

#define IP_EX2_ADD_3             181
#define IP_EX2_ADD_3_SGN         182
#define IP_EX2_SUB_3             183
#define IP_EX2_SUB_3_SGN         184
#define IP_EX2_MUL_3             185
#define IP_EX2_MUL_3_SGN         186
#define IP_EX2_DIV_3             187
#define IP_EX2_DIV_3_SGN         188

#define IP_EX2_GT_3              189
#define IP_EX2_GT_3_SGN          190
#define IP_EX2_GE_3              191
#define IP_EX2_GE_3_SGN          192
#define IP_EX2_LE_3              193
#define IP_EX2_LE_3_SGN          194
#define IP_EX2_LT_3              195
#define IP_EX2_LT_3_SGN          196
#define IP_EX2_EQ_3              197
#define IP_EX2_NE_3              198

#define IP_EX2_NOT_3             199
#define IP_EX2_SHL_3             200
#define IP_EX2_SHR_3             201
#define IP_EX2_ROL_3             202
#define IP_EX2_ROR_3             203

#define IP_EX2_ABS_3             204
#define IP_EX2_ABS_3_SGN         205
#define IP_EX2_MOD_3             206
#define IP_EX2_MOD_3_SGN         207

/*#define IP_EX2_EXPT_DOUBLE_3       208        // DOUBLE = DOUBLE ^ UINT24*/
/*#define IP_EX2_EXPT_DOUBLE_3_SGN       209        // DOUBLE = DOUBLE ^ INT24*/

/*#define IP_EX2_EXPT_REAL_3       210      // REAL = REAL ^ UINT24*/
/*#define IP_EX2_EXPT_REAL_3_SGN       211      // REAL = REAL ^ INT24*/



#define IP_EX2_MIN_3             212
#define IP_EX2_MIN_3_SGN         213
#define IP_EX2_MAX_3             214
#define IP_EX2_MAX_3_SGN         215
/*#define IP_EX2_LIMIT_3           216*/
/*#define IP_EX2_LIMIT_3_SGN       217*/
/*#define IP_EX2_LIMIT_REAL48      218*/
/*#define IP_EX2_SEL_3             219*/
/*#define IP_EX2_SEL_3_SGN         220*/
/*#define IP_EX2_SEL_REAL48        221*/


#define IP_EX2_NEG_3        222

#define IP_EX2_LD_DIR_BYREF_6        223
#define IP_EX2_LDN_DIR_BYREF_6       224
#define IP_EX2_LDS_DIR_BYREF_6       225
#define IP_EX2_LDNS_DIR_BYREF_6      226
#define IP_EX2_ST_DIR_BYREF_6        227
#define IP_EX2_STN_DIR_BYREF_6       228
#define IP_EX2_LD_DIR_BYREF_3        229
#define IP_EX2_LDN_DIR_BYREF_3       230
#define IP_EX2_LDS_DIR_BYREF_3       231
#define IP_EX2_LDNS_DIR_BYREF_3      232
#define IP_EX2_ST_DIR_BYREF_3        233
#define IP_EX2_STN_DIR_BYREF_3       234

#define IP_EX2_ST_NEAR_WSTRING         235
#define IP_EX2_ST_FAR_WSTRING         236
#define IP_EX2_ST_BYREF_WSTRING         237
#define IP_EX2_ST_IND_WSTRING         238
#define IP_EX2_ST_DIR_BYREF_WSTRING     239

#define IP_EX2_ST_NEAR_ARRAY         240 
#define IP_EX2_ST_FAR_ARRAY             241 
#define IP_EX2_ST_BYREF_ARRAY         242 
#define IP_EX2_ST_IND_ARRAY             243
#define IP_EX2_ST_DIR_BYREF_ARRAY     244

/* #define IP_EX2_                     245 */
/* #define IP_EX2_                     246 */
/* #define IP_EX2_                     247 */
/* #define IP_EX2_                     248 */
/* #define IP_EX2_                     249 */
/* #define IP_EX2_                     250 */
/* #define IP_EX2_                     251 */
/* #define IP_EX2_                     252 */
/* #define IP_EX2_                     253 */
/* #define IP_EX2_                     254 */
/* #define IP_EX2_                     255 */

/*--------------------------------------------------------------------------- */
/* operands for command IP_OP_TYPECAST */
/*--------------------------------------------------------------------------- */
/* for ANY_NUM, ANY_BIT */
#define kIpBit1                   0
#define kIpBit8                   1
#define kIpBit16                  2
#define kIpBit32                  3
#define kIpBit64                  4
#define kIpBit24                  5



#define kIpSigned                 0x80  /* OR mask for extension of */
                                        /* kIpBit8, kIpBit16 and kIpBit32 */

/* all other types which are not ANY_NUM, ANY_BIT (MR 30 05 98) */
#define IP_TYPE_REAL  4
#define IP_TYPE_LREAL  6
#define IP_TYPE_STRING 8
#define IP_TYPE_TIME 12
#define IP_TYPE_TOD 16
#define IP_TYPE_DT  20
#define IP_TYPE_DATE 24     
#define IP_TYPE_BCD 28
#define IP_TYPE_REAL48 32



#endif /* _IP_OPC_H_ */


