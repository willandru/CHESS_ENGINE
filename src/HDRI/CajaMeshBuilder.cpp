#include "CajaMeshBuilder.h"

#include <vector>



//====================================================
// BUILD FACE
//====================================================

static void buildFace(
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

    const glm::vec3& dimensions,

    const glm::vec3& color
)
{

    float hx =
        dimensions.x * 0.5f;


    float hy =
        dimensions.y * 0.5f;


    float hz =
        dimensions.z * 0.5f;



    //------------------------------------------------
    // FLOOR
    //------------------------------------------------

    {

        std::vector<Vertex3D> vertices =
        {

            {{-hx,-hy,-hz},{0,1,0},{0,0},color},
            {{ hx,-hy,-hz},{0,1,0},{1,0},color},
            {{ hx,-hy, hz},{0,1,0},{1,1},color},
            {{-hx,-hy, hz},{0,1,0},{0,1},color}

        };


        std::vector<uint32_t> indices =
        {
            0,2,1,
            0,3,2
        };


        buildFace(
            caja.getFace(
                CajaMesh3D::Face::FLOOR
            ),
            vertices,
            indices
        );

    }



    //------------------------------------------------
    // CEILING
    //------------------------------------------------

    {

        std::vector<Vertex3D> vertices =
        {

            {{-hx,hy,hz},{0,-1,0},{0,0},color},
            {{ hx,hy,hz},{0,-1,0},{1,0},color},
            {{ hx,hy,-hz},{0,-1,0},{1,1},color},
            {{-hx,hy,-hz},{0,-1,0},{0,1},color}

        };


        std::vector<uint32_t> indices =
        {
            0,2,1,
            0,3,2
        };


        buildFace(
            caja.getFace(
                CajaMesh3D::Face::CEILING
            ),
            vertices,
            indices
        );

    }



    //------------------------------------------------
    // FRONT
    //------------------------------------------------

    {

        std::vector<Vertex3D> vertices =
        {

            {{-hx,-hy,hz},{0,0,-1},{0,0},color},
            {{ hx,-hy,hz},{0,0,-1},{1,0},color},
            {{ hx, hy,hz},{0,0,-1},{1,1},color},
            {{-hx, hy,hz},{0,0,-1},{0,1},color}

        };


        std::vector<uint32_t> indices =
        {
            0,2,1,
            0,3,2
        };


        buildFace(
            caja.getFace(
                CajaMesh3D::Face::FRONT
            ),
            vertices,
            indices
        );

    }



    //------------------------------------------------
    // BACK
    //------------------------------------------------

    {

        std::vector<Vertex3D> vertices =
        {

            {{ hx,-hy,-hz},{0,0,1},{0,0},color},
            {{-hx,-hy,-hz},{0,0,1},{1,0},color},
            {{-hx, hy,-hz},{0,0,1},{1,1},color},
            {{ hx, hy,-hz},{0,0,1},{0,1},color}

        };


        std::vector<uint32_t> indices =
        {
            0,2,1,
            0,3,2
        };


        buildFace(
            caja.getFace(
                CajaMesh3D::Face::BACK
            ),
            vertices,
            indices
        );

    }



    //------------------------------------------------
    // LEFT
    //------------------------------------------------

    {

        std::vector<Vertex3D> vertices =
        {

            {{-hx,-hy,-hz},{1,0,0},{0,0},color},
            {{-hx,-hy, hz},{1,0,0},{1,0},color},
            {{-hx, hy, hz},{1,0,0},{1,1},color},
            {{-hx, hy,-hz},{1,0,0},{0,1},color}

        };


        std::vector<uint32_t> indices =
        {
            0,2,1,
            0,3,2
        };


        buildFace(
            caja.getFace(
                CajaMesh3D::Face::LEFT
            ),
            vertices,
            indices
        );

    }



    //------------------------------------------------
    // RIGHT
    //------------------------------------------------

    {

        std::vector<Vertex3D> vertices =
        {

            {{hx,-hy,hz},{-1,0,0},{0,0},color},
            {{hx,-hy,-hz},{-1,0,0},{1,0},color},
            {{hx,hy,-hz},{-1,0,0},{1,1},color},
            {{hx,hy,hz},{-1,0,0},{0,1},color}

        };


        std::vector<uint32_t> indices =
        {
            0,2,1,
            0,3,2
        };


        buildFace(
            caja.getFace(
                CajaMesh3D::Face::RIGHT
            ),
            vertices,
            indices
        );

    }

}