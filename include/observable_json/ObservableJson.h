#include "ObservableJsonIF.h"

#include <memory>

namespace observable_json {
class ObservableJson : public ObservableJsonIF {
public:
    ObservableJson();
    virtual ~ObservableJson();

private:
  std::shared_ptr<class ObservableJsonImpl> impl_;
};
}
