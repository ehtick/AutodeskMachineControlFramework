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

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AUTODESK INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "amc_discretefielddata2d.hpp"

#include "libmc_exceptiontypes.hpp"
#include "libmcenv_interfaceexception.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

using namespace AMC;

#define DISCRETEFIELD_MAXPIXELCOUNT (1024ULL * 1024ULL * 32ULL)
#define DISCRETEFIELD_MINVALUEDISTANCE 1E-6
#define DISCRETEFIELD_MAXPOINTVALUESCOUNT (1024ULL * 1024ULL * 1024ULL)

#define DISCRETEFIELD_MAXORIGINCOORDINATE 1.0e9

#define DISCRETEFIELD2D_STREAMFILESIGN 0x17AE971A
#define DISCRETEFIELD2D_STREAMFILEMAJORVERSION 1
#define DISCRETEFIELD2D_STREAMFILEMINORVERSION 0
#define DISCRETEFIELD2D_STREAMFILEPATCHVERSION 0

#define DISCRETEFIELD2D_STREAMSTORAGETYPE_RAWDATA 1

#pragma pack(push)
#pragma pack(1)
typedef struct _sDiscreteField2DStreamHeader {
	uint32_t m_nFileSign;
	uint8_t m_nMajorVersion;
	uint8_t m_nMinorVersion;
	uint8_t m_nPatchVersion;
	uint8_t m_nStreamStorageType;
	uint32_t m_nPixelCountX;
	uint32_t m_nPixelCountY;
	double m_dDPIX;
	double m_dDPIY;
	double m_dOriginX;
	double m_dOriginY;
	uint64_t m_nDataOffset;
	uint32_t m_nReserved[32];
} sDiscreteField2DStreamHeader;
#pragma pack(pop)


PDiscreteFieldData2DInstance CDiscreteFieldData2DInstance::createFromBuffer(const std::vector<uint8_t>& Buffer)
{
	if (Buffer.size () < sizeof (sDiscreteField2DStreamHeader))
		throw ELibMCInterfaceException(LIBMC_ERROR_INVALIDDISCRETEFIELDBUFFER);

	sDiscreteField2DStreamHeader* header = (sDiscreteField2DStreamHeader*)Buffer.data();

	if (header->m_nFileSign != DISCRETEFIELD2D_STREAMFILESIGN)
		throw ELibMCInterfaceException(LIBMC_ERROR_INVALIDDISCRETEFIELDFILESIGN);

	if (header->m_nMajorVersion != DISCRETEFIELD2D_STREAMFILEMAJORVERSION)
		throw ELibMCInterfaceException(LIBMC_ERROR_INCOMPATIBLEDISCRETEFIELDFILEVERSION);

	if (header->m_nMinorVersion > DISCRETEFIELD2D_STREAMFILEMINORVERSION)
		throw ELibMCInterfaceException(LIBMC_ERROR_TOONEWDISCRETEFIELDFILEVERSION);

	if (header->m_nStreamStorageType != DISCRETEFIELD2D_STREAMSTORAGETYPE_RAWDATA)
		throw ELibMCInterfaceException(LIBMC_ERROR_TOONEWDISCRETEFIELDSTREAMTYPE);

	if (header->m_nDataOffset < sizeof(sDiscreteField2DStreamHeader))
		throw ELibMCInterfaceException(LIBMC_ERROR_INVALIDDISCRETEFIELDDATAOFFSET);

	auto pInstance = std::make_shared<CDiscreteFieldData2DInstance>(header->m_nPixelCountX, header->m_nPixelCountY, header->m_dDPIX, header->m_dDPIY, header->m_dOriginX, header->m_dOriginY, 0.0, false);

	uint64_t nPixelCount = (uint64_t)header->m_nPixelCountX * (uint64_t)header->m_nPixelCountY;
	if (header->m_nDataOffset + nPixelCount * sizeof (double) > Buffer.size ())
		throw ELibMCInterfaceException(LIBMC_ERROR_INVALIDDISCRETEFIELDSTREAMSIZE);

	auto * pDataVector = pInstance->m_Data.get ();
	if (pDataVector == nullptr)
		throw ELibMCInterfaceException(LIBMC_ERROR_INVALIDDISCRETEFIELDINTERNALDATA);
	if (pDataVector->size () != nPixelCount)
		throw ELibMCInterfaceException(LIBMC_ERROR_INVALIDDISCRETEFIELDINTERNALDATA);

	double * pTargetPtr = pDataVector->data();
	double * pSourcePtr = (double*)&Buffer.at(header->m_nDataOffset);
	for (uint64_t nIndex = 0; nIndex < nPixelCount; nIndex++) {
		*pTargetPtr = *pSourcePtr;
		pTargetPtr++;
		pSourcePtr++;
	}


	return pInstance;
}

CDiscreteFieldData2DInstance::CDiscreteFieldData2DInstance(size_t nPixelCountX, size_t nPixelCountY, double dDPIX, double dDPIY, double dOriginX, double dOriginY, double dDefaultValue, bool bDoClear)
	: m_nPixelCountX (nPixelCountX), m_nPixelCountY (nPixelCountY), m_dDPIX (dDPIX), m_dDPIY (dDPIY), m_dOriginX (dOriginX), m_dOriginY (dOriginY)
{
	if (nPixelCountX <= 0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPIXELCOUNT);
	if (nPixelCountY <= 0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPIXELCOUNT);
	if (nPixelCountX > DISCRETEFIELD_MAXPIXELCOUNT)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPIXELCOUNT);
	if (nPixelCountY > DISCRETEFIELD_MAXPIXELCOUNT)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPIXELCOUNT);
	if (dDPIX <= 0.0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDDPIVALUE);
	if (dDPIY <= 0.0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDDPIVALUE);
	if (abs (dOriginX) > DISCRETEFIELD_MAXORIGINCOORDINATE)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_ORIGINOUTOFRANGE);
	if (abs(dOriginY) > DISCRETEFIELD_MAXORIGINCOORDINATE)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_ORIGINOUTOFRANGE);

	m_Data = std::make_unique<std::vector<double>> ();

	m_Data->resize((size_t)m_nPixelCountX * (size_t)m_nPixelCountY);

	if (bDoClear)
		Clear(dDefaultValue);

}
		
CDiscreteFieldData2DInstance::~CDiscreteFieldData2DInstance()
{
	
}

void CDiscreteFieldData2DInstance::GetDPI(double& dDPIValueX, double& dDPIValueY)
{
	dDPIValueX = m_dDPIX;
	dDPIValueY = m_dDPIY;
}

void CDiscreteFieldData2DInstance::SetDPI(const double dDPIValueX, const double dDPIValueY)
{
	if (dDPIValueX <= 0.0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDDPIVALUE);
	if (dDPIValueY <= 0.0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDDPIVALUE);

	m_dDPIX = dDPIValueX;
	m_dDPIY = dDPIValueY;
}

void CDiscreteFieldData2DInstance::GetOriginInMM(double& dOriginX, double& dOriginY)
{
	dOriginX = m_dOriginX;
	dOriginY = m_dOriginY;
}

void CDiscreteFieldData2DInstance::SetOriginInMM(const double dOriginX, const double dOriginY)
{
	m_dOriginX = dOriginX;
	m_dOriginY = dOriginY;
}

void CDiscreteFieldData2DInstance::GetSizeInMM(double& dSizeX, double& dSizeY)
{
	// 1 inch is 25.4 mm
	double dMMperPixelX = 25.4 / m_dDPIX;
	double dMMperPixelY = 25.4 / m_dDPIY;
	dSizeX = m_nPixelCountX * dMMperPixelX;
	dSizeY = m_nPixelCountY * dMMperPixelY;
}

void CDiscreteFieldData2DInstance::GetSizeInPixels(uint32_t& nPixelCountX, uint32_t& nPixelCountY)
{
	nPixelCountX = (uint32_t) m_nPixelCountX;
	nPixelCountY = (uint32_t) m_nPixelCountY;
}

void CDiscreteFieldData2DInstance::ResizeField(uint32_t& nPixelCountX, uint32_t& nPixelCountY, double dDefaultValue)
{
	if (m_Data.get() == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDFIELDBUFFER);

	if (nPixelCountX <= 0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPIXELCOUNT);
	if (nPixelCountY <= 0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPIXELCOUNT);
	if (nPixelCountX > DISCRETEFIELD_MAXPIXELCOUNT)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPIXELCOUNT);
	if (nPixelCountY > DISCRETEFIELD_MAXPIXELCOUNT)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPIXELCOUNT);

	if ((nPixelCountX == m_nPixelCountX) && (nPixelCountY == m_nPixelCountY)) {
		return;
	}

	auto pNewData = std::make_unique<std::vector<double>>();

	pNewData->resize((size_t)nPixelCountX * (size_t)nPixelCountY);

	for (uint32_t nY = 0; nY < nPixelCountY; nY++) {
		double* pTarget = &pNewData->at((size_t)nY * (size_t)nPixelCountX);

		if (nY < m_nPixelCountY) {
			double * pSource = &m_Data->at((size_t)nY * (size_t)m_nPixelCountX);

			for (uint32_t nX = 0; nX < nPixelCountX; nX++) {
				
				if (nX < m_nPixelCountX) {
					*pTarget = *pSource;
					pSource++;
				}
				else {
					*pTarget = dDefaultValue;
				}
				pTarget++;
			
			}
		}
		else {

			for (uint32_t nX = 0; nX < nPixelCountX; nX++) {
				*pTarget = dDefaultValue;
				pTarget++;
			}

		}
		
	}

	m_Data.reset(pNewData.release ());
	m_nPixelCountX = nPixelCountX;
	m_nPixelCountY = nPixelCountY;


}

void CDiscreteFieldData2DInstance::Clear(const double dValue)
{
	if (m_Data.get() == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDFIELDBUFFER);

	for (auto iter = m_Data->begin(); iter != m_Data->end(); iter++) {
		*iter = dValue;
	}

}

void CDiscreteFieldData2DInstance::Clamp(const double dMinValue, const double dMaxValue)
{
	if (dMinValue >= dMaxValue)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDCLAMPINTERVAL);

	for (auto iter = m_Data->begin(); iter != m_Data->end(); iter++) {
		auto dValue = *iter;
		if (dValue < dMinValue)
			*iter = dMinValue;
		if (dValue > dMaxValue)
			*iter = dMaxValue;
	}

}


double CDiscreteFieldData2DInstance::GetPixel(const uint32_t nX, const uint32_t nY)
{
	if (m_Data.get() == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDFIELDBUFFER);

	if (nX >= m_nPixelCountX)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDXCOORDINATE);
	if (nY >= m_nPixelCountY)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDYCOORDINATE);

	size_t nAddress = (size_t)nX + (size_t)nY * (size_t)m_nPixelCountX;
	return m_Data->at(nAddress);
}

void CDiscreteFieldData2DInstance::SetPixel(const uint32_t nX, const uint32_t nY, const double dValue)
{
	if (m_Data.get() == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDFIELDBUFFER);

	if (nX >= m_nPixelCountX)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDXCOORDINATE);
	if (nY >= m_nPixelCountY)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDYCOORDINATE);

	size_t nAddress = (size_t)nX + (size_t)nY * (size_t)m_nPixelCountX;
	m_Data->at(nAddress) = dValue;

}

void CDiscreteFieldData2DInstance::GetPixelRange(const uint32_t nXMin, const uint32_t nYMin, const uint32_t nXMax, const uint32_t nYMax, uint64_t nValueBufferSize, uint64_t* pValueNeededCount, double* pValueBuffer)
{
	throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_NOTIMPLEMENTED);
}

void CDiscreteFieldData2DInstance::SetPixelRange(const uint32_t nXMin, const uint32_t nYMin, const uint32_t nXMax, const uint32_t nYMax, const uint64_t nValueBufferSize, const double* pValueBuffer)
{
	throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_NOTIMPLEMENTED);
}


PDiscreteFieldData2DInstance CDiscreteFieldData2DInstance::ScaleFieldDown(const uint32_t nFactorX, const uint32_t nFactorY)
{
	if (nFactorX == 0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDFIELDSCALINGFACTOR);
	if (nFactorY == 0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDFIELDSCALINGFACTOR);

	size_t nNewPixelCountX = (m_nPixelCountX + (nFactorX - 1)) / nFactorX;
	size_t nNewPixelCountY = (m_nPixelCountY + (nFactorY - 1)) / nFactorY;

	PDiscreteFieldData2DInstance pNewField = std::make_shared<CDiscreteFieldData2DInstance>(nNewPixelCountX, nNewPixelCountY, m_dDPIX * (double)nFactorX, m_dDPIY * (double)nFactorX, m_dOriginX, m_dOriginY, 0.0, false);

	for (uint32_t nY = 0; nY < nNewPixelCountY; nY++) {

		double* pTarget = &pNewField->m_Data->at (nY * nNewPixelCountX);
		for (uint32_t nX = 0; nX < nNewPixelCountX; nX++) {
			double dValueSum = 0.0;
			uint32_t nCount = 0;

			for (uint32_t dY = 0; dY < nFactorY; dY++) {
				size_t nTargetY = ((uint64_t)nY + dY);

				if (nTargetY < m_nPixelCountY) {

					double* pSource = &m_Data->at(nTargetY * (size_t)nFactorY * nNewPixelCountX + nX * (size_t)nFactorX);
					size_t nTargetX = nX;
					for (uint32_t dX = 0; dX < nFactorX; dX++) {
						if (nTargetX < m_nPixelCountX) {
							dValueSum += *pSource;
							pSource++;
							nCount++;
						}
						else {
							break;
						}
					}
				}
				else {
					break;
				}
			}

			if (nCount == 0)
				throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INTERNALSCALINGERROR);

			*pTarget = dValueSum / (double) nCount;
			pTarget++;
		}
	}

	return pNewField;
}

PDiscreteFieldData2DInstance CDiscreteFieldData2DInstance::ScaleFieldUp(const uint32_t nFactorX, const uint32_t nFactorY)
{
	if (nFactorX == 0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDFIELDSCALINGFACTOR);
	if (nFactorY == 0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDFIELDSCALINGFACTOR);

	size_t nNewPixelCountX = m_nPixelCountX * nFactorX;
	size_t nNewPixelCountY = m_nPixelCountY * nFactorY;

	if (nNewPixelCountX > DISCRETEFIELD_MAXPIXELCOUNT)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_SCALINGEXCEEDSMAXIMUMPIXELCOUNT);
	if (nNewPixelCountY > DISCRETEFIELD_MAXPIXELCOUNT)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_SCALINGEXCEEDSMAXIMUMPIXELCOUNT);

	PDiscreteFieldData2DInstance pNewField = std::make_shared<CDiscreteFieldData2DInstance>(nNewPixelCountX, nNewPixelCountY, m_dDPIX / (double)nFactorX, m_dDPIY / (double)nFactorX, m_dOriginX, m_dOriginY, 0.0, false);

	for (uint32_t nY = 0; nY < m_nPixelCountY; nY++) {

		double* pSource = &m_Data->at(nY * m_nPixelCountX);
		for (uint32_t nX = 0; nX < m_nPixelCountX; nX++) {
			double dValue = *pSource;
			pSource++;

			for (uint32_t dY = 0; dY < nFactorY; dY++) {
				double* pTarget = &pNewField->m_Data->at(((size_t)nY * nFactorY + dY) * nNewPixelCountX);
				for (uint32_t dX = 0; dX < nFactorX; dX++) {
					*pTarget = dValue;
					pTarget++;
				}
			}

		}
	}

	return pNewField;

}

void CDiscreteFieldData2DInstance::DiscretizeWithMapping(const uint64_t nDiscreteValuesBufferSize, const double* pDiscreteValuesBuffer, const uint64_t nNewValuesBufferSize, const double* pNewValuesBuffer)
{
	throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_NOTIMPLEMENTED);
}

void CDiscreteFieldData2DInstance::TransformField(const double dScale, const double dOffset)
{
	for (auto iter = m_Data->begin(); iter != m_Data->end(); iter++) {
		double dValue = *iter;
		*iter = (dValue * dScale) + dOffset;
	}
}

void CDiscreteFieldData2DInstance::AddField(CDiscreteFieldData2DInstance* pOtherField, const double dScale, const double dOffset)
{
	if (pOtherField == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPARAM);

	if (pOtherField->m_nPixelCountX != m_nPixelCountX)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDFIELDSIZE);

	if (pOtherField->m_nPixelCountY != m_nPixelCountY)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDFIELDSIZE);

	if (pOtherField->m_Data->size() != m_Data->size())
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INTERNALFIELDSIZEERROR);

	auto srcIter = pOtherField->m_Data->begin();
	for (auto dstIter = m_Data->begin(); dstIter != m_Data->end();) {
		*dstIter += (*srcIter * dScale) + dOffset;
		srcIter++;
		dstIter++;
	}
}

PDiscreteFieldData2DInstance CDiscreteFieldData2DInstance::Duplicate()
{
	PDiscreteFieldData2DInstance pNewField = std::make_shared<CDiscreteFieldData2DInstance>(m_nPixelCountX, m_nPixelCountY, m_dDPIX, m_dDPIY, m_dOriginX, m_dOriginY, 0.0, false);
	if (pNewField->m_Data->size () != m_Data->size ())
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INTERNALFIELDSIZEERROR);

	auto dstIter = pNewField->m_Data->begin();
	for (auto srcIter = m_Data->begin(); srcIter != m_Data->end();) {
		*dstIter = *srcIter;
		srcIter++;
		dstIter++;
	}

	return pNewField;

}

void CDiscreteFieldData2DInstance::renderRGBImage(std::vector<uint8_t>* pPixelData, double minValue, double minRed, double minGreen, double minBlue, double midValue, double midRed, double midGreen, double midBlue, double maxValue, double maxRed, double maxGreen, double maxBlue)
{
	if (pPixelData == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPARAM);

	pPixelData->resize((size_t) m_nPixelCountX * (size_t)m_nPixelCountY * 3);

	double dDeltaMin = midValue - minValue;
	double dDeltaMax = maxValue - midValue;

	if (dDeltaMin < 0.0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDCOLORRANGE);
	if (dDeltaMax < 0.0)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDCOLORRANGE);

	size_t nPixelIndex = 0;

	for (auto iter = m_Data->begin(); iter != m_Data->end(); iter++) {
		double dValue = *iter;
		double dFactor;

		double dRed, dGreen, dBlue;

		if (dValue < midValue) {

			if (dDeltaMin > DISCRETEFIELD_MINVALUEDISTANCE) {
				dFactor = (dValue - minValue) / dDeltaMin;
			}
			else {
				dFactor = 0.0;
			}

			if (dFactor < 0.0)
				dFactor = 0.0;

			if (dFactor > 1.0)
				dFactor = 1.0;

			dRed = minRed * (1.0 - dFactor) + midRed * dFactor;
			dGreen = minGreen * (1.0 - dFactor) + midGreen * dFactor;
			dBlue = minBlue * (1.0 - dFactor) + midBlue * dFactor;


		} else {

			if (dDeltaMax > DISCRETEFIELD_MINVALUEDISTANCE) {
				dFactor = (dValue - midValue) / dDeltaMax;
			}
			else {
				dFactor = 0.0;
			}

			if (dFactor < 0.0)
				dFactor = 0.0;

			if (dFactor > 1.0)
				dFactor = 1.0;

			dRed = midRed * (1.0 - dFactor) + maxRed * dFactor;
			dGreen = midGreen * (1.0 - dFactor) + maxGreen * dFactor;
			dBlue = midBlue * (1.0 - dFactor) + maxBlue * dFactor;


		}

		dRed = std::clamp(dRed, 0.0, 1.0);
		dGreen = std::clamp(dGreen, 0.0, 1.0);
		dBlue = std::clamp(dBlue, 0.0, 1.0);

		uint8_t nRed = (uint8_t) round(dRed * 255.0);
		uint8_t nGreen = (uint8_t)round(dGreen * 255.0);
		uint8_t nBlue = (uint8_t)round(dBlue * 255.0);

		pPixelData->at(nPixelIndex * 3) = nRed;
		pPixelData->at(nPixelIndex * 3 + 1) = nGreen;
		pPixelData->at(nPixelIndex * 3 + 2) = nBlue;

		nPixelIndex++;
	}

	
	
}


void CDiscreteFieldData2DInstance::renderAveragePointValues_FloorSampling(const LibMCEnv_double dDefaultValue, const uint64_t nPointValuesBufferSize, const LibMCEnv::sFieldData2DPoint* pPointValuesBuffer)
{
	if (nPointValuesBufferSize == 0) {
		Clear(dDefaultValue);
		return;
	}

	if (nPointValuesBufferSize > DISCRETEFIELD_MAXPOINTVALUESCOUNT)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_SAMPLEPOINTCOUNTEXCEEDSMAXIMUM);
	if (pPointValuesBuffer == nullptr)
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPARAM);

	std::vector<double> sampleSumBuffer;
	sampleSumBuffer.resize(m_nPixelCountX * m_nPixelCountY);


	std::vector<uint32_t> sampleCountBuffer;
	sampleCountBuffer.resize(m_nPixelCountX * m_nPixelCountY);
	for (auto& sampleCount : sampleCountBuffer)
		sampleCount = 0;

	double dPixelPerMMX = m_dDPIX / 25.4;
	double dPixelPerMMY = m_dDPIY / 25.4;

	auto pPointValue = pPointValuesBuffer;
	for (size_t nPointValueIndex = 0; nPointValueIndex < nPointValuesBufferSize; nPointValueIndex++) {
		double dPixelPositionX = (pPointValue->m_Coordinates[0] - m_dOriginX) * dPixelPerMMX;
		double dPixelPositionY = (pPointValue->m_Coordinates[1] - m_dOriginY) * dPixelPerMMY;
		double dValue = pPointValue->m_Value;

		int64_t nRoundedPixelPositionX = (int64_t) floor(dPixelPositionX);
		int64_t nRoundedPixelPositionY = (int64_t) floor(dPixelPositionY);

		if ((nRoundedPixelPositionX >= 0) && (nRoundedPixelPositionY >= 0) &&
			(nRoundedPixelPositionX < (int64_t) m_nPixelCountX) && (nRoundedPixelPositionY < (int64_t) m_nPixelCountY)) {

			size_t nAddress = nRoundedPixelPositionX + nRoundedPixelPositionY * m_nPixelCountX;
			auto & sampleCount = sampleCountBuffer.at (nAddress);
			auto & sampleSum = sampleSumBuffer.at(nAddress);
			if (sampleCount == 0) {
				sampleSum = dValue;
				sampleCount = 1;
			}
			else {
				sampleSum += dValue;
				sampleCount++;
			}

		}

		pPointValue++;
	}

	for (uint32_t nY = 0; nY < m_nPixelCountY; nY++) {
		for (uint32_t nX = 0; nX < m_nPixelCountX; nX++) {
			size_t nAddress = nX + nY * m_nPixelCountX;
			auto& sampleCount = sampleCountBuffer.at(nAddress);
			auto& sampleSum = sampleSumBuffer.at(nAddress);

			if (sampleCount == 0) {
				SetPixel(nX, nY, dDefaultValue);
			}
			else {
				SetPixel(nX, nY, sampleSum / (double)sampleCount);
			}
		}

	}

}

void CDiscreteFieldData2DInstance::saveToBuffer(std::vector<uint8_t>& Buffer)
{
	uint64_t nPixelCount = m_nPixelCountX * m_nPixelCountY;
	Buffer.resize (sizeof (sDiscreteField2DStreamHeader) + nPixelCount * sizeof (double));
	sDiscreteField2DStreamHeader* header = (sDiscreteField2DStreamHeader*)Buffer.data();

	memset((void*)header, 0, sizeof(sDiscreteField2DStreamHeader));
	header->m_nFileSign = DISCRETEFIELD2D_STREAMFILESIGN;
	header->m_nMajorVersion = DISCRETEFIELD2D_STREAMFILEMAJORVERSION;
	header->m_nMinorVersion = DISCRETEFIELD2D_STREAMFILEMINORVERSION;
	header->m_nPatchVersion = DISCRETEFIELD2D_STREAMFILEPATCHVERSION;
	header->m_nStreamStorageType = DISCRETEFIELD2D_STREAMSTORAGETYPE_RAWDATA;
	header->m_nPixelCountX = (uint32_t) m_nPixelCountX;
	header->m_nPixelCountY = (uint32_t) m_nPixelCountY;
	header->m_dDPIX = m_dDPIX;
	header->m_dDPIY = m_dDPIY;
	header->m_dOriginX = m_dOriginX;
	header->m_dOriginY = m_dOriginY;
	header->m_nDataOffset = sizeof(sDiscreteField2DStreamHeader);

	double* pSourcePtr = m_Data.get()->data();
	double* pTargetPtr = (double*)&Buffer.at(header->m_nDataOffset);
	for (uint64_t nIndex = 0; nIndex < nPixelCount; nIndex++) {
		*pTargetPtr = *pSourcePtr;
		pTargetPtr++;
		pSourcePtr++;
	}
}

void CDiscreteFieldData2DInstance::loadFromRawPixelData(const std::vector<uint8_t>& pixelData, LibMCEnv::eImagePixelFormat pixelFormat, double dBlackValue, double dWhiteValue)
{

	switch (pixelFormat) {
	case LibMCEnv::eImagePixelFormat::GreyScale8bit:
		if (pixelData.size() != (m_nPixelCountX * m_nPixelCountY))
			throw eLibMCEnvImagePixelFormat(LIBMCENV_ERROR_RAWPIXELDATASIZEMISMATCH);

		for (uint32_t nY = 0; nY < m_nPixelCountY; nY++) {

			double* pTarget = &m_Data->at(nY * m_nPixelCountX);
			const uint8_t* pSource = &pixelData.at (nY * m_nPixelCountX);
			for (uint32_t nX = 0; nX < m_nPixelCountX; nX++) {
				double dGreyScale = (*pSource) / 255.0;
				pSource++;

				double dValue = (1.0 - dGreyScale) * dBlackValue + dGreyScale * dWhiteValue;
				*pTarget = dValue;
				pTarget++;

			}
		}



		break;

	case LibMCEnv::eImagePixelFormat::RGB24bit:
		if (pixelData.size() != (m_nPixelCountX * m_nPixelCountY * 3))
			throw eLibMCEnvImagePixelFormat(LIBMCENV_ERROR_RAWPIXELDATASIZEMISMATCH);

		for (uint32_t nY = 0; nY < m_nPixelCountY; nY++) {

			double* pTarget = &m_Data->at(nY * m_nPixelCountX);
			const uint8_t* pSource = &pixelData.at(nY * m_nPixelCountX * 3);
			for (uint32_t nX = 0; nX < m_nPixelCountX; nX++) {
				int64_t nRed = *pSource; 
				pSource++;

				int64_t nGreen = *pSource;
				pSource++;

				int64_t nBlue = *pSource;
				pSource++;

				double dGreyScale = (nRed + nGreen + nBlue) / (255.0 * 3);

				double dValue = (1.0 - dGreyScale) * dBlackValue + dGreyScale * dWhiteValue;
				*pTarget = dValue;
				pTarget++;

			}
		}



		break;

	case LibMCEnv::eImagePixelFormat::RGBA32bit:
		if (pixelData.size() != (m_nPixelCountX * m_nPixelCountY * 4))
			throw eLibMCEnvImagePixelFormat(LIBMCENV_ERROR_RAWPIXELDATASIZEMISMATCH);

		for (uint32_t nY = 0; nY < m_nPixelCountY; nY++) {

			double* pTarget = &m_Data->at(nY * m_nPixelCountX);
			const uint8_t* pSource = &pixelData.at(nY * m_nPixelCountX * 4);
			for (uint32_t nX = 0; nX < m_nPixelCountX; nX++) {
				int64_t nRed = *pSource;
				pSource++;

				int64_t nGreen = *pSource;
				pSource++;

				int64_t nBlue = *pSource;
				pSource++;

				// Skip Alpha
				pSource++;

				double dGreyScale = (nRed + nGreen + nBlue) / (255.0 * 3);

				double dValue = (1.0 - dGreyScale) * dBlackValue + dGreyScale * dWhiteValue;
				*pTarget = dValue;
				pTarget++;

			}
		}



		break;

	default:
		throw ELibMCEnvInterfaceException(LIBMCENV_ERROR_INVALIDPIXELFORMAT);
	}

}
