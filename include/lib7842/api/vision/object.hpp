#pragma once
#include "pros/vision.h"
#include "query.hpp"

namespace lib7842::Vision {

class Object {
public:
  Object() = default;
  explicit Object(const pros::vision_object& iobject);

  friend class Query;
  double get(const Query& iquery) const;

  uint16_t sig {0};
  double x {0};
  double y {0};
  double width {0};
  double height {0};
};

} // namespace lib7842::Vision
