#pragma once

#include "Mesh3D.h"

#include <glm/glm.hpp>

class PlaneMeshBuilder
{
public:

    //------------------------------------------------
    // BUILD
    //------------------------------------------------

    static void build(
        Mesh3D& mesh,
        float width,
        float height,
        const glm::vec3& color
    );

};