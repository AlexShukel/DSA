FILE(GLOB TEST_FILES *.test.cpp)

add_executable(orientedGraphTest ${TEST_FILES})

target_link_libraries(orientedGraphTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(orientedGraphTest)
