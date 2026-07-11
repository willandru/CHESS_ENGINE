#include "Mesh3D.h"

#include <iostream>

Mesh3D::Mesh3D()
{
}

Mesh3D::~Mesh3D()
{
    clear();
}

//====================================================
// UPLOAD
//====================================================

void Mesh3D::upload(
    const std::vector<Vertex3D>& newVertices,
    const std::vector<uint32_t>& newIndices
)
{
    //------------------------------------------------
    // REMOVE PREVIOUS GPU DATA
    //------------------------------------------------

    clear();

    //------------------------------------------------
    // STORE CPU COPY
    //------------------------------------------------

    vertices = newVertices;
    indices  = newIndices;

    indexCount =
        static_cast<uint32_t>(
            indices.size()
        );

    //------------------------------------------------
    // CREATE GPU OBJECTS
    //------------------------------------------------

    glGenVertexArrays(
        1,
        &vao
    );

    glGenBuffers(
        1,
        &vbo
    );

    glGenBuffers(
        1,
        &ebo
    );

    glBindVertexArray(
        vao
    );

    //------------------------------------------------
    // VBO
    //------------------------------------------------

    glBindBuffer(
        GL_ARRAY_BUFFER,
        vbo
    );

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex3D),
        vertices.data(),
        GL_STATIC_DRAW
    );

    //------------------------------------------------
    // EBO
    //------------------------------------------------

    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        ebo
    );

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(uint32_t),
        indices.data(),
        GL_STATIC_DRAW
    );

    //------------------------------------------------
    // POSITION
    //------------------------------------------------

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex3D),
        (void*)offsetof(Vertex3D, position)
    );

    //------------------------------------------------
    // NORMAL
    //------------------------------------------------

    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex3D),
        (void*)offsetof(Vertex3D, normal)
    );

    //------------------------------------------------
    // TEXCOORD
    //------------------------------------------------

    glEnableVertexAttribArray(2);

    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex3D),
        (void*)offsetof(Vertex3D, texCoord)
    );

    //------------------------------------------------
    // COLOR
    //------------------------------------------------

    glEnableVertexAttribArray(3);

    glVertexAttribPointer(
        3,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex3D),
        (void*)offsetof(Vertex3D, color)
    );

    glBindVertexArray(0);
}

//====================================================
// DRAW
//====================================================

void Mesh3D::draw() const
{
    if (vao == 0)
    {
        std::cout
            << "VAO == 0"
            << std::endl;

        return;
    }

    glBindVertexArray(
        vao
    );

    glDrawElements(
        GL_TRIANGLES,
        indexCount,
        GL_UNSIGNED_INT,
        nullptr
    );

    glBindVertexArray(0);
}

//====================================================
// CLEAR
//====================================================

void Mesh3D::clear()
{
    if (ebo != 0)
    {
        glDeleteBuffers(
            1,
            &ebo
        );

        ebo = 0;
    }

    if (vbo != 0)
    {
        glDeleteBuffers(
            1,
            &vbo
        );

        vbo = 0;
    }

    if (vao != 0)
    {
        glDeleteVertexArrays(
            1,
            &vao
        );

        vao = 0;
    }

    indexCount = 0;
}

//====================================================
// INFO
//====================================================

uint32_t Mesh3D::getIndexCount() const
{
    return indexCount;
}

const std::vector<Vertex3D>& Mesh3D::getVertices() const
{
    return vertices;
}

const std::vector<uint32_t>& Mesh3D::getIndices() const
{
    return indices;
}