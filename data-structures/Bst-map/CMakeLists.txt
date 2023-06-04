FILE(GLOB TEST_FILES *.test.cpp)

add_executable(bst_map_tests ${TEST_FILES})

target_link_libraries(bst_map_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(bst_map_tests)
