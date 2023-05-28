FILE(GLOB TEST_FILES *.test.cpp)

add_executable(astartTest ${TEST_FILES})

target_link_libraries(astartTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(astartTest)
