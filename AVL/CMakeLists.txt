FILE(GLOB TEST_FILES *.test.cpp)

add_executable(avlTest ${TEST_FILES})

target_link_libraries(avlTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(avlTest)
