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


Abstract: This is the class declaration of CBuildJobHandler

*/


#ifndef __LIBMCDATA_BUILDJOBHANDLER
#define __LIBMCDATA_BUILDJOBHANDLER

#include "libmcdata_interfaces.hpp"
#include <vector>

// Parent classes
#include "libmcdata_base.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.
#include "amcdata_sqlhandler.hpp"
#include "amcdata_storagestate.hpp"

#include <mutex>
#include <thread>


namespace LibMCData {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CBuildJobHandler 
**************************************************************************************************************************/

class CBuildJobHandler : public virtual IBuildJobHandler, public virtual CBase {
private:

	AMCData::PSQLHandler m_pSQLHandler;
    AMCData::PStorageState m_pStorageState;

protected:




public:


    CBuildJobHandler(AMCData::PSQLHandler pSQLHandler, AMCData::PStorageState pStorageState);

    IBuildJob* CreateJob(const std::string& sJobUUID, const std::string& sName, const std::string& sUserID, const std::string& sStorageStreamUUID, const LibMCData_uint64 nAbsoluteTimeStamp) override;

    bool JobExists(const std::string& sJobUUID) override;

	IBuildJob * RetrieveJob(const std::string & sJobUUID) override;

	IBuildJobIterator * ListJobsByStatus(const LibMCData::eBuildJobStatus eStatus) override;

    IBuildJob* FindJobOfData(const std::string& sDataUUID) override;

    std::string ConvertBuildStatusToString(const LibMCData::eBuildJobStatus eStatus) override;

    LibMCData::eBuildJobStatus ConvertStringToBuildStatus(const std::string& sString) override;

    IBuildJobExecution* RetrieveJobExecution(const std::string& sExecutionUUID) override;

    IBuildJobExecutionIterator* ListJobExecutions(const std::string& sMinTimestamp, const std::string& sMaxTimestamp, const std::string& sJournalUUIDFilter) override;

};

} // namespace Impl
} // namespace LibMCData

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // __LIBMCDATA_BUILDJOBHANDLER
