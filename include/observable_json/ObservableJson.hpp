#pragma once

#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "JsonIF.hpp"

namespace observable_json {

// Define the type trait
template <typename T>
struct is_json_type : std::false_type {};

// Specialize for your specific JsonIF types
// You'll need to add specializations for your actual JSON interface types
template <>
struct is_json_type<class JsonIF> : std::true_type {};

template <typename T>
constexpr bool is_json_type_v = is_json_type<T>::value;

// Forward declare the template class for type aliases
template <class JsonIF, typename = std::enable_if_t<is_json_type_v<JsonIF>>>
class ObservableJson;

// Type aliases
template <class JsonBase>
using ObservableJsonPtr = std::shared_ptr<ObservableJson<JsonBase>>;

using NodePathPtr = std::shared_ptr<std::vector<std::string>>;

// Forward declare for callback
template <class JsonBase>
using ChangeCallback = std::function<void(const ObservableJson<JsonBase>&)>;

template <class JsonBase, typename>
class ObservableJson {
 public:
  // Constructors (removed override keyword)
  ObservableJson(JsonType type = JsonType::NUL) {
    switch (type) {
      case JsonType::NUL:
        json_ = nullptr;
        break;
      case JsonType::INTEGER:
        json_ = 0;
        break;
      case JsonType::DOUBLE:
        json_ = 0.0;
        break;
      case JsonType::STRING:
        json_ = std::string();
        break;
      case JsonType::BOOL:
        json_ = false;
        break;
      case JsonType::OBJECT:
        json_ = JsonObject();
        break;
      case JsonType::ARRAY:
        json_ = JsonArray();
        break;
      default:
        throw std::invalid_argument("Invalid JsonType provided");
    }
  }

  virtual ~ObservableJson() = default;

  // Value constructors
  template <typename T>
    requires std::is_same_v<T, int> || std::is_same_v<T, double> ||
             std::is_same_v<T, std::string> || std::is_same_v<T, bool> ||
             std::is_same_v<T, JsonObject> || std::is_same_v<T, JsonArray> ||
             std::is_same_v<T, std::nullptr_t>
  ObservableJson(const T& value) {
    json_ = std::forward<T>(value);
    notify_observers();
  }

  // Assignment operators (removed override keyword)
  template <typename T>
    requires std::is_same_v<T, int> || std::is_same_v<T, double> ||
             std::is_same_v<T, std::string> || std::is_same_v<T, bool> ||
             std::is_same_v<T, JsonObject> || std::is_same_v<T, JsonArray> ||
             std::is_same_v<T, std::nullptr_t>
  ObservableJson& operator=(T&& value) {
    json_ = std::forward<T>(value);
    notify_observers();
    return *this;
  }

  // Indexing operators (removed override keyword)
  ObservableJson& operator[](const std::string& key) {
    if (json_->is_object()) {
      auto& obj = json_->object_value();
      if (obj.find(key) == obj.end()) {
        obj[key] = std::make_shared<ObservableJson<JsonBase>>();
      }
      return *obj[key];
    } else {
      throw std::runtime_error("Cannot index into a non-object JSON type");
    }
  }

  const ObservableJson& operator[](const std::string& key) const {
    if (json_->is_object()) {
      const auto& obj = json_->object_value();
      auto it = obj.find(key);
      if (it != obj.end()) {
        return *it->second;
      } else {
        throw std::runtime_error("Key not found in JSON object");
      }
    } else {
      throw std::runtime_error("Cannot index into a non-object JSON type");
    }
  }

  ObservableJson& operator[](size_t index) {
    if (json_->is_array()) {
      auto& arr = json_->array_value();
      if (index >= arr.size()) {
        throw std::out_of_range("Index out of bounds for JSON array");
      }
      return *arr[index];
    } else {
      throw std::runtime_error("Cannot index into a non-array JSON type");
    }
  }

  const ObservableJson& operator[](size_t index) const {
    if (json_->is_array()) {
      const auto& arr = json_->array_value();
      if (index >= arr.size()) {
        throw std::out_of_range("Index out of bounds for JSON array");
      }
      return *arr[index];
    } else {
      throw std::runtime_error("Cannot index into a non-array JSON type");
    }
  }

  // Value getters
  std::string string_value() const;
  int int_value() const;
  double double_value() const;
  bool bool_value() const;
  JsonObject& object_value();
  JsonArray& array_value();

  // Type checking
  bool is_null() const { return json_->is_null(); }
  bool is_array() const { return json_->is_array(); }
  bool is_object() const { return json_->is_object(); }

  // Container operations
  void clear() {
    json_->clear();
    notify_observers();
  }
  size_t size() const { return json_->size(); }
  void remove(const std::string& key) {
    json_->remove(key);
    notify_observers();
  }

  // ObservableJson specific methods
  bool connect(const std::string& path, const ChangeCallback<JsonBase>& cb) {}

 private:
  bool connect(NodePathPtr path, const ChangeCallback<JsonBase>& cb);
  bool notify_observers() {
    for (const auto& callback : callbacks_) {
      callback();
    }
    if (parent_) {
      parent_->notify_observers();
    }
  }

 private:
  std::unique_ptr<JsonBase> json_;
  std::unordered_map<std::string, ObservableJsonPtr<JsonBase>> children_;

  ObservableJsonPtr<JsonBase> parent_;
  std::vector<ChangeCallback<JsonBase>> callbacks_;
};

}  // namespace observable_json
