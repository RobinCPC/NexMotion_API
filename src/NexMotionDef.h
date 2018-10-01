#ifndef   __NEXMOTION_DEF_H
#define   __NEXMOTION_DEF_H

#include "nex_type.h"

// Device types. for NMC_DeviceOpenUp()
#define NMC_DEVICE_TYPE_SIMULATOR           (0)
#define NMC_DEVICE_TYPE_ETHERCAT            (1)

// Wati functions timeout
#define NMC_WAIT_TIME_INFINITE              (0xFFFFFFFF)

// State definition of devices. NMC_DeviceGetState()
#define NMC_DEVICE_STATE_INIT               (1)
#define NMC_DEVICE_STATE_READY              (2)
#define NMC_DEVICE_STATE_ERROR              (3)
#define NMC_DEVICE_STATE_OPERATION          (4)

// State definition of safety
#define NMC_SAFETY_STATE_DISABLE            (0)
#define NMC_SAFETY_STATE_READY              (1)
#define NMC_SAFETY_STATE_ERROR              (2)

// Safety operation mode definition.
#define NMC_SAFETY_MODE_OP_T1               (0)
#define NMC_SAFETY_MODE_OP_T2               (1)
#define NMC_SAFETY_MODE_OP_AUT              (2)

// Watch dog timeout mode
#define NMC_SAFETY_WDT_TIMEOUT_STOP0        (0)
#define NMC_SAFETY_WDT_TIMEOUT_STOP1        (1)

// Coordinate system type definition for group operation
#define NMC_COORD_MCS                       (0)  // (MCS) Mechanical also called base/world coord. system
#define NMC_COORD_PCS                       (1)  // (PCS) Programming also called product/work coord. system
#define NMC_COORD_ACS                       (2)  // (ACS) Axis coord. system

// State definition of axis.
#define NMC_AXIS_STATE_DISABLE              (0)
#define NMC_AXIS_STATE_STAND_STILL          (1)
#define NMC_AXIS_STATE_HOMING               (2)
#define NMC_AXIS_STATE_DISCRETE_MOTION      (3)
#define NMC_AXIS_STATE_CONTINUOUS_MOTION    (4)
#define NMC_AXIS_STATE_STOPPING             (5)
#define NMC_AXIS_STATE_STOPPED              (6)
#define NMC_AXIS_STATE_WAIT_SYNC            (7)
#define NMC_AXIS_STATE_GROUP_MOTION         (8)
#define NMC_AXIS_STATE_ERROR                (10)

// Status bit number definition of axis
#define NMC_AXIS_STATUS_EMG                 (0)
#define NMC_AXIS_STATUS_ALM                 (1)
#define NMC_AXIS_STATUS_PEL                 (2)
#define NMC_AXIS_STATUS_NEL                 (3)
#define NMC_AXIS_STATUS_PSEL                (4)
#define NMC_AXIS_STATUS_NSEL                (5)
#define NMC_AXIS_STATUS_ENA                 (6)
#define NMC_AXIS_STATUS_ERR                 (7)
#define NMC_AXIS_STATUS_TAR                 (8)
#define NMC_AXIS_STATUS_CSTP                (9)
#define NMC_AXIS_STATUS_ACC                 (10)
#define NMC_AXIS_STATUS_DEC                 (11)
#define NMC_AXIS_STATUS_MV                  (12)
#define NMC_AXIS_STATUS_OP                  (13)
#define NMC_AXIS_STATUS_STOP                (14)
#define NMC_AXIS_STATUS_RPEL	            (16)
#define NMC_AXIS_STATUS_RNEL	            (17)
#define NMC_AXIS_STATUS_RHOM	            (18)


// Status bit mask definition of axis         
#define NMC_AXIS_STATUS_MASK_EMG            (0x00000001) 
#define NMC_AXIS_STATUS_MASK_ALM            (0x00000002) 
#define NMC_AXIS_STATUS_MASK_PEL            (0x00000004) 
#define NMC_AXIS_STATUS_MASK_NEL            (0x00000008) 
#define NMC_AXIS_STATUS_MASK_PSEL           (0x00000010) 
#define NMC_AXIS_STATUS_MASK_NSEL           (0x00000020) 
#define NMC_AXIS_STATUS_MASK_ENA            (0x00000040) 
#define NMC_AXIS_STATUS_MASK_ERR            (0x00000080) 
#define NMC_AXIS_STATUS_MASK_TAR            (0x00000100) 
#define NMC_AXIS_STATUS_MASK_CSTP           (0x00000200) 
#define NMC_AXIS_STATUS_MASK_ACC            (0x00000400)
#define NMC_AXIS_STATUS_MASK_DEC            (0x00000800)
#define NMC_AXIS_STATUS_MASK_MV             (0x00001000)
#define NMC_AXIS_STATUS_MASK_OP             (0x00002000)
#define NMC_AXIS_STATUS_MASK_STOP           (0x00004000)
#define NMC_AXIS_STATUS_MASK_RPEL	        (0x00010000)
#define NMC_AXIS_STATUS_MASK_RNEL	        (0x00020000)
#define NMC_AXIS_STATUS_MASK_RHOM	        (0x00040000)

// State definition of group
#define NMC_GROUP_STATE_DISABLE             (0)
#define NMC_GROUP_STATE_STAND_STILL         (1)
#define NMC_GROUP_STATE_STOPPED             (2)
#define NMC_GROUP_STATE_STOPPING            (3)
#define NMC_GROUP_STATE_MOVING              (4)
#define NMC_GROUP_STATE_HOMING              (5)
#define NMC_GROUP_STATE_ERROR               (6)

// Status bit number definition of group
#define NMC_GROUP_STATUS_EMG                (0)
#define NMC_GROUP_STATUS_ALM                (1)
#define NMC_GROUP_STATUS_PEL                (2)
#define NMC_GROUP_STATUS_NEL                (3)
#define NMC_GROUP_STATUS_PSEL               (4)
#define NMC_GROUP_STATUS_NSEL               (5)
#define NMC_GROUP_STATUS_ENA                (6)
#define NMC_GROUP_STATUS_ERR                (7)
#define NMC_GROUP_STATUS_CSTP               (9)
#define NMC_GROUP_STATUS_ACC                (10)
#define NMC_GROUP_STATUS_DEC                (11)
#define NMC_GROUP_STATUS_MV                 (12)
#define NMC_GROUP_STATUS_OP                 (13)
#define NMC_GROUP_STATUS_STOP               (14)

// Status bit mask definition of group
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

// Group axis number definition
#define NMC_MAX_AXES_IN_GROUP               (8)

// Pos_T array size definition
#define NMC_MAX_POS_SIZE                    (8)

// Xyz_T array size definition
#define NMC_MAX_XYZ_SIZE                    (3)

// APos_T array size definition
#define NMC_MAX_AXIS_POS_SIZE               (NMC_MAX_AXES_IN_GROUP)

// CPos_T array size definition
#define NMC_MAX_CARTESIAN_POS_SIZE          (6)

// Group axis index definition
#define NMC_GROUP_AXIS_X                    (0)
#define NMC_GROUP_AXIS_Y                    (1)
#define NMC_GROUP_AXIS_Z                    (2)
#define NMC_GROUP_AXIS_A                    (3)
#define NMC_GROUP_AXIS_B                    (4)
#define NMC_GROUP_AXIS_C                    (5)
#define NMC_GROUP_AXIS_U                    (6)
#define NMC_GROUP_AXIS_V                    (7)

// Group axis mask definition
#define NMC_GROUP_AXIS_MASK_X               (0x00000001)
#define NMC_GROUP_AXIS_MASK_Y               (0x00000002)
#define NMC_GROUP_AXIS_MASK_Z               (0x00000004)
#define NMC_GROUP_AXIS_MASK_A               (0x00000008)
#define NMC_GROUP_AXIS_MASK_B               (0x00000010)
#define NMC_GROUP_AXIS_MASK_C               (0x00000020)
#define NMC_GROUP_AXIS_MASK_U               (0x00000040)
#define NMC_GROUP_AXIS_MASK_V               (0x00000080)
#define NMC_GROUP_AXIS_MASK_ALL             (0x000000FF)

// API Trace mode definition
#define NMC_TRACE_MODE_DISABLE              (0)
#define NMC_TRACE_MODE_ERROR                (1)
#define NMC_TRACE_MODE_ALL                  (2)

// Message type definition
#define NMC_MAX_MSG_SOURCE_SIZE             (128)
#define NMC_MAX_MSG_TEXT_SIZE               (1024)
#define NMC_MSG_TYPE_NORMAL                 (0)
#define NMC_MSG_TYPE_WARNING                (1)
#define NMC_MSG_TYPE_ERROR                  (2)
#define NMC_MSG_TYPE_DEBUGING               (3)

// Memory entry infomation
#define NMC_MEM_ENTRY_NAME_SIZE             (128)
#define NMC_MEM_ENTRY_CLASS_DIO             (0)
#define NMC_MEM_ENTRY_CLASS_DATA            (1)

// Coordinate transform
#define NMC_MAX_POSE_DATA_SIZE              (6)

// Tool & Base
#define NMC_TOOL_NONE                       (-1)
#define NMC_BASE_NONE                       (-1)

//RCFG
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

typedef struct
{
    // For Cartesian space(MCS,PCS) : X, Y, Z, A, B, C, U, V
    // For Axis space(ACS): Axis 0 ~ 7
    F64_T pos[NMC_MAX_POS_SIZE];
} Pos_T;

typedef struct
{
    // For Cartesian space(MCS,PCS) : X, Y, Z,
    F64_T pos[NMC_MAX_XYZ_SIZE];
} Xyz_T;

typedef struct
{
    // To describe a position in Axis space (ACS): Axis 0 ~ 7
    F64_T aPos[NMC_MAX_AXIS_POS_SIZE];
} APos_T;

typedef struct
{
    // To describe a position in Cartesian space(MCS,PCS) : X, Y, Z, A, B, C
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

// Hook function type definition
typedef void(*PF_NmcHookAPI)( const void *FPFuncAddress , const char *PFuncName, RTN_ERR ReturnCode, void *PUserData );

#pragma  pack(push, 1)
typedef struct
{
    U32_T year;         //  1601 through 30827
    U32_T month;        //  1 through 12.
    U32_T day;          //  1 through 31.
    U32_T hour;         //  0 through 23.
    U32_T minute;       //  0 through 59.
    U32_T second;       //  0 through 59
    U32_T milliseconds; //  0 through 999
} NmcTime_T;

typedef struct
{
    U32_T       sizeOfStruct;  // return sizeof( NmcMsg_T )
    NmcTime_T   localTime;
    U32_T       index;
    I32_T       type;    
    char        source[NMC_MAX_MSG_SOURCE_SIZE];
    I32_T       id;
    I32_T       code;
    char        text[NMC_MAX_MSG_TEXT_SIZE];
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
