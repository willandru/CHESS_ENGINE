#pragma once

#include <cstdint>

enum Piece : uint8_t
{
    EMPTY = 0,

    WHITE_PAWN,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_ROOK,
    WHITE_QUEEN,
    WHITE_KING,

    BLACK_PAWN,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_ROOK,
    BLACK_QUEEN,
    BLACK_KING
};

inline bool isWhite(Piece p)
{
    return p >= WHITE_PAWN &&
           p <= WHITE_KING;
}

inline bool isBlack(Piece p)
{
    return p >= BLACK_PAWN &&
           p <= BLACK_KING;
}

inline bool isEmpty(Piece p)
{
    return p == EMPTY;
}