#include "PlaneMeshBuilder.h"

#include <vector>

void PlaneMeshBuilder::build(
    Mesh3D& mesh,
    float width,
    float height,
    const glm::vec3& color
)
{
    const float halfWidth  = width  * 0.5f;
    const float halfHeight = height * 0.5f;

    //------------------------------------------------
    // VERTICES
    //------------------------------------------------

    std::vector<Vertex3D> vertices(4);

    // Bottom Left
    vertices[0].position = {
        -halfWidth,
        -halfHeight,
        0.0f
    };

    vertices[0].normal = {
        0.0f,
        0.0f,
        1.0f
    };

    vertices[0].texCoord = {
        0.0f,
        0.0f
    };

    vertices[0].color = color;


    // Bottom Right
    vertices[1].position = {
         halfWidth,
        -halfHeight,
         0.0f
    };

    vertices[1].normal = {
        0.0f,
        0.0f,
        1.0f
    };

    vertices[1].texCoord = {
        1.0f,
        0.0f
    };

    vertices[1].color = color;


    // Top Right
    vertices[2].position = {
         halfWidth,
         halfHeight,
         0.0f
    };

    vertices[2].normal = {
        0.0f,
        0.0f,
        1.0f
    };

    vertices[2].texCoord = {
        1.0f,
        1.0f
    };

    vertices[2].color = color;


    // Top Left
    vertices[3].position = {
        -halfWidth,
         halfHeight,
         0.0f
    };

    vertices[3].normal = {
        0.0f,
        0.0f,
        1.0f
    };

    vertices[3].texCoord = {
        0.0f,
        1.0f
    };

    vertices[3].color = color;


    //------------------------------------------------
    // INDICES
    //------------------------------------------------

    std::vector<uint32_t> indices =
    {
        0, 1, 2,
        2, 3, 0
    };


    //------------------------------------------------
    // GPU
    //------------------------------------------------

    mesh.upload(
        vertices,
        indices
    );
}