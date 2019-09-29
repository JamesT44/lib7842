#include "pathSegment.hpp"

namespace lib7842 {

void PathSegment::addPoint(const PathPoint& ipoint) {
  segments.push_back(ipoint);
}

void PathSegment::addSegment(const PathSegment& isegment) {
  segments.push_back(isegment);
}

void PathSegment::addPoints(const std::vector<PathPoint>& ipoints) {
  for (auto&& ipoint : ipoints) {
    addPoint(ipoint);
  }
}

void PathSegment::addSegments(const std::vector<PathSegment>& isegments) {
  for (auto&& isegment : isegments) {
    addSegment(isegment);
  }
}

std::vector<PathPoint> PathSegment::extract() const {
  std::vector<PathPoint> temp;
  for (auto&& segment : segments) {
    if (std::holds_alternative<PathPoint>(segment)) {
      temp.push_back(std::get<PathPoint>(segment));
    } else {
      auto&& points = std::get<PathSegment>(segment).extract();
      for (auto&& point : points) {
        temp.push_back(point);
      }
    }
  }
  return temp;
}

} // namespace lib7842