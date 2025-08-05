cmake_minimum_required(VERSION 3.24)
project(DES)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

set(CXX_FILE main.cpp)


set_source_files_properties(${CXX_FILE}
        PROPERTIES 
        COMPILE_FLAGS 
        "-O2 -DNDEBUG -Wall -Wextra")


include_directories(${PROJECT_NAME}  ./)

add_executable(${PROJECT_NAME} ${CXX_FILE})
