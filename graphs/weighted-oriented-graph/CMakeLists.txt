FILE(GLOB TEST_FILES *.test.cpp)

add_executable(weightedOrientedGraphTest ${TEST_FILES})

target_link_libraries(weightedOrientedGraphTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(weightedOrientedGraphTest)
