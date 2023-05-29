FILE(GLOB TEST_FILES *.test.cpp)

add_executable(graph_tests ${TEST_FILES})

target_link_libraries(graph_tests GTest::gtest_main graph)
target_include_directories(graph_tests PUBLIC "../src")

include(GoogleTest)
gtest_discover_tests(graph_tests)
