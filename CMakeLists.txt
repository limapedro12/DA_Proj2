cmake_minimum_required(VERSION 3.23)
project(DA_Proj2)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_Proj2 main.cpp "Data Reading/read_data.cpp" "Data Reading/read_data.h" Classes/Graph.cpp Classes/Graph.h Classes/VertexEdge.cpp Classes/VertexEdge.h Classes/two-opt.h Classes/two-opt.cpp Interface/Menu.cpp Interface/Menu.h Classes/k-opt.cpp)
