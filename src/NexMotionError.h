/*!
 * @file        NexMotionError.h
 * @brief       A head file define all of error codes for NexMotion Library
 * @author      NexCOBOT, Inc.
 */

#ifndef   __NEXMOTION_ERRORS_H
#define   __NEXMOTION_ERRORS_H


/*! \addtogroup Error_code
 *  Error codes for all API output.
 *  @{
 */
//! The operation completed successfully.
#define ERR_NEXMOTION_SUCCESS                               (0)

//! The system cannot find the externel library.
#define ERR_NEXMOTION_EXTERNAL_LIBRARY_NOT_FOUND            (-1)

//! The system cannot find an API address when specified library is loading.
#define ERR_NEXMOTION_API_NOT_FOUND                         (-2)

//! The system cannot load the externel library.
#define ERR_NEXMOTION_LOAD_EXTERNAL_LIBRARY_FAILED          (-3)

//! The system cannot load the runtime library.
#define ERR_NEXMOTION_LOAD_RUNTIME_FAILED                   (-4)

//! The system cannot find the specified file.
#define ERR_NEXMOTION_FILE_NOT_FOUND                        (-5)

//! The system cannot open the specified file.
#define ERR_NEXMOTION_FILE_OPEN_FAILED                      (-6)

//! The system cannot load the specified file.
#define ERR_NEXMOTION_FILE_LOAD_FAILED                      (-7)

//! The format of the file is bad.
#define ERR_NEXMOTION_FILE_BAD_FORMAT                       (-8)

//! The file cannot be read.
#define ERR_NEXMOTION_FILE_READ_PROHIBIT                    (-9)

//! The file cannot be write.
#define ERR_NEXMOTION_FILE_WRITE_PROHIBIT                   (-10)

//! The version of the file is incompatible.
#define ERR_NEXMOTION_FILE_VERSION_INCOMPTIBLE              (-11)

//! The system cannot openup the runtime, system state error, check devices or network.
#define ERR_NEXMOTION_OPENUP_RUNTIME_FAILED                 (-12)

//! The version of the runtime is incompatible.
#define ERR_NEXMOTION_RUNTIME_VERSION_INCOMPTIBLE           (-13)

//! The version of the runtime (external runtime system) is incompatible.
#define ERR_NEXMOTION_EXTERNAL_RUNTIME_VERSION_INCOMPTIBLE  (-14)

//! The system resources is inefficient.
#define ERR_NEXMOTION_OUT_OF_SYSTEM_RESOURCES               (-15)

//! An external call or system call has made an error.
#define ERR_NEXMOTION_EXTERNAL_CALL_FAILED                  (-16)

//! The system cannot be accessed before initialization process.
#define ERR_NEXMOTION_SYSTEM_NOT_INITIALIZATION             (-21)

//! The system cannot be closed before clean up process.
#define ERR_NEXMOTION_SYSTEM_CLOSED_DENIED                  (-22)

//! In current state, the system cannot accept the operation.
#define ERR_NEXMOTION_OPERATION_DENIED                      (-23)

//! The user does not have permission.
#define ERR_NEXMOTION_PERMISSION_DENIED                     (-24)

//! The operation occurred unexpected exception.
#define ERR_NEXMOTION_UNEXPECTED_EXCEPTION                  (-25)

//! The system is not ready.
#define ERR_NEXMOTION_SYSTEM_NOT_READY                      (-26)

//! The system is busy and cannot accept the operation.
#define ERR_NEXMOTION_OPERATION_BUSY                        (-27)

//! The wait function has failed. No wait condition.
#define ERR_NEXMOTION_WAIT_FAILED                           (-28)

//! System perform current process is timeout.
#define ERR_NEXMOTION_PROCESS_TIMEOUT                       (-31)

//! Runtime module does not respond in a certain time.
#define ERR_NEXMOTION_RUNTIME_RESPONSE_TIMEOUT              (-32)

//! The system cannot find the object through specified [ID], [Index], or [Handle] etc.
#define ERR_NEXMOTION_OBJECT_ID_INVALID                     (-41)

//! The parameter number is invalid.
#define ERR_NEXMOTION_PARAMETER_NUMBER_INVALID              (-42)

//! The parameter value is invalid.
#define ERR_NEXMOTION_PARAMETER_VALUE_INVALID               (-43)

//! The parameter is read only.
#define ERR_NEXMOTION_PARAMETER_READ_ONLY                   (-44)

//! The operation attempted to access invalid area.
#define ERR_NEXMOTION_ACCESS_AREA_INVALID                   (-45)

//! The input pointer variable is null.
#define ERR_NEXMOTION_POINTER_NULL                          (-46)

//! The queue is empty.
#define ERR_NEXMOTION_QUEUE_EMPTY                           (-47)

//! The size of structure is incomptible.
#define ERR_NEXMOTION_STRUCT_SIZE_INCOMPTIBLE               (-48)

//! The initial position of an axis is out of limit.
#define ERR_NEXMOTION_INITIAL_AXIS_POSITION_INVALID         (-100)

//! Inverse kinematics process is failed.
#define ERR_NEXMOTION_INVERSE_KINEMATICS_FAILED             (-101)

//! The solution of inverse kinematics is out of limit.
#define ERR_NEXMOTION_INVERSE_KINEMATICS_OVER_AXIS_LIMIT    (-102)

//! The solution of inverse kinematics is singular.
#define ERR_NEXMOTION_INVERSE_KINEMATICS_SINGULAR           (-103)

//! The type of kinematics is invalid.
#define ERR_NEXMOTION_KINEMATICS_TYPE_INVALID               (-104)

//! The count of axis is invalid.
#define ERR_NEXMOTION_AXIS_COUNT_INVALID                    (-105)

//! The count of group is invalid.
#define ERR_NEXMOTION_GROUP_COUNT_INVALID                   (-106)

//! The map setting of the axis is invalid.
#define ERR_NEXMOTION_AXIS_MAPPING_INVALID                  (-107)

//! The kinematics parameter of a group is invalid.
#define ERR_NEXMOTION_KINEMATICS_PARAMETER_INVALID          (-108)

//! Emergency stop signal is detected.
#define ERR_NEXMOTION_EMERGENCY_STOP_ACTIVE                 (-109)

//! Enabling switch full pressed signal is detected.
#define ERR_NEXMOTION_ENABLE_SWITCH_FULL_PRESSED            (-110)

//! Safe-guard signal is detected.
#define ERR_NEXMOTION_SAFE_GUARD_ACTIVE                     (-111)

//! Safety error is detected.
#define ERR_NEXMOTION_SAFETY_ERROR                          (-112)

/*!
 *  @}
 */

#endif // #ifndef   __NEXMOTION_ERRORS_H
