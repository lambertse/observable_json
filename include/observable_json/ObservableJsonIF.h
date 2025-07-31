#pragma once

#include <functional>
#include <string>
namespace observable_json {

class ObservableJsonIF;
using ChangeCallback =
    std::function<void(const ObservableJsonIF&, const ObservableJsonIF&)>;

class ObservableJsonIF {
 public:
  ObservableJsonIF() = default;
  ObservableJsonIF(const ObservableJsonIF&) = default;
  ObservableJsonIF(ObservableJsonIF&&) = default;
  ObservableJsonIF& operator=(const ObservableJsonIF&) = default;
  ObservableJsonIF& operator=(ObservableJsonIF&&) = default;
  virtual ~ObservableJsonIF() = default;

  virtual bool connect(const std::string& path, const ChangeCallback& cb) = 0;
};
}  // namespace observable_json
