FILE(GLOB TEST_FILES *.test.cpp)

add_executable(bstTest ${TEST_FILES})

target_link_libraries(bstTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(bstTest)
