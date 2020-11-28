#include "Utilities/StructuredDataWrapper.hpp"

#include "Utilities/Utilitiy.h"

APIResult Store(const StructuredDataAPI_v1* api, Nil, char* buffer, int32_t& buffer_size)
{
  return api->StoreNil(buffer, &buffer_size);
}

APIResult Store(const StructuredDataAPI_v1* api, bool value, char* buffer, int32_t& buffer_size)
{
  return api->StoreBool32(static_cast<bool32_t>(value), buffer, &buffer_size);
}

APIResult Store(const StructuredDataAPI_v1* api, double value, char* buffer, int32_t& buffer_size)
{
  return api->StoreFloat64(static_cast<float64_t>(value), buffer, &buffer_size);
}

APIResult Store(const StructuredDataAPI_v1* api, const char* value, char* buffer, int32_t& buffer_size)
{
  return api->StoreString(value, buffer, &buffer_size);
}

APIResult Store(const StructuredDataAPI_v1* api, const Vector3f64_v3& value, char* buffer, int32_t& buffer_size)
{
  return api->StoreVector3f64(value, buffer, &buffer_size);
}

APIResult Store(const StructuredDataAPI_v1* api, const ObjectHandle_v3& value, char* buffer, int32_t& buffer_size)
{
  return api->StoreObjectHandle(value, buffer, &buffer_size);
}

APIResult Store(const StructuredDataAPI_v1* api, CollectionStart, char* buffer, int32_t& buffer_size)
{
  return api->StoreCollectionStart(buffer, &buffer_size);
}

APIResult Store(const StructuredDataAPI_v1* api, CollectionEnd, char* buffer, int32_t& buffer_size)
{
  return api->StoreCollectionEnd(buffer, &buffer_size);
}

APIResult Read(const StructuredDataAPI_v1* api, bool& value, const char* buffer, int32_t bufferSize)
{
  bool32_t convertedValue = value;
  const auto result = api->ReadBool32(buffer, bufferSize, &convertedValue);
  value = convertedValue != FALSE;
  return result;
}

APIResult Read(const StructuredDataAPI_v1* api, double& value, const char* buffer, int32_t bufferSize)
{
  return api->ReadFloat64(buffer, bufferSize, &value);
}

APIResult Read(const StructuredDataAPI_v1* api, std::string& value, const char* buffer, int32_t bufferSize)
{
  int32_t size = 0;
  auto result = api->ReadString(buffer, bufferSize, nullptr, &size);
  if (!APIRESULT_SUCCESS(result))
    return result;

  value.resize(size);
  result = api->ReadString(buffer, bufferSize, &value[0], &size);
  value.pop_back();

  return result;
}

APIResult Read(const StructuredDataAPI_v1* api, std::vector<char>& value, const char* buffer, int32_t bufferSize)
{
  int32_t size = 0;
  auto result = api->ReadString(buffer, bufferSize, nullptr, &size);
  if (!APIRESULT_SUCCESS(result))
    return result;

  value.resize(size);
  result = api->ReadString(buffer, bufferSize, value.data(), &size);
  return result;
}

APIResult Read(const StructuredDataAPI_v1* api, Vector3f64_v3& value, const char* buffer, int32_t bufferSize)
{
  return api->ReadVector3f64(buffer, bufferSize, &value);
}

APIResult Read(const StructuredDataAPI_v1* api, ObjectHandle_v3& value, const char* buffer, int32_t bufferSize)
{
  return api->ReadObjectHandle(buffer, bufferSize, &value);
}

int32_t GetItemSize(const StructuredDataAPI_v1* api, const char* buffer, int32_t bufferSize)
{
  SDKCheck(api->GetItemSize(buffer, &bufferSize));
  return bufferSize;
}

StructuredDataItemType_v1 GetItemType(const StructuredDataAPI_v1* api, const char* buffer, int32_t bufferSize)
{
  auto type = kStructuredDataItemType_Nil;
  SDKCheck(api->GetItemType(buffer, bufferSize, &type));
  return type;
}

void BufferWriter::operator()(const std::vector<char> & value)
{
  buffer.resize(bytesWritten);
  buffer.insert(buffer.end(), value.begin(), value.end());
  bytesWritten += static_cast<int32_t>(value.size());
}

std::vector<char> BufferWriter::Result()
{
  buffer.resize(bytesWritten);
  std::vector<char> result = std::move(buffer);
  *this = BufferWriter(api);
  return result;
}

std::vector<char> BufferReader::Buffer()
{
  return std::vector<char>(buffer, buffer + bytesRemaining);
}
