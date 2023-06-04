cmake_minimum_required(VERSION 3.23)
project(DSA)

set(CMAKE_CXX_STANDARD 11)

# Add googletest library
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(sqrt)
add_subdirectory(BST)
add_subdirectory(AVL)
add_subdirectory(sorts)
add_subdirectory(hungarian)
add_subdirectory(edit-distance)
add_subdirectory(hash-table)
add_subdirectory(graphs)
add_subdirectory(data-structures)

add_executable(DSA main.cpp)

target_link_libraries(DSA sqrt)
target_include_directories(DSA PUBLIC sqrt/src)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif ()
