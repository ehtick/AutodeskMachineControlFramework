/*++

Copyright (C) 2024 Autodesk Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Autodesk Inc. nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AUTODESK INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


This file has been generated by the Automatic Component Toolkit (ACT) version 1.8.0-develop.

Abstract: This is an autogenerated C++-Header file in order to allow an easy
 use of MC Driver Technosoft Motion Library

Interface version: 2.0.0

*/

#ifndef __LIBMCDRIVER_TML_HEADER_CPP
#define __LIBMCDRIVER_TML_HEADER_CPP

#ifdef __LIBMCDRIVER_TML_EXPORTS
#ifdef _WIN32
#define LIBMCDRIVER_TML_DECLSPEC __declspec (dllexport)
#else // _WIN32
#define LIBMCDRIVER_TML_DECLSPEC __attribute__((visibility("default")))
#endif // _WIN32
#else // __LIBMCDRIVER_TML_EXPORTS
#define LIBMCDRIVER_TML_DECLSPEC
#endif // __LIBMCDRIVER_TML_EXPORTS

#include "libmcdriver_tml_types.hpp"

#include "libmcenv_dynamic.hpp"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************************************************************
 Class definition for Base
**************************************************************************************************************************/

/*************************************************************************************************************************
 Class definition for Driver
**************************************************************************************************************************/

/**
* Configures a driver with its specific configuration data.
*
* @param[in] pDriver - Driver instance.
* @param[in] pConfigurationString - Configuration data of driver.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_configure(LibMCDriver_TML_Driver pDriver, const char * pConfigurationString);

/**
* returns the name identifier of the driver
*
* @param[in] pDriver - Driver instance.
* @param[in] nNameBufferSize - size of the buffer (including trailing 0)
* @param[out] pNameNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pNameBuffer -  buffer of Name of the driver., may be NULL
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_getname(LibMCDriver_TML_Driver pDriver, const LibMCDriver_TML_uint32 nNameBufferSize, LibMCDriver_TML_uint32* pNameNeededChars, char * pNameBuffer);

/**
* returns the type identifier of the driver
*
* @param[in] pDriver - Driver instance.
* @param[in] nTypeBufferSize - size of the buffer (including trailing 0)
* @param[out] pTypeNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pTypeBuffer -  buffer of Type of the driver., may be NULL
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_gettype(LibMCDriver_TML_Driver pDriver, const LibMCDriver_TML_uint32 nTypeBufferSize, LibMCDriver_TML_uint32* pTypeNeededChars, char * pTypeBuffer);

/**
* returns the version identifiers of the driver
*
* @param[in] pDriver - Driver instance.
* @param[out] pMajor - Major version.
* @param[out] pMinor - Minor version.
* @param[out] pMicro - Micro version.
* @param[in] nBuildBufferSize - size of the buffer (including trailing 0)
* @param[out] pBuildNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pBuildBuffer -  buffer of Build identifier., may be NULL
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_getversion(LibMCDriver_TML_Driver pDriver, LibMCDriver_TML_uint32 * pMajor, LibMCDriver_TML_uint32 * pMinor, LibMCDriver_TML_uint32 * pMicro, const LibMCDriver_TML_uint32 nBuildBufferSize, LibMCDriver_TML_uint32* pBuildNeededChars, char * pBuildBuffer);

/**
* Updates the driver parameters in the driver environment. Should only be called in the driver thread.
*
* @param[in] pDriver - Driver instance.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_queryparameters(LibMCDriver_TML_Driver pDriver);

/**
* Updates the driver parameters in the driver environment. Might be called out of thread. Implementation MUST be able to handle parallel calls.
*
* @param[in] pDriver - Driver instance.
* @param[in] pDriverUpdateInstance - Status update instance.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_queryparametersex(LibMCDriver_TML_Driver pDriver, LibMCEnv_DriverStatusUpdateSession pDriverUpdateInstance);

/*************************************************************************************************************************
 Class definition for Axis
**************************************************************************************************************************/

/**
* Moves the selected drive a relative distance.
*
* @param[in] pAxis - Axis instance.
* @param[in] dDistance - Distance (mm)
* @param[in] dSpeed - Speed (mm/s)
* @param[in] dAcceleration - Acceleration (mm/s^2)
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_moverelative(LibMCDriver_TML_Axis pAxis, LibMCDriver_TML_double dDistance, LibMCDriver_TML_double dSpeed, LibMCDriver_TML_double dAcceleration);

/**
* Moves the selected drive to an absolute location.
*
* @param[in] pAxis - Axis instance.
* @param[in] dDistance - Distance (mm)
* @param[in] dSpeed - Speed (mm/s)
* @param[in] dAcceleration - Acceleration (mm/s^2)
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_moveabsolute(LibMCDriver_TML_Axis pAxis, LibMCDriver_TML_double dDistance, LibMCDriver_TML_double dSpeed, LibMCDriver_TML_double dAcceleration);

/**
* Runs a subroutine on the selected drive.
*
* @param[in] pAxis - Axis instance.
* @param[in] pRoutine - Label of routine
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_callsubroutine(LibMCDriver_TML_Axis pAxis, const char * pRoutine);

/**
* Retrieves the current position of the drive.
*
* @param[in] pAxis - Axis instance.
* @param[in] eReference - Reference type to use for the position.
* @param[out] pPosition - Position (mm)
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_getposition(LibMCDriver_TML_Axis pAxis, LibMCDriver_TML::eReferenceType eReference, LibMCDriver_TML_double * pPosition);

/**
* Retrieves the current speed of the drive.
*
* @param[in] pAxis - Axis instance.
* @param[in] eReference - Reference type to use for the speed.
* @param[out] pSpeed - Speed (mm/s)
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_getspeed(LibMCDriver_TML_Axis pAxis, LibMCDriver_TML::eReferenceType eReference, LibMCDriver_TML_double * pSpeed);

/**
* Retrieves the current position of the drive.
*
* @param[in] pAxis - Axis instance.
* @param[in] pVariableName - Variable name
* @param[out] pValue - Value
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_getintvariable(LibMCDriver_TML_Axis pAxis, const char * pVariableName, LibMCDriver_TML_int32 * pValue);

/**
* Checks to see if the  is currently moving.
*
* @param[in] pAxis - Axis instance.
* @param[out] pMotionComplete - Boolean reflecting if the drive is in currently moving.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_motioncomplete(LibMCDriver_TML_Axis pAxis, bool * pMotionComplete);

/**
* Checks to see if the drive is in position.
*
* @param[in] pAxis - Axis instance.
* @param[out] pTargetReached - Boolean reflecting if the drive is in position.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_targetreached(LibMCDriver_TML_Axis pAxis, bool * pTargetReached);

/**
* Returns the axis identifier.
*
* @param[in] pAxis - Axis instance.
* @param[in] nIdentifierBufferSize - size of the buffer (including trailing 0)
* @param[out] pIdentifierNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pIdentifierBuffer -  buffer of Axis identifier., may be NULL
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_getidentifier(LibMCDriver_TML_Axis pAxis, const LibMCDriver_TML_uint32 nIdentifierBufferSize, LibMCDriver_TML_uint32* pIdentifierNeededChars, char * pIdentifierBuffer);

/**
* Returns the identifier of the channel of the axis.
*
* @param[in] pAxis - Axis instance.
* @param[in] nIdentifierBufferSize - size of the buffer (including trailing 0)
* @param[out] pIdentifierNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pIdentifierBuffer -  buffer of Channel identifier., may be NULL
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_getchannelidentifier(LibMCDriver_TML_Axis pAxis, const LibMCDriver_TML_uint32 nIdentifierBufferSize, LibMCDriver_TML_uint32* pIdentifierNeededChars, char * pIdentifierBuffer);

/**
* Sets the power for an axis.
*
* @param[in] pAxis - Axis instance.
* @param[in] bEnable - Flag if the power is enabled or not enabled.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_setpower(LibMCDriver_TML_Axis pAxis, bool bEnable);

/**
* Reads the selected register of an axis.
*
* @param[in] pAxis - Axis instance.
* @param[in] nRegister - Selected register.
* @param[out] pData - Value inside register.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_readregister(LibMCDriver_TML_Axis pAxis, LibMCDriver_TML_uint32 nRegister, LibMCDriver_TML_uint32 * pData);

/**
* Checks the power of the selected axis.
*
* @param[in] pAxis - Axis instance.
* @param[out] pData - True for power on.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_checkpower(LibMCDriver_TML_Axis pAxis, bool * pData);

/**
* Checks for any errors on the selected axis, ignores limits.
*
* @param[in] pAxis - Axis instance.
* @param[out] pErrorRegister - Error register.
* @param[out] pData - True for error.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_checkaxiserror(LibMCDriver_TML_Axis pAxis, LibMCDriver_TML_uint16 * pErrorRegister, bool * pData);

/**
* Resets the selected axis, homing will be required.
*
* @param[in] pAxis - Axis instance.
* @param[in] bForceFull - To set if a full or just fault reset is run (false=faultreset, true=fullreset).
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_axis_resetaxis(LibMCDriver_TML_Axis pAxis, bool bForceFull);

/*************************************************************************************************************************
 Class definition for Channel
**************************************************************************************************************************/

/**
* Returns the channel identifier.
*
* @param[in] pChannel - Channel instance.
* @param[in] nIdentifierBufferSize - size of the buffer (including trailing 0)
* @param[out] pIdentifierNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pIdentifierBuffer -  buffer of Channel identifier., may be NULL
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_channel_getidentifier(LibMCDriver_TML_Channel pChannel, const LibMCDriver_TML_uint32 nIdentifierBufferSize, LibMCDriver_TML_uint32* pIdentifierNeededChars, char * pIdentifierBuffer);

/**
* Setups an axis for this channel. The identifier MUST be globally unique.
*
* @param[in] pChannel - Channel instance.
* @param[in] pIdentifier - Identifier for the axis. Fails if axis already exist.
* @param[in] nAxisID - Hardware ID of the axis. MUST be unique in the channel.
* @param[in] nConfigurationBufferSize - Number of elements in buffer
* @param[in] pConfigurationBuffer - uint8 buffer of Configuration ZIP file for the axis.
* @param[in] nCountsPerMM - Sets the mm per count used for all moves and accelerations.
* @param[out] pAxisInstance - Returns the axis instance.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_channel_setupaxis(LibMCDriver_TML_Channel pChannel, const char * pIdentifier, LibMCDriver_TML_uint32 nAxisID, LibMCDriver_TML_uint64 nConfigurationBufferSize, const LibMCDriver_TML_uint8 * pConfigurationBuffer, LibMCDriver_TML_uint32 nCountsPerMM, LibMCDriver_TML_Axis * pAxisInstance);

/**
* Finds an existing axis of this channel.
*
* @param[in] pChannel - Channel instance.
* @param[in] pIdentifier - Identifier for the axis. Fails if axis already exist.
* @param[out] pAxisInstance - Returns the axis instance.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_channel_findaxis(LibMCDriver_TML_Channel pChannel, const char * pIdentifier, LibMCDriver_TML_Axis * pAxisInstance);

/**
* Returns if the axis exists on this channel.
*
* @param[in] pChannel - Channel instance.
* @param[in] pIdentifier - Identifier of the axis.
* @param[out] pValue - Flag if the axis exists.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_channel_axisexists(LibMCDriver_TML_Channel pChannel, const char * pIdentifier, bool * pValue);

/**
* Closes the channel. Any other call will fail after closing.
*
* @param[in] pChannel - Channel instance.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_channel_close(LibMCDriver_TML_Channel pChannel);

/*************************************************************************************************************************
 Class definition for Driver_TML
**************************************************************************************************************************/

/**
* Turns the driver into a simulation mode.
*
* @param[in] pDriver_TML - Driver_TML instance.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_tml_settosimulationmode(LibMCDriver_TML_Driver_TML pDriver_TML);

/**
* Returns if the driver is in simulation mode.
*
* @param[in] pDriver_TML - Driver_TML instance.
* @param[out] pSimulationModeEnabled - Flag if driver is in simulation mode.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_tml_issimulationmode(LibMCDriver_TML_Driver_TML pDriver_TML, bool * pSimulationModeEnabled);

/**
* Sets the machine resource name of the TML SDK to load. MUST be called before Connect or it has no effect.
*
* @param[in] pDriver_TML - Driver_TML instance.
* @param[in] pLibResourceName - Resource name of core machine package that contains the proprietary tml_lib.dll. Empty means standard naming applies.
* @param[in] pCommsResourceName - Resource name of core machine package that contains the proprietary tmlcomms.dll. Empty means standard naming applies.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_tml_setcustomsdkresource(LibMCDriver_TML_Driver_TML pDriver_TML, const char * pLibResourceName, const char * pCommsResourceName);

/**
* Opens a communication channel.
*
* @param[in] pDriver_TML - Driver_TML instance.
* @param[in] pIdentifier - Identifier of the device.
* @param[in] pDeviceName - Name of the device.
* @param[in] eChannelTypeToUse - Type of the interface device.
* @param[in] eProtocolTypeToUse - Type of the protocol.
* @param[in] nHostID - Host ID to use.
* @param[in] nBaudrate - Baudrate to use.
* @param[out] pChannelInstance - Returns the channel instance.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_tml_openchannel(LibMCDriver_TML_Driver_TML pDriver_TML, const char * pIdentifier, const char * pDeviceName, LibMCDriver_TML::eChannelType eChannelTypeToUse, LibMCDriver_TML::eProtocolType eProtocolTypeToUse, LibMCDriver_TML_uint32 nHostID, LibMCDriver_TML_uint32 nBaudrate, LibMCDriver_TML_Channel * pChannelInstance);

/**
* Returns if the channel exists..
*
* @param[in] pDriver_TML - Driver_TML instance.
* @param[in] pIdentifier - Identifier of the device.
* @param[out] pValue - Flag if the channel exists.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_tml_channelexists(LibMCDriver_TML_Driver_TML pDriver_TML, const char * pIdentifier, bool * pValue);

/**
* Find a communication channel by integer. Fails if the channel does not exist.
*
* @param[in] pDriver_TML - Driver_TML instance.
* @param[in] pIdentifier - Identifier of the device.
* @param[out] pChannelInstance - Returns the channel instance.
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_driver_tml_findchannel(LibMCDriver_TML_Driver_TML pDriver_TML, const char * pIdentifier, LibMCDriver_TML_Channel * pChannelInstance);

/*************************************************************************************************************************
 Global functions
**************************************************************************************************************************/

/**
* retrieves the binary version of this library.
*
* @param[out] pMajor - returns the major version of this library
* @param[out] pMinor - returns the minor version of this library
* @param[out] pMicro - returns the micro version of this library
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_getversion(LibMCDriver_TML_uint32 * pMajor, LibMCDriver_TML_uint32 * pMinor, LibMCDriver_TML_uint32 * pMicro);

/**
* Returns the last error recorded on this object
*
* @param[in] pInstance - Instance Handle
* @param[in] nErrorMessageBufferSize - size of the buffer (including trailing 0)
* @param[out] pErrorMessageNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pErrorMessageBuffer -  buffer of Message of the last error, may be NULL
* @param[out] pHasError - Is there a last error to query
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_getlasterror(LibMCDriver_TML_Base pInstance, const LibMCDriver_TML_uint32 nErrorMessageBufferSize, LibMCDriver_TML_uint32* pErrorMessageNeededChars, char * pErrorMessageBuffer, bool * pHasError);

/**
* Releases shared ownership of an Instance
*
* @param[in] pInstance - Instance Handle
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_releaseinstance(LibMCDriver_TML_Base pInstance);

/**
* Acquires shared ownership of an Instance
*
* @param[in] pInstance - Instance Handle
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_acquireinstance(LibMCDriver_TML_Base pInstance);

/**
* Injects an imported component for usage within this component
*
* @param[in] pNameSpace - NameSpace of the injected component
* @param[in] pSymbolAddressMethod - Address of the SymbolAddressMethod of the injected component
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_injectcomponent(const char * pNameSpace, LibMCDriver_TML_pvoid pSymbolAddressMethod);

/**
* Returns the address of the SymbolLookupMethod
*
* @param[out] pSymbolLookupMethod - Address of the SymbolAddressMethod
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_getsymbollookupmethod(LibMCDriver_TML_pvoid * pSymbolLookupMethod);

/**
* Creates a driver instance with a specific name.
*
* @param[in] pName - Name of driver to be created.
* @param[in] pType - Type of driver to be created.
* @param[in] pDriverEnvironment - Environment of this driver.
* @param[out] pInstance - New Driver instance
* @return error code or 0 (success)
*/
LIBMCDRIVER_TML_DECLSPEC LibMCDriver_TMLResult libmcdriver_tml_createdriver(const char * pName, const char * pType, LibMCEnv_DriverEnvironment pDriverEnvironment, LibMCDriver_TML_Driver * pInstance);

#ifdef __cplusplus
}
#endif

#endif // __LIBMCDRIVER_TML_HEADER_CPP
