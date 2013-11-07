/******************************************************************************
 *  (c) 2005 infoteam Software GmbH, D-91088 Bubenreuth, Tel. +49-9131-7800-0
 *  
 *  DESCRIPTION: definitions shared between runtime system and compiler backend
 *  
 *****************************************************************************/

#ifndef _LZSCBE_H_
#define _LZSCBE_H_

#define CBETYPESIZE_STRING_LENGTH_MAX   256
#define CBETYPESIZE_WSTRING_LENGTH_MAX  128        /* given in number of characters, not bytes */

typedef enum 
{
    kCbeTypeUndef = 0 ,
    kCbeTypeBool = 1,
    kCbeTypeByte = 2 ,
    kCbeTypeWord   = 3 ,
    kCbeTypeDword   = 4 ,
    kCbeTypeUsint  = 5 ,
    kCbeTypeUint  = 6 ,
    kCbeTypeUdint  = 7 ,
    kCbeTypeSint = 8 ,
    kCbeTypeInt  = 9 ,
    kCbeTypeDint = 10 ,
    kCbeTypeReal  = 11 ,
    kCbeTypeTime = 12 ,
    kCbeTypeDate = 13 ,
    kCbeTypeTod = 14 ,
    kCbeTypeDt = 15 ,
    kCbeTypeLword = 16 ,
    kCbeTypeUlint = 17 ,
    kCbeTypeLint = 18 ,
    kCbeTypeLreal = 19 ,
    kCbeTypeString = 20 ,
    kCbeTypeEnum  = 21 ,
    kCbeTypeArray = 22 ,
    kCbeTypeStruct = 23 ,
    kCbeTypeBit    = 24 ,
    kCbeTypeBcdReal = 25,
    kCbeTypeReferenz = 26 ,
    kCbeTypeUser = 27  ,
    kCbeTypeArrayOfArray = 28 ,
    kCbeTypeArrayOfStruct = 29 ,
    kCbeTypeStructOfStruct = 30 ,
    kCbeTypeStructOfArray = 31 ,
    kCbeTypeInitvalues = 32 ,
    kCbeTypeFbInstance = 33 ,
    kCbeTypeInt24  = 34 ,
    kCbeTypeReal48  = 35 ,
    kCbeTypeAddress = 36,
    kCbeTypeWString = 37,
    /* ----------------------------*/
    kCbeTypeCount = 40
} tCbeType;

typedef enum {
    kCbeTypeSizeUndef = 0 ,
    kCbeTypeSizeBit = 1,
    kCbeTypeSizeBool = 1,
    kCbeTypeSizeSint = 1,
    kCbeTypeSizeInt = 2,
    kCbeTypeSizeDint = 4,
    kCbeTypeSizeLint = 8 ,
    kCbeTypeSizeEnum = 2,
    kCbeTypeSizeUsint = 1 ,
    kCbeTypeSizeUint = 2,
    kCbeTypeSizeUdint = 4 ,
    kCbeTypeSizeUlint = 8  ,
    kCbeTypeSizeReal = 4,       /* war früher 0 */
    kCbeTypeSizeLreal = 8,      /* war früher 0 */
    kCbeTypeSizeTime = 4 ,
    kCbeTypeSizeDate = 4,
    kCbeTypeSizeTod = 4,
    kCbeTypeSizeDt  = 8 ,
    kCbeTypeSizeByte = 1 ,
    kCbeTypeSizeWord = 2 ,
    kCbeTypeSizeDword = 4,
    kCbeTypeSizeLword = 8,
    kCbeTypeSizeRferenz = 4,
    kCbeTypeSizeInt24 = 3,
    kCbeTypeSizeReal48 = 6,
    kCbeTypeSizeString  = CBETYPESIZE_STRING_LENGTH_MAX
} tCbeSizeType ;

typedef enum 
{
        kCbeUndefScopedVariable,
        kCbeRelativeVariable,
        kCbeParameterVariable ,
        kCbeParameterRetainVariable ,
        kCbeLocalVariable,
        kCbeGlobalVariable,
        kCbeLocalRetainVariable,
        kCbeGlobalRetainVariable,
        kCbeExternalsVariable,

        kInInputBitVariable,
        kInOutputBitVariable,

        kInInputWordVariable,
        kInOutputWordVariable,

        kInInputBitRetainVariable,
        kInOutputBitRetainVariable,

        kInInputWordRetainVariable,
        kInOutputWordRetainVariable,

        kInMemBitVariable,
        kInMemWordVariable,
        kInMemBitRetainVariable,
        kInMemWordRetainVariable
} tCbeVarScope;

#endif

