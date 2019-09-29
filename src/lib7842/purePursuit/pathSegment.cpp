#include "pathSegment.hpp"

namespace lib7842 {

PathSegment::PathSegment(const segment_t& isegment) {
  addSegment(isegment);
}

PathSegment::PathSegment(const segments_t& isegments) {
  addSegments(isegments);
}

void PathSegment::addSegment(const segment_t& isegment) {
  segments.push_back(isegment);
}

void PathSegment::addSegments(const segments_t& isegments) {
  for (auto&& isegment : isegments) {
    segments.push_back(isegment);
  }
}

segments_t PathSegment::concat() {
  return segments;
}

} // namespace lib7842