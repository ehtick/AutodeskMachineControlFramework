/*++

Copyright (C) 2020 Autodesk Inc.

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


This file has been generated by the Automatic Component Toolkit (ACT) version 1.7.0-develop.

Abstract: This is an autogenerated C++-Header file with basic types in
order to allow an easy use of MC Driver BR Automation 2.0

Interface version: 1.0.0

*/

#ifndef __LIBMCDRIVER_BUR_TYPES_HEADER_CPP
#define __LIBMCDRIVER_BUR_TYPES_HEADER_CPP


/*************************************************************************************************************************
 Scalar types definition
**************************************************************************************************************************/

#ifdef LIBMCDRIVER_BUR_USELEGACYINTEGERTYPES

typedef unsigned char LibMCDriver_BuR_uint8;
typedef unsigned short LibMCDriver_BuR_uint16 ;
typedef unsigned int LibMCDriver_BuR_uint32;
typedef unsigned long long LibMCDriver_BuR_uint64;
typedef char LibMCDriver_BuR_int8;
typedef short LibMCDriver_BuR_int16;
typedef int LibMCDriver_BuR_int32;
typedef long long LibMCDriver_BuR_int64;

#else // LIBMCDRIVER_BUR_USELEGACYINTEGERTYPES

#include <stdint.h>

typedef uint8_t LibMCDriver_BuR_uint8;
typedef uint16_t LibMCDriver_BuR_uint16;
typedef uint32_t LibMCDriver_BuR_uint32;
typedef uint64_t LibMCDriver_BuR_uint64;
typedef int8_t LibMCDriver_BuR_int8;
typedef int16_t LibMCDriver_BuR_int16;
typedef int32_t LibMCDriver_BuR_int32;
typedef int64_t LibMCDriver_BuR_int64 ;

#endif // LIBMCDRIVER_BUR_USELEGACYINTEGERTYPES

typedef float LibMCDriver_BuR_single;
typedef double LibMCDriver_BuR_double;

/*************************************************************************************************************************
 General type definitions
**************************************************************************************************************************/

typedef LibMCDriver_BuR_int32 LibMCDriver_BuRResult;
typedef void * LibMCDriver_BuRHandle;
typedef void * LibMCDriver_BuR_pvoid;

/*************************************************************************************************************************
 Version for LibMCDriver_BuR
**************************************************************************************************************************/

#define LIBMCDRIVER_BUR_VERSION_MAJOR 1
#define LIBMCDRIVER_BUR_VERSION_MINOR 0
#define LIBMCDRIVER_BUR_VERSION_MICRO 0
#define LIBMCDRIVER_BUR_VERSION_PRERELEASEINFO ""
#define LIBMCDRIVER_BUR_VERSION_BUILDINFO ""

/*************************************************************************************************************************
 Error constants for LibMCDriver_BuR
**************************************************************************************************************************/

#define LIBMCDRIVER_BUR_SUCCESS 0
#define LIBMCDRIVER_BUR_ERROR_NOTIMPLEMENTED 1
#define LIBMCDRIVER_BUR_ERROR_INVALIDPARAM 2
#define LIBMCDRIVER_BUR_ERROR_INVALIDCAST 3
#define LIBMCDRIVER_BUR_ERROR_BUFFERTOOSMALL 4
#define LIBMCDRIVER_BUR_ERROR_GENERICEXCEPTION 5
#define LIBMCDRIVER_BUR_ERROR_COULDNOTLOADLIBRARY 6
#define LIBMCDRIVER_BUR_ERROR_COULDNOTFINDLIBRARYEXPORT 7
#define LIBMCDRIVER_BUR_ERROR_INCOMPATIBLEBINARYVERSION 8
#define LIBMCDRIVER_BUR_ERROR_INVALIDSTATENAME 9
#define LIBMCDRIVER_BUR_ERROR_DRIVERERROR 1000
#define LIBMCDRIVER_BUR_ERROR_DRIVERNOTINITIALISED 1001
#define LIBMCDRIVER_BUR_ERROR_DRIVERNOTCONNECTED 1002
#define LIBMCDRIVER_BUR_ERROR_INVALIDDRIVERPROTOCOL 1003
#define LIBMCDRIVER_BUR_ERROR_COULDNOTPARSEDRIVERPROTOCOL 1004
#define LIBMCDRIVER_BUR_ERROR_NOMACHINESTATUSDEFINITION 1005
#define LIBMCDRIVER_BUR_ERROR_NONAMEATTRIBUTE 1010
#define LIBMCDRIVER_BUR_ERROR_NOADDRESSEATTRIBUTE 1011
#define LIBMCDRIVER_BUR_ERROR_NODESCRIPTIONATTRIBUTE 1012
#define LIBMCDRIVER_BUR_ERROR_NOBITATTRIBUTE 1013
#define LIBMCDRIVER_BUR_ERROR_INVALIDNAMEATTRIBUTE 1014
#define LIBMCDRIVER_BUR_ERROR_INVALIDADDRESSEATTRIBUTE 1015
#define LIBMCDRIVER_BUR_ERROR_INVALIDDESCRIPTIONATTRIBUTE 1016
#define LIBMCDRIVER_BUR_ERROR_INVALIDBITATTRIBUTE 1017
#define LIBMCDRIVER_BUR_ERROR_INVALIDCPUTYPE 1018
#define LIBMCDRIVER_BUR_ERROR_UNKNOWNCOMMANDNAME 1022
#define LIBMCDRIVER_BUR_ERROR_NOCOMMANDNAME 1023
#define LIBMCDRIVER_BUR_ERROR_NOCOMMANDID 1024
#define LIBMCDRIVER_BUR_ERROR_INVALIDCOMMANDNAME 1025
#define LIBMCDRIVER_BUR_ERROR_INVALIDCOMMANDID 1026
#define LIBMCDRIVER_BUR_ERROR_COMMANDHASALREADYBEENEXECUTED 1027
#define LIBMCDRIVER_BUR_ERROR_COMMANDHASNOTBEENEXECUTED 1028
#define LIBMCDRIVER_BUR_ERROR_INVALIDSEQUENCEID 1029
#define LIBMCDRIVER_BUR_ERROR_COMMANDSEQUENCEERROR 1030
#define LIBMCDRIVER_BUR_ERROR_COMMANDREACTIONTIMEOUT 1031
#define LIBMCDRIVER_BUR_ERROR_NOCOMMANDSDEFINITION 1032
#define LIBMCDRIVER_BUR_ERROR_NOVERSIONDEFINITION 1033
#define LIBMCDRIVER_BUR_ERROR_NOMAJORVERSION 1034
#define LIBMCDRIVER_BUR_ERROR_NOMINORVERSION 1035
#define LIBMCDRIVER_BUR_ERROR_NOPATCHVERSION 1036
#define LIBMCDRIVER_BUR_ERROR_COULDNOTFINDADDRESS 1039
#define LIBMCDRIVER_BUR_ERROR_FIELDISNOINTPARAM 1040
#define LIBMCDRIVER_BUR_ERROR_FIELDISNODINTPARAM 1041
#define LIBMCDRIVER_BUR_ERROR_FIELDISNOSTRINGPARAM 1042
#define LIBMCDRIVER_BUR_ERROR_NOLENGTHATTRIBUTE 1043
#define LIBMCDRIVER_BUR_ERROR_INVALIDLENGTHATTRIBUTE 1044
#define LIBMCDRIVER_BUR_ERROR_COMMANDPARAMETERNAMEMISSING 1045
#define LIBMCDRIVER_BUR_ERROR_COMMANDPARAMETERDESCRIPTIONMISSING 1046
#define LIBMCDRIVER_BUR_ERROR_COMMANDPARAMETERFIELDMISSING 1047
#define LIBMCDRIVER_BUR_ERROR_COMMANDPARAMETERNOTFOUND 1048
#define LIBMCDRIVER_BUR_ERROR_COMMANDFIELDNOTFOUND 1049
#define LIBMCDRIVER_BUR_ERROR_INVALIDPARAMETERTYPE 1050
#define LIBMCDRIVER_BUR_ERROR_COMMANDPARAMETEROUTOFBOUNDS 1051
#define LIBMCDRIVER_BUR_ERROR_INVALIDPARAMETERADDRESS 1052
#define LIBMCDRIVER_BUR_ERROR_STRINGPARAMETEROVERFLOW 1053
#define LIBMCDRIVER_BUR_ERROR_RECEIVEDINVALIDPACKETSIGNATURE 1054
#define LIBMCDRIVER_BUR_ERROR_INVALIDTCPCONNECTIONPOINTER 1055
#define LIBMCDRIVER_BUR_ERROR_INVALIDCLIENTSEQUENCEID 1056
#define LIBMCDRIVER_BUR_ERROR_INVALIDCLIENTID 1057
#define LIBMCDRIVER_BUR_ERROR_PACKETQUEUEOVERFLOW 1058
#define LIBMCDRIVER_BUR_ERROR_NOCOMMANDSLIST 1059
#define LIBMCDRIVER_BUR_ERROR_COMMANDNAMEMISSING 1060
#define LIBMCDRIVER_BUR_ERROR_COMMANDIDMISSING 1061
#define LIBMCDRIVER_BUR_ERROR_DUPLICATECOMMANDPARAMETER 1062
#define LIBMCDRIVER_BUR_ERROR_INTEGERPARAMETERNOTFOUND 1063
#define LIBMCDRIVER_BUR_ERROR_BOOLPARAMETERNOTFOUND 1064
#define LIBMCDRIVER_BUR_ERROR_DOUBLEPARAMETERNOTFOUND 1065
#define LIBMCDRIVER_BUR_ERROR_VALUEISNOTINTEGERVALUE 1066
#define LIBMCDRIVER_BUR_ERROR_VALUEISNOTBOOLVALUE 1067
#define LIBMCDRIVER_BUR_ERROR_VALUEISNOTDOUBLEVALUE 1068
#define LIBMCDRIVER_BUR_ERROR_COMMANDDEFINITIONNOTFOUND 1069
#define LIBMCDRIVER_BUR_ERROR_NOTCONNECTED 1070
#define LIBMCDRIVER_BUR_ERROR_COULDNOTGETADDRESSINFO 1071
#define LIBMCDRIVER_BUR_ERROR_COULDNOTCREATESOCKET 1072
#define LIBMCDRIVER_BUR_ERROR_COULDNOTCONNECT 1073
#define LIBMCDRIVER_BUR_ERROR_SENDERROR 1074
#define LIBMCDRIVER_BUR_ERROR_RECEIVECOUNTEXCEEDSMAXIMUM 1075
#define LIBMCDRIVER_BUR_ERROR_CONNECTIONCLOSED 1076
#define LIBMCDRIVER_BUR_ERROR_RECEIVEERROR 1077
#define LIBMCDRIVER_BUR_ERROR_SENDCOUNTEXCEEDSMAXIMUM 1078
#define LIBMCDRIVER_BUR_ERROR_RECEIVEDINVALIDPACKETLENGTH 1079
#define LIBMCDRIVER_BUR_ERROR_COULDNOTWRITETOPAYLOAD 1080
#define LIBMCDRIVER_BUR_ERROR_INVALIDPAYLOADADDRESS 1081

/*************************************************************************************************************************
 Error strings for LibMCDriver_BuR
**************************************************************************************************************************/

inline const char * LIBMCDRIVER_BUR_GETERRORSTRING (LibMCDriver_BuRResult nErrorCode) {
  switch (nErrorCode) {
    case LIBMCDRIVER_BUR_SUCCESS: return "no error";
    case LIBMCDRIVER_BUR_ERROR_NOTIMPLEMENTED: return "functionality not implemented";
    case LIBMCDRIVER_BUR_ERROR_INVALIDPARAM: return "an invalid parameter was passed";
    case LIBMCDRIVER_BUR_ERROR_INVALIDCAST: return "a type cast failed";
    case LIBMCDRIVER_BUR_ERROR_BUFFERTOOSMALL: return "a provided buffer is too small";
    case LIBMCDRIVER_BUR_ERROR_GENERICEXCEPTION: return "a generic exception occurred";
    case LIBMCDRIVER_BUR_ERROR_COULDNOTLOADLIBRARY: return "the library could not be loaded";
    case LIBMCDRIVER_BUR_ERROR_COULDNOTFINDLIBRARYEXPORT: return "a required exported symbol could not be found in the library";
    case LIBMCDRIVER_BUR_ERROR_INCOMPATIBLEBINARYVERSION: return "the version of the binary interface does not match the bindings interface";
    case LIBMCDRIVER_BUR_ERROR_INVALIDSTATENAME: return "invalid state name";
    case LIBMCDRIVER_BUR_ERROR_DRIVERERROR: return "a driver error occured";
    case LIBMCDRIVER_BUR_ERROR_DRIVERNOTINITIALISED: return "the driver is not initialised";
    case LIBMCDRIVER_BUR_ERROR_DRIVERNOTCONNECTED: return "the driver is not connected";
    case LIBMCDRIVER_BUR_ERROR_INVALIDDRIVERPROTOCOL: return "invalid driver protocol definition";
    case LIBMCDRIVER_BUR_ERROR_COULDNOTPARSEDRIVERPROTOCOL: return "could not parse driver protocol";
    case LIBMCDRIVER_BUR_ERROR_NOMACHINESTATUSDEFINITION: return "no machine status definition";
    case LIBMCDRIVER_BUR_ERROR_NONAMEATTRIBUTE: return "no name attribute";
    case LIBMCDRIVER_BUR_ERROR_NOADDRESSEATTRIBUTE: return "no address attribute";
    case LIBMCDRIVER_BUR_ERROR_NODESCRIPTIONATTRIBUTE: return "no description attribute";
    case LIBMCDRIVER_BUR_ERROR_NOBITATTRIBUTE: return "no bit attribute";
    case LIBMCDRIVER_BUR_ERROR_INVALIDNAMEATTRIBUTE: return "invalid name attribute";
    case LIBMCDRIVER_BUR_ERROR_INVALIDADDRESSEATTRIBUTE: return "invalid address attribute";
    case LIBMCDRIVER_BUR_ERROR_INVALIDDESCRIPTIONATTRIBUTE: return "invalid description attribute";
    case LIBMCDRIVER_BUR_ERROR_INVALIDBITATTRIBUTE: return "invalid bit attribute";
    case LIBMCDRIVER_BUR_ERROR_INVALIDCPUTYPE: return "invalid cpu type";
    case LIBMCDRIVER_BUR_ERROR_UNKNOWNCOMMANDNAME: return "unknown command name";
    case LIBMCDRIVER_BUR_ERROR_NOCOMMANDNAME: return "no command name";
    case LIBMCDRIVER_BUR_ERROR_NOCOMMANDID: return "no command id";
    case LIBMCDRIVER_BUR_ERROR_INVALIDCOMMANDNAME: return "invalid command name";
    case LIBMCDRIVER_BUR_ERROR_INVALIDCOMMANDID: return "invalid command id";
    case LIBMCDRIVER_BUR_ERROR_COMMANDHASALREADYBEENEXECUTED: return "command has already been executed";
    case LIBMCDRIVER_BUR_ERROR_COMMANDHASNOTBEENEXECUTED: return "command has not been executed";
    case LIBMCDRIVER_BUR_ERROR_INVALIDSEQUENCEID: return "invalid sequence id";
    case LIBMCDRIVER_BUR_ERROR_COMMANDSEQUENCEERROR: return "command sequence communication error";
    case LIBMCDRIVER_BUR_ERROR_COMMANDREACTIONTIMEOUT: return "command reaction timeout";
    case LIBMCDRIVER_BUR_ERROR_NOCOMMANDSDEFINITION: return "no commands definition";
    case LIBMCDRIVER_BUR_ERROR_NOVERSIONDEFINITION: return "no version definition";
    case LIBMCDRIVER_BUR_ERROR_NOMAJORVERSION: return "no major version";
    case LIBMCDRIVER_BUR_ERROR_NOMINORVERSION: return "no minor version";
    case LIBMCDRIVER_BUR_ERROR_NOPATCHVERSION: return "no patch version";
    case LIBMCDRIVER_BUR_ERROR_COULDNOTFINDADDRESS: return "could not find address";
    case LIBMCDRIVER_BUR_ERROR_FIELDISNOINTPARAM: return "field is no int parameter";
    case LIBMCDRIVER_BUR_ERROR_FIELDISNODINTPARAM: return "field is no dint parameter";
    case LIBMCDRIVER_BUR_ERROR_FIELDISNOSTRINGPARAM: return "field is no string parameter";
    case LIBMCDRIVER_BUR_ERROR_NOLENGTHATTRIBUTE: return "no length attribute";
    case LIBMCDRIVER_BUR_ERROR_INVALIDLENGTHATTRIBUTE: return "invalid length attribute";
    case LIBMCDRIVER_BUR_ERROR_COMMANDPARAMETERNAMEMISSING: return "command parameter name missing";
    case LIBMCDRIVER_BUR_ERROR_COMMANDPARAMETERDESCRIPTIONMISSING: return "command parameter description missing";
    case LIBMCDRIVER_BUR_ERROR_COMMANDPARAMETERFIELDMISSING: return "command parameter field missing";
    case LIBMCDRIVER_BUR_ERROR_COMMANDPARAMETERNOTFOUND: return "command parameter not found";
    case LIBMCDRIVER_BUR_ERROR_COMMANDFIELDNOTFOUND: return "command field not found";
    case LIBMCDRIVER_BUR_ERROR_INVALIDPARAMETERTYPE: return "command field parameter is of wrong type";
    case LIBMCDRIVER_BUR_ERROR_COMMANDPARAMETEROUTOFBOUNDS: return "command field parameter is out of bounds";
    case LIBMCDRIVER_BUR_ERROR_INVALIDPARAMETERADDRESS: return "invalid parameter address";
    case LIBMCDRIVER_BUR_ERROR_STRINGPARAMETEROVERFLOW: return "string parameter overflow";
    case LIBMCDRIVER_BUR_ERROR_RECEIVEDINVALIDPACKETSIGNATURE: return "received invalid packet signature";
    case LIBMCDRIVER_BUR_ERROR_INVALIDTCPCONNECTIONPOINTER: return "invalid tcp connection pointer";
    case LIBMCDRIVER_BUR_ERROR_INVALIDCLIENTSEQUENCEID: return "Invalid client sequence id";
    case LIBMCDRIVER_BUR_ERROR_INVALIDCLIENTID: return "Invalid client id";
    case LIBMCDRIVER_BUR_ERROR_PACKETQUEUEOVERFLOW: return "Packet queue overflow.";
    case LIBMCDRIVER_BUR_ERROR_NOCOMMANDSLIST: return "No commands list.";
    case LIBMCDRIVER_BUR_ERROR_COMMANDNAMEMISSING: return "Command name missing.";
    case LIBMCDRIVER_BUR_ERROR_COMMANDIDMISSING: return "Command ID missing.";
    case LIBMCDRIVER_BUR_ERROR_DUPLICATECOMMANDPARAMETER: return "Duplicate command parameter.";
    case LIBMCDRIVER_BUR_ERROR_INTEGERPARAMETERNOTFOUND: return "Integer parameter not found.";
    case LIBMCDRIVER_BUR_ERROR_BOOLPARAMETERNOTFOUND: return "Bool parameter not found.";
    case LIBMCDRIVER_BUR_ERROR_DOUBLEPARAMETERNOTFOUND: return "Double parameter not found.";
    case LIBMCDRIVER_BUR_ERROR_VALUEISNOTINTEGERVALUE: return "Value is not integer value.";
    case LIBMCDRIVER_BUR_ERROR_VALUEISNOTBOOLVALUE: return "Value is not bool value.";
    case LIBMCDRIVER_BUR_ERROR_VALUEISNOTDOUBLEVALUE: return "Value is not double value.";
    case LIBMCDRIVER_BUR_ERROR_COMMANDDEFINITIONNOTFOUND: return "Command definition not found.";
    case LIBMCDRIVER_BUR_ERROR_NOTCONNECTED: return "Not connected.";
    case LIBMCDRIVER_BUR_ERROR_COULDNOTGETADDRESSINFO: return "Could not get address info.";
    case LIBMCDRIVER_BUR_ERROR_COULDNOTCREATESOCKET: return "Could not create socket.";
    case LIBMCDRIVER_BUR_ERROR_COULDNOTCONNECT: return "Could not connect.";
    case LIBMCDRIVER_BUR_ERROR_SENDERROR: return "Send error.";
    case LIBMCDRIVER_BUR_ERROR_RECEIVECOUNTEXCEEDSMAXIMUM: return "Receive count exceeds maximum.";
    case LIBMCDRIVER_BUR_ERROR_CONNECTIONCLOSED: return "Connection closed.";
    case LIBMCDRIVER_BUR_ERROR_RECEIVEERROR: return "Receive error.";
    case LIBMCDRIVER_BUR_ERROR_SENDCOUNTEXCEEDSMAXIMUM: return "Send count exceeds maximum.";
    case LIBMCDRIVER_BUR_ERROR_RECEIVEDINVALIDPACKETLENGTH: return "Received invalid packet length.";
    case LIBMCDRIVER_BUR_ERROR_COULDNOTWRITETOPAYLOAD: return "Could not write to payload.";
    case LIBMCDRIVER_BUR_ERROR_INVALIDPAYLOADADDRESS: return "Invalid payload address.";
    default: return "unknown error";
  }
}

/*************************************************************************************************************************
 Declaration of handle classes 
**************************************************************************************************************************/

typedef LibMCDriver_BuRHandle LibMCDriver_BuR_Base;
typedef LibMCDriver_BuRHandle LibMCDriver_BuR_Driver;
typedef LibMCDriver_BuRHandle LibMCDriver_BuR_PLCCommand;
typedef LibMCDriver_BuRHandle LibMCDriver_BuR_PLCCommandList;
typedef LibMCDriver_BuRHandle LibMCDriver_BuR_Driver_BuR;

namespace LibMCDriver_BuR {

} // namespace LibMCDriver_BuR;

// define legacy C-names for enums, structs and function types

#endif // __LIBMCDRIVER_BUR_TYPES_HEADER_CPP