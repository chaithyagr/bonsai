# CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(fmm)

find_package(PythonInterp 3.5 REQUIRED)
find_package(PythonLibs 3.5 REQUIRED)
set(CUDA_SEPARABLE_COMPILATION ON)
find_package(CUDA REQUIRED)

add_subdirectory(pybind11)

FILE(GLOB sources src/*.cu)

include_directories(${CUDA_INCLUDE_DIRS})
include_directories(include/)
set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} -arch=sm_52 --use_fast_math -rdc=true -g -lcudadevrt)
link_directories(${CUDA_TOOLKIT_ROOT_DIR}/lib64)
cuda_add_library(serial ${sources})
pybind11_add_module(fmm src/bonsai_python.cpp)

#CPP File for debug
add_executable(fmmcpp src/bonsai_main.cpp)
target_link_libraries(fmmcpp serial ${CUDA_LIBRARIES} -lcudadevrt)
target_link_libraries(fmm PRIVATE serial ${CUDA_LIBRARIES} -lcudadevrt)