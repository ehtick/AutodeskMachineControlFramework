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

#ifndef __AMC_UI_MODULE_CONTENTITEM_BUTTONGROUP
#define __AMC_UI_MODULE_CONTENTITEM_BUTTONGROUP

#include "header_protection.hpp"

#ifndef __AMCIMPL_UI_MODULE
#error this header is protected and should only be included in the corresponding implementation CPP files.
#endif

#include "amc_ui_module_contentitem.hpp"
#include "amc_ui_interfaces.hpp"
#include "amc_ui_expression.hpp"
#include "amc_parameterhandler.hpp"

#include "pugixml.hpp"

namespace AMC {

	amcDeclareDependingClass(CUIModule_ContentButtonGroup, PUIModule_ContentButtonGroup);
	amcDeclareDependingClass(CUIModule_ContentButton, PUIModule_ContentButton);
	amcDeclareDependingClass(CUIModule_ContentFormEntity, PUIModule_ContentFormEntity);
	amcDeclareDependingClass(CUIModuleEnvironment, PUIModuleEnvironment);



	enum class eUIModule_ContentButtonDistribution : int32_t {
		cbdRightAligned = 0,
		cbdLeftAligned = 1,
		cbdCentered = 2,
		cbdEquallyDistributed = 3,
	};


	class CUIModule_ContentButton {
	protected:

		std::string m_sUUID;
		std::string m_sElementPath;
		std::string m_sButtonName;

		CUIExpression m_CaptionExpression;
		CUIExpression m_DisabledExpression;
		CUIExpression m_TargetPageExpression;
		CUIExpression m_EventExpression;
		CUIExpression m_IconExpression;

		PStateMachineData m_pStateMachineData;

		std::string m_sEventFormValueSetting;
		std::list<PUIModule_ContentFormEntity> m_pFormValues;

		PParameterGroup getClientVariableGroup(CParameterHandler* pClientVariableHandler);

	public:

		CUIModule_ContentButton (const std::string & sGroupPath, const CUIExpression& Caption, const CUIExpression& TargetPage, const CUIExpression& Event, const std::string& sButtonName, const CUIExpression & IconName, const CUIExpression& Disabled, const std::string& sEventFormValueSetting, PStateMachineData pStateMachineData);

		virtual ~CUIModule_ContentButton();

		std::string getElementPath();

		std::string getUUID();

		std::string getEventFormValueSetting();

		std::string getButtonName();

		void addFormFieldValue(PUIModule_ContentFormEntity pEntity);

		void writeFormValuesToJSON (CJSONWriterArray & pArray);

		void writeVariablesToJSON(CJSONWriter& writer, CJSONWriterObject& object, CParameterHandler* pClientVariableHandler);

		PParameterGroup registerClientVariableGroup(CParameterHandler* pClientVariableHandler);

		void syncClientVariables(CParameterHandler* pClientVariableHandler);

	};

	class CUIModule_ContentButtonGroup : public CUIModule_ContentItem {
	protected:		
		std::list<PUIModule_ContentButton> m_Buttons;
		std::map<std::string, PUIModule_ContentButton> m_ButtonMap;
		CUIModule_ContentRegistry* m_pFormOwner;
		PStateMachineData m_pStateMachineData;

		eUIModule_ContentButtonDistribution m_ButtonDistribution;

	public:

		static PUIModule_ContentButtonGroup makeFromXML(const pugi::xml_node& xmlNode, const std::string& sItemName, const std::string& sModulePath, PUIModuleEnvironment pUIModuleEnvironment);

		CUIModule_ContentButtonGroup(CUIModule_ContentRegistry* pFormOwner, const eUIModule_ContentButtonDistribution buttonDistribution, const std::string& sItemName, const std::string & sModulePath, PStateMachineData pStateMachineData);

		virtual ~CUIModule_ContentButtonGroup();

		void addDefinitionToJSON(CJSONWriter& writer, CJSONWriterObject& object, CParameterHandler* pClientVariableHandler) override;

		void addContentToJSON(CJSONWriter& writer, CJSONWriterObject& object, CParameterHandler* pClientVariableHandler, uint32_t nStateID) override;

		PUIModule_ContentButton addButton(const CUIExpression& Caption, const CUIExpression& TargetPage, const CUIExpression& Event, const std::string& sButtonName, const CUIExpression& IconName, const CUIExpression& DisabledExpression, const std::string& sEventFormValueSetting);

		virtual void configurePostLoading() override;

		// Returns all UUIDs that could be contained in this Item
		virtual std::list <std::string> getReferenceUUIDs() override;

		eUIModule_ContentButtonDistribution getButtonDistribution ();
		void setButtonDistribution(const eUIModule_ContentButtonDistribution buttonDistribution);

		static eUIModule_ContentButtonDistribution stringToButtonDistribution(const std::string & sValue);
		static std::string buttonDistributionToString(const eUIModule_ContentButtonDistribution buttonDistribution);

		virtual std::string findElementPathByUUID(const std::string& sUUID) override;

		virtual void populateClientVariables(CParameterHandler* pClientVariableHandler) override;


	};


}


#endif //__AMC_UI_MODULE_CONTENTITEM_BUTTONGROUP



