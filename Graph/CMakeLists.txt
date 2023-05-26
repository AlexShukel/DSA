FILE(GLOB TEST_FILES *.test.cpp)

add_executable(graphTest ${TEST_FILES})

target_link_libraries(graphTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(graphTest)
