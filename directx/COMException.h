#pragma once
#include <comdef.h>
#include "StringConverter.h"

#define COM_ERROR_IF_FAILED(hr,msg) if (FAILED(hr)) throw COMException(hr,msg,__FILE__, __FUNCTION__, __LINE__)

class COMException
{
	std::wstring m_msg;
public:
	COMException(HRESULT hr, const std::string& msg, const std::string& file, const std::string& function, int line)
	{
		_com_error error(hr);
		m_msg = L"Msg: " + StringConverter::stringConverter(msg) + L"\n";
		m_msg += error.ErrorMessage();
		m_msg += L"\nFile: " + StringConverter::stringConverter(file) + L"\n";
		m_msg += L"Function: " + StringConverter::stringConverter(function) + L"\n";
		m_msg += L"Line: " + StringConverter::stringConverter(std::to_string(line)) + L"\n";
	}
	const std::wstring& GetMsg()
	{
		return m_msg;
	}
};