FILE(GLOB TEST_FILES *.test.cpp)

add_executable(gnomeTest ${TEST_FILES})

target_link_libraries(gnomeTest GTest::gtest_main gnome)
target_include_directories(gnomeTest PUBLIC ../src)

include(GoogleTest)
gtest_discover_tests(gnomeTest)
