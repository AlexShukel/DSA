FILE(GLOB SRC_FILES *.cpp)
FILE(GLOB TPP_FILES *.tpp)

add_library(sqrt STATIC ${SRC_FILES} ${TPP_FILES})
