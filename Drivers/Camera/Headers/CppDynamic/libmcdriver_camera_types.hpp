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

Abstract: This is an autogenerated C++-Header file with basic types in
order to allow an easy use of Generic Camera Driver for Windows or Linux devices

Interface version: 2.0.0

*/

#ifndef __LIBMCDRIVER_CAMERA_TYPES_HEADER_CPP
#define __LIBMCDRIVER_CAMERA_TYPES_HEADER_CPP


/*************************************************************************************************************************
 Scalar types definition
**************************************************************************************************************************/

#ifdef LIBMCDRIVER_CAMERA_USELEGACYINTEGERTYPES

typedef unsigned char LibMCDriver_Camera_uint8;
typedef unsigned short LibMCDriver_Camera_uint16 ;
typedef unsigned int LibMCDriver_Camera_uint32;
typedef unsigned long long LibMCDriver_Camera_uint64;
typedef char LibMCDriver_Camera_int8;
typedef short LibMCDriver_Camera_int16;
typedef int LibMCDriver_Camera_int32;
typedef long long LibMCDriver_Camera_int64;

#else // LIBMCDRIVER_CAMERA_USELEGACYINTEGERTYPES

#include <stdint.h>

typedef uint8_t LibMCDriver_Camera_uint8;
typedef uint16_t LibMCDriver_Camera_uint16;
typedef uint32_t LibMCDriver_Camera_uint32;
typedef uint64_t LibMCDriver_Camera_uint64;
typedef int8_t LibMCDriver_Camera_int8;
typedef int16_t LibMCDriver_Camera_int16;
typedef int32_t LibMCDriver_Camera_int32;
typedef int64_t LibMCDriver_Camera_int64 ;

#endif // LIBMCDRIVER_CAMERA_USELEGACYINTEGERTYPES

typedef float LibMCDriver_Camera_single;
typedef double LibMCDriver_Camera_double;

/*************************************************************************************************************************
 General type definitions
**************************************************************************************************************************/

typedef LibMCDriver_Camera_int32 LibMCDriver_CameraResult;
typedef void * LibMCDriver_CameraHandle;
typedef void * LibMCDriver_Camera_pvoid;

/*************************************************************************************************************************
 Version for LibMCDriver_Camera
**************************************************************************************************************************/

#define LIBMCDRIVER_CAMERA_VERSION_MAJOR 2
#define LIBMCDRIVER_CAMERA_VERSION_MINOR 0
#define LIBMCDRIVER_CAMERA_VERSION_MICRO 0
#define LIBMCDRIVER_CAMERA_VERSION_PRERELEASEINFO ""
#define LIBMCDRIVER_CAMERA_VERSION_BUILDINFO ""

/*************************************************************************************************************************
 Error constants for LibMCDriver_Camera
**************************************************************************************************************************/

#define LIBMCDRIVER_CAMERA_SUCCESS 0
#define LIBMCDRIVER_CAMERA_ERROR_NOTIMPLEMENTED 1 /** functionality not implemented */
#define LIBMCDRIVER_CAMERA_ERROR_INVALIDPARAM 2 /** an invalid parameter was passed */
#define LIBMCDRIVER_CAMERA_ERROR_INVALIDCAST 3 /** a type cast failed */
#define LIBMCDRIVER_CAMERA_ERROR_BUFFERTOOSMALL 4 /** a provided buffer is too small */
#define LIBMCDRIVER_CAMERA_ERROR_GENERICEXCEPTION 5 /** a generic exception occurred */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTLOADLIBRARY 6 /** the library could not be loaded */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTFINDLIBRARYEXPORT 7 /** a required exported symbol could not be found in the library */
#define LIBMCDRIVER_CAMERA_ERROR_INCOMPATIBLEBINARYVERSION 8 /** the version of the binary interface does not match the bindings interface */
#define LIBMCDRIVER_CAMERA_ERROR_DRIVERERROR 1000 /** a driver error occured */
#define LIBMCDRIVER_CAMERA_ERROR_DEVICENOTSUPPORTEDONPLATFORM 1001 /** device not supported on platform */
#define LIBMCDRIVER_CAMERA_ERROR_INVALIDDEVICEINDEX 1002 /** device not supported on platform */
#define LIBMCDRIVER_CAMERA_ERROR_CAMERADEVICENOTFOUND 1003 /** camera device not found */
#define LIBMCDRIVER_CAMERA_ERROR_INVALIDDRIVERTYPE 1004 /** invalid driver type */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTINITIALIZEWMF 1005 /** could not initialize WMF */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTFILTERFORVIDEODEVICES 1006 /** could not filter for video devices */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTENUMERATEDEVICESOURCES 1007 /** could not enumerate device sources */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTCREATEWMFATTRIBUTES 1008 /** could not create Windows Media Foundation Attributes */
#define LIBMCDRIVER_CAMERA_ERROR_WIDECHARTOUTF8CONVERSIONFAILED 1009 /** Widechar to UTF8 conversion failed */
#define LIBMCDRIVER_CAMERA_ERROR_CAMERADEVICELISTOVERRUN 1010 /** Camera device list overrun */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTOPENVIDEODEVICE 1011 /** Could not open video device */
#define LIBMCDRIVER_CAMERA_ERROR_INVALIDCAMERAIDENTIFIERLENGTH 1012 /** Invalid camera identifier length */
#define LIBMCDRIVER_CAMERA_ERROR_INVALIDCAMERAIDENTIFIER 1013 /** Invalid camera identifier */
#define LIBMCDRIVER_CAMERA_ERROR_CAMERAIDENTIFIERALREADYREGISTERED 1014 /** Camera identifier already registered */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTCREATEMEDIATYPE 1015 /** Could not create media type */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETMEDIATYPETOVIDEO 1016 /** Could not set media type to video */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETMEDIATYPEFORMAT 1017 /** Could not set media type format */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETMEDIARESOLUTION 1018 /** Could not set media resolution */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETMEDIAFRAMERATE 1019 /** Could not set media framerate */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETPIXELASPECTRATIO 1020 /** Could not set pixel aspect ratio */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTACTIVATEDEVICE 1021 /** Could not activate device */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTCREATEREADER 1022 /** Could not create reader */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETMEDIATYPE 1023 /** Could not set media type */
#define LIBMCDRIVER_CAMERA_ERROR_NOMEDIASOURCEREADERAVAILABLE 1024 /** No media source reader available */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTGETMEDIATYPEFRAMERATE 1025 /** Could not get media type framerate */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTGETMEDIATYPESIZE 1026 /** Could not get media type size */
#define LIBMCDRIVER_CAMERA_ERROR_INVALIDCAMERARESOLUTION 1027 /** Invalid camera resolution */
#define LIBMCDRIVER_CAMERA_ERROR_INVALIDCAMERAFRAMERATE 1028 /** Invalid camera framerate */
#define LIBMCDRIVER_CAMERA_ERROR_INVALIDMEDIATYPEFRAMERATE 1029 /** Invalid media type framerate */
#define LIBMCDRIVER_CAMERA_ERROR_INVALIDRESOLUTIONINDEX 1030 /** Invalid resolution index */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTQUERYMJPEGENCODERS 1031 /** Could not query MJPEG Encoders */
#define LIBMCDRIVER_CAMERA_ERROR_NOMJPEGENCODERFOUND 1032 /** No MJPEG Encoder found */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTACTIVATEMJPEGENCODER 1033 /** Could not activate MJPEG Encoder */
#define LIBMCDRIVER_CAMERA_ERROR_CAMERAREADERNOTINITIALIZED 1034 /** Camera reader not initialized */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTREADSAMPLEFRAME 1035 /** Could not read sample frame */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTREADSAMPLEBUFFER 1036 /** Could not read sample buffer */
#define LIBMCDRIVER_CAMERA_ERROR_COULDNOTLOCKMEDIABUFFER 1037 /** Could not lock media buffer */
#define LIBMCDRIVER_CAMERA_ERROR_RAWBUFFERRETURNEDNULL 1038 /** Raw buffer returned null */
#define LIBMCDRIVER_CAMERA_ERROR_YUY2SAMPLEBUFFERSIZEMISMATCH 1039 /** YUY2 sample buffer size mismatch */

/*************************************************************************************************************************
 Error strings for LibMCDriver_Camera
**************************************************************************************************************************/

inline const char * LIBMCDRIVER_CAMERA_GETERRORSTRING (LibMCDriver_CameraResult nErrorCode) {
  switch (nErrorCode) {
    case LIBMCDRIVER_CAMERA_SUCCESS: return "no error";
    case LIBMCDRIVER_CAMERA_ERROR_NOTIMPLEMENTED: return "functionality not implemented";
    case LIBMCDRIVER_CAMERA_ERROR_INVALIDPARAM: return "an invalid parameter was passed";
    case LIBMCDRIVER_CAMERA_ERROR_INVALIDCAST: return "a type cast failed";
    case LIBMCDRIVER_CAMERA_ERROR_BUFFERTOOSMALL: return "a provided buffer is too small";
    case LIBMCDRIVER_CAMERA_ERROR_GENERICEXCEPTION: return "a generic exception occurred";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTLOADLIBRARY: return "the library could not be loaded";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTFINDLIBRARYEXPORT: return "a required exported symbol could not be found in the library";
    case LIBMCDRIVER_CAMERA_ERROR_INCOMPATIBLEBINARYVERSION: return "the version of the binary interface does not match the bindings interface";
    case LIBMCDRIVER_CAMERA_ERROR_DRIVERERROR: return "a driver error occured";
    case LIBMCDRIVER_CAMERA_ERROR_DEVICENOTSUPPORTEDONPLATFORM: return "device not supported on platform";
    case LIBMCDRIVER_CAMERA_ERROR_INVALIDDEVICEINDEX: return "device not supported on platform";
    case LIBMCDRIVER_CAMERA_ERROR_CAMERADEVICENOTFOUND: return "camera device not found";
    case LIBMCDRIVER_CAMERA_ERROR_INVALIDDRIVERTYPE: return "invalid driver type";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTINITIALIZEWMF: return "could not initialize WMF";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTFILTERFORVIDEODEVICES: return "could not filter for video devices";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTENUMERATEDEVICESOURCES: return "could not enumerate device sources";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTCREATEWMFATTRIBUTES: return "could not create Windows Media Foundation Attributes";
    case LIBMCDRIVER_CAMERA_ERROR_WIDECHARTOUTF8CONVERSIONFAILED: return "Widechar to UTF8 conversion failed";
    case LIBMCDRIVER_CAMERA_ERROR_CAMERADEVICELISTOVERRUN: return "Camera device list overrun";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTOPENVIDEODEVICE: return "Could not open video device";
    case LIBMCDRIVER_CAMERA_ERROR_INVALIDCAMERAIDENTIFIERLENGTH: return "Invalid camera identifier length";
    case LIBMCDRIVER_CAMERA_ERROR_INVALIDCAMERAIDENTIFIER: return "Invalid camera identifier";
    case LIBMCDRIVER_CAMERA_ERROR_CAMERAIDENTIFIERALREADYREGISTERED: return "Camera identifier already registered";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTCREATEMEDIATYPE: return "Could not create media type";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETMEDIATYPETOVIDEO: return "Could not set media type to video";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETMEDIATYPEFORMAT: return "Could not set media type format";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETMEDIARESOLUTION: return "Could not set media resolution";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETMEDIAFRAMERATE: return "Could not set media framerate";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETPIXELASPECTRATIO: return "Could not set pixel aspect ratio";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTACTIVATEDEVICE: return "Could not activate device";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTCREATEREADER: return "Could not create reader";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTSETMEDIATYPE: return "Could not set media type";
    case LIBMCDRIVER_CAMERA_ERROR_NOMEDIASOURCEREADERAVAILABLE: return "No media source reader available";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTGETMEDIATYPEFRAMERATE: return "Could not get media type framerate";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTGETMEDIATYPESIZE: return "Could not get media type size";
    case LIBMCDRIVER_CAMERA_ERROR_INVALIDCAMERARESOLUTION: return "Invalid camera resolution";
    case LIBMCDRIVER_CAMERA_ERROR_INVALIDCAMERAFRAMERATE: return "Invalid camera framerate";
    case LIBMCDRIVER_CAMERA_ERROR_INVALIDMEDIATYPEFRAMERATE: return "Invalid media type framerate";
    case LIBMCDRIVER_CAMERA_ERROR_INVALIDRESOLUTIONINDEX: return "Invalid resolution index";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTQUERYMJPEGENCODERS: return "Could not query MJPEG Encoders";
    case LIBMCDRIVER_CAMERA_ERROR_NOMJPEGENCODERFOUND: return "No MJPEG Encoder found";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTACTIVATEMJPEGENCODER: return "Could not activate MJPEG Encoder";
    case LIBMCDRIVER_CAMERA_ERROR_CAMERAREADERNOTINITIALIZED: return "Camera reader not initialized";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTREADSAMPLEFRAME: return "Could not read sample frame";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTREADSAMPLEBUFFER: return "Could not read sample buffer";
    case LIBMCDRIVER_CAMERA_ERROR_COULDNOTLOCKMEDIABUFFER: return "Could not lock media buffer";
    case LIBMCDRIVER_CAMERA_ERROR_RAWBUFFERRETURNEDNULL: return "Raw buffer returned null";
    case LIBMCDRIVER_CAMERA_ERROR_YUY2SAMPLEBUFFERSIZEMISMATCH: return "YUY2 sample buffer size mismatch";
    default: return "unknown error";
  }
}

/*************************************************************************************************************************
 Declaration of handle classes 
**************************************************************************************************************************/

typedef LibMCDriver_CameraHandle LibMCDriver_Camera_Base;
typedef LibMCDriver_CameraHandle LibMCDriver_Camera_Driver;
typedef LibMCDriver_CameraHandle LibMCDriver_Camera_DeviceBase;
typedef LibMCDriver_CameraHandle LibMCDriver_Camera_VideoDevice;
typedef LibMCDriver_CameraHandle LibMCDriver_Camera_DeviceInfo;
typedef LibMCDriver_CameraHandle LibMCDriver_Camera_DeviceList;
typedef LibMCDriver_CameraHandle LibMCDriver_Camera_Driver_Camera;
typedef LibMCDriver_CameraHandle LibMCDriver_Camera_Driver_Camera_Windows;

namespace LibMCDriver_Camera {

} // namespace LibMCDriver_Camera;

// define legacy C-names for enums, structs and function types

#endif // __LIBMCDRIVER_CAMERA_TYPES_HEADER_CPP
