cmake_minimum_required(VERSION 3.9)
project(DrawVTK)

set(CMAKE_CXX_STANDARD 11)

#find_package(VTK REQUIRED)

#include(${VTK_USE_FILE})



include_directories(
        /home/steve/anaconda3/include/vtk-7.1/
)

link_directories(
        /home/steve/anaconda3/lib/
)

add_executable(ScatterPlot ScatterPlot.cpp )

target_link_libraries(ScatterPlot  ${VTK_LIBRARIES})




add_library(DrawVTK SHARED library.cpp library.h)