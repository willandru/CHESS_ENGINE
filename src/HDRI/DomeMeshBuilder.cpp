#include "DomeMeshBuilder.h"
#include "DomeConstants3D.h"

#include <glm/geometric.hpp>

#include <vector>
#include <cmath>

//====================================================
// BUILD HEMISPHERE
//====================================================

void DomeMeshBuilder::build(
    Mesh3D& mesh,
    float radius,
    uint32_t latitudeSegments,
    uint32_t longitudeSegments,
    const glm::vec3& color
)
{

    //------------------------------------------------
    // CPU DATA
    //------------------------------------------------

    std::vector<Vertex3D> vertices;

    std::vector<uint32_t> indices;



    //------------------------------------------------
    // HEMISPHERE VERTICES
    //------------------------------------------------

    for(
        uint32_t lat = 0;
        lat <= latitudeSegments;
        ++lat
    )
    {

        float v =
            static_cast<float>(lat)
            /
            static_cast<float>(
                latitudeSegments
            );



        //------------------------------------------------
        // 0° -> 90°
        //------------------------------------------------

        float phi =
            v *
            (
                DomeConstants3D::PI * 0.5f
            );



        float sinPhi =
            std::sin(phi);

        float cosPhi =
            std::cos(phi);



        for(
            uint32_t lon = 0;
            lon <= longitudeSegments;
            ++lon
        )
        {

            float u =
                static_cast<float>(lon)
                /
                static_cast<float>(
                    longitudeSegments
                );



            //------------------------------------------------
            // 0° -> 360°
            //------------------------------------------------

            float theta =
                u *
                (
                    2.0f *
                    DomeConstants3D::PI
                );



            float sinTheta =
                std::sin(theta);

            float cosTheta =
                std::cos(theta);



            //------------------------------------------------
            // POSITION
            //------------------------------------------------

            glm::vec3 position;

            position.x =
                radius *
                sinPhi *
                cosTheta;

            position.y =
                radius *
                cosPhi;

            position.z =
                radius *
                sinPhi *
                sinTheta;



            //------------------------------------------------
            // NORMAL
            //------------------------------------------------

            glm::vec3 normal =
                glm::normalize(
                    position
                );



            //------------------------------------------------
            // UV
            //------------------------------------------------

            glm::vec2 texCoord;

            texCoord.x = u;

            texCoord.y = 1.0f - v;



            //------------------------------------------------
            // VERTEX
            //------------------------------------------------

            Vertex3D vertex;

            vertex.position =
                position;

            vertex.normal =
                normal;

            vertex.texCoord =
                texCoord;

            vertex.color =
                color;



            vertices.push_back(
                vertex
            );

        }

    }



    //------------------------------------------------
    // INDICES
    //------------------------------------------------

    for(
        uint32_t lat = 0;
        lat < latitudeSegments;
        ++lat
    )
    {

        for(
            uint32_t lon = 0;
            lon < longitudeSegments;
            ++lon
        )
        {

            uint32_t current =
                lat *
                (longitudeSegments + 1)
                +
                lon;


            uint32_t next =
                current
                +
                longitudeSegments
                +
                1;



            //------------------------------------------------
            // TRIANGLE 1
            //------------------------------------------------

            indices.push_back(
                current
            );

            indices.push_back(
                next
            );

            indices.push_back(
                current + 1
            );



            //------------------------------------------------
            // TRIANGLE 2
            //------------------------------------------------

            indices.push_back(
                current + 1
            );

            indices.push_back(
                next
            );

            indices.push_back(
                next + 1
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



//====================================================
// BUILD GROUND DISK
//====================================================

//====================================================
// BUILD GROUND DISK
//====================================================

void DomeMeshBuilder::buildGroundDisk(
    Mesh3D& mesh,
    float radius,
    uint32_t segments,
    const glm::vec3& color
)
{

    //------------------------------------------------
    // CPU DATA
    //------------------------------------------------

    std::vector<Vertex3D> vertices;

    std::vector<uint32_t> indices;



    //------------------------------------------------
    // CENTER VERTEX
    //------------------------------------------------

    Vertex3D center;

    center.position =
    {
        0.0f,
        0.0f,
        0.0f
    };

    center.normal =
    {
        0.0f,
        1.0f,
        0.0f
    };

    center.texCoord =
    {
        0.5f,
        0.5f
    };

    center.color =
        color;

    vertices.push_back(
        center
    );



    //------------------------------------------------
    // OUTER RING
    //------------------------------------------------

    for(
        uint32_t i = 0;
        i <= segments;
        ++i
    )
    {

        float u =
            static_cast<float>(i)
            /
            static_cast<float>(
                segments
            );



        float theta =
            u *
            (
                2.0f *
                DomeConstants3D::PI
            );



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
            0.0f,
            z
        };

        vertex.normal =
        {
            0.0f,
            1.0f,
            0.0f
        };

        vertex.texCoord =
        {
            (x / radius + 1.0f) * 0.5f,
            (z / radius + 1.0f) * 0.5f
        };

        vertex.color =
            color;

        vertices.push_back(
            vertex
        );

    }



    //------------------------------------------------
    // TRIANGLES
    //------------------------------------------------

    for(
        uint32_t i = 1;
        i <= segments;
        ++i
    )
    {

        indices.push_back(
            0
        );

        indices.push_back(
            i
        );

        indices.push_back(
            i + 1
        );

    }



    //------------------------------------------------
    // UPLOAD
    //------------------------------------------------

    mesh.upload(
        vertices,
        indices
    );

}
