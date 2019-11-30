#include "test.hpp"

using namespace lib7842::units;

class PathGeneratorTest : public ::testing::Test, public PathGenerator {
protected:
  PursuitLimits limits {2_ips, 8_ips, 8_ips2, 1};
};

TEST_F(PathGeneratorTest, ComputeSingleCurvature) {
  double straight = PathGenerator::calculateCurvature({0_in, 0_in}, {0_in, 5_in}, {0_in, 10_in});
  ASSERT_EQ(straight, 0);

  double curvature = PathGenerator::calculateCurvature({0_in, 0_in}, {3_in, 5_in}, {0_in, 10_in});
  ASSERT_NE(curvature, 0);

  double turn = PathGenerator::calculateCurvature({0_in, 0_in}, {3_in, 5_in}, {0_in, 0_in});
  ASSERT_EQ(turn, 0);
}

TEST_F(PathGeneratorTest, SetCurvatures) {
  PursuitPath pathStraight({{0_in, 0_in}, {0_in, 5_in}, {0_in, 10_in}});
  PathGenerator::setCurvatures(pathStraight);

  ASSERT_EQ(pathStraight()[1]->getData<double>("curvature"), 0);

  ASSERT_EQ(pathStraight()[0]->getData<double>("curvature"), 0);
  ASSERT_EQ(pathStraight()[2]->getData<double>("curvature"), 0);

  PursuitPath pathCurv({{0_in, 0_in}, {3_in, 5_in}, {0_in, 10_in}});
  PathGenerator::setCurvatures(pathCurv);
  ASSERT_NE(pathCurv()[1]->getData<double>("curvature"), 0);

  ASSERT_EQ(pathCurv()[0]->getData<double>("curvature"), 0);
  ASSERT_EQ(pathCurv()[2]->getData<double>("curvature"), 0);

  PursuitPath pathTurn({{0_in, 0_in}, {3_in, 5_in}, {0_in, 0_in}});
  PathGenerator::setCurvatures(pathTurn);
  ASSERT_EQ(pathTurn()[1]->getData<double>("curvature"), 0);

  ASSERT_EQ(pathTurn()[0]->getData<double>("curvature"), 0);
  ASSERT_EQ(pathTurn()[2]->getData<double>("curvature"), 0);
}

TEST_F(PathGeneratorTest, SetMaxVelocity) {
  PursuitPath path({{0_in, 0_in}, {0_in, 5_in}, {0_in, 10_in}});
  PathGenerator::setCurvatures(path);
  PathGenerator::setMaxVelocity(path, limits);

  ASSERT_EQ(path()[0]->getData<QSpeed>("velocity").convert(ips), 8);
  ASSERT_EQ(path()[1]->getData<QSpeed>("velocity").convert(ips), 8);
  ASSERT_EQ(path()[2]->getData<QSpeed>("velocity").convert(ips), 0);
}

TEST_F(PathGeneratorTest, SetMaxVelocityTurn) {
  PursuitPath path({{0_in, 0_in}, {3_in, 4_in}, {6_in, 10_in}, {5_in, 12_in}});
  PathGenerator::setCurvatures(path);
  PathGenerator::setMaxVelocity(path, limits);

  ASSERT_EQ(path()[0]->getData<QSpeed>("velocity").convert(ips), 8);
  ASSERT_LT(path()[1]->getData<QSpeed>("velocity").convert(ips), 8);
  ASSERT_LT(path()[2]->getData<QSpeed>("velocity").convert(ips), 8);
  ASSERT_EQ(path()[3]->getData<QSpeed>("velocity").convert(ips), 0);
}