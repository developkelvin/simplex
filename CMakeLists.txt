cmake_minimum_required(VERSION 3.21)
project(solver)

set(CMAKE_CXX_STANDARD 14)
find_package(Armadillo REQUIRED)
include_directories(${/Users/yoonsikjung/Downloads/armadillo-10.8.2})
add_executable(solver main.cpp lp.cpp lp.h ../../../CLionProjects/modern_cpp/example1_1.cpp ../../../CLionProjects/modern_cpp/example1_2.cpp ../../../CLionProjects/modern_cpp/example1_3.cpp ../../../CLionProjects/modern_cpp/musiclist.cpp matrixutil.h matrixutil.cpp)

#target_link_libraries(solver ${ARMADILLO_LIBRARIES})