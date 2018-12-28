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


// Version and error read APIs
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


// Controller initialization APIs
/**
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
/**
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
/**
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
/**
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
/**
 * @brief Request the device shut down (Non-blocking call).
 *
 * @param DevID The device ID of the machine that request to be shutdown.
 *
 * @return Return an error code. <br>
 * If the function is called successfully, the return value is ERR_NEXMOTION_SUCCESS (0). Otherwise, the return value is an error code. All error codes are defined in the header file, NexMotionError.h.
 */
RTN_ERR FNTYPE NMC_DeviceShutdownRequest( I32_T DevID );
/**
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


// Watchdog APIs
RTN_ERR FNTYPE NMC_DeviceWatchdogTimerEnable( I32_T DevID, U32_T TimeoutMs, I32_T Mode );
RTN_ERR FNTYPE NMC_DeviceWatchdogTimerDisable( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceWatchdogTimerReset( I32_T DevID );

// Advanced controller initialization APIs
RTN_ERR FNTYPE NMC_DeviceCreate( I32_T DevType, I32_T DevIndex, I32_T *PRetDevID );
RTN_ERR FNTYPE NMC_DeviceDelete( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceLoadIniConfig( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceResetConfig( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceStart( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceStop( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceStartRequest( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceStopRequest( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceGetState( I32_T DevID, I32_T *PRetDeviceState );

// System parameter setting APIs
RTN_ERR FNTYPE NMC_DeviceSetParam( I32_T DevID, I32_T ParamNum, I32_T SubIndex, I32_T ParaValue );
RTN_ERR FNTYPE NMC_DeviceGetParam( I32_T DevID, I32_T ParamNum, I32_T SubIndex, I32_T *PRetParaValue );
RTN_ERR FNTYPE NMC_SetIniPath( _opt_null_ const char *PIniPath );

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
RTN_ERR FNTYPE NMC_DeviceGetAxisCount( I32_T DevID, I32_T *PRetAxisCount );
RTN_ERR FNTYPE NMC_DeviceGetGroupCount( I32_T DevID, I32_T *PRetGroupCount );
RTN_ERR FNTYPE NMC_DeviceGetGroupAxisCount( I32_T DevID, I32_T GroupIndex, I32_T *PRetGroupAxisCount );

// Read axis/group description APIs
RTN_ERR FNTYPE NMC_AxisGetDescription( I32_T DevID, I32_T AxisIndex, U32_T DescStrSize, char *PRetAxisDescription );
RTN_ERR FNTYPE NMC_GroupGetDescription( I32_T DevID, I32_T GroupIndex, U32_T DescStrSize, char *PRetGroupDescription );

// All axes and groups enable/disable APIs
RTN_ERR FNTYPE NMC_DeviceResetStateAll( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceEnableAll( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceDisableAll( I32_T DevID );

// All axes and groups motion termination APIs
RTN_ERR FNTYPE NMC_DeviceHaltAll( I32_T DevID );
RTN_ERR FNTYPE NMC_DeviceStopAll( I32_T DevID );

// Axis parameter setting APIs
RTN_ERR FNTYPE NMC_AxisSetParamI32( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, I32_T ParaValueI32 );
RTN_ERR FNTYPE NMC_AxisGetParamI32( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, I32_T *PRetParaValueI32 );
RTN_ERR FNTYPE NMC_AxisSetParamF64( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, F64_T ParaValueF64 );
RTN_ERR FNTYPE NMC_AxisGetParamF64( I32_T DevID, I32_T AxisIndex, I32_T ParamNum, I32_T SubIndex, F64_T *PRetParaValueF64 );

// Axis state control APIs
RTN_ERR FNTYPE NMC_AxisEnable( I32_T DevID, I32_T AxisIndex );
RTN_ERR FNTYPE NMC_AxisDisable( I32_T DevID, I32_T AxisIndex );
RTN_ERR FNTYPE NMC_AxisGetStatus( I32_T DevID, I32_T AxisIndex, I32_T *PRetAxisStatus );
RTN_ERR FNTYPE NMC_AxisGetState( I32_T DevID, I32_T AxisIndex, I32_T *PRetAxisState );
RTN_ERR FNTYPE NMC_AxisResetState( I32_T DevID, I32_T AxisIndex );
RTN_ERR FNTYPE NMC_AxisResetDriveAlm( I32_T DevID, I32_T AxisIndex );
RTN_ERR FNTYPE NMC_AxisGetDriveAlmCode( I32_T DevID, I32_T AxisIndex, I32_T *PRetAlmCode );

// Axis motion profile read APIs
RTN_ERR FNTYPE NMC_AxisGetCommandPos( I32_T DevID, I32_T AxisIndex, F64_T *PRetCmdPos );
RTN_ERR FNTYPE NMC_AxisGetActualPos( I32_T DevID, I32_T AxisIndex, F64_T *PRetActPos );
RTN_ERR FNTYPE NMC_AxisGetCommandVel( I32_T DevID, I32_T AxisIndex, F64_T *PRetCmdVel );
RTN_ERR FNTYPE NMC_AxisGetActualVel( I32_T DevID, I32_T AxisIndex, F64_T *PRetActVel );
RTN_ERR FNTYPE NMC_AxisGetMotionBuffSpace(  I32_T DevID, I32_T AxisIndex, I32_T *PRetFreeSpace );

// Axis motion control APIs
RTN_ERR FNTYPE NMC_AxisPtp( I32_T DevID, I32_T AxisIndex, F64_T TargetPos, _opt_null_ const F64_T *PMaxVel );
RTN_ERR FNTYPE NMC_AxisJog( I32_T DevID, I32_T AxisIndex, I32_T Dir, _opt_null_ const F64_T *PMaxVel );

// Axis homing control APIs
RTN_ERR FNTYPE NMC_AxisSetHomePos( I32_T DevID, I32_T AxisIndex, F64_T HomePos );
RTN_ERR FNTYPE NMC_AxisHomeDrive( I32_T DevID, I32_T AxisIndex );


// Axis motion termination APIs
RTN_ERR FNTYPE NMC_AxisHalt( I32_T DevID, I32_T AxisIndex );
RTN_ERR FNTYPE NMC_AxisStop( I32_T DevID, I32_T AxisIndex );
RTN_ERR FNTYPE NMC_AxisHaltAll( I32_T DevID );
RTN_ERR FNTYPE NMC_AxisStopAll( I32_T DevID );

// Axis profile change on the fly APIs
RTN_ERR FNTYPE NMC_AxisVelOverride( I32_T DevID, I32_T AxisIndex, F64_T TargetVel );
RTN_ERR FNTYPE NMC_AxisAccOverride( I32_T DevID, I32_T AxisIndex, F64_T TargetAcc );
RTN_ERR FNTYPE NMC_AxisDecOverride( I32_T DevID, I32_T AxisIndex, F64_T TargetDec );

// Axis velocity ratio setting APIs
RTN_ERR FNTYPE NMC_AxisSetSpeedRatio( I32_T DevID, I32_T AxisIndex, F64_T Percentage );
RTN_ERR FNTYPE NMC_AxisGetSpeedRatio( I32_T DevID, I32_T AxisIndex, F64_T *PPercentage );

// Group parameter setting APIs
RTN_ERR FNTYPE NMC_GroupSetParamI32( I32_T DevID, I32_T GroupIndex, I32_T ParamNum, I32_T SubIndex, I32_T ParaValueI32 );
RTN_ERR FNTYPE NMC_GroupGetParamI32( I32_T DevID, I32_T GroupIndex, I32_T ParamNum, I32_T SubIndex, I32_T *PRetParaValueI32 );
RTN_ERR FNTYPE NMC_GroupSetParamF64( I32_T DevID, I32_T GroupIndex, I32_T ParamNum, I32_T SubIndex, F64_T ParaValueF64 );
RTN_ERR FNTYPE NMC_GroupGetParamF64( I32_T DevID, I32_T GroupIndex, I32_T ParamNum, I32_T SubIndex, F64_T *PRetParaValueF64 );
RTN_ERR FNTYPE NMC_GroupAxSetParamI32( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T ParamNum, I32_T SubIndex, I32_T ParaValueI32 );
RTN_ERR FNTYPE NMC_GroupAxGetParamI32( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T ParamNum, I32_T SubIndex, I32_T *PRetParaValueI32 );
RTN_ERR FNTYPE NMC_GroupAxSetParamF64( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T ParamNum, I32_T SubIndex, F64_T ParaValueF64 );
RTN_ERR FNTYPE NMC_GroupAxGetParamF64( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T ParamNum, I32_T SubIndex, F64_T *PRetParaValueF64 );

// Group state control APIs
RTN_ERR FNTYPE NMC_GroupEnable( I32_T DevID, I32_T GroupIndex );
RTN_ERR FNTYPE NMC_GroupDisable( I32_T DevID, I32_T GroupIndex );
RTN_ERR FNTYPE NMC_GroupGetStatus( I32_T DevID, I32_T GroupIndex, I32_T *PRetStatusInBit );
RTN_ERR FNTYPE NMC_GroupGetState( I32_T DevID, I32_T GroupIndex, I32_T *PRetState );
RTN_ERR FNTYPE NMC_GroupResetState( I32_T DevID, I32_T GroupIndex );
RTN_ERR FNTYPE NMC_GroupResetDriveAlm( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex );
RTN_ERR FNTYPE NMC_GroupResetDriveAlmAll( I32_T DevID, I32_T GroupIndex );
RTN_ERR FNTYPE NMC_GroupGetDriveAlmCode( I32_T DevID, I32_T GroupIndex, I32_T GroupAxisIndex, I32_T *PRetAlmCode );

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
RTN_ERR FNTYPE NMC_GroupGetCommandPosAcs( I32_T DevID, I32_T GroupIndex, Pos_T *PRetCmdPosAcs );
RTN_ERR FNTYPE NMC_GroupGetActualPosAcs( I32_T DevID, I32_T GroupIndex, Pos_T *PRetActPosAcs );
RTN_ERR FNTYPE NMC_GroupGetCommandPosPcs( I32_T DevID, I32_T GroupIndex, Pos_T *PRetCmdPosPcs );
RTN_ERR FNTYPE NMC_GroupGetActualPosPcs( I32_T DevID, I32_T GroupIndex, Pos_T *PRetActPosPcs );
RTN_ERR FNTYPE NMC_GroupGetCommandPos( I32_T DevID, I32_T GroupIndex, I32_T CoordSys, Pos_T *PRetCmdPos );
RTN_ERR FNTYPE NMC_GroupGetActualPos( I32_T DevID, I32_T GroupIndex, I32_T CoordSys, Pos_T *PRetActPos );
RTN_ERR FNTYPE NMC_GroupGetMotionBuffSpace( I32_T DevID, I32_T GroupIndex, I32_T *PRetFreeSpace );

// Group homing oparation APIs
RTN_ERR FNTYPE NMC_GroupSetHomePos( I32_T DevID, I32_T GroupIndex, I32_T GroupAxesIdxMask, const Pos_T *PHomePosAcs );
RTN_ERR FNTYPE NMC_GroupAxesHomeDrive( I32_T DevID, I32_T GroupIndex, I32_T GroupAxesIdxMask  );

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
