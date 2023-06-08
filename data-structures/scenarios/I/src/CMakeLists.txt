FILE(GLOB SRC_FILES *.cpp)

add_library(midlar STATIC ${SRC_FILES})
target_link_libraries(midlar dynamic_array)
target_include_directories(midlar PUBLIC "${CMAKE_SOURCE_DIR}/data-structures/dynamic-array/src")
