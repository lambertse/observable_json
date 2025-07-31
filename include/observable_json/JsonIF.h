#pragma once

#include <memory>
#include <string>

namespace observable_json {
template <typename KeyType = std::string>
class JsonInterface {
 public:
  JsonInterface();
  virtual ~JsonInterface() = default;

  virtual KeyType string_value(const KeyType &key) = 0;
  virtual int int_value(const KeyType &key) = 0;
  virtual double double_value(const KeyType &key) = 0;
  virtual bool bool_value(const KeyType &key) = 0;
  virtual std::shared_ptr<JsonInterface> object_value(const KeyType &key) = 0;
};
}  // namespace observable_json
