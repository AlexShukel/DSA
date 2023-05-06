FILE(GLOB TEST_FILES *.test.cpp)

add_executable(hungarianTests ${TEST_FILES})

target_link_libraries(hungarianTests GTest::gtest_main hungarian)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include(GoogleTest)
gtest_discover_tests(hungarianTests)
