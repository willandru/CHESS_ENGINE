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

    // Radio base de la geometría
    constexpr float RADIUS =
        30.0f;



    // Radio transición suelo-pared

    constexpr float CURVE_RADIUS =
        0.3f;



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
    // HDRI SETTINGS
    //------------------------------------------------

    constexpr float HDRI_EXPOSURE =
        1.0f;


    constexpr float HDRI_ROTATION =
        0.0f;



    //------------------------------------------------
    // HDRI PROJECTION
    //------------------------------------------------

    constexpr float HDRI_RADIUS =
        RADIUS;


    constexpr float HDRI_CAPTURE_HEIGHT =
        1.0f;



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