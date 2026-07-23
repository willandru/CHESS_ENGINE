#pragma once

namespace SceneConstants
{

    //------------------------------------------------
    // GLOBAL SCENE OFFSET
    //------------------------------------------------

    // Movimiento global de toda la escena de ajedrez
    // No afecta al HDRI ni al suelo
    constexpr float SCENE_VERTICAL_OFFSET = -0.30f;



    //------------------------------------------------
    // TABLE / SCENE HEIGHT
    //------------------------------------------------

    // Altura física de la mesa
    constexpr float TABLE_HEIGHT = 0.10f;



    //------------------------------------------------
    // CHESS BOARD
    //------------------------------------------------

    constexpr int BOARD_SQUARES = 8;


    constexpr int BOARD_CELL_COUNT =
        BOARD_SQUARES * BOARD_SQUARES;



    // Tamaño real de una casilla (6 cm)
    constexpr float SQUARE_SIZE = 0.06f;



    // Espesor del tablero
    constexpr float BOARD_THICKNESS = 0.015f;



    // Altura base del tablero
    constexpr float BOARD_HEIGHT =
        0.0f;



    constexpr float BOARD_SIZE =
        BOARD_SQUARES * SQUARE_SIZE;



    constexpr float HALF_BOARD_SIZE =
        BOARD_SIZE * 0.5f;



    //------------------------------------------------
    // CHESS PIECES
    //------------------------------------------------

    constexpr float PIECE_SCALE = 1.0f;



    // Altura donde empiezan las piezas
    constexpr float PIECE_HEIGHT =
        BOARD_HEIGHT +
        BOARD_THICKNESS;



    //------------------------------------------------
    // PIECE VERTICAL OFFSETS
    //------------------------------------------------

    constexpr float PAWN_OFFSET_Y = 0.0f;

    constexpr float KNIGHT_OFFSET_Y = 0.0f;

    constexpr float BISHOP_OFFSET_Y = 0.0f;

    constexpr float ROOK_OFFSET_Y = 0.0f;

    constexpr float QUEEN_OFFSET_Y = 0.0f;

    constexpr float KING_OFFSET_Y = 0.0f;



    //------------------------------------------------
    // HIGHLIGHTS
    //------------------------------------------------

    constexpr float HIGHLIGHT_OFFSET = 0.001f;


    constexpr float HIGHLIGHT_HEIGHT =
        PIECE_HEIGHT +
        HIGHLIGHT_OFFSET;



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

    constexpr float CAMERA_FIELD_OF_VIEW = 60.0f;


    constexpr float CAMERA_NEAR_PLANE = 0.01f;


    constexpr float CAMERA_FAR_PLANE = 100.0f;



    constexpr float CAMERA_OVERVIEW_POSITION_X = 0.0f;


    constexpr float CAMERA_OVERVIEW_POSITION_Y =
        1.8f +
        SCENE_VERTICAL_OFFSET;



    constexpr float CAMERA_OVERVIEW_POSITION_Z = 1.8f;



    constexpr float CAMERA_TARGET_X = 0.0f;


    constexpr float CAMERA_TARGET_Y =
        TABLE_HEIGHT +
        SCENE_VERTICAL_OFFSET;



    constexpr float CAMERA_TARGET_Z = 0.0f;



    //------------------------------------------------
    // ORBIT
    //------------------------------------------------

    constexpr float CAMERA_ORBIT_SENSITIVITY = 0.35f;



    //------------------------------------------------
    // ZOOM
    //------------------------------------------------

    constexpr float CAMERA_ZOOM_SPEED = 0.05f;


    constexpr float CAMERA_MIN_DISTANCE = 0.3f;


    constexpr float CAMERA_MAX_DISTANCE = 5.0f;



    //------------------------------------------------
    // PITCH
    //------------------------------------------------

    constexpr float CAMERA_MIN_PITCH = -89.0f;


    constexpr float CAMERA_MAX_PITCH = 89.0f;


}