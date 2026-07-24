#pragma once

#include "Mesh3D.h"

#include <glm/glm.hpp>

#include <vector>
#include <cstdint>


class CupulaMeshBuilder
{

public:


    //------------------------------------------------
    // BUILD REVOLUTION MESH
    //------------------------------------------------

    static void build(
        Mesh3D& mesh,

        const std::vector<glm::vec2>& profile,

        uint32_t radialSegments,

        const glm::vec3& color
    );


};