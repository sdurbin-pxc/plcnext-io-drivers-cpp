/*****************************************************************************
**                                                                          **
**              PHOENIX CONTACT GmbH & Co., 32819 Blomberg, Germany         **
**                  Copyright Phoenix Contact 2016                          **
**                                                                          **
******************************************************************************
**                                                                          **
** Project      : -- (global)                                               **
** Sub-Project  : --                                                        **
**                                                                          **
*****************************************************************************/

/*
** File         : stdtypes.h
** Component(s) : -
** Device(s)    : -
** Terminology  : -
**              :
** Definition   :
** Author       :
**         $Date: $
**              :
**     $Revision: $
** Last-PVCS-Rev: $
**
** Status       : -
**              :
** Description  : unique data type definitions
**              : New Version, map old data types to arp types
**              : for use old DDI sources in arp fw.
**              :
******************************************************************************
** Change Notes :
**
** Date      Version  Author        Description
** ---------------------------------------------------------------------------
**
*/

#ifndef INCL_STDTYPES
#define INCL_STDTYPES

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

//#ifndef VOID
//#define VOID          void
//#endif
//#ifndef INT8
//#define INT8         int8_t       // signed char
//#endif
//#ifndef INT16
//#define INT16        int16_t      // signed short
//#endif
//#ifndef INT32
//#define INT32        int32_t      // signed long
//#endif
//#ifndef USIGN8
//#define USIGN8       uint8_t      // unsigned char
//#endif
//#ifndef USIGN16
//#define USIGN16      uint16_t     // unsigned short
//#endif
//#ifndef USIGN32
//#define USIGN32      uint32_t     // unsigned long
//#endif
//#ifndef PHO_FLOAT
//#define PHO_FLOAT    float        // float
//#endif
//#ifndef PHO_DOUBLE
//#define PHO_DOUBLE   double       // double
//#endif
//#ifndef FLOAT
//#define FLOAT        float        // float
//#endif
//#ifndef DOUBLE
//#define DOUBLE       double       // double
//#endif
//#ifndef CHAR
//#define CHAR         signed char  // char
//#endif
//#ifndef PHO_BOOL
//#define PHO_BOOL     bool         // bool
//#endif
//#ifndef MAXENUM
//#define MAXENUM      32767
//#endif


/* System specific Constants */
// #define  IBDDIRET
// #define  IBDDIHND
// #define  IBDDIFUNC
// #define  IBDRVHND
//#define  IBPTR
// #define  ERR_BASE       0

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* INCL_STDTYPES */

