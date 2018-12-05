/*!
 * @file        NexMotionDef.h
 * @brief       A head file define more variable types for NexMotion Library
 * @author      NexCOBOT, Inc.
 */

#ifndef   __NEXMOTION_DEF_H
#define   __NEXMOTION_DEF_H

#include "nex_type.h"

/*! \addtogroup Device_Type
 *  Device types. for NMC_DeviceOpenUp()
 *  @{
 */
#define NMC_DEVICE_TYPE_SIMULATOR           (0)   //!< Use Simulator as device types. for NMC_DeviceOpenUp()
#define NMC_DEVICE_TYPE_ETHERCAT            (1)   //!< Use EtherCAT as Device types. for NMC_DeviceOpenUp()
/*!
 *  @}
 */

//! Wait functions timeout
#define NMC_WAIT_TIME_INFINITE              (0xFFFFFFFF)

/*! \addtogroup Device_State
 *  State definition of devices. NMC_DeviceGetState()
 *  @{
 */
#define NMC_DEVICE_STATE_INIT               (1)   //!< Init: The device parameters are not configured or have been removed.
#define NMC_DEVICE_STATE_READY              (2)   //!< Ready: The device parameters have been configured
#define NMC_DEVICE_STATE_ERROR              (3)   //!< Error: The device enters a critical error state, such as the communication failure.
#define NMC_DEVICE_STATE_OPERATION          (4)   //!< Operation
/*!
 *  @}
 */

/*! \addtogroup Safety
 *  State definition of safety
 *  @{
 */
#define NMC_SAFETY_STATE_DISABLE            (0)
#define NMC_SAFETY_STATE_READY              (1)
#define NMC_SAFETY_STATE_ERROR              (2)
/*!
 *  @}
 */

/*! \addtogroup Sefety_Mode
 *  Safety operation mode definition.
 *  @{
 */
#define NMC_SAFETY_MODE_OP_T1               (0)
#define NMC_SAFETY_MODE_OP_T2               (1)
#define NMC_SAFETY_MODE_OP_AUT              (2)
/*!
 *  @}
 */

/*! \addtogroup Watchdog_Mode
 *  Watch dog timeout mode
 *  @{
 */
#define NMC_SAFETY_WDT_TIMEOUT_STOP0        (0)
#define NMC_SAFETY_WDT_TIMEOUT_STOP1        (1)
/*!
 *  @}
 */

/*! \addtogroup Coord_Type
 *  Coordinate system type definition for group operation
 *  @{
 */
#define NMC_COORD_MCS                       (0)   //!< (MCS) Mechanical also called base/world coordinate system
#define NMC_COORD_PCS                       (1)   //!< (PCS) Programming also called product/work coordinate system
#define NMC_COORD_ACS                       (2)   //!< (ACS) Axis coordinate system
/*!
 *  @}
 */

/*! \addtogroup Axis_State
 *  State definition of axis.
 *  The axis state is read via NMC_AxisGetState(). The variable represents the
 *  meanings as following.
 *  @{
 */
#define NMC_AXIS_STATE_DISABLE              (0)   //!< Disable: The servo is OFF.
#define NMC_AXIS_STATE_STAND_STILL          (1)   //!< Enable: The servo is stand still.
#define NMC_AXIS_STATE_HOMING               (2)   //!< Executing the Homing motion.
#define NMC_AXIS_STATE_DISCRETE_MOTION      (3)   //!< Executing the point-to-point motion.
#define NMC_AXIS_STATE_CONTINUOUS_MOTION    (4)   //!< Executing the continuous motion.
#define NMC_AXIS_STATE_STOPPING             (5)   //!< Receiving the Stop command and slowing down to stop.
#define NMC_AXIS_STATE_STOPPED              (6)   //!< Receiving the Stop command and stopped.
#define NMC_AXIS_STATE_WAIT_SYNC            (7)   //!< Receiving the Wait command and waiting for SYNC signal.
#define NMC_AXIS_STATE_GROUP_MOTION         (8)
#define NMC_AXIS_STATE_ERROR                (10)  //!< Stop for error.
/*!
 *  @}
 */

/*! \addtogroup Axis_Status
 *  Status bit number definition of axis
 *  The axis status is read via NMC_AxisGetStatus(). Each bit code of the
 *  variable represents the meanings Positiveas following.
 *
 *  (*1) After the error state is resolved, the Latched signal will be cleared
 *  to 0 after the function NMC_AxisResetState() is called.
 *  @{
 */
#define NMC_AXIS_STATUS_EMG                 (0)   //!< A latched signal is issued at the EMG signal (*1).
#define NMC_AXIS_STATUS_ALM                 (1)   //!< A latched signal is issued at the servo Alarm (*1).
#define NMC_AXIS_STATUS_PEL                 (2)   //!< A latched signal is issued at the positive limit signal (*1).
#define NMC_AXIS_STATUS_NEL                 (3)   //!< A latched signal is issued at the negative limit signal (*1).
#define NMC_AXIS_STATUS_PSEL                (4)   //!< A latched signal is issued at the software positive limit signal (*1).
#define NMC_AXIS_STATUS_NSEL                (5)   //!< A latched signal is issued at the software negitive limit signal (*1).
#define NMC_AXIS_STATUS_ENA                 (6)   //!< The axis is Enable or Disable.
#define NMC_AXIS_STATUS_ERR                 (7)   //!< Axis error
#define NMC_AXIS_STATUS_TAR                 (8)   //!< The axis has reached the target position.
#define NMC_AXIS_STATUS_CSTP                (9)   //!< The axis commands to Stop.
#define NMC_AXIS_STATUS_ACC                 (10)  //!< The axis is operating in acceleration.
#define NMC_AXIS_STATUS_DEC                 (11)  //!< The axis is operating in decceleration.
#define NMC_AXIS_STATUS_MV                  (12)  //!< The axis is operating at the maximum velocity.
#define NMC_AXIS_STATUS_OP                  (13)  //!< The axis is operating.
#define NMC_AXIS_STATUS_STOP                (14)  //!< The axis is STOP.
#define NMC_AXIS_STATUS_RPEL	              (16)  //!< Positive limit signal: 1: Triggered, 0: Not Triggered
#define NMC_AXIS_STATUS_RNEL	              (17)  //!< Negative limit signal: 1: Triggered, 0: Not Triggered
#define NMC_AXIS_STATUS_RHOM	              (18)  //!< Home signal: 1: High level, 0: Low Level
/*!
 *  @}
 */


/*! \addtogroup Axis_Status_Mask
 *  Status bit mask definition of axis
 *
 *  The motion status is read via NMC_AxisGetStatus(). Each bit mask of the
 *  variable represents the meanings as following.
 *
 *  (*1) After the error state is resolved, the Latched signal will be cleared
 *  to 0 after the function NMC_AxisResetState() is called.
 *  @{
 */
#define NMC_AXIS_STATUS_MASK_EMG            (0x00000001)  //!< The mask for a latched signal issued at the EMG signal (*1).
#define NMC_AXIS_STATUS_MASK_ALM            (0x00000002)  //!< The mask for a latched signal issued at the servo Alarm (*1).
#define NMC_AXIS_STATUS_MASK_PEL            (0x00000004)  //!< The mask for a latched signal issued at the positive limit signal (*1).
#define NMC_AXIS_STATUS_MASK_NEL            (0x00000008)  //!< The mask for a latched signal issued at the negative limit signal (*1).
#define NMC_AXIS_STATUS_MASK_PSEL           (0x00000010)  //!< The mask for a latched signal issued at the software positive signal (*1).
#define NMC_AXIS_STATUS_MASK_NSEL           (0x00000020)  //!< The mask for a latched signal issued at the software negative signal (*1).
#define NMC_AXIS_STATUS_MASK_ENA            (0x00000040)  //!< The mask to indicate the axis is Enable or Disable.
#define NMC_AXIS_STATUS_MASK_ERR            (0x00000080)  //!< The mask for axis error.
#define NMC_AXIS_STATUS_MASK_TAR            (0x00000100)  //!< The mask to indicate the axis has reached the target position.
#define NMC_AXIS_STATUS_MASK_CSTP           (0x00000200)  //!< The mask to indicate the axis commands to Stop.
#define NMC_AXIS_STATUS_MASK_ACC            (0x00000400)  //!< The mask to indicate the axis is operating in acceleration.
#define NMC_AXIS_STATUS_MASK_DEC            (0x00000800)  //!< The mask to indicate the axis is operating in decceleration.
#define NMC_AXIS_STATUS_MASK_MV             (0x00001000)  //!< The mask to indicate the axis is operating at the maximum velocity.
#define NMC_AXIS_STATUS_MASK_OP             (0x00002000)  //!< The mask to indicate the axis is operating.
#define NMC_AXIS_STATUS_MASK_STOP           (0x00004000)  //!< The mask to indicate the axis is STOP.
#define NMC_AXIS_STATUS_MASK_RPEL	          (0x00010000)  //!< The mask for the positive limit signal: 1:Triggered, 0: Not Triggered.
#define NMC_AXIS_STATUS_MASK_RNEL	          (0x00020000)  //!< The mask for the negative limit signal: 1:Triggered, 0: Not Triggered.
#define NMC_AXIS_STATUS_MASK_RHOM	          (0x00040000)  //!< The mask for the home signal: 1: High level, 0: Low level.
/*!
 *  @}
 */

/*! \addtogroup Group_State
 *  State definition of group
 *
 *  The group state is read via NMC_GroupGetState(). The variable represents
 *  the meanings as following
 *  @{
 */
#define NMC_GROUP_STATE_DISABLE             (0)   //!< Disable: The group servo is OFF.
#define NMC_GROUP_STATE_STAND_STILL         (1)   //!< Enable: The group servo is stand still.
#define NMC_GROUP_STATE_STOPPED             (2)   //!< Receiving the Stop command and stopped.
#define NMC_GROUP_STATE_STOPPING            (3)   //!< Receiving the Stop command and slowing down to stop.
#define NMC_GROUP_STATE_MOVING              (4)   //!< Executing the move command.
#define NMC_GROUP_STATE_HOMING              (5)   //!< Executing the Homing motion.
#define NMC_GROUP_STATE_ERROR               (6)   //!< Stop for error.
/*!
 *  @}
 */

/*! \addtogroup Group_Status
 *  Status bit number definition of group
 *
 *  The group status is read via NMC_GroupGetStatus(). Each bit code of the
 *  variable represents the meanings as following.
 *
 *  (*1) After the error state is resolved, the Latched signal will be cleared
 *  to 0 after the function NMC_GroupResetState() is called.
 *  @{
 */
#define NMC_GROUP_STATUS_EMG                (0)   //!< A latched signal is issued at the external EMG signal (*1).
#define NMC_GROUP_STATUS_ALM                (1)   //!< A latched signal is issued at a group axis servo Alarm (*1).
#define NMC_GROUP_STATUS_PEL                (2)   //!< A latched signal is issued at the positive limit signal of a group axis (*1).
#define NMC_GROUP_STATUS_NEL                (3)   //!< A latched signal is issued at the negative limit signal of a group axis (*1).
#define NMC_GROUP_STATUS_PSEL               (4)   //!< A latched signal is issued at the software positive limit signal of a group axis (*1).
#define NMC_GROUP_STATUS_NSEL               (5)   //!< A latched signal is issued at the software negative limit signal of a group axis (*1).
#define NMC_GROUP_STATUS_ENA                (6)   //!< The group is Enable or Disable.
#define NMC_GROUP_STATUS_ERR                (7)   //!< Group (a group of axis) error
#define NMC_GROUP_STATUS_CSTP               (9)   //!< No displacement of all group axis (i.e. the displacement is 0)
#define NMC_GROUP_STATUS_ACC                (10)  //!< Moving in the Cartesian coordinate system (along a line or an arc) and accelerating to the maximum velocity or decelerating. The value is 0 for PTP or JOG motion.
#define NMC_GROUP_STATUS_DEC                (11)  //!< Moving in the Cartesian coordinate system (along a line or an arc) and deccelerating to the target position or STOP. The value is 0 for PTP or JOG motion.
#define NMC_GROUP_STATUS_MV                 (12)  //!< Moving in the Cartesian coordinate system (along a line or an arc) at the maximum velocity. The value is 0 for PTP or JOG motion.
#define NMC_GROUP_STATUS_OP                 (13)  //!< The group is moving. That is the state is GROUP_MOVING, GROUP_HOMING or GROUP_STOPPING.
#define NMC_GROUP_STATUS_STOP               (14)  //!< The group is STOP. That is the state is GROUP_STOPPED.
/*!
 *  @}
 */

/*! \addtogroup Group_Status_Mask
 *  Status bit mask definition of group
 *  @{
 */
#define NMC_GROUP_STATUS_MASK_EMG           (0x00000001)
#define NMC_GROUP_STATUS_MASK_ALM           (0x00000002)
#define NMC_GROUP_STATUS_MASK_PEL           (0x00000004)
#define NMC_GROUP_STATUS_MASK_NEL           (0x00000008)
#define NMC_GROUP_STATUS_MASK_PSEL          (0x00000010)
#define NMC_GROUP_STATUS_MASK_NSEL          (0x00000020)
#define NMC_GROUP_STATUS_MASK_ENA           (0x00000040)
#define NMC_GROUP_STATUS_MASK_ERR           (0x00000080)
#define NMC_GROUP_STATUS_MASK_CSTP          (0x00000200)
#define NMC_GROUP_STATUS_MASK_ACC           (0x00000400)
#define NMC_GROUP_STATUS_MASK_DEC           (0x00000800)
#define NMC_GROUP_STATUS_MASK_MV            (0x00001000)
#define NMC_GROUP_STATUS_MASK_OP            (0x00002000)
#define NMC_GROUP_STATUS_MASK_STOP          (0x00004000)
/*!
 *  @}
 */

//! Group axis number definition
#define NMC_MAX_AXES_IN_GROUP               (8)

//! Pos_T array size definition
#define NMC_MAX_POS_SIZE                    (8)

//! Xyz_T array size definition
#define NMC_MAX_XYZ_SIZE                    (3)

//! APos_T array size definition
#define NMC_MAX_AXIS_POS_SIZE               (NMC_MAX_AXES_IN_GROUP)

//! CPos_T array size definition
#define NMC_MAX_CARTESIAN_POS_SIZE          (6)

/*! \addtogroup Group_Axis_Idx
 *  Group axis index definition
 *  @{
 */
#define NMC_GROUP_AXIS_X                    (0)
#define NMC_GROUP_AXIS_Y                    (1)
#define NMC_GROUP_AXIS_Z                    (2)
#define NMC_GROUP_AXIS_A                    (3)
#define NMC_GROUP_AXIS_B                    (4)
#define NMC_GROUP_AXIS_C                    (5)
#define NMC_GROUP_AXIS_U                    (6)
#define NMC_GROUP_AXIS_V                    (7)
/*!
 *  @}
 */

/*! \addtogroup Group_Axis_Mask
 *  Group axis mask definition
 *  @{
 */
#define NMC_GROUP_AXIS_MASK_X               (0x00000001)
#define NMC_GROUP_AXIS_MASK_Y               (0x00000002)
#define NMC_GROUP_AXIS_MASK_Z               (0x00000004)
#define NMC_GROUP_AXIS_MASK_A               (0x00000008)
#define NMC_GROUP_AXIS_MASK_B               (0x00000010)
#define NMC_GROUP_AXIS_MASK_C               (0x00000020)
#define NMC_GROUP_AXIS_MASK_U               (0x00000040)
#define NMC_GROUP_AXIS_MASK_V               (0x00000080)
#define NMC_GROUP_AXIS_MASK_ALL             (0x000000FF)
/*!
 *  @}
 */

/*! \addtogroup Trace_Mode
 *  API Trace mode definition
 *  @{
 */
#define NMC_TRACE_MODE_DISABLE              (0)
#define NMC_TRACE_MODE_ERROR                (1)
#define NMC_TRACE_MODE_ALL                  (2)
/*!
 *  @}
 */

/*! \addtogroup Msg_Type_Size
 *  Message type definition
 *  @{
 */
#define NMC_MAX_MSG_SOURCE_SIZE             (128)
#define NMC_MAX_MSG_TEXT_SIZE               (1024)
#define NMC_MSG_TYPE_NORMAL                 (0)
#define NMC_MSG_TYPE_WARNING                (1)
#define NMC_MSG_TYPE_ERROR                  (2)
#define NMC_MSG_TYPE_DEBUGING               (3)
/*!
 *  @}
 */

/*! \addtogroup Memory_Entry_Info
 *  Memory entry infomation
 *  @{
 */
#define NMC_MEM_ENTRY_NAME_SIZE             (128)
#define NMC_MEM_ENTRY_CLASS_DIO             (0)
#define NMC_MEM_ENTRY_CLASS_DATA            (1)
/*!
 *  @}
 */

//! Coordinate transform
#define NMC_MAX_POSE_DATA_SIZE              (6)

/*! \addtogroup Tool_Base
 *  Tool & Base
 *  @{
 */
#define NMC_TOOL_NONE                       (-1)
#define NMC_BASE_NONE                       (-1)
/*!
 *  @}
 */

/*! \addtogroup RCFG
 *  RCFG
 *  @{
 */
#define  RCFG_BIT0       0
#define  RCFG_BIT1       1
#define  RCFG_BIT2       2
#define  RCFG_SIZE       4
#define  RCFG_1          0
#define  RCFG_4          1
#define  RCFG_6          2
#define  RCFG_X          3
#define  RCFG_OPTION     10
#define  RCFG_INI        20
#define  RCFG_UNUSE      30
/*!
 *  @}
 */


/*! @struct Pos_T     NexMotionDef.h
 *  @brief  The general data types related to motion, which is defined in NexMotionDef.h
 *
 *  It is used to describe the coordinate position of group, and can be ACS
 *  coordinates or MCS/PCS coordinates depended on the definitions of API.
 */
typedef struct
{
    // For Cartesian space(MCS,PCS) : X, Y, Z, A, B, C, U, V
    // For Axis space(ACS): Axis 0 ~ 7
    /*! The pos[0~7] represents the coordinate axis 0~7 in the group for the ACS
     *  coordinate system, and it represents the X-axis, Y-axis, Z-axis, A-axis,
     *  B-axis, C-axis, U-axis, and V-axis for the Cartesian coordinate system
     *  (MCS/PCS).
     */
    F64_T pos[NMC_MAX_POS_SIZE];
} Pos_T;


/*! @struct Xyz_T     NexMotionDef.h
 *  @brief  The data types related to motion in Cartesian system,
 *          which is defined in NexMotionDef.h.
 *
 *  It is used to describe the X-axis, Y-axis and Z-axis of the Cartesian
 *  coordinate system.
 */
typedef struct
{
    // For Cartesian space(MCS,PCS) : X, Y, Z,
    /*! The pos[0], pos[1] and pos[2] represent the X-axis, Y-axis, and Z-axis
     *  of the Cartesian coordinate system, respectively.
     */
    F64_T pos[NMC_MAX_XYZ_SIZE];
} Xyz_T;


/*! @struct APos_T     NexMotionDef.h
 *  @brief  The data types related to motion in Axis system,
 *          which is defined in NexMotionDef.h.
 *
 *  It is used to describe the value of axes of the Machine coordinate system.
 */
typedef struct
{
    //! To describe a position in Axis space (ACS): Axis 0 ~ 7
    F64_T aPos[NMC_MAX_AXIS_POS_SIZE];
} APos_T;


/*! @struct CPos_T     NexMotionDef.h
 *  @brief  The data types related to pose in Cartesian space,
 *          which is defined in NexMotionDef.h.
 *
 *  It is used to describe the value of position & orientation of the Cartesian coordinate system.
 */
typedef struct
{
    //! To describe a position in Cartesian space(MCS,PCS) : X, Y, Z, A, B, C
    F64_T  cPos[NMC_MAX_CARTESIAN_POS_SIZE];
} CPos_T;

typedef struct
{
    I32_T rc1;
    I32_T rc2;
    I32_T rc3;
    I32_T rc4;
} RCfg_T;

typedef struct
{
    // To describe a position in Cartesian space(MCS,PCS) : X, Y, Z, A, B, C
    CPos_T  cPos;
    RCfg_T  rCfg;
} RCPos_T;

typedef struct
{
    // To describe the coordinate transformation between two coordinate systems: (x, y, z, roll, pitch, yaw)
    // (x,y,z) for translation, (r,p,y) for rotation
    F64_T pose[NMC_MAX_POSE_DATA_SIZE];
} CoordTrans_T;


/*!
 *  @brief  Hook function type definition.
 *  @param *FPFuncAddress The index of the called function.
 *  @param *PFuncName     The name of the called function.
 *  @param ReturnCode     The return value of the called function.
 *  @param *PUserData     The index of user data set by NMC_DebugSetHookData().
 *  @return None
 */
typedef void(*PF_NmcHookAPI)( const void *FPFuncAddress , const char *PFuncName, RTN_ERR ReturnCode, void *PUserData );

#pragma  pack(push, 1)
/*! @struct NmcTime_T     NexMotionDef.h
 *  @brief  A data structure is used to describe the system time.
 *
 */
typedef struct
{
    U32_T year;         //!<  1601 through 30827
    U32_T month;        //!<  1 through 12.
    U32_T day;          //!<  1 through 31.
    U32_T hour;         //!<  0 through 23.
    U32_T minute;       //!<  0 through 59.
    U32_T second;       //!<  0 through 59
    U32_T milliseconds; //!<  0 through 999
} NmcTime_T;


/*! @struct NmcMsg_T     NexMotionDef.h
 *  @brief  A data structure is used to describe the system message.
 *
 */
typedef struct
{
    U32_T       sizeOfStruct;   //!< The size of NmcMsg_T, and equivalent to the sizeof(NmcMsg_T).
    NmcTime_T   localTime;      //!< The system time recorded when the message is generated.
    U32_T       index;          //!< The index of message.
    I32_T       type;           //!< The type of message. 0: Normal, 1: Warning, 2: Error
    char        source[NMC_MAX_MSG_SOURCE_SIZE];  //!< The source of message (reserved).
    I32_T       id;             //!< The identification of message (reserved).
    I32_T       code;           //!< The code of message.
    char        text[NMC_MAX_MSG_TEXT_SIZE];  //!< The content of message.
} NmcMsg_T;
#pragma	pack(pop)


typedef struct
{
    U32_T bitStartOffset;
    U32_T bitLen;
    U32_T dataType;
    U32_T fclass;
    char  name[NMC_MEM_ENTRY_NAME_SIZE];
}MemEntryInfo_T;

/////////////////////////////////////////////////////////////////////
//                      Obsolete definition
/////////////////////////////////////////////////////////////////////
#define MAX_POS_SIZE                        (NMC_MAX_POS_SIZE)
#define MAX_XYZ_SIZE                        (NMC_MAX_XYZ_SIZE)

// Group axis index definition
#define GROUP_AXIS_X                        (0)
#define GROUP_AXIS_Y                        (1)
#define GROUP_AXIS_Z                        (2)
#define GROUP_AXIS_A                        (3)
#define GROUP_AXIS_B                        (4)
#define GROUP_AXIS_C                        (5)
#define GROUP_AXIS_U                        (6)
#define GROUP_AXIS_V                        (7)

// Group axis mask definition
#define GROUP_AXIS_MASK_X                   (0x00000001)
#define GROUP_AXIS_MASK_Y                   (0x00000002)
#define GROUP_AXIS_MASK_Z                   (0x00000004)
#define GROUP_AXIS_MASK_A                   (0x00000008)
#define GROUP_AXIS_MASK_B                   (0x00000010)
#define GROUP_AXIS_MASK_C                   (0x00000020)
#define GROUP_AXIS_MASK_U                   (0x00000040)
#define GROUP_AXIS_MASK_V                   (0x00000080)

#endif
