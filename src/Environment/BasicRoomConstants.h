#pragma once

#include <glm/glm.hpp>


namespace BasicRoomConstants
{

    //------------------------------------------------
    // ROOM DIMENSIONS
    //------------------------------------------------

    constexpr float ROOM_WIDTH  = 120.0f;

    constexpr float ROOM_HEIGHT = 20.0f;

    constexpr float ROOM_DEPTH  = 120.0f;



    //------------------------------------------------
    // ROOM CENTER
    //------------------------------------------------

    constexpr float ROOM_CENTER_X = 0.0f;

    constexpr float ROOM_CENTER_Y = 0.0f;

    constexpr float ROOM_CENTER_Z = 0.0f;



    //------------------------------------------------
    // DERIVED DIMENSIONS
    //------------------------------------------------

    constexpr float HALF_ROOM_WIDTH =
        ROOM_WIDTH * 0.5f;


    constexpr float HALF_ROOM_DEPTH =
        ROOM_DEPTH * 0.5f;


    constexpr float HALF_ROOM_HEIGHT =
        ROOM_HEIGHT * 0.5f;



    //------------------------------------------------
    // PANEL ROTATIONS
    //------------------------------------------------

    constexpr float FLOOR_ROT_X = -90.0f;
    constexpr float FLOOR_ROT_Y = 0.0f;
    constexpr float FLOOR_ROT_Z = 0.0f;


    constexpr float CEILING_ROT_X = 90.0f;
    constexpr float CEILING_ROT_Y = 0.0f;
    constexpr float CEILING_ROT_Z = 0.0f;


    constexpr float NORTH_WALL_ROT_Y = 180.0f;

    constexpr float SOUTH_WALL_ROT_Y = 0.0f;

    constexpr float EAST_WALL_ROT_Y = -90.0f;

    constexpr float WEST_WALL_ROT_Y = 90.0f;



    //------------------------------------------------
    // PANEL POSITIONS
    //------------------------------------------------

    constexpr float FLOOR_Y = 0.0f;

    constexpr float CEILING_Y =
        ROOM_HEIGHT;


    constexpr float WALL_CENTER_Y =
        ROOM_HEIGHT * 0.5f;



    //------------------------------------------------
    // COLORS
    //------------------------------------------------

    inline const glm::vec3 WALL_COLOR =
    {
        0.88f,
        0.87f,
        0.82f
    };


    inline const glm::vec3 FLOOR_COLOR =
    {
        0.55f,
        0.40f,
        0.28f
    };


    inline const glm::vec3 CEILING_COLOR =
    {
        0.95f,
        0.95f,
        0.95f
    };

}