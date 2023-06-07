FILE(GLOB TEST_FILES *.test.cpp)

add_executable(dynamic_array_tests ${TEST_FILES})

target_link_libraries(dynamic_array_tests GTest::gtest_main dynamic_array)
target_include_directories(dynamic_array_tests PUBLIC "../src")

include(GoogleTest)
gtest_discover_tests(dynamic_array_tests)
