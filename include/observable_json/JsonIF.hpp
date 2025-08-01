#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace observable_json {

class JsonIF;
using JsonIFPtr = std::shared_ptr<JsonIF>;
using JsonObject = std::map<std::string, JsonIFPtr>;
using JsonArray = std::vector<JsonIFPtr>;
enum class JsonType { NUL = 0, INTEGER, DOUBLE, STRING, BOOL, OBJECT, ARRAY };

class JsonIF {
 public:
  JsonIF() = default;
  virtual ~JsonIF() = default;

  JsonIF(const JsonIF &) = delete;
  JsonIF(JsonIF &&) = delete;
  virtual JsonIF &operator=(const JsonIF &) = delete;
  virtual JsonIF &operator=(JsonIF &&) = delete;

  JsonIF(const int &value);
  JsonIF(const double &value);
  JsonIF(const std::string &value);
  JsonIF(const bool &value);
  JsonIF(const JsonObject &value);
  JsonIF(const JsonArray &value);

  virtual JsonIF &operator=(const int &value) = 0;
  virtual JsonIF &operator=(const double &value) = 0;
  virtual JsonIF &operator=(const std::string &value) = 0;
  virtual JsonIF &operator=(const bool &value) = 0;
  virtual JsonIF &operator=(const JsonObject &value) = 0;
  virtual JsonIF &operator=(const JsonArray &value) = 0;
  virtual JsonIF &operator=(const std::nullptr_t &value) = 0;

  virtual JsonIF &operator[](const std::string &key) = 0;
  virtual const JsonIF &operator[](const std::string &key) const = 0;
  // virtual std::unique_ptr<JsonIF> clone() const = 0;
  //
  virtual std::string string_value() const = 0;
  virtual int int_value() const = 0;
  virtual double double_value() const = 0;
  virtual bool bool_value() const = 0;
  virtual JsonObject &object_value() = 0;
  virtual JsonArray &array_value() = 0;

  virtual bool is_null() const = 0;
  virtual bool is_array() const = 0;
  virtual bool is_object() const = 0;

  virtual void clear() = 0;
  virtual size_t size() const = 0;
  virtual void remove(const std::string &key) = 0;
};
}  // namespace observable_json
