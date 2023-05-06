FILE(GLOB TEST_FILES *.test.cpp)

add_executable(sortsTest ${TEST_FILES})

target_link_libraries(sortsTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(sortsTest)
