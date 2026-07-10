#pragma once

#include "Vertex3D.h"

#include <vector>
#include <cstdint>

#include <glad/glad.h>


class Mesh3D
{
public:

    Mesh3D();

    ~Mesh3D();


    //------------------------------------------------
    // GPU
    //------------------------------------------------

    void upload(
        const std::vector<Vertex3D>& vertices,
        const std::vector<uint32_t>& indices
    );

    void draw() const;

    void clear();


    //------------------------------------------------
    // INFO
    //------------------------------------------------

    uint32_t getIndexCount() const;


private:

    GLuint vao = 0;

    GLuint vbo = 0;

    GLuint ebo = 0;


    uint32_t indexCount = 0;
};