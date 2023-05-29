FILE(GLOB TEST_FILES *.test.cpp)

add_executable(dijkstra_tests ${TEST_FILES})

target_link_libraries(dijkstra_tests GTest::gtest_main graph dijkstra)
target_include_directories(dijkstra_tests PUBLIC "../src" "../../Graph/src")

include(GoogleTest)
gtest_discover_tests(dijkstra_tests)
