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


Abstract: This is a stub class definition of CGPIOSequence

*/

#include "libmcdriver_scanlab_gpiosequenceinstance.hpp"
#include "libmcdriver_scanlab_interfaceexception.hpp"

using namespace LibMCDriver_ScanLab::Impl;

#define GPIOSEQUENCE_MAXIDENTIFIERLENGTH 512
#define GPIOSEQUENCE_MAXLABELLENGTH 128
#define GPIOSEQUENCE_MAXDELAYINMS 120000000
#define GPIOSEQUENCE_MAXINPUTBIT 15
#define GPIOSEQUENCE_MAXOUTPUTBIT 15

CGPIOLabels::CGPIOLabels()
{

}

CGPIOLabels::~CGPIOLabels()
{

}

void CGPIOLabels::checkLabelName(const std::string& sLabel)
{
    if (sLabel.empty())
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_EMPTYGPIOLABELNAME);

    if (sLabel.length() > GPIOSEQUENCE_MAXLABELLENGTH)
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDGPIOLABELNAMELENGTH);

    for (auto ch : sLabel) {
        if (!(isalnum (ch) || (ch == '_') || (ch == '-')))
            throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDGPIOLABELNAME, "Invalid GPIO Label name: " + sLabel);
    }
}

void CGPIOLabels::addLabel(const std::string& sLabel, uint32_t nLabelAddress)
{
    checkLabelName(sLabel);

    m_LabelStartAddresses.insert(std::make_pair (sLabel, nLabelAddress));
}

uint32_t CGPIOLabels::findLabelAddress(const std::string& sLabel)
{
    checkLabelName(sLabel);

    auto iIter = m_LabelStartAddresses.find(sLabel);
    if (iIter == m_LabelStartAddresses.end ())
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_GPIOLABELNOTFOUND, "GPIO Label not found: " + sLabel);

    return iIter->second;
}

CGPIOTask::CGPIOTask(uint32_t nRelativeStartAddress, PGPIOLabels pLabels)
    : m_nRelativeStartAddress (nRelativeStartAddress), m_pLabels (pLabels)
{
    if (pLabels.get() == nullptr)
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDPARAM);

}

CGPIOTask::~CGPIOTask()
{

}

uint32_t CGPIOTask::getRelativeStartAddress()
{
    return m_nRelativeStartAddress;
}

uint32_t CGPIOTask::findLabelAddress(const std::string& sLabel)
{
    return m_pLabels->findLabelAddress(sLabel);
}


CGPIOTask_Output::CGPIOTask_Output(uint32_t nRelativeStartAddress, PGPIOLabels pLabels, const uint32_t nOutputBit, const bool bOutputValue)
    : CGPIOTask (nRelativeStartAddress, pLabels), m_nOutputBit (nOutputBit), m_bOutputValue (bOutputValue)
{

}

CGPIOTask_Output::~CGPIOTask_Output()
{

}

uint32_t CGPIOTask_Output::getOutputBit()
{
    return m_nOutputBit;
}

bool CGPIOTask_Output::getOutputValue()
{
    return m_bOutputValue;
}

uint32_t CGPIOTask_Output::getNeededListCapacity()
{
    return 1;
}


void CGPIOTask_Output::writeToSDKList(CScanLabSDK* pSDK, uint32_t nCardNo)
{
    if (pSDK == nullptr)
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDPARAM);

    uint32_t nBitmask = 1UL << m_nOutputBit;
    uint32_t nSelectionValue = 0;
    if (m_bOutputValue)
        nSelectionValue = nBitmask;

    pSDK->n_write_io_port_mask_list(nCardNo, nSelectionValue, nBitmask);
}



CGPIOTask_Delay::CGPIOTask_Delay(uint32_t nRelativeStartAddress, PGPIOLabels pLabels, const uint32_t nDelayInMilliseconds)
    : CGPIOTask (nRelativeStartAddress, pLabels), m_nDelayInMilliseconds (nDelayInMilliseconds)
{
    if ((nDelayInMilliseconds == 0) || (nDelayInMilliseconds > GPIOSEQUENCE_MAXDELAYINMS))
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDGPIOTASKDELAY);
}

CGPIOTask_Delay::~CGPIOTask_Delay()
{

}

uint32_t CGPIOTask_Delay::getDelayInMilliseconds()
{
    return m_nDelayInMilliseconds;
}

uint32_t CGPIOTask_Delay::getNeededListCapacity()
{
    return 1;
}

void CGPIOTask_Delay::writeToSDKList(CScanLabSDK* pSDK, uint32_t nCardNo)
{
    if (pSDK == nullptr)
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDPARAM);

    uint32_t nDelayInTicks = m_nDelayInMilliseconds * 100;

    pSDK->n_long_delay(nCardNo, nDelayInTicks);
}


CGPIOTask_WaitforInput::CGPIOTask_WaitforInput(uint32_t nRelativeStartAddress, PGPIOLabels pLabels, const uint32_t nInputBit, const bool bInputValue, const uint32_t nMaxDelayInMilliseconds)
    : CGPIOTask (nRelativeStartAddress, pLabels), m_nInputBit (nInputBit), m_bInputValue (bInputValue), m_nMaxDelayInMilliseconds (nMaxDelayInMilliseconds)
{
    if ((nMaxDelayInMilliseconds == 0) || (nMaxDelayInMilliseconds > GPIOSEQUENCE_MAXDELAYINMS))
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDGPIOTASKDELAY);
    if (nInputBit > GPIOSEQUENCE_MAXINPUTBIT)
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDGPIOINPUTBIT);

}

CGPIOTask_WaitforInput::~CGPIOTask_WaitforInput()
{

}

uint32_t CGPIOTask_WaitforInput::getInputBit()
{
    return m_nInputBit;
}

bool CGPIOTask_WaitforInput::getInputValue()
{
    return m_bInputValue;
}

uint32_t CGPIOTask_WaitforInput::getMaxDelayInMilliseconds()
{
    return m_nMaxDelayInMilliseconds;
}

uint32_t CGPIOTask_WaitforInput::getNeededListCapacity()
{
    return 6;
}

void CGPIOTask_WaitforInput::writeToSDKList(CScanLabSDK* pSDK, uint32_t nCardNo)
{
    if (pSDK == nullptr)
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDPARAM);

    uint32_t nMask1 = 0;
    uint32_t nMask0 = 0;

    if (m_bInputValue) {
        nMask1 = 1UL << m_nInputBit;
    }
    else {
        nMask0 = 1UL << m_nInputBit;
    }

    uint32_t nErrorVariableNo = 5;
    uint32_t nErrorCode = 1;

    pSDK->n_list_repeat(nCardNo); // Repeat list
    pSDK->n_list_jump_rel_cond(nCardNo, nMask1, nMask0, 5); 
    pSDK->n_long_delay(nCardNo, 100); 
    pSDK->n_list_until(nCardNo, m_nMaxDelayInMilliseconds);
    pSDK->n_set_free_variable_list(nCardNo, nErrorVariableNo, nErrorCode);
    pSDK->n_set_end_of_list(nCardNo);

}


CGPIOTask_Label::CGPIOTask_Label(uint32_t nRelativeStartAddress, PGPIOLabels pLabels, const std::string& sLabelName, const uint32_t nMaxPasses)
    : CGPIOTask (nRelativeStartAddress, pLabels), m_sLabelName (sLabelName), m_nMaxPasses (nMaxPasses)
{
    pLabels->addLabel(sLabelName, nRelativeStartAddress);
}

CGPIOTask_Label::~CGPIOTask_Label()
{

}

std::string CGPIOTask_Label::getLabelName()
{
    return m_sLabelName;
}

uint32_t CGPIOTask_Label::getMaxPasses()
{
    return m_nMaxPasses;
}

uint32_t CGPIOTask_Label::getNeededListCapacity()
{
    return 0;
}

void CGPIOTask_Label::writeToSDKList(CScanLabSDK* pSDK, uint32_t nCardNo)
{
    if (pSDK == nullptr)
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDPARAM);

}


CGPIOTask_GoToLabel::CGPIOTask_GoToLabel(uint32_t nRelativeStartAddress, PGPIOLabels pLabels, const std::string& sLabelName)
: CGPIOTask (nRelativeStartAddress, pLabels), m_sLabelName (sLabelName)
{

}

CGPIOTask_GoToLabel::~CGPIOTask_GoToLabel()
{

}

std::string CGPIOTask_GoToLabel::getLabelName()
{
     return m_sLabelName;
}


uint32_t CGPIOTask_GoToLabel::getNeededListCapacity()
{
    return 1;
}

void CGPIOTask_GoToLabel::writeToSDKList(CScanLabSDK* pSDK, uint32_t nCardNo)
{
    if (pSDK == nullptr)
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDPARAM);

    uint32_t nCurrentAddress = getRelativeStartAddress();
    uint32_t nLabelAddress = findLabelAddress(m_sLabelName);

    int32_t nRelativeJumpPosition = (int32_t)nLabelAddress - (int32_t)nCurrentAddress;
    pSDK->n_list_jump_rel(nCardNo, nRelativeJumpPosition);
}


CGPIOTask_ConditionalGoToLabel::CGPIOTask_ConditionalGoToLabel(uint32_t nRelativeStartAddress, PGPIOLabels pLabels, const uint32_t nInputBit, const bool bInputValue, const std::string& sLabelName)
    : CGPIOTask (nRelativeStartAddress, pLabels), m_nInputBit (nInputBit), m_bInputValue (bInputValue), m_sLabelName (sLabelName)
{
    if (nInputBit > GPIOSEQUENCE_MAXINPUTBIT)
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDGPIOINPUTBIT);

}

CGPIOTask_ConditionalGoToLabel::~CGPIOTask_ConditionalGoToLabel()
{

}

uint32_t CGPIOTask_ConditionalGoToLabel::getInputBit()
{
    return m_nInputBit;
}

bool CGPIOTask_ConditionalGoToLabel::getInputValue()
{
    return m_bInputValue;
}

std::string CGPIOTask_ConditionalGoToLabel::getLabelName()
{
    return m_sLabelName;
}

uint32_t CGPIOTask_ConditionalGoToLabel::getNeededListCapacity()
{
    return 0;
}

void CGPIOTask_ConditionalGoToLabel::writeToSDKList(CScanLabSDK* pSDK, uint32_t nCardNo)
{

    if (pSDK == nullptr)
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDPARAM);

    uint32_t nMask1 = 0;
    uint32_t nMask0 = 0;

    if (m_bInputValue) {
        nMask1 = 1UL << m_nInputBit;
    }
    else {
        nMask0 = 1UL << m_nInputBit;
    }

    uint32_t nCurrentAddress = getRelativeStartAddress();
    uint32_t nLabelAddress = findLabelAddress(m_sLabelName);

    int32_t nRelativeJumpPosition = (int32_t)nLabelAddress - (int32_t)nCurrentAddress;
    pSDK->n_list_jump_rel_cond(nCardNo, nMask1, nMask0, nRelativeJumpPosition);

}


CGPIOSequenceInstance::CGPIOSequenceInstance(const std::string& sIdentifier)
    : m_sIdentifier(sIdentifier), m_nListSize (0), m_bAutomaticSelection (true)
{
    if (sIdentifier.empty () || (sIdentifier.length () > GPIOSEQUENCE_MAXIDENTIFIERLENGTH))
        throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDSEQUENCEIDENTIFIER);

    for (auto ch : sIdentifier) {
        if (!(isalnum(ch) || (ch == '-') || (ch == '_')))
            throw ELibMCDriver_ScanLabInterfaceException(LIBMCDRIVER_SCANLAB_ERROR_INVALIDSEQUENCEIDENTIFIER);
    }

    m_pLabels = std::make_shared<CGPIOLabels>();

}

CGPIOSequenceInstance::~CGPIOSequenceInstance()
{

}

std::string CGPIOSequenceInstance::GetIdentifier()
{
    return m_sIdentifier;
}

void CGPIOSequenceInstance::Clear()
{
    m_Tasks.clear();
    m_nListSize = 0;
}

void CGPIOSequenceInstance::AddOutput(const LibMCDriver_ScanLab_uint32 nOutputBit, const bool bOutputValue)
{
    auto pTask = std::make_shared<CGPIOTask_Output>(m_nListSize, m_pLabels, nOutputBit, bOutputValue);
    m_nListSize += pTask->getNeededListCapacity();
    m_Tasks.push_back (pTask);
}


void CGPIOSequenceInstance::AddDelay(const LibMCDriver_ScanLab_uint32 nDelayInMilliseconds)
{
    auto pTask = std::make_shared<CGPIOTask_Delay> (m_nListSize, m_pLabels, nDelayInMilliseconds);
    m_nListSize += pTask->getNeededListCapacity();
    m_Tasks.push_back(pTask);
}


void CGPIOSequenceInstance::WaitforInput(const LibMCDriver_ScanLab_uint32 nInputBit, const bool bInputValue, const LibMCDriver_ScanLab_uint32 nMaxDelayInMilliseconds)
{
    auto pTask = std::make_shared<CGPIOTask_WaitforInput> (m_nListSize, m_pLabels, nInputBit, bInputValue, nMaxDelayInMilliseconds);
    m_nListSize += pTask->getNeededListCapacity();
    m_Tasks.push_back(pTask);
}

void CGPIOSequenceInstance::AddLabel(const std::string& sLabelName, const LibMCDriver_ScanLab_uint32 nMaxPasses)
{
    auto pTask = std::make_shared<CGPIOTask_Label> (m_nListSize, m_pLabels, sLabelName, nMaxPasses);
    m_nListSize += pTask->getNeededListCapacity();
    m_Tasks.push_back(pTask);
}

void CGPIOSequenceInstance::GoToLabel(const std::string& sLabelName)
{
    auto pTask = std::make_shared<CGPIOTask_GoToLabel> (m_nListSize, m_pLabels, sLabelName);
    m_nListSize += pTask->getNeededListCapacity();
    m_Tasks.push_back(pTask);
}

void CGPIOSequenceInstance::ConditionalGoToLabel(const LibMCDriver_ScanLab_uint32 nInputBit, const bool bInputValue, const std::string& sLabelName)
{
    auto pTask = std::make_shared<CGPIOTask_ConditionalGoToLabel>(m_nListSize, m_pLabels, nInputBit, bInputValue, sLabelName);
    m_nListSize += pTask->getNeededListCapacity();
    m_Tasks.push_back(pTask);
}

void CGPIOSequenceInstance::writeToSDKList(CScanLabSDK* pSDK, uint32_t nCardNo)
{
    for (auto pTask : m_Tasks) {
       pTask->writeToSDKList(pSDK, nCardNo);
    }

}

void CGPIOSequenceInstance::enableAutomaticSelection()
{
    m_bAutomaticSelection = true;
}

void CGPIOSequenceInstance::disableAutomaticSelection()
{
    m_bAutomaticSelection = false;
}

bool CGPIOSequenceInstance::getAutomaticSelection()
{
    return m_bAutomaticSelection;
}
