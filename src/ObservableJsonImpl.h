#pragma once 
#include "JsonNode.h"

namespace observable_json {
class ObservableJsonImpl {
 public:
  ObservableJsonImpl();
  ObservableJsonImpl(const ObservableJsonImpl&);
  ObservableJsonImpl(ObservableJsonImpl&&);
  ObservableJsonImpl& operator=(const ObservableJsonImpl&);
  ObservableJsonImpl& operator=(ObservableJsonImpl&&);
  virtual ~ObservableJsonImpl();

private:
  JNodePtr root_;
};

}
