cmake_minimum_required(VERSION 3.5.1)
message(STATUS "CMake version: ${CMAKE_VERSION}")

project(linear_sample)

option(USE_CUDA "Use CUDA" ON)

file(GLOB cpu_source_files "${CMAKE_SOURCE_DIR}/*.cpp")
file(GLOB gpu_source_files "${CMAKE_SOURCE_DIR}/*.cu")
enable_language("CUDA")
add_executable(linear_sample ${cpu_source_files} ${gpu_source_files})

find_package(yaml-cpp REQUIRED)

message(STATUS "USE_CUDA: ${USE_CUDA}")
if(USE_CUDA)
    add_definitions(-DUSE_CUDA)
endif()

include_directories(
    ${YAML_INCLUDE_DIRS}
)

target_link_libraries(linear_sample 
    ${YAML_CPP_LIBRARIES}
)