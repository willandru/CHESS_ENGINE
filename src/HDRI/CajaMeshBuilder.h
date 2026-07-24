#pragma once

#include "CajaMesh3D.h"

#include <glm/glm.hpp>

#include <vector>



//====================================================
// CAJA MESH BUILDER
//====================================================

class CajaMeshBuilder
{

public:

    //------------------------------------------------
    // BUILD
    //------------------------------------------------

    static void build(
        CajaMesh3D& caja,

        float left,
        float right,

        float front,
        float back,

        float floor,
        float ceiling,

        const glm::vec3& color
    );



private:

    //------------------------------------------------
    // HELPERS
    //------------------------------------------------

    static void addQuad(

        std::vector<Vertex3D>& vertices,
        std::vector<uint32_t>& indices,

        const glm::vec3& v0,
        const glm::vec3& v1,
        const glm::vec3& v2,
        const glm::vec3& v3,

        const glm::vec3& normal,
        const glm::vec3& color

    );

};