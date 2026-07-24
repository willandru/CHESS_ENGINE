#include "CupulaMeshBuilder.h"

#include <glm/gtc/constants.hpp>

#include <cmath>
#include <vector>



//====================================================
// BUILD
//====================================================

void CupulaMeshBuilder::build(
    Mesh3D& mesh,

    const std::vector<glm::vec2>& profile,

    uint32_t radialSegments,

    const glm::vec3& color
)
{

    if(profile.size() < 2)
    {
        return;
    }



    //------------------------------------------------
    // BUFFERS
    //------------------------------------------------

    std::vector<Vertex3D> vertices;

    std::vector<uint32_t> indices;



    const uint32_t profileSize =
        static_cast<uint32_t>(
            profile.size()
        );



    //------------------------------------------------
    // VERTICES
    //------------------------------------------------

    for(uint32_t r = 0;
        r < radialSegments;
        ++r)
    {

        float u =
            static_cast<float>(r) /
            static_cast<float>(radialSegments);



        float angle =
            glm::two_pi<float>() *
            u;



        float cs =
            std::cos(angle);



        float sn =
            std::sin(angle);



        for(uint32_t i = 0;
            i < profileSize;
            ++i)
        {

            glm::vec2 point =
                profile[i];



            Vertex3D vertex;



            //------------------------------------------------
            // POSITION
            //------------------------------------------------

            vertex.position =
            {
                point.x * cs,
                point.y,
                point.x * sn
            };



            //------------------------------------------------
            // PROFILE TANGENT
            //------------------------------------------------

            glm::vec2 tangent;


            if(i == 0)
            {

                tangent =
                    profile[1] -
                    profile[0];

            }
            else if(i == profileSize - 1)
            {

                tangent =
                    profile[i] -
                    profile[i-1];

            }
            else
            {

                tangent =
                    profile[i+1] -
                    profile[i-1];

            }



            tangent =
                glm::normalize(
                    tangent
                );



            //------------------------------------------------
            // NORMAL
            //------------------------------------------------

            glm::vec2 normal2D =
            {
                -tangent.y,
                 tangent.x
            };



            glm::vec3 normal =
            {
                normal2D.x * cs,
                normal2D.y,
                normal2D.x * sn
            };



            // interior surface
            vertex.normal =
                glm::normalize(
                    -normal
                );



            //------------------------------------------------
            // UV
            //------------------------------------------------

            vertex.texCoord =
            {
                u,

                static_cast<float>(i) /
                static_cast<float>(
                    profileSize - 1
                )
            };



            //------------------------------------------------
            // COLOR
            //------------------------------------------------

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

    for(uint32_t r = 0;
        r < radialSegments;
        ++r)
    {

        uint32_t next =
        (r + 1) % radialSegments;



        for(uint32_t i = 0;
            i < profileSize - 1;
            ++i)
        {

            uint32_t a =
                r * profileSize + i;


            uint32_t b =
                next * profileSize + i;


            uint32_t c =
                next * profileSize + i + 1;


            uint32_t d =
                r * profileSize + i + 1;



            //------------------------------------------------
            // INSIDE WINDING
            //------------------------------------------------

            indices.push_back(a);
            indices.push_back(c);
            indices.push_back(b);


            indices.push_back(a);
            indices.push_back(d);
            indices.push_back(c);

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