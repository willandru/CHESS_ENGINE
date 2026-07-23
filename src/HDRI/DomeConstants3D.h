#pragma once

#include <glm/glm.hpp>


namespace DomeConstants3D
{

    //------------------------------------------------
    // MATHEMATICAL CONSTANTS
    //------------------------------------------------

    constexpr float PI =
        3.14159265358979323846f;



    //------------------------------------------------
    // DOME DIMENSIONS
    //------------------------------------------------

    constexpr float DOME_RADIUS = 20.0f;

    constexpr float GROUND_RADIUS = 500.0f;



    //------------------------------------------------
    // TESSELLATION
    //------------------------------------------------

    constexpr uint32_t LATITUDE_SEGMENTS = 32;

    constexpr uint32_t LONGITUDE_SEGMENTS = 64;



    //------------------------------------------------
    // DOME CENTER
    //------------------------------------------------

    constexpr float CENTER_X = 0.0f;

    constexpr float CENTER_Y = 0.0f;

    constexpr float CENTER_Z = 0.0f;



    //------------------------------------------------
    // DOME POSITION
    //------------------------------------------------

    constexpr float DOME_POS_X = CENTER_X;

    constexpr float DOME_POS_Y = CENTER_Y;

    constexpr float DOME_POS_Z = CENTER_Z;



    //------------------------------------------------
    // GROUND POSITION
    //------------------------------------------------

    // Suelo debajo de la mesa
    constexpr float GROUND_POS_X = 0.0f;

    constexpr float GROUND_POS_Y = 0.0f;

    constexpr float GROUND_POS_Z = 0.0f;



    //------------------------------------------------
    // DOME ROTATION
    //------------------------------------------------

    constexpr float DOME_ROT_X = 0.0f;

    constexpr float DOME_ROT_Y = 0.0f;

    constexpr float DOME_ROT_Z = 0.0f;



    //------------------------------------------------
    // GROUND ROTATION
    //------------------------------------------------

    constexpr float GROUND_ROT_X = 0.0f;

    constexpr float GROUND_ROT_Y = 0.0f;

    constexpr float GROUND_ROT_Z = 0.0f;



    //------------------------------------------------
    // COLORS
    //------------------------------------------------

    inline const glm::vec3 DOME_COLOR =
    {
        0.75f,
        0.85f,
        1.0f
    };



    inline const glm::vec3 GROUND_COLOR =
    {
        0.35f,
        0.35f,
        0.35f
    };


}