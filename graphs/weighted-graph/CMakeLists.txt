FILE(GLOB TEST_FILES *.test.cpp)

add_executable(weightedGraphTest ${TEST_FILES})

target_link_libraries(weightedGraphTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(weightedGraphTest)
