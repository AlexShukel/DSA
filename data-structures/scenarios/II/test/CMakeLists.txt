FILE(GLOB TEST_FILES *.test.cpp)

add_executable(modread_tests ${TEST_FILES})

target_link_libraries(modread_tests GTest::gtest_main modread test_utils)
target_include_directories(modread_tests PUBLIC "../src" "${CMAKE_SOURCE_DIR}/test-utils")

include(GoogleTest)
gtest_discover_tests(modread_tests)
