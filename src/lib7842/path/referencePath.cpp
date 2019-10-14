#include "referencePath.hpp"

namespace lib7842 {

ReferencePath::ReferencePath(const std::vector<VectorRef>& ipath) : path(ipath) {}

std::vector<VectorRef>& ReferencePath::get() {
  return path;
}

std::vector<VectorRef>& ReferencePath::operator()() {
  return path;
}

SimplePath ReferencePath::extract() const {
  return SimplePath(path);
}

SimplePath ReferencePath::extractCopy() const {
  return SimplePath(path).extractCopy();
}

ReferencePath ReferencePath::extractRef() const {
  return *this;
}

std::shared_ptr<AbstractPath> ReferencePath::copyPtr() const {
  return std::make_shared<ReferencePath>(*this);
}

std::shared_ptr<AbstractPath> ReferencePath::movePtr() const {
  return std::make_shared<ReferencePath>(std::move(*this));
}

SimplePath ReferencePath::generate(const size_t isteps) const {
  return SimplePath(path).generate(isteps);
}

} // namespace lib7842