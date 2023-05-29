FILE(GLOB TEST_FILES *.test.cpp)

add_executable(a_start_tests ${TEST_FILES})

target_link_libraries(a_start_tests GTest::gtest_main graph a_star)
target_include_directories(a_start_tests PUBLIC "../src" "../../Graph/src")

include(GoogleTest)
gtest_discover_tests(a_start_tests)
