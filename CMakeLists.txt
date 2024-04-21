cmake_minimum_required(VERSION 3.5)
set( CMAKE_CXX_COMPILER "D:/MinGW/bin/g++.exe" )
set( CMAKE_C_COMPILER "D:/MinGW/bin/gcc.exe" )

project (FlexRent)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/head)

# add_subdirectory(lib)

aux_source_directory(./src DIR_SRCS)

add_executable(FlexRent ${DIR_SRCS})

# target_link_libraries(Demo add)
# target_link_libraries(Demo sub)