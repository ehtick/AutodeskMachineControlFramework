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


This file has been generated by the Automatic Component Toolkit (ACT) version 1.8.0-develop.

Abstract: This is an autogenerated C++ header file in order to allow easy
development of MC Driver cifX. The implementer of MC Driver cifX needs to
derive concrete classes from the abstract classes in this header.

Interface version: 2.0.0

*/


#ifndef __LIBMCDRIVER_CIFX_CPPINTERFACES
#define __LIBMCDRIVER_CIFX_CPPINTERFACES

#include <string>
#include <memory>

#include "libmcdriver_cifx_types.hpp"


#include "libmcenv_dynamic.hpp"

namespace LibMCDriver_CifX {
namespace Impl {

/**
 Forward declarations of class interfaces
*/
class IBase;
class IDriver;
class IChannelInformation;
class IDriver_CifX;



/*************************************************************************************************************************
 Parameter Cache definitions
**************************************************************************************************************************/

class ParameterCache {
	public:
		virtual ~ParameterCache() {}
};

template <class T1> class ParameterCache_1 : public ParameterCache {
	private:
		T1 m_param1;
	public:
		ParameterCache_1 (const T1 & param1)
			: m_param1 (param1)
		{
		}

		void retrieveData (T1 & param1)
		{
			param1 = m_param1;
		}
};

template <class T1, class T2> class ParameterCache_2 : public ParameterCache {
	private:
		T1 m_param1;
		T2 m_param2;
	public:
		ParameterCache_2 (const T1 & param1, const T2 & param2)
			: m_param1 (param1), m_param2 (param2)
		{
		}

		void retrieveData (T1 & param1, T2 & param2)
		{
			param1 = m_param1;
			param2 = m_param2;
		}
};

template <class T1, class T2, class T3> class ParameterCache_3 : public ParameterCache {
	private:
		T1 m_param1;
		T2 m_param2;
		T3 m_param3;
	public:
		ParameterCache_3 (const T1 & param1, const T2 & param2, const T3 & param3)
			: m_param1 (param1), m_param2 (param2), m_param3 (param3)
		{
		}

		void retrieveData (T1 & param1, T2 & param2, T3 & param3)
		{
			param1 = m_param1;
			param2 = m_param2;
			param3 = m_param3;
		}
};

template <class T1, class T2, class T3, class T4> class ParameterCache_4 : public ParameterCache {
	private:
		T1 m_param1;
		T2 m_param2;
		T3 m_param3;
		T4 m_param4;
	public:
		ParameterCache_4 (const T1 & param1, const T2 & param2, const T3 & param3, const T4 & param4)
			: m_param1 (param1), m_param2 (param2), m_param3 (param3), m_param4 (param4)
		{
		}

		void retrieveData (T1 & param1, T2 & param2, T3 & param3, T4 & param4)
		{
			param1 = m_param1;
			param2 = m_param2;
			param3 = m_param3;
			param4 = m_param4;
		}
};

template <class T1, class T2, class T3, class T4, class T5> class ParameterCache_5 : public ParameterCache {
	private:
		T1 m_param1;
		T2 m_param2;
		T3 m_param3;
		T4 m_param4;
		T5 m_param5;
	public:
		ParameterCache_5 (const T1 & param1, const T2 & param2, const T3 & param3, const T4 & param4, const T5 & param5)
			: m_param1 (param1), m_param2 (param2), m_param3 (param3), m_param4 (param4), m_param5 (param5)
		{
		}

		void retrieveData (T1 & param1, T2 & param2, T3 & param3, T4 & param4, T5 & param5)
		{
			param1 = m_param1;
			param2 = m_param2;
			param3 = m_param3;
			param4 = m_param4;
			param5 = m_param5;
		}
};

template <class T1, class T2, class T3, class T4, class T5, class T6> class ParameterCache_6 : public ParameterCache {
	private:
		T1 m_param1;
		T2 m_param2;
		T3 m_param3;
		T4 m_param4;
		T5 m_param5;
		T6 m_param6;
	public:
		ParameterCache_6 (const T1 & param1, const T2 & param2, const T3 & param3, const T4 & param4, const T5 & param5, const T6 & param6)
			: m_param1 (param1), m_param2 (param2), m_param3 (param3), m_param4 (param4), m_param5 (param5), m_param6 (param6)
		{
		}

		void retrieveData (T1 & param1, T2 & param2, T3 & param3, T4 & param4, T5 & param5, T6 & param6)
		{
			param1 = m_param1;
			param2 = m_param2;
			param3 = m_param3;
			param4 = m_param4;
			param5 = m_param5;
			param6 = m_param6;
		}
};


/*************************************************************************************************************************
 Class interface for Base 
**************************************************************************************************************************/

class IBase {
private:
	std::unique_ptr<ParameterCache> m_ParameterCache;
public:
	/**
	* IBase::~IBase - virtual destructor of IBase
	*/
	virtual ~IBase() {};

	/**
	* IBase::ReleaseBaseClassInterface - Releases ownership of a base class interface. Deletes the reference, if necessary.
	* @param[in] pIBase - The base class instance to release
	*/
	static void ReleaseBaseClassInterface(IBase* pIBase)
	{
		if (pIBase) {
			pIBase->DecRefCount();
		}
	};

	/**
	* IBase::AcquireBaseClassInterface - Acquires shared ownership of a base class interface.
	* @param[in] pIBase - The base class instance to acquire
	*/
	static void AcquireBaseClassInterface(IBase* pIBase)
	{
		if (pIBase) {
			pIBase->IncRefCount();
		}
	};


	/**
	* IBase::GetLastErrorMessage - Returns the last error registered of this class instance
	* @param[out] sErrorMessage - Message of the last error registered
	* @return Has an error been registered already
	*/
	virtual bool GetLastErrorMessage(std::string & sErrorMessage) = 0;

	/**
	* IBase::ClearErrorMessages - Clears all registered messages of this class instance
	*/
	virtual void ClearErrorMessages() = 0;

	/**
	* IBase::RegisterErrorMessage - Registers an error message with this class instance
	* @param[in] sErrorMessage - Error message to register
	*/
	virtual void RegisterErrorMessage(const std::string & sErrorMessage) = 0;

	/**
	* IBase::IncRefCount - Increases the reference count of a class instance
	*/
	virtual void IncRefCount() = 0;

	/**
	* IBase::DecRefCount - Decreases the reference count of a class instance and free releases it, if the last reference has been removed
	* @return Has the object been released
	*/
	virtual bool DecRefCount() = 0;

	/**
	* IBase::_setCache - set parameter cache of object
	*/
	void _setCache(ParameterCache * pCache)
	{
		m_ParameterCache.reset(pCache);
	}

	/**
	* IBase::_getCache - returns parameter cache of object
	*/
	ParameterCache* _getCache()
	{
		return m_ParameterCache.get();
	}

};


/**
 Definition of a shared pointer class for IBase
*/
template<class T>
class IBaseSharedPtr : public std::shared_ptr<T>
{
public:
	explicit IBaseSharedPtr(T* t = nullptr)
		: std::shared_ptr<T>(t, IBase::ReleaseBaseClassInterface)
	{
		t->IncRefCount();
	}

	// Reset function, as it also needs to properly set the deleter.
	void reset(T* t = nullptr)
	{
		std::shared_ptr<T>::reset(t, IBase::ReleaseBaseClassInterface);
	}

	// Get-function that increases the Base class's reference count
	T* getCoOwningPtr()
	{
		T* t = this->get();
		t->IncRefCount();
		return t;
	}
};


typedef IBaseSharedPtr<IBase> PIBase;


/*************************************************************************************************************************
 Class interface for Driver 
**************************************************************************************************************************/

class IDriver : public virtual IBase {
public:
	/**
	* IDriver::Configure - Configures a driver with its specific configuration data.
	* @param[in] sConfigurationString - Configuration data of driver.
	*/
	virtual void Configure(const std::string & sConfigurationString) = 0;

	/**
	* IDriver::GetName - returns the name identifier of the driver
	* @return Name of the driver.
	*/
	virtual std::string GetName() = 0;

	/**
	* IDriver::GetType - returns the type identifier of the driver
	* @return Type of the driver.
	*/
	virtual std::string GetType() = 0;

	/**
	* IDriver::GetVersion - returns the version identifiers of the driver
	* @param[out] nMajor - Major version.
	* @param[out] nMinor - Minor version.
	* @param[out] nMicro - Micro version.
	* @param[out] sBuild - Build identifier.
	*/
	virtual void GetVersion(LibMCDriver_CifX_uint32 & nMajor, LibMCDriver_CifX_uint32 & nMinor, LibMCDriver_CifX_uint32 & nMicro, std::string & sBuild) = 0;

	/**
	* IDriver::QueryParameters - Updates the driver parameters in the driver environment. Should only be called in the driver thread.
	*/
	virtual void QueryParameters() = 0;

	/**
	* IDriver::QueryParametersEx - Updates the driver parameters in the driver environment. Might be called out of thread. Implementation MUST be able to handle parallel calls.
	* @param[in] pDriverUpdateInstance - Status update instance.
	*/
	virtual void QueryParametersEx(LibMCEnv::PDriverStatusUpdateSession pDriverUpdateInstance) = 0;

};

typedef IBaseSharedPtr<IDriver> PIDriver;


/*************************************************************************************************************************
 Class interface for ChannelInformation 
**************************************************************************************************************************/

class IChannelInformation : public virtual IBase {
public:
	/**
	* IChannelInformation::GetBoardName - Returns the name of the board that it is connected to.
	* @return Board name.
	*/
	virtual std::string GetBoardName() = 0;

	/**
	* IChannelInformation::GetChannelIndex - Returns the channel index of the board that it is connected to.
	* @return Channel Index.
	*/
	virtual LibMCDriver_CifX_uint32 GetChannelIndex() = 0;

	/**
	* IChannelInformation::IsConnected - Returns if the driver is connected and updates are being received.
	* @return The channel is connected.
	*/
	virtual bool IsConnected() = 0;

	/**
	* IChannelInformation::GetMillisecondsSinceLastUpdate - Returns how many milliseconds ago the last channel update was received.
	* @return Returns 0, if no update has ever been received or channel is not connected.
	*/
	virtual LibMCDriver_CifX_uint32 GetMillisecondsSinceLastUpdate() = 0;

	/**
	* IChannelInformation::GetConnectionStatistics - Returns connection statistics for this channel.
	* @param[out] nNumberOfSucceededUpdates - Returns number of successful state updates.
	* @param[out] nNumberOfUpdateErrors - Returns number of update errors.
	* @param[out] dMinimumUpdateDurationInMs - Returns minium update duration in milliseconds.
	* @param[out] dMaximumUpdateDurationInMs - Returns maximum update duration in milliseconds.
	* @param[out] dAverageUpdateDurationInMs - Returns average update duration in milliseconds.
	* @param[out] dUpdateDurationVarianceInMs - Returns the variance of update durations in milliseconds.
	*/
	virtual void GetConnectionStatistics(LibMCDriver_CifX_uint32 & nNumberOfSucceededUpdates, LibMCDriver_CifX_uint32 & nNumberOfUpdateErrors, LibMCDriver_CifX_double & dMinimumUpdateDurationInMs, LibMCDriver_CifX_double & dMaximumUpdateDurationInMs, LibMCDriver_CifX_double & dAverageUpdateDurationInMs, LibMCDriver_CifX_double & dUpdateDurationVarianceInMs) = 0;

	/**
	* IChannelInformation::ValueExists - Returns if a value exists in this channel.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @return Returns if a value exist.
	*/
	virtual bool ValueExists(const std::string & sName) = 0;

	/**
	* IChannelInformation::GetValueType - Returns the type of a value. Fails if value does not exist in this channel.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @param[out] eValueType - Type of value.
	* @param[out] bIsInput - Returns true if value is an input value.
	* @param[out] bIsOutput - Returns true if value is an output value.
	*/
	virtual void GetValueType(const std::string & sName, LibMCDriver_CifX::eValueType & eValueType, bool & bIsInput, bool & bIsOutput) = 0;

	/**
	* IChannelInformation::GetIntegerValueRange - Returns the possible range of an integer value.
	* @param[in] sName - Name of value. Call fails if value does not exist in this channel.
	* @param[out] nMinValue - Minimum integer value this variable can hold. Returns 0 if variable is of float type.
	* @param[out] nMaxValue - Maximum integer value this variable can hold. Returns 0 if variable is of float type.
	*/
	virtual void GetIntegerValueRange(const std::string & sName, LibMCDriver_CifX_int64 & nMinValue, LibMCDriver_CifX_int64 & nMaxValue) = 0;

	/**
	* IChannelInformation::GetInputValueCount - Returns number of input variables on this channel.
	* @return Number of input variables.
	*/
	virtual LibMCDriver_CifX_uint32 GetInputValueCount() = 0;

	/**
	* IChannelInformation::GetInputValueName - Returns the name of an input variable on this channel.
	* @param[in] nIndex - Index of input variable. 0-based. Fails if larger or equal than the count.
	* @return Name of value.
	*/
	virtual std::string GetInputValueName(const LibMCDriver_CifX_uint32 nIndex) = 0;

	/**
	* IChannelInformation::GetOutputValueCount - Returns number of output variables on this channel.
	* @return Number of input variables.
	*/
	virtual LibMCDriver_CifX_uint32 GetOutputValueCount() = 0;

	/**
	* IChannelInformation::GetOutputValueName - Returns the name of an output variable on this channel.
	* @param[in] nIndex - Index of output variable. 0-based. Fails if larger or equal than the count.
	* @return Name of value.
	*/
	virtual std::string GetOutputValueName(const LibMCDriver_CifX_uint32 nIndex) = 0;

};

typedef IBaseSharedPtr<IChannelInformation> PIChannelInformation;


/*************************************************************************************************************************
 Class interface for Driver_CifX 
**************************************************************************************************************************/

class IDriver_CifX : public virtual IDriver {
public:
	/**
	* IDriver_CifX::SetToSimulationMode - Turns the driver into a simulation mode.
	*/
	virtual void SetToSimulationMode() = 0;

	/**
	* IDriver_CifX::IsSimulationMode - Returns if the driver is in simulation mode.
	* @return Flag if driver is in simulation mode.
	*/
	virtual bool IsSimulationMode() = 0;

	/**
	* IDriver_CifX::SetCustomSDKResource - Sets the machine resource name of the cifX SDK to load. MUST be called before Connect or it has no effect.
	* @param[in] sResourceName - Resource name of core machine package. Empty means standard naming applies.
	*/
	virtual void SetCustomSDKResource(const std::string & sResourceName) = 0;

	/**
	* IDriver_CifX::GetChannelCount - Returns the number of configured channels.
	* @return Returns the number of channels.
	*/
	virtual LibMCDriver_CifX_uint32 GetChannelCount() = 0;

	/**
	* IDriver_CifX::GetChannelInformation - Returns the channel information by index.
	* @param[in] nChannelIndex - Index of the board. MUST be between 0 and GetBoardCount - 1.
	* @return Channel Information Instance.
	*/
	virtual IChannelInformation * GetChannelInformation(const LibMCDriver_CifX_uint32 nChannelIndex) = 0;

	/**
	* IDriver_CifX::Connect - Connects to a cifX board by configuration.
	*/
	virtual void Connect() = 0;

	/**
	* IDriver_CifX::Disconnect - Disconnects from cifX board.
	*/
	virtual void Disconnect() = 0;

	/**
	* IDriver_CifX::Reconnect - Reconnects to the cifX board.
	*/
	virtual void Reconnect() = 0;

	/**
	* IDriver_CifX::IsConnected - Returns if the driver is connected.
	* @return All selected boards are connected.
	*/
	virtual bool IsConnected() = 0;

	/**
	* IDriver_CifX::ValueExists - Returns if a value exists.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @return Returns if a value exist.
	*/
	virtual bool ValueExists(const std::string & sName) = 0;

	/**
	* IDriver_CifX::GetValueType - Returns the type of a value. Fails if value does not exist.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @param[out] eValueType - Type of value.
	* @param[out] bIsInput - Returns true if value is an input value.
	* @param[out] bIsOutput - Returns true if value is an output value.
	*/
	virtual void GetValueType(const std::string & sName, LibMCDriver_CifX::eValueType & eValueType, bool & bIsInput, bool & bIsOutput) = 0;

	/**
	* IDriver_CifX::GetIntegerValueRange - Returns the possible range of an integer value.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @param[out] nMinValue - Minimum integer value this variable can hold. Returns 0 if variable is of float type.
	* @param[out] nMaxValue - Maximum integer value this variable can hold. Returns 0 if variable is of float type.
	*/
	virtual void GetIntegerValueRange(const std::string & sName, LibMCDriver_CifX_int64 & nMinValue, LibMCDriver_CifX_int64 & nMaxValue) = 0;

	/**
	* IDriver_CifX::WriteIntegerValue - Writes an output integer value. Value MUST be within the bit-range of the value type defined by the configuration.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @param[in] nValue - Value to set. The named value MUST be of type integer or boolean. If value is of boolean type, 0 means false and every other value means true.
	* @param[in] bClampToRange - If Integer value is outside of the permissible range, should they be clamped the value to the boundaries (ClampToRange is true) or an error raised (ClampToRange is false).
	* @param[in] nTimeOutInMs - If Timeout is larger than 0, the call waits until the end point has acknowledged that the new value has been set. If timeout is 0, the call returns immediately, even if the end point might not have changed the value yet.
	*/
	virtual void WriteIntegerValue(const std::string & sName, const LibMCDriver_CifX_int64 nValue, const bool bClampToRange, const LibMCDriver_CifX_uint32 nTimeOutInMs) = 0;

	/**
	* IDriver_CifX::WriteBoolValue - Writes an output boolean value.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @param[in] bValue - Value to set. The named value MUST be of type boolean.
	* @param[in] nTimeOutInMs - If Timeout is larger than 0, the call waits until the end point has acknowledged that the new value has been set. If timeout is 0, the call returns immediately, even if the end point might not have changed the value yet.
	*/
	virtual void WriteBoolValue(const std::string & sName, const bool bValue, const LibMCDriver_CifX_uint32 nTimeOutInMs) = 0;

	/**
	* IDriver_CifX::WriteDoubleValue - Writes an output float value. Accuracy will be determined by the bit-range of the value defined by the configuration.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @param[in] dValue - Value to set. The named value MUST be of type double or float.
	* @param[in] nTimeOutInMs - If Timeout is larger than 0, the call waits until the end point has acknowledged that the new value has been set. If timeout is 0, the call returns immediately, even if the end point might not have changed the value yet.
	*/
	virtual void WriteDoubleValue(const std::string & sName, const LibMCDriver_CifX_double dValue, const LibMCDriver_CifX_uint32 nTimeOutInMs) = 0;

	/**
	* IDriver_CifX::ReadIntegerValue - Reads an input integer value.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @return Value that was read.
	*/
	virtual LibMCDriver_CifX_int64 ReadIntegerValue(const std::string & sName) = 0;

	/**
	* IDriver_CifX::ReadBoolValue - Reads an bool integer value.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @return Value that was read.
	*/
	virtual bool ReadBoolValue(const std::string & sName) = 0;

	/**
	* IDriver_CifX::ReadDoubleValue - Reads an input float value.
	* @param[in] sName - Name of value. Call fails if value does not exist.
	* @return Value that was read.
	*/
	virtual LibMCDriver_CifX_double ReadDoubleValue(const std::string & sName) = 0;

};

typedef IBaseSharedPtr<IDriver_CifX> PIDriver_CifX;


/*************************************************************************************************************************
 Global functions declarations
**************************************************************************************************************************/
class CWrapper {
public:
	// Injected Components
	static LibMCEnv::PWrapper sPLibMCEnvWrapper;

	/**
	* Ilibmcdriver_cifx::GetVersion - retrieves the binary version of this library.
	* @param[out] nMajor - returns the major version of this library
	* @param[out] nMinor - returns the minor version of this library
	* @param[out] nMicro - returns the micro version of this library
	*/
	static void GetVersion(LibMCDriver_CifX_uint32 & nMajor, LibMCDriver_CifX_uint32 & nMinor, LibMCDriver_CifX_uint32 & nMicro);

	/**
	* Ilibmcdriver_cifx::GetLastError - Returns the last error recorded on this object
	* @param[in] pInstance - Instance Handle
	* @param[out] sErrorMessage - Message of the last error
	* @return Is there a last error to query
	*/
	static bool GetLastError(IBase* pInstance, std::string & sErrorMessage);

	/**
	* Ilibmcdriver_cifx::ReleaseInstance - Releases shared ownership of an Instance
	* @param[in] pInstance - Instance Handle
	*/
	static void ReleaseInstance(IBase* pInstance);

	/**
	* Ilibmcdriver_cifx::AcquireInstance - Acquires shared ownership of an Instance
	* @param[in] pInstance - Instance Handle
	*/
	static void AcquireInstance(IBase* pInstance);

	/**
	* Ilibmcdriver_cifx::CreateDriver - Creates a driver instance with a specific name.
	* @param[in] sName - Name of driver to be created.
	* @param[in] sType - Type of driver to be created.
	* @param[in] pDriverEnvironment - Environment of this driver.
	* @return New Driver instance
	*/
	static IDriver * CreateDriver(const std::string & sName, const std::string & sType, LibMCEnv::PDriverEnvironment pDriverEnvironment);

};

LibMCDriver_CifXResult LibMCDriver_CifX_GetProcAddress (const char * pProcName, void ** ppProcAddress);

} // namespace Impl
} // namespace LibMCDriver_CifX

#endif // __LIBMCDRIVER_CIFX_CPPINTERFACES