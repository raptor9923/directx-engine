#pragma once
#include<string>
#include<Windows.h>
#include"StringConverter.h"
#include"COMException.h"

namespace ErrorLogger
{
	void errorLog(const std::string&);			//logs error
	void errorLog(HRESULT,const std::string&);	//logs error with HRESULT
	void errorLog(HRESULT, const std::wstring&);
	void errorLog(COMException& exception);
}
