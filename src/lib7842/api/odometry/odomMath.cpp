#include "odomMath.hpp"

namespace lib7842 {

namespace OdomMath {

Vector closest(const Vector& current, const QAngle& heading, const Vector& target) {
  double headRad = heading.convert(radian);
  Vector n = Vector::normalize({sin(headRad) * meter, cos(headRad) * meter});
  Vector v = target - current;
  QArea d = Vector::dot(v, n);
  return current + (n * d.convert(meter2));
}

Vector closest(const State& state, const Vector& target) {
  return closest(state, state.theta, target);
}

QAngle rollAngle360(const QAngle& angle) {
  return angle - 360.0_deg * std::floor(angle.convert(degree) * (1.0 / 360.0));
}

QAngle rollAngle180(const QAngle& angle) {
  return angle - 360.0_deg * std::floor((angle.convert(degree) + 180.0) * (1.0 / 360.0));
}

QAngle rotateAngle90(const QAngle& angle) {
  QAngle iangle = rollAngle180(angle);
  if (iangle.abs() > 90_deg) {
    iangle += 180_deg;
    iangle = rollAngle180(iangle);
  }
  return iangle;
}

} // namespace OdomMath

} // namespace lib7842
