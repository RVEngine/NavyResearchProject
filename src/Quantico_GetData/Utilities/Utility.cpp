#include "Utilities/Utilitiy.h"

namespace SDKUtility
{

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

std::string UnifyFilepathSlashes(std::string filepath)
{
  std::string::size_type pos = 0u;
  while ((pos = filepath.find("/", pos)) != std::string::npos)
  {
    filepath.replace(pos, 1, "\\");
    ++pos;
  }

  return filepath;
}

} // namespace SDKUtility
