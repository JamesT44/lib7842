#include "test.hpp"
#include "okapi/api/util/logging.hpp"

int lvglMain();

int main(int argc, char** argv) {
  Logger::setDefaultLogger(std::make_shared<Logger>(
    std::make_unique<MockTimer>(), "/dev/stdout", Logger::LogLevel::debug));

  if (argc > 1 && std::string(argv[1]) == "lvgl") {
    std::cout << "Running lvgl:" << std::endl;
    return lvglMain();
  } else {
    std::cout << "Running gtest:" << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
}