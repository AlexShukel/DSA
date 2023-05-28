FILE(GLOB TEST_FILES *.test.cpp)

add_executable(dijkstraTest ${TEST_FILES})

target_link_libraries(dijkstraTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(dijkstraTest)
