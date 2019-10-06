#pragma once
#include "main.h"
#include "abstractPath.hpp"
#include "referencePath.hpp"

#include "lib7842/point/point.hpp"
#include <variant>

namespace lib7842 {

class CompoundPath : AbstractPath {

 public:
  /**
   * Default Constructors
   */
  CompoundPath() = default;
  CompoundPath(const CompoundPath& ipath) = default;
  virtual ~CompoundPath() = default;

  /**
   * Explicit Functions
   */
  CompoundPath& addPoint(const QPoint& ipoint);
  CompoundPath& addSegment(const AbstractPath& isegment);

  CompoundPath& addPoints(const std::vector<QPoint>& ipoints);
  CompoundPath& addSegments(const std::vector<AbstractPath>& isegments);

  /**
   * Extractors
   */
  virtual SimplePath extract() const override;
  virtual ReferencePath extractRef() const override;

 protected:
  using AbstractPathRef = std::reference_wrapper<const AbstractPath>;
  std::vector<std::variant<QPoint, AbstractPathRef>> path {};
};

} // namespace lib7842