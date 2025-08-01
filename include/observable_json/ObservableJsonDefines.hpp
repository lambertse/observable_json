#pragma once

#include "ObservableJson.h"
namespace observable_json {
using ObservableJson11 =
    ObservableJson<class Json11Compat,
                   std::enable_if_t<is_json_type_v<class Json11Compat>>>;
}
