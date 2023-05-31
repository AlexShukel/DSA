FILE(GLOB SRC_FILES *.cpp)

add_library(hamiltonian_cycle STATIC ${SRC_FILES})
target_link_libraries(hamiltonian_cycle graph)
target_include_directories(hamiltonian_cycle PUBLIC "../../Graph/src")
