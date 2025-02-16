/*++

Copyright (C) 2024 ASL Inc.

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


Abstract: This is the class declaration of CDriver_ASL

*/


#ifndef __LIBMCDRIVER_ASL_DRIVER_ASL
#define __LIBMCDRIVER_ASL_DRIVER_ASL

#include "libmcdriver_asl_interfaces.hpp"

// Parent classes
#include "libmcdriver_asl_driver.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.
#include "libmcdriver_asl_drivercontextinstance.hpp"

#include <string>
#include <map>

namespace LibMCDriver_ASL {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CDriver_ASL 
**************************************************************************************************************************/

class CDriver_ASL : public virtual IDriver_ASL, public virtual CDriver {
private:

	std::string m_sName;
	LibMCEnv::PDriverEnvironment m_pDriverEnvironment;
	bool m_bSimulationMode;

	std::map<std::string, std::shared_ptr<CDriverContextInstance>> m_InstanceMap;

public:

	CDriver_ASL(const std::string& sName, LibMCEnv::PDriverEnvironment pDriverEnvironment);

	virtual ~CDriver_ASL();


	void SetToSimulationMode() override;

	bool IsSimulationMode() override;

	IDriverContext * Connect(const std::string & sIdentifier, const std::string & sCOMPort) override;

	bool ContextExists(const std::string & sIdentifier) override;
	void ClearContexts() override;

	IDriverContext * FindContext(const std::string & sIdentifier) override;

	void Configure(const std::string& sConfigurationString) override;

	std::string GetName() override;

	static std::string getTypeStatic();

	std::string GetType() override;

	void GetVersion(LibMCDriver_ASL_uint32& nMajor, LibMCDriver_ASL_uint32& nMinor, LibMCDriver_ASL_uint32& nMicro, std::string& sBuild) override;

	void QueryParameters() override;

	void QueryParametersEx(LibMCEnv::PDriverStatusUpdateSession pDriverUpdateInstance) override;


};

} // namespace Impl
} // namespace LibMCDriver_ASL

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // __LIBMCDRIVER_ASL_DRIVER_ASL
