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
 * @param PRetMajor [Input] A pointer variable, [Output] The major version number. Input NULL(0) can ignore the parameter.
 * @param PRetMinor [Input] A pointer variable, [Output] The minor version number. Input NULL(0) can ignore the parameter.
 * @param PRetStage [Input] A pointer variable, [Output] The stage of version number. Input NULL(0) can ignore the parameter. The return value 1 ~ 4 indicate the trial versions, and the 5 indicates the official release version.
 * @param PRetBuild [Input] A pointer variable, [Output] The build of version number. Input NULL(0) can ignore the parameter.
 *
 * @return The version number will be returned with the data type of I32_T. The return value means: Version = (Major×10,000,000) + (Minor×100,000) + (Stage×10,000) + Build
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
 * \b Examples:
 * @code{.h}
 * char versionString[32];
 * NMC_GetLibVersionString( versionString, 32 );
 * printf( "Library version = (%s) \n", versionString );
 * @endcode
 */
void    FNTYPE NMC_GetLibVersionString( char *PRetVersionString, U32_T StringSize );
/*!
 * @brief Return the error code description in the format of a C string.
 *
 * @param ErrorCode     The error code to be inquired
 * @param PRetErrorDesc A char array which is 512 characters at least
 * @param StringSize    The size of input char array
 *
 * @return The error code description. It will be NULL if the ErrorCode is undefined
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
 * @param DevType The specified device type. 0: Simulator, 1: EtherCAT
 * @param DevIndex The specified index of device which is set to 0
 * @param PRetDevID [Output] The device ID (DevID) after the function is called successfully
 *
 * @return Return an error code.
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @param WaitMs    Waiting time for device open up (unit: ms). It can be set to the NMC_WAIT_TIME_INFINITE (0xFFFFFFFF) to wait for the completion of open up.
 * @param PRetDevID [Output] The device ID (DevID) after the function is called successfully.
 *
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 */
RTN_ERR FNTYPE NMC_DeviceShutdownRequest( I32_T DevID );
/*!
 * @brief Wait for device shut down (Blocking call).
 *
 * @param DevID   The device ID of the machine that request to be shutdown.
 * @param WaitMs  Waiting time for device open up (unit: ms). It can be set to the NMC_WAIT_TIME_INFINITE (0xFFFFFFFF) to wait for the completion of open up.
 *
 * @return Return an error code. <br>
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
RTN_ERR FNTYPE NMC_DeviceWatchdogTimerEnable( I32_T DevID, U32_T TimeoutMs, I32_T Mode );
RTN_ERR FNTYPE NMC_DeviceWatchdogTimerDisable( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceWatchdogTimerReset( I32_T DevID );

// Advanced controller initialization APIs
/*! \addtogroup Advanced_Device_Open_Shutdown
 *  Advanced Device Open up and Shut Down
 *  @{
 */
/*!
 * @brief Create the device ID.
 *
 * @param DevType   The specified device type. 0: Simulator, 1: EtherCAT.
 * @param DevIndex  The specified index of device which is set to 0.
 * @param PRetDevID [Output] The device ID (DevID) after the function is called successfully.
 *
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * The function will load the device configurations in accordance with the file, `NexMotionLibConfig.ini`.
 * The file, `NexMotionLibConfig.ini`, is saved in the default path, `C:\NEXCOBOT`. Users must not create the file, nor modify the file name or content in order to avoid the loading error. NMC_DeviceLoadIniConfig() will search the file, `NexMotionLibConfig.ini`, in the following path in order:
 * ```
 * NexMotion.dll folder
 * C:\NEXCOBOT
 * C:\Windows\System32
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @param DevID         Device ID (DevID)
 * @param ParamNum      Parameter Number
 * @param SubIndex      Parameter Sub-index
 * @param PRetParaValue [Output] The value to be returned after the function is called successfully.
 *
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
RTN_ERR FNTYPE NMC_GetInputMemorySize ( I32_T DevID, U32_T *PRetSizeByte );
RTN_ERR FNTYPE NMC_GetOutputMemorySize( I32_T DevID, U32_T *PRetSizeByte );
RTN_ERR FNTYPE NMC_ReadInputMemory( I32_T DevID, U32_T OffsetByte, U32_T SizeByte, void *PRetValue );
RTN_ERR FNTYPE NMC_ReadOutputMemory( I32_T DevID, U32_T OffsetByte, U32_T SizeByte, void *PRetValue );
RTN_ERR FNTYPE NMC_WriteOutputMemory( I32_T DevID, U32_T OffsetByte, U32_T SizeByte, const void *PValue );
RTN_ERR FNTYPE NMC_ReadInputBit( I32_T DevID, U32_T OffsetByte, U32_T BitIndex, BOOL_T *PRetBitValue );
RTN_ERR FNTYPE NMC_ReadInputI8( I32_T DevID, U32_T OffsetByte, I8_T *PRetI8Value );
RTN_ERR FNTYPE NMC_ReadInputI16( I32_T DevID, U32_T OffsetByte, I16_T *PRetI16Value );
RTN_ERR FNTYPE NMC_ReadInputI32( I32_T DevID, U32_T OffsetByte, I32_T *PRetI32Value );
RTN_ERR FNTYPE NMC_ReadOutputBit( I32_T DevID, U32_T OffsetByte, U32_T BitIndex, BOOL_T *PRetBitValue );
RTN_ERR FNTYPE NMC_ReadOutputI8( I32_T DevID, U32_T OffsetByte, I8_T *PRetI8Value );
RTN_ERR FNTYPE NMC_ReadOutputI16( I32_T DevID, U32_T OffsetByte, I16_T *PRetI16Value );
RTN_ERR FNTYPE NMC_ReadOutputI32( I32_T DevID, U32_T OffsetByte, I32_T *PRetI32Value );
RTN_ERR FNTYPE NMC_WriteOutputBit( I32_T DevID, U32_T OffsetByte, U32_T BitIndex, BOOL_T BitValue );
RTN_ERR FNTYPE NMC_WriteOutputI8( I32_T DevID, U32_T OffsetByte, I8_T I8Value );
RTN_ERR FNTYPE NMC_WriteOutputI16( I32_T DevID, U32_T OffsetByte, I16_T I16Value );
RTN_ERR FNTYPE NMC_WriteOutputI32( I32_T DevID, U32_T OffsetByte, I32_T I32Value );

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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 *  @{
 */
RTN_ERR FNTYPE NMC_DeviceResetStateAll( I32_T DevID );
/*!
 * @brief Enable all axes and groups in the system.
 *
 * @param DevID Device ID (DevID)
 *
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 *  @{
 */
// Axis parameter setting APIs
RTN_ERR FNTYPE NMC_AxisSetParamI32( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, I32_T ParaValueI32 );
RTN_ERR FNTYPE NMC_AxisGetParamI32( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, I32_T *PRetParaValueI32 );
RTN_ERR FNTYPE NMC_AxisSetParamF64( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, F64_T ParaValueF64 );
RTN_ERR FNTYPE NMC_AxisGetParamF64( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, F64_T *PRetParaValueF64 );

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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @param PRetAlmCode [Output] The value of alarm code.
 *
 * @return Return an error code. <br>
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
RTN_ERR FNTYPE NMC_AxisGetCommandPos( I32_T DevID, I32_T AxisIndex, F64_T *PRetCmdPos );
RTN_ERR FNTYPE NMC_AxisGetActualPos( I32_T DevID, I32_T AxisIndex, F64_T *PRetActPos );
RTN_ERR FNTYPE NMC_AxisGetCommandVel( I32_T DevID, I32_T AxisIndex, F64_T *PRetCmdVel );
RTN_ERR FNTYPE NMC_AxisGetActualVel( I32_T DevID, I32_T AxisIndex, F64_T *PRetActVel );
RTN_ERR FNTYPE NMC_AxisGetMotionBuffSpace(  I32_T DevID, I32_T AxisIndex, I32_T *PRetFreeSpace );

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
 * @return Return an error code. <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * 1. The function can be called for point-to-point motion if the axis is excitation.
 * 2. If the axis is homing, the function will return the error code.
 * 3. If the axis is in the axis state_STATE_STOPPING, AXIS_STATE_STOPPED or AXIS_STATE_ERROR, the function will return the error code. After NMC_AxisResetState() is called to reset the axis to normal excitation (AXIS_STATE_STAND_STILL), the function can be called for point-to-point motion successfully.
 * 4. If the axis is executing other motions, it will execute the corresponding behavior depended on the axis parameter AXP_BUFF_PARAM after the function is called.
 * 5. The function can be called to enable the point-to-point motion. After the motion completely, the axis will move to the input target position. If the axis parameter 0x30 (Absolute or relative programming) is set to 1, the target position and the relative distance from the current position shall be input in the function. If the relative distance is set to 0, the target position will be set as an absolute position.
 * 6. If the axis is excuting the point-to-point motion, the axis state will transfer to AXIS_STATE_DISCRETE_MOTION. After the axis moves to the target position and there is no successive motion, the bit 9 of axis status will become to 1, and the axis will transfer to the normal excitation (AXIS_STATE_STAND_STILL).
 * 7. The drive will plan the velocity curve depended on the axis parameters, AXP_PROF_TYPE, AXP_ACC, AXP_DEC and AXP_JERK.
 * 8. The maximum velocity can be input with the pointer variable, PMaxVel. Then the corresponding axis parameter AXP_VM will be modified to the input value, and the velocity plan will be performed accordingly.
 * 9. If the pointer variable, PMaxVel, is set to 0, the drive will perform the velocity plan based on the axis parameter AXP_VM as the target velocity.
 * 10. If the axis state is AXIS_STATE_STAND_STILL, the function will enable the point-to-point motion immediately after called whether the content of axis parameter AXP_BUFF_PARAM.
 * 11. After the function is called and if the axis state is AXIS_STATE_WAIT_SYNC and the axis parameter AXP_BUFF_PARAM is aborting, the motions stored in the motion queue will be removed. Then the point-to-point motion will be stored into the motion queue and wait for trigger signal.
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
 * @return Return an error code. <br>
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
RTN_ERR FNTYPE NMC_AxisSetHomePos( I32_T DevID, I32_T AxisIndex, F64_T HomePos );
/*!
 * @brief Drive an axis to move to the origin (by driver).
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis Index
 *
 * @return Return an error code. <br>
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
/*! \addtogroup Axis_Motion_Status
 *  Axis Motion Status Functions
 *  @{
 */
/*!
 * @brief The function can be called to halt the axis motion.
 *
 * @param DevID     Device ID (DevID)
 * @param AxisIndex Axis index
 *
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @param PRetParaValueI32  [Input] A pointer variable, [Output] Value of the parameter
 *
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @param PRetParaValueF64  [Output] Value to be returned (double precision float)
 *
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @param DevID             Device ID (Dev ID)
 * @param GroupIndex        Group index
 * @param GroupAxisIndex    Group axis index
 * @param ParamNum          Parameter number
 * @param SubIndex          Parameter sub-index
 * @param PRetParaValueI32  [Output] Value to be returned (signed integer)
 *
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @param DevID             Device ID (Dev ID)
 * @param GroupIndex        Group index
 * @param GroupAxisIndex    Group axis index
 * @param ParamNum          Parameter number
 * @param SubIndex          Parameter sub-index
 * @param PRetParaValueF64  [Output] Value to be returned (double precision float)
 *
 * @return Return an error code. <br>
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
RTN_ERR FNTYPE NMC_GroupEnable( I32_T DevID, I32_T GroupIndex );
RTN_ERR FNTYPE NMC_GroupDisable( I32_T DevID, I32_T GroupIndex );
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
 * @param PRetState   [Input] A pointer variable, [Output] Group state
 *
 * @return Return an error code. <br>
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
RTN_ERR FNTYPE NMC_GroupResetState( I32_T DevID, I32_T GroupIndex );
RTN_ERR FNTYPE NMC_GroupResetDriveAlm( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex );
/*!
 * @brief Reset all group servo alarms.
 *
 * @param DevID       Device ID (DevID)
 * @param GroupIndex  Group Index
 *
 * @return Return an error code. <br>
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
RTN_ERR FNTYPE NMC_GroupGetDriveAlmCode( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T *PRetAlmCode );
/*!
 *  @}
 */

// Group velocity ratio setting APIs
RTN_ERR FNTYPE NMC_GroupSetSpeedRatio( I32_T DevID, I32_T GroupIndex, F64_T Percentage );
RTN_ERR FNTYPE NMC_GroupGetSpeedRatio( I32_T DevID, I32_T GroupIndex, F64_T *PRetPercentage );

// Group axis point to point motion in ACS
RTN_ERR FNTYPE NMC_GroupPtpAcs( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, F64_T AcsPos, _opt_null_ const F64_T *PAcsMaxVel );
RTN_ERR FNTYPE NMC_GroupPtpAcsAll( I32_T DevID, I32_T GroupIndex, I32_T GroupAxesIdxMask, const Pos_T *PAcsPos );

// Group axis jog motion in ACS
RTN_ERR FNTYPE NMC_GroupJogAcs( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T Dir, _opt_null_ const F64_T *PAcsMaxVel  );

// Group axis jog motion in PCS
RTN_ERR FNTYPE NMC_GroupJogTcpFrame( I32_T DevID, I32_T GroupIndex, I32_T CartAxis, I32_T Dir, _opt_null_ const F64_T *PMaxVel  );
RTN_ERR FNTYPE NMC_GroupJogPcsFrame( I32_T DevID, I32_T GroupIndex, I32_T CartAxis, I32_T Dir, _opt_null_ const F64_T *PMaxVel  );

// Group point to point motion in PCS
RTN_ERR FNTYPE NMC_GroupPtpCart( I32_T DevID, I32_T GroupIndex, I32_T CartAxis, F64_T CartPos );
RTN_ERR FNTYPE NMC_GroupPtpCartAll( I32_T DevID, I32_T GroupIndex, I32_T CartAxesMask, const Pos_T *PTargetPos );

// Group motion termination APIs
RTN_ERR FNTYPE NMC_GroupHalt( I32_T DevID, I32_T GroupIndex );
RTN_ERR FNTYPE NMC_GroupStop( I32_T DevID, I32_T GroupIndex );
RTN_ERR FNTYPE NMC_GroupHaltAll( I32_T DevID );
RTN_ERR FNTYPE NMC_GroupStopAll( I32_T DevID );

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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
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
 * @return Return an error code. <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * | Group Axis                    | 8     | 7      | 6      | 5      | 4      | 3      | 2      | 1      |
 * | :----:                        | :---- | :----: | :----: | :----: | :----: | :----: | :----: | :----: |
 * | Bit index                     | 7     | 6      | 5      | 4      | 3      | 2      | 1      | 0      |
 * | The power is the index of bit | 2^7   | 2^6    | 2^5    | 2^4    | 2^3    | 2^2    | 2^1    | 2^0    |
 *
 * The usage of the group axis index mask (GroupAxesIdxMask) is described as follows:
 * If the group axes to be moved are the 1st, 3rd and 8th axes, the GroupAxesIdxMask is 20 + 22 + 27 = 133.
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
 * @return Return an error code. <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 *
 * \b Usage: <br>
 * | Group Axis                    | 8     | 7      | 6      | 5      | 4      | 3      | 2      | 1      |
 * | :----:                        | :---- | :----: | :----: | :----: | :----: | :----: | :----: | :----: |
 * | Bit index                     | 7     | 6      | 5      | 4      | 3      | 2      | 1      | 0      |
 * | The power is the index of bit | 2^7   | 2^6    | 2^5    | 2^4    | 2^3    | 2^2    | 2^1    | 2^0    |
 *
 * The usage of the group axis index mask (GroupAxesIdxMask) is described as follows:
 * If the group axes to be moved are the 1st, 3rd and 8th axes, the GroupAxesIdxMask is 20 + 22 + 27 = 133.
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
RTN_ERR FNTYPE NMC_GroupLineXY( I32_T DevID, I32_T GroupIndex, _opt_null_ const F64_T *PX, _opt_null_ const F64_T *PY, const F64_T _opt_null_ *PMaxVel );
RTN_ERR FNTYPE NMC_GroupCirc2R( I32_T DevID, I32_T GroupIndex, _opt_null_ const F64_T *PEX, _opt_null_ const F64_T *PEY, F64_T Radius, I32_T CW_CCW, _opt_null_ const F64_T *PMaxVel );
RTN_ERR FNTYPE NMC_GroupCirc2C( I32_T DevID, I32_T GroupIndex, _opt_null_ const F64_T *PEX, _opt_null_ const F64_T *PEY, _opt_null_ const F64_T *PCXOffset, _opt_null_ const F64_T *PCYOffset, I32_T CW_CCW, _opt_null_ const F64_T *PMaxVel );
RTN_ERR FNTYPE NMC_GroupCirc2B( I32_T DevID, I32_T GroupIndex, _opt_null_ const F64_T *PEX, _opt_null_ const F64_T *PEY, _opt_null_ const F64_T *PBX, _opt_null_ const F64_T *PBY, _opt_null_ const F64_T *PMaxVel );
RTN_ERR FNTYPE NMC_GroupCirc2BEx( I32_T DevID, I32_T GroupIndex, _opt_null_ const F64_T *PEX, _opt_null_ const F64_T *PEY, _opt_null_ const F64_T *PBX, _opt_null_ const F64_T *PBY, _opt_null_ const F64_T *PAngleDeg, _opt_null_ const F64_T *PMaxVel );

// 3D cartesian space (MCS,PCS) interpolation with orientation control
RTN_ERR FNTYPE NMC_GroupLine(  I32_T DevID, I32_T GroupIndex, I32_T CartAxisMask, const Pos_T *PCartPos, _opt_null_ const F64_T *PMaxVel );
RTN_ERR FNTYPE NMC_GroupCircR( I32_T DevID, I32_T GroupIndex, I32_T CartAxisMask, const Pos_T *PCartPos, const Xyz_T *PNormalVector, F64_T Radius, I32_T CW_CCW, _opt_null_ const F64_T *PMaxVel );
RTN_ERR FNTYPE NMC_GroupCircC( I32_T DevID, I32_T GroupIndex, I32_T CartAxisMask, const Pos_T *PCartPos, I32_T CenOfsMask, const Xyz_T *PCenOfs, I32_T CW_CCW, _opt_null_ const F64_T *PMaxVel );
RTN_ERR FNTYPE NMC_GroupCircB( I32_T DevID, I32_T GroupIndex, I32_T CartAxisMask, const Pos_T *PCartPos, I32_T BorPosMask, const Xyz_T *PBorPoint, _opt_null_ const F64_T *PMaxVel );
RTN_ERR FNTYPE NMC_GroupCircBEx( I32_T DevID, I32_T GroupIndex, I32_T CartAxisMask, const Pos_T *PCartPos, I32_T BorPosMask, const Xyz_T *PBorPoint, _opt_null_ const F64_T *PAngleDeg, _opt_null_ const F64_T *PMaxVel );

// Tool (TCP) calibration
RTN_ERR FNTYPE NMC_ToolCalib_4p       ( const Pos_T *PMcsKinP1, const Pos_T *PMcsKinP2, const Pos_T *PMcsKinP3, const Pos_T *PMcsKinP4    , CoordTrans_T *PRetToolCoordTrans, F64_T *PRetTolerance );
RTN_ERR FNTYPE NMC_ToolCalib_4pWithZ  ( const Pos_T *PMcsKinP1, const Pos_T *PMcsKinP2, const Pos_T *PMcsKinP3, const Pos_T *PMcsKinP4ZDir, CoordTrans_T *PRetToolCoordTrans, F64_T *PRetTolerance );
RTN_ERR FNTYPE NMC_ToolCalib_4pWithOri( const Pos_T *PMcsKinP1, const Pos_T *PMcsKinP2, const Pos_T *PMcsKinP3, const Pos_T *PMcsKinP4,  const Pos_T *PMcsKinMinusZAxisPt, const Pos_T *PMcsKinYZPlanPt, CoordTrans_T *PRetToolCoordTrans, F64_T *PRetTolerance );
RTN_ERR FNTYPE NMC_ToolCalib_Ori      ( const Pos_T *PMcsKinOrg, const Pos_T *PMcsKinMinusZAxisPt, const Pos_T *PMcsKinYZPt, CoordTrans_T *PRetToolCoordTrans );

// Base calibration
RTN_ERR FNTYPE NMC_BaseCalib_1p( const Pos_T *PRefBaseP1, CoordTrans_T *PRetBaseCoordTrans );
RTN_ERR FNTYPE NMC_BaseCalib_2p( const Pos_T *PRefBaseP1, const Pos_T *PRefBaseP2, CoordTrans_T *PRetBaseCoordTrans );
RTN_ERR FNTYPE NMC_BaseCalib_3p( const Pos_T *PRefBaseP1, const Pos_T *PRefBaseP2, const Pos_T *PRefBaseP3, CoordTrans_T *PRetBaseCoordTrans );
/*!
 *  @}
 */


// Message output
RTN_ERR FNTYPE NMC_MessagePopFirst( _opt_null_ NmcMsg_T *PRetMsg );
void    FNTYPE NMC_MessageOutputEnable( BOOL_T Enable );

// API debugging helper
void    FNTYPE NMC_DebugSetTraceMode( I32_T TraceMode );
void    FNTYPE NMC_DebugSetHookData( void *PHookUserData );
void    FNTYPE NMC_DebugSetHookFunction( PF_NmcHookAPI PFHookFuncPtr );
const void* FNTYPE NMC_DebugGetApiAddress( const char *PApiName );


// Obsolete API
RTN_ERR FNTYPE NMC_AxisSetVelRatio( I32_T DevID, I32_T AxisIndex, F64_T Percentage );
RTN_ERR FNTYPE NMC_AxisGetVelRatio( I32_T DevID, I32_T AxisIndex, F64_T *PPercentage );

RTN_ERR FNTYPE NMC_GroupSetVelRatio( I32_T DevID, I32_T GroupIndex, F64_T Percentage );
RTN_ERR FNTYPE NMC_GroupGetVelRatio( I32_T DevID, I32_T GroupIndex, F64_T *PRetPercentage );

#ifdef __cplusplus
}
#endif

#endif
