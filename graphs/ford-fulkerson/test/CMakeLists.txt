FILE(GLOB TEST_FILES *.test.cpp)

add_executable(ford_fulkerson_tests ${TEST_FILES})

target_link_libraries(ford_fulkerson_tests GTest::gtest_main ford_fulkerson graph)
target_include_directories(ford_fulkerson_tests PUBLIC "../src" "../../Graph/src")

include(GoogleTest)
gtest_discover_tests(ford_fulkerson_tests)
