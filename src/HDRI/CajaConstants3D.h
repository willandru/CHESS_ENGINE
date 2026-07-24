#pragma once

#include <glm/glm.hpp>

namespace CajaConstants3D
{

    //------------------------------------------------
    // ROOM DIMENSIONS
    //------------------------------------------------

    // Dimensiones principales de la caja
    // Cambiar estas modifica el tamaño completo

    constexpr float WIDTH =
        8.0f;      // ancho X

    constexpr float LENGTH =
        8.0f;      // largo Z

    constexpr float HEIGHT =
        4.0f;       // alto Y



    //------------------------------------------------
    // ROOM LIMITS
    //------------------------------------------------

    constexpr float LEFT =
        -WIDTH * 0.5f;


    constexpr float RIGHT =
         WIDTH * 0.5f;


    constexpr float FRONT =
         LENGTH * 0.5f;


    constexpr float BACK =
        -LENGTH * 0.5f;


    constexpr float FLOOR =
        0.0f;


    constexpr float CEILING =
        HEIGHT;



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



    //------------------------------------------------
    // HDRI PROJECTION
    //------------------------------------------------

    constexpr float HDRI_HEIGHT =
        1.8f;

}