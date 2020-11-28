#pragma once

#include "Gears.h"

#include <cstdarg>

#ifdef _DEBUG
#define SDKCheck(function) \
  [&]()->APIResult { \
    APIResult assert_res = (function); \
    if (!APIRESULT_SUCCESS(assert_res)) \
    { \
      SDKUtility::LogMessage(kSeverityLevel_Error, __FUNCTION__ "%s (Returned %d)", #function, static_cast<int>(assert_res)); \
    } \
    assert(APIRESULT_SUCCESS(assert_res)); \
    return assert_res; \
  }()
#else
#define SDKCheck(function) \
  [&]()->APIResult { \
    APIResult assert_res = (function); \
    if (!APIRESULT_SUCCESS(assert_res)) \
    { \
      SDKUtility::LogMessage(kSeverityLevel_Error, __FUNCTION__ "%s (Returned %d)", #function, static_cast<int>(assert_res)); \
    } \
    return assert_res; \
  }()
#endif

namespace SDKUtility
{

void LogMessage(const SeverityLevel_v1 severity, const char* message, std::va_list args);
void LogMessage(const SeverityLevel_v1 severity, const char* message, ...);

std::string UnifyFilepathSlashes(std::string filepath);

} // namespace SDKUtility
