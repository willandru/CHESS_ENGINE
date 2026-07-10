cmake_minimum_required(VERSION 3.16)

project(CHESS_ENGINE)

# ==========================================
# C++ STANDARD
# ==========================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ==========================================
# LIBTORCH
# ==========================================

set(Torch_DIR
    "${CMAKE_SOURCE_DIR}/externals/libtorch/share/cmake/Torch"
)

find_package(Torch REQUIRED)


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
    src/Analysis
    src/RL

    externals/glad/include
    externals/glfw-3.4/include
    externals/glm
    externals/stb
    externals/tinygltf

    ${TORCH_INCLUDE_DIRS}
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

add_subdirectory(
    externals/glfw-3.4
)


# ==========================================
# SOURCES
# ==========================================

file(GLOB_RECURSE SOURCES

    src/*.cpp

)


# ==========================================
# EXECUTABLE
# ==========================================

add_executable(chess_engine

    main.cpp
    ${SOURCES}

)


# ==========================================
# LINK LIBRARIES
# ==========================================

target_link_libraries(chess_engine

    PRIVATE

        glad
        glfw
        opengl32

        ${TORCH_LIBRARIES}

)


# ==========================================
# TORCH C++ FLAGS
# ==========================================

set_property(
    TARGET chess_engine
    PROPERTY CXX_STANDARD 20
)


# ==========================================
# WORKING DIRECTORY
# ==========================================

set_target_properties(
    chess_engine PROPERTIES

    VS_DEBUGGER_WORKING_DIRECTORY
    "${CMAKE_BINARY_DIR}"

)


# ==========================================
# COPY LIBTORCH DLLs (WINDOWS)
# ==========================================

add_custom_command(

    TARGET chess_engine
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory

        "${CMAKE_SOURCE_DIR}/externals/libtorch/lib"

        "$<TARGET_FILE_DIR:chess_engine>"

)



# ==========================================
# COPY SHADERS
# ==========================================

file(COPY

    "${CMAKE_SOURCE_DIR}/src/Graphics/Shaders"

    DESTINATION

    "${CMAKE_BINARY_DIR}"

)



# ==========================================
# COPY ASSETS
# ==========================================

file(COPY

    "${CMAKE_SOURCE_DIR}/src/Assets"

    DESTINATION

    "${CMAKE_BINARY_DIR}"

)