cmake_minimum_required(VERSION 3.10)

# Define name of the project
project(Gustelandyard)

# Include src/ as a directory (executes the CMakeLists.txt in there)
add_subdirectory(vendor/libzmq)
add_subdirectory(src)