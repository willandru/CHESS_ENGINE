#pragma once

#include <cstdint>

//====================================================
// InitialPosition
//====================================================
//
// Describe la posición inicial estándar del ajedrez.
//
// Contiene únicamente constantes.
// No implementa lógica.
//====================================================

class InitialPosition
{
public:

    //================================================
    // WHITE PIECES
    //================================================

    static constexpr uint8_t WHITE_ROOK_QUEENSIDE   = 56;
    static constexpr uint8_t WHITE_KNIGHT_QUEENSIDE = 57;
    static constexpr uint8_t WHITE_BISHOP_QUEENSIDE = 58;
    static constexpr uint8_t WHITE_QUEEN            = 59;
    static constexpr uint8_t WHITE_KING             = 60;
    static constexpr uint8_t WHITE_BISHOP_KINGSIDE  = 61;
    static constexpr uint8_t WHITE_KNIGHT_KINGSIDE  = 62;
    static constexpr uint8_t WHITE_ROOK_KINGSIDE    = 63;

    //================================================
    // BLACK PIECES
    //================================================

    static constexpr uint8_t BLACK_ROOK_QUEENSIDE   = 0;
    static constexpr uint8_t BLACK_KNIGHT_QUEENSIDE = 1;
    static constexpr uint8_t BLACK_BISHOP_QUEENSIDE = 2;
    static constexpr uint8_t BLACK_QUEEN            = 3;
    static constexpr uint8_t BLACK_KING             = 4;
    static constexpr uint8_t BLACK_BISHOP_KINGSIDE  = 5;
    static constexpr uint8_t BLACK_KNIGHT_KINGSIDE  = 6;
    static constexpr uint8_t BLACK_ROOK_KINGSIDE    = 7;

    //================================================
    // PAWN ROWS
    //================================================

    static constexpr uint8_t WHITE_PAWN_ROW = 6;
    static constexpr uint8_t BLACK_PAWN_ROW = 1;

    //================================================
    // PROMOTION ROWS
    //================================================

    static constexpr uint8_t WHITE_PROMOTION_ROW = 0;
    static constexpr uint8_t BLACK_PROMOTION_ROW = 7;
};