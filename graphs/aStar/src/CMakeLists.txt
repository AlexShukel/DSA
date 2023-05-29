FILE(GLOB SRC_FILES *.cpp)

add_library(a_star STATIC ${SRC_FILES})
target_link_libraries(a_star graph)
target_include_directories(a_star PUBLIC "../../Graph/src")
