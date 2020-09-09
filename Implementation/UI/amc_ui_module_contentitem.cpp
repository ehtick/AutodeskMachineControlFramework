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

#define __AMCIMPL_UI_MODULE
#define __AMCIMPL_API_CONSTANTS

#include "amc_ui_module_contentitem.hpp"
#include "libmc_interfaceexception.hpp"

#include "amc_api_constants.hpp"
#include "Common/common_utils.hpp"

using namespace AMC;


CUIModule_ContentItem::CUIModule_ContentItem(const std::string& sUUID)
	: m_sUUID (AMCCommon::CUtils::normalizeUUIDString (sUUID))
{

}

CUIModule_ContentItem::~CUIModule_ContentItem()
{

}

std::string CUIModule_ContentItem::getUUID()
{
	return m_sUUID;
}



CUIModule_ContentParagraph::CUIModule_ContentParagraph(const std::string& sText)
	: CUIModule_ContentItem(AMCCommon::CUtils::createUUID ()), m_sText (sText)
{

}

CUIModule_ContentParagraph::~CUIModule_ContentParagraph()
{

}

std::string CUIModule_ContentParagraph::getText()
{
	return m_sText;
}

void CUIModule_ContentParagraph::addToJSON(CJSONWriter& writer, CJSONWriterObject& object)
{
	object.addString(AMC_API_KEY_UI_ITEMTYPE, "paragraph");
	object.addString(AMC_API_KEY_UI_ITEMUUID, m_sUUID);
	object.addString(AMC_API_KEY_UI_ITEMTEXT, m_sText);
}



CUIModule_ContentImage::CUIModule_ContentImage(const std::string& sUUID)
	: CUIModule_ContentItem (sUUID)
{

}

CUIModule_ContentImage::~CUIModule_ContentImage()
{

}


void CUIModule_ContentImage::addToJSON(CJSONWriter& writer, CJSONWriterObject& object)
{
	object.addString(AMC_API_KEY_UI_ITEMTYPE, "image");
	object.addString(AMC_API_KEY_UI_ITEMUUID, m_sUUID);
}

CUIModule_ContentUpload::CUIModule_ContentUpload(const std::string& sUploadClass, const std::string& sUploadCaption)
	: CUIModule_ContentItem(AMCCommon::CUtils::createUUID()), m_sUploadClass(sUploadClass), m_sUploadCaption (sUploadCaption)
{

}

CUIModule_ContentUpload::~CUIModule_ContentUpload()
{

}

void CUIModule_ContentUpload::addToJSON(CJSONWriter& writer, CJSONWriterObject& object)
{
	object.addString(AMC_API_KEY_UI_ITEMTYPE, "upload");
	object.addString(AMC_API_KEY_UI_ITEMUPLOADCLASS, m_sUploadClass);
	object.addString(AMC_API_KEY_UI_ITEMUPLOADCAPTION, m_sUploadCaption);
	object.addInteger(AMC_API_KEY_UI_ITEMUPLOADISINITIAL, 1);
	object.addInteger(AMC_API_KEY_UI_ITEMUPLOADISSAVING, 0);
	object.addString(AMC_API_KEY_UI_ITEMUPLOADFILENAME, "");
}
