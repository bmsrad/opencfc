/*========================================================== */
/*    infoteam Software GmbH , Am Bauhof 4 , D-91088 Bubenreuth */
/*             (C) 1996-1998 */
/*    MR: Do, 09 Apr 98   */
/*    DESCRIPTION: */
/*        TRACE definition for the smartplc  */
/*        if a module (c-file shall support TRACE -> */
/*        -> #define SMARTPLC_TRACE in this module */
/*        the define is undefine after each module */
/* */
/*        this Header file is only for use in smartplc-projects */
/*         */
/*============================================================ */


/*
    $Log:   O:/infoteam/pvcs/archives/infoteam/v400/Smart.PLC/OEM/inc/OEM/trace.h-arc  $
 * 
 *    Rev 1.0   24 Jun 2004 14:56:44   Gumbmann
 * Initial revision.
 * 
*/

#ifndef __SMARTPLC_TRACE_H__
#define __SMARTPLC_TRACE_H__




/*--------------------------------------------------------------------------- */
/*  Definition von TRACE */
/*--------------------------------------------------------------------------- */

#ifdef SMARTPLC_TRACE

	#define LZSTRACE6(STR,A1,A2,A3,A4,A5,A6) logMsg(STR,A1,A2,A3,A4,A5,A6) 
    #define LZSTRACE0(STR) logMsg(STR,0,0,0,0,0,0)
    #define LZSTRACE1(STR,A1) logMsg(STR,A1,0,0,0,0,0)
    #define LZSTRACE2(STR,A1,A2) logMsg(STR,A1,A2,0,0,0,0)
    #define LZSTRACE3(STR,A1,A2,A3) logMsg(STR,A1,A2,A3,0,0,0)
    #define LZSTRACE4(STR,A1,A2,A3,A4) logMsg(STR,A1,A2,A3,A4,0,0)
    #define LZSTRACE5(STR,A1,A2,A3,A4,A5) logMsg(STR,A1,A2,A3,A4,A5,0)
       

  
    
    
    #ifndef LZSTRACE
        /* when we want to trace anything, we have to use */
        /* the function trace() */
        /* look there to insert the code for your machine */
         void trace(char *fmt, ...);
        #define LZSTRACE trace
    #endif

   #ifndef LZSTRACE0
      #define LZSTRACE0(p0)              LZSTRACE(p0)
   #endif

   #ifndef LZSTRACE1
      #define LZSTRACE1(p0, p1)          LZSTRACE(p0, p1)
   #endif

   #ifndef LZSTRACE2
      #define LZSTRACE2(p0, p1, p2)      LZSTRACE(p0, p1, p2)
   #endif

   #ifndef LZSTRACE3
      #define LZSTRACE3(p0, p1, p2, p3)  LZSTRACE(p0, p1, p2, p3)
   #endif

   #ifndef LZSTRACE4
      #define LZSTRACE4(p0, p1, p2, p3, p4)  LZSTRACE(p0, p1, p2, p3, p4)
   #endif
   
   #ifndef LZSTRACE5
      #define LZSTRACE5(p0, p1, p2, p3, p4, p5)  LZSTRACE(p0, p1, p2, p3, p4, p5)
   #endif
   

#else

    #ifndef LZSTRACE
        #define LZSTRACE(p)
    #endif    
    
   #ifndef LZSTRACE0
      #define LZSTRACE0(p0)
   #endif

   #ifndef LZSTRACE1
      #define LZSTRACE1(p0, p1)
   #endif

   #ifndef LZSTRACE2
      #define LZSTRACE2(p0, p1, p2)
   #endif

   #ifndef LZSTRACE3
      #define LZSTRACE3(p0, p1, p2, p3)
   #endif

   #ifndef LZSTRACE4
      #define LZSTRACE4(p0, p1, p2, p3, p4)
   #endif
   
   #ifndef LZSTRACE5
      #define LZSTRACE5(p0, p1, p2, p3, p4, p5)
   #endif
   

#endif

#endif

