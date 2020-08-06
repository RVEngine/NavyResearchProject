#pragma once
#include "Gears.h"

#include <cstdarg>

#ifdef _DEBUG
#define SDKCheck(function) \
  [&]()->APIResult { \
    APIResult assert_res = (function); \
    if (!APIRESULT_SUCCESS(assert_res)) \
    { \
      LogMessage(kSeverityLevel_Error, __FUNCTION__ "%s (Returned %d)", #function, static_cast<int>(assert_res)); \
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
      LogMessage(kSeverityLevel_Error, __FUNCTION__ "%s (Returned %d)", #function, static_cast<int>(assert_res)); \
    } \
    return assert_res; \
  }()
#endif

/**
* Wrapper functionality for logging a message with the LogAPI.
*/

void LogMessage(const SeverityLevel_v1 severity, const char* message, std::va_list args)
{
    const auto buf_size = std::vsnprintf(nullptr, 0U, message, args);
    std::string buffer(buf_size, '\0');

    std::vsnprintf(&*std::begin(buffer), buf_size + 1, message, args);

    switch (severity)
    {
    case kSeverityLevel_Critical:
        Gears::API::LogAPIv1()->LogCritical(Gears::API::LogAPIv1(), std::data(buffer));
        break;
    case kSeverityLevel_Error:
        Gears::API::LogAPIv1()->LogError(Gears::API::LogAPIv1(), std::data(buffer));
        break;
    case kSeverityLevel_Warning:
        Gears::API::LogAPIv1()->LogWarning(Gears::API::LogAPIv1(), std::data(buffer));
        break;
    case kSeverityLevel_Info:
        Gears::API::LogAPIv1()->LogInfo(Gears::API::LogAPIv1(), std::data(buffer));
        break;
    case kSeverityLevel_Debug:
        Gears::API::LogAPIv1()->LogDebug(Gears::API::LogAPIv1(), std::data(buffer));
        break;
    default:
        break;
    };
}

void LogMessage(const SeverityLevel_v1 severity, const char* message, ...)
{
    std::va_list args;

    va_start(args, message);
    LogMessage(severity, message, args);
    va_end(args);
}
