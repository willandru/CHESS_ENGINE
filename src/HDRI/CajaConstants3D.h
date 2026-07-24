#pragma once

#include <glm/glm.hpp>

namespace CajaConstants3D
{

    //------------------------------------------------
    // ROOM LIMITS
    //------------------------------------------------

    constexpr float LEFT =
        -6.0f;

    constexpr float RIGHT =
         6.0f;

    constexpr float FRONT =
         6.0f;

    constexpr float BACK =
        -6.0f;

    constexpr float FLOOR =
        -2.0f;

    constexpr float CEILING =
         2.0f;



    //------------------------------------------------
    // ROOM CENTER
    //------------------------------------------------

    constexpr glm::vec3 CENTER =
    {
        0.0f,
        0.0f,
        0.0f
    };



    //------------------------------------------------
    // ROOM COLOR
    //------------------------------------------------

    constexpr glm::vec3 COLOR =
    {
        1.0f,
        1.0f,
        1.0f
    };



    //------------------------------------------------
    // HDRI
    //------------------------------------------------

    constexpr float HDRI_EXPOSURE =
        1.0f;

    constexpr float HDRI_ROTATION =
        0.0f;

}