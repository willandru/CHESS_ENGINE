#include "CajaMeshBuilder.h"

#include <vector>
#include <cstdint>



//====================================================
// ADD QUAD
//====================================================

void CajaMeshBuilder::addQuad(

    std::vector<Vertex3D>& vertices,
    std::vector<uint32_t>& indices,

    const glm::vec3& v0,
    const glm::vec3& v1,
    const glm::vec3& v2,
    const glm::vec3& v3,

    const glm::vec3& normal,
    const glm::vec3& color

)
{

    uint32_t start =
        static_cast<uint32_t>(
            vertices.size()
        );



    vertices.push_back(
    {
        v0,
        normal,
        {0.0f, 0.0f},
        color
    });



    vertices.push_back(
    {
        v1,
        normal,
        {1.0f, 0.0f},
        color
    });



    vertices.push_back(
    {
        v2,
        normal,
        {1.0f, 1.0f},
        color
    });



    vertices.push_back(
    {
        v3,
        normal,
        {0.0f, 1.0f},
        color
    });



    indices.push_back(
        start + 0
    );

    indices.push_back(
        start + 2
    );

    indices.push_back(
        start + 1
    );



    indices.push_back(
        start + 0
    );

    indices.push_back(
        start + 3
    );

    indices.push_back(
        start + 2
    );

}



//====================================================
// BUILD
//====================================================

void CajaMeshBuilder::build(

    CajaMesh3D& caja,

    float left,
    float right,

    float front,
    float back,

    float floor,
    float ceiling,

    const glm::vec3& color

)
{

    std::vector<Vertex3D> vertices;

    std::vector<uint32_t> indices;



    //------------------------------------------------
    // FLOOR
    //------------------------------------------------

    addQuad(

        vertices,
        indices,

        { left,  floor, front },
        { right, floor, front },
        { right, floor, back },
        { left,  floor, back },

        { 0.0f, 1.0f, 0.0f },

        color

    );



    //------------------------------------------------
    // CEILING
    //------------------------------------------------

    addQuad(

        vertices,
        indices,

        { left,  ceiling, back },
        { right, ceiling, back },
        { right, ceiling, front },
        { left,  ceiling, front },

        { 0.0f, -1.0f, 0.0f },

        color

    );



    //------------------------------------------------
    // FRONT
    //------------------------------------------------

    addQuad(

        vertices,
        indices,

        { left, floor, front },
        { right, floor, front },
        { right, ceiling, front },
        { left, ceiling, front },

        { 0.0f, 0.0f, -1.0f },

        color

    );



    //------------------------------------------------
    // BACK
    //------------------------------------------------

    addQuad(

        vertices,
        indices,

        { right, floor, back },
        { left, floor, back },
        { left, ceiling, back },
        { right, ceiling, back },

        { 0.0f, 0.0f, 1.0f },

        color

    );



    //------------------------------------------------
    // LEFT
    //------------------------------------------------

    addQuad(

        vertices,
        indices,

        { left, floor, back },
        { left, floor, front },
        { left, ceiling, front },
        { left, ceiling, back },

        { 1.0f, 0.0f, 0.0f },

        color

    );



    //------------------------------------------------
    // RIGHT
    //------------------------------------------------

    addQuad(

        vertices,
        indices,

        { right, floor, front },
        { right, floor, back },
        { right, ceiling, back },
        { right, ceiling, front },

        { -1.0f, 0.0f, 0.0f },

        color

    );



    //------------------------------------------------
    // UPLOAD
    //------------------------------------------------

    caja.getMesh().upload(

        vertices,

        indices

    );

}