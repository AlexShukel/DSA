FILE(GLOB SRC_FILES *.cpp)

add_library(test_utils STATIC ${SRC_FILES})
target_link_libraries(test_utils GTest::gtest_main)
