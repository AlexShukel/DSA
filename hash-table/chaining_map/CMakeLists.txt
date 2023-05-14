FILE(GLOB TEST_FILES *.test.cpp)

add_executable(hash_table_map_chaining ${TEST_FILES})

target_link_libraries(hash_table_map_chaining GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(hash_table_map_chaining)
