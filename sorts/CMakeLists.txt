FILE(GLOB TEST_FILES *.test.cpp)

add_executable(sortsTest ${TEST_FILES})

target_link_libraries(sortsTest GTest::gtest_main test_utils)
target_include_directories(sortsTest PUBLIC "${CMAKE_SOURCE_DIR}/test-utils")

include(GoogleTest)
gtest_discover_tests(sortsTest)
