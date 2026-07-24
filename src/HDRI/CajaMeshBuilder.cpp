#include "CajaMeshBuilder.h"

#include <vector>



//====================================================
// UPLOAD FACE
//====================================================

void CajaMeshBuilder::uploadFace(
    Mesh3D& mesh,
    const std::vector<Vertex3D>& vertices,
    const std::vector<uint32_t>& indices
)
{

    mesh.upload(
        vertices,
        indices
    );

}



//====================================================
// BUILD
//====================================================

void CajaMeshBuilder::build(
    CajaMesh3D& caja,
    const glm::vec3& size,
    const glm::vec3& color
)
{

    float hx =
        size.x * 0.5f;

    float hy =
        size.y * 0.5f;

    float hz =
        size.z * 0.5f;



    buildFloor(
        caja,
        hx,
        hy,
        hz,
        color
    );



    buildCeiling(
        caja,
        hx,
        hy,
        hz,
        color
    );



    buildFront(
        caja,
        hx,
        hy,
        hz,
        color
    );



    buildBack(
        caja,
        hx,
        hy,
        hz,
        color
    );



    buildLeft(
        caja,
        hx,
        hy,
        hz,
        color
    );



    buildRight(
        caja,
        hx,
        hy,
        hz,
        color
    );

}

//====================================================
// BUILD FLOOR
//====================================================

void CajaMeshBuilder::buildFloor(
    CajaMesh3D& caja,
    float hx,
    float hy,
    float hz,
    const glm::vec3& color
)
{

    std::vector<Vertex3D> vertices =
    {

        //------------------------------------------------
        // Bottom Left
        //------------------------------------------------

        {
            {-hx, -hy,  hz},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Bottom Right
        //------------------------------------------------

        {
            { hx, -hy,  hz},
            {0.0f, 1.0f, 0.0f},
            {1.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Top Right
        //------------------------------------------------

        {
            { hx, -hy, -hz},
            {0.0f, 1.0f, 0.0f},
            {1.0f, 1.0f},
            color
        },



        //------------------------------------------------
        // Top Left
        //------------------------------------------------

        {
            {-hx, -hy, -hz},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 1.0f},
            color
        }

    };



    std::vector<uint32_t> indices =
    {
        0, 2, 1,
        0, 3, 2
    };



    uploadFace(
        caja.getFace(
            CajaMesh3D::Face::FLOOR
        ),
        vertices,
        indices
    );

}

//====================================================
// BUILD CEILING
//====================================================

void CajaMeshBuilder::buildCeiling(
    CajaMesh3D& caja,
    float hx,
    float hy,
    float hz,
    const glm::vec3& color
)
{

    std::vector<Vertex3D> vertices =
    {

        //------------------------------------------------
        // Bottom Left
        //------------------------------------------------

        {
            {-hx, hy, -hz},
            {0.0f, -1.0f, 0.0f},
            {0.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Bottom Right
        //------------------------------------------------

        {
            { hx, hy, -hz},
            {0.0f, -1.0f, 0.0f},
            {1.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Top Right
        //------------------------------------------------

        {
            { hx, hy,  hz},
            {0.0f, -1.0f, 0.0f},
            {1.0f, 1.0f},
            color
        },



        //------------------------------------------------
        // Top Left
        //------------------------------------------------

        {
            {-hx, hy,  hz},
            {0.0f, -1.0f, 0.0f},
            {0.0f, 1.0f},
            color
        }

    };



    std::vector<uint32_t> indices =
    {
        0, 2, 1,
        0, 3, 2
    };



    uploadFace(
        caja.getFace(
            CajaMesh3D::Face::CEILING
        ),
        vertices,
        indices
    );

}

//====================================================
// BUILD FRONT
//====================================================

void CajaMeshBuilder::buildFront(
    CajaMesh3D& caja,
    float hx,
    float hy,
    float hz,
    const glm::vec3& color
)
{

    std::vector<Vertex3D> vertices =
    {

        //------------------------------------------------
        // Bottom Left
        //------------------------------------------------

        {
            {-hx, -hy, hz},
            {0.0f, 0.0f, -1.0f},
            {0.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Bottom Right
        //------------------------------------------------

        {
            { hx, -hy, hz},
            {0.0f, 0.0f, -1.0f},
            {1.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Top Right
        //------------------------------------------------

        {
            { hx,  hy, hz},
            {0.0f, 0.0f, -1.0f},
            {1.0f, 1.0f},
            color
        },



        //------------------------------------------------
        // Top Left
        //------------------------------------------------

        {
            {-hx,  hy, hz},
            {0.0f, 0.0f, -1.0f},
            {0.0f, 1.0f},
            color
        }

    };



    std::vector<uint32_t> indices =
    {
        0, 2, 1,
        0, 3, 2
    };



    uploadFace(
        caja.getFace(
            CajaMesh3D::Face::FRONT
        ),
        vertices,
        indices
    );

}

//====================================================
// BUILD BACK
//====================================================

void CajaMeshBuilder::buildBack(
    CajaMesh3D& caja,
    float hx,
    float hy,
    float hz,
    const glm::vec3& color
)
{

    std::vector<Vertex3D> vertices =
    {

        //------------------------------------------------
        // Bottom Left
        //------------------------------------------------

        {
            { hx, -hy, -hz},
            {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Bottom Right
        //------------------------------------------------

        {
            {-hx, -hy, -hz},
            {0.0f, 0.0f, 1.0f},
            {1.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Top Right
        //------------------------------------------------

        {
            {-hx,  hy, -hz},
            {0.0f, 0.0f, 1.0f},
            {1.0f, 1.0f},
            color
        },



        //------------------------------------------------
        // Top Left
        //------------------------------------------------

        {
            { hx,  hy, -hz},
            {0.0f, 0.0f, 1.0f},
            {0.0f, 1.0f},
            color
        }

    };



    std::vector<uint32_t> indices =
    {
        0, 2, 1,
        0, 3, 2
    };



    uploadFace(
        caja.getFace(
            CajaMesh3D::Face::BACK
        ),
        vertices,
        indices
    );

}

//====================================================
// BUILD LEFT
//====================================================

void CajaMeshBuilder::buildLeft(
    CajaMesh3D& caja,
    float hx,
    float hy,
    float hz,
    const glm::vec3& color
)
{

    std::vector<Vertex3D> vertices =
    {

        //------------------------------------------------
        // Bottom Left
        //------------------------------------------------

        {
            {-hx, -hy, -hz},
            {1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Bottom Right
        //------------------------------------------------

        {
            {-hx, -hy,  hz},
            {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Top Right
        //------------------------------------------------

        {
            {-hx,  hy,  hz},
            {1.0f, 0.0f, 0.0f},
            {1.0f, 1.0f},
            color
        },



        //------------------------------------------------
        // Top Left
        //------------------------------------------------

        {
            {-hx,  hy, -hz},
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f},
            color
        }

    };



    std::vector<uint32_t> indices =
    {
        0, 2, 1,
        0, 3, 2
    };



    uploadFace(
        caja.getFace(
            CajaMesh3D::Face::LEFT
        ),
        vertices,
        indices
    );

}

//====================================================
// BUILD RIGHT
//====================================================

void CajaMeshBuilder::buildRight(
    CajaMesh3D& caja,
    float hx,
    float hy,
    float hz,
    const glm::vec3& color
)
{

    std::vector<Vertex3D> vertices =
    {

        //------------------------------------------------
        // Bottom Left
        //------------------------------------------------

        {
            { hx, -hy,  hz},
            {-1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Bottom Right
        //------------------------------------------------

        {
            { hx, -hy, -hz},
            {-1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f},
            color
        },



        //------------------------------------------------
        // Top Right
        //------------------------------------------------

        {
            { hx,  hy, -hz},
            {-1.0f, 0.0f, 0.0f},
            {1.0f, 1.0f},
            color
        },



        //------------------------------------------------
        // Top Left
        //------------------------------------------------

        {
            { hx,  hy,  hz},
            {-1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f},
            color
        }

    };



    std::vector<uint32_t> indices =
    {
        0, 2, 1,
        0, 3, 2
    };



    uploadFace(
        caja.getFace(
            CajaMesh3D::Face::RIGHT
        ),
        vertices,
        indices
    );

}