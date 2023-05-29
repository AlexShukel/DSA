FILE(GLOB SRC_FILES *.cpp)

add_library(dijkstra STATIC ${SRC_FILES})
target_link_libraries(dijkstra graph)
target_include_directories(dijkstra PUBLIC "../../Graph/src")
