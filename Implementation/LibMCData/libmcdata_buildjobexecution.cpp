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


Abstract: This is a stub class definition of CBuildJobExecution

*/

#include "libmcdata_buildjobexecution.hpp"
#include "libmcdata_interfaceexception.hpp"

// Include custom headers here.
#include "libmcdata_buildjobexecutiondata.hpp"
#include "libmcdata_buildjobexecutiondataiterator.hpp"
#include "libmcdata_buildjob.hpp"
#include "common_utils.hpp"
#include "common_chrono.hpp"

using namespace LibMCData::Impl;

/*************************************************************************************************************************
 Class definition of CBuildJobExecution 
**************************************************************************************************************************/

CBuildJobExecution::CBuildJobExecution(AMCData::PSQLHandler pSQLHandler, const std::string& sExecutionUUID, const std::string& sJobUUID, const std::string& sJournalUUID, const std::string& sUserUUID, uint64_t nStartJournalTimeStamp, const std::string& sJobName, eBuildJobStatus jobStatus, uint32_t nJobLayerCount, AMCData::PStorageState pStorageState)
	: m_pSQLHandler (pSQLHandler),
	m_sExecutionUUID (AMCCommon::CUtils::normalizeUUIDString (sExecutionUUID)),
	m_pStorageState (pStorageState),
	m_sJobUUID (AMCCommon::CUtils::normalizeUUIDString (sJobUUID)),
	m_sJournalUUID(AMCCommon::CUtils::normalizeUUIDString(sJournalUUID)),
	m_sUserUUID(AMCCommon::CUtils::normalizeUUIDString(sUserUUID)),
	m_nStartJournalTimestamp (nStartJournalTimeStamp),
	m_sJobName (sJobName),
	m_JobStatus (jobStatus),
	m_nJobLayerCount (nJobLayerCount)
{
	if (pSQLHandler.get() == nullptr)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);
	if (pStorageState.get () == nullptr)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

}

CBuildJobExecution::~CBuildJobExecution()
{

}

CBuildJobExecution* CBuildJobExecution::makeFromStatement(AMCData::PSQLHandler pSQLHandler, AMCData::PSQLStatement pStatement, AMCData::PStorageState pStorageState)
{
	// ATTENTION: All callers of makeFromStatement MUST BE in Sync in terms of column order!!
	// Column 1: Execution UUID
	// Column 2: Job UUID
	// Column 3: Journal UUID
	// Column 4: User UUID
	// Column 5: Start TimeStamp
	// Column 6: Job Name
	// Column 7: Job Status
	// Column 8: Job Layer Count

	if (pStatement.get() == nullptr)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

	std::string sExecutionUUID = AMCCommon::CUtils::normalizeUUIDString(pStatement->getColumnString(1));
	std::string sJobUUID = AMCCommon::CUtils::normalizeUUIDString(pStatement->getColumnString(2));
	std::string sJournalUUID = AMCCommon::CUtils::normalizeUUIDString(pStatement->getColumnString(3));
	std::string sUserUUID = AMCCommon::CUtils::normalizeUUIDString(pStatement->getColumnString(4));
	int64_t nStartTimeStamp = AMCCommon::CChrono::parseISO8601TimeUTC(pStatement->getColumnString(5));
	if (nStartTimeStamp < 0)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDBUILDJOBEXECUTIONSTART, "invalid build job execution start: " + sExecutionUUID);
	if (!AMCCommon::CChrono::timeStampIsWithinAMillionYears((uint64_t)nStartTimeStamp))
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDBUILDJOBEXECUTIONSTART, "invalid build job execution start: " + sExecutionUUID);

	uint64_t nStartJournalTimestamp = (uint64_t)nStartTimeStamp;

	std::string sJobName = pStatement->getColumnString(6);
	eBuildJobStatus jobStatus = CBuildJob::convertStringToBuildJobStatus (pStatement->getColumnString(7));	
	int32_t nLayerCount = pStatement->getColumnInt(8);
	if (nLayerCount < 0)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDBUILDJOBLAYERCOUNT, "invalid build job layer count: " + sJobUUID);

	auto pExecution = std::make_unique<CBuildJobExecution>(pSQLHandler, sExecutionUUID, sJobUUID, sJournalUUID, sUserUUID, nStartJournalTimestamp, sJobName, jobStatus, (uint32_t) nLayerCount, pStorageState);

	return pExecution.release();
}


CBuildJobExecution* CBuildJobExecution::makeFromDatabase(AMCData::PSQLHandler pSQLHandler, const std::string& sExecutionUUID, AMCData::PStorageState pStorageState)
{
	std::string sNormalizedExecutionUUID = AMCCommon::CUtils::normalizeUUIDString(sExecutionUUID);

	if (pSQLHandler.get() == nullptr)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

	// Retrieve non-mutable values at the beginning
	std::string sSelectQuery = "SELECT buildjobexecutions.uuid, buildjobexecutions.jobuuid, buildjobexecutions.journaluuid, buildjobexecutions.useruuid, buildjobexecutions.startjournaltimestamp, buildjobs.name, buildjobs.status, buildjobs.layercount FROM buildjobexecutions LEFT JOIN buildjobs ON buildjobs.uuid=buildjobexecutions.jobuuid WHERE buildjobexecutions.active=1 AND buildjobexecutions.uuid=?";
	auto pSelectStatement = pSQLHandler->prepareStatement(sSelectQuery);
	pSelectStatement->setString(1, sNormalizedExecutionUUID);

	if (!pSelectStatement->nextRow())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONNOTFOUND, "build job execution not found: " + sNormalizedExecutionUUID);

	// ATTENTION: All callers of makeFromStatement MUST BE in Sync in terms of column order!!
	// Column 1: Execution UUID
	// Column 2: Job UUID
	// Column 3: Journal UUID
	// Column 4: User UUID
	// Column 5: Start TimeStamp
	// Column 6: Job Name
	// Column 7: Job Status
	// Column 8: Job Layer Count

	return makeFromStatement(pSQLHandler, pSelectStatement, pStorageState);
}


std::shared_ptr<CBuildJobExecution> CBuildJobExecution::makeSharedFromDatabase(AMCData::PSQLHandler pSQLHandler, const std::string& sExecutionUUID, AMCData::PStorageState pStorageState)
{
	return std::shared_ptr<CBuildJobExecution>(makeFromDatabase(pSQLHandler, sExecutionUUID, pStorageState));
}

std::shared_ptr<CBuildJobExecution> CBuildJobExecution::makeSharedFromStatement(AMCData::PSQLHandler pSQLHandler, AMCData::PSQLStatement pStatement, AMCData::PStorageState pStorageState)
{
	return std::shared_ptr<CBuildJobExecution>(makeFromStatement(pSQLHandler, pStatement, pStorageState));
}


CBuildJobExecution* CBuildJobExecution::makeFrom(CBuildJobExecution* pBuildJobExecution)
{
	if (pBuildJobExecution == nullptr)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

	return new CBuildJobExecution(pBuildJobExecution->m_pSQLHandler, pBuildJobExecution->m_sExecutionUUID, pBuildJobExecution->m_sJobUUID, pBuildJobExecution->m_sJournalUUID, pBuildJobExecution->m_sUserUUID, pBuildJobExecution->m_nStartJournalTimestamp, pBuildJobExecution->m_sJobName, pBuildJobExecution->m_JobStatus, pBuildJobExecution->m_nJobLayerCount,  pBuildJobExecution->m_pStorageState);
}

std::shared_ptr<CBuildJobExecution> CBuildJobExecution::makeSharedFrom(CBuildJobExecution* pBuildJobExecution)
{
	return std::shared_ptr<CBuildJobExecution>(makeFrom (pBuildJobExecution));
}


std::string CBuildJobExecution::GetExecutionUUID()
{
	return m_sExecutionUUID;
}

std::string CBuildJobExecution::GetJobUUID()
{
	return m_sJobUUID;
}

std::string CBuildJobExecution::GetJobName()
{
	return m_sJobName;
}

LibMCData::eBuildJobStatus CBuildJobExecution::GetJobStatus()
{
	return m_JobStatus;
}

std::string CBuildJobExecution::GetJobStatusString()
{
	return CBuildJob::convertBuildJobStatusToString (m_JobStatus);
}

LibMCData_uint32 CBuildJobExecution::GetJobLayerCount()
{
	return m_nJobLayerCount;
}


LibMCData::eBuildJobExecutionStatus CBuildJobExecution::GetStatus()
{
	std::string sSelectQuery = "SELECT status FROM buildjobexecutions WHERE uuid=? AND active=1";
	auto pSelectStatement = m_pSQLHandler->prepareStatement(sSelectQuery);
	pSelectStatement->setString(1, m_sExecutionUUID);

	if (!pSelectStatement->nextRow())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONNOTFOUND, "build job execution not found: " + m_sExecutionUUID);

	return CBuildJobExecution::convertStringToBuildJobExecutionStatus (pSelectStatement->getColumnString(1));
}

std::string CBuildJobExecution::GetStatusString()
{
	return convertBuildJobExecutionStatusToString(GetStatus());
}

void CBuildJobExecution::ChangeStatus(const LibMCData::eBuildJobExecutionStatus eNewExecutionStatus, const LibMCData_uint64 nAbsoluteEndTimeStampInMicrosecondsSince1970)
{

	if (!AMCCommon::CChrono::timeStampIsWithinAMillionYears(nAbsoluteEndTimeStampInMicrosecondsSince1970))
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDTIMESTAMP, "Invalid build execution timestamp");

	auto pTransaction = m_pSQLHandler->beginTransaction();

	std::string sSelectQuery = "SELECT status, startjournaltimestamp FROM buildjobexecutions WHERE uuid=? AND active=1";
	auto pSelectStatement = pTransaction->prepareStatement(sSelectQuery);
	pSelectStatement->setString(1, m_sExecutionUUID);

	if (!pSelectStatement->nextRow())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONNOTFOUND, "build job execution not found: " + m_sExecutionUUID);

	auto eOldStatus = convertStringToBuildJobExecutionStatus(pSelectStatement->getColumnString(1));
	int64_t nStartTimeStamp = AMCCommon::CChrono::parseISO8601TimeUTC (pSelectStatement->getColumnString(2));

	if (nStartTimeStamp > (int64_t)nAbsoluteEndTimeStampInMicrosecondsSince1970)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDTIMESTAMP, "Build execution end timestamp is before start timestamp!");

	pSelectStatement = nullptr;

	if (eOldStatus != eBuildJobExecutionStatus::InProcess)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONISNOTINPROCESS, "build job execution is not in process: " + m_sExecutionUUID);

	std::string sUpdateQuery = "UPDATE buildjobexecutions SET status=?, endjournaltimestamp=? WHERE uuid=? AND active=1";
	auto pUpdateStatement = pTransaction->prepareStatement(sUpdateQuery);
	pUpdateStatement->setString(1, convertBuildJobExecutionStatusToString (eNewExecutionStatus));
	pUpdateStatement->setString(2, AMCCommon::CChrono::convertToISO8601TimeUTC (nAbsoluteEndTimeStampInMicrosecondsSince1970));
	pUpdateStatement->setString(3, m_sExecutionUUID);
	pUpdateStatement->execute();

	pTransaction->commit();
}

std::string CBuildJobExecution::GetDescription()
{
	std::string sSelectQuery = "SELECT description FROM buildjobexecutions WHERE uuid=? AND active=1";
	auto pSelectStatement = m_pSQLHandler->prepareStatement(sSelectQuery);
	pSelectStatement->setString(1, m_sExecutionUUID);

	if (!pSelectStatement->nextRow())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONNOTFOUND, "build job execution not found: " + m_sExecutionUUID);

	return pSelectStatement->getColumnString(1);
}

void CBuildJobExecution::SetDescription(const std::string & sNewDescription)
{
	std::string sUpdateQuery = "UPDATE buildjobexecutions SET description=? WHERE uuid=? AND active=1";
	auto pUpdateStatement = m_pSQLHandler->prepareStatement(sUpdateQuery);
	pUpdateStatement->setString(1, sNewDescription);
	pUpdateStatement->setString(2, m_sExecutionUUID);
	pUpdateStatement->execute();
}

std::string CBuildJobExecution::GetJournalUUID()
{
	return m_sJournalUUID;
}

std::string CBuildJobExecution::GetUserUUID()
{
	return m_sUserUUID;
}

LibMCData_uint64 CBuildJobExecution::GetStartTimeStampInMicroseconds()
{
	return m_nStartJournalTimestamp;
}

LibMCData_uint64 CBuildJobExecution::GetEndTimeStampInMicroseconds()
{
	std::string sSelectQuery = "SELECT status, endjournaltimestamp FROM buildjobexecutions WHERE uuid=? AND active=1";
	auto pSelectStatement = m_pSQLHandler->prepareStatement(sSelectQuery);
	pSelectStatement->setString(1, m_sExecutionUUID);

	if (!pSelectStatement->nextRow())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONNOTFOUND, "build job execution not found: " + m_sExecutionUUID);

	auto eStatus = convertStringToBuildJobExecutionStatus(pSelectStatement->getColumnString(1));
	if ((eStatus != eBuildJobExecutionStatus::Finished) && (eStatus != eBuildJobExecutionStatus::Failed))
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONENDNOTAVAILABLE, "build job execution end is not available: " + m_sExecutionUUID);

	int64_t nEndTimeStamp = AMCCommon::CChrono::parseISO8601TimeUTC (pSelectStatement->getColumnString(2));
	if (nEndTimeStamp < 0)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDBUILDJOBEXECUTIONEND, "invalid build job execution end: " + m_sExecutionUUID);
	if (!AMCCommon::CChrono::timeStampIsWithinAMillionYears((uint64_t)nEndTimeStamp))
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDBUILDJOBEXECUTIONEND, "invalid build job execution end: " + m_sExecutionUUID);

	if ((uint64_t) (nEndTimeStamp) < m_nStartJournalTimestamp)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONENDISBEFORESTART, "Build job execution end is before start: " + m_sExecutionUUID);

	return (uint64_t)nEndTimeStamp;

}

LibMCData_uint64 CBuildJobExecution::ComputeElapsedTimeInMicroseconds(const LibMCData_uint64 nGlobalTimerInMicroseconds, const bool bThrowExceptionInFailure) 
{

	if (!AMCCommon::CChrono::timeStampIsWithinAMillionYears(nGlobalTimerInMicroseconds)) {
		if (bThrowExceptionInFailure)
			throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

		return 0;
	}

	std::string sSelectQuery = "SELECT status, endjournaltimestamp FROM buildjobexecutions WHERE uuid=? AND active=1";
	auto pSelectStatement = m_pSQLHandler->prepareStatement(sSelectQuery);
	pSelectStatement->setString(1, m_sExecutionUUID);

	if (!pSelectStatement->nextRow()) {
		if (bThrowExceptionInFailure)
			throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONNOTFOUND, "build job execution not found: " + m_sExecutionUUID);

		return 0;
	}

	auto eStatus = convertStringToBuildJobExecutionStatus(pSelectStatement->getColumnString(1));

	switch (eStatus) {

		case eBuildJobExecutionStatus::InProcess:
		{
			if (m_sJournalUUID != m_pStorageState->getSessionUUID()) {
				if (bThrowExceptionInFailure)
					throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONISFROMPASTJOURNAL, "build job execution is from past journal: " + m_sExecutionUUID);

				return 0;
			}

			if (nGlobalTimerInMicroseconds < m_nStartJournalTimestamp) {
				if (bThrowExceptionInFailure)
					throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONSTARTISINTHEFUTURE, "build job execution start is in the future: " + m_sExecutionUUID);

				return 0;
			}
			
			return nGlobalTimerInMicroseconds - m_nStartJournalTimestamp;
		}

		case eBuildJobExecutionStatus::Finished:
		case eBuildJobExecutionStatus::Failed:
		{
			int64_t nEndTimeStamp = AMCCommon::CChrono::parseISO8601TimeUTC(pSelectStatement->getColumnString(2));
			if (nEndTimeStamp < 0) {
				if (bThrowExceptionInFailure)
					throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDBUILDJOBEXECUTIONEND, "invalid build job execution end: " + m_sExecutionUUID);

				return 0;
			}
			if (!AMCCommon::CChrono::timeStampIsWithinAMillionYears((uint64_t)nEndTimeStamp)) {
				if (bThrowExceptionInFailure)
					throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDBUILDJOBEXECUTIONEND, "invalid build job execution end: " + m_sExecutionUUID);

				return 0;
			}

			if ((uint64_t)(nEndTimeStamp) < m_nStartJournalTimestamp) {
				if (bThrowExceptionInFailure)
					throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONENDISBEFORESTART, "Build job execution end is before start: " + m_sExecutionUUID);

				return 0;
			}

			return (uint64_t)nEndTimeStamp - m_nStartJournalTimestamp;
		}

		default:
			if (bThrowExceptionInFailure)
				throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBDURATIONNOTAVAILABLE, "build job duration is not available: " + m_sExecutionUUID);

			return 0;

	}
}

std::string CBuildJobExecution::AddJobExecutionData(const std::string& sIdentifier, const std::string& sName, IStorageStream* pStream, const LibMCData::eCustomDataType eDataType, const std::string& sUserUUID, const LibMCData_uint64 nAbsoluteTimeStamp)
{
	if (pStream == nullptr)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

	auto sStreamUUID = pStream->GetUUID();
	auto sStreamSHA2 = pStream->GetSHA2();
	auto nStreamSize = pStream->GetSize();

	auto sTimeStamp = AMCCommon::CChrono::convertToISO8601TimeUTC(nAbsoluteTimeStamp);
	std::unique_ptr<CBuildJobExecutionData> buildJobData(CBuildJobExecutionData::createInDatabase(sIdentifier, sName, m_sExecutionUUID, eDataType, sTimeStamp, sStreamUUID, sUserUUID, sStreamSHA2, nStreamSize, m_pSQLHandler, m_pStorageState));

	return buildJobData->GetDataUUID();
}

CBuildJobExecutionData* CBuildJobExecution::makeJobExecutionDataEx(AMCData::CSQLStatement* pStatement)
{
	if (pStatement == nullptr)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

	std::string sDataUUID = pStatement->getColumnUUID(1);
	std::string sExecutionUUID = pStatement->getColumnString(2);
	std::string sIdentifier = pStatement->getColumnString(3);
	std::string sName = pStatement->getColumnString(4);
	LibMCData::eCustomDataType eDataType = CCustomDataStream::convertStringToCustomDataType(pStatement->getColumnString(5));
	std::string sTimeStamp = pStatement->getColumnString(6);
	std::string sStorageStreamUUID = pStatement->getColumnUUID(7);
	std::string sUserUUID = pStatement->getColumnString(8);
	std::string sSHA2 = pStatement->getColumnString(9);
	uint64_t nStreamSize = pStatement->getColumnInt64(10);

	return CBuildJobExecutionData::make(sDataUUID, sIdentifier, sName, sExecutionUUID, eDataType, sTimeStamp, sStorageStreamUUID, sUserUUID, sSHA2, nStreamSize, m_pSQLHandler, m_pStorageState);
}


IBuildJobExecutionDataIterator* CBuildJobExecution::listJobExecutionDataEx(AMCData::CSQLStatement* pStatement)
{
	if (pStatement == nullptr)
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

	std::unique_ptr<CBuildJobExecutionDataIterator> buildJobIterator(new CBuildJobExecutionDataIterator());

	while (pStatement->nextRow()) {
		buildJobIterator->AddJobExecutionData(std::shared_ptr<CBuildJobExecutionData>(makeJobExecutionDataEx(pStatement)));
	}

	return buildJobIterator.release();
}



IBuildJobExecutionDataIterator* CBuildJobExecution::ListJobExecutionDataByType(const LibMCData::eCustomDataType eDataType)
{
	std::string sQuery = "SELECT buildjobexecutiondata.uuid, buildjobexecutiondata.executionuuid, buildjobexecutiondata.identifier, buildjobexecutiondata.name, buildjobexecutiondata.datatype, buildjobexecutiondata.timestamp, buildjobexecutiondata.storagestreamuuid, buildjobexecutiondata.useruuid, storage_streams.sha2, storage_streams.size FROM buildjobexecutiondata LEFT JOIN storage_streams ON storage_streams.uuid=storagestreamuuid WHERE executionuuid=? AND active=? AND datatype=? ORDER BY buildjobexecutiondata.timestamp DESC";
	auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
	pStatement->setString(1, m_sExecutionUUID);
	pStatement->setInt(2, 1);
	pStatement->setString(3, CCustomDataStream::convertCustomDataTypeToString(eDataType));

	return listJobExecutionDataEx(pStatement.get());
}

IBuildJobExecutionDataIterator* CBuildJobExecution::ListJobExecutionData()
{
	std::string sQuery = "SELECT buildjobexecutiondata.uuid, buildjobexecutiondata.executionuuid, buildjobexecutiondata.identifier, buildjobexecutiondata.name, buildjobexecutiondata.datatype, buildjobexecutiondata.timestamp, buildjobexecutiondata.storagestreamuuid, buildjobexecutiondata.useruuid, storage_streams.sha2, storage_streams.size FROM buildjobexecutiondata LEFT JOIN storage_streams ON storage_streams.uuid=storagestreamuuid WHERE executionuuid=? AND active=? ORDER BY buildjobexecutiondata.timestamp DESC";
	auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
	pStatement->setString(1, m_sExecutionUUID);
	pStatement->setInt(2, 1);

	return listJobExecutionDataEx(pStatement.get());
}

IBuildJobExecutionData* CBuildJobExecution::RetrieveJobExecutionData(const std::string& sDataUUID)
{
	std::string sNormalizedDataUUID = AMCCommon::CUtils::normalizeUUIDString(sDataUUID);

	std::unique_ptr<CBuildJobExecutionDataIterator> buildJobIterator(new CBuildJobExecutionDataIterator());

	std::string sQuery = "SELECT buildjobexecutiondata.uuid, buildjobexecutiondata.executionuuid, buildjobexecutiondata.identifier, buildjobexecutiondata.name, buildjobexecutiondata.datatype, buildjobexecutiondata.timestamp, buildjobexecutiondata.storagestreamuuid, buildjobexecutiondata.useruuid, storage_streams.sha2, storage_streams.size FROM buildjobexecutiondata LEFT JOIN storage_streams ON storage_streams.uuid=storagestreamuuid WHERE executionuuid=? AND buildjobexecutiondata.uuid=? AND active=?";
	auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
	pStatement->setString(1, m_sExecutionUUID);
	pStatement->setString(2, sNormalizedDataUUID);
	pStatement->setInt(3, 1);

	if (!pStatement->nextRow())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONDATANOTFOUND, "build job execution data not found: " + sNormalizedDataUUID);

	return makeJobExecutionDataEx(pStatement.get());
}

IBuildJobExecutionData* CBuildJobExecution::RetrieveJobExecutionDataByIdentifier(const std::string& sIdentifier)
{
	if (sIdentifier.empty())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_EMPTYJOBEXECUTIONDATAIDENTIFIER, "empty job execution data identifier");

	std::unique_ptr<CBuildJobExecutionDataIterator> buildJobIterator(new CBuildJobExecutionDataIterator());

	std::string sQuery = "SELECT buildjobexecutiondata.uuid, buildjobexecutiondata.executionuuid, buildjobexecutiondata.identifier, buildjobexecutiondata.name, buildjobexecutiondata.datatype, buildjobexecutiondata.timestamp, buildjobexecutiondata.storagestreamuuid, buildjobexecutiondata.useruuid, storage_streams.sha2, storage_streams.size FROM buildjobexecutiondata LEFT JOIN storage_streams ON storage_streams.uuid=storagestreamuuid WHERE executionuuid=? AND buildjobexecutiondata.identifier=? AND active=?";
	auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
	pStatement->setString(1, m_sExecutionUUID);
	pStatement->setString(2, sIdentifier);
	pStatement->setInt(3, 1);

	if (!pStatement->nextRow())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONDATANOTFOUND, "build job execution data not found: " + sIdentifier);

	return makeJobExecutionDataEx(pStatement.get());
}

bool CBuildJobExecution::HasJobExecutionDataUUID(const std::string& sUUID)
{
	std::string sNormalizedDataUUID = AMCCommon::CUtils::normalizeUUIDString(sUUID);

	std::string sQuery = "SELECT buildjobexecutiondata.uuid FROM buildjobexecutiondata WHERE executionuuid=? AND buildjobexecutiondata.uuid=? AND active=?";
	auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
	pStatement->setString(1, m_sExecutionUUID);
	pStatement->setString(2, sNormalizedDataUUID);
	pStatement->setInt(3, 1);

	return (pStatement->nextRow());
}

bool CBuildJobExecution::HasJobExecutionDataIdentifier(const std::string& sIdentifier)
{
	if (sIdentifier.empty())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_EMPTYJOBDATAIDENTIFIER, "empty job execution data identifier");

	std::string sQuery = "SELECT buildjobexecutiondata.uuid FROM buildjobexecutiondata WHERE executionuuid=? AND buildjobexecutiondata.identifier=? AND active=?";
	auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
	pStatement->setString(1, m_sExecutionUUID);
	pStatement->setString(2, sIdentifier);
	pStatement->setInt(3, 1);

	return (pStatement->nextRow());
}


void CBuildJobExecution::StoreMetaDataString(const std::string& sKey, const std::string& sValue, const LibMCData_uint64 nAbsoluteTimeStamp)
{
	if (sKey.empty())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONMETADATAKEYEMPTY);

	if (!AMCCommon::CUtils::stringIsValidAlphanumericNameString(sKey))
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONMETADATAKEYINVALID, "build job execution meta data key is invalid: " + sKey);
	
	auto sTimeStamp = AMCCommon::CChrono::convertToISO8601TimeUTC(nAbsoluteTimeStamp);

	std::string sMetaDataUUID = AMCCommon::CUtils::createUUID();

	auto pTransaction = m_pSQLHandler->beginTransaction();

	std::string sDuplicateQuery = "SELECT uuid FROM buildjobexecutionmetadata WHERE executionuuid=? AND metadatakey=? AND active=?";
	auto pDuplicateStatement = pTransaction->prepareStatement(sDuplicateQuery);
	pDuplicateStatement->setString(1, m_sExecutionUUID);
	pDuplicateStatement->setString(2, sKey);
	pDuplicateStatement->setInt(3, 1);

	if (pDuplicateStatement->nextRow())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONMETADATAKEYDUPLICATE, "build job execution meta data key is not unisque: " + sKey);
	pDuplicateStatement = nullptr;

	std::string sInsertQuery = "INSERT INTO buildjobexecutionmetadata (uuid, executionuuid, metadatakey, metadatavalue, active, timestamp) VALUES (?, ?, ?, ?, ?, ?)";
	auto pInsertStatement = pTransaction->prepareStatement(sInsertQuery);
	pInsertStatement->setString(1, sMetaDataUUID);
	pInsertStatement->setString(2, m_sExecutionUUID);
	pInsertStatement->setString(3, sKey);
	pInsertStatement->setString(4, sValue);
	pInsertStatement->setInt(5, 1);
	pInsertStatement->setString(6, sTimeStamp);
	pInsertStatement->execute();

	pTransaction->commit();


}

bool CBuildJobExecution::HasMetaDataString(const std::string& sKey)
{
	if (sKey.empty())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONMETADATAKEYEMPTY);

	if (!AMCCommon::CUtils::stringIsValidAlphanumericNameString(sKey))
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONMETADATAKEYINVALID, "build job execution meta data key is invalid: " + sKey);

	std::string sSelectQuery = "SELECT uuid FROM buildjobexecutionmetadata WHERE executionuuid=? AND metadatakey=? AND active=?";
	auto pSelectStatement = m_pSQLHandler->prepareStatement(sSelectQuery);
	pSelectStatement->setString(1, m_sExecutionUUID);
	pSelectStatement->setString(2, sKey);
	pSelectStatement->setInt(3, 1);

	return (pSelectStatement->nextRow());
}

std::string CBuildJobExecution::GetMetaDataString(const std::string& sKey)
{
	if (sKey.empty())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONMETADATAKEYEMPTY);

	if (!AMCCommon::CUtils::stringIsValidAlphanumericNameString(sKey))
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONMETADATAKEYINVALID, "build job execution meta data key is invalid: " + sKey);

	std::string sSelectQuery = "SELECT metadatavalue FROM buildjobexecutionmetadata WHERE executionuuid=? AND metadatakey=? AND active=?";
	auto pSelectStatement = m_pSQLHandler->prepareStatement(sSelectQuery);
	pSelectStatement->setString(1, m_sExecutionUUID);
	pSelectStatement->setString(2, sKey);
	pSelectStatement->setInt(3, 1);

	if (!pSelectStatement->nextRow())
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBEXECUTIONMETADATAKEYNOTFOUND, "build job execution meta data key not found: " + sKey);

	return pSelectStatement->getColumnString(1);
}


std::string CBuildJobExecution::convertBuildJobExecutionStatusToString(const LibMCData::eBuildJobExecutionStatus eStatus)
{
	switch (eStatus) {
	case LibMCData::eBuildJobExecutionStatus::InProcess: return "inprocess";
	case LibMCData::eBuildJobExecutionStatus::Finished: return "finished";
	case LibMCData::eBuildJobExecutionStatus::Failed: return "failed";
	case LibMCData::eBuildJobExecutionStatus::Unknown: return "unknown";
	default:
		throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDBUILDJOBEXECUTIONSTATUS);
	}
}

LibMCData::eBuildJobExecutionStatus CBuildJobExecution::convertStringToBuildJobExecutionStatus(const std::string& sValue)
{
	if (sValue == "inprocess")
		return LibMCData::eBuildJobExecutionStatus::InProcess;
	if (sValue == "finished")
		return LibMCData::eBuildJobExecutionStatus::Finished;
	if (sValue == "failed")
		return LibMCData::eBuildJobExecutionStatus::Failed;
	if (sValue == "unknown")
		return LibMCData::eBuildJobExecutionStatus::Unknown;

	throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDBUILDJOBEXECUTIONSTATUS);
}
