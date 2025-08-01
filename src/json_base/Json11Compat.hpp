#pragma once

#include <json11.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "observable_json/JsonIF.hpp"

namespace observable_json {
namespace json = json11;

class Json11Compat : public JsonIF {
 public:
  template <typename T>
    requires std::is_same_v<T, int> || std::is_same_v<T, double> ||
             std::is_same_v<T, std::string> || std::is_same_v<T, bool> ||
             std::is_same_v<T, JsonObject> || std::is_same_v<T, JsonArray> ||
             std::is_same_v<T, std::nullptr_t>
  Json11Compat(const T& value) {
    json_ = std::forward<T>(value);
  }

  JsonIF& operator=(const JsonArray& value) override;
  JsonIF& operator=(const std::nullptr_t&) override;

  JsonIF& operator[](const std::string& key) override;
  const JsonIF& operator[](const std::string& key) const override;

  std::string string_value() const override;

  int int_value() const override;
  double double_value() const override;
  bool bool_value() const override;

  JsonObject& object_value() override;
  JsonArray& array_value() override;

  bool is_null() const override;
  bool is_array() const override;
  bool is_object() const override;
  void clear() override;

 private:
  json::Json json_;
};

}  // namespace observable_json
