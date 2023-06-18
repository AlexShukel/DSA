FILE(GLOB SRC_FILES *.cpp)

add_library(modread STATIC ${SRC_FILES})
target_link_libraries(modread dynamic_array)
target_include_directories(modread PUBLIC "${CMAKE_SOURCE_DIR}/data-structures/dynamic-array/src")
