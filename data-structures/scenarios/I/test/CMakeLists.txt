FILE(GLOB TEST_FILES *.test.cpp)

add_executable(midlar_tests ${TEST_FILES})

target_link_libraries(midlar_tests GTest::gtest_main midlar test_utils)
target_include_directories(midlar_tests PUBLIC "../src" "${CMAKE_SOURCE_DIR}/test-utils")

include(GoogleTest)
gtest_discover_tests(midlar_tests)
