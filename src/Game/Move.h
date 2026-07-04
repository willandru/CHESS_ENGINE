#pragma once

#include <cstdint>
#include "ChessTypes.h"

//====================================================
// Move (representación compacta del engine)
//====================================================
//
// from / to  -> índice 0..63
// flags      -> tipo de jugada (bitmask)
// captured   -> pieza capturada (si aplica)
// promo      -> pieza de promoción (si aplica)
//====================================================

struct Move
{
    uint8_t from;
    uint8_t to;

    uint8_t flags;

    Piece captured;
    Piece promo;

    //====================================================
    // FLAGS (bitmask)
    //====================================================

    enum Flag : uint8_t
    {
        CAPTURE     = 1 << 0,
        PROMOTION   = 1 << 1,
        EN_PASSANT  = 1 << 2,
        CASTLING    = 1 << 3
    };

    //====================================================
    // CONSTRUCTORS
    //====================================================

    Move()
        : from(0),
          to(0),
          flags(0),
          captured(EMPTY),
          promo(EMPTY)
    {}

    Move(uint8_t f, uint8_t t)
        : from(f),
          to(t),
          flags(0),
          captured(EMPTY),
          promo(EMPTY)
    {}

    Move(uint8_t f, uint8_t t, uint8_t fl)
        : from(f),
          to(t),
          flags(fl),
          captured(EMPTY),
          promo(EMPTY)
    {}

    //====================================================
    // QUERY HELPERS
    //====================================================

    inline bool isCapture() const
    {
        return flags & CAPTURE;
    }

    inline bool isPromotion() const
    {
        return flags & PROMOTION;
    }

    inline bool isEnPassant() const
    {
        return flags & EN_PASSANT;
    }

    inline bool isCastling() const
    {
        return flags & CASTLING;
    }

    inline bool isQuiet() const
    {
        return flags == 0;
    }

    //====================================================
    // FLAG OPERATIONS
    //====================================================

    inline void setFlag(Flag f)
    {
        flags |= f;
    }

    inline void clearFlag(Flag f)
    {
        flags &= ~f;
    }
};