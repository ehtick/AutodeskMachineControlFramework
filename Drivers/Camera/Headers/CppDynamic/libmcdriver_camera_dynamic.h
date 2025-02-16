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
 use of Generic Camera Driver for Windows or Linux devices

Interface version: 2.0.0

*/

#ifndef __LIBMCDRIVER_CAMERA_DYNAMICHEADER_CPPTYPES
#define __LIBMCDRIVER_CAMERA_DYNAMICHEADER_CPPTYPES

#include "libmcdriver_camera_types.hpp"

#include "libmcenv_types.hpp"


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
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDriver_ConfigurePtr) (LibMCDriver_Camera_Driver pDriver, const char * pConfigurationString);

/**
* returns the name identifier of the driver
*
* @param[in] pDriver - Driver instance.
* @param[in] nNameBufferSize - size of the buffer (including trailing 0)
* @param[out] pNameNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pNameBuffer -  buffer of Name of the driver., may be NULL
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDriver_GetNamePtr) (LibMCDriver_Camera_Driver pDriver, const LibMCDriver_Camera_uint32 nNameBufferSize, LibMCDriver_Camera_uint32* pNameNeededChars, char * pNameBuffer);

/**
* returns the type identifier of the driver
*
* @param[in] pDriver - Driver instance.
* @param[in] nTypeBufferSize - size of the buffer (including trailing 0)
* @param[out] pTypeNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pTypeBuffer -  buffer of Type of the driver., may be NULL
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDriver_GetTypePtr) (LibMCDriver_Camera_Driver pDriver, const LibMCDriver_Camera_uint32 nTypeBufferSize, LibMCDriver_Camera_uint32* pTypeNeededChars, char * pTypeBuffer);

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
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDriver_GetVersionPtr) (LibMCDriver_Camera_Driver pDriver, LibMCDriver_Camera_uint32 * pMajor, LibMCDriver_Camera_uint32 * pMinor, LibMCDriver_Camera_uint32 * pMicro, const LibMCDriver_Camera_uint32 nBuildBufferSize, LibMCDriver_Camera_uint32* pBuildNeededChars, char * pBuildBuffer);

/**
* Updates the driver parameters in the driver environment. Should only be called in the driver thread.
*
* @param[in] pDriver - Driver instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDriver_QueryParametersPtr) (LibMCDriver_Camera_Driver pDriver);

/**
* Updates the driver parameters in the driver environment. Might be called out of thread. Implementation MUST be able to handle parallel calls.
*
* @param[in] pDriver - Driver instance.
* @param[in] pDriverUpdateInstance - Status update instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDriver_QueryParametersExPtr) (LibMCDriver_Camera_Driver pDriver, LibMCEnv_DriverStatusUpdateSession pDriverUpdateInstance);

/*************************************************************************************************************************
 Class definition for DeviceBase
**************************************************************************************************************************/

/**
* Returns the name of the device in a human readable form.
*
* @param[in] pDeviceBase - DeviceBase instance.
* @param[in] nFriendlyNameBufferSize - size of the buffer (including trailing 0)
* @param[out] pFriendlyNameNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pFriendlyNameBuffer -  buffer of Name of device., may be NULL
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDeviceBase_GetFriendlyNamePtr) (LibMCDriver_Camera_DeviceBase pDeviceBase, const LibMCDriver_Camera_uint32 nFriendlyNameBufferSize, LibMCDriver_Camera_uint32* pFriendlyNameNeededChars, char * pFriendlyNameBuffer);

/**
* Returns a unique name of the device from the operating system.
*
* @param[in] pDeviceBase - DeviceBase instance.
* @param[in] nOperatingSystemNameBufferSize - size of the buffer (including trailing 0)
* @param[out] pOperatingSystemNameNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pOperatingSystemNameBuffer -  buffer of Operating system Identifier of the device., may be NULL
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDeviceBase_GetOperatingSystemNamePtr) (LibMCDriver_Camera_DeviceBase pDeviceBase, const LibMCDriver_Camera_uint32 nOperatingSystemNameBufferSize, LibMCDriver_Camera_uint32* pOperatingSystemNameNeededChars, char * pOperatingSystemNameBuffer);

/**
* Returns if the device supports video capture.
*
* @param[in] pDeviceBase - DeviceBase instance.
* @param[out] pIsVideo - Returns true if the device is a video device.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDeviceBase_IsVideoDevicePtr) (LibMCDriver_Camera_DeviceBase pDeviceBase, bool * pIsVideo);

/*************************************************************************************************************************
 Class definition for VideoDevice
**************************************************************************************************************************/

/**
* Returns the identifier of the video device.
*
* @param[in] pVideoDevice - VideoDevice instance.
* @param[in] nIdentifierBufferSize - size of the buffer (including trailing 0)
* @param[out] pIdentifierNeededChars - will be filled with the count of the written bytes, or needed buffer size.
* @param[out] pIdentifierBuffer -  buffer of Identifier of the device., may be NULL
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraVideoDevice_GetIdentifierPtr) (LibMCDriver_Camera_VideoDevice pVideoDevice, const LibMCDriver_Camera_uint32 nIdentifierBufferSize, LibMCDriver_Camera_uint32* pIdentifierNeededChars, char * pIdentifierBuffer);

/**
* Returns the number of supported resolutions.
*
* @param[in] pVideoDevice - VideoDevice instance.
* @param[out] pCount - Number of supported resolutions.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraVideoDevice_GetSupportedResolutionCountPtr) (LibMCDriver_Camera_VideoDevice pVideoDevice, LibMCDriver_Camera_uint32 * pCount);

/**
* Returns a resolution from the supported resolution list.
*
* @param[in] pVideoDevice - VideoDevice instance.
* @param[in] nIndex - Index to return. 0-based.
* @param[out] pWidth - Width in pixels.
* @param[out] pHeight - Height in pixels.
* @param[out] pFramerate - Framerate in FPS. Currently only integer framerates are supported.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraVideoDevice_GetSupportedResolutionPtr) (LibMCDriver_Camera_VideoDevice pVideoDevice, LibMCDriver_Camera_uint32 nIndex, LibMCDriver_Camera_uint32 * pWidth, LibMCDriver_Camera_uint32 * pHeight, LibMCDriver_Camera_uint32 * pFramerate);

/**
* Returns a the current resolution and Framerate of the video stream.
*
* @param[in] pVideoDevice - VideoDevice instance.
* @param[out] pWidth - Width in pixels.
* @param[out] pHeight - Height in pixels.
* @param[out] pFramerate - Framerate in FPS. Currently only integer framerates are supported.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraVideoDevice_GetCurrentResolutionPtr) (LibMCDriver_Camera_VideoDevice pVideoDevice, LibMCDriver_Camera_uint32 * pWidth, LibMCDriver_Camera_uint32 * pHeight, LibMCDriver_Camera_uint32 * pFramerate);

/**
* Sets the resolution of the video stream. Fails if framerate is not supported.
*
* @param[in] pVideoDevice - VideoDevice instance.
* @param[in] nWidth - Width in pixels.
* @param[in] nHeight - Height in pixels.
* @param[in] nFramerate - Framerate in FPS to set. Currently only integer framerates are supported.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraVideoDevice_SetResolutionPtr) (LibMCDriver_Camera_VideoDevice pVideoDevice, LibMCDriver_Camera_uint32 nWidth, LibMCDriver_Camera_uint32 nHeight, LibMCDriver_Camera_uint32 nFramerate);

/**
* Captures a still image from the video stream.
*
* @param[in] pVideoDevice - VideoDevice instance.
* @param[in] pImageData - Capture image object.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraVideoDevice_CaptureRawImagePtr) (LibMCDriver_Camera_VideoDevice pVideoDevice, LibMCEnv_ImageData pImageData);

/**
* Starts automatic capturing of the video into a video stream. If a stream capture is active, it will stop the current capture process.
*
* @param[in] pVideoDevice - VideoDevice instance.
* @param[in] pStreamInstance - Framework stream capture instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraVideoDevice_StartStreamCapturePtr) (LibMCDriver_Camera_VideoDevice pVideoDevice, LibMCEnv_VideoStream pStreamInstance);

/**
* Stops any current video stream capturing.
*
* @param[in] pVideoDevice - VideoDevice instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraVideoDevice_StopStreamCapturePtr) (LibMCDriver_Camera_VideoDevice pVideoDevice);

/**
* Returns if a screen capture is active.
*
* @param[in] pVideoDevice - VideoDevice instance.
* @param[out] pIsActive - Returns true, if a stream capture is active.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraVideoDevice_StreamCaptureIsActivePtr) (LibMCDriver_Camera_VideoDevice pVideoDevice, bool * pIsActive);

/**
* Returns statistics about the current stream capture process.
*
* @param[in] pVideoDevice - VideoDevice instance.
* @param[out] pDesiredFramerate - Desired Framerate in fps.
* @param[out] pMinFramerate - Minimum achieved Capture Framerate in fps.
* @param[out] pMaxFramerate - Maximum achieved Capture Framerate in fps.
* @param[out] pMeanFramerate - Mean achieved Capture Framerate in fps.
* @param[out] pStdDevFramerate - Standard deviation of the Captured Framerate in fps.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraVideoDevice_GetStreamCaptureStatisticsPtr) (LibMCDriver_Camera_VideoDevice pVideoDevice, LibMCDriver_Camera_double * pDesiredFramerate, LibMCDriver_Camera_double * pMinFramerate, LibMCDriver_Camera_double * pMaxFramerate, LibMCDriver_Camera_double * pMeanFramerate, LibMCDriver_Camera_double * pStdDevFramerate);

/*************************************************************************************************************************
 Class definition for DeviceInfo
**************************************************************************************************************************/

/*************************************************************************************************************************
 Class definition for DeviceList
**************************************************************************************************************************/

/**
* Returns number of devices found.
*
* @param[in] pDeviceList - DeviceList instance.
* @param[out] pCount - Number of devices found.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDeviceList_GetCountPtr) (LibMCDriver_Camera_DeviceList pDeviceList, LibMCDriver_Camera_uint32 * pCount);

/**
* Returns a device info by index.
*
* @param[in] pDeviceList - DeviceList instance.
* @param[in] nIndex - Index of device (0-based).
* @param[out] pDeviceInfoInstance - Info of discovered device.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDeviceList_GetDeviceInfoPtr) (LibMCDriver_Camera_DeviceList pDeviceList, LibMCDriver_Camera_uint32 nIndex, LibMCDriver_Camera_DeviceInfo * pDeviceInfoInstance);

/**
* Finds a device info by operating system name.
*
* @param[in] pDeviceList - DeviceList instance.
* @param[in] pOperatingSystemName - Operating system Identifier of the device.
* @param[in] bMustExist - If true, an exception will be thrown if the device does not exist. If false, the call will return null if the device does not exist.
* @param[out] pDeviceInfoInstance - Info of discovered device.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDeviceList_FindDeviceInfoByOperatingSystemNamePtr) (LibMCDriver_Camera_DeviceList pDeviceList, const char * pOperatingSystemName, bool bMustExist, LibMCDriver_Camera_DeviceInfo * pDeviceInfoInstance);

/*************************************************************************************************************************
 Class definition for Driver_Camera
**************************************************************************************************************************/

/**
* Lists all devices available on the system.
*
* @param[in] pDriver_Camera - Driver_Camera instance.
* @param[out] pDeviceListInstance - List of discovered devices.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDriver_Camera_EnumerateDevicesPtr) (LibMCDriver_Camera_Driver_Camera pDriver_Camera, LibMCDriver_Camera_DeviceList * pDeviceListInstance);

/**
* Tries to reserve and activate a device. 
*
* @param[in] pDriver_Camera - Driver_Camera instance.
* @param[in] pIdentifier - An internal identifier that will recover the open device. MUST NOT be empty. Fails if the identifier is already in use.
* @param[in] pVideoDeviceInfo - The information object of the device.
* @param[out] pVideoDeviceInstance - The actual video device instance.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDriver_Camera_OpenVideoDevicePtr) (LibMCDriver_Camera_Driver_Camera pDriver_Camera, const char * pIdentifier, LibMCDriver_Camera_DeviceInfo pVideoDeviceInfo, LibMCDriver_Camera_VideoDevice * pVideoDeviceInstance);

/**
* Finds a device instance by internal identifier.
*
* @param[in] pDriver_Camera - Driver_Camera instance.
* @param[in] pIdentifier - Internal Identifier of the device.
* @param[in] bMustExist - If true, an exception will be thrown if the device does not exist. If false, the call will return null if the device does not exist.
* @param[out] pDeviceInstance - Instance of discovered device.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDriver_Camera_FindDeviceByIdentifierPtr) (LibMCDriver_Camera_Driver_Camera pDriver_Camera, const char * pIdentifier, bool bMustExist, LibMCDriver_Camera_VideoDevice * pDeviceInstance);

/**
* Finds a device instance by operating system name.
*
* @param[in] pDriver_Camera - Driver_Camera instance.
* @param[in] pOperatingSystemName - Operating system Identifier of the device.
* @param[in] bMustExist - If true, an exception will be thrown if the device does not exist. If false, the call will return null if the device does not exist.
* @param[out] pDeviceInstance - Instance of discovered device.
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraDriver_Camera_FindDeviceByOperatingSystemNamePtr) (LibMCDriver_Camera_Driver_Camera pDriver_Camera, const char * pOperatingSystemName, bool bMustExist, LibMCDriver_Camera_VideoDevice * pDeviceInstance);

/*************************************************************************************************************************
 Class definition for Driver_Camera_Windows
**************************************************************************************************************************/

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
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraGetVersionPtr) (LibMCDriver_Camera_uint32 * pMajor, LibMCDriver_Camera_uint32 * pMinor, LibMCDriver_Camera_uint32 * pMicro);

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
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraGetLastErrorPtr) (LibMCDriver_Camera_Base pInstance, const LibMCDriver_Camera_uint32 nErrorMessageBufferSize, LibMCDriver_Camera_uint32* pErrorMessageNeededChars, char * pErrorMessageBuffer, bool * pHasError);

/**
* Releases shared ownership of an Instance
*
* @param[in] pInstance - Instance Handle
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraReleaseInstancePtr) (LibMCDriver_Camera_Base pInstance);

/**
* Acquires shared ownership of an Instance
*
* @param[in] pInstance - Instance Handle
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraAcquireInstancePtr) (LibMCDriver_Camera_Base pInstance);

/**
* Injects an imported component for usage within this component
*
* @param[in] pNameSpace - NameSpace of the injected component
* @param[in] pSymbolAddressMethod - Address of the SymbolAddressMethod of the injected component
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraInjectComponentPtr) (const char * pNameSpace, LibMCDriver_Camera_pvoid pSymbolAddressMethod);

/**
* Returns the address of the SymbolLookupMethod
*
* @param[out] pSymbolLookupMethod - Address of the SymbolAddressMethod
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraGetSymbolLookupMethodPtr) (LibMCDriver_Camera_pvoid * pSymbolLookupMethod);

/**
* Creates a driver instance with a specific name.
*
* @param[in] pName - Name of driver to be created.
* @param[in] pType - Type of driver to be created.
* @param[in] pDriverEnvironment - Environment of this driver.
* @param[out] pInstance - New Driver instance
* @return error code or 0 (success)
*/
typedef LibMCDriver_CameraResult (*PLibMCDriver_CameraCreateDriverPtr) (const char * pName, const char * pType, LibMCEnv_DriverEnvironment pDriverEnvironment, LibMCDriver_Camera_Driver * pInstance);

/*************************************************************************************************************************
 Function Table Structure
**************************************************************************************************************************/

typedef struct {
	void * m_LibraryHandle;
	PLibMCDriver_CameraDriver_ConfigurePtr m_Driver_Configure;
	PLibMCDriver_CameraDriver_GetNamePtr m_Driver_GetName;
	PLibMCDriver_CameraDriver_GetTypePtr m_Driver_GetType;
	PLibMCDriver_CameraDriver_GetVersionPtr m_Driver_GetVersion;
	PLibMCDriver_CameraDriver_QueryParametersPtr m_Driver_QueryParameters;
	PLibMCDriver_CameraDriver_QueryParametersExPtr m_Driver_QueryParametersEx;
	PLibMCDriver_CameraDeviceBase_GetFriendlyNamePtr m_DeviceBase_GetFriendlyName;
	PLibMCDriver_CameraDeviceBase_GetOperatingSystemNamePtr m_DeviceBase_GetOperatingSystemName;
	PLibMCDriver_CameraDeviceBase_IsVideoDevicePtr m_DeviceBase_IsVideoDevice;
	PLibMCDriver_CameraVideoDevice_GetIdentifierPtr m_VideoDevice_GetIdentifier;
	PLibMCDriver_CameraVideoDevice_GetSupportedResolutionCountPtr m_VideoDevice_GetSupportedResolutionCount;
	PLibMCDriver_CameraVideoDevice_GetSupportedResolutionPtr m_VideoDevice_GetSupportedResolution;
	PLibMCDriver_CameraVideoDevice_GetCurrentResolutionPtr m_VideoDevice_GetCurrentResolution;
	PLibMCDriver_CameraVideoDevice_SetResolutionPtr m_VideoDevice_SetResolution;
	PLibMCDriver_CameraVideoDevice_CaptureRawImagePtr m_VideoDevice_CaptureRawImage;
	PLibMCDriver_CameraVideoDevice_StartStreamCapturePtr m_VideoDevice_StartStreamCapture;
	PLibMCDriver_CameraVideoDevice_StopStreamCapturePtr m_VideoDevice_StopStreamCapture;
	PLibMCDriver_CameraVideoDevice_StreamCaptureIsActivePtr m_VideoDevice_StreamCaptureIsActive;
	PLibMCDriver_CameraVideoDevice_GetStreamCaptureStatisticsPtr m_VideoDevice_GetStreamCaptureStatistics;
	PLibMCDriver_CameraDeviceList_GetCountPtr m_DeviceList_GetCount;
	PLibMCDriver_CameraDeviceList_GetDeviceInfoPtr m_DeviceList_GetDeviceInfo;
	PLibMCDriver_CameraDeviceList_FindDeviceInfoByOperatingSystemNamePtr m_DeviceList_FindDeviceInfoByOperatingSystemName;
	PLibMCDriver_CameraDriver_Camera_EnumerateDevicesPtr m_Driver_Camera_EnumerateDevices;
	PLibMCDriver_CameraDriver_Camera_OpenVideoDevicePtr m_Driver_Camera_OpenVideoDevice;
	PLibMCDriver_CameraDriver_Camera_FindDeviceByIdentifierPtr m_Driver_Camera_FindDeviceByIdentifier;
	PLibMCDriver_CameraDriver_Camera_FindDeviceByOperatingSystemNamePtr m_Driver_Camera_FindDeviceByOperatingSystemName;
	PLibMCDriver_CameraGetVersionPtr m_GetVersion;
	PLibMCDriver_CameraGetLastErrorPtr m_GetLastError;
	PLibMCDriver_CameraReleaseInstancePtr m_ReleaseInstance;
	PLibMCDriver_CameraAcquireInstancePtr m_AcquireInstance;
	PLibMCDriver_CameraInjectComponentPtr m_InjectComponent;
	PLibMCDriver_CameraGetSymbolLookupMethodPtr m_GetSymbolLookupMethod;
	PLibMCDriver_CameraCreateDriverPtr m_CreateDriver;
} sLibMCDriver_CameraDynamicWrapperTable;

#endif // __LIBMCDRIVER_CAMERA_DYNAMICHEADER_CPPTYPES

