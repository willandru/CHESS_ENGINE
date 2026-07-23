#pragma once

#include "Mesh3D.h"

#include <glm/glm.hpp>

#include <cstdint>


class CupulaMeshBuilder
{

public:


    //------------------------------------------------
    // BUILD COMPLETE CUPULA
    //------------------------------------------------
    //
    // Genera:
    //
    //  - suelo plano
    //  - transición curva
    //  - hemisferio
    //
    //------------------------------------------------

    static void build(
        Mesh3D& mesh,
        float cupulaRadius,
        float groundRadius,
        float curveRadius,
        uint32_t radialSegments,
        uint32_t heightSegments,
        const glm::vec3& color
    );


};