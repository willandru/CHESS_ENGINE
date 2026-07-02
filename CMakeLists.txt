cmake_minimum_required(VERSION 3.16)
project(CHESS_ENGINE)

set(CMAKE_CXX_STANDARD 17)

# =========================
# INCLUDES (ROOTS DEL PROYECTO)
# =========================
include_directories(
    src
    src/Screens
    src/UI
    src/Core
    src/Graphics
    externals/glad/include
    externals/glfw-3.4/include
    externals/glm
)

# =========================
# GLAD
# =========================
add_library(glad externals/glad/src/glad.c)

# =========================
# GLFW (build interno)
# =========================
add_subdirectory(externals/glfw-3.4)

# =========================
# SOURCES
# =========================
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# =========================
# EXECUTABLE
# =========================
add_executable(chess_engine
    main.cpp
    ${SOURCES}
)

# =========================
# LINK LIBS
# =========================
target_link_libraries(chess_engine
    glad
    glfw
    opengl32
)