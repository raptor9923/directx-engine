#include "ErrorLogger.h"
#include <comdef.h>


namespace ErrorLogger   // functions for logging errors
{
	void errorLog(const std::string& message)								
	{												
		std::string error_message = "Error:\n" + message;										
		MessageBoxA(nullptr, error_message.c_str(), nullptr, MB_ICONERROR); 
	}

	void errorLog(HRESULT hresult, const std::string& message)																
	{
		_com_error error(hresult);																							
		std::wstring error_message = L"Error:\n" + StringConverter::stringConverter(message) + L'\n' + error.ErrorMessage(); 
		MessageBoxW(nullptr, error_message.c_str(), nullptr, MB_ICONERROR);													
	}

	void errorLog(HRESULT hresult, const std::wstring& message)																
	{
		_com_error error(hresult);																							
		std::wstring error_message = L"Error:\n" + message  + L'\n' + error.ErrorMessage(); 
		MessageBoxW(nullptr, error_message.c_str(), nullptr, MB_ICONERROR);													
	}
	void errorLog(COMException& exception)
	{
		std::wstring errorMsg = exception.GetMsg();
		MessageBoxW(nullptr, errorMsg.c_str(), L"ERROR", MB_ICONERROR);
	}
}