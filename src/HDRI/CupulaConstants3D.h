#pragma once

#include <glm/glm.hpp>


namespace CupulaConstants3D
{

    //------------------------------------------------
    // MATHEMATICAL CONSTANTS
    //------------------------------------------------

    constexpr float PI =
        3.14159265358979323846f;



    //------------------------------------------------
    // MAIN RADIUS
    //------------------------------------------------
    //
    // Radio global de la cúpula.
    // Es el mismo sistema radial para:
    // suelo + transición + cielo.
    //
    //------------------------------------------------

    constexpr float CUPULA_RADIUS = 100.0f;



    //------------------------------------------------
    // GROUND AREA
    //------------------------------------------------
    //
    // Radio del plano donde estará el tablero.
    //
    //------------------------------------------------

    constexpr float GROUND_RADIUS = 10.0f;



    //------------------------------------------------
    // CURVE TRANSITION
    //------------------------------------------------
    //
    // Zona curva que une suelo y cielo.
    //
    //------------------------------------------------

    constexpr float CURVE_RADIUS = 20.0f;



    //------------------------------------------------
    // TESSELLATION
    //------------------------------------------------

    constexpr uint32_t RADIAL_SEGMENTS = 128;

    constexpr uint32_t HEIGHT_SEGMENTS = 64;



    //------------------------------------------------
    // POSITION
    //------------------------------------------------

    constexpr float CENTER_X = 0.0f;

    constexpr float CENTER_Y = 0.0f;

    constexpr float CENTER_Z = 0.0f;



    //------------------------------------------------
    // ROTATION
    //------------------------------------------------

    constexpr float ROT_X = 0.0f;

    constexpr float ROT_Y = 0.0f;

    constexpr float ROT_Z = 0.0f;



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