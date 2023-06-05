FILE(GLOB TEST_FILES *.test.cpp)

add_executable(hamiltonian_cycle_tests ${TEST_FILES})

target_link_libraries(hamiltonian_cycle_tests GTest::gtest_main hamiltonian_cycle graph)
target_include_directories(hamiltonian_cycle_tests PUBLIC "../src" "../../Graph/src" "${CMAKE_SOURCE_DIR}/test-utils")

include(GoogleTest)
gtest_discover_tests(hamiltonian_cycle_tests)
