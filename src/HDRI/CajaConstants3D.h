#pragma once

#include <glm/glm.hpp>
#include <cstdint>


namespace CajaConstants3D
{

    //------------------------------------------------
    // MATHEMATICS
    //------------------------------------------------

    constexpr float PI =
        3.14159265358979323846f;



    //------------------------------------------------
    // ENVIRONMENT DIMENSIONS
    //------------------------------------------------

    // Dimensiones del volumen cerrado

    constexpr float WIDTH =
        60.0f;


    constexpr float HEIGHT =
        30.0f;


    constexpr float DEPTH =
        60.0f;



    //------------------------------------------------
    // FACE TESSELLATION
    //------------------------------------------------

    // Subdivisión de las caras
    // permite aumentar resolución futura

    constexpr uint32_t FACE_SEGMENTS =
        1;



    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    constexpr float CENTER_X =
        0.0f;


    constexpr float CENTER_Y =
        0.0f;


    constexpr float CENTER_Z =
        0.0f;



    constexpr float ROT_X =
        0.0f;


    constexpr float ROT_Y =
        0.0f;


    constexpr float ROT_Z =
        0.0f;



    //------------------------------------------------
    // COLOR
    //------------------------------------------------

    inline const glm::vec3 CAJA_COLOR =
    {
        1.0f,
        1.0f,
        1.0f
    };

}