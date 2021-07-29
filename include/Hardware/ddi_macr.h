/*****************************************************************************
**                                                                          **
**              PHOENIX CONTACT GmbH & Co., 32819 Blomberg, Germany         **
**                                                                          **
******************************************************************************
**                                                                          **
** Project      : --                                                        **
** Sub-Project  : --                                                        **
**                                                                          **
*****************************************************************************/

/*
** File         : DDI_MACR.H
** Component(s) : -
** Device(s)    : -
** Terminology  : -
**              :
** Definition   :
** Author       :
**         $Date: 2013-01-17 13:04:59 +0100 (Do, 17 Jan 2013) $
**              :
**     $Revision: 222473 $
** Last-PVCS-Rev:   1.5  $
**
** Status       :
**              :
** Description  : Macros for processing commands, messages and
**              : process data.
**              :
******************************************************************************
** Change Notes :
**
** Date      Version  Author        Description
** ---------------------------------------------------------------------------
**
*/


#ifndef INCL_DDI_MACR
#define INCL_DDI_MACR

#ifdef __cplusplus
extern "C" {
#endif

//#include "stdtypes.h"

/*****************************************************************************
****  CONSTANT DEFINITIONS                                                ****
*****************************************************************************/

#ifdef  ETHA_LITTLE_ENDIAN /* If Intel processor */

#define  IBS_HTONL(l) ( (((l) & 0x000000ff) << 24) | \
                        (((l) & 0x0000ff00) << 8)  | \
                        (((l) & 0x00ff0000) >> 8)  | \
                        (((l) & 0xff000000) >> 24) )
#define  IBS_NTOHL(l) IBS_HTON(l)
#define  IBS_HTONS(s) ((uint16_t)(((uint16_t)(s) >> 8) | ((uint16_t)(s) << 8)))
#define  IBS_NTOHS(s) IBS_HTONS(s)

#define  IBS_HIBYTE(w)          (uint8_t)((w) >> 8)
#define  IBS_LOBYTE(w)          (uint8_t)((w) & 0xFF)

#define  IBS_HIWORD(l)          ((uint16_t)((((uint32_t)(l)) >> 16) & 0xFFFF))
#define  IBS_LOWORD(l)          ((uint16_t)(uint32_t)(l))

#define  IBS_MAKELONG(low, high)    ((uint32_t)(((uint16_t)(low)) | \
                                    (((uint32_t)((uint16_t)(high))) << 16)))

/* Macros for creating a command */
#define  IB_SetCmdCode(n, m)            (((uint8_t  *)n)[0] = IBS_HIBYTE(m), \
                                        ((uint8_t  *)n)[1] = IBS_LOBYTE(m))
#define  IB_SetParaCnt(n, m)            (((uint8_t  *)n)[2] = IBS_HIBYTE(m), \
                                        ((uint8_t  *)n)[3] = IBS_LOBYTE(m))
#define  IB_SetParaN(n, m, o)           (((uint8_t  *)n)[((m)<<1)+2] = IBS_HIBYTE(o), \
                                        ((uint8_t  *)n)[((m)<<1)+3] = IBS_LOBYTE(o))
#define  IB_SetParaNHiByte(n, m, o)     (((uint8_t  *)n)[((m)<<1)+2] = (uint8_t)o)
#define  IB_SetParaNLoByte(n, m, o)     (((uint8_t  *)n)[((m)<<1)+3] = (uint8_t)o)
#define  IB_SetBytePtrHiByte(n, m)      ((uint8_t  *)&(n[((m)<<1)+2]))
#define  IB_SetBytePtrLoByte(n, m)      ((uint8_t  *)&(n[((m)<<1)+3]))

/* Macros for reading a message */
#define  IB_GetMsgCode(n)               (((uint8_t  *)n)[1] | \
                                        (((uint8_t  *)n)[0]<<8))
#define  IB_GetParaCnt(n)               (((uint8_t  *)n)[3] | \
                                        (((uint8_t  *)n)[2]<<8))
#define  IB_GetParaN(n,m)               (((uint8_t  *)n)[((m)<<1)+3] | \
                                        (((uint8_t  *)n)[((m)<<1)+2]<<8))
#define  IB_GetParaNHiByte(n,m)         (((uint8_t  *)n)[((m)<<1)+2])
#define  IB_GetParaNLoByte(n,m)         (((uint8_t  *)n)[((m)<<1)+3])
#define  IB_GetBytePtrHiByte(n,m)       (&(n[((m)<<1)+2]))
#define  IB_GetBytePtrLoByte(n,m)       (&(n[((m)<<1)+3]))

/* Macros for general handling of PMS files */
#define  IB_PMS_SetInvokeID(n, o)       (((uint8_t  *)n)[4] = (uint8_t)o)
#define  IB_PMS_SetCR(n, o)             (((uint8_t  *)n)[5] = (uint8_t)o)
#define  IB_PMS_GetInvokeID(n)          (((uint8_t  *)n)[4])
#define  IB_PMS_GetCR(n)                (((uint8_t  *)n)[5])
#define  IB_PMS_GetCnfResult(n)         (((uint8_t  *)n)[6])

/* Macros for reading negative confirmation parameters */
#define  IB_PMS_GetNCnfErrClass(n)      (((uint8_t  *)n)[6])
#define  IB_PMS_GetNCnfErrCode(n)       (((uint8_t  *)n)[7])
#define  IB_PMS_GetNCnfAddCode(n)       ((((uint8_t  *)n)[8]<<8) \
                                        | ((uint8_t  *)n)[9])
#define  IB_PMS_GetNCnfPiState(n)       (((uint8_t  *)n)[10])

/* Get OD service macros */
#define  IB_PMS_GetStatCnfLogStat(n)    (((uint8_t  *)n)[7])
#define  IB_PMS_GetStatCnfPhysStat(n)   (((uint8_t  *)n)[8])
#define  IB_PMS_GetStatCnfLclDetailLen(n)   (((uint8_t  *)n)[9])
#define  IB_PMS_GetStatCnfLclDetailStr(n)   (&(((uint8_t  *)n)[10]))

/* Macros specific to Initiate services */
#define  IB_PMS_GetInitCnfVersion(n)    ((((uint8_t  *)n)[7]<<8) \
                                        | ((uint8_t  *)n)[8])
#define  IB_PMS_GetInitErrSndHigh(n)    (((uint8_t  *)n)[11])
#define  IB_PMS_GetInitErrSndLow(n)     (((uint8_t  *)n)[12])
#define  IB_PMS_GetInitErrRcvHigh(n)    (((uint8_t  *)n)[13])
#define  IB_PMS_GetInitErrRcvLow(n)     (((uint8_t  *)n)[14])
#define  IB_PMS_GetInitErrServPtr(n)    (&(((uint8_t  *)n)[15]))

/* Abort Indication macros */
#define  IB_PMS_GetAbortLclyGen(n)      (((uint8_t  *)n)[6])
#define  IB_PMS_GetAbortID(n)           (((uint8_t  *)n)[7])
#define  IB_PMS_GetAbortReasonCode(n)   (((uint8_t  *)n)[8])
#define  IB_PMS_GetAbortDetail(n)       (((uint8_t  *)n)[9])

/* Reject Indication macros */
#define  IB_PMS_GetRjctDetectHere(n)    (((uint8_t  *)n)[6])
#define  IB_PMS_GetRjctOrgInvokeID(n)   (((uint8_t  *)n)[7])
#define  IB_PMS_GetRjctPDUType(n)       (((uint8_t  *)n)[8])
#define  IB_PMS_GetRjctCode(n)          (((uint8_t  *)n)[9])

#define  IB_PMS_GetGetOVCnfMore(n)      (((uint8_t  *)n)[7])
#define  IB_PMS_GetGetOVCnfLength(n)    (((uint8_t  *)n)[8])
#define  IB_PMS_GetGetOVCnfObjList(n)   (&(((uint8_t  *)n)[9]))

/* Read Variable service macros */
#define  IB_PMS_SetReadReqParaCnt(n)    (((uint8_t  *)n)[2] = 0x00, \
                                        ((uint8_t  *)n)[3] = 0x03)
#define  IB_PMS_SetReadReqIndex(n, o)   (((uint8_t  *)n)[6] = IBS_HIBYTE(m), \
                                        ((uint8_t  *)n)[7] = IBS_LOBYTE(m))
#define  IB_PMS_SetReadReqSubindex(n, o)    (((uint8_t  *)n)[8] = (uint8_t)o)
#define  IB_PMS_GetReadCnfResult(n)     (((uint8_t  *)n)[6])
#define  IB_PMS_GetReadCnfLength(n)     (((uint8_t  *)n)[7])
#define  IB_PMS_GetReadCnfDataPtr(n)    (&(((uint8_t  *)n)[8]))
#define  IB_PMS_GetReadIndIndex(n)      ((((uint8_t  *)n)[6]<<8) \
                                        |((uint8_t  *)n)[7])
#define  IB_PMS_GetReadIndSubindex(n)   (((uint8_t  *)n)[8])

/* Write Variable service macros */
#define  IB_PMS_SetWriteReqIndex(n, o)  (((uint8_t  *)n)[6] = IBS_HIBYTE(m), \
                                        ((uint8_t  *)n)[7] = IBS_LOBYTE(m))
#define  IB_PMS_SetWriteReqSubindex(n, o)   (((uint8_t  *)n)[8] = (uint8_t)o)
#define  IB_PMS_SetWriteReqLength(n, o) (((uint8_t  *)n)[9] = (uint8_t)o)
#define  IB_PMS_GetWriteReqDataPtr(n)   ((uint8_t  *)&(((uint8_t  *)n)[10]))
#define  IB_PMS_GetWriteCnfResult(n)    (((uint8_t  *)n)[6])
#define  IB_PMS_GetWriteIndIndex(n)     ((((uint8_t  *)n)[6]<<8) \
                                        | ((uint8_t  *)n)[7])
#define  IB_PMS_GetWriteIndSubindex(n)  (((uint8_t  *)n)[8])
#define  IB_PMS_GetWriteIndLength(n)    (((uint8_t  *)n)[9])
#define  IB_PMS_GetWriteIndDataPtr(n)   (&(((uint8_t  *)n)[10]))


/* Process data processing macros */
#define  IB_PD_SetDataN(n, m, o)        (((uint8_t  *)n)[(m<<1)] = IBS_HIBYTE(o), \
                                        ((uint8_t  *)n)[(m<<1)+1] = IBS_LOBYTE(o))
#define  IB_PD_SetDataNHiByte(n, m, o)  (((uint8_t  *)n)[(m<<1)] = (uint8_t)o)
#define  IB_PD_SetDataNLoByte(n, m, o)  (((uint8_t  *)n)[(m<<1)+1] = (uint8_t)o)
#define  IB_PD_SetBytePtrHiByte(n, m)   ((uint8_t  *)&(((uint8_t  *)n)[(m<<1)]))
#define  IB_PD_SetBytePtrLoByte(n, m)   ((uint8_t  *)&(((uint8_t  *)n)[(m<<1)+1]))

#define  IB_PD_GetDataN(n, m)           (((uint8_t  *)n)[(m<<1)+1] | \
                                        (((uint8_t  *)n)[(m<<1)]<<8))
#define  IB_PD_GetDataNHiByte(n, m)     (((uint8_t  *)n)[(m<<1)])
#define  IB_PD_GetDataNLoByte(n, m)     (((uint8_t  *)n)[(m<<1)+1])
#define  IB_PD_GetBytePtrHiByte(n, m)   ((uint8_t  *)&(((uint8_t  *)n)[(m<<1)]))
#define  IB_PD_GetBytePtrLoByte(n, m)   ((uint8_t  *)&(((uint8_t  *)n)[(m<<1)+1]))

#define  IB_PD_SetLongDataN(n, m, o)    (((uint8_t  *)n)[(m<<1)] = \
                                            IBS_HIBYTE(IBS_HIWORD(o)), \
                                         ((uint8_t  *)n)[(m<<1)+1] = \
                                            IBS_LOBYTE(IBS_HIWORD(o)), \
                                         ((uint8_t  *)n)[(m<<1)+2] = \
                                            IBS_HIBYTE(IBS_LOWORD(o)), \
                                         ((uint8_t  *)n)[(m<<1)+3] = \
                                            IBS_LOBYTE(IBS_LOWORD(o)))

#define  IB_PD_GetLongDataN(n, m)       (IBS_MAKELONG( ((uint8_t  *)n)[(m<<1)+3] | \
                                          (((uint8_t  *)n)[(m<<1)+2]<<8), \
                                         ((uint8_t  *)n)[(m<<1)+1] | \
                                          (((uint8_t  *)n)[(m<<1)]<<8)))

#elif defined(ETHA_BIG_ENDIAN) /* If not Intel processor */
/*
 * Warning : Currently, only the most important macros are available
 * for processors with Big Endian data format.
 * These macros are only available for reasons of compatibility, because
 * the data buffer can be worked on directly without problems when
 * Big Endian data format processors are used.
 */

#define  IBS_HTONL(l) (l)
#define  IBS_NTOHL(l) (l)
#define  IBS_HTONS(s) (s)
#define  IBS_NTOHS(s) (s)

#define  IBS_HIWORD(l)          ((uint16_t)((((uint32_t)(l)) >> 16) & 0xFFFF))
#define  IBS_LOWORD(l)          ((uint16_t)(uint32_t)(l))

#define  IBS_MAKELONG(low, high)    ((uint32_t)(((uint16_t)(low)) | \
                                    (((uint32_t)((uint16_t)(high))) << 16)))

/* Macros for creating a command */
#define  IB_SetCmdCode(n, m)            (((uint16_t *)n)[0] = m)
#define  IB_SetParaCnt(n, m)            (((uint16_t *)n)[1] = m)
#define  IB_SetParaN(n, m, o)           (((uint16_t *)n)[m+1] = o)

/* Macros for reading a message */
#define  IB_GetMsgCode(n)               (((uint16_t *)n)[0])
#define  IB_GetParaCnt(n)               (((uint16_t *)n)[1])
#define  IB_GetParaN(n,m)               (((uint16_t *)n)[m+1])

/* Macros for process data processing */
#define  IB_PD_SetDataN(n, m, o)        (((uint16_t *)n)[m] = o)
#define  IB_PD_GetDataN(n, m)           (((uint16_t *)n)[m])



#else

/* no define is set:
   use macros for little endian format (Intel processor)
*/

#define  IBS_HTONL(l) ( (((l) & 0x000000ff) << 24) | \
                        (((l) & 0x0000ff00) << 8)  | \
                        (((l) & 0x00ff0000) >> 8)  | \
                        (((l) & 0xff000000) >> 24) )
#define  IBS_NTOHL(l) IBS_HTON(l)
#define  IBS_HTONS(s) ((uint16_t)(((uint16_t)(s) >> 8) | ((uint16_t)(s) << 8)))
#define  IBS_NTOHS(s) IBS_HTONS(s)

#define  IBS_HIBYTE(w)          (uint8_t)((w) >> 8)
#define  IBS_LOBYTE(w)          (uint8_t)((w) & 0xFF)

#define  IBS_HIWORD(l)          ((uint16_t)((((uint32_t)(l)) >> 16) & 0xFFFF))
#define  IBS_LOWORD(l)          ((uint16_t)(uint32_t)(l))

#define  IBS_MAKELONG(low, high)    ((uint32_t)(((uint16_t)(low)) | \
                                    (((uint32_t)((uint16_t)(high))) << 16)))

/* Makros zum Zusammenstellen eines Kommandos */
#define  IB_SetCmdCode(n, m)            (((uint8_t  *)(n))[0] = \
                                            IBS_HIBYTE((m)),\
                                            ((uint8_t  *)(n))[1] = \
                                            IBS_LOBYTE(m))
#define  IB_SetParaCnt(n, m)            (((uint8_t  *)(n))[2] = \
                                            IBS_HIBYTE((m)), \
                                            ((uint8_t  *)(n))[3] = \
                                            IBS_LOBYTE((m)))
#define  IB_SetParaN(n, m, o)           (((uint8_t  *)(n))[((m)<<1)+2] = \
                                            IBS_HIBYTE(o), \
                                            ((uint8_t  *)(n))[((m)<<1)+3] = \
                                            IBS_LOBYTE((o)))
#define  IB_SetParaNHiByte(n, m, o)     (((uint8_t  *)(n))[((m)<<1)+2] = \
                                            (uint8_t)(o))
#define  IB_SetParaNLoByte(n, m, o)     (((uint8_t  *)(n))[((m)<<1)+3] = \
                                            (uint8_t)(o))
#define  IB_SetBytePtrHiByte(n, m)      ((uint8_t  *)&((n)[((m)<<1)+2]))
#define  IB_SetBytePtrLoByte(n, m)      ((uint8_t  *)&((n)[((m)<<1)+3]))

/* Makros zum Lesen einer Message */
#define  IB_GetMsgCode(n)               (((uint8_t  *)(n))[1] | \
                                        (((uint8_t  *)(n))[0]<<8))
#define  IB_GetParaCnt(n)               (((uint8_t  *)(n))[3] | \
                                        (((uint8_t  *)(n))[2]<<8))
#define  IB_GetParaN(n,m)               (((uint8_t  *)(n))[((m)<<1)+3] | \
                                        (((uint8_t  *)(n))[((m)<<1)+2]<<8))
#define  IB_GetParaNHiByte(n,m)         (((uint8_t  *)(n))[((m)<<1)+2])
#define  IB_GetParaNLoByte(n,m)         (((uint8_t  *)(n))[((m)<<1)+3])
#define  IB_GetBytePtrHiByte(n,m)       (&((n)[((m)<<1)+2]))
#define  IB_GetBytePtrLoByte(n,m)       (&((n)[((m)<<1)+3]))

/* Makros zur Prozessdatenbearbeitung */
#define  IB_PD_SetDataN(n, m, o)        (((uint8_t  *)n)[(m<<1)] = \
                                            IBS_HIBYTE(o), \
                                        ((uint8_t  *)n)[(m<<1)+1] = \
                                            IBS_LOBYTE(o))
#define  IB_PD_SetDataNHiByte(n, m, o)  (((uint8_t  *)n)[(m<<1)] = \
                                            (uint8_t)o)
#define  IB_PD_SetDataNLoByte(n, m, o)  (((uint8_t  *)n)[(m<<1)+1] = \
                                            (uint8_t)o)
#define  IB_PD_SetBytePtrHiByte(n, m)   ((uint8_t  *)&(((uint8_t  *)n)\
                                            [(m<<1)]))
#define  IB_PD_SetBytePtrLoByte(n, m)   ((uint8_t  *)&(((uint8_t  *)n)\
                                            [(m<<1)+1]))

#define  IB_PD_GetDataN(n, m)           (((uint8_t  *)n)[(m<<1)+1] | \
                                        (((uint8_t  *)n)[(m<<1)]<<8))
#define  IB_PD_GetDataNHiByte(n, m)     (((uint8_t  *)n)[(m<<1)])
#define  IB_PD_GetDataNLoByte(n, m)     (((uint8_t  *)n)[(m<<1)+1])
#define  IB_PD_GetBytePtrHiByte(n, m)   ((uint8_t  *)&(((uint8_t  *)n)\
                                            [(m<<1)]))
#define  IB_PD_GetBytePtrLoByte(n, m)   ((uint8_t  *)&(((uint8_t  *)n)\
                                            [(m<<1)+1]))

#define  IB_PD_SetLongDataN(n, m, o)    (((uint8_t  *)n)[(m<<1)] = \
                                            IBS_HIBYTE(IBS_HIWORD(o)), \
                                         ((uint8_t  *)n)[(m<<1)+1] = \
                                            IBS_LOBYTE(IBS_HIWORD(o)), \
                                         ((uint8_t  *)n)[(m<<1)+2] = \
                                            IBS_HIBYTE(IBS_LOWORD(o)), \
                                         ((uint8_t  *)n)[(m<<1)+3] = \
                                            IBS_LOBYTE(IBS_LOWORD(o)))

#define  IB_PD_GetLongDataN(n, m)       (IBS_MAKELONG( ((uint8_t  *)n)\
                                           [(m<<1)+3] | \
                                           (((uint8_t  *)n)[(m<<1)+2]<<8),\
                                           ((uint8_t  *)n)[(m<<1)+1] | \
                                           (((uint8_t  *)n)[(m<<1)]<<8)))



#endif


/*****************************************************************************
****  TYPE DEFINITIONS                                                    ****
*****************************************************************************/


/*****************************************************************************
****  GLOBAL FUNCTION DECLARATIONS (EXTERNAL LINKAGE)                     ****
*****************************************************************************/


/*****************************************************************************
****  GLOBAL DATA DECLARATIONS (EXTERNAL LINKAGE)                         ****
*****************************************************************************/


#ifdef __cplusplus
}
#endif

#endif    /* (ifndef INCL_DDI_MACR) */



