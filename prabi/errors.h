#pragma once
#include <string>

std::string MakeErrorDesc(const char* desc, int errorCode);

#define MAKE_ERROR(stmt,code) MakeErrorDesc(stmt,code).data()

#define MAKE_ERRNO(stmt) MAKE_ERROR(stmt,errno)