# Create a target "gustelandyard" which will be compiled into an executable using the given source files
add_executable(gustelandyard 
    main.cpp
    map.cpp
    player.cpp
    game.cpp
)

# Tell gustelandyard where to find additional include files
target_include_directories(gustelandyard PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/include
)

# Copy additional files to executable directory
add_custom_command(TARGET gustelandyard POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:gustelandyard>/data
)