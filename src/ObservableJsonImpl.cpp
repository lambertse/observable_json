#include "ObservableJsonImpl.h"

namespace observable_json {
ObservableJsonImpl::ObservableJsonImpl() : root_(std::make_shared<JsonNode>()) {}
ObservableJsonImpl::~ObservableJsonImpl() = default;

}
