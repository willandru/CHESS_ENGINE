cmake_minimum_required(VERSION 3.16)

project(CHESS_ENGINE)

# ==========================================
# C++ STANDARD
# ==========================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# INCLUDE DIRECTORIES
# ==========================================
include_directories(
    src
    src/Core
    src/Graphics
    src/Screens
    src/UI
    src/Game
    src/AI

    externals/glad/include
    externals/glfw-3.4/include
    externals/glm
    externals/stb
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
# SOURCE FILES (ENGINE CORE)
# ==========================================
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# ==========================================
# EXECUTABLE 1: CHESS ENGINE
# ==========================================
add_executable(chess_engine
    main.cpp
    ${SOURCES}
)

target_link_libraries(chess_engine
    PRIVATE
        glad
        glfw
        opengl32
)

set_target_properties(chess_engine PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# ==========================================
# EXECUTABLE 2: RL TRAINER / AGENT SYSTEM
# ==========================================
add_executable(rl_trainer
    main_rl.cpp
)

# (opcional ahora, futuro RL libs)
target_link_libraries(rl_trainer
    PRIVATE
        glad
        glfw
        opengl32
)

set_target_properties(rl_trainer PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# ==========================================
# SHADERS COPY
# ==========================================
file(COPY
    "${CMAKE_SOURCE_DIR}/src/Graphics/Shaders"
    DESTINATION "${CMAKE_BINARY_DIR}"
)

# ==========================================
# ASSETS COPY
# ==========================================
file(COPY
    "${CMAKE_SOURCE_DIR}/src/Assets"
    DESTINATION "${CMAKE_BINARY_DIR}"
)