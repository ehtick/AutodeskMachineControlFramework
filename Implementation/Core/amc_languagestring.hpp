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


#ifndef __AMC_LANGUAGESTRING
#define __AMC_LANGUAGESTRING

#include <string>
#include <set>
#include <memory>

namespace pugi {
	class xml_node;
}

namespace AMC {
	
	class CLanguageDefinition;
	typedef std::shared_ptr<CLanguageDefinition> PLanguageDefinition;

	class CLanguageString {
	private:
		std::string m_sStringIdentifier;
		std::string m_sCustomValue;

	public:

		CLanguageString (const std::string & sStringIdentifier, const std::string & sCustomValue);
		
		CLanguageString(pugi::xml_node & xmlNode, const std::string& sAttributeName);

		virtual ~CLanguageString();
		
		std::string getStringIdentifier ();
		
		std::string getCustomValue ();

		std::string getTranslatedString (CLanguageDefinition * pLanguageDefinition);

		std::string getTranslatedString (PLanguageDefinition pLanguageDefinition);
		
	};

	
}


#endif //__AMC_LANGUAGESTRING

