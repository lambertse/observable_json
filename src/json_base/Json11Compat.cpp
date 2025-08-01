#include "Json11Compat.hpp"

namespace observable_json {

JsonIF& Json11Compat::operator=(const JsonArray& value) {
  // TBD
}

JsonIF& Json11Compat::operator=(const std::nullptr_t&) {
  // TBD
}

JsonIF& Json11Compat::operator[](const std::string& key) {
  return *(new Json11Compat(json_[key]));
}

const JsonIF& Json11Compat::operator[](const std::string& key) const {
  return *(new Json11Compat(json_[key]));
}

std::string Json11Compat::string_value() const { return json_.dump(); }

int Json11Compat::int_value() const { return json_.int_value(); }

double Json11Compat::double_value() const { return json_.number_value(); }

bool Json11Compat::bool_value() const { return json_.bool_value(); }

JsonObject& Json11Compat::object_value() {
  // This is a stub. You should implement conversion if needed.
  throw std::runtime_error("object_value() not implemented for Json11Compat");
}

JsonArray& Json11Compat::array_value() {
  if (json_.is_array()) {
    // This is a stub. You should implement conversion if needed.
    throw std::runtime_error("array_value() not implemented for Json11Compat");
  }
  throw std::runtime_error("Not an array type");
}

bool Json11Compat::is_null() const { return json_.is_null(); }

bool Json11Compat::is_array() const { return json_.is_array(); }

bool Json11Compat::is_object() const { return json_.is_object(); }

void Json11Compat::clear() { json_.clear(); }

}  // namespace observable_json
