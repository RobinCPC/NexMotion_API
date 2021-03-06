/*!
 * @file        NexMotion.h
 * @brief       A head file define API for NexMotion Library
 * @author      NexCOBOT, Inc.
 */
/******************************************************************************
  Open Robots & Machines
  (C) 2018 NEXCOBOT Co., Ltd. All Rights Reserved.
*******************************************************************************/
#ifndef __NEXMOTION_H
#define __NEXMOTION_H

/*!
 * @brief define marco FNTYPE as __stdcall
 */
#define FNTYPE  __stdcall

#ifdef __cplusplus
  extern "C" {
#endif

#include "NexMotionDef.h"


/*! \addtogroup System_API
 *  System APIs
 *  @{
 */
// Version and error read APIs
/*! \addtogroup Version_Error_Read
 *  Version and Error Information Functions
 *  @{
 */
/*!
 * @brief Return the version number of the Library: Major.Minor.Stage.Build
 *
 * @param[out] PRetMajor [Input] A pointer variable, [Output] The major version number. Input NULL(0) can ignore the parameter.
 * @param[out] PRetMinor [Input] A pointer variable, [Output] The minor version number. Input NULL(0) can ignore the parameter.
 * @param[out] PRetStage [Input] A pointer variable, [Output] The stage of version number. Input NULL(0) can ignore the parameter. The return value 1 to 4 indicate the trial versions, and the 5 indicates the official release version.
 * @param[out] PRetBuild [Input] A pointer variable, [Output] The build of version number. Input NULL(0) can ignore the parameter.
 *
 * @return The version number will be returned with the data type of I32_T. The return value means: Version = (Majorx10,000,000) + (Minorx100,000) + (Stagex10,000) + Build
 *
 * \b Examples:
 * @code{.h}
 * U32_T version;
 * I32_T major, minor, stage, build;
 * version = NMC_GetLibVersion( &major, &minor, &stage, &build );
 * printf( "Library version = %d, (%d,%d,%d,%d) \n", version, major, minor, stage, build );
 * @endcode
 */
I32_T   FNTYPE NMC_GetLibVersion( _opt_null_ I32_T *PRetMajor, _opt_null_ I32_T *PRetMinor, _opt_null_ I32_T *PRetStage, _opt_null_ I32_T *PRetBuild  );
/*!
 * @brief Return the version number of the Library in the format of a C string: Major.Minor.Stage.Build
 *
 * @param PRetVersionString A C string which is 32 characters at least
 * @param StringSize The size of the input C String
 *
 * @return  None
 *
 * \b Usage: <br>
 *
 * \b Examples:
 * @code{.h}
 * char versionString[32];
 * NMC_GetLibVersionString( versionString, 32 );
 * printf( "Library version = (%s) \n", versionString );
 * @endcode
 *
 * \b Reference: <br>
 *
 */
void    FNTYPE NMC_GetLibVersionString( char *PRetVersionString, U32_T StringSize );
/*!
 * @brief Return the error code description in the format of a C string.
 *
 * @param ErrorCode     The error code to be inquired
 * @param PRetErrorDesc A char array which is 512 characters at least
 * @param StringSize    The size of input char array
 *
 * @return The [error code](@ref Error_code) description. It will be NULL if the ErrorCode is undefined
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 *
 */
const char* FNTYPE NMC_GetErrorDescription( RTN_ERR ErrorCode, _opt_null_ char *PRetErrorDesc, U32_T StringSize );
/*!
 *  @}
 */


// Controller initialization APIs
/*! \addtogroup Device_Open_Shutdown
 *  Device Open up and Shut Down
 *  @{
 */
/*!
 * @brief Open up the device (Blocking call).
 *
 * @param      DevType The specified device type. 0: Simulator, 1: EtherCAT
 * @param      DevIndex The specified index of device which is set to 0
 * @param[out] PRetDevID [Output] The device ID (DevID) after the function is called successfully
 *
 * @return Return an [error code](@ref Error_code).
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h
 *
 * \b Usage: <br>
 *  NMC_DeviceOpenUp() can be called to control a device before the other control APIs are called. The function is a blocking call. It costs a short time to process the initialization, including the loading of configuration file, and returns after the device is in the operation state.
 *
 * \b Refence: <br>
 *  NMC_DeviceShutdown()
 */
RTN_ERR FNTYPE NMC_DeviceOpenUp( I32_T DevType, I32_T DevIndex, I32_T *PRetDevID );
/*!
 * @brief Shut down the device (Blocking call).
 *
 * @param DevID The device ID of the machine that request to be shutdown.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h
 *
 * \b Usage: <br>
 *  After the application is closed, the function shall be called to shut down the device and release system resources. After called, the function will block the application until the application is closed.
 *
 * \b Reference: <br>
 *  NMC_DeviceOpenUp()
 */
RTN_ERR FNTYPE NMC_DeviceShutdown( I32_T DevID );
/*!
 * @brief Request the device open up (Non-blocking call).
 *
 * @param DevType   The specified device type
 * @param DevIndex  The specified index of device which is set to 0
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function will return immediately after called. NMC_DeviceWaitOpenUpRequest() or NMC_DeviceGetState() shall be used to read the device state, in order to check if the device is in the operation state.
 *
 * \b Reference: <br>
 * NMC_DeviceWaitOpenUpRequest()
 */
RTN_ERR FNTYPE NMC_DeviceOpenUpRequest( I32_T DevType, I32_T DevIndex );
/*!
 * @brief Wait for device open up (Blocking call).
 *
 * @param      WaitMs    Waiting time for device open up (unit: ms). It can be set to the NMC_WAIT_TIME_INFINITE (0xFFFFFFFF) to wait for the completion of open up.
 * @param[out] PRetDevID [Output] The device ID (DevID) after the function is called successfully.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Generally, the function is used to check if the device open up is successful, and called after NMC_DeviceOpenUpRequest(). After called, the function will block the application until the device is in the operation or error state.
 *
 * \b Reference: <br>
 * NMC_DeviceOpenUpRequest()
 */
RTN_ERR FNTYPE NMC_DeviceWaitOpenUpRequest( U32_T WaitMs, I32_T *PRetDevID  );
/*!
 * @brief Request the device shut down (Non-blocking call).
 *
 * @param DevID The device ID of the machine that request to be shutdown.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 */
RTN_ERR FNTYPE NMC_DeviceShutdownRequest( I32_T DevID );
/*!
 * @brief Wait for device shut down (Blocking call).
 *
 * @param DevID   The device ID of the machine that request to be shutdown.
 * @param WaitMs  Waiting time for device open up (unit: ms). It can be set to the NMC_WAIT_TIME_INFINITE (0xFFFFFFFF) to wait for the completion of open up.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Generally, the function is used to check if the device shut down is successful, and called after NMC_DeviceShutdownRequest(). After called, the function will block the application until the device is in the operation or error state.
 *
 * \b Reference: <br>
 * NMC_DeviceShutdownRequest()
 */
RTN_ERR FNTYPE NMC_DeviceWaitShutdownRequest( I32_T DevID, U32_T WaitMs );
/*!
 *  @}
 */

// Watchdog APIs
/*! \addtogroup Watch_Dog_Functions
 *  Functions for watch dog feature
 *  @{
 */
/*!
 * @brief Enable the watch dog timer.
 *
 * @param DevID     Device ID (DevID)
 * @param TimeoutMs Timeout value for the watch dog timer. Unit: milliseconds. Range: 20 to 200000 ms.
 * @param Mode      Time out mode. 0: Device will transfer to ready state if the device in the operation state.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section, [Watch Dog Timer](@ref WatchDogTimer)
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceWatchdogTimerEnable( I32_T DevID, U32_T TimeoutMs, I32_T Mode );
/*!
 * @brief Disable the watch dog timer.
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section, [Watch Dog Timer](@ref WatchDogTimer)
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceWatchdogTimerDisable( I32_T DevID );
/*!
 * @brief Reset the watch dog timer.
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section, [Watch Dog Timer](@ref WatchDogTimer)
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceWatchdogTimerReset( I32_T DevID );
/*!
 *  @}
 */

// Advanced controller initialization APIs
/*! \addtogroup Advanced_Device_Open_Shutdown
 *  Advanced Device Open up and Shut Down
 *  @{
 */
/*!
 * @brief Create the device ID.
 *
 * @param      DevType   The specified device type. 0: Simulator, 1: EtherCAT.
 * @param      DevIndex  The specified index of device which is set to 0.
 * @param[out] PRetDevID [Output] The device ID (DevID) after the function is called successfully.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section, Advanced System Initializeation.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceCreate( I32_T DevType, I32_T DevIndex, I32_T *PRetDevID );
/*!
 * @brief Delete the device ID.
 *
 * @param DevID     Device ID
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section, Advanced System Initializeation.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceDelete( I32_T DevID );
/*!
 * @brief Load the device configurations
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function will load the device configurations in accordance with the file, `NexMotionLibConfig.ini`.
 * The file, `NexMotionLibConfig.ini`, is saved in the default path, `C:\\NEXCOBOT`. Users must not create the file, nor modify the file name or content in order to avoid the loading error. NMC_DeviceLoadIniConfig() will search the file, `NexMotionLibConfig.ini`, in the following path in order:
 * ```
 * NexMotion.dll folder
 * C:\\NEXCOBOT
 * C:\\Windows\System32
 * ```
 * To specify a new path for the file, `NexMotionLibConfig.ini`, NMC_SetIniPath() can be called.
 * After NMC_DeviceLoadIniConfig() is called successfully, the device is in the ready state and ready to start.
 *
 * \b Reference: <br>
 * NMC_SetIniPath()
 */
RTN_ERR FNTYPE NMC_DeviceLoadIniConfig( I32_T DevID );
/*!
 * @brief Reset the device configurations.
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * NMC_DeviceResetConfig() is used to reset the device configurations. After the function is called successfully, the device will return to the init state. If the device is in the operation state, the fuction shall not be called.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceResetConfig( I32_T DevID );
/*!
 * @brief Start the device (Blocking call).
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * If the device is in the ready state, the function can be called to start the device. After the function is called and returned successfully, the device is in operation state.
 * Please refer to the section, Advanced System Initialization.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceStart( I32_T DevID );
/*!
 * @brief Stop the device (Blocking call).
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * If the device is in the operation state, the function can be called to stop the device. After the function is called and returned successfully, the device is in ready state.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceStop( I32_T DevID );
/*!
 * @brief Request the device start (Non-blocking call).
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * If the device is in the ready state, the function can be called to send the request for device start, and the function will be returned immediately. NMC_DeviceGetState(), can be used to used to read the device state, in order to check if the device is not in the operation state.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceStartRequest( I32_T DevID );
/*!
 * @brief Request the device stop (Non-blocking call).
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * If the device is in the operation state, the function can be called to send the request for device stop, and the function will be returned immediately. NMC_DeviceGetState(), can be used to used to read the device state, in order to check if the device is not in the ready state.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceStopRequest( I32_T DevID );
/*!
 * @brief Get the device state.
 *
 * @param DevID           Device ID (DevID)
 * @param PRetDeviceState Return the state of the device after called successfully.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceGetState( I32_T DevID, I32_T *PRetDeviceState );
/*!
 *  @}
 */

// System parameter setting APIs
/*! \addtogroup System_Config
 *  System Configuration Functions
 *  @{
 */
/*!
 * @brief Set device parameters.
 *
 * @param DevID     Device ID (DevID)
 * @param ParamNum  Parameter Number
 * @param SubIndex  Parameter Sub-index
 * @param ParaValue Value to be set
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section, System Parameters.
 *
 * \b Reference: <br>
 * Please refer to the section, System Parameters.
 */
RTN_ERR FNTYPE NMC_DeviceSetParam( I32_T DevID, I32_T ParamNum, I32_T SubIndex, I32_T ParaValue );
/*!
 * @brief Get device parameters.
 *
 * @param      DevID         Device ID (DevID)
 * @param      ParamNum      Parameter Number
 * @param      SubIndex      Parameter Sub-index
 * @param[out] PRetParaValue [Output] The value to be returned after the function is called successfully.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section, System Parameters.
 *
 * \b Reference: <br>
 * Please refer to the section, System Parameters.
 */
RTN_ERR FNTYPE NMC_DeviceGetParam( I32_T DevID, I32_T ParamNum, I32_T SubIndex, I32_T *PRetParaValue );
/*!
 * @brief Set the path of the ini file.
 *
 * @param PIniPath  The ini file to be set. it shall be a C string, and can be set to NULL(0) to reset the path to the default value.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * During the starting, the system will load the configurations in accordance with the file, NexMotionLibConfig.ini. Also, the function can be called to specify the ini file path. The default path is `C:\NEXCOM\`.
 *
 * \b Reference: <br>
 * NMC_DeviceOpenUp() and NMC_DeviceOpenUpRequest()
 */
RTN_ERR FNTYPE NMC_SetIniPath( _opt_null_ const char *PIniPath );
/*!
 *  @}
 */

// I/O access APIs
/*! \addtogroup IO_Control_Functions
 *  I/O Control Functions
 *  @{
 */
/*!
 * @brief Get the size of mapped input(Input) memory.
 *
 * @param DevID         Device ID (DevID)
 * @param PRetSizeByte  The size of I/O output memory will be returned after the function is called successfully. Unit: byte.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * NMC_GetInputMemorySize() is used to read the accessible range of the I/O memory in the controller (0 to the return size, in bytes). Different controllers (different models) may have different I/O memory sizes that can be controlled,
 * so this API can be used to confirm the actual reachable range.
 *
 * The function can be called after the device is started.
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 *
 */
RTN_ERR FNTYPE NMC_GetInputMemorySize ( I32_T DevID, U32_T *PRetSizeByte );
/*!
 * @brief Get the size of mapped output (Output) memory.
 *
 * @param DevID         Device ID (DevID)
 * @param PRetSizeByte  The size of I/O output memory will be returned after the function is called successfully. Unit: byte.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * NMC_GetOutputMemorySize () is used to read the accessible range of the I/O memory in the controller (0 to the return size, in bytes). Different controllers (different models) may have different I/O memory sizes that can be controlled,
 * so this API can be used to confirm the actual reachable range.
 *
 * The function can be called after the device is started.
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 *
 */
RTN_ERR FNTYPE NMC_GetOutputMemorySize( I32_T DevID, U32_T *PRetSizeByte );
/*!
 * @brief Read the mapped input (Input) memory.
 *
 * @param DevID       Device ID (DEVID)
 * @param OffsetByte  Memory offset (byte) from 0.
 * @param SizeByte    Size of the memory to be read.
 * @param PRetValue   The contents within the specified memory segment will be saved into the variable after the function is called successfully.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the [I/O Control](@ref IO_Control) chapter for information on how to map I/O to the controller's internal I/O memory.
 * This function can be called after the controller is started.
 * Suppose an I/O device sets its DI-0 to DI-15 to the first Byte and the second Byte of the I/O Input memory.
 * I want to read the value of the fourth DI input (DI-3). Please refer to the following example
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret;
 * U32_T offsetByte = 0;
 * U32_T sizeByte = 2;
 * U16_T diValue = 0;
 * U16_T di_03;
 *
 * ret = NMC_ReadInputMemory( devId, offsetByte, sizeByte, &diValue );
 * di_03 = ( diValue >> 3 ) & 1;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_ReadInputMemory( I32_T DevID, U32_T OffsetByte, U32_T SizeByte, void *PRetValue );
/*!
 * @brief Read the mapped output (Output) memory
 *
 * @param DevID       Device ID (DevID)
 * @param OffsetByte  Memory offset (byte) from 0.
 * @param SizeByte    Size of the memory to be read.
 * @param PRetValue   The contents within the specified memory segment will be saved into the variable after the function is called successfully.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the [I/O Control](@ref IO_Control) chapter for information on how to map I/O to the controller's internal I/O memory.
 * This function can be called after the controller is started.
 * Suppose an I/O device sets its DO-0 to DO-15 to the first Byte and the second Byte of the I/O output memory.
 * I want to read the value of the fourth DO output (DO-3). Please refer to the following example:
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret;
 * U32_T offsetByte = 0;
 * U32_T sizeByte = 2;
 * U16_T doValue = 0;
 * U16_T do_03;
 * ret = NMC_ReadOutputMemory( devId, offsetByte, sizeByte, &doValue );
 * do_03 = ( doValue >> 3 ) & 1;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_ReadOutputMemory( I32_T DevID, U32_T OffsetByte, U32_T SizeByte, void *PRetValue );
/*!
 * @brief Write the mapped output (Output) memory.
 *
 * @param DevID       Device ID (DevID)
 * @param OffsetByte  Memory offset (byte) from 0.
 * @param SizeByte    Size of the memory to be read.
 * @param PValue      set the value into output memory
 *
 * @todo Update the description of PValue
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the [I/O Control](@ref IO_Control) chapter for information on how to map I/O to the controller's internal I/O memory.
 * This function can be called after the controller is started.
 * Suppose an I/O device has its DO-0 to DO-15 set to the first Byte and the second Byte of the I/O output memory.
 * I want to set the value of the fourth output point (DO 3). Refer to the following example:
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret;
 * U32_T offsetByte = 0;
 * U32_T sizeByte = 2;
 * U16_T doValue = 0;
 * U16_T do_03;
 * NMC_ReadOutputMemory( devId, offsetByte, sizeByte, &doValue );
 * doValue = doValue | ( ( 1 << 3 ) ); // Set bit 3 ON
 * //doValue = doValue & (~( 1 << 3 ) ); // Set bit 3 OFF
 * NMC_WriteOutputMemory( devId, offsetByte, sizeByte, &doValue );
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_WriteOutputMemory( I32_T DevID, U32_T OffsetByte, U32_T SizeByte, const void *PValue );
/*!
 * @brief Read the mapped input memory by bit, word or dword.
 *
 * @param DevID         Device ID (DevID)
 * @param OffsetByte    Memory offset (byte) from 0
 * @param BitIndex      Bit index in a byte, value must be 0~7
 * @param[out] PRetBitValue  Return bit value (0 or 1)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called after the device is started.
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_ReadInputBit( I32_T DevID, U32_T OffsetByte, U32_T BitIndex, BOOL_T *PRetBitValue );
RTN_ERR FNTYPE NMC_ReadInputI8( I32_T DevID, U32_T OffsetByte, I8_T *PRetI8Value );
RTN_ERR FNTYPE NMC_ReadInputI16( I32_T DevID, U32_T OffsetByte, I16_T *PRetI16Value );
RTN_ERR FNTYPE NMC_ReadInputI32( I32_T DevID, U32_T OffsetByte, I32_T *PRetI32Value );
/*!
 * @brief Read the mapped output memory by bit, word or dword.
 *
 * @param DevID         Device ID (DevID)
 * @param OffsetByte    Memory offset (byte) from 0
 * @param BitIndex      Bit index in a byte, value must be 0~7
 * @param[out] PRetBitValue  Return bit value (0 or 1)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called after the device is started.
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_ReadOutputBit( I32_T DevID, U32_T OffsetByte, U32_T BitIndex, BOOL_T *PRetBitValue );
RTN_ERR FNTYPE NMC_ReadOutputI8( I32_T DevID, U32_T OffsetByte, I8_T *PRetI8Value );
RTN_ERR FNTYPE NMC_ReadOutputI16( I32_T DevID, U32_T OffsetByte, I16_T *PRetI16Value );
RTN_ERR FNTYPE NMC_ReadOutputI32( I32_T DevID, U32_T OffsetByte, I32_T *PRetI32Value );
/*!
 * @brief Write the mapped output memory by bit, word or dword.
 *
 * @param DevID       Device ID (DevID)
 * @param OffsetByte  Memory offset (byte) from 0
 * @param BitIndex    Bit index in a byte, value must be 0~7
 * @param BitValue    Bit value (0 or 1) to be set
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called after the device is started.
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_WriteOutputBit( I32_T DevID, U32_T OffsetByte, U32_T BitIndex, BOOL_T BitValue );
RTN_ERR FNTYPE NMC_WriteOutputI8( I32_T DevID, U32_T OffsetByte, I8_T I8Value );
RTN_ERR FNTYPE NMC_WriteOutputI16( I32_T DevID, U32_T OffsetByte, I16_T I16Value );
RTN_ERR FNTYPE NMC_WriteOutputI32( I32_T DevID, U32_T OffsetByte, I32_T I32Value );
/*!
 *  @}
 */

// Read axis/group number APIs
/*! \addtogroup Axis_Group_Quantity
 *  Read Axis or Group Quantity
 *  @{
 */
/*!
 * @brief Get the axis quantity.
 *
 * @param DevID         Device ID (DevID)
 * @param PRetAxisCount The quantity of axis started will be returned after the function is called successfully.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * After the configuration file is loaded, the function can be called to confirm the quantity of axis started. After NMC_DeviceResetConfig() is called to reset the device configurations, the quantity of axis is 0.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceGetAxisCount( I32_T DevID, I32_T *PRetAxisCount );
/*!
 * @brief Get the quantity of group.
 *
 * @param DevID           Device ID (DevID)
 * @param PRetGroupCount  The quantity of group started will be returned after the function is called successfully.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * After the configuration file is loaded, the function can be called to confirm the quantity of group started. After NMC_DeviceResetConfig() is called to reset the device configurations, the quantity of group is 0.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceGetGroupCount( I32_T DevID, I32_T *PRetGroupCount );
/*!
 * @brief Get the quantity of group axis.
 *
 * @param DevID               Device ID (DevID)
 * @param GroupIndex          Group Index
 * @param PRetGroupAxisCount  The quantity of group axis will be returned after the function is called successfully.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * After the configuration file is loaded, the function can be called to confirm the actual quantity of group axis.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceGetGroupAxisCount( I32_T DevID, I32_T GroupIndex, I32_T *PRetGroupAxisCount );
/*!
 *  @}
 */

// Read axis/group description APIs
/*! \addtogroup Axis_Group_Description
 *  Read Axis or Group Description
 *  @{
 */
/*!
 * @brief Read the name description information of the specified axis
 *
 * @param DevID               Device ID (DevID)
 * @param AxisIndex           The specified axis index to be read from
 * @param DescStrSize         C-style string buff size, in byte
 * @param PRetAxisDescription Given C-style string buff and return description
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * This function is used to read the name description of the specified axis. The information source is based on the NCF file loaded byh the system, so it must be loaded before it can be read normally. In other words, the system state must be in READY state.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_AxisGetDescription( I32_T DevID, I32_T AxisIndex, U32_T DescStrSize, char *PRetAxisDescription );
/*!
 * @brief Read the name desciption information of the specified group
 *
 * @param DevID                 Device ID (DevID)
 * @param GroupIndex            The specified group index to be read from
 * @param DescStrSize           C-style string buff size, in byte
 * @param PRetGroupDescription  Given C-style string buff and return description
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * This function is used to read the name description of the specified group. The information source is based on the NCF file loaded byh the system, so it must be loaded before it can be read normally. In other words, the system state must be in READY state.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupGetDescription( I32_T DevID, I32_T GroupIndex, U32_T DescStrSize, char *PRetGroupDescription );
/*!
 *  @}
 */

// All axes and groups enable/disable APIs
/*! \addtogroup Device_Enable_Disable
 *  Enable and Disable Functions for All Axes and Groups
 *  @todo Add description for NMC_DeviceResetStateAll (empty in official pdf manual).
 *  @{
 */
RTN_ERR FNTYPE NMC_DeviceResetStateAll( I32_T DevID );
/*!
 * @brief Enable all axes and groups in the system.
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called after the device is started.
 * After the function is called, all axes and groups will be enabled (servo on). The start procedure will enable all axes and then all groups in order. The procedure will stop for any failure and return the error immediately.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceEnableAll( I32_T DevID );
/*!
 * @brief Disable all axes and groups in the system.
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called after the device is started.
 * After the function is called, all axes and groups will be disabled (servo off). The stop procedure will disable all axes and then all groups in order. The procedure will stop for any failure and return the error immediately.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceDisableAll( I32_T DevID );
/*!
 *  @}
 */

// All axes and groups motion termination APIs
/*! \addtogroup Device_Motion_Termination
 *  Halt and Stop Functions for All Axes and Groups
 *  @{
 */
/*!
 * @brief Holt all axes and groups in the system (Stand still state).
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called after the device is started.
 * After the function is called, all axes and groups will be halted. The halt procedure will halt all axes and then all groups in order. The procedure will stop for any failure and return the error immediately.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceHaltAll( I32_T DevID );
/*!
 * @brief Stop all axes and groups in the system (Stopped state).
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called after the device is started.
 * After the function is called, all axes and groups will be stopped. The stop procedure will stop all axes and then all groups in order. The procedure will stop for any failure and return the error immediately.
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_DeviceStopAll( I32_T DevID );
/*!
 *  @}
 */
/*!
 *  @}
 */


/*! \addtogroup Axis_API
 *  Axis APIs
 *  @todo Add description to NMC_AxisSetSpeedRatio, NMC_AxisGetSpeedRatio
 *  @{
 */
// Axis parameter setting APIs
/*! \addtogroup Axis_Config
 *  Axis Configuration Functions
 *  @{
 */
/*!
 * @brief Set the axis parameters (I_32T data type)
 *
 * @param DevID             Device ID (DevID)
 * @param AxisIndex         Axis index
 * @param ParamNum          Parameter number
 * @param SubIndex          Parameter Sub-index
 * @param[in] ParaValueI32  [Input] Value to be set (siged integer)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section: [Axis Parameters](@ref AxisParameters).
 * The device will load the configurations in according with the configuration file during starting. The
 * function can be used to set some axis parameters. A suitable function shall be selected depended
 * on the data type of the parameters (I32_T).
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * Please refer to the section: [Axis Parameters](@ref AxisParameters).
 */
RTN_ERR FNTYPE NMC_AxisSetParamI32( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, I32_T ParaValueI32 );
/*!
 * @brief Get the axis parameters (I_32T data type)
 *
 * @param DevID                 Device ID (DevID)
 * @param AxisIndex             Axis index
 * @param ParamNum              Parameter number
 * @param SubIndex              Parameter Sub-index
 * @param[out] PRetParaValueI32 [Output] Value to be returned (signed integer)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section: [Axis Parameters](@ref AxisParameters).
 * The device will load the configurations in according with the configuration file during starting. The
 * function can be used to get some axis parameters. A suitable function shall be selected depended
 * on the data type of the parameters (I32_T).
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * Please refer to the section: [Axis Parameters](@ref AxisParameters).
 */
RTN_ERR FNTYPE NMC_AxisGetParamI32( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, I32_T *PRetParaValueI32 );
/*!
 * @brief Set the axis patameters (F64_T data type)
 *
 * @param DevID             Device ID (DevID)
 * @param AxisIndex         Axis index
 * @param ParamNum          Parameter number
 * @param SubIndex          Parameter Sub-index
 * @param[in] ParaValueF64  [Input] Value to be set (double precision float)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section: [Axis Parameters](@ref AxisParameters).
 * The device will load the configurations in according with the configuration file during starting. The
 * function can be used to set some axis parameters. A suitable function shall be selected depended
 * on the data type of the parameters (F64_T).
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * Please refer to the section: [Axis Parameters](@ref AxisParameters).
 */
RTN_ERR FNTYPE NMC_AxisSetParamF64( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, F64_T ParaValueF64 );
/*!
 * @brief Get the axis parameters (F64_T data type)
 *
 * @param DevID                 Device ID (DevID)
 * @param AxisIndex             Axis index
 * @param ParamNum              Parameter number
 * @param SubIndex              Parameter Sub-index
 * @param[out] PRetParaValueF64 [Output] Value to be returned (double precision float)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Please refer to the section: [Axis Parameters](@ref AxisParameters).
 * The device will load the configurations in according with the configuration file during starting. The
 * function can be used to get some axis parameters. A suitable function shall be selected depended
 * on the data type of the parameters (F64_T).
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * Please refer to the section: [Axis Parameters](@ref AxisParameters).
 */
RTN_ERR FNTYPE NMC_AxisGetParamF64( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, F64_T *PRetParaValueF64 );
/*!
 *  @}
 */

// Axis state control APIs
/*! \addtogroup Axis_State_Control
 *  Axis State Control Functions
 *  @{
 */
/*!
 * @brief Enable an axis.
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. Before the axis motion, the function shall be called to drive the axis into the excitation.
 * 2. After the axis is excitation, the function will return successfully.
 * 3. If the axis is in the error state, the function will return the error code. After the error is resolved and the NMC_AxisResetState() is called, the function can be called to drive the axis into the excitation again.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * ret = NMC_AxisEnable(0, 0);
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisDisable(), NMC_AxisGetState(), and NMC_AxisResetState()
 */
RTN_ERR FNTYPE NMC_AxisEnable( I32_T DevID, I32_T AxisIndex );
/*!
 * @brief Disable an axis.
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * ret = NMC_AxisDisable(0, 0);
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisEnable() and NMC_AxisGetState()
 */
RTN_ERR FNTYPE NMC_AxisDisable( I32_T DevID, I32_T AxisIndex );
/*!
 * @brief Get the status of the axis
 *
 * @param DevID           Device ID (DevID)
 * @param AxisIndex       Axis Index
 * @param PRetAxisStatus  Return the axis status
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0; I32_T status = 0;
 * ret = NMC_AxisGetStatus( 0, 0, &status );
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisGetState()
 */
RTN_ERR FNTYPE NMC_AxisGetStatus( I32_T DevID, I32_T AxisIndex, I32_T *PRetAxisStatus );
/*!
 * @brief Get the state of the axis
 *
 * @param DevID         Device ID (DevID)
 * @param AxisIndex     Axis Index
 * @param PRetAxisState Return the axis state.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. The function can be called in a periodic procedure to confirm the current axis state.
 * 2. Before being in motion or executing the Homing procedure, the axis shall be excitation. After NMC_AxisEnable() is called, NMC_AxisGetState() can be called to confirm the axis is excitation.
 * 3. If the axis is in the error state or not stopped normally, and NMC_AxisResetState() is called, NMC_AxisGetState() can be called to confirm the axis error state is resolved.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * I32_T state = 0;
 * ret = NMC_AxisGetState( 0, 0, &state );
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisGetStatus()
 * NMC_AxisEnable()
 * NMC_AxisResetState()
 */
RTN_ERR FNTYPE NMC_AxisGetState( I32_T DevID, I32_T AxisIndex, I32_T *PRetAxisState );
/*!
 * @brief Reset the state of the axis.
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis Index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. If an axis is in the error state, or an aix is requested with a forced stop command and has stopped, the function can be called to reset the axis to the nonexcitation state or the normal excitation state. NMC_AxisGetState() can be called to confirm the axis is normal.
 * 2. If the axis drive is in the alarm state and the function is called, the device will reset the alarm automatically. After the error is resolved, the axis state will trafer to the nonexcitation state from the error state (AXIS_STATE_ERROR).
 * 3. If an axis is requested with a forced stop command and has stopped, the function can be called to reset the axis to nonexcitation state (AXIS_STATE_STAND_STILL).
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * ret = NMC_AxisResetState( 0, 0 );
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisGetState()
 * NMC_AxisResetDriveAlm()
 */
RTN_ERR FNTYPE NMC_AxisResetState( I32_T DevID, I32_T AxisIndex );
/*!
 * @brief Reset the axis servo alarm.
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex The index of the axis will be reset.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. When an alarm of axis drive is issued, the drive will automatically release the excitation in general. After the error is resolved, the function can be called to reset the alarm, and NMC_AxisGetStatus() can be called to get the axis status for the confirmation of alarm reset.
 * 2. Unless all drive alarms can be reseted with the function, some drive alarms shall be reseted by means of reengerization.
 * 3. After the function is called to reset the drive alarms successfully, the axis state can not be reset from the error state, unless NMC_AxisResetState() is called to reset the axis to the nonexcitation (AXIS_STATE_DISABLE).
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * ret = NMC_AxisResetDriveAlm( 0, 0 );
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisGetStatus()
 * NMC_AxisResetState()
 */
RTN_ERR FNTYPE NMC_AxisResetDriveAlm( I32_T DevID, I32_T AxisIndex );
/*!
 * @brief Get the axis servo alarm code.
 *
 * @param DevID       Device ID (DevID)
 * @param AxisIndex   Axis index
 * @param[out] PRetAlmCode [Output] The value of alarm code.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * NMC_AxisGetStatus(), NMC_AxisResetState()
 */
RTN_ERR FNTYPE NMC_AxisGetDriveAlmCode( I32_T DevID, I32_T AxisIndex, I32_T *PRetAlmCode );
/*!
 *  @}
 */

// Axis motion profile read APIs
/*! \addtogroup Axis_Motion_Status
 *  Axis Motion Status Functions
 *  @{
 */
/*!
 * @brief Get the command position for desired axis.
 *
 * @param DevID           Device ID (DevID)
 * @param AxisIndex       Axis index
 * @param[out] PRetCmdPos Return the command position. Unit: user unit.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called to get the command position for an axis.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * F64_T cmdPos = 0.0;
 * F64_T actPos = 0.0;
 * ret = NMC_AxisGetCommandPos( 0, 0, &cmdPos );
 * ret = NMC_AxisGetActualPos( 0, 0, &actPos );
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_AxisGetCommandPos( I32_T DevID, I32_T AxisIndex, F64_T *PRetCmdPos );
/*!
 * @brief Get the encoder feedback position for desired axis.
 *
 * @param DevID           Device ID (DevID)
 * @param AxisIndex       Axis index
 * @param[out] PRetActPos Return the encoder feedback position. Unit: user unit.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called to get the encoder feedback position for an axis.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * F64_T cmdPos = 0.0;
 * F64_T actPos = 0.0;
 * ret = NMC_AxisGetCommandPos( 0, 0, &cmdPos );
 * ret = NMC_AxisGetActualPos( 0, 0, &actPos );
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_AxisGetActualPos( I32_T DevID, I32_T AxisIndex, F64_T *PRetActPos );
/*!
 * @brief Get the command velocity for desired axis.
 *
 * @param DevID           Device ID (DevID)
 * @param AxisIndex       Axis index
 * @param[out] PRetCmdVel Return the command velocity. Unit: user unit/sec.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called to get the command velocity for an axis.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * F64_T cmdVel = 0.0;
 * F64_T actVel = 0.0;
 * ret = NMC_AxisGetCommandVel( 0, 0, &cmdVel );
 * ret = NMC_AxisGetActualVel( 0, 0, &actVel );
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_AxisGetCommandVel( I32_T DevID, I32_T AxisIndex, F64_T *PRetCmdVel );
/*!
 * @brief Get the encoder feedback velocity for desired axis.
 *
 * @param DevID           Device ID (DevID)
 * @param AxisIndex       Axis index
 * @param[out] PRetActVel Return the encoder feedback velocity. Unit: user unit/sec.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function can be called to get the encoder feedback velocity for an axis.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * F64_T cmdVel = 0.0;
 * F64_T actVel = 0.0;
 * ret = NMC_AxisGetCommandVel( 0, 0, &cmdVel );
 * ret = NMC_AxisGetActualVel( 0, 0, &actVel );
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_AxisGetActualVel( I32_T DevID, I32_T AxisIndex, F64_T *PRetActVel );
/*!
 * @brief Get the quantity of motions segment which can still be stored into the axis motion queue.
 *
 * @param DevID               Device ID (DevID)
 * @param AxisIndex           Axis index
 * @param[out] PRetFreeSpace  Return the quantity of motions which can still be stored into the axis motion queue.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * Because the axis supports the motion queue , the function can be called to confirm the quantity of motions which can still be stored into the axis motion queue.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * I32_T space = 0;
 * ret = NMC_AxisGetMotionBuffSpace( 0, 0, &space );
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisPtp()
 * NMC_AxisJog()
 * NMC_AxisHalt()
 */
RTN_ERR FNTYPE NMC_AxisGetMotionBuffSpace(  I32_T DevID, I32_T AxisIndex, I32_T *PRetFreeSpace );
/*!
 *  @}
 */

// Axis motion control APIs
/*! \addtogroup Axis_Motion_Control
 *  Axis Motion Control Functions
 *  @{
 */
/*!
 * @brief Execute Point-To-Point Motion according with target position.
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis index
 * @param TargetPos Taget Position (Unit: user unit). The value will be interpreted to absolute or relative distance based on the axis parameter `0x30` (absolute or relative programming).
 * @param PMaxVel   Input the target velocity with a pointer variable. Moreover, input 0 directly for no target velocity, and the driver can plan the motion based on the velocity configuratio of the axis parameter `AXP_VM`.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. The function can be called for point-to-point motion if the axis is excitation.
 * 2. If the axis is homing, the function will return the error code.
 * 3. If the axis is in the [axis state](@ref NMC_AxisGetState) AXIS_STATE_STOPPING, AXIS_STATE_STOPPED or AXIS_STATE_ERROR, the function will return the error code. After NMC_AxisResetState() is called to reset the axis to normal excitation (AXIS_STATE_STAND_STILL), the function can be called for point-to-point motion successfully.
 * 4. If the axis is executing other motions, it will execute the corresponding behavior depended on the axis parameter AXP_BUFF_PARAM after the function is called.
 * 5. The function can be called to enable the point-to-point motion. After the motion completely, the axis will move to the input target position. If the axis parameter 0x30 (Absolute or relative programming) is set to 1, the target position and the relative distance from the current position shall be input in the function. If the relative distance is set to 0, the target position will be set as an absolute position.
 * 6. If the axis is excuting the point-to-point motion, the [axis state](@ref NMC_AxisGetState) will transfer to AXIS_STATE_DISCRETE_MOTION. After the axis moves to the target position and there is no successive motion, the bit 9 of axis status will become to 1, and the axis will transfer to the normal excitation (AXIS_STATE_STAND_STILL).
 * 7. The drive will plan the velocity curve depended on the axis parameters, AXP_PROF_TYPE, AXP_ACC, AXP_DEC and AXP_JERK.
 * 8. The maximum velocity can be input with the pointer variable, PMaxVel. Then the corresponding axis parameter AXP_VM will be modified to the input value, and the velocity plan will be performed accordingly.
 * 9. If the pointer variable, PMaxVel, is set to 0, the drive will perform the velocity plan based on the axis parameter AXP_VM as the target velocity.
 * 10. If the [axis state](@ref NMC_AxisGetState) is AXIS_STATE_STAND_STILL, the function will enable the point-to-point motion immediately after called whether the content of axis parameter AXP_BUFF_PARAM.
 * 11. After the function is called and if the [axis state](@ref NMC_AxisGetState) is AXIS_STATE_WAIT_SYNC and the axis parameter AXP_BUFF_PARAM is aborting, the motions stored in the motion queue will be removed. Then the point-to-point motion will be stored into the motion queue and wait for trigger signal.
 * 12. If the axis has not reach the target position during the point-to-point motion, NMC_AxisHalt() can be called to stop the motion.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * ret = NMC_AxisPtp( 0, 0, 100, 0 ) // Plan the motion based on the velocity configuration of the axis parameter AXP_VM
 * @endcode
 *
 * \b Reference: <br>
 * 1. NMC_AxisSetParamI32(), NMC_AxisSetParamF64()
 * 2. NMC_AxisResetState()
 * 3. NMC_AxisGetStatus()
 * 4. NMC_AxisHalt()
 */
RTN_ERR FNTYPE NMC_AxisPtp( I32_T DevID, I32_T AxisIndex, F64_T TargetPos, _opt_null_ const F64_T *PMaxVel );
/*!
 * @brief Execute Point-To-Point Motion according with target (or default) velocity.
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis Index
 * @param Dir       Direction. 1:Forward, -1:Reverse
 * @param PMaxVel   Input target velocity with a pointer variable. Moreover, input 0 directly for no target velocity, and the driver will get the configuration in axis parameter `AXP_VM` as the target velocity.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. The function can be called for point-to-point motion if the axis is excitation.
 * 2. If the axis is homing, the function will return the error code.
 * 3. If the axis is in the axis state `AXIS_STATE_STOPPING`, `AXIS_STATE_STOPPED` or `AXIS_STATE_ERROR`, the function will return the error code. After NMC_AxisResetState() is called to reset the axis to normal excitation (`AXIS_STATE_STAND_STILL`), the function can be called for JOG motion successfully.
 * 4. After the function is called, the drive will increase/decrease the velocity to the target velocity in accordance with the configuration in the axis parameter `AXP_ACC`, and the axis state will transfer to `AXIS_STATE_CONTINUOUS_MOTION`.
 * 5. After the target velocity is input with the pointer variable PMaxVel, the axis parameter `AXP_VM` will be modified accordingly. The input target velocity can be 0.
 * 6. After the function is called and the target velocity is reached, the bit 8 of the axis status becomes to 0, and the motion is continued at the target velocity.
 * 7. If the axis is executing other motions, it will execute the corresponding behavior depended on the axis parameter `AXP_BUFF_PARAM` after the function is called.
 * 8. After the function is called, NMC_AxisHalt() can be called to stop the motion.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * F64_T maxVel = 100;
 * ret = NMC_AxisJog( 0, 0, -1, &maxVel ); // Set the axis move reversely. Modify the axis parameter AXP_VM to 100 as the target velocity for the velocity plan.
 * @endcode
 *
 * \b Reference: <br>
 * 1. NMC_AxisSetParamI32(), NMC_AxisSetParamF64()
 * 2. NMC_AxisResetState()
 * 3. NMC_AxisGetStatus()
 * 4. NMC_AxisHalt()
 */
RTN_ERR FNTYPE NMC_AxisJog( I32_T DevID, I32_T AxisIndex, I32_T Dir, _opt_null_ const F64_T *PMaxVel );
/*!
 *  @}
 */

// Axis homing control APIs
/*! \addtogroup Axis_Homing
 *  Axis Returns to Home Functions
 *  @{
 */
/*!
 * @brief Set the origin of a single axis in the axis coordination system.
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis Index
 * @param HomePos   The value to set the origin in the axis coordinate system (ACS).
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_AxisSetHomePos( I32_T DevID, I32_T AxisIndex, F64_T HomePos );
/*!
 * @brief Drive an axis to move to the origin (by driver).
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis Index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. Before the axis motion, the function may be called to execute the homing procedure of axis in general, in order to drive the axis returns to the origin.
 * 2. The parameters related to homing are defined in the axis parameter table, including the homing methods, acceleration, velocity, offset, etc. Among these parameters, the methods shall be determined depended the methods supported by the drive.
 * 3. In case of any error occurred in the axis homing procedure, the bit 7 of the axis status will become to 1, and the axis will transfer to error state (AXIS_STATE_ERROR). In the case, after the axis stops completely (which can be determined by checking the bit 9 of axis status is 1), NMC_AxisResetDriveAlm() or NMC_AxisResetState() can be called to reset the axis to the normal state.
 * 4. After the axis completes the homing procedure, the bit18 of axis status will become to 1, and axis will transfer to normal excitation (AXIS_STATE_STAND_STILL).
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * ret = NMC_AxisHomeDrive( 0, 0 );
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_AxisHomeDrive( I32_T DevID, I32_T AxisIndex );
/*!
 *  @}
 */


// Axis motion termination APIs
/*! \addtogroup Axis_Motion_Termination
 *  Axis Motion Termination Functions
 *  @todo This group name is duplicated in pdf manual. Check if need to rename.
 *  @{
 */
/*!
 * @brief The function can be called to halt the axis motion.
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. When an axis is executing the point-to-point motion or JOG motion, the function can be called to stop the axis motion. The drive will decrease the velocity from the configuration in the axis parameter AXP_DEC to this in the AXP_V_BASE.
 * 2. If the axis is homing, the function will return the error code.
 * 3. If the axis is in the axis state_STATE_STOPPING, AXIS_STATE_STOPPED or AXIS_STATE_ERROR, the function will return the error code.
 * 4. If the axis is in the axis state_STATE_DISABLE or AXIS_STATE_STAND_STILL, the function will not return any error code.
 * 5. If the axis parameter AXP_BUFF_PARAM is set to aborting, the function can be called to stop the axis motion normally. If the axis parameter AXP_BUFF_PARAM is set to buffered, the function can be called to wait the bit 8 of axis status to 1 (the completion of the previous motion) and then to stop the axis motion normally.
 * 6. After the function is called and the motion is stopped successfully, the axis state will transfer to AXIS_STATE_DISCRETE_MOTION. After the axis is stopped, the bit 8 and 9 of axis status will become 1, and the axis state will transfer to normal excitation (AXIS_STATE_STAND_STILL).
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * ret = NMC_AxisHalt( 0, 0 );
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_AxisHalt( I32_T DevID, I32_T AxisIndex );
/*!
 * @brief The function can be called to stop the axis motion.
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. Whether an axis is executing each type of motion and such axis motion shall be stopped for some undesired cases, the function can be called to perform the forced stop procedure. The drive will decrease the velocity from the configuration in the axis parameter AXP_STOP_PROF_DEC to this in the AXP_V_BASE.
 * 2. If the axis is homing, the function will return the error code.
 * 3. After the function is called to perform the forced stop procedure and the axis has not stopped, the axis state will transfer to AXIS_STATE_STOPPING. After the axis is stopped, the bit 9 of axis status will become 1, and the axis state will transfer to AXIS_STATE_STOPPED.
 * 4. If the axis state is AXIS_STATE_STAND_STILL, it will transfer to AXIS_STATE_STOPPED after the function is called.
 * 5. After the function is called to perform the forced stop procedure and the axis has stopped, the axis is prohibited to execute any axis motion, until NMC_AxisResetState() is called to reset the axis to normal excitation (AXIS_STATE_STAND_STILL).
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * ret = NMC_AxisStop( 0, 0 );
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisResetState()
 */
RTN_ERR FNTYPE NMC_AxisStop( I32_T DevID, I32_T AxisIndex );
/*!
 * @brief The function can be called to halt the motions of all axes in a specified device normally.
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The usage is similar to this of NMC_AxisHalt(). The function can be called to stop the motions of all axes in a specified device normally.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * ret = NMC_AxisHaltAll( 0 );
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisHalt()
 */
RTN_ERR FNTYPE NMC_AxisHaltAll( I32_T DevID );
/*!
 * @brief The function can be called to stop the motions of all axes in a specified device forcedly.
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The usage is similar to this of NMC_AxisStop(). The function can be called to stop the motions of all axes in a specified device forcedly.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * ret = NMC_AxisStopAll( 0 );
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisStop()
 */
RTN_ERR FNTYPE NMC_AxisStopAll( I32_T DevID );
/*!
 *  @}
 */

// Axis profile change on the fly APIs
/*! \addtogroup Axis_Motion_Change
 *  Axis Motion Change Functions. Change Axis profile on the fly.
 *  @{
 */
/*!
 * @brief Override the velocity of a single axis.
 *
 * @param DevID     Device ID (Dev ID)
 * @param AxisIndex Axis index
 * @param TargetVel Target velocity (Unit: user unit/sec)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. The function can only be called to change the target velocity after the axis point-to-point motion (NMC_AxisPtp) or the axis JOG motion (NMC_AxisJog) is enabled.
 * 2. The target velocity input through the function will be effective to the current motion only, not to modify the axis parameter AXP_VM.
 * 3. If the JOG motion is enabled, the input target velocity can be reached, and the bit 8 of axis status will become to 1.
 * 4. If the point-to-point motion is enabled, the input target velocity may not be reached. To meet the specified target position and acceleration/deceleration, the drive will plan the practical velocity curve based on the input target velocity.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * F64_T maxVel = 100.0;
 * ret = NMC_AxisJog( 0, 0, 1, &maxVel ); // Enable the axis JOG motion at target velocity 100.
 * Sleep(100);
 * ret = NMC_AxisVelOverride( 0, 0, 50.0 ); // Decrease the target velocity to 50.
 * @endcode
 *
 * \b Reference: <br>
 * NMC_AxisPtp()
 * NMC_AxisJog()
 */
RTN_ERR FNTYPE NMC_AxisVelOverride( I32_T DevID, I32_T AxisIndex, F64_T TargetVel );
/*!
 * @brief Override the acceleration of a single axis.
 *
 * @param DevID     Device ID (Dev ID)
 * @param AxisIndex Axis index
 * @param TargetAcc Target acceleration
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. The function can only be called to change the target acceleration after the axis point-to-point motion (NMC_AxisPtp) or the axis JOG motion (NMC_AxisJog) is enabled.
 * 2. The input acceleration will be set to the axis parameter AXP_ACC.
 * 3. If the axis has reached the target velocity (bit 12 of axis status is 1), there is no any impact of the input acceleration on the current motion.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * I32_T status = 0;
 * F64_T maxVel = 50.0;
 * ret = NMC_AxisJog( 0, 0, 1, &maxVel ); // Enable the axis JOG motion at target velocity 50.
 * Sleep(100);
 * ret = NMC_AxisGetStatus( 0, 0, &status );
 * if( !( status & 0x1000 ) )
 * {
 * ret = NMC_AxisAccOverride ( 0, 0, 100.0 ); // // Change the acceleration to 100.
 * }
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_AxisAccOverride( I32_T DevID, I32_T AxisIndex, F64_T TargetAcc );
/*!
 * @brief Override the deceleration of a single axis.
 *
 * @param DevID     Device ID (Dev ID)
 * @param AxisIndex Axis index
 * @param TargetDec Target deceleration
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. The function can only be called to change the target deceleration after the axis point-to-point motion (NMC_AxisPtp) or the normal stop (NMC_AxisHalt) is enabled.
 * 2. The input deceleration will be set to the axis parameter AXP_DEC.
 * 3. If the axis point-to-point is enabled and the axis velocity is changed from the target velocity to the configured end velocity gradually (bit 11 of axis status is 1), there is no any impact of the input deceleration on the current motion.
 * 4. If the normal stop of axis (NMC_AxisHalt) is enabled and the axis has not stopped, the input deceleration will impact on the current motion
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * I32_T status = 0;
 * F64_T maxVel = 50.0;
 * ret = NMC_AxisPtp( 0, 0, 100, 0 ); // Enable the axis point-to-point motion at the target velocity based on the AXP_VM.
 * ret = NMC_AxisDecOverride ( 0, 0, 100.0 ); // Change the deceleration to 100.0
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_AxisDecOverride( I32_T DevID, I32_T AxisIndex, F64_T TargetDec );
/*!
 *  @}
 */

// Axis velocity ratio setting APIs
RTN_ERR FNTYPE NMC_AxisSetSpeedRatio( I32_T DevID, I32_T AxisIndex, F64_T Percentage );
RTN_ERR FNTYPE NMC_AxisGetSpeedRatio( I32_T DevID, I32_T AxisIndex, F64_T *PPercentage );
/*!
 *  @}
 */

/*! \addtogroup Group_API
 *  Group APIs
 *  @{
 */
// Group parameter setting APIs
/*! \addtogroup Group_Config
 *  Group Configuration Functions
 *  @{
 */
/*!
 * @brief Set the Group Parameters (I32_T, data type).
 *
 * @param DevID         Device ID (DevID)
 * @param GroupIndex    Group Index
 * @param ParamNum      Parameter Number
 * @param SubIndex      Parameter sub-index
 * @param ParaValueI32  [Input] Value to be set (signed integer).
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T paramNum = 0x30; // The set command is an absolute or incremental parameter
 * I32_T subIndex = 0;
 * I32_T paraValueI32 = 1; // The command is incremental
 * RTN_ERR ret = 0;
 * ret = NMC_GroupSetParamI32( devID, groupIndex, paramNum, subIndex, paraValueI32 );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupSetParamI32( I32_T DevID, I32_T GroupIndex, I32_T ParamNum, I32_T SubIndex, I32_T ParaValueI32 );
/*!
 * @brief Get the Group Parameters (I32_T, data type).
 *
 * @param DevID             Device ID (DevID)
 * @param GroupIndex        Group Index
 * @param ParamNum          Parameter Number
 * @param SubIndex          Parameter sub-index
 * @param[out] PRetParaValueI32  [Input] A pointer variable, [Output] Value of the parameter
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T paramNum = 0x30; // The get command is an absolute or incremental parameter
 * I32_T subIndex = 0;
 * I32_T paraValueI32 = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetParamI32( devID, groupIndex, paramNum, subIndex, &paraValueI32 );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupGetParamI32( I32_T DevID, I32_T GroupIndex, I32_T ParamNum, I32_T SubIndex, I32_T *PRetParaValueI32 );
/*!
 * @brief Set the group parameters (F64_T, data type).
 *
 * @param DevID         Device ID (Dev ID)
 * @param GroupIndex    Group Index
 * @param ParamNum      Parameter number
 * @param SubIndex      Parameter sub-index
 * @param ParaValueF64  [Input] Value to be set (double precision float)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T paramNum = 0x21; // Set the deceleration to stop motion.
 * I32_T subIndex = 0;
 * F64_T paraValueF64 = 80.5; // Value of the deceleration to stop motion.
 * RTN_ERR ret = 0;
 * ret = NMC_GroupSetParamF64( devID, groupIndex, paramNum, subIndex, paraValueF64 );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupSetParamF64( I32_T DevID, I32_T GroupIndex, I32_T ParamNum, I32_T SubIndex, F64_T ParaValueF64 );
/*!
 * @brief Get the group parameters (F64_T, data type).
 *
 * @param DevID             Device ID (Dev ID)
 * @param GroupIndex        Group Index
 * @param ParamNum          Parameter number
 * @param SubIndex          Parameter sub-index
 * @param[out] PRetParaValueF64  [Output] Value to be returned (double precision float)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T paramNum = 0x21; // Set the deceleration to stop motion.
 * I32_T subIndex = 0;
 * F64_T paraValueF64 = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetParamF64( devID, groupIndex, paramNum, subIndex, &paraValueF64 );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupGetParamF64( I32_T DevID, I32_T GroupIndex, I32_T ParamNum, I32_T SubIndex, F64_T *PRetParaValueF64 );
/*!
 * @brief Set the parameters of group axis (I32_T, data type)
 *
 * @param DevID           Device ID (Dev ID)
 * @param GroupIndex      Group Index
 * @param GroupAxisIndex  Group Axis Index
 * @param ParamNum        Parameter Number
 * @param SubIndex        Parameter Sub-Index
 * @param ParaValueI32    [Input] Value to be set (signed integer)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T groupAxisIndex = 2;
 * I32_T paramNum = 0x30; // The set command is an absolute or incremental parameter
 * I32_T subIndex = 0;
 * I32_T paraValueI32 = 1; // The command is incremental
 * RTN_ERR ret = 0;
 * ret = NMC_GroupAxSetParamI32( devID, groupIndex, groupAxisIndex, paramNum, subIndex, paraValueI32 );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupAxSetParamI32( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T ParamNum, I32_T SubIndex, I32_T ParaValueI32 );
/*!
 * @brief Get the parameters of group axis (I32_T, data type).
 *
 * @param      DevID             Device ID (Dev ID)
 * @param      GroupIndex        Group index
 * @param      GroupAxisIndex    Group axis index
 * @param      ParamNum          Parameter number
 * @param      SubIndex          Parameter sub-index
 * @param[out] PRetParaValueI32  [Output] Value to be returned (signed integer)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T groupAxisIndex = 2
 * I32_T paramNum = 0x30; // The get command is an absolute or incremental parameter
 * I32_T subIndex = 0;
 * I32_T paraValueI32 = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupAxGetParamI32( devID, groupIndex, groupAxisIndex, paramNum, subIndex, &paraValueI32 );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupAxGetParamI32( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T ParamNum, I32_T SubIndex, I32_T *PRetParaValueI32 );
/*!
 * @brief Set the parameters of group axis (F64_T, data type)
 *
 * @param DevID           Device ID (Dev ID)
 * @param GroupIndex      Group Index
 * @param GroupAxisIndex  Group Axis Index
 * @param ParamNum        Parameter Number
 * @param SubIndex        Parameter Sub-Index
 * @param ParaValueF64    [Input] Value to be set (double precision float)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T groupAxisIndex = 2;
 * I32_T paramNum = 0x21; // Set the deceleration to stop motion.
 * I32_T subIndex = 0;
 * F64_T paraValueF64 = 80.5; // Value of the deceleration to stop motion.
 * RTN_ERR ret = 0;
 * ret = NMC_GroupAxSetParamF64( devID, groupIndex, groupAxisIndex, paramNum, subIndex, paraValueF64 );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupAxSetParamF64( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T ParamNum, I32_T SubIndex, F64_T ParaValueF64 );
/*!
 * @brief Get the parameters of group axis (F64_T, data type).
 *
 * @param      DevID             Device ID (Dev ID)
 * @param      GroupIndex        Group index
 * @param      GroupAxisIndex    Group axis index
 * @param      ParamNum          Parameter number
 * @param      SubIndex          Parameter sub-index
 * @param[out] PRetParaValueF64  [Output] Value to be returned (double precision float)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T groupAxisIndex = 2;
 * I32_T paramNum = 0x21; // Set the deceleration to stop motion.
 * I32_T subIndex = 0;
 * F64_T paraValueF64 = 0; // Value of the deceleration to stop motion.
 * RTN_ERR ret = 0;
 * ret = NMC_GroupAxGetParamF64( devID, groupIndex, groupAxisIndex, paramNum, subIndex, &paraValueF64 );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupAxGetParamF64( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T ParamNum, I32_T SubIndex, F64_T *PRetParaValueF64 );
/*!
 *  @}
 */

// Group state control APIs
/*! \addtogroup Group_State_Control
 *  Group State Control Functions
 *  @{
 */
/*!
 * @brief Enable all group axes (Servo On). If all group axes are enabled successfully, the [group state](@ref NMC_GroupGetState) will transfer from GROUP_DISABLE to GROUP_ENABLE
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group Index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupEnable( devID, groupIndex );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupEnable( I32_T DevID, I32_T GroupIndex );
/*!
 * @brief Disable all group axes ( Servo Off ). If all group axes are disabled successfully, the [group state](@ref NMC_GroupGetState) will transfer to GROUP_DISABLE.
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32 _T devID = 0;
 * I32_T groupIndex = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupDisable( devID, groupIndex );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupDisable( I32_T DevID, I32_T GroupIndex );
/*!
 * @brief Get the [group status](@ref Group_Status) by bit. The meanings of the bits are describe as follows. if the bit values is 1, the event is triggered.
 *
 * | bit   | Description                  |
 * | :---: | :----                        |
 * |0      |Trigger the external emergency switch|
 * |1      |Drive alarm|
 * |2      |Over the positive limit of hardware|
 * |3      |Over the negative limit of hardware|
 * |4      |Over the positive limit of soft ware|
 * |5      |Over the negative limit of software|
 * |6      |All groups enabled (i.e. all group state are GROUP_STAND_STILL)|
 * |7      |A group axis error (i.e. a group axis state is GROUP_ERROR_STOP)|
 * |9      |No position change for all group axes|
 * |10     |The (line or arc) motion in the Cartesian coordinate system is accelerated (or decelerated) to the maximum velocity. The bit is 0 in case of the PTP or JOG motion.|
 * |11     |The (line or arc) motion in the Cartesian coordinate system is decelerated to the target velocity or 0. The bit is 0 in case of the PTP or JOG motion.|
 * |12     |The (line or arc) motion in the Cartesian coordinate system is executed at the maximum velocity. The bit is 0 in case of the PTP or JOG motion.|
 * |13     |The group is in motion (i.e. the group state is GROUP_MOVING , GROUP_HOMING or GROUP_STOPPING)|
 * |14     |The group is stopped (i.e. the group state is GROUP_STOPPED)|
 *
 * @param DevID           Device ID (DevID)
 * @param GroupIndex      Group index
 * @param[out] PRetStatusInBit  [Input]A pointer variable,[Output] Status by bit.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T group Index = 0;
 * I32_T statusInBit = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetStatus( devID, groupIndex, &statusInBit );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 *
 */
RTN_ERR FNTYPE NMC_GroupGetStatus( I32_T DevID, I32_T GroupIndex, I32_T *PRetStatusInBit );
/*!
 * @brief Get the state of group. Please refer to the below table for details.
 *
 * | Value  | State             | Description                                             |
 * | :----: | :----             | :----                                                   |
 * | 0      | GROUP_DISABLE     | A group axis is disabled.                               |
 * | 1      | GROUP_STAND_STILL | A group axes are enabled.                               |
 * | 2      | GROUP_STOPPED     | After NMC_GroupStop() is called, the group is stopped.  |
 * | 3      | GROUP_STOPPING    | After NMC_GroupStop() is called, the group is stopping. |
 * | 4      | GROUP_MOVING      | A group is moving.                                      |
 * | 5      | GROUP_HOMING      | A group is homing.                                      |
 * | 6      | GROUP_ERROR_STOP  | An error is occured in a group axis.                    |
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group index
 * @param[out] PRetState   [Input] A pointer variable, [Output] Group state
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T state = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetState( devID, groupIndex, &state );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupGetState( I32_T DevID, I32_T GroupIndex, I32_T *PRetState );
/*!
 * @brief Reset the [group state](@ref Group_State) . It can reset the group state from GROUP_STOPPED to GROUP_STAND_STILL.
 * If the group state is GROUP_ERROR_STOP and the API is called, all drive alarms will be reset automatically.
 * Then the group state will transfer to GROUP_STAND_STILL after all drive alarms are reset.
 *
 * @param DevID Device ID (DevID)
 * @param GroupIndex  Group index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * RTN_ERR ret = 0;
 *
 * ret = NMC_GroupResetState( devID, groupIndex );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupResetState( I32_T DevID, I32_T GroupIndex );
/*!
 * @brief Reset the group servo alarm.
 *
 * @param DevID Device ID (DevID)
 * @param GroupIndex Group index
 * @param GroupAxisIndex The index of the group axis which alarm to be reset.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID =
 * I32_T groupIndex = 0;
 * I32_T groupAxisIndex = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupResetDriveAlm( devID, groupIndex, groupAxisInde x );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupResetDriveAlm( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex );
/*!
 * @brief Reset all group servo alarms.
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group Index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupResetDriveAlmAll( devID, groupIndex );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupResetDriveAlmAll( I32_T DevID, I32_T GroupIndex );
/*!
 * @brief Get alarm code fo Drive
 *
 * @param DevID Device ID (DevID)
 * @param GroupIndex Group index
 * @param GroupAxisIndex Group axis index
 * @param[out] PRetAlmCode  The alarm code.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 *
 * @todo Add more description. The original definition is empty in official pdf manual.
 */
RTN_ERR FNTYPE NMC_GroupGetDriveAlmCode( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T *PRetAlmCode );
/*!
 *  @}
 */

// Group velocity ratio setting APIs
/*! \addtogroup Group_Speed_Config
 *  Group Speed Ratio Configuration Functions
 *  @{
 */
/*!
 * @brief Set the speed percentage of a group from 0.0 to 100.0%.
 *
 * @param DevID       Decice ID (DevID)
 * @param GroupIndex  Group Inex
 * @param Percentage  Speed percentage to be set (0 to 100 %)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * F64_T percentage = 100.0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupSetSpeedRatio( devID, groupIndex, percentag e );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupSetSpeedRatio( I32_T DevID, I32_T GroupIndex, F64_T Percentage );
/*!
 * @brief Get the speed percentage of a group from 0.0 to 100.0%.
 *
 * @param DevID            Decice ID (DevID)
 * @param GroupIndex       Group Inex
 * @param[out] PRetPercentage  [Input] A pointer variable, [Output] Velocity percentage.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * F64_T percentage = 0.0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetSpeedRatio( devID, groupIndex, &percentag e );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 */
RTN_ERR FNTYPE NMC_GroupGetSpeedRatio( I32_T DevID, I32_T GroupIndex, F64_T *PRetPercentage );
/*!
 *  @}
 */

// Group axis point to point motion in ACS
/*! \addtogroup Group_P2P_Motion_ACS
 *  Group Point-to-Point Motion Function. (Axis Coordinate System)
 *  @{
 */
/*!
 * @brief Enable the point-to-point motion for a group axis in the a xis coordinate system (ACS). The default
 * maximum velocity will refer to the value in the input parameters. If required, the maximum velocity
 * can be set in the API, and the specified value will be stored in the corresponding parameters
 * automatically.
 *
 * @param DevID Device ID (DevID)
 * @param GroupIndex  Group index
 * @param GroupAxisIndex  The group axis index to be driven a motion
 * @param AcsPos  The point position to be reached
 * @param PAcsMaxVel  A pointer variable which can specify the maximum velocity. Input NULL (0) to ignore the parameter.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T groupAxisIndex = 2;
 * F64_T acsPos = 35.5;
 * F64_T acsMaxVel = 80.0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupPtpAcs( devID, groupIndex, groupAxisIndex, acsPos, &acsMaxVel );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupPtpAcs( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, F64_T AcsPos, _opt_null_ const F64_T *PAcsMaxVel );
/*!
 * @brief Enable the point-to-point motion for multiple group axes in the a xis coordinate system (ACS). The
 * specified group axes will start the motion and reach the target position at the same time.
 *
 * @param DevID Device ID (DevID)
 * @param GroupIndex  Group index
 * @param GroupAxesIdxMask  The group axis index mask is specified to execute the motion. Please refer to the below table.
 * @param PAcsPos A pointer variable to set the target position.
 *
 * | Group Axis                    | 8         | 7         | 6         | 5         | 4         | 3         | 2         | 1         |
 * | :----:                        | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    |
 * | Bit index                     | 7         | 6         | 5         | 4         | 3         | 2         | 1         | 0         |
 * | The power is the index of bit | \f$2^7\f$ | \f$2^6\f$ | \f$2^5\f$ | \f$2^4\f$ | \f$2^3\f$ | \f$2^2\f$ | \f$2^1\f$ | \f$2^0\f$ |
 *
 * The usage of the group axis index mask (GroupAxesIdxMask) is described as follows:
 * If the group axes to be moved are the 1st, 3rd and 8th axes, the GroupAxesIdxMask is \f$2^0\f$ + \f$2^2\f$ + \f$2^7\f$ = 133.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T groupAxes IdxMask = 133; // Move the 1st , 3rd and 8th axes.
 * Pos_T acsPos = { 10, 20, 30, 40, 50, 60, 70 };
 * RTN_ERR ret = 0;
 *
 * ret = NMC_GroupPtpAcsAll( devID, groupIndex, groupAxesIdxMask, &acsPos );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupPtpAcsAll( I32_T DevID, I32_T GroupIndex, I32_T GroupAxesIdxMask, const Pos_T *PAcsPos );
/*!
 *  @}
 */

// Group axis jog motion in ACS
/*! \addtogroup Group_Jog_Motion_ACS
 *  Group Axis Jog Motion Function. (Axis Coordinate System)
 *  @{
 */
/*!
 * @brief Enable the JOG motion for a group axis in the axis coordinate system (ACS). The default maximum velocity
 * will refer to the value in the input parameters. If required, the maximum velocity can be set in the API, and
 * the specified value will be stored in the corresponding parameters automatically.
 *
 * @param DevID           Device ID (DevID)
 * @param GroupIndex      Group index
 * @param GroupAxisIndex  Group axis index
 * @param Dir             Rotation direction
 * @param PAcsMaxVel      A pointer variable which can specify the maximum velocity. Input NULL (0) to igore the parameter.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T groupAxisIndex = 2;
 * I32_T dir =1;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupJogAcs( devID, groupIndex, groupAxisIndex, dir, NULL );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupJogAcs( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T Dir, _opt_null_ const F64_T *PAcsMaxVel  );
/*!
 *  @}
 */

// Group axis jog motion in PCS
/*! \addtogroup Group_Jog_Motion_PCS
 *  Group Jog Motion Functions (Cartesian coordinate system)
 *  @todo Update description of Tcp & Pcs Frame function. (No description in official pdf manual).
 *  @{
 */
/*!
 * @brief Enable the JOG motion of group axis in the Cartesian coordinate system with respect to the tool center point (TCP).
 *
 * @param DevID         Device ID (DevID)
 * @param GroupIndex    Group index
 * @param CartAxis      The coordinate axis index for the motion in the (TCP) Cartesian coordinate system. Please refer to the below table.
 * @param Dir           Direction. 0: Forward, 1: Reverse
 * @param[out] PMaxVel  A pointer variable to set the maximum. Input NULL (0) to ignore the parameter.
 *
 * | Cartesian Coordinate Axis (TCP)  | V         | U         | C         | B         | A         | Z         | Y         | X         |
 * | :----:                           | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    |
 * | Bit index                        | 7         | 6         | 5         | 4         | 3         | 2         | 1         | 0         |
 * | The power is the index of bit    | \f$2^7\f$ | \f$2^6\f$ | \f$2^5\f$ | \f$2^4\f$ | \f$2^3\f$ | \f$2^2\f$ | \f$2^1\f$ | \f$2^0\f$ |
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupJogTcpFrame( I32_T DevID, I32_T GroupIndex, I32_T CartAxis, I32_T Dir, _opt_null_ const F64_T *PMaxVel  );
/*!
 * @brief Enable the JOG motion of group axis in the Product coordinate system.
 *
 * @param DevID         Device ID (DevID)
 * @param GroupIndex    Group index
 * @param CartAxis      The coordinate axis index for the motion in the (TCP) Cartesian coordinate system. Please refer to the below table.
 * @param Dir           Direction. 0: Forward, 1: Reverse
 * @param[out] PMaxVel  A pointer variable to set the maximum. Input NULL (0) to ignore the parameter.
 *
 * | Cartesian Coordinate Axis (PCS)  | V         | U         | C         | B         | A         | Z         | Y         | X         |
 * | :----:                           | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    |
 * | Bit index                        | 7         | 6         | 5         | 4         | 3         | 2         | 1         | 0         |
 * | The power is the index of bit    | \f$2^7\f$ | \f$2^6\f$ | \f$2^5\f$ | \f$2^4\f$ | \f$2^3\f$ | \f$2^2\f$ | \f$2^1\f$ | \f$2^0\f$ |
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupJogPcsFrame( I32_T DevID, I32_T GroupIndex, I32_T CartAxis, I32_T Dir, _opt_null_ const F64_T *PMaxVel  );
/*!
 *  @}
 */

// Group point to point motion in PCS
/*! \addtogroup Group_P2P_Motion_PCS
 *  Group Point-to-Point Motion Functions. (Cartesian Coordinate System)
 *  @{
 */
/*!
 * @brief Enable the point-to-point motion of group axis in the Cartesian coordinate system.
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group index
 * @param CartAxis    The Coordinate axis index for the motion in the Cartesin coordinate system. Please refer to the below table.
 * @param CartPos     The point position to be reached.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * | Cartesian Coordinate          | U     | V      | C      | B      | A      | Z      | Y      | X      |
 * | :----:                        | :---- | :----: | :----: | :----: | :----: | :----: | :----: | :----: |
 * | Axis Value                    | 7     | 6      | 5      | 4      | 3      | 2      | 1      | 0      |
 *
 * The usage of the coordinate axis index in the Cartesian coordinate system (CartAxis) is described as follows:
 * If the motion is executed on the z-axis in the Cartesian coordinate system, the CartAxis is 2.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T cartAxis = 2;
 * F64_T cartPos = 55.5;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupPtpCart( devID, groupIndex, cartAxis, cartPos );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupPtpCart( I32_T DevID, I32_T GroupIndex, I32_T CartAxis, F64_T CartPos );
/*!
 * @brief Enable the point-to-point motion of multiple group axes on the points in the Cartesian coordinate system.
 *
 * @param DevID         Device ID (DevID)
 * @param GroupIndex    Group index
 * @param CartAxesMask  The group axis index mask is specified to execute the point-to-point motion in the Cartesian coordinate system. Please refer to the below table.
 * @param PTargetPos    A pointer variable to set the target position.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * | Cartesian Coordinate          | U         | V         | C         | B         | A         | Z         | Y         | X         |
 * | :----:                        | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    |
 * | Axis Value/Bit index          | 7         | 6         | 5         | 4         | 3         | 2         | 1         | 0         |
 * | The power is the index of bit | \f$2^7\f$ | \f$2^6\f$ | \f$2^5\f$ | \f$2^4\f$ | \f$2^3\f$ | \f$2^2\f$ | \f$2^1\f$ | \f$2^0\f$ |
 *
 * The usage of the group axis index mask in the Cartesian coordinate system (CartAxesMask) is described as follows:
 * If the group axes to be moved are the X-, Z- and A-axis, the GroupAxesIdxMask is \f$2^0\f$ + \f$2^2\f$ + \f$2^3\f$ = 13.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T cartAxesMask = 13;
 * // Move the X-, Z- and A-axis
 * Pos_T targetPos = { 10, 20, 30, 40, 50, 60, 70 };
 * RTN_ERR ret = 0;
 * ret = NMC_GroupPtpCartAll( devID, groupIndex, cartAxesMask, &targetPos );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupPtpCartAll( I32_T DevID, I32_T GroupIndex, I32_T CartAxesMask, const Pos_T *PTargetPos );
/*!
 *  @}
 */

// Group motion termination APIs
/*! \addtogroup Group_Halt_and_Stop
 *  Group Halt and Stop Functions
 *  @{
 */
/*!
 * @brief Halt a group (Stand still state). The API will decrease the velocity for each type of motion, and
 *        the [group state](@ref NMC_GroupGetState) will transfer from GROUP_MOVING to GROUP_STOPPING during the velocity decreasing,
 *        and to the GROUP_STAND_STILL when the velocity is 0.
 *        The API shall specify the motion stop in accompanying the buffer mode. If the buffer mode is aborting,
 *        the current motion will decrease the velocity immediately. If the buffer mode is buffered, the API will
 *        be added into the motion buffer and will not be effective immediately.
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group Index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T dev ID = 0;
 * I32_T groupIndex = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupHalt( devID, gro upIndex );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * NMC_GroupGetState()
 */
RTN_ERR FNTYPE NMC_GroupHalt( I32_T DevID, I32_T GroupIndex );
/*!
 * @brief Stop a group (Stop state). The API will decrease the velocity for each type of motion, and the [group state](@ref NMC_GroupGetState)
 *        will transfer from GROUP_MOVING to GROUP_ST OPPING during the velocity decreasing, and to the GROUP_STAND_STOPPED when the velocity is 0.
 *        To execute a new motion, NMC_GroupResetState() shall be called to reset the group state GROUP_STOPPED.
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group Index
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T dev ID = 0;
 * I32_T groupIndex = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupStop( devID, groupIndex );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * NMC_GroupGetState()
 */
RTN_ERR FNTYPE NMC_GroupStop( I32_T DevID, I32_T GroupIndex );
/*!
 * @brief Halt all groups (Stand still state). The API will decrease the velocity for each type of motion, and the
 *        [group state](@ref NMC_GroupGetState) will transfer from GROUP_MOVING to GROUP_STOPPING during the velocity decreasing,
 *        and to the GROUP_STAND_STILL when the velocity is 0.
 *        The API shall specify the motion stop in accompanying the buffer mode. If the buffer mode is aborting,
 *        the current moti on will decrease the velocity immediately. If the buffer mode is buffered, the API will
 *        be added into the motion buffer and will not be effective immediately.
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID =
 * RTN_ERR ret =
 * r et = NMC_GroupHaltAll( devID );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * NMC_GroupGetState()
 */
RTN_ERR FNTYPE NMC_GroupHaltAll( I32_T DevID );
/*!
 * @brief Stop all groups (Stop state). The API will decrease the velocity for each type of motion, and
 *        the [group state](@ref NMC_GroupGetState) will transfer from GROUP_MOVING to GROUP_STOPPING during the velocity decreasing, and to
 *        the GROUP_STAND_S TOPPED when the velocity is 0.
 *        To execute a new motion, NMC_GroupResetState() shall be called to reset the group state GROUP_STOPPED.
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * RTN_ERR ret =
 * ret = NMC_GroupStopAll( devID );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * NMC_GroupGetState()
 */
RTN_ERR FNTYPE NMC_GroupStopAll( I32_T DevID );
/*!
 *  @}
 */

// Group motion profile read APIs
/*! \addtogroup Group_Motion_Status
 *  Group Motion Status Functions
 *  @{
 */
/*!
 * @brief Get the command position of a group axis in the axis coordinate system (ACS).
 *
 * @param DevID              Device ID (DevID)
 * @param GroupIndex         Group index
 * @param[out] PRetCmdPosAcs [Input] A pointer variable, [Output] The command position of the specified group axis.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * Pos_T cmdPosAcs = {0};
 * RTN_ERR ret = 0;
 *
 * ret = NMC_GroupGetCommandPosAcs(devID, groupIndex, &cmdPosAcs);
 * if(ret != 0) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupGetCommandPosAcs( I32_T DevID, I32_T GroupIndex, Pos_T *PRetCmdPosAcs );
/*!
 * @brief Get the actual position of a group axis in the axis coordinate system (ACS). The actual value is converted from the count value of the encoder based on the gear ratio or the lead screw pitch in the axis coordinate system (ACS).
 *
 * @param DevID              Device ID (DevID)
 * @param GroupIndex         Group index
 * @param[out] PRetActPosAcs [Input] A pointer variable, [Output] The actual position of each group axis.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * Pos_T actPosAcs = { 0 };
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetActualPosAcs( devID, groupIndex, &actPosAcs );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupGetActualPosAcs( I32_T DevID, I32_T GroupIndex, Pos_T *PRetActPosAcs );
/*!
 * @brief Get the command position of a group axis in the Cartesian coordinate system (PCS).
 *
 * @param DevID              Device ID (DevID)
 * @param GroupIndex         Group index
 * @param[out] PRetCmdPosPcs [Input] A pointer variable, [Output] The command position of the specified group axis.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * Pos_T cmdPosPcs = { 0 };
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetCommandPosPcs( devID, groupIndex, &cmdPosPcs );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupGetCommandPosPcs( I32_T DevID, I32_T GroupIndex, Pos_T *PRetCmdPosPcs );
/*!
 * @brief Get the actual position of a group axis in the Cartesian coordinate system (PCS). The actual value is converted from the count value of the encoder based on the gear ratio or the lead screw pitch in the Cartesian coordinate system (PCS).
 *
 * @param DevID              Device ID (DevID)
 * @param GroupIndex         Group index
 * @param[out] PRetActPosPcs [Input] A pointer variable, [Output] The actual position of each group axis.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * Pos_T actPosPcs = { 0 };
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetActualPosPcs( devID, groupIndex, &actPosPcs );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupGetActualPosPcs( I32_T DevID, I32_T GroupIndex, Pos_T *PRetActPosPcs );
/*!
 * @brief Get the command position of a group. The returned value is specified depended on the coordinate system.
 *
 * @param DevID            Device ID (DevID)
 * @param GroupIndex       Group index
 * @param CoordSys         Specified the coordinate system ( 0:MCS, 1:PCS, 2:ACS )
 * @param[out] PRetCmdPos  [Input] A pointer variable, [Output] The command position depended on the specified coordinate system
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T coordSys = 2; // Get the command position in the axis coordinate system
 * Pos_T cmdPos = { 0 };
 * RTN_ERR ret = 0;
 *
 * ret = NMC_GroupGetCommandPos( devID, groupIndex, coordSys, &cmdPos );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupGetCommandPos( I32_T DevID, I32_T GroupIndex, I32_T CoordSys, Pos_T *PRetCmdPos );
/*!
 * @brief Get the actual position of a group. The returned value is specified depended on the coordinate system.
 *
 * @param DevID            Device ID (DevID)
 * @param GroupIndex       Group index
 * @param CoordSys         Specified the coordinate system ( 0:MCS, 1:PCS, 2:ACS )
 * @param[out] PRetActPos  [Input] A pointer variable, [Output] The command position depended on the specified coordinate system
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T coordSys = 2; // Get the actual position in the axis coordinate system
 * Pos_T actPos = { 0 };
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetActualPos( devID, groupIndex, coordSys, &actPos );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupGetActualPos( I32_T DevID, I32_T GroupIndex, I32_T CoordSys, Pos_T *PRetActPos );
/*!
 * @brief Get the size of buffer space of group motion command.
 *
 * @param DevID              Device ID (DevID)
 * @param GroupIndex         Group index
 * @param[out] PRetFreeSpace [Input] A pointer variable, [Output] The free size of the motion buffer
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T freeSpace = 0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetMotionBuffSpace( devID, groupIndex, &freeSpace );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupGetMotionBuffSpace( I32_T DevID, I32_T GroupIndex, I32_T *PRetFreeSpace );
/*!
 *  @}
 */

// Group homing oparation APIs
/*! \addtogroup Group_Homing
 *  Group Returns to Home Functions
 *  @{
 */
/*!
 * @brief Set the origin of a group axis in the axis coordination system.
 *
 * @param DevID             Device ID (DevID)
 * @param GroupIndex        Group Index
 * @param GroupAxesIdxMask  The group axis index mask is specified toexecute the motion.
 * @param PHomePosAcs       A pointer variable to set the origin in the axis coordinate system (ACS).
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * | Group Axis                    | 8         | 7         | 6         | 5         | 4         | 3         | 2         | 1         |
 * | :----:                        | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    |
 * | Bit index                     | 7         | 6         | 5         | 4         | 3         | 2         | 1         | 0         |
 * | The power is the index of bit | \f$2^7\f$ | \f$2^6\f$ | \f$2^5\f$ | \f$2^4\f$ | \f$2^3\f$ | \f$2^2\f$ | \f$2^1\f$ | \f$2^0\f$ |
 *
 * The usage of the group axis index mask (GroupAxesIdxMask) is described as follows:
 * If the group axes to be moved are the 1st, 3rd and 8th axes, the GroupAxesIdxMask is \f$2^0\f$ + \f$2^2\f$ + \f$2^7\f$ = 133.
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupSetHomePos( I32_T DevID, I32_T GroupIndex, I32_T GroupAxesIdxMask, const Pos_T *PHomePosAcs );
/*!
 * @brief Drive a group to move to the origin.
 *
 * @param DevID             Device ID (DevID)
 * @param GroupIndex        Group Index
 * @param GroupAxesIdxMask  The group axis index mask is specified to execute the motion.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * | Group Axis                    | 8         | 7         | 6         | 5         | 4         | 3         | 2         | 1         |
 * | :----:                        | :----     | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    |
 * | Bit index                     | 7         | 6         | 5         | 4         | 3         | 2         | 1         | 0         |
 * | The power is the index of bit | \f$2^7\f$ | \f$2^6\f$ | \f$2^5\f$ | \f$2^4\f$ | \f$2^3\f$ | \f$2^2\f$ | \f$2^1\f$ | \f$2^0\f$ |
 *
 * The usage of the group axis index mask (GroupAxesIdxMask) is described as follows:
 * If the group axes to be moved are the 1st, 3rd and 8th axes, the GroupAxesIdxMask is \f$2^0\f$ + \f$2^2\f$ + \f$2^7\f$ = 133.
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupAxesHomeDrive( I32_T DevID, I32_T GroupIndex, I32_T GroupAxesIdxMask );
/*!
 *  @}
 */

// 2D cartesian space (MCS,PCS) interpolation
/*! \addtogroup Group_2D_Motion
 *  Group 2D Line or Arc Interpolation Motion Functions
 *  @todo Add description to NMC_GroupCirc2BEx function
 *  @{
 */
/*!
 * @brief Enable the group line interpolation motion on the XY plane from the current position to the target position in the Cartesian coordinate
 * system. The [group state](@ref NMC_GroupGetState) will transfer from GROUP_STAND_STILL to GROUP_MOVING. If the group reaches the target position (i.e. the velocity is
 * decreased to 0), the [group state](@ref NMC_GroupGetState) will transfer to GROUP_STAND_STILL. The default maximum velocity will refer to the value in the input parameters.
 * If required, the maximum velocity can be set in the API, and the specified value will be stored in the corresponding parameters automatically.
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group index
 * @param[in] PX      A pointer variable to set the target position at X-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param[in] PY      A pointer variable to set the target position at Y-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param[in] PMaxVel A pointer variable to set the maximum velocity. Input NULL (0) to ignore the parameter.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * F64_T posX= 10.0;
 * F64_T posY = 20.0;
 * RTN_ERR ret = 0;
 *
 * ret = NMC_GroupLineXY( devID, groupIndex, &posX, &posY, NULL );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupLineXY( I32_T DevID, I32_T GroupIndex, _opt_null_ const F64_T *PX, _opt_null_ const F64_T *PY, const F64_T _opt_null_ *PMaxVel );
/*!
 * @brief Enable the group arc interpolation motion on the XY plane from the current position to the target position in the Cartesian coordinate
 * system (radius method). The [group state](@ref NMC_GroupGetState) will transfer from GROUP_STAND_STILL to GROUP_MOVING. If the group reaches the target position (i.e. the
 * velocity is decreased to 0), the [group state](@ref NMC_GroupGetState) will transfer to GROUP_STAND_STILL. The default maximum velocity will refer to the value in the input
 * parameters. If required, the maximum velocity can be set in the API, and the specified value will be stored in the corresponding parameters
 * automatically.
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group index
 * @param[in] PEX     A pointer variable to set the target position at X-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param[in] PEY     A pointer variable to set the target position at Y-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param Radius      Radius of arc (negative value indicates the larger radian path).
 * @param CW_CCW      Rotation direction of arc (0=CW; 1=CCW)
 * @param[in] PMaxVel A pointer variable to set the maximum velocity. Input NULL (0) to ignore the parameter.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * F64_T posX = 50.0;
 * F64_T posY = 50.0;
 * F64_T radius = 25.0;
 * I32_T cwCcw = 1;
 * RTN_ERR ret = 0;
 *
 * ret = NMC_GroupCirc2R( devID, groupIndex, &posX, &posX, radius, cwCcw, NULL );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupCirc2R( I32_T DevID, I32_T GroupIndex, _opt_null_ const F64_T *PEX, _opt_null_ const F64_T *PEY, F64_T Radius, I32_T CW_CCW, _opt_null_ const F64_T *PMaxVel );
/*!
 * @brief Enable the group arc interpolation motion on the XY plane from the current position to the target position in the Cartesian coordinate
 * system (circle center method). The [group state](@ref NMC_GroupGetState) will transfer from GROUP_STAND_STILL to GROUP_MOVING. If the group reaches the target position
 * (i.e. the velocity is decreased to 0), the [group state](@ref NMC_GroupGetState) will transfer to GROUP_STAND_STILL. The default maximum velocity will refer to the value in
 * the input parameters. If required, the maximum velocity can be set in the API, and the specified value will be stored in the corresponding
 * parameters automatically.
 *
 * @param DevID         Device ID (DevID)
 * @param GroupIndex    Group index
 * @param[in] PEX       A pointer variable to set the target position at X-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param[in] PEY       A pointer variable to set the target position at Y-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param[in] PCXOffset A pointer variable to set the position of the circle center at X-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param[in] PCYOffset A pointer variable to set the position of the circle center at Y-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param CW_CCW        Rotation direction of arc (0=CW; 1=CCW)
 * @param[in] PMaxVel   A pointer variable to set the maximum velocity. Input NULL (0) to ignore the parameter.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * F64_T posTarX = 20.0;
 * F64_T posTarY = 0.0;
 * F64_T posCenX = 10.0;
 * F64_T posCenY = 0.0;
 * I32_T cwCcw = 1;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupCirc2C( devID, groupIndex, &posTarX, NULL, &posCenX, NULL, cwCcw, NULL );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupCirc2C( I32_T DevID, I32_T GroupIndex, _opt_null_ const F64_T *PEX, _opt_null_ const F64_T *PEY, _opt_null_ const F64_T *PCXOffset, _opt_null_ const F64_T *PCYOffset, I32_T CW_CCW, _opt_null_ const F64_T *PMaxVel );
/*!
 * @brief Enable the group arc interpolation motion on the XY plane from the current position to the target position in the Cartesian coordinate
 * system (pass-through method). The [group state](@ref NMC_GroupGetState) will transfer from GROUP_STAND_STILL to GROUP_MOVING. If the group reaches
 * the target position (i.e. the velocity is decreased to 0), the [group state](@ref NMC_GroupGetState) will transfer to GROUP_STAND_STILL. The
 * default maximum velocity will refer to the value in the input parameters. If required, the maximum velocity can be set in the API, and the
 * specified value will be stored in the corresponding parameters automatically.
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group index
 * @param[in] PEX     A pointer variable to set the target position at X-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param[in] PEY     A pointer variable to set the target position at Y-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param[in] PBX     A pointer variable to set the pass-through point at X-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param[in] PBY     A pointer variable to set the pass-through point at Y-axis. Input NULL (0) to ignore the parameter (not to move).
 * @param[in] PMaxVel A pointer variable to set the maximum velocity. Input NULL (0) to ignore the parameter.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * F64_T posTarX = 20.0;
 * F64_T posTarY = 20.0;
 * F64_T posBorX = 0.0;
 * F64_T posBorY = 20.0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupCirc2B( devID, groupIndex, &posTarX, &posTarY, &posBorX, &posBorY, NULL );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupCirc2B( I32_T DevID, I32_T GroupIndex, _opt_null_ const F64_T *PEX, _opt_null_ const F64_T *PEY, _opt_null_ const F64_T *PBX, _opt_null_ const F64_T *PBY, _opt_null_ const F64_T *PMaxVel );
RTN_ERR FNTYPE NMC_GroupCirc2BEx( I32_T DevID, I32_T GroupIndex, _opt_null_ const F64_T *PEX, _opt_null_ const F64_T *PEY, _opt_null_ const F64_T *PBX, _opt_null_ const F64_T *PBY, _opt_null_ const F64_T *PAngleDeg, _opt_null_ const F64_T *PMaxVel );
/*!
 *  @}
 */

// 3D cartesian space (MCS,PCS) interpolation with orientation control
/*! \addtogroup Group_3D_Motion
 *  Group 3D Line or Arc Interpolation Motion Functions
 *  @todo Add description to NMC_GroupCircBEx function
 *  @{
 */
/*!
 * @brief Enable the group line interpolation motion from the current position to the target position in the Cartesian space. The
 * [group state](@ref NMC_GroupGetState) will transfer from GROUP_STAND_STILL to GROUP_MOVING. If the group reaches the target position (i.e. the
 * velocity is decreased to 0), the [group state](@ref NMC_GroupGetState) will transfer to GROUP_STAND_STILL.
 *
 * @param DevID         Device ID (DevID)
 * @param GroupIndex    Group index
 * @param CartAxisMask  The mask is specified to execute the motion in the Cartesian space. Please refer to the below table.
 * @param[in] PCartPos  A pointer variable to set the target position
 * @param[in] PMaxVel   A pointer variable to set the maximum velocity. Input NULL (0) to ignore the parameter.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * | Cartesian Coordinate Axis     | V         | U         | C         | B         | A         | Z         | Y         | X         |
 * | :----:                        | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    |
 * | Bit index                     | 7         | 6         | 5         | 4         | 3         | 2         | 1         | 0         |
 * | The power is the index of bit | \f$2^7\f$ | \f$2^6\f$ | \f$2^5\f$ | \f$2^4\f$ | \f$2^3\f$ | \f$2^2\f$ | \f$2^1\f$ | \f$2^0\f$ |
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T cartAxesMask = 13; // Move the X-, Z- and A-axis
 * Pos_T targetPos = { 10, 20, 30, 40, 50, 60, 70 };
 * RTN_ERR ret = 0;
 * ret = NMC_GroupLine( devID, groupIndex, cartAxesMask, &targetPos, NULL );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupLine(  I32_T DevID, I32_T GroupIndex, I32_T CartAxisMask, const Pos_T *PCartPos, _opt_null_ const F64_T *PMaxVel );
/*!
 * @brief Enable the group arc interpolation motion from the current position to the target position in the Cartesian space (radius method). The
 * [group state](@ref NMC_GroupGetState) will transfer from GROUP_STAND_STILL to GROUP_MOVING. If the group reaches the target position (i.e. the
 * velocity is decreased to 0), the [group state](@ref NMC_GroupGetState) will transfer to GROUP_STAND_STILL.
 * The path algorithm of the arc motion (radius method) is developed based on the PLCopen specification.
 * Please pay attention to the following items:
 *
 * + The starting point of normal vector of the circle plane is the origin in the Cartesian space coordinate system. The unit vector cannot be input.<br>
 * + The vector formed by the starting point and the end point must be perpendicular to the normal vector of the circle plane. Otherwise, an error code will be returned.<br>
 * + The path developed based on the radius method can be divided to the larger radian path and the small radian path, and one of the paths shall be selected. They shall be determined by the sign of the radius. That is, the positive sign indicates the small radian path, and the negative sign indicates the larger radian path.<br>
 * + If the arc is a 2D path, the normal vector of the circle plane is dispensable to set, but the rotation direction (CW_CCW) shall be set because the right-hand rule will be used in the XY-, YZ- or ZX-plane.<br>
 * + If the arc is a 3D path, the rotation direction (CW_CCW) shall not be referred because the 3D path cannot be determined based on the right-hand rule.<br>
 *
 * ![](images/GroupCircR.png)
 *
 * @param DevID             Device ID (DevID)
 * @param GroupIndex        Group index
 * @param CartAxisMask      The mask is specified to execute the motion in the Cartesian space. Please refer to the below table.
 * @param[in] PCartPos      A pointer variable to set the target position
 * @param[in] PNormalVector A pointer variable to set the normal vector of the circle plane
 * @param Radius            Radius of arc (negative value indicates the larger radian path).
 * @param CW_CCW            Rotation direction of arc (0=CW; 1=CCW)
 * @param[in] PMaxVel       A pointer variable to set the maximum velocity. Input NULL (0) to ignore the parameter.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * | Cartesian Coordinate Axis     | V         | U         | C         | B         | A         | Z         | Y         | X         |
 * | :----:                        | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    |
 * | Bit index                     | 7         | 6         | 5         | 4         | 3         | 2         | 1         | 0         |
 * | The power is the index of bit | \f$2^7\f$ | \f$2^6\f$ | \f$2^5\f$ | \f$2^4\f$ | \f$2^3\f$ | \f$2^2\f$ | \f$2^1\f$ | \f$2^0\f$ |
 *
 * The usage of the mask in the Cartesian space coordinate system (CartAxesMask) is described as follows: <br>
 * If the group axes to be moved are the X-, Z- and A-axis, the GroupAxesIdxMask is \f$2^0\f$ + \f$2^2\f$ + \f$2^3\f$ = 13.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T cartAxesMask = 3; // Move the X- and Y-axis
 * Pos_T targetPos = { 50, 50, 0, 0, 0, 0, 0 };
 * Xyz_T normalVec = { 0, 0, 50 };
 * F64_T radius = 50.0;
 * I32_T cwCcw = 1;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupCircR( devID, groupIndex, cartAxesMask, &targetPos, &normalVec, radius, cwCcw, NULL );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupCircR( I32_T DevID, I32_T GroupIndex, I32_T CartAxisMask, const Pos_T *PCartPos, const Xyz_T *PNormalVector, F64_T Radius, I32_T CW_CCW, _opt_null_ const F64_T *PMaxVel );
/*!
 * @brief Enable the group arc interpolation motion from the current position to the target position in the Cartesian space (circle center method). The
 * [group state](@ref NMC_GroupGetState) will transfer from GROUP_STAND_STILL to GROUP_MOVING. If the group reaches the target position (i.e. the
 * velocity is decreased to 0), the [group state](@ref NMC_GroupGetState) will transfer to GROUP_STAND_STILL.
 * The path algorithm of the arc motion (circle center method) is developed based on the PLCopen specification.
 * Please pay attention to the following items:
 *
 * + The path developed based on the circle center method can be divided to the larger radian path and the small radian path, and one of the paths
 * shall be selected. They shall be determined by the rotation direction (CW_CCW). That is, the CW indicates the small radian path, and the CCW
 * indicates the larger radian path.
 * + If the arc is a 2D path, the path can be determined based on the rotation direction (CW_CCW) because the right-hand rule will be used in the XY-, YZ- or ZX-plane.
 *
 * ![](images/GroupCircC.png)
 *
 * @param DevID         Device ID (DevID)
 * @param GroupIndex    Group index
 * @param CartAxisMask  The mask is specified to execute the motion in the Cartesian space. Please refer to the below table.
 * @param[in] PCartPos  A pointer variable to set the target position
 * @param CenOfsMask    The mask of the circle center in the Cartesian space. Please refer to the below table.
 * @param[in] PCenOfs   A pointer variable to set the position of the circle center
 * @param CW_CCW        Rotation direction of arc (0=CW; 1=CCW)
 * @param[in] PMaxVel   A pointer variable to set the maximum. Input NULL (0) to ignore the parameter.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * | Cartesian Coordinate Axis     | V         | U         | C         | B         | A         | Z         | Y         | X         |
 * | :----:                        | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    |
 * | Bit index                     | 7         | 6         | 5         | 4         | 3         | 2         | 1         | 0         |
 * | The power is the index of bit | \f$2^7\f$ | \f$2^6\f$ | \f$2^5\f$ | \f$2^4\f$ | \f$2^3\f$ | \f$2^2\f$ | \f$2^1\f$ | \f$2^0\f$ |
 *
 * The usage of the mask in the Cartesian space coordinate system (CartAxesMask) is described as follows: <br>
 * If the group axes to be moved are the X-, Z- and A-axis, the GroupAxesIdxMask is \f$2^0\f$ + \f$2^2\f$ + \f$2^3\f$ = 13.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T cartAxesMask = 7; // Move the X-, Y- and Z-axis
 * Pos_T targetPos = { 50, 50, 0, 0, 0, 0, 0 };
 * I32_T cenOfsMask = 7; // Move the X-, Y- and Z-axis
 * Xyz_T cenOfs = { 50, 0, 50 };
 * I32_T cwCcw = 1;
 * RTN_ERR ret = 0;
 *
 * ret = NMC_GroupCircC( devID, groupIndex, cartAxesMask, &targetPos, cenOfsMask, &cenOfs, cwCcw, NULL );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupCircC( I32_T DevID, I32_T GroupIndex, I32_T CartAxisMask, const Pos_T *PCartPos, I32_T CenOfsMask, const Xyz_T *PCenOfs, I32_T CW_CCW, _opt_null_ const F64_T *PMaxVel );
/*!
 * @brief Enable the group arc interpolation motion from the current position to the target position in the Cartesian space (pass-through method). The
 * [group state](@ref NMC_GroupGetState) will transfer from GROUP_STAND_STILL to GROUP_MOVING. If the group reaches the target position (i.e. the
 * velocity is decreased to 0), the group state will transfer to GROUP_STAND_STILL.
 * The path algorithm of the arc motion (pass-through method) is developed based on the PLCopen specification.
 * Please refer to the below figure for the coordination.
 *
 * ![](images/GroupCircB.png)
 *
 * @param DevID         Device ID (DevID)
 * @param GroupIndex    Group index
 * @param CartAxisMask  The mask is specified to execute the motion in the Cartesian space. Please refer to the below table.
 * @param[in] PCartPos  A pointer variable to set the target position
 * @param BorPosMask    The mask of the pass-through point in the Cartesian space. Please refer to the below table.
 * @param[in] PBorPoint A pointer variable to set the pass-through point
 * @param[in] PMaxVel   A pointer variable to set the maximum. Input NULL (0) to ignore the parameter.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * | Cartesian Coordinate Axis     | V         | U         | C         | B         | A         | Z         | Y         | X         |
 * | :----:                        | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    | :----:    |
 * | Bit index                     | 7         | 6         | 5         | 4         | 3         | 2         | 1         | 0         |
 * | The power is the index of bit | \f$2^7\f$ | \f$2^6\f$ | \f$2^5\f$ | \f$2^4\f$ | \f$2^3\f$ | \f$2^2\f$ | \f$2^1\f$ | \f$2^0\f$ |
 *
 * The usage of the mask in the Cartesian space coordinate system (CartAxesMask) is described as follows: <br>
 * If the group axes to be moved are the X-, Z- and A-axis, the GroupAxesIdxMask is \f$2^0\f$ + \f$2^2\f$ + \f$2^3\f$ = 13.
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * I32_T cartAxesMask = 7; // Move the X-, Y- and Z-axis
 * Pos_T targetPos = { 50, 50, 0, 0, 0, 0, 0 };
 * I32_T borPosMask = 7; // Move the X-, Y- and Z-axis
 * Xyz_T borPoint = { 50, 0, 50 };
 * RTN_ERR ret = 0;
 * ret = NMC_GroupCircB( devID, groupIndex, cartAxesMask, targetPos, borPosMask, borPoint, NULL );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupCircB( I32_T DevID, I32_T GroupIndex, I32_T CartAxisMask, const Pos_T *PCartPos, I32_T BorPosMask, const Xyz_T *PBorPoint, _opt_null_ const F64_T *PMaxVel );
RTN_ERR FNTYPE NMC_GroupCircBEx( I32_T DevID, I32_T GroupIndex, I32_T CartAxisMask, const Pos_T *PCartPos, I32_T BorPosMask, const Xyz_T *PBorPoint, _opt_null_ const F64_T *PAngleDeg, _opt_null_ const F64_T *PMaxVel );
/*!
 *  @}
 */

// Tool (TCP) calibration
/*! \addtogroup Group_Tool_Calibration
 *  Fuctions for the group to calibrate its tool coordination
 *  @{
 */
/*!
 * @brief ool calibration - TCP translation method
 *
 * @param PMcsKinP1               The first step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinP2               The second step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinP3               The third step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinP4               The forth step position, TCP must (as far as possible) fall in the reference position
 * @param[out] PRetToolCoordTrans Return setting of Tool coordinate convertion
 * @param[out] PRetTolerance      Return tolerance
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_ToolCalib_4p       ( const Pos_T *PMcsKinP1, const Pos_T *PMcsKinP2, const Pos_T *PMcsKinP3, const Pos_T *PMcsKinP4    , CoordTrans_T *PRetToolCoordTrans, F64_T *PRetTolerance );
/*!
 * @brief Tool calibration - TCP translation with Z-direction setting method
 *
 * @param PMcsKinP1               The first step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinP2               The second step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinP3               The third step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinP4ZDir           The fourth step position, the positive direction of Z axis of TCP needs to indicate negative direction of Z axis of MCS
 * @param[out] PRetToolCoordTrans Return setting of Tool coordinate convertion
 * @param[out] PRetTolerance      Return tolerance
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_ToolCalib_4pWithZ  ( const Pos_T *PMcsKinP1, const Pos_T *PMcsKinP2, const Pos_T *PMcsKinP3, const Pos_T *PMcsKinP4ZDir, CoordTrans_T *PRetToolCoordTrans, F64_T *PRetTolerance );
/*!
 * @brief Tool calibration - TCP translation with orientation setting method
 *
 * @param PMcsKinP1               The first step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinP2               The second step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinP3               The third step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinP4               The forth step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinMinusZAxisPt     The fifth step position, reference position must fall in negative direction of Z axis of TCP
 * @param PMcsKinYZPlanPt         The sixth step position, reference position must fall in positive direction of Y axis of TCP
 * @param[out] PRetToolCoordTrans Return setting of Tool coordinate convertion
 * @param[out] PRetTolerance      Return tolerance
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_ToolCalib_4pWithOri( const Pos_T *PMcsKinP1, const Pos_T *PMcsKinP2, const Pos_T *PMcsKinP3, const Pos_T *PMcsKinP4,  const Pos_T *PMcsKinMinusZAxisPt, const Pos_T *PMcsKinYZPlanPt, CoordTrans_T *PRetToolCoordTrans, F64_T *PRetTolerance );
/*!
 * @brief Tool calibration - Orientation setting method
 *
 * @param PMcsKinOrg              The first step position, TCP must (as far as possible) fall in the reference position
 * @param PMcsKinMinusZAxisPt     The second step position, reference position must fall in negative direction of Z axis of TCP
 * @param PMcsKinYZPt             The third step position, reference position must fall in positive direction of Y axis of TCP
 * @param[out] PRetToolCoordTrans Return setting of Tool coordinate convertion(Only modified the orientation transformation paramter)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_ToolCalib_Ori      ( const Pos_T *PMcsKinOrg, const Pos_T *PMcsKinMinusZAxisPt, const Pos_T *PMcsKinYZPt, CoordTrans_T *PRetToolCoordTrans );
/*!
 *  @}
 */

// Base calibration
/*! \addtogroup Group_Base_Calibration
 *  Fuctions for the group to calibration its base coordination
 *  @{
 */
/*!
 * @brief Base teaching - 1 point method
 *
 * @param PRefBaseP1          The position used in the first step.
 * @param PRetBaseCoordTrans  Return the relationship respected to reference coordinate convertion.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_BaseCalib_1p( const Pos_T *PRefBaseP1, CoordTrans_T *PRetBaseCoordTrans );
/*!
 * @brief Base teaching - 2 points method
 *
 * @param PRefBaseP1          The position used in the first step.
 * @param PRefBaseP2          The position used in the second step.
 * @param PRetBaseCoordTrans  Return the relationship respected to reference coordinate convertion.
 *
 * @return Return an error code. <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_BaseCalib_2p( const Pos_T *PRefBaseP1, const Pos_T *PRefBaseP2, CoordTrans_T *PRetBaseCoordTrans );
/*!
 * @brief Base teaching - 3 point method
 *
 * @param PRefBaseP1          The position used in the first step.
 * @param PRefBaseP2          The position used in the second step.
 * @param PRefBaseP3          The position used in the third step.
 * @param PRetBaseCoordTrans  Return the relationship respected to reference coordinate convertion.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_BaseCalib_3p( const Pos_T *PRefBaseP1, const Pos_T *PRefBaseP2, const Pos_T *PRefBaseP3, CoordTrans_T *PRetBaseCoordTrans );
/*!
 *  @}
 */
/*!
 *  @}
 */


/*! \addtogroup System_API
 *  @{
 */
// Message output
/*! \addtogroup System_Information
 *  Fuctions for outputing messages of system information
 *  @{
 */
/*!
 * @brief Read system message queue.
 *
 * @param[out] PRetMsg Data structure of system information which can be set to NULL to remove the message from the message queue. Note that if the
 * parameter is not NULL, the "sizeOfStruct" member variable in the structure must be initialized before calling NMC_MessagePopFirst(). See the
 * sample program below.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 * If there is no system message, the function will return ERR_NEXMOTION_QUEUE_EMPTY.
 *
 * \b Usage: <br>
 * NMC_MessagePopFirst() will read and remove the first (oldest) message from the message queue in order.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret;
 * NmcMsg_T msg;
 * msg.sizeOfStruct = sizeof(msg);
 * do{
 *   ret = NMC_MessagePopFirst( &msg );
 *   if( ret == ERR_NEXMOTION_SUCCESS )
 *   {
 *     printf( " Msg:Type=%d, code=%d, src=%s, text=%s\n", msg.type, msg.code, msg.source, msg.text );
 *   }
 * }while( ret == ERR_NEXMOTION_SUCCESS );
 * @endcode
 *
 * \b Reference: <br>
 * NMC_MessageOutputEnable()
 */
RTN_ERR FNTYPE NMC_MessagePopFirst( _opt_null_ NmcMsg_T *PRetMsg );
/*!
 * @brief Transfer a copy of message to MS Windows system message.
 *
 * @param Enable  False (0): not to transfer, True (1): transfer
 *
 * @return None.
 *
 * \b Usage: <br>
 * After NMC_MessageOutputEnable(True) is called, the system message will be transferred to MS Windows system message.
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * NMC_MessagePopFirst()
 */
void    FNTYPE NMC_MessageOutputEnable( BOOL_T Enable );
/*!
 *  @}
 */

// API debugging helper
/*! \addtogroup Debug_Trace
 *  Debug trace functions
 *  @{
 */
/*!
 * @brief Set API trace mode.
 *
 * @param TraceMode <br>
 *  0: Turn off the trace function and do not output anything <br>
 *  1: Output the APIs with errors only <br>
 *  2: Output all APIs <br>
 *
 * @return None.
 *
 * \b Usage: <br>
 * Please refer to the section, [Function Trace](@ref API_Trace).
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * None
 */
void    FNTYPE NMC_DebugSetTraceMode( I32_T TraceMode );
/*!
 * @brief Set the data structure index for the hook function.
 *
 * @param[in] PHookUserData [Input] A pointer variable to set a variable or a data structure specified by user
 *
 * @return None.
 *
 * \b Usage: <br>
 * Please refer to the section, [Function Trace](@ref API_Trace).
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * None
 */
void    FNTYPE NMC_DebugSetHookData( void *PHookUserData );
/*!
 * @brief Set the hook function.
 *
 * @param PFHookFuncPtr A function pointer to set the hook function
 *
 * @return None.
 *
 * \b Usage: <br>
 * Please refer to the section, [Function Trace](@ref API_Trace).
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * None
 */
void    FNTYPE NMC_DebugSetHookFunction( PF_NmcHookAPI PFHookFuncPtr );
/*!
 * @brief Read the API address.
 *
 * @param[in] PApiName [Input] The function name of a NexMotion API
 *
 * @return const void*:  Return the function pointer to set the NexMotion API.
 *
 * \b Usage: <br>
 * Please refer to the section, [Function Trace](@ref API_Trace).
 *
 * \b Examples: <br>
 * @code{.h}
 * @endcode
 *
 * \b Reference: <br>
 * None
 */
const void* FNTYPE NMC_DebugGetApiAddress( const char *PApiName );
/*!
 *  @}
 */
/*!
 *  @}
 */


// Obsolete API
/*! \addtogroup Deprecated_API
 * Deprecated functions
 *  @{
 */
/*!
 * @brief Axis function for setting velocity ratio
 *
 * @param DevID           Device ID (DevID)
 * @param AxisIndex       Axis index
 * @param[in] Percentage  [Input] Velocity percentage
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. Whether the axis is in motion, the function can be called to set the velocity percentage. The default value of the velocity percentage is 1.0.
 * 2. The input velocity percentage shall be more than or equal to 0, and less than 1.
 * 3. If the axis is in the [axis state](@ref NMC_AxisGetState) AXIS _STATE_STOPPING, AXIS_STATE_STOPPED or AXIS_STATE_ERROR, the function will return the error code.
 * 4. If the axis is homing, the function will return the error code.
 * 5. After the function is called to set the velocity percentage, the target velocity of the later axis motion shall be the input maximum velocity multiplied by such velocity percentage.
 * 6. If the axis is executing the point-to-point motion or the JOG motion and the function is called, the input velocity percentage will change the target velocity of the current motion.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * F64_T maxVel = 50.0;
 * ret = NMC_AxisJog( 0, 0, 1, &maxVel ); // Enable axis JOG motion at target velocity 50.
 * ret = NMC_AxisSetVelRatio( 0, 0, 0.5 ); // Change velocity percentage to target velocity 25.
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_AxisSetVelRatio( I32_T DevID, I32_T AxisIndex, F64_T Percentage );
/*!
 * @brief Axis function for getting velocity ratio
 *
 * @param DevID             Device ID (DevID)
 * @param AxisIndex         Axis index
 * @param[out] PPercentage  Return the velocity percentage.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function is called to get the current velocity percentage.
 *
 * \b Examples: <br>
 * @code{.h}
 * RTN_ERR ret = 0;
 * F64_T velRatio = 0.0;
 * ret = NMC_AxisGetVelRatio( 0, 0, &velRatio );
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_AxisGetVelRatio( I32_T DevID, I32_T AxisIndex, F64_T *PPercentage );

/*!
 * @brief Set the velocity percentage of a group from 0.0 ~ 100.0%.
 * @todo check velocity percentage maximum value (100 or 1000).
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group index
 * @param Percentage  Velocity percentage to be set (0% ~ 100.0%)
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * F64_T percentage = 100.0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupSetVelRatio( devID, groupIndex, percentage );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupSetVelRatio( I32_T DevID, I32_T GroupIndex, F64_T Percentage );
/*!
 * @brief Get the velocity percentage of a group from 0.0 ~ 100.0%.
 *
 * @param DevID               Device ID (DevID)
 * @param GroupIndex          Group index
 * @param[out] PRetPercentage [Input] A pointer variable, [Output] Velocity percentage.
 *
 * @return Return an [error code](@ref Error_code). <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 *
 * \b Examples: <br>
 * @code{.h}
 * I32_T devID = 0;
 * I32_T groupIndex = 0;
 * F64_T percentage = 0.0;
 * RTN_ERR ret = 0;
 * ret = NMC_GroupGetVelRatio( devID, groupIndex, &percentage );
 * if( ret != 0 ) return ret;
 * @endcode
 *
 * \b Reference: <br>
 * None.
 */
RTN_ERR FNTYPE NMC_GroupGetVelRatio( I32_T DevID, I32_T GroupIndex, F64_T *PRetPercentage );
/*!
 *  @}
 */

#ifdef __cplusplus
}
#endif

#endif
