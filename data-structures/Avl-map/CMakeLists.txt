FILE(GLOB TEST_FILES *.test.cpp)

add_executable(avl_map_tests ${TEST_FILES})

target_link_libraries(avl_map_tests GTest::gtest_main)
target_include_directories(avl_map_tests PUBLIC "../Bst-map")

include(GoogleTest)
gtest_discover_tests(avl_map_tests)
