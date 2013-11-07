/****************************************************************************

   (c) 1998 infoteam Software GmbH, D-91088 Bubenreuth, Am Bauhof 4

   command prototypes for IEC1131 interpreter

   27.01.1997   -rs

****************************************************************************/

#ifndef _IP_CMDS_H_
#define _IP_CMDS_H_

/****************************************************************************
*                                                                           *
*           I N T E R P R E T E R - O P C O D E S                           *
*                                                                           *
****************************************************************************/

/*--------------------------------------------------------------------------- */
/* NOP */
/*--------------------------------------------------------------------------- */

void IpIP_OP_NOP                 (void);



/*--------------------------------------------------------------------------- */
/* program branching */
/*--------------------------------------------------------------------------- */

void IpIP_OP_JMP                 (void);
void IpIP_OP_JMPC                (void);
void IpIP_OP_JMPCN               (void);



/*-cd- 19990824  ncc   */
/* these functions are called by IpIP_OP_CAL and itself recursively */
LZSBOOL  IpIP_CALL (tPlchInst hChildInst, LZSWORD  Offset);
LZSBOOL  IpIP_CAL (tPlcOffset  pHandle);
LZSBOOL  IpIP_CALUcodeFBFromNcc (
    tPlchInst          hChildInst_p
    );

LZSBOOL  IpIP_CALFirmFBFromNcc (
    tPlchInst hChildInst_p,
    LZSWORD wExtension_p
    );


LZSBOOL  IpIP_OP_CAL                 (void);
LZSBOOL  IpIP_OP_CALC                (void);
LZSBOOL  IpIP_OP_CALCN               (void);


LZSBOOL  IpIP_OP_RET                 (void);
LZSBOOL  IpIP_OP_RETC                (void);
LZSBOOL  IpIP_OP_RETCN               (void);



/*--------------------------------------------------------------------------- */
/*access to variables */
/*--------------------------------------------------------------------------- */

void IpIP_OP_LD_NEAR_BIT         (void);
void IpIP_OP_LD_NEAR_1           (void);
void IpIP_OP_LD_NEAR_2           (void);
void IpIP_OP_LD_NEAR_4           (void);
void IpIP_OP_LD_NEAR_ANY         (void);
void IpIP_OP_LD_FAR_BIT          (void);
void IpIP_OP_LD_FAR_1            (void);
void IpIP_OP_LD_FAR_2            (void);
void IpIP_OP_LD_FAR_4            (void);
void IpIP_OP_LD_FAR_ANY          (void);
void IpIP_OP_LD_BYREF_BIT        (void);
void IpIP_OP_LD_BYREF_1          (void);
void IpIP_OP_LD_BYREF_2          (void);
void IpIP_OP_LD_BYREF_4          (void);
void IpIP_OP_LD_BYREF_ANY        (void);
void IpIP_OP_LD_IND_BIT          (void);
void IpIP_OP_LD_IND_1            (void);
void IpIP_OP_LD_IND_2            (void);
void IpIP_OP_LD_IND_4            (void);
void IpIP_OP_LD_IND_ANY          (void);

void IpIP_OP_LD_CONST_TRUE       (void);
void IpIP_OP_LD_CONST_FALSE      (void);
void IpIP_OP_LD_CONST_1          (void);
void IpIP_OP_LD_CONST_2          (void);
void IpIP_OP_LD_CONST_4          (void);
void IpIP_OP_LD_CONST_ANY        (void);

void IpIP_OP_LDN_NEAR_BIT        (void);
void IpIP_OP_LDN_NEAR_1          (void);
void IpIP_OP_LDN_NEAR_2          (void);
void IpIP_OP_LDN_NEAR_4          (void);
void IpIP_OP_LDN_FAR_BIT         (void);
void IpIP_OP_LDN_FAR_1           (void);
void IpIP_OP_LDN_FAR_2           (void);
void IpIP_OP_LDN_FAR_4           (void);
void IpIP_OP_LDN_BYREF_BIT       (void);
void IpIP_OP_LDN_BYREF_1         (void);
void IpIP_OP_LDN_BYREF_2         (void);
void IpIP_OP_LDN_BYREF_4         (void);
void IpIP_OP_LDN_IND_BIT         (void);
void IpIP_OP_LDN_IND_1           (void);
void IpIP_OP_LDN_IND_2           (void);
void IpIP_OP_LDN_IND_4           (void);

void IpIP_OP_ST_NEAR_BIT         (void);
void IpIP_OP_ST_NEAR_1           (void);
void IpIP_OP_ST_NEAR_2           (void);
void IpIP_OP_ST_NEAR_4           (void);
void IpIP_OP_ST_NEAR_ANY         (void);
void IpIP_OP_ST_FAR_BIT          (void);
void IpIP_OP_ST_FAR_1            (void);
void IpIP_OP_ST_FAR_2            (void);
void IpIP_OP_ST_FAR_4            (void);
void IpIP_OP_ST_FAR_ANY          (void);
void IpIP_OP_ST_BYREF_BIT        (void);
void IpIP_OP_ST_BYREF_1          (void);
void IpIP_OP_ST_BYREF_2          (void);
void IpIP_OP_ST_BYREF_4          (void);
void IpIP_OP_ST_BYREF_ANY        (void);
void IpIP_OP_ST_IND_BIT          (void);
void IpIP_OP_ST_IND_1            (void);
void IpIP_OP_ST_IND_2            (void);
void IpIP_OP_ST_IND_4            (void);
void IpIP_OP_ST_IND_ANY          (void);

void IpIP_OP_STN_NEAR_BIT        (void);
void IpIP_OP_STN_NEAR_1          (void);
void IpIP_OP_STN_NEAR_2          (void);
void IpIP_OP_STN_NEAR_4          (void);
void IpIP_OP_STN_FAR_BIT         (void);
void IpIP_OP_STN_FAR_1           (void);
void IpIP_OP_STN_FAR_2           (void);
void IpIP_OP_STN_FAR_4           (void);
void IpIP_OP_STN_BYREF_BIT       (void);
void IpIP_OP_STN_BYREF_1         (void);
void IpIP_OP_STN_BYREF_2         (void);
void IpIP_OP_STN_BYREF_4         (void);
void IpIP_OP_STN_IND_BIT         (void);
void IpIP_OP_STN_IND_1           (void);
void IpIP_OP_STN_IND_2           (void);
void IpIP_OP_STN_IND_4           (void);


void IpIP_OP_S_NEAR_BIT          (void);
void IpIP_OP_S_FAR_BIT           (void);
void IpIP_OP_S_BYREF_BIT         (void);
void IpIP_OP_S_IND_BIT           (void);
void IpIP_OP_R_NEAR_BIT          (void);
void IpIP_OP_R_FAR_BIT           (void);
void IpIP_OP_R_BYREF_BIT         (void);
void IpIP_OP_R_IND_BIT           (void);

void IpIP_OP_CREATE_REFERENCE    (void);

void IpIP_OP_CREATE_REFERENCE_FAR(void);

void IpIP_OP_LD_REFERENCE        (void);
void IpIP_OP_ST_REFERENCE        (void);
void IpIP_OP_ADD_OFFSET          (void);


void IpIP_OP_LDS_NEAR_BIT        (void);
void IpIP_OP_LDS_NEAR_1          (void);
void IpIP_OP_LDS_NEAR_2          (void);
void IpIP_OP_LDS_NEAR_4          (void);
void IpIP_OP_LDS_NEAR_ANY        (void);
void IpIP_OP_LDS_FAR_BIT         (void);
void IpIP_OP_LDS_FAR_1           (void);
void IpIP_OP_LDS_FAR_2           (void);
void IpIP_OP_LDS_FAR_4           (void);
void IpIP_OP_LDS_FAR_ANY         (void);
void IpIP_OP_LDS_BYREF_BIT       (void);
void IpIP_OP_LDS_BYREF_1         (void);
void IpIP_OP_LDS_BYREF_2         (void);
void IpIP_OP_LDS_BYREF_4         (void);
void IpIP_OP_LDS_BYREF_ANY       (void);
void IpIP_OP_LDS_IND_BIT         (void);
void IpIP_OP_LDS_IND_1           (void);
void IpIP_OP_LDS_IND_2           (void);
void IpIP_OP_LDS_IND_4           (void);
void IpIP_OP_LDS_IND_ANY         (void);

void IpIP_OP_LDS_CONST_TRUE      (void);
void IpIP_OP_LDS_CONST_FALSE     (void);
void IpIP_OP_LDS_CONST_1         (void);
void IpIP_OP_LDS_CONST_2         (void);
void IpIP_OP_LDS_CONST_4         (void);
void IpIP_OP_LDS_CONST_ANY       (void);

void IpIP_OP_LDNS_NEAR_BIT       (void);
void IpIP_OP_LDNS_NEAR_1         (void);
void IpIP_OP_LDNS_NEAR_2         (void);
void IpIP_OP_LDNS_NEAR_4         (void);
void IpIP_OP_LDNS_FAR_BIT        (void);
void IpIP_OP_LDNS_FAR_1          (void);
void IpIP_OP_LDNS_FAR_2          (void);
void IpIP_OP_LDNS_FAR_4          (void);
void IpIP_OP_LDNS_BYREF_BIT      (void);
void IpIP_OP_LDNS_BYREF_1        (void);
void IpIP_OP_LDNS_BYREF_2        (void);
void IpIP_OP_LDNS_BYREF_4        (void);
void IpIP_OP_LDNS_IND_BIT        (void);
void IpIP_OP_LDNS_IND_1          (void);
void IpIP_OP_LDNS_IND_2          (void);
void IpIP_OP_LDNS_IND_4          (void);

void IpIP_OP_PUSH_AE             (void);
void IpIP_OP_POP_AE              (void);
void IpIP_OP_PUSH_REF            (void);
void IpIP_OP_POP_REF             (void);
void IpIP_OP_PUSH_AE_ANY         (void);
void IpIP_OP_POP_AE_ANY          (void);

void IpIP_OP_RESTORE_DATA        (void);



/*--------------------------------------------------------------------------- */
/* operators */
/*--------------------------------------------------------------------------- */

void IpIP_OP_AND_BIT             (void);
void IpIP_OP_AND_1               (void);
void IpIP_OP_AND_2               (void);
void IpIP_OP_AND_4               (void);

void IpIP_OP_OR_BIT              (void);
void IpIP_OP_OR_1                (void);
void IpIP_OP_OR_2                (void);
void IpIP_OP_OR_4                (void);

void IpIP_OP_XOR_BIT             (void);
void IpIP_OP_XOR_1               (void);
void IpIP_OP_XOR_2               (void);
void IpIP_OP_XOR_4               (void);

void IpIP_OP_ADD_1               (void);
void IpIP_OP_ADD_1_SGN           (void);
void IpIP_OP_ADD_2               (void);
void IpIP_OP_ADD_2_SGN           (void);
void IpIP_OP_ADD_4               (void);
void IpIP_OP_ADD_4_SGN           (void);
void IpIP_OP_ADD_FLOAT           (void);

void IpIP_OP_SUB_1               (void);
void IpIP_OP_SUB_1_SGN           (void);
void IpIP_OP_SUB_2               (void);
void IpIP_OP_SUB_2_SGN           (void);
void IpIP_OP_SUB_4               (void);
void IpIP_OP_SUB_4_SGN           (void);
void IpIP_OP_SUB_FLOAT           (void);

void IpIP_OP_MUL_1               (void);
void IpIP_OP_MUL_1_SGN           (void);
void IpIP_OP_MUL_2               (void);
void IpIP_OP_MUL_2_SGN           (void);
void IpIP_OP_MUL_4               (void);
void IpIP_OP_MUL_4_SGN           (void);
void IpIP_OP_MUL_FLOAT           (void);

void IpIP_OP_DIV_1               (void);
void IpIP_OP_DIV_1_SGN           (void);
void IpIP_OP_DIV_2               (void);
void IpIP_OP_DIV_2_SGN           (void);
void IpIP_OP_DIV_4               (void);
void IpIP_OP_DIV_4_SGN           (void);
void IpIP_OP_DIV_FLOAT           (void);
                                  
void IpIP_OP_GT_BIT              (void);
void IpIP_OP_GT_1                (void);
void IpIP_OP_GT_1_SGN            (void);
void IpIP_OP_GT_2                (void);
void IpIP_OP_GT_2_SGN            (void);
void IpIP_OP_GT_4                (void);
void IpIP_OP_GT_4_SGN            (void);
void IpIP_OP_GT_FLOAT            (void);

void IpIP_OP_GE_BIT              (void);
void IpIP_OP_GE_1                (void);
void IpIP_OP_GE_1_SGN            (void);
void IpIP_OP_GE_2                (void);
void IpIP_OP_GE_2_SGN            (void);
void IpIP_OP_GE_4                (void);
void IpIP_OP_GE_4_SGN            (void);
void IpIP_OP_GE_FLOAT            (void);

void IpIP_OP_LE_BIT              (void);
void IpIP_OP_LE_1                (void);
void IpIP_OP_LE_1_SGN            (void);
void IpIP_OP_LE_2                (void);
void IpIP_OP_LE_2_SGN            (void);
void IpIP_OP_LE_4                (void);
void IpIP_OP_LE_4_SGN            (void);
void IpIP_OP_LE_FLOAT            (void);

void IpIP_OP_LT_BIT              (void);
void IpIP_OP_LT_1                (void);
void IpIP_OP_LT_1_SGN            (void);
void IpIP_OP_LT_2                (void);
void IpIP_OP_LT_2_SGN            (void);
void IpIP_OP_LT_4                (void);
void IpIP_OP_LT_4_SGN            (void);
void IpIP_OP_LT_FLOAT            (void);

void IpIP_OP_EQ_BIT              (void);
void IpIP_OP_EQ_1                (void);
void IpIP_OP_EQ_2                (void);
void IpIP_OP_EQ_4                (void);

void IpIP_OP_NE_BIT              (void);
void IpIP_OP_NE_1                (void);
void IpIP_OP_NE_2                (void);
void IpIP_OP_NE_4                (void);



/*--------------------------------------------------------------------------- */
/* typecast / handling of arrays */
/*--------------------------------------------------------------------------- */

void IpIP_OP_TYPECAST            (void);

void IpIP_OP_SELCT_ARRAY_IND     (void);

void IpIP_OP_CREATE_BITREF_NEAR  (void);
void IpIP_OP_CREATE_BITREF_FAR   (void);
void IpIP_OP_CREATE_BITREF_BYREF (void);
void IpIP_OP_CREATE_BITREF_IND   (void);


/*--------------------------------------------------------------------------- */
/* extensions/control commands */
/*--------------------------------------------------------------------------- */

void IpIP_OP_EXT1                (void);
void IpIP_OP_EXT2                (void);

LZSBYTE  IpIP_OP_BREAK               (void);

/****************************************************************************
*                                                                           *
*           I N T E R P R E T E R - E X T E N S I O N S                     *
*                                                                           *
****************************************************************************/

/*--------------------------------------------------------------------------- */
/* extensions negation */
/*--------------------------------------------------------------------------- */

void IpIP_EX_NOT_BIT             (void);
void IpIP_EX_NOT_1               (void);
void IpIP_EX_NOT_2               (void);
void IpIP_EX_NOT_4               (void);



/*--------------------------------------------------------------------------- */
/* extensions shift/rotate */
/*--------------------------------------------------------------------------- */

void IpIP_EX_SHL_1               (void);
void IpIP_EX_SHL_2               (void);
void IpIP_EX_SHL_4               (void);
void IpIP_EX_SHR_1               (void);
void IpIP_EX_SHR_2               (void);
void IpIP_EX_SHR_4               (void);

void IpIP_EX_ROL_1               (void);
void IpIP_EX_ROL_2               (void);
void IpIP_EX_ROL_4               (void);
void IpIP_EX_ROR_1               (void);
void IpIP_EX_ROR_2               (void);
void IpIP_EX_ROR_4               (void);

void IpIP_EX_ABS_1_SGN        (void);
void IpIP_EX_ABS_2_SGN        (void);
void IpIP_EX_ABS_4_SGN        (void);

void IpIP_EX_MIN_1(void);                
void IpIP_EX_MIN_1_SGN(void);            
void IpIP_EX_MIN_2(void);                
void IpIP_EX_MIN_2_SGN(void);            
void IpIP_EX_MIN_4(void);                
void IpIP_EX_MIN_4_SGN(void);            

        /*MAX*/
void IpIP_EX_MAX_1(void);                
void IpIP_EX_MAX_1_SGN(void);            
void IpIP_EX_MAX_2(void);                
void IpIP_EX_MAX_2_SGN(void);            
void IpIP_EX_MAX_4(void);                
void IpIP_EX_MAX_4_SGN(void);            

        /*MOD*/
void IpIP_EX_MOD_1(void);                
void IpIP_EX_MOD_1_SGN(void);            
void IpIP_EX_MOD_2(void);                
void IpIP_EX_MOD_2_SGN(void);            
void IpIP_EX_MOD_4(void);                
void IpIP_EX_MOD_4_SGN(void);

        /* NEG */
void IpIP_EX_NEG_BIT        (void);
void IpIP_EX_NEG_1        (void);
void IpIP_EX_NEG_2        (void);
void IpIP_EX_NEG_4        (void);
    

/*--------------------------------------------------------------------------- */
/* extensions 8-byte datatypes                                                  */
/*--------------------------------------------------------------------------- */

#ifdef _IP_8BYTEDATA_

        /* LD */
void IpIP_EX_LD_NEAR_8    (void);
void IpIP_EX_LD_FAR_8    (void);
void IpIP_EX_LD_BYREF_8    (void);
void IpIP_EX_LD_IND_8    (void);
void IpIP_EX_LD_CONST_8    (void);
        
        /* LDN */
void IpIP_EX_LDN_NEAR_8    (void);
void IpIP_EX_LDN_FAR_8    (void);
void IpIP_EX_LDN_BYREF_8    (void);
void IpIP_EX_LDN_IND_8    (void);

        /* LDS */
void IpIP_EX_LDS_NEAR_8    (void);
void IpIP_EX_LDS_FAR_8    (void);
void IpIP_EX_LDS_BYREF_8    (void);
void IpIP_EX_LDS_IND_8    (void);
void IpIP_EX_LDS_CONST_8    (void);

        /* LDNS */
void IpIP_EX_LDNS_NEAR_8        (void);
void IpIP_EX_LDNS_FAR_8        (void);
void IpIP_EX_LDNS_BYREF_8    (void);
void IpIP_EX_LDNS_IND_8        (void);

        /* ST */
void IpIP_EX_ST_NEAR_8    (void);
void IpIP_EX_ST_FAR_8    (void);
void IpIP_EX_ST_BYREF_8    (void);
void IpIP_EX_ST_IND_8    (void);

        /* STN */
void IpIP_EX_STN_NEAR_8    (void);
void IpIP_EX_STN_FAR_8    (void);
void IpIP_EX_STN_BYREF_8    (void);
void IpIP_EX_STN_IND_8    (void);

/*  PUSH / POP */
void IpIP_EX_PUSH_AE_8        (void);            
void IpIP_EX_POP_AE_8        (void);            

/*  AND / OR / XOR */
void IpIP_EX_AND_8            (void);                
void IpIP_EX_OR_8            (void);            
void IpIP_EX_XOR_8            (void);            

/* ADD / SUB / MUL / DIV */
void IpIP_EX_ADD_8            (void);                        
void IpIP_EX_ADD_8_SGN        (void);        
void IpIP_EX_SUB_8            (void);            
void IpIP_EX_SUB_8_SGN        (void);        
void IpIP_EX_MUL_8            (void);            
void IpIP_EX_MUL_8_SGN        (void);    
void IpIP_EX_DIV_8            (void);            
void IpIP_EX_DIV_8_SGN        (void);        

/* GT / GE / LE / LT / EQ / NE*/
void IpIP_EX_GT_8            (void);            
void IpIP_EX_GT_8_SGN        (void);    
void IpIP_EX_GE_8            (void);            
void IpIP_EX_GE_8_SGN        (void);        
void IpIP_EX_LE_8            (void);            
void IpIP_EX_LE_8_SGN        (void);        
void IpIP_EX_LT_8            (void);            
void IpIP_EX_LT_8_SGN        (void);        
void IpIP_EX_EQ_8            (void);            
void IpIP_EX_NE_8            (void);        

/* NOT / NEG */
void IpIP_EX_NOT_8            (void);            
void IpIP_EX_NEG_8            (void);

/* SHIFT / ROTATE */
void IpIP_EX_SHL_8    (void);            
void IpIP_EX_SHR_8    (void);            
void IpIP_EX_ROL_8    (void);            
void IpIP_EX_ROR_8    (void);        

/* ABS */
void IpIP_EX_ABS_8            (void);                        
void IpIP_EX_ABS_8_SGN        (void);        

/* MOD */
void IpIP_EX_MOD_8            (void);            
void IpIP_EX_MOD_8_SGN        (void);    

/* EXPT */
void IpIP_EX_EXPT_8        (void);        
void IpIP_EX_EXPT_8_SGN    (void);        

/* MOVE */
void IpIP_EX_MOVE_8        (void);

/* MIN / MAX */
void IpIP_EX_MIN_8            (void);            
void IpIP_EX_MIN_8_SGN        (void);        
void IpIP_EX_MAX_8            (void);            
void IpIP_EX_MAX_8_SGN        (void);        

/* LIMIT */
void IpIP_EX_LIMIT_8        (void);            
void IpIP_EX_LIMIT_8_SGN   (void);        

/* SEL */ 
void IpIP_EX_SEL_8            (void);            
void IpIP_EX_SEL_8_SGN        (void);    

/* NEG */
void IpIP_EX_NEG_8            (void);            

/* DT */
#ifdef _IP_ANYDATE_
void IpIP_EX_SUB_DATE_DATE    (void);
void IpIP_EX_SUB_TOD_TOD    (void);
void IpIP_EX_SUB_DT_DT        (void);

void IpIPAddTodTime(LZSLONG nTime);

#define IpIP_EX_ADD_TOD_TIME()		IpIPAddTodTime(   *((LZSLONG *)&pCurrentProgramData_g->TaskData.m_CurrAEs.d) )
#define IpIP_EX_SUB_TOD_TIME()		IpIPAddTodTime( - *((LZSLONG *)&pCurrentProgramData_g->TaskData.m_CurrAEs.d) )

void IpIPAddDtTime(LZSLONG nTime);

#define IpIP_EX_ADD_DT_TIME()		IpIPAddDtTime(   *((LZSLONG *)&pCurrentProgramData_g->TaskData.m_CurrAEs.d) )
#define IpIP_EX_SUB_DT_TIME()		IpIPAddDtTime( - *((LZSLONG *)&pCurrentProgramData_g->TaskData.m_CurrAEs.d) )

#endif

#ifdef _IP_REAL48_
    void IpIP_EX2_LD_NEAR_6(void);
    void IpIP_EX2_LD_FAR_6(void);
    void IpIP_EX2_LD_BYREF_6(void);                
    void IpIP_EX2_LD_IND_6(void);                
    void IpIP_EX2_LD_CONST_6(void);                

    void IpIP_EX2_LDS_NEAR_6(void);                
    void IpIP_EX2_LDS_FAR_6(void);                
    void IpIP_EX2_LDS_BYREF_6(void);            
    void IpIP_EX2_LDS_IND_6(void);                    
    void IpIP_EX2_LDS_CONST_6(void);            


    void IpIP_EX2_ST_NEAR_6(void);                    
    void IpIP_EX2_ST_FAR_6(void);                    
    void IpIP_EX2_ST_BYREF_6(void);                    
    void IpIP_EX2_ST_IND_6(void);                    


    void IpIP_EX2_PUSH_AE_6(void);                    
    void IpIP_EX2_POP_AE_6(void);                    
#endif /*_IP_REAL48_*/

#ifdef _IP_INT24_
    void IpIP_EX2_LD_NEAR_3(void);                
    void IpIP_EX2_LD_FAR_3(void);                
    void IpIP_EX2_LD_BYREF_3(void);                
    void IpIP_EX2_LD_IND_3(void);                
    void IpIP_EX2_LD_CONST_3(void);                

    void IpIP_EX2_LDN_NEAR_3(void);                
    void IpIP_EX2_LDN_FAR_3(void);                
    void IpIP_EX2_LDN_BYREF_3(void);                
    void IpIP_EX2_LDN_IND_3(void);                

    void IpIP_EX2_LDS_NEAR_3(void);                
    void IpIP_EX2_LDS_FAR_3(void);                
    void IpIP_EX2_LDS_BYREF_3(void);                
    void IpIP_EX2_LDS_IND_3(void);                
    void IpIP_EX2_LDS_CONST_3(void);                

    void IpIP_EX2_LDNS_NEAR_3(void);                
    void IpIP_EX2_LDNS_FAR_3(void);                
    void IpIP_EX2_LDNS_BYREF_3(void);            
    void IpIP_EX2_LDNS_IND_3(void);                

    void IpIP_EX2_ST_NEAR_3(void);                
    void IpIP_EX2_ST_FAR_3(void);                
    void IpIP_EX2_ST_BYREF_3(void);                
    void IpIP_EX2_ST_IND_3(void);                

    void IpIP_EX2_STN_NEAR_3(void);                
    void IpIP_EX2_STN_FAR_3(void);                
    void IpIP_EX2_STN_BYREF_3(void);                
    void IpIP_EX2_STN_IND_3(void);                

    void IpIP_EX2_PUSH_AE_3(void);                
    void IpIP_EX2_POP_AE_3(void);                
#endif /* _IP_INT24_*/



#ifdef    _IP_FLOAT_ 
void IpIP_EX_ADD_DOUBLE        (void);        
void IpIP_EX_SUB_DOUBLE        (void);    
void IpIP_EX_MUL_DOUBLE        (void);        
void IpIP_EX_DIV_DOUBLE        (void);        
void IpIP_EX_GT_DOUBLE        (void);        
void IpIP_EX_GE_DOUBLE        (void);        
void IpIP_EX_LE_DOUBLE        (void);        
void IpIP_EX_LT_DOUBLE        (void);        
void IpIP_EX_ABS_DOUBLE        (void);        
void IpIP_EX_MOD_DOUBLE        (void);        
void IpIP_EX_EXPT_DOUBLE        (void);        
void IpIP_EX_MIN_DOUBLE        (void);    
void IpIP_EX_MAX_DOUBLE        (void);        
void IpIP_EX_LIMIT_DOUBLE    (void);    
void IpIP_EX_SEL_DOUBLE        (void);        
void IpIP_EX_NEG_DOUBLE        (void);        
void IpIP_EX_EXP_DOUBLE        (void);    
void IpIP_EX_SQRT_DOUBLE        (void);        
void IpIP_EX_LN_DOUBLE        (void);        
void IpIP_EX_LOG_DOUBLE        (void);        
void IpIP_EX_SIN_DOUBLE        (void);    
void IpIP_EX_COS_DOUBLE        (void);        
void IpIP_EX_TAN_DOUBLE        (void);        
void IpIP_EX_ASIN_DOUBLE        (void);    
void IpIP_EX_ACOS_DOUBLE        (void);        
void IpIP_EX_ATAN_DOUBLE        (void);        
void IpIP_EX_NEG_DOUBLE        (void);        
void IpIP_EX_EXPT_DOUBLE_1_SGN(void);
void IpIP_EX_EXPT_DOUBLE_1_SGN (void);
void IpIP_EX_EXPT_DOUBLE_1     (void);
void IpIP_EX_EXPT_DOUBLE_2_SGN (void);
void IpIP_EX_EXPT_DOUBLE_2     (void);
void IpIP_EX_EXPT_DOUBLE_3_SGN (void);
void IpIP_EX_EXPT_DOUBLE_3     (void);
void IpIP_EX_EXPT_DOUBLE_4_SGN (void);
void IpIP_EX_EXPT_DOUBLE_4     (void);
void IpIP_EX_EXPT_DOUBLE_8_SGN (void);
void IpIP_EX_EXPT_DOUBLE_8     (void);
void IpIP_EX_EXPT_DOUBLE_FLOAT (void);
void IpIP_EX_EXPT_DOUBLE_REAL48(void);
void IpIP_EX_EXPT_DOUBLE_DOUBLE(void);
#endif /* _IP_FLOAT_    */
#endif /* _IP_8BYTEDATA_*/

#ifdef _IP_POINTER_
    void IpIP_EX2_LDA_NEAR(void);
    void IpIP_EX2_LDA_BYREF(void);
    void IpIP_EX2_LDA_FAR(void);
    
    void IpIP_EX2_LDAS_NEAR(void);    
    void IpIP_EX2_LDAS_BYREF(void);
    void IpIP_EX2_LDAS_FAR(void);
#endif

#ifdef _IP_WSTRING_
    void IpIP_EX2_ST_NEAR_WSTRING(void);
    void IpIP_EX2_ST_FAR_WSTRING(void);    
    void IpIP_EX2_ST_BYREF_WSTRING(void);
    void IpIP_EX2_ST_IND_WSTRING(void);
    void IpIP_EX2_ST_DIR_BYREF_WSTRING(void);    
#endif

void IpIP_EX2_ST_NEAR_ARRAY(void);
void IpIP_EX2_ST_FAR_ARRAY(void);    
void IpIP_EX2_ST_BYREF_ARRAY(void);
void IpIP_EX2_ST_IND_ARRAY(void);
void IpIP_EX2_ST_DIR_BYREF_ARRAY(void);    

#ifdef    _IP_FLOAT_ 
/* Real functions */
void IpIP_EX_ABS_FLOAT            (void);
void IpIP_EX_MOD_FLOAT               (void);
void IpIP_EX_MIN_FLOAT               (void);
void IpIP_EX_MAX_FLOAT               (void);
void IpIP_EX_LIMIT_FLOAT               (void);
void IpIP_EX_EXP               (void);
void IpIP_EX_SQRT               (void);
void IpIP_EX_LN               (void);
void IpIP_EX_LOG               (void);
void IpIP_EX_SIN               (void);
void IpIP_EX_COS               (void);
void IpIP_EX_TAN               (void);
void IpIP_EX_ASIN               (void);
void IpIP_EX_ACOS               (void);
void IpIP_EX_ATAN               (void);
void IpIP_OP_TRUNC (void);

        /* NEG FLOAT */
void IpIP_EX_NEG_FLOAT    (void);

/* BEGINN PATCH*/
/* EXPT Functions B.S. 09.06.00*/
void IpIP_EX_EXPT_1(void);
void IpIP_EX_EXPT_1_SGN(void);
void IpIP_EX_EXPT_2(void);
void IpIP_EX_EXPT_2_SGN(void);
void IpIP_EX_EXPT_4(void);
void IpIP_EX_EXPT_4_SGN(void);
void IpIP_EX_EXPT_FLOAT(void);
/* EXPT Functions B.S. 09.06.00*/
/* END PATCH*/
#endif

#ifdef _IP_STRING_
/* String functions */
void IpIP_OP_EQ_ANY               (void);
void IpIP_OP_NE_ANY               (void);
void IpIP_OP_GT_ANY               (void);
void IpIP_OP_GE_ANY               (void);
void IpIP_OP_LT_ANY               (void);
void IpIP_OP_LE_ANY               (void);

void IpIP_EX_LEN               (void);
void IpIP_EX_LEFT               (void);
void IpIP_EX_RIGHT               (void);
void IpIP_EX_MID               (void);
void IpIP_EX_CONCAT               (void);
void IpIP_EX_INSERT               (void);
void IpIP_EX_DELETE               (void);
void IpIP_EX_REPLACE               (void);
void IpIP_EX_FIND               (void);
void IpIP_EX_MIN_ANY            (void);
void IpIP_EX_MAX_ANY            (void);

void IpIP_OP_ST_NEAR_STRING (void);
void IpIP_OP_ST_FAR_STRING (void);
void IpIP_OP_ST_BYREF_STRING (void);
void IpIP_OP_ST_IND_STRING (void);


void IpIP_EX_EXCHANGE_IO_WRITE (void);
void IpIP_EX_EXCHANGE_IO_READ (void);

#endif

#ifdef _LZS_DIRECT_BYREF_
void IpIP_EX_CREATE_BITREF_DIR_BYREF(void); 
void IpIP_EX_ST_DIR_BYREF_STRING(void); 
void IpIP_EX_LD_DIR_BYREF_BIT(void); 
void IpIP_EX_LD_DIR_BYREF_1(void); 
void IpIP_EX_LD_DIR_BYREF_2(void); 
void IpIP_EX_LD_DIR_BYREF_4(void); 
void IpIP_EX_LD_DIR_BYREF_8(void); 
void IpIP_EX_LD_DIR_BYREF_ANY(void); 
void IpIP_EX_LDN_DIR_BYREF_BIT(void); 
void IpIP_EX_LDN_DIR_BYREF_1(void); 
void IpIP_EX_LDN_DIR_BYREF_2(void); 
void IpIP_EX_LDN_DIR_BYREF_4(void); 
void IpIP_EX_LDN_DIR_BYREF_8(void); 
void IpIP_EX_ST_DIR_BYREF_BIT(void); 
void IpIP_EX_ST_DIR_BYREF_1(void); 
void IpIP_EX_ST_DIR_BYREF_2(void); 
void IpIP_EX_ST_DIR_BYREF_4(void); 
void IpIP_EX_ST_DIR_BYREF_8(void); 
void IpIP_EX_ST_DIR_BYREF_ANY(void); 
void IpIP_EX_STN_DIR_BYREF_BIT(void); 
void IpIP_EX_STN_DIR_BYREF_1(void); 
void IpIP_EX_STN_DIR_BYREF_2(void); 
void IpIP_EX_STN_DIR_BYREF_4(void); 
void IpIP_EX_STN_DIR_BYREF_8(void); 
void IpIP_EX_S_DIR_BYREF_BIT(void); 
void IpIP_EX_R_DIR_BYREF_BIT(void); 
void IpIP_EX_LDS_DIR_BYREF_BIT(void); 
void IpIP_EX_LDS_DIR_BYREF_1(void); 
void IpIP_EX_LDS_DIR_BYREF_2(void); 
void IpIP_EX_LDS_DIR_BYREF_4(void); 
void IpIP_EX_LDS_DIR_BYREF_8(void); 
void IpIP_EX_LDS_DIR_BYREF_ANY(void); 
void IpIP_EX_LDNS_DIR_BYREF_BIT(void); 
void IpIP_EX_LDNS_DIR_BYREF_1(void); 
void IpIP_EX_LDNS_DIR_BYREF_2(void); 
void IpIP_EX_LDNS_DIR_BYREF_4(void); 
void IpIP_EX_LDNS_DIR_BYREF_8(void); 
void IpIP_EX_CREATE_DIR_REFERENCE(void); 
void IpIP_EX_CREATE_DIR_REFERENCE_FAR(void); 
void IpIP_EX_LD_DIR_REFERENCE(void); 
void IpIP_EX_ST_DIR_REFERENCE(void); 
#endif 

/****************************************************************************
*                                                                           *
*           INTERNAL FUNCTIONS                                              *
*                                                                           *
****************************************************************************/

LZSBOOL  IpExecCommand (void);

#ifdef _LZS_GENERATE_IP_DEBUG_INFO_
void  IpGenerateDebugInfo (LZSBYTE bCurrIpCmd_p, LZSBYTE bState_p);
#endif


#ifdef _IP_PFLOW_ 
#ifdef _LZS_PRAGMAMESSAGE_
#pragma message("_IP_PFLOW_")
#endif
/* B.S. 19.05.98 */
LZSBOOL  IpPflowRegisterSection (tPlcPgmNr wPflowPgmNr_p,tPlchInst hPflowInst_p, tPlcOffset StartOffs_p,
                              tPlcOffset EndOffs_p, LZSWORD wDataBuffSize_p);

void  IpPflowStartSession (void);
void  IpPflowWorkSession  (LZSBYTE bStep_p);
void  IpPflowStopSession  (void);
#endif /* #ifdef _IP_PFLOW_ */




#endif /* _IP_CMDS_H_ */
