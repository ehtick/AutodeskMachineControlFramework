/*++

Copyright (C) 2022 Autodesk Inc.

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


Abstract: This is the class declaration of CDriver_TCPIPPacket

*/


#ifndef __LIBMCDRIVER_TCPIP_DRIVER_TCPIPPACKET
#define __LIBMCDRIVER_TCPIP_DRIVER_TCPIPPACKET

#include "libmcdriver_tcpip_interfaces.hpp"

// Parent classes
#include "libmcdriver_tcpip_base.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.


namespace LibMCDriver_TCPIP {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CDriver_TCPIPPacket 
**************************************************************************************************************************/

class CDriver_TCPIPPacket : public virtual IDriver_TCPIPPacket, public virtual CBase {
private:


protected:

    std::vector<uint8_t> m_BufferData;

public:

    CDriver_TCPIPPacket();
    virtual ~CDriver_TCPIPPacket();

	LibMCDriver_TCPIP_uint32 GetSize() override;

	void GetData(LibMCDriver_TCPIP_uint64 nBufferBufferSize, LibMCDriver_TCPIP_uint64* pBufferNeededCount, LibMCDriver_TCPIP_uint8 * pBufferBuffer) override;

    std::vector<uint8_t> & getBufferDataReference ();

};

} // namespace Impl
} // namespace LibMCDriver_TCPIP

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // __LIBMCDRIVER_TCPIP_DRIVER_TCPIPPACKET
