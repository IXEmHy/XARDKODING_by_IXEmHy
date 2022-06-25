#include "string_operators.h"

//   string     //
///  operators  ///
std::string operator*(const std::string& str,                     
	const uint32_t& num) {
	return num > 0 ? str + operator*(str, num - 1) : "";
}

std::string operator*(const uint32_t& num,                        
	const std::string& str)	{
	return operator*(str, num);
}

std::string& operator/(std::string& str,                          
	const std::string& str2) {
	return str.find(str2) != str.npos ?
		operator/(str.erase(str.find(str2), str2.length()), str2)
		: str;
}

std::string& operator-(std::string& str,                          
	const std::string& str2) {
	return str.find(str2) != str.npos ?
		str.erase(str.find(str2), str2.length())
		: str;
}


bool operator==(const std::string& str, const std::string& str2) {
	return str.size() == str2.size() && str.find(str2) != str.npos;
}

bool operator!=(const std::string& str, const std::string& str2) {
	return !operator==(str, str2);
}

// function //
size_t strlen_t(const char* str, size_t len = 0) {
	return str[len] != '\0' ? strlen_t(str, len + 1) : len;
}

