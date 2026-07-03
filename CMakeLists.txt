cmake_minimum_required(VERSION 3.16)

project(CHESS_ENGINE)

# ==========================================
# C++
# ==========================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# Include directories
# ==========================================
include_directories(
    src
    src/Core
    src/Graphics
    src/Screens
    src/UI

    externals/glad/include
    externals/glfw-3.4/include
    externals/glm
)

# ==========================================
# GLAD
# ==========================================
add_library(glad
    externals/glad/src/glad.c
)

# ==========================================
# GLFW
# ==========================================
add_subdirectory(externals/glfw-3.4)

# ==========================================
# Source files
# ==========================================
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# ==========================================
# Executable
# ==========================================
add_executable(chess_engine
    main.cpp
    ${SOURCES}
)

# ==========================================
# Link libraries
# ==========================================
target_link_libraries(chess_engine
    PRIVATE
        glad
        glfw
        opengl32
)

# ==========================================
# Visual Studio
# ==========================================
set_target_properties(chess_engine PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# ==========================================
# Copy shaders to build/Shaders
# ==========================================
file(COPY
    "${CMAKE_SOURCE_DIR}/src/Graphics/Shaders"
    DESTINATION "${CMAKE_BINARY_DIR}"
)