cmake_minimum_required(VERSION 3.9)
project(DrawVTK)

set(CMAKE_CXX_STANDARD 14)

set(VTK_DIR /home/steve/Downloads/VTK-8.1.0/build/)
find_package(VTK REQUIRED)

#include(${VTK_USE_FILE})
include(
        ${VTK_USE_FILE}
)

link_directories(
        /home/steve/anaconda3/lib/
)

add_executable(ScatterPlot ScatterPlot.cpp )

target_link_libraries(ScatterPlot  ${VTK_LIBRARIES})




add_library(DrawVTK SHARED library.cpp library.h)