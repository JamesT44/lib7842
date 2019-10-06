#include "test.hpp"
#include "lib7842/path/compoundPath.hpp"

class CompoundPathTest : public ::testing::Test {
 protected:
  CompoundPath path;
  QPoint point1 {5_in, 3_in};
};

TEST_F(CompoundPathTest, Constructors) {
  CompoundPath();
  CompoundPath(std::make_unique<SimplePath>());
  CompoundPath(std::make_unique<ReferencePath>());
}

TEST_F(CompoundPathTest, AddPaths) {
  path.addPath(std::make_unique<SimplePath>());
  path.addPath(std::make_unique<ReferencePath>());
  path.addPath(SimplePath {point1});
  path.addPath(SimplePath({point1, point1}));
}

TEST_F(CompoundPathTest, ExtractSegments) {
  path.addPath(SimplePath({point1}));
  path.addPath(SimplePath({point1, point1}));
  path.addPath(std::make_unique<SimplePath>());

  std::vector<QPoint> ipath = path.extract().get();
  ASSERT_EQ(ipath.size(), 3);
  for (auto&& point : ipath) {
    ASSERT_EQ(point, point1);
  }
}

TEST_F(CompoundPathTest, ExtractSegmentsRef) {
  path.addPath(SimplePath({point1}));
  path.addPath(SimplePath({point1, point1}));
  path.addPath(std::make_unique<SimplePath>());
  path.addPath(SimplePath({{5_in, 3_in}}));

  ReferencePath ipath = path.extractRef();
  ReferencePath ipath2 = path.extractRef();

  for (size_t i = 0; i < ipath.get().size(); i++) {
    ASSERT_EQ(&ipath.get()[i].get(), &ipath2.get()[i].get());
  }
}

TEST_F(CompoundPathTest, ProperOrder) {
  path.addPath(SimplePath({{1_in, 2_in}}));
  path.addPath(SimplePath({{2_in, 3_in}, {3_in, 4_in}}));

  CompoundPath segment1 = CompoundPath().addPath(SimplePath({{4_in, 5_in}, {5_in, 6_in}}));
  CompoundPath segment2 = CompoundPath().addPath(SimplePath({{6_in, 7_in}}));
  CompoundPath segment3 = CompoundPath().addPath(SimplePath({{7_in, 8_in}}));
  CompoundPath segment3b = CompoundPath(std::make_unique<CompoundPath>(segment3));
  CompoundPath segment4 = CompoundPath()
                            .addPath(std::move(std::unique_ptr<CompoundPath>(&segment2)))
                            .addPath(std::move(std::unique_ptr<CompoundPath>(&segment3b)));
  CompoundPath segment5 = CompoundPath().addPath(SimplePath({{8_in, 9_in}}));

  path.addPath(std::move(std::unique_ptr<CompoundPath>(&segment1)));
  path.addPath(std::move(std::unique_ptr<CompoundPath>(&segment4)))
    .addPath(std::move(std::unique_ptr<CompoundPath>(&segment5)));

  std::vector<QPoint> ipath = path.extract().get();

  ASSERT_EQ(ipath.size(), 8);
  for (size_t i = 0; i < ipath.size(); ++i) {
    ASSERT_EQ(ipath[i], (QPoint {(i + 1) * inch, (i + 2) * inch}));
  }
}
