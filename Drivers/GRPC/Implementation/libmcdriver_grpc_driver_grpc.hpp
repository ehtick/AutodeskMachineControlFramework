/*++

Copyright (C) 2023 Autodesk Inc.

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


Abstract: This is the class declaration of CDriver_GRPC

*/


#ifndef __LIBMCDRIVER_GRPC_DRIVER_GRPC
#define __LIBMCDRIVER_GRPC_DRIVER_GRPC

#include "libmcdriver_grpc_interfaces.hpp"

// Parent classes
#include "libmcdriver_grpc_driver.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.
#include "libgrpcwrapper_dynamic.hpp"
#include <map>
namespace LibMCDriver_GRPC {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CDriver_GRPC 
**************************************************************************************************************************/

class CDriver_GRPC : public virtual IDriver_GRPC, public virtual CDriver {
private:

	std::string m_sName;
	LibMCEnv::PDriverEnvironment m_pDriverEnvironment;
	bool m_bSimulationMode;

	LibMCEnv::PWorkingDirectory m_pWorkingDirectory;

	std::map<std::string, LibGRPCWrapper::PConnection> m_Connections;

#ifdef _WIN32

	std::wstring m_sDLLDirectoryW;

	LibMCEnv::PWorkingFile m_pGRPCDLL_AbseilDLL;
	LibMCEnv::PWorkingFile m_pGRPCDLL_Cares;
	LibMCEnv::PWorkingFile m_pGRPCDLL_LibCrypto3;
	LibMCEnv::PWorkingFile m_pGRPCDLL_LibGRPCWrapper;
	LibMCEnv::PWorkingFile m_pGRPCDLL_LibProtobuf;
	LibMCEnv::PWorkingFile m_pGRPCDLL_LibProtobufLite;
	LibMCEnv::PWorkingFile m_pGRPCDLL_LibSSL;
	LibMCEnv::PWorkingFile m_pGRPCDLL_Re2;
	LibMCEnv::PWorkingFile m_pGRPCDLL_ZLib;
#endif

	LibGRPCWrapper::PWrapper m_pGRPCWrapper;
	LibGRPCWrapper::PConnection m_pGRPCConnection;

	void loadGRPCSDK();

public:

	CDriver_GRPC (const std::string & sName, LibMCEnv::PDriverEnvironment pDriverEnvironment);

	virtual ~CDriver_GRPC();

	void Configure(const std::string& sConfigurationString) override;

	std::string GetName() override;

	std::string GetType() override;

	void GetVersion(LibMCDriver_GRPC_uint32& nMajor, LibMCDriver_GRPC_uint32& nMinor, LibMCDriver_GRPC_uint32& nMicro, std::string& sBuild) override;

	void QueryParameters() override;

	void QueryParametersEx(LibMCEnv::PDriverStatusUpdateSession pDriverUpdateInstance) override;

	void SetToSimulationMode() override;

	bool IsSimulationMode() override;

	IGRPCConnection* ConnectUnsecure(const std::string& sIdentifier, const std::string& sNetworkCredentials, const std::string& sProtobufDefinition);

	IGRPCConnection* FindConnection(const std::string& sIdentifier, const bool bMustExist) override;

};

} // namespace Impl
} // namespace LibMCDriver_GRPC

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // __LIBMCDRIVER_GRPC_DRIVER_GRPC