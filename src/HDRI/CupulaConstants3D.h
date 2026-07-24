#pragma once

#include <glm/glm.hpp>
#include <cstdint>


namespace CupulaConstants3D
{

    //------------------------------------------------
    // MATHEMATICS
    //------------------------------------------------

    constexpr float PI =
        3.14159265358979323846f;



    //------------------------------------------------
    // ENVIRONMENT DIMENSIONS
    //------------------------------------------------

    // Radio único del entorno
    // usado por suelo y cúpula

    constexpr float RADIUS =
        200.0f;



    // Radio de la unión curva
    // entre plano y pared/cúpula

    constexpr float CURVE_RADIUS =
        1.0f;



    //------------------------------------------------
    // PROFILE TESSELLATION
    //------------------------------------------------

    constexpr uint32_t CURVE_SEGMENTS =
        32;



    constexpr uint32_t DOME_SEGMENTS =
        128;



    //------------------------------------------------
    // REVOLUTION TESSELLATION
    //------------------------------------------------

    constexpr uint32_t RADIAL_SEGMENTS =
        256;



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

    inline const glm::vec3 CUPULA_COLOR =
    {
        1.0f,
        1.0f,
        1.0f
    };

}