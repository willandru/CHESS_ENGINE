#pragma once

#include "CajaMesh3D.h"

#include <glm/glm.hpp>


class CajaMeshBuilder
{

public:


    //------------------------------------------------
    // BUILD BOX
    //------------------------------------------------

    static void build(
        CajaMesh3D& caja,

        const glm::vec3& dimensions,

        const glm::vec3& color
    );


};