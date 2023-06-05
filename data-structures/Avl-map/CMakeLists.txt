FILE(GLOB TEST_FILES *.test.cpp)

add_executable(avl_map_tests ${TEST_FILES})

target_link_libraries(avl_map_tests GTest::gtest_main test_utils)
target_include_directories(avl_map_tests PUBLIC "../Bst-map" "${CMAKE_SOURCE_DIR}/test-utils")

include(GoogleTest)
gtest_discover_tests(avl_map_tests)
