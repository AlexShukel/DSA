FILE(GLOB TEST_FILES *.test.cpp)

add_executable(sortsTest ${TEST_FILES})

target_link_libraries(sortsTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(sortsTest)

# Extract test utils in static lib
add_library(test_utils STATIC utils.test.cpp)
target_link_libraries(test_utils GTest::gtest_main)
