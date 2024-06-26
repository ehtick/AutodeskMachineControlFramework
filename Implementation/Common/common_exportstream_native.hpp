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


#ifndef __AMCCOMMON_EXPORTSTREAM_NATIVE
#define __AMCCOMMON_EXPORTSTREAM_NATIVE

#include "common_exportstream.hpp"
#include <string>
#include <iostream>
#include <fstream>

namespace AMCCommon {

	class CExportStream_Native : public CExportStream {
	private:
		std::ofstream m_Stream;
	public:
		CExportStream_Native(const std::string & sFileName);
		~CExportStream_Native();

		bool seekPosition(uint64_t position, bool bHasToSucceed) override;
		bool seekForward(uint64_t bytes, bool bHasToSucceed) override;
		bool seekFromEnd(uint64_t bytes, bool bHasToSucceed) override;
		uint64_t getPosition() override;
		uint64_t writeBuffer(const void* pBuffer, uint64_t cbTotalBytesToWrite) override;

		void writeZeros(uint64_t bytes) override;

		void flushStream ();
	};

	typedef std::shared_ptr<CExportStream_Native> PExportStream_Native;

}

#endif // __AMCCOMMON_EXPORTSTREAM_NATIVE

