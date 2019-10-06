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
  path.addPoint(point1);
  path.addPoints({point1, point1});
  path.addPath(std::make_unique<SimplePath>());
  path.addPath(std::make_unique<ReferencePath>());
}

TEST_F(CompoundPathTest, ExtractSegments) {
  path.addPoint(point1);
  path.addPoints({point1, point1});
  path.addPath(std::make_unique<SimplePath>());

  std::vector<QPoint> ipath = path.extract().get();
  ASSERT_EQ(ipath.size(), 3);
  for (auto&& point : ipath) {
    ASSERT_EQ(point, point1);
  }
}

TEST_F(CompoundPathTest, ExtractSegmentsRef) {
  path.addPoint(point1);
  path.addPoints({point1, point1});
  SimplePath simple({{5_in, 3_in}});
  path.addPath(std::make_unique<SimplePath>());
  ReferencePath ipath = path.extractRef();
  ReferencePath ipath2 = path.extractRef();

  for (size_t i = 0; i < ipath.get().size(); i++) {
    ASSERT_EQ(&ipath.get()[i].get(), &ipath2.get()[i].get());
  }
}

TEST_F(CompoundPathTest, ProperOrder) {
  path.addPoint({1_in, 2_in});
  path.addPoints({{2_in, 3_in}, {3_in, 4_in}});

  CompoundPath segment1 = CompoundPath().addPoints({{4_in, 5_in}, {5_in, 6_in}});
  CompoundPath segment2 = CompoundPath().addPoint({6_in, 7_in});
  CompoundPath segment3 = CompoundPath().addPoint({7_in, 8_in});
  CompoundPath segment3b = CompoundPath(std::make_unique<CompoundPath>(segment3));
  CompoundPath segment4 = CompoundPath()
                            .addPath(std::unique_ptr<CompoundPath>(&segment2))
                            .addPath(std::unique_ptr<CompoundPath>(&segment3b));
  CompoundPath segment5 = CompoundPath().addPoint({8_in, 9_in});

  path.addPath(std::unique_ptr<CompoundPath>(&segment1));
  path.addPath(std::unique_ptr<CompoundPath>(&segment4))
    .addPath(std::unique_ptr<CompoundPath>(&segment5));

  std::vector<QPoint> ipath = path.extract().get();

  ASSERT_EQ(ipath.size(), 8);
  for (size_t i = 0; i < ipath.size(); ++i) {
    ASSERT_EQ(ipath[i], (QPoint {(i + 1) * inch, (i + 2) * inch}));
  }
}
