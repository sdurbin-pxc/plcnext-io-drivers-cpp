/*****************************************************************************
**                                                                          **
**              PHOENIX CONTACT Electronics GmbH, 31812 Bad Pyrmont         **
**                                                                          **
******************************************************************************
**                                                                          **
** Project      : AXIO Message Box Interface Driver                         **
** Sub-Project  : AXIO Bus, DDI - Device Driver Interface                   **
**                                                                          **
*****************************************************************************/
/*
**    Definition:   Stefan Schmitz
**
**  Component(s):   -
**
**     Device(s):   independent
**
**   Terminology:   -
**
**        Status:   -
**
*/
/*!
\file
\brief          System-Firmware, AXIOFIBO Agent
**
**       $Author: Stefan, Schmitz $
**         $Date: 2016-03-03 14:16:07 +0100 $
**     $Revision: $
**          $URL: $
**
\b Description  :
\par
                Driver to communicate with the Nios2 firmware.
                This Driver allows to send messages in mailbox format and read
                some control registers (e.g. diagnostic).

******************************************************************************
Change Notes:
 *
 * Initial revision.
*/
#ifndef AXIO_XFER_H_
#define AXIO_XFER_H_


/*****************************************************************************
****  CONSTANT DEFINITIONS                                                ****
*****************************************************************************/
/*! macro to build the device io control codes for AXM */
#define MONA_IOCTL_AXM(func)        (func)

/* Message Box Interface definitions */
#define AXM_MXI_MAX_MSGLEN_BYTES    1024u    /* Max message size in bytes */

/* DRIVER IOCTRLS (old notation for compatibility)*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//#define MONA_IOCTL_AXM_DMA_SET_CYCLE_TIME       MONA_IOCTL_AXM(0x10)    /* not supported --> return 0 */
#define MONA_IOCTL_AXM_DTI_WRITE_DATA           MONA_IOCTL_AXM(0x20)
#define MONA_IOCTL_AXM_DTI_READ_DATA            MONA_IOCTL_AXM(0x21)
#define MONA_IOCTL_AXM_MXI_SND_MSG              MONA_IOCTL_AXM(0x30)
#define MONA_IOCTL_AXM_MXI_RCV_MSG              MONA_IOCTL_AXM(0x31)
//#define MONA_IOCTL_AXM_GET_API_COMM_RESRC       MONA_IOCTL_AXM(0x40)
#define MONA_IOCTL_AXM_GET_DIAGNOSTIC_EX        MONA_IOCTL_AXM(0x5A)    /* DDI_GET_DIAGNOSTIC_EX    */
//#define MONA_IOCTL_AXM_MPM_WRITE_DATA           MONA_IOCTL_AXM(0x21)    /* DDI_WRITE_MPM            */
//#define MONA_IOCTL_AXM_MPM_READ_DATA            MONA_IOCTL_AXM(0x20)    /* DDI_READ_MPM             */
#define MONA_IOCTL_AXM_GET_SYSFAIL_REG          MONA_IOCTL_AXM(0x29)    /* DDI_GET_SYS_FAIL         */
#define MONA_IOCTL_AXM_SET_SYSFAIL_SIGNAL       MONA_IOCTL_AXM(0x87)    /* DDI_SET_SYS_FAIL         */
#define MONA_IOCTL_AXM_CLR_SYSFAIL_SIGNAL       MONA_IOCTL_AXM(0x88)    /* DDI_CLR_SYS_FAIL         */
//#define MONA_IOCTL_AXM_DBG_DRV                  MONA_IOCTL_AXM(0x90)

/* New notation */
#define IOCTL_AXM_PD_WRITE_DATA                 MONA_IOCTL_AXM_DTI_WRITE_DATA       /* Write process data.     */
#define IOCTL_AXM_PD_READ_DATA                  MONA_IOCTL_AXM_DTI_READ_DATA        /* Read process data.      */
#define IOCTL_AXM_MXI_SND_MSG                   MONA_IOCTL_AXM_MXI_SND_MSG          /* Send data via MXI.      */
#define IOCTL_AXM_MXI_RCV_MSG                   MONA_IOCTL_AXM_MXI_RCV_MSG          /* Read data via MXI.      */
#define IOCTL_AXM_GET_DIAGNOSTIC_EX             MONA_IOCTL_AXM_GET_DIAGNOSTIC_EX    /* Read diagnosis data.    */
#define IOCTL_AXM_GET_SYSFAIL_REG               MONA_IOCTL_AXM_GET_SYSFAIL_REG      /* Read sysfail register.  */
#define IOCTL_AXM_SET_SYSFAIL_SIGNAL            MONA_IOCTL_AXM_SET_SYSFAIL_SIGNAL   /* Set sysfail register.   */
#define IOCTL_AXM_CLR_SYSFAIL_SIGNAL            MONA_IOCTL_AXM_CLR_SYSFAIL_SIGNAL   /* Clear sysfail register. */
#define IOCTL_AXM_RESET_DRIVER                  0x100                               /* Clear all buffers.      */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Data structures for ioctl() command codes */

#ifndef VOID
    typedef void VOID;
#endif

#ifndef INT8
    typedef signed char INT8;
#endif

#ifndef INT16
    typedef signed short INT16;
#endif

#ifndef INT32
    typedef signed int INT32;
#endif

#ifndef INT64
    typedef signed long long INT64;
#endif

#ifndef USIGN8
    typedef unsigned char USIGN8;
#endif

#ifndef USIGN16
    typedef unsigned short USIGN16;
#endif

#ifndef USIGN32
    typedef unsigned int USIGN32;
#endif

#ifndef USIGN64
    typedef unsigned long long USIGN64;
#endif

#ifndef CHAR
    typedef signed char CHAR;
#endif

#ifndef BOOL
    typedef int BOOL;
#endif

#ifndef HANDLE
    typedef int HANDLE;
#endif

#ifndef H_ES
    typedef void* H_ES;
#endif

#ifndef H_DRVCTX
    typedef int H_DRVCTX;
#endif

#ifndef FWAPIRET
    typedef int FWAPIRET;
#endif

#pragma pack (1)
typedef struct t_axm_mxi_msg
{
    USIGN8      byClntId;
    USIGN8      byMsgOpts;
    USIGN16     wMsgType;
    USIGN16     wMsgBytes;
    USIGN16     wMsgId;
    USIGN32     dwMsgTO;
    USIGN8     *pbyMsgBuf;
//#if defined ARP_CXX_COMPILER_GCC
} T_AXM_MXI_MSG __attribute__ ((aligned (1)));
//#else
//} T_AXM_MXI_MSG;
//#endif

typedef struct t_axm_dti_acc
{
    USIGN8     *pbyData;
    USIGN32     dwAccOffs;
    USIGN32     dwAccLen;
    USIGN32     dwAccTO;
    USIGN32     dwOpts;
//#if defined ARP_CXX_COMPILER_GCC
} T_AXM_DTI_ACC __attribute__((aligned(1)));
//#else
//} T_AXM_DTI_ACC;
//#endif
#pragma pack ()

/* For AXM_DRVAPI_GetDiagnosticEx */
typedef struct t_axm_diag_ex
{
    USIGN16  wStatus;       /* diagnostic bit register */
    USIGN16  wDiagPara;     /* diagnostic parameter register */
    USIGN16  wAddInfo;      /* diagnostic register Add_Error_Info */
    USIGN16  wReserved;
} T_AXM_DIAG_EX;


#endif /* AXIO_XFER_H_ */
