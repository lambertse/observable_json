#pragma once
#include <unordered_map>
#include <memory>

namespace observable_json {
using JNodePtr = std::shared_ptr<class JsonNode>;
class JsonNode {
 public:
  JsonNode() = default;
  JsonNode(const JsonNode&) = default;
  JsonNode(JsonNode&&) = default;
  JsonNode& operator=(const JsonNode&) = default;
  JsonNode& operator=(JsonNode&&) = default;
  virtual ~JsonNode() = default;

private:
  JNodePtr parent_ = nullptr;
  std::unordered_map<std::string, JNodePtr> children_;
};
}
