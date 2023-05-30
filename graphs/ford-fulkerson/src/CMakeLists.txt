FILE(GLOB SRC_FILES *.cpp)

add_library(ford_fulkerson STATIC ${SRC_FILES})
target_link_libraries(ford_fulkerson graph)
target_include_directories(ford_fulkerson PUBLIC "../../Graph/src")
