/*****************************************************************************
**                                                                          **
**              PHOENIX CONTACT GmbH & Co., 32819 Blomberg                  **
**                                                                          **
******************************************************************************
**                                                                          **
** Project      : System-Firmware                                           **
** Sub-Project  : FIBO Agent                                                **
**                                                                          **
*****************************************************************************/
/*
**    Definition:   Matthias Prüßner
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
\brief          System-Firmware, FIBO Agent
**
**       $Author: $
**         $Date: $
**     $Revision: $
**          $URL: h $
**
\b Description  :
\par
                messages-codes for all Service-Primitives (.req,.ind,.rsp,.cnf)

*****************************************************************************/
#ifndef INCL_FIBO_MSG_CODES
#define INCL_FIBO_MSG_CODES

#ifdef __cplusplus
extern "C" {
#endif

/* For FIBO we use the same Mailbox Interface as used for IBS-G4.
 * So we use the same structure for build the message code.
 */
/*****************************************************************************
****  CONSTANT DEFINITIONS                                                ****
*****************************************************************************/
/* Ab FW V4.0 werden die Message-Codes nach bestimmten Kriterien vergeben,  */
/* welche sich in der Struktur der Codes niederschlagen. Aus dieser Struktur*/
/* lassen sich die Grundeigenschaften des Services, wie Service-Primitiven, */
/* Prioritaeten, confirmed/unconfirmed und exclusiv-usable ablesen          */
/* Der Message-Code ist folgendermassen strukturiert :                      */
/*                                                                          */
/*      Bit     |15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00|           */
/*              |__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|           */
/*              |     |     |c/|  |                             |           */
/*              |prim.|prior|/u|ex|    1024  Service-Codes      |           */
/*                                                                          */
/*                                                                          */
/* prim. (Service-Primitive):                                               */
/*                                                                          */
/* 0 0 - Request                                                            */
/* 0 1 - Indication                                                         */
/* 1 0 - Confirmation                                                       */
/* 1 1 - Response                                                           */
/*                                                                          */
/*                                                                          */
/* prior (Prioritaet des Services):                                         */
/*                                                                          */
/* fuer Indication und Confirmation:                                        */
/* 0 0 - Anwenderfehler      (niedrigste Prioritaet)                        */
/* 0 1 - Modul - Fehler                                                     */
/* 1 0 - Bus - Fehler                                                       */
/* 1 1 - Controller - Fehler (hoechste Prioritaet)                          */
/*                                                                          */
/* fuer Request (und Response):                                             */
/* 0 0 - niederpriore Services (fast alle)                                  */
/* 0 1 - hochpriore Services   (z.B. Alarm-Stop)                            */
/*                                                                          */
/*                                                                          */
/* c/u  (confirmed / unconfirmed Service):                                  */
/*                                                                          */
/*  0  - confirmed Service                                                  */
/*  1  - unconfirmed Service                                                */
/*                                                                          */
/*                                                                          */
/* ex (exclusiv usable Services):                                           */
/*                                                                          */
/*  0  - Service ist ohne besondere Verriegelung von mehreren Usern nutzbar */
/*  1  - Service ist nur von einem User exclusiv nutzbar                    */
/*                                                                          */
/*                                                                          */
/* Service-Codes:                                                           */
/* Innerhalb der 1024 Services-Codes gibt es folgende Bereiche :            */
/*                                                                          */
/* 1. 000 - 0FF : remote Services                                           */
/* 2. 100 - 2FF : lokale, immediate-confirmed Services                      */
/* 3. 300 - 3FF : lokale, zeitlich entkoppelte Services bzw. Indications    */
/*                                                                          */
/* Innerhalb dieser 3 Bereiche koennen noch Teilbereiche geschaffen werden, */
/* in welchen die Service-Codes bestimmter Firmware-Komponenten (SM, PCP..) */
/* vergeben werden koennen :                                                */
/*                                                                          */
/* zu 1. 000 - 0FF : PDI                                                    */
/*                                                                          */
/* zu 2. 100 - 13F : SM ???                                                 */
/*       140   17F : L_API                                                  */
/*       180 - 2FE : frei                                                   */
/*       2FF       : extension                                              */
/*                                                                          */
/* zu 3. 300 - 33F : SM lokale, zeitlich entkoppelte Services               */
/*       340 - 34F : SM Indications                                         */
/*       350 - 36F : L-API lokale, zeitlich entkoppelte Services            */
/*       370 - 3FE : frei                                                   */
/*       3FF       : extension                                              */
/*                                                                          */
/* Innerhalb dieser Teilbereiche koennen noch Unterteilungen vorgenommen    */
/* werden, welche die interne Struktur der Firmware-Komponente widerspiegeln*/
/* z.B. Bereiche fuer Meta-Services, PNM7-Services im PCP  oder             */
/*      Bereiche fuer PD-OV-, PDRL- und CFG-Services im SM                  */
/*                                                                          */
/****************************************************************************/

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!      Bei der Vergabe von Message-Codes fuer neue Services ist    !!! */
/* !!!      unbedingt die oben beschriebene Struktur einzuhalten        !!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/* Mask for set confirmation bit in a request */
#define MSG_CODE_CONF_BIT               0x8000

/* Mask for the bit c/u (confirmed / unconfirmed service) */
#define MSG_CODE_UNCONF_SERV_MASK       0x0800

/* Mask for the bit ex (exclusiv service) */
#define MSG_CODE_EXCLUSIV_SERV_MASK     0x0400


/*
 * Message-Codes fuer PDI
 */
/* PDI Read */
#define FIBO_PDI_READ_OBJECT_REQ                    0x0041
#define FIBO_PDI_READ_OBJECT_CNF                    0x8041

/* PDI Write */
#define FIBO_PDI_WRITE_OBJECT_REQ                   0x0042
#define FIBO_PDI_WRITE_OBJECT_CNF                   0x8042

/*  Indication des PDI */
#define FIBO_PDI_SYSTEM_RCV_IND                     0x40F0



/*
 * L-API immidiatly
 */

/*
 * L-API lokale, zeitlich entkoppelte Services
 * (Execute in SM-Task)
 */

/* Listen Set Value */
#define FIBO_LAPI_SET_VALUE_REQ                     0x0750
#define FIBO_LAPI_SET_VALUE_CNF                     0x8750

/* Listen Read Value */
#define FIBO_LAPI_READ_VALUE_REQ                    0x0351
#define FIBO_LAPI_READ_VALUE_CNF                    0x8351

/* L-API-Change-Exclusive-Rights */
#define FIBO_LAPI_CHANGE_EXCLUSIVE_RIGHTS_REQ       0x014F
#define FIBO_LAPI_CHANGE_EXCLUSIVE_RIGHTS_CNF       0x814F

/* L-API-Set_Indication */
#define FIBO_LAPI_SET_INDICATION_REQ                0x0152
#define FIBO_LAPI_SET_INDICATION_CNF                0x8152

#if 0

/* L-API-Fetch-Exclusive-Rights */
#define L_API_FETCH_EXCLUSIVE_RIGHTS_REQ_CODE       0x0156
#define L_API_FETCH_EXCLUSIVE_RIGHTS_CNF_CODE       0x8156

/*L-API-Switch-Var-Id-Access (on / off ) */
#define L_API_SWITCH_VAR_ID_ACCESS_REQ_CODE         0x0157
#define L_API_SWITCH_VAR_ID_ACCESS_CNF_CODE         0x8157

#define L_API_STORE_RESIDENT_CURRENT_CFG_REQ_CODE   0x0162
#define L_API_STORE_RESIDENT_CURRENT_CFG_CNF_CODE   0x8162

#endif

/*
 * Service for DDI:
 * Exchange of Data between upper and lower part of the DDI (DPM)
 */
#define FIBO_DDI_CLOSE_NODE_UC_REQ                  0x0980
#define FIBO_DDI_CLOSE_NODE_REQ                     0x0180
#define FIBO_DDI_CLOSE_NODE_CNF                     0x8180

#define FIBO_DDI_SET_VALUE_REQ                      0x0181
#define FIBO_DDI_SET_VALUE_CNF                      0x8181

#define FIBO_DDI_READ_VALUE_REQ                     0x0182
#define FIBO_DDI_READ_VALUE_CNF                     0x8182

#define FIBO_LAPI_WRITE_FILE                        0x0183
#define FIBO_LAPI_WRITE_FILE_CNF                    0x8183

#if 0

/* Confirm-Diagnose */
#define DDP_CONFIRM_DIAG_REQ_CODE                   0x0760
#define DDP_CONFIRM_DIAG_CNF_CODE                   0x8760

#endif



/*
 * Messages-Codes fuer zeitlich entkoppelte SM-Services
 */

/* Start-Data-Transfer */
#define FIBO_SM_ENABLE_DATA_OUTPUT_REQ              0x0701
#define FIBO_SM_ENABLE_DATA_OUTPUT_CNF              0x8701

/* Stop-Data-Transfer */
#define FIBO_SM_DISABLE_DATA_OUTPUT_REQ             0x0702
#define FIBO_SM_DISABLE_DATA_OUTPUT_CNF             0x8702

/* Alarm-Stop 0x1303, but no exclusiv */
#define FIBO_SM_RESET_DRV_REQ                       0x1703
#define FIBO_SM_RESET_DRV_CNF                       0x9703

/* Switch FIBO-Bus Power */
#define FIBO_SM_CHANGE_POWER_STATE_REQ              0x0704
#define FIBO_SM_CHANGE_POWER_STATE_CNF              0x8704

/* Initiate-Load */
#define FIBO_SM_INITIATE_LOAD_REQ                   0x0306
#define FIBO_SM_INITIATE_LOAD_CNF                   0x8306

/* Load-Configuration */
#define FIBO_SM_LOAD_CFG_REQ                        0x0307
#define FIBO_SM_LOAD_CFG_CNF                        0x8307

/* Complete-Load-Configuration */
#define FIBO_SM_COMPLETE_LOAD_CFG_REQ               0x030A
#define FIBO_SM_COMPLETE_LOAD_CFG_CNF               0x830A

/* Terminate-Load */
#define FIBO_SM_TERMINATE_LOAD_REQ                  0x0308
#define FIBO_SM_TERMINATE_LOAD_CNF                  0x8308

/* Read-Configuration */
#define FIBO_SM_READ_CFG_REQ                        0x0309
#define FIBO_SM_READ_CFG_CNF                        0x8309

/* Complete-Read-Configuration */
#define FIBO_SM_COMPLETE_READ_CFG_REQ               0x030B
#define FIBO_SM_COMPLETE_READ_CFG_CNF               0x830B

/* Control-Statistics */
#define FIBO_SM_CONTROL_STATISTICS_REQ              0x030F
#define FIBO_SM_CONTROL_STATISTICS_CNF              0x830F


/* Create-Configuration */
#define FIBO_SM_CREATE_CFG_REQ                      0x0710
#define FIBO_SM_CREATE_CFG_CNF                      0x8710

/* Activate-Configuration */
#define FIBO_SM_ACTIVATE_CFG_REQ                    0x0711
#define FIBO_SM_ACTIVATE_CFG_CNF                    0x8711

/* Deactivate-Configuration */
#define FIBO_SM_DEACTIVATE_CFG_REQ                  0x0712
#define FIBO_SM_DEACTIVATE_CFG_CNF                  0x8712

/* Activate-Sync */
#define FIBO_SM_ACTIVATE_SYNC_REQ                   0x0714
#define FIBO_SM_ACTIVATE_SYNC_CNF                   0x8714
/* Evaluate-Sync */
#define FIBO_SM_EVALUATE_SYNC_REQ                   0x0315
#define FIBO_SM_EVALUATE_SYNC_CNF                   0x8315

/* Control-Device-Function */
#define FIBO_SM_CONTROL_DEVICE_FUNC_REQ             0x0718
#define FIBO_SM_CONTROL_DEVICE_FUNC_CNF             0x8718

/* Load_PD_Mapping */
#define FIBO_SM_LOAD_PD_MAPPING_REQ                 0x0728
#define FIBO_SM_LOAD_PD_MAPPING_CNF                 0x8728

/* Get-Revision-Info */
#define FIBO_SM_GET_REVISION_INFO_REQ               0x032A
#define FIBO_SM_GET_REVISION_INFO_CNF               0x832A

/* Get-Diag-Info */
#define FIBO_SM_GET_DIAG_INFO_REQ                   0x032B
#define FIBO_SM_GET_DIAG_INFO_CNF                   0x832B

/* Read-PD-IN */
#define FIBO_SM_READ_PD_IN_REQ                      0x0335
#define FIBO_SM_READ_PD_IN_CNF                      0x8335

/* Force-PD */
#define FIBO_SM_FORCE_PD_REQ                        0x0736
#define FIBO_SM_FORCE_PD_CNF                        0x8736

#if 0

/* Control-Device-Function */
#define SM_CONTROL_DEVICE_FUNC_REQ_CODE             0x0714
#define SM_CONTROL_DEVICE_FUNC_CNF_CODE             0x8714

/* Control-Device-Function-no-exclusive */
#define SM_CONTROL_DEVICE_FUNC_NO_EX_REQ_CODE       0x0314
#define SM_CONTROL_DEVICE_FUNC_NO_EX_CNF_CODE       0x8314

/* Read-Device-State */
#define SM_READ_DEVICE_STATE_REQ_CODE               0x0315
#define SM_READ_DEVICE_STATE_CNF_CODE               0x8315

/* Read-Process-Data */
#define SM_READ_PROCESS_DATA_REQ_CODE               0x0335
#define SM_READ_PROCESS_DATA_CNF_CODE               0x8335

#endif


/*
 * Messages-Codes fuer Indikations
 */
/*#define FIBO_DEVICE_STATE_IND                     0x5340  not supported since FIBO Rev. 1.40, use FIBO_DEVICE_STATE_EXT_IND */
#define FIBO_DEVICE_PARA_REQ_IND                    0x5341
#define FIBO_DEVICE_STATE_EXT_IND                   0x5345

#define FIBO_BUS_STATE_IND                          0x6342
#define FIBO_BUS_INFO_IND                           0x4343
#define FIBO_BUS_SYNC_IND                           0x4344

#define FIBO_DRV_DEVICE_REPORT_IND                  0x534E  /* used only between HW-CTRL and SM */
#define FIBO_DRV_PMODULE_REPLACED_IND               0x534F  /* used only between HW-CTRL and SM */


/*****************************************************************************/
/* Defines for Service Parameter                                             */
/*****************************************************************************/

/* ! Bit-Mask for Used_Attributs from FIBO-Config-Services */
/* FIBO-Devices have a unique ModuletypeCode (Object 0x0037)
   In the high 4 Bytes we have a Type, in the low 4 Bytes a unique Number.
   For handling as DWORD we make to entrys */
#define DEV_TYPE_BIT                0x0001
#define DEV_ID_BIT                  0x0002
#define DEV_LEN_BIT                 0x0004

#define DEV_STATE_BIT               0x0010  /* Last received error state from device */
#define DEV_STATE_ADD_BIT           0x0020  /* Last received error count, prio and location */

#define DEV_MM_STATE_BIT            0x0080  /* Device Management State */

#define DEV_ERR_COUNT               0x0100  /* Counter for Link Lost */

#define DEV_SUBBUS_TYPE_BIT         0x1000  /* Type of Subbus Master */
#define DEV_MODE_BIT                0x2000  /* Control Bits for Device access */
#define DEV_CHIP_VERSION_BIT        0x4000

#define ATTIB_EXT_BIT               0x8000  /* reserved for extensions */

/* ! Bit-Mask for Diag_Info_Attr from FIBO-Diag-Service */
#define HW_ERROR_ATTR_BIT           0x4000

/* ! specific FRAME-Ref for force a Setup-Cycle */
#define FORCE_SETUP_FRAME_REF       0x7FFE

/* ! Bit-Mask for Enable/Disable PD-Exchange with CRs */
#define FCR_0                       0x0001
#define FCR_1                       0x0002
#define FCR_2                       0x0004
#define FCR_3                       0x0008
#define FCR_CROSS                   0x4000
#define FCR_CPU                     0x8000
#define FCR_ALL                     0xFFFF /* only for disable */

/* ! Supported CR Bits */
#define SELECTABLE_CR_BITS         (FCR_0 | FCR_1 | FCR_2 | FCR_3 | FCR_CROSS | FCR_CPU)

/* ! Bit-Mask for Load_PD_Mapping-Service */
/* Address Direktion*/
#define PD_MAP_ADDR_DIRECTION_IN    0x1000
#define PD_MAP_ADDR_DIRECTION_OUT   0x2000
/* CR use same as for Enable/Disable */
/* Mode */
#define PD_MAP_MODE_IOXS_MASK       0x000F
#define PD_MAP_MODE_IOXS_OFFSET     0x0001
#define PD_MAP_MODE_IOXS_STICKY     0x0002
#define PD_MAP_MODE_IOXS_LEAST      0x0003

#define PD_MAP_MODE_CYCLIC_EXT_DATA 0x0010
#define PD_MAP_MODE_INIT_IOXS_OUT   0x0020
#define PD_MAP_MODE_SET_INTERNALS   0x1000

/* Parameter for Switch FIOBO Power Mode */
#define FIBO_POWER_ON               0x0001
#define FIBO_POWER_OFF              0x0000

/* Parameter for Control_Device_Function */
#define FIBO_CTRL_DEV_FUNC_ENABLE   0x0001
#define FIBO_CTRL_DEV_FUNC_DISABLE  0x0002

/* Bitmask for CompleteReadConfig - Field wSubBusType */
#define FIBO_SUBBUS_NO_MASTER       0x0000
#define FIBO_SUBBUS_TYPE_MSK        0xFF00
#define FIBO_SUBBUS_VERSION_MSK     0x00FF
#define FIBO_SUBBUS_TYPE_UNKNOWN    0x0100
#define FIBO_SUBBUS_TYPE_ASI_03     0x0203
#define FIBO_SUBBUS_TYPE_CAN_01     0x0301
#define FIBO_SUBBUS_TYPE_DALI_01    0x0401
#define FIBO_SUBBUS_TYPE_IBS_01     0x0501
#define FIBO_SUBBUS_TYPE_IOL_01     0x0601
#define FIBO_SUBBUS_TYPE_PB_01      0x0701


#ifdef __cplusplus
}
#endif

#endif  /* INCL_FIBO_MSG_CODES */

