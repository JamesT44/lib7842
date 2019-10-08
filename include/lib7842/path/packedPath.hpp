#pragma once
#include "main.h"
#include "simplePath.hpp"

#include "lib7842/point/packedPoint.hpp"

namespace lib7842 {

class PackedPath : public SimplePath {

 public:
  /**
   * Default Constructors
   */
  PackedPath() = default;
  PackedPath(const PackedPath& ipath) = default;
  virtual ~PackedPath() = default;

  /**
   * Explicit Constructors
   */
  explicit PackedPath(const std::initializer_list<PackedPoint>& ipath);
  explicit PackedPath(const std::vector<PackedPoint>& ipath);

  /**
   * Explicit Functions
   */
  std::vector<PackedPoint>& get();

  /**
   * Extractors
   */
  virtual SimplePath extract() const override;
  virtual ReferencePath extractRef() const override;
  virtual std::shared_ptr<AbstractPath> copyPtr() const override;
  virtual std::shared_ptr<AbstractPath> movePtr() const override;

 protected:
  std::vector<PackedPoint> path {};
};

} // namespace lib7842