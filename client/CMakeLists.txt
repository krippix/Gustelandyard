# Create a target "gustelandyard" which will be compiled into an executable using the given source files
add_executable(testclient 
    testclient.cpp
)

# Tell gustelandyard where to find additional include files
target_include_directories(testclient PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/include
)

target_link_libraries(testclient libzmq-static)