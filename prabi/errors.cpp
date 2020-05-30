#define _CRT_SECURE_NO_WARNINGS
#include "errors.h"

std::string MakeErrorDesc(const char* desc, int errorCode)
{
	return std::string(desc) + '-' + strerror(errorCode);
}
