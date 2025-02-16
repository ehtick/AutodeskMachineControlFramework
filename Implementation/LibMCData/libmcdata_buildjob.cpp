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


Abstract: This is a stub class definition of CBuildJob

*/

#include "libmcdata_buildjob.hpp"
#include "libmcdata_interfaceexception.hpp"
#include "libmcdata_storagestream.hpp"
#include "libmcdata_buildjobexecution.hpp"
#include "libmcdata_buildjobexecutioniterator.hpp"

#include "libmcdata_buildjobdata.hpp"
#include "libmcdata_buildjobdataiterator.hpp"

// Include custom headers here.
#include "common_utils.hpp"
#include "common_chrono.hpp"

using namespace LibMCData::Impl;

/*************************************************************************************************************************
 Class definition of CBuildJob 
**************************************************************************************************************************/
CBuildJob::CBuildJob(const std::string& sUUID, const std::string& sName, LibMCData::eBuildJobStatus eJobStatus, const std::string& sTimeStamp, const std::string& sStorageStreamUUID, const std::string& sUserUUID, const std::string& sUserName, uint32_t nLayerCount, uint32_t nExecutionCount, const std::string& sThumbnailStreamUUID, AMCData::PSQLHandler pSQLHandler, AMCData::PStorageState pStorageState)
  : m_sUUID (AMCCommon::CUtils::normalizeUUIDString(sUUID)),
    m_sName (sName), 
    m_eJobStatus (eJobStatus), 
    m_sTimeStamp (sTimeStamp), 
    m_sStorageStreamUUID (AMCCommon::CUtils::normalizeUUIDString(sStorageStreamUUID)),
    m_sUserUUID (AMCCommon::CUtils::normalizeUUIDString (sUserUUID)),
    m_pSQLHandler(pSQLHandler),
    m_sUserName(sUserName),
    m_nLayerCount(nLayerCount),
    m_nExecutionCount (nExecutionCount),
    m_sThumbnailStreamUUID(AMCCommon::CUtils::normalizeUUIDString(sThumbnailStreamUUID)),
    m_pStorageState (pStorageState)
{
    if (pSQLHandler.get() == nullptr)
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);
    if (pStorageState.get() == nullptr)
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);
    if (sName.empty())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDJOBNAME);
    if (sTimeStamp.empty())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDJOBTIMESTAMP);
}

CBuildJob* CBuildJob::make(const std::string& sUUID, const std::string& sName, LibMCData::eBuildJobStatus eJobStatus, const std::string& sTimeStamp, const std::string& sStorageStreamUUID, const std::string& sUserUUID, const std::string& sUserName, uint32_t nLayerCount, uint32_t nExecutionCount, const std::string& sThumbnailStreamUUID, AMCData::PSQLHandler pSQLHandler, AMCData::PStorageState pStorageState)
{
    return new CBuildJob(sUUID, sName, eJobStatus, sTimeStamp, sStorageStreamUUID, sUserUUID, sUserName, nLayerCount, nExecutionCount, sThumbnailStreamUUID, pSQLHandler, pStorageState);
}

CBuildJob* CBuildJob::makeFromDatabase(const std::string& sJobUUID, AMCData::PSQLHandler pSQLHandler, AMCData::PStorageState pStorageState)
{
    if (pSQLHandler.get() == nullptr)
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);
    if (pStorageState.get() == nullptr)
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

    auto sParsedJobUUID = AMCCommon::CUtils::normalizeUUIDString(sJobUUID);

    std::string sQuery = "SELECT buildjobs.uuid, buildjobs.name, buildjobs.status, buildjobs.timestamp, buildjobs.storagestreamuuid, buildjobs.layercount, buildjobs.useruuid, users.login, (SELECT count(buildjobexecutions.uuid) FROM buildjobexecutions WHERE buildjobexecutions.jobuuid=buildjobs.uuid), buildjobs.thumbnailuuid FROM buildjobs LEFT JOIN users ON users.uuid=buildjobs.useruuid WHERE buildjobs.uuid=?";
    auto pStatement = pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, sParsedJobUUID);
    if (!pStatement->nextRow())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_JOBUUIDNOTFOUND);

    auto sUUID = pStatement->getColumnString(1);
    auto sName = pStatement->getColumnString(2);
    auto eJobStatus = convertStringToBuildJobStatus(pStatement->getColumnString(3));
    auto sTimeStamp = pStatement->getColumnString(4);
    auto sStorageStreamUUID = pStatement->getColumnString(5);
    auto nLayerCount = pStatement->getColumnInt(6);
    auto sUserUUID = pStatement->getColumnString(7);
    std::string sUserName;
    if (!pStatement->columnIsNull(8))
        sUserName = pStatement->getColumnString(8);
    int32_t nExecutionCount = pStatement->getColumnInt(9);
    if (nExecutionCount < 0)
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_COULDNOTDETERMINEEXECUTIONCOUNT);

    std::string sThumbnailStreamUUID = AMCCommon::CUtils::normalizeUUIDString(pStatement->getColumnString(10));

    pStatement = nullptr;

    return make (sUUID, sName, eJobStatus, sTimeStamp, sStorageStreamUUID, sUserUUID, sUserName, nLayerCount, (uint32_t) nExecutionCount, sThumbnailStreamUUID, pSQLHandler, pStorageState);
}

CBuildJob* CBuildJob::makeFrom(CBuildJob* pBuildJob)
{
    if (pBuildJob == nullptr)
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

    return make(pBuildJob->m_sUUID, pBuildJob->m_sName, pBuildJob->m_eJobStatus, pBuildJob->m_sTimeStamp, pBuildJob->m_sStorageStreamUUID, pBuildJob->m_sUserUUID, pBuildJob->m_sUserName,
            pBuildJob->m_nLayerCount, pBuildJob->m_nExecutionCount, pBuildJob->m_sThumbnailStreamUUID, pBuildJob->m_pSQLHandler, pBuildJob->m_pStorageState);
}

PBuildJob CBuildJob::makeShared(const std::string& sUUID, const std::string& sName, LibMCData::eBuildJobStatus eJobStatus, const std::string& sTimeStamp, const std::string& sStorageStreamUUID, const std::string& sUserUUID, const std::string& sUserName, uint32_t nLayerCount, uint32_t nExecutionCount, const std::string& sThumbnailStreamUUID, AMCData::PSQLHandler pSQLHandler, AMCData::PStorageState pStorageState)
{
    return std::shared_ptr<CBuildJob>(make(sUUID, sName, eJobStatus, sTimeStamp, sStorageStreamUUID, sUserUUID, sUserName, nLayerCount, nExecutionCount, sThumbnailStreamUUID, pSQLHandler, pStorageState));
}

PBuildJob CBuildJob::makeSharedFromDatabase(const std::string& sJobUUID, AMCData::PSQLHandler pSQLHandler, AMCData::PStorageState pStorageState)
{
    return std::shared_ptr<CBuildJob>(makeFromDatabase (sJobUUID, pSQLHandler, pStorageState));
}

PBuildJob CBuildJob::makeSharedFrom(CBuildJob* pBuildJob)
{
    if (pBuildJob == nullptr)
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

    return std::shared_ptr<CBuildJob>(makeFrom (pBuildJob));
}


std::string CBuildJob::GetUUID()
{
    return m_sUUID;
}

std::string CBuildJob::GetName()
{
    return m_sName;
}

LibMCData_uint32 CBuildJob::GetLayerCount()
{
    return m_nLayerCount;
}

LibMCData_uint32 CBuildJob::GetExecutionCount()
{
    return m_nExecutionCount;
}



LibMCData::eBuildJobStatus CBuildJob::GetStatus()
{
    return m_eJobStatus;
}

std::string CBuildJob::GetTimeStamp()
{
	return m_sTimeStamp;
}

std::string CBuildJob::GetCreatorUUID()
{
    return m_sUserUUID;
}

std::string CBuildJob::GetCreatorName()
{
    return m_sUserName;
}

bool CBuildJob::HasThumbnailStream()
{
    return (m_sThumbnailStreamUUID != AMCCommon::CUtils::createEmptyUUID());
}

std::string CBuildJob::GetThumbnailStreamUUID()
{
    return m_sThumbnailStreamUUID;
}

void CBuildJob::SetThumbnailStreamUUID(const std::string& sStreamUUID)
{
    std::string sNormalizedThumbnailUUID;
    if (!sStreamUUID.empty()) {
        sNormalizedThumbnailUUID = AMCCommon::CUtils::normalizeUUIDString(sStreamUUID);
    }
    else {
        sNormalizedThumbnailUUID = AMCCommon::CUtils::createEmptyUUID();
    }

    auto pTransaction = m_pSQLHandler->beginTransaction();

    if (sNormalizedThumbnailUUID != AMCCommon::CUtils::createEmptyUUID()) {
        std::string sStreamQuery = "SELECT uuid FROM storage_streams WHERE uuid=?";
        auto pStreamQueryStatement = pTransaction->prepareStatement(sStreamQuery);
        pStreamQueryStatement->setString(1, sNormalizedThumbnailUUID);

        if (!pStreamQueryStatement->nextRow())
            throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_STORAGESTREAMNOTFOUND, "thumbnail storage stream not found: " + sNormalizedThumbnailUUID);
        pStreamQueryStatement = nullptr;
    }

    auto updateUUID = AMCCommon::CUtils::createUUID();
    std::string sQuery = "UPDATE buildjobs SET thumbnailuuid=?, updateuuid=? WHERE uuid=?";
    auto pStatement = pTransaction->prepareStatement(sQuery);
    pStatement->setString(1, sNormalizedThumbnailUUID);
    pStatement->setString(2, updateUUID);
    pStatement->setString(3, m_sUUID);
    pStatement->execute();
    pStatement = nullptr;

    pTransaction->commit();
    pTransaction = nullptr;

    ensureUpdate(updateUUID, LIBMCDATA_ERROR_COULDNOTUPDATEBUILDSTATUS);
}


IStorageStream * CBuildJob::GetStorageStream()
{
    return CStorageStream::makeFromDatabase(m_sStorageStreamUUID, m_pSQLHandler, m_pStorageState);
}

std::string CBuildJob::GetStorageStreamUUID()
{
    return m_sStorageStreamUUID;
}

void CBuildJob::ensureUpdate(const std::string sUpdateUUID, uint32_t nErrorCode)
{
    std::string sSelectQuery = "SELECT uuid FROM buildjobs WHERE updateuuid=?";
    auto pSelectStatement = m_pSQLHandler->prepareStatement(sSelectQuery);
    pSelectStatement->setString(1, sUpdateUUID);
    if (!pSelectStatement->nextRow())
        throw ELibMCDataInterfaceException(nErrorCode);

}

void CBuildJob::StartValidating()
{

    auto updateUUID = AMCCommon::CUtils::createUUID();
    std::string sQuery = "UPDATE buildjobs SET status=?, updateuuid=? WHERE status=? AND uuid=?";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Validating));
    pStatement->setString(2, updateUUID);
    pStatement->setString(3, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Created));
    pStatement->setString(4, m_sUUID);
    pStatement->execute();
    pStatement = nullptr;

    ensureUpdate(updateUUID, LIBMCDATA_ERROR_COULDNOTUPDATEBUILDSTATUS);
}

void CBuildJob::FinishValidating(const LibMCData_uint32 nLayerCount)
{

    auto updateUUID = AMCCommon::CUtils::createUUID();
    std::string sQuery = "UPDATE buildjobs SET status=?, layercount=?, updateuuid=? WHERE status=? AND uuid=?";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Validated));
    pStatement->setInt64(2, nLayerCount);
    pStatement->setString(3, updateUUID);
    pStatement->setString(4, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Validating));
    pStatement->setString(5, m_sUUID);
    pStatement->execute();
    pStatement = nullptr;

    ensureUpdate(updateUUID, LIBMCDATA_ERROR_COULDNOTUPDATEBUILDSTATUS);
}


void CBuildJob::ArchiveJob()
{
    auto updateUUID = AMCCommon::CUtils::createUUID();
    std::string sQuery = "UPDATE buildjobs SET status=?, updateuuid=? WHERE status=? AND uuid=?";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Archived));
    pStatement->setString(2, updateUUID);
    pStatement->setString(3, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Validated));
    pStatement->setString(4, m_sUUID);
    pStatement->execute();
    pStatement = nullptr;

    ensureUpdate(updateUUID, LIBMCDATA_ERROR_COULDNOTUPDATEBUILDSTATUS);
}


void CBuildJob::UnArchiveJob()
{
    auto updateUUID = AMCCommon::CUtils::createUUID();
    std::string sQuery = "UPDATE buildjobs SET status=?, updateuuid=? WHERE status=? AND uuid=?";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Validated));
    pStatement->setString(2, updateUUID);
    pStatement->setString(3, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Archived));
    pStatement->setString(4, m_sUUID);
    pStatement->execute();

    ensureUpdate(updateUUID, LIBMCDATA_ERROR_COULDNOTUPDATEBUILDSTATUS);

}

void CBuildJob::DeleteJob()
{
    // TODO: Physically delete job from disk!

    auto updateUUID = AMCCommon::CUtils::createUUID();
    std::string sQuery = "UPDATE buildjobs SET status=?, updateuuid=? WHERE status=? AND uuid=?";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Deleted));
    pStatement->setString(2, updateUUID);
    pStatement->setString(3, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Archived));
    pStatement->setString(4, m_sUUID);
    pStatement->execute();
    pStatement = nullptr;

    ensureUpdate(updateUUID, LIBMCDATA_ERROR_COULDNOTUPDATEBUILDSTATUS);

}

bool CBuildJob::JobCanBeArchived()

{
    // TODO: Track active jobs and prevent them from archiving.
    std::string sQuery = "SELECT uuid FROM buildjobs WHERE status=? AND uuid=?";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, convertBuildJobStatusToString(LibMCData::eBuildJobStatus::Validated));
    pStatement->setString(2, m_sUUID);
    return pStatement->nextRow();

}

std::string CBuildJob::AddJobData(const std::string& sIdentifier, const std::string& sName, IStorageStream* pStream, const LibMCData::eCustomDataType eDataType, const std::string& sUserUUID, const LibMCData_uint64 nAbsoluteTimeStamp)
{
    if (pStream == nullptr)
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

    auto sStreamUUID = pStream->GetUUID();
    auto sStreamSHA2 = pStream->GetSHA2();
    auto nStreamSize = pStream->GetSize();

    auto sTimeStamp = AMCCommon::CChrono::convertToISO8601TimeUTC (nAbsoluteTimeStamp);
    std::unique_ptr<CBuildJobData> buildJobData (CBuildJobData::createInDatabase (sIdentifier, sName, m_sUUID, eDataType, sTimeStamp, sStreamUUID, sUserUUID, sStreamSHA2, nStreamSize, m_pSQLHandler, m_pStorageState));

    return buildJobData->GetDataUUID ();
}


CBuildJobData * CBuildJob::makeJobDataEx(AMCData::CSQLStatement* pStatement)
{
    if (pStatement == nullptr)
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

    std::string sDataUUID = pStatement->getColumnUUID(1);
    std::string sJobUUID = pStatement->getColumnString(2);
    std::string sIdentifier = pStatement->getColumnString(3);
    std::string sName = pStatement->getColumnString(4);
    LibMCData::eCustomDataType eDataType = CBuildJobData::convertStringToCustomDataType(pStatement->getColumnString(5));
    std::string sTimeStamp = pStatement->getColumnString(6);
    std::string sStorageStreamUUID = pStatement->getColumnUUID(7);
    std::string sUserUUID = pStatement->getColumnString(8);
    std::string sSHA2 = pStatement->getColumnString(9);
    uint64_t nStreamSize = pStatement->getColumnInt64(10);

    return CBuildJobData::make(sDataUUID, sIdentifier, sName, sJobUUID, eDataType, sTimeStamp, sStorageStreamUUID, sUserUUID, sSHA2, nStreamSize, m_pSQLHandler, m_pStorageState);
}


IBuildJobDataIterator* CBuildJob::listJobDataEx(AMCData::CSQLStatement* pStatement)
{
    if (pStatement == nullptr)
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDPARAM);

    std::unique_ptr<CBuildJobDataIterator> buildJobIterator(new CBuildJobDataIterator());

    while (pStatement->nextRow()) {
        buildJobIterator->AddJobData(std::shared_ptr<CBuildJobData> (makeJobDataEx (pStatement)));
    }

    return buildJobIterator.release();
}


IBuildJobDataIterator* CBuildJob::ListJobDataByType(const LibMCData::eCustomDataType eDataType)
{

    std::string sQuery = "SELECT buildjobdata.uuid, buildjobdata.jobuuid, buildjobdata.identifier, buildjobdata.name, buildjobdata.datatype, buildjobdata.timestamp, buildjobdata.storagestreamuuid, buildjobdata.useruuid, storage_streams.sha2, storage_streams.size FROM buildjobdata LEFT JOIN storage_streams ON storage_streams.uuid=storagestreamuuid WHERE jobuuid=? AND active=? AND datatype=? ORDER BY buildjobdata.timestamp DESC";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString (1, m_sUUID);
    pStatement->setInt(2, 1);
    pStatement->setString(3, CBuildJobData::convertCustomDataTypeToString(eDataType));

    return listJobDataEx (pStatement.get());
}

IBuildJobDataIterator* CBuildJob::ListJobData()
{
    std::unique_ptr<CBuildJobDataIterator> buildJobIterator (new CBuildJobDataIterator ());

    std::string sQuery = "SELECT buildjobdata.uuid, buildjobdata.jobuuid, buildjobdata.identifier, buildjobdata.name, buildjobdata.datatype, buildjobdata.timestamp, buildjobdata.storagestreamuuid, buildjobdata.useruuid, storage_streams.sha2, storage_streams.size FROM buildjobdata LEFT JOIN storage_streams ON storage_streams.uuid=storagestreamuuid WHERE jobuuid=? AND active=? ORDER BY buildjobdata.timestamp DESC";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, m_sUUID);
    pStatement->setInt(2, 1);

    return listJobDataEx(pStatement.get());
}


IBuildJobData* CBuildJob::RetrieveJobData(const std::string& sDataUUID)
{
    std::string sNormalizedDataUUID = AMCCommon::CUtils::normalizeUUIDString(sDataUUID);

    std::unique_ptr<CBuildJobDataIterator> buildJobIterator(new CBuildJobDataIterator());

    std::string sQuery = "SELECT buildjobdata.uuid, buildjobdata.jobuuid, buildjobdata.identifier, buildjobdata.name, buildjobdata.datatype, buildjobdata.timestamp, buildjobdata.storagestreamuuid, buildjobdata.useruuid, storage_streams.sha2, storage_streams.size FROM buildjobdata LEFT JOIN storage_streams ON storage_streams.uuid=storagestreamuuid WHERE jobuuid=? AND buildjobdata.uuid=? AND active=?";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, m_sUUID);
    pStatement->setString(2, sNormalizedDataUUID);
    pStatement->setInt(3, 1);

    if (!pStatement->nextRow())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBDATANOTFOUND, "build job data not found: " + sNormalizedDataUUID);
    
    return makeJobDataEx(pStatement.get());
}

IBuildJobData* CBuildJob::RetrieveJobDataByIdentifier(const std::string& sIdentifier)
{
    if (sIdentifier.empty ())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_EMPTYJOBDATAIDENTIFIER, "empty job data identifier");

    std::unique_ptr<CBuildJobDataIterator> buildJobIterator(new CBuildJobDataIterator());

    std::string sQuery = "SELECT buildjobdata.uuid, buildjobdata.jobuuid, buildjobdata.identifier, buildjobdata.name, buildjobdata.datatype, buildjobdata.timestamp, buildjobdata.storagestreamuuid, buildjobdata.useruuid, storage_streams.sha2, storage_streams.size FROM buildjobdata LEFT JOIN storage_streams ON storage_streams.uuid=storagestreamuuid WHERE jobuuid=? AND buildjobdata.identifier=? AND active=?";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, m_sUUID);
    pStatement->setString(2, sIdentifier);
    pStatement->setInt(3, 1);

    if (!pStatement->nextRow())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBDATANOTFOUND, "build job data not found: " + sIdentifier);

    return makeJobDataEx(pStatement.get());

}

bool CBuildJob::HasJobDataUUID(const std::string& sUUID)
{
    std::string sNormalizedDataUUID = AMCCommon::CUtils::normalizeUUIDString(sUUID);

    std::string sQuery = "SELECT buildjobdata.uuid FROM buildjobdata WHERE jobuuid=? AND buildjobdata.uuid=? AND active=?";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, m_sUUID);
    pStatement->setString(2, sNormalizedDataUUID);
    pStatement->setInt(3, 1);

    return (pStatement->nextRow());
}

bool CBuildJob::HasJobDataIdentifier(const std::string& sIdentifier)
{
    if (sIdentifier.empty())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_EMPTYJOBDATAIDENTIFIER, "empty job data identifier");

    std::string sQuery = "SELECT buildjobdata.uuid FROM buildjobdata WHERE jobuuid=? AND buildjobdata.identifier=? AND active=?";
    auto pStatement = m_pSQLHandler->prepareStatement(sQuery);
    pStatement->setString(1, m_sUUID);
    pStatement->setString(2, sIdentifier);
    pStatement->setInt(3, 1);

    return (pStatement->nextRow());
}


void CBuildJob::StoreMetaDataString(const std::string& sKey, const std::string& sValue, const LibMCData_uint64 nAbsoluteTimeStamp)
{
    if (sKey.empty())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBMETADATAKEYEMPTY);

    if (!AMCCommon::CUtils::stringIsValidAlphanumericNameString (sKey))
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBMETADATAKEYINVALID, "build job meta data key is invalid: " + sKey);

    
    auto sTimeStamp = AMCCommon::CChrono::convertToISO8601TimeUTC(nAbsoluteTimeStamp);

    std::string sMetaDataUUID = AMCCommon::CUtils::createUUID();

    auto pTransaction = m_pSQLHandler->beginTransaction();

    std::string sDuplicateQuery = "SELECT uuid FROM buildjobmetadata WHERE jobuuid=? AND metadatakey=? AND active=?";
    auto pDuplicateStatement = pTransaction->prepareStatement(sDuplicateQuery);
    pDuplicateStatement->setString(1, m_sUUID);
    pDuplicateStatement->setString(2, sKey);
    pDuplicateStatement->setInt(3, 1);

    if (pDuplicateStatement->nextRow ())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBMETADATAKEYDUPLICATE, "build job meta data key is not unisque: " + sKey);
    pDuplicateStatement = nullptr;

    std::string sInsertQuery = "INSERT INTO buildjobmetadata (uuid, jobuuid, metadatakey, metadatavalue, active, timestamp) VALUES (?, ?, ?, ?, ?, ?)";
    auto pInsertStatement = pTransaction->prepareStatement(sInsertQuery);
    pInsertStatement->setString(1, sMetaDataUUID);
    pInsertStatement->setString(2, m_sUUID);
    pInsertStatement->setString(3, sKey);
    pInsertStatement->setString(4, sValue);
    pInsertStatement->setInt(5, 1);
    pInsertStatement->setString(6, sTimeStamp);
    pInsertStatement->execute();

    pTransaction->commit();


}

bool CBuildJob::HasMetaDataString(const std::string& sKey)
{
    if (sKey.empty())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBMETADATAKEYEMPTY);

    if (!AMCCommon::CUtils::stringIsValidAlphanumericNameString(sKey))
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBMETADATAKEYINVALID, "build job meta data key is invalid: " + sKey);

    std::string sSelectQuery = "SELECT uuid FROM buildjobmetadata WHERE jobuuid=? AND metadatakey=? AND active=?";
    auto pSelectStatement = m_pSQLHandler->prepareStatement(sSelectQuery);
    pSelectStatement->setString(1, m_sUUID);
    pSelectStatement->setString(2, sKey);
    pSelectStatement->setInt(3, 1);

    return (pSelectStatement->nextRow());
}

std::string CBuildJob::GetMetaDataString(const std::string& sKey)
{
    if (sKey.empty())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBMETADATAKEYEMPTY);

    if (!AMCCommon::CUtils::stringIsValidAlphanumericNameString(sKey))
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBMETADATAKEYINVALID, "build job meta data key is invalid: " + sKey);

    std::string sSelectQuery = "SELECT metadatavalue FROM buildjobmetadata WHERE jobuuid=? AND metadatakey=? AND active=?";
    auto pSelectStatement = m_pSQLHandler->prepareStatement(sSelectQuery);
    pSelectStatement->setString(1, m_sUUID);
    pSelectStatement->setString(2, sKey);
    pSelectStatement->setInt(3, 1);

    if (!pSelectStatement->nextRow())
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_BUILDJOBMETADATAKEYNOTFOUND, "build job meta data key not found: " + sKey);

    return pSelectStatement->getColumnString(1);
}

IBuildJobExecution* CBuildJob::CreateBuildJobExecution(const std::string& sDescription, const std::string& sUserUUID, const LibMCData_uint64 nAbsoluteStartTimeStampInMicrosecondsSince1970)
{
    if (!AMCCommon::CChrono::timeStampIsWithinAMillionYears (nAbsoluteStartTimeStampInMicrosecondsSince1970))
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDTIMESTAMP, "Invalid build execution timestamp");

    std::string sExecutionUUID = AMCCommon::CUtils::createUUID();
    std::string sJournalUUID = m_pStorageState->getSessionUUID();

    auto sAbsoluteCreationTimeStamp = AMCCommon::CChrono::convertToISO8601TimeUTC (nAbsoluteStartTimeStampInMicrosecondsSince1970);

    std::string sNormalizedUserUUID;
    if (!sUserUUID.empty())
        sNormalizedUserUUID = AMCCommon::CUtils::normalizeUUIDString(sUserUUID);
    else
        sNormalizedUserUUID = AMCCommon::CUtils::createEmptyUUID();

    std::string sInsertQuery = "INSERT INTO buildjobexecutions (uuid, jobuuid, journaluuid, startjournaltimestamp, endjournaltimestamp, useruuid, status, description, active, timestamp) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto pInsertStatement = m_pSQLHandler->prepareStatement(sInsertQuery);
    pInsertStatement->setString(1, sExecutionUUID);
    pInsertStatement->setString(2, m_sUUID);
    pInsertStatement->setString(3, sJournalUUID);
    pInsertStatement->setString(4, AMCCommon::CChrono::convertToISO8601TimeUTC (nAbsoluteStartTimeStampInMicrosecondsSince1970));
    pInsertStatement->setInt64(5, 0);
    pInsertStatement->setString(6, sUserUUID);
    pInsertStatement->setString(7, CBuildJobExecution::convertBuildJobExecutionStatusToString (LibMCData::eBuildJobExecutionStatus::InProcess));
    pInsertStatement->setString(8, sDescription);
    pInsertStatement->setInt(9, 1);
    pInsertStatement->setString(10, sAbsoluteCreationTimeStamp);
    pInsertStatement->execute();

    return new CBuildJobExecution(m_pSQLHandler, sExecutionUUID, m_sUUID, sJournalUUID, sUserUUID, nAbsoluteStartTimeStampInMicrosecondsSince1970, m_sName, m_eJobStatus, m_nLayerCount, m_pStorageState);

}

IBuildJobExecution* CBuildJob::RetrieveBuildJobExecution(const std::string& sExecutionUUID)
{
    std::string sNormalizedUUID = AMCCommon::CUtils::normalizeUUIDString(sExecutionUUID);

    return CBuildJobExecution::makeFromDatabase(m_pSQLHandler, sNormalizedUUID, m_pStorageState);
}

IBuildJobExecutionIterator* CBuildJob::RetrieveBuildJobExecutions(const std::string& sJournalUUIDFilter)
{
    std::string sJournalQuery;
    if (!sJournalUUIDFilter.empty())
        sJournalQuery = " AND buildjobexecutions.journaluuid=?";

    std::string sSelectQuery = "SELECT buildjobexecutions.uuid, buildjobexecutions.jobuuid, buildjobexecutions.journaluuid, buildjobexecutions.useruuid, buildjobexecutions.startjournaltimestamp, buildjobs.name, buildjobs.status, buildjobs.layercount FROM buildjobexecutions LEFT JOIN buildjobs ON buildjobs.uuid=buildjobexecutions.jobuuid WHERE buildjobexecutions.jobuuid=? AND buildjobexecutions.active=?" + sJournalQuery + " ORDER BY buildjobexecutions.timestamp DESC";
    auto pStatement = m_pSQLHandler->prepareStatement(sSelectQuery);    
    pStatement->setString(1, m_sUUID);
    pStatement->setInt(2, 1);
    if (!sJournalUUIDFilter.empty())
        pStatement->setString(3, AMCCommon::CUtils::normalizeUUIDString (sJournalUUIDFilter));

    std::unique_ptr<CBuildJobExecutionIterator> buildJobExecutionIterator(new CBuildJobExecutionIterator());

    while (pStatement->nextRow()) {
        // ATTENTION: All callers of makeFromStatement MUST BE in Sync in terms of column order!!
        // Column 1: Execution UUID
        // Column 2: Job UUID
        // Column 3: Journal UUID
        // Column 4: User UUID
        // Column 5: Start TimeStamp
        // Column 6: Job Name
        // Column 7: Job Status
        // Column 8: Job Layer Count

        buildJobExecutionIterator->AddJobExecution(CBuildJobExecution::makeSharedFromStatement(m_pSQLHandler, pStatement, m_pStorageState));
    }

    return buildJobExecutionIterator.release();
}

IBuildJobExecutionIterator* CBuildJob::RetrieveBuildJobExecutionsByStatus(const LibMCData::eBuildJobExecutionStatus eStatusFilter, const std::string& sJournalUUIDFilter)
{
    std::string sJournalQuery;
    if (!sJournalUUIDFilter.empty())
        sJournalQuery = " AND buildjobexecutions.journaluuid=?";

    std::string sSelectQuery = "SELECT buildjobexecutions.uuid, buildjobexecutions.jobuuid, buildjobexecutions.journaluuid, buildjobexecutions.useruuid, buildjobexecutions.startjournaltimestamp, buildjobs.name, buildjobs.status, buildjobs.layercount FROM buildjobexecutions LEFT JOIN buildjobs ON buildjobs.uuid=buildjobexecutions.jobuuid WHERE buildjobexecutions.jobuuid=? AND buildjobexecutions.active=? AND buildjobexecutions.status=?" + sJournalQuery + " ORDER BY buildjobexecutions.timestamp DESC";

    auto pStatement = m_pSQLHandler->prepareStatement(sSelectQuery);
    pStatement->setString(1, m_sUUID);
    pStatement->setInt(2, 1);
    pStatement->setString(3, CBuildJobExecution::convertBuildJobExecutionStatusToString(eStatusFilter));
    if (!sJournalUUIDFilter.empty())
        pStatement->setString(4, AMCCommon::CUtils::normalizeUUIDString(sJournalUUIDFilter));

    std::unique_ptr<CBuildJobExecutionIterator> buildJobExecutionIterator(new CBuildJobExecutionIterator());

    while (pStatement->nextRow()) {
        // ATTENTION: All callers of makeFromStatement MUST BE in Sync in terms of column order!!
        // Column 1: Execution UUID
        // Column 2: Job UUID
        // Column 3: Journal UUID
        // Column 4: User UUID
        // Column 5: Start TimeStamp
        // Column 6: Job Name
        // Column 7: Job Status
        // Column 8: Job Layer Count

        buildJobExecutionIterator->AddJobExecution(CBuildJobExecution::makeSharedFromStatement(m_pSQLHandler, pStatement, m_pStorageState));
    }

    return buildJobExecutionIterator.release();
}


std::string CBuildJob::convertBuildJobStatusToString(const LibMCData::eBuildJobStatus eStatus)
{
    switch (eStatus) {
    case LibMCData::eBuildJobStatus::Created: return "created";
    case LibMCData::eBuildJobStatus::Validating: return "validating";
    case LibMCData::eBuildJobStatus::Validated: return "validated";
    case LibMCData::eBuildJobStatus::Archived: return "archived";
    case LibMCData::eBuildJobStatus::Deleted: return "deleted";
    default:
        throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDJOBSTATUS);
    }
}

LibMCData::eBuildJobStatus CBuildJob::convertStringToBuildJobStatus(const std::string& sValue)
{
    if (sValue == "created")
        return LibMCData::eBuildJobStatus::Created;
    if (sValue == "validating")
        return LibMCData::eBuildJobStatus::Validating;
    if (sValue == "validated")
        return LibMCData::eBuildJobStatus::Validated;
    if (sValue == "archived")
        return LibMCData::eBuildJobStatus::Archived;
    if (sValue == "deleted")
        return LibMCData::eBuildJobStatus::Deleted;

    throw ELibMCDataInterfaceException(LIBMCDATA_ERROR_INVALIDJOBSTATUS);
}


