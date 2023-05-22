#include "StringConverter.h"

namespace StringConverter
{
	std::wstring stringConverter(std::string_view str)	//converts string to wide_string
	{
		std::wstring wstring(str.begin(), str.end());	
		return wstring;
	}

}