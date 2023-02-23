FILE(GLOB TEST_FILES *.test.cpp)

add_executable(sqrtTest ${TEST_FILES})

target_link_libraries(sqrtTest GTest::gtest_main sqrt)
target_include_directories(sqrtTest PUBLIC ../src)

include(GoogleTest)
gtest_discover_tests(sqrtTest)

add_test(NAME SQRT COMMAND sqrtTest)
