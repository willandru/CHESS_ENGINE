#pragma once

#include "Mesh3D.h"

#include <glm/glm.hpp>

#include <cstdint>

class DomeMeshBuilder
{

public:

    //------------------------------------------------
    // HEMISPHERE
    //------------------------------------------------

    static void build(
        Mesh3D& mesh,
        float radius,
        uint32_t latitudeSegments,
        uint32_t longitudeSegments,
        const glm::vec3& color
    );



    //------------------------------------------------
    // GROUND DISK
    //------------------------------------------------

    static void buildGroundDisk(
        Mesh3D& mesh,
        float radius,
        uint32_t segments,
        const glm::vec3& color
    );

};