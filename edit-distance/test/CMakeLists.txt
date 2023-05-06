FILE(GLOB TEST_FILES *.test.cpp)

add_executable(editDistanceTests ${TEST_FILES})

target_link_libraries(editDistanceTests GTest::gtest_main editDistance)

include(GoogleTest)
gtest_discover_tests(editDistanceTests)
