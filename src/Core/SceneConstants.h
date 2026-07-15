#pragma once

namespace SceneConstants
{
    //------------------------------------------------
    // CHESS BOARD
    //------------------------------------------------

    constexpr int BOARD_SQUARES = 8;

    constexpr int BOARD_CELL_COUNT =
        BOARD_SQUARES * BOARD_SQUARES;

    constexpr float SQUARE_SIZE = 1.0f;

    // Espesor físico del tablero
    constexpr float BOARD_THICKNESS = 0.25f;

    // Posición del tablero en el mundo (eje Y)
    constexpr float BOARD_HEIGHT = 4.0f;

    constexpr float BOARD_SIZE =
        BOARD_SQUARES * SQUARE_SIZE;

    constexpr float HALF_BOARD_SIZE =
        BOARD_SIZE * 0.5f;


    //------------------------------------------------
    // CHESS PIECES
    //------------------------------------------------

    constexpr float PIECE_SCALE = 0.8f;

    // Base de las piezas (encima del tablero)
    constexpr float PIECE_HEIGHT =
        BOARD_HEIGHT + BOARD_THICKNESS;



    //------------------------------------------------
    // HIGHLIGHTS
    //------------------------------------------------

    constexpr float HIGHLIGHT_OFFSET = 0.001f;

    constexpr float HIGHLIGHT_HEIGHT =
        PIECE_HEIGHT + HIGHLIGHT_OFFSET;



    //------------------------------------------------
    // BOARD TRANSFORM
    //------------------------------------------------

    constexpr float BOARD_POSITION_X = 0.0f;
    constexpr float BOARD_POSITION_Z = 0.0f;

    constexpr float BOARD_ROTATION_X = 0.0f;
    constexpr float BOARD_ROTATION_Y = 0.0f;
    constexpr float BOARD_ROTATION_Z = 0.0f;

    constexpr float BOARD_SCALE_X = 1.0f;
    constexpr float BOARD_SCALE_Y = 1.0f;
    constexpr float BOARD_SCALE_Z = 1.0f;



    //------------------------------------------------
    // PIECE COLORS
    //------------------------------------------------

    constexpr float WHITE_PIECE_COLOR_R = 0.90f;
    constexpr float WHITE_PIECE_COLOR_G = 0.90f;
    constexpr float WHITE_PIECE_COLOR_B = 0.90f;

    constexpr float BLACK_PIECE_COLOR_R = 0.05f;
    constexpr float BLACK_PIECE_COLOR_G = 0.05f;
    constexpr float BLACK_PIECE_COLOR_B = 0.05f;



    //------------------------------------------------
    // CAMERA
    //------------------------------------------------

    // Projection

    constexpr float CAMERA_FIELD_OF_VIEW = 60.0f;

    constexpr float CAMERA_NEAR_PLANE = 0.1f;

    constexpr float CAMERA_FAR_PLANE = 500.0f;



    // Initial Overview Position

    constexpr float CAMERA_OVERVIEW_POSITION_X = 0.0f;

    constexpr float CAMERA_OVERVIEW_POSITION_Y = 8.0f;

    constexpr float CAMERA_OVERVIEW_POSITION_Z = 10.0f;



    // Initial target

    constexpr float CAMERA_TARGET_X = 0.0f;

    constexpr float CAMERA_TARGET_Y = 0.0f;

    constexpr float CAMERA_TARGET_Z = 0.0f;



    // Mouse orbit

    constexpr float CAMERA_ORBIT_SENSITIVITY = 0.35f;



    // Zoom

    constexpr float CAMERA_ZOOM_SPEED = 0.5f;

    constexpr float CAMERA_MIN_DISTANCE = 2.0f;

    constexpr float CAMERA_MAX_DISTANCE = 25.0f;



    // Vertical rotation limits

    constexpr float CAMERA_MIN_PITCH = -89.0f;

    constexpr float CAMERA_MAX_PITCH = 89.0f;

}