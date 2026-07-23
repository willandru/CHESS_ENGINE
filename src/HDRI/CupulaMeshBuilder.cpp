#include "CupulaMeshBuilder.h"

#include "CupulaConstants3D.h"

#include <vector>
#include <cmath>


//====================================================
// BUILD COMPLETE CUPULA
//====================================================

void CupulaMeshBuilder::build(
    Mesh3D& mesh,
    float cupulaRadius,
    float groundRadius,
    float curveRadius,
    uint32_t radialSegments,
    uint32_t heightSegments,
    const glm::vec3& color
)
{

    std::vector<Vertex3D> vertices;

    std::vector<uint32_t> indices;



    //------------------------------------------------
    // STORE RINGS
    //------------------------------------------------

    uint32_t rings = 0;



    //------------------------------------------------
    // FUNCTION ADD RING
    //------------------------------------------------

    auto addRing =
    [&](float radius, float height)
    {

        for(
            uint32_t i = 0;
            i <= radialSegments;
            ++i
        )
        {

            float u =
                static_cast<float>(i)
                /
                static_cast<float>(radialSegments);



            float theta =
                u *
                2.0f *
                CupulaConstants3D::PI;



            float x =
                radius *
                std::cos(theta);


            float z =
                radius *
                std::sin(theta);



            Vertex3D vertex;



            vertex.position =
            {
                x,
                height,
                z
            };



            // Interior de la cúpula
            vertex.normal =
            {
                -std::cos(theta),
                0.0f,
                -std::sin(theta)
            };



            vertex.texCoord =
            {
                u,
                0.0f
            };


            vertex.color =
                color;



            vertices.push_back(
                vertex
            );

        }


        rings++;

    };



    //------------------------------------------------
    // 1) GROUND PLANE
    //------------------------------------------------

    addRing(
        0.0f,
        0.0f
    );


    addRing(
        groundRadius,
        0.0f
    );



    //------------------------------------------------
    // 2) CURVED TRANSITION
    //------------------------------------------------
    //
    // Cuarto de esfera
    //
    //------------------------------------------------

    for(
        uint32_t i = 1;
        i <= heightSegments;
        ++i
    )
    {

        float t =
            static_cast<float>(i)
            /
            static_cast<float>(heightSegments);



        float angle =
            t *
            (
                CupulaConstants3D::PI * 0.5f
            );



        float radius =
            groundRadius
            +
            curveRadius *
            std::sin(angle);



        float height =
            curveRadius *
            (
                1.0f -
                std::cos(angle)
            );



        addRing(
            radius,
            height
        );

    }



    //------------------------------------------------
    // 3) HEMISPHERE
    //------------------------------------------------

    for(
        uint32_t i = 1;
        i <= heightSegments;
        ++i
    )
    {

        float t =
            static_cast<float>(i)
            /
            static_cast<float>(heightSegments);



        float phi =
            t *
            (
                CupulaConstants3D::PI * 0.5f
            );



        float radius =
            cupulaRadius *
            std::sin(phi);



        float height =
            curveRadius
            +
            cupulaRadius *
            std::cos(phi);



        addRing(
            radius,
            height
        );

    }



    //------------------------------------------------
    // INDICES
    //------------------------------------------------

    uint32_t ringSize =
        radialSegments + 1;



    for(
        uint32_t r = 0;
        r < rings - 1;
        ++r
    )
    {

        for(
            uint32_t i = 0;
            i < radialSegments;
            ++i
        )
        {

            uint32_t current =
                r *
                ringSize
                +
                i;


            uint32_t next =
                current
                +
                ringSize;



            // invertido porque estamos dentro

            indices.push_back(
                current
            );

            indices.push_back(
                current + 1
            );

            indices.push_back(
                next
            );



            indices.push_back(
                current + 1
            );

            indices.push_back(
                next + 1
            );

            indices.push_back(
                next
            );

        }

    }



    //------------------------------------------------
    // UPLOAD
    //------------------------------------------------

    mesh.upload(
        vertices,
        indices
    );

}