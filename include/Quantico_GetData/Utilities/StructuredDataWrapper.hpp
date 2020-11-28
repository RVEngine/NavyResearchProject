#pragma once

#include <StructuredDataAPI.h>
#include <string>
#include <vector>

/// Convenience wrappers over the C API of StructuredData

struct Nil {};
struct CollectionStart {};
struct CollectionEnd {};

APIResult Store(const StructuredDataAPI_v1* api, Nil, char* buffer, int32_t& buffer_size);
APIResult Store(const StructuredDataAPI_v1* api, bool value, char* buffer, int32_t& buffer_size);
APIResult Store(const StructuredDataAPI_v1* api, double value, char* buffer, int32_t& buffer_size);
APIResult Store(const StructuredDataAPI_v1* api, const char* value, char* buffer, int32_t& buffer_size);
APIResult Store(const StructuredDataAPI_v1* api, const Vector3f64_v3& value, char* buffer, int32_t& buffer_size);
APIResult Store(const StructuredDataAPI_v1* api, const ObjectHandle_v3& value, char* buffer, int32_t& buffer_size);
APIResult Store(const StructuredDataAPI_v1* api, CollectionStart, char* buffer, int32_t& buffer_size);
APIResult Store(const StructuredDataAPI_v1* api, CollectionEnd, char* buffer, int32_t& buffer_size);

APIResult Read(const StructuredDataAPI_v1* api, bool& value, const char* buffer, int32_t bufferSize);
APIResult Read(const StructuredDataAPI_v1* api, double& value, const char* buffer, int32_t bufferSize);
APIResult Read(const StructuredDataAPI_v1* api, std::string& value, const char* buffer, int32_t bufferSize);
APIResult Read(const StructuredDataAPI_v1* api, std::vector<char>& value, const char* buffer, int32_t bufferSize);
APIResult Read(const StructuredDataAPI_v1* api, Vector3f64_v3& value, const char* buffer, int32_t bufferSize);
APIResult Read(const StructuredDataAPI_v1* api, ObjectHandle_v3& value, const char* buffer, int32_t bufferSize);

int32_t GetItemSize(const StructuredDataAPI_v1* api, const char* buffer, int32_t bufferSize);
StructuredDataItemType_v1 GetItemType(const StructuredDataAPI_v1* api, const char* buffer, int32_t bufferSize);

/// Writes data into a binary buffer using StructuredDataAPI, and used to encapsulate the low-level details of writing StructuredData.
struct BufferWriter
{
  explicit BufferWriter(const StructuredDataAPI_v1* api) :
      api(api)
    , bytesWritten(0)
  {
    buffer = std::vector<char>(64, 0);
  }

  template <typename T>
  void operator()(const T& value)
  {
    auto size = static_cast<int32_t>(buffer.size()) - bytesWritten;
    /// Try to write the value into the buffer. If there isn't enough space, grow the buffer and try again
    if (Store(api, value, buffer.data() + bytesWritten, size) == kAPIResult_PartialSuccess)
    {
      buffer.resize(max(bytesWritten + size, static_cast<int32_t>(buffer.size()) * 2));
      Store(api, value, buffer.data() + bytesWritten, size);
    }
    bytesWritten += size;
  }

  /// Append entire content of \a value. Expects \a value to contain valid StructuredData
  void operator()(const std::vector<char> & value);

  /// Returns the written buffer and resets it.
  std::vector<char> Result();

  const StructuredDataAPI_v1* api;
  std::vector<char> buffer;
  int32_t bytesWritten;
};

/// Reads data from a binary buffer using StructuredDataAPI
struct BufferReader
{
  BufferReader(const StructuredDataAPI_v1* api, const char* buffer, int32_t size)
    : api(api)
    , buffer(buffer)
    , bytesRemaining(size)
  {
  }

  template <typename T>
  APIResult operator()(T& value)
  {
    const auto result = Read(api, value, buffer, bytesRemaining);
    if (!APIRESULT_SUCCESS(result))
      return result;

    const auto size = GetItemSize(api, buffer, bytesRemaining);
    buffer += size;
    bytesRemaining -= size;
    return result;
  }

  /// Returns the remaining unread buffer
  std::vector<char> Buffer();

  const StructuredDataAPI_v1* api;
  const char* buffer;
  int32_t bytesRemaining;
};