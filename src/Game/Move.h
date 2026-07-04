#pragma once

#include <cstdint>
#include "ChessTypes.h"

//====================================================
// Move (representación compacta para IA / engine)
//====================================================
//
// from / to -> índice 0..63 (uint8_t)
// flags     -> información extra (promoción, captura, etc.)
//====================================================

struct Move
{
    uint8_t from;   // 0..63
    uint8_t to;     // 0..63

    uint8_t flags;  // metadata (bitmask)

    Piece captured; // pieza capturada (si existe)
    Piece promo;    // promoción (si aplica)

    //-------------------------------
    // Flags (bitmask)
    //-------------------------------
    enum Flag : uint8_t
    {
        QUIET       = 0,
        CAPTURE     = 1 << 0,
        PROMOTION   = 1 << 1,
        EN_PASSANT  = 1 << 2,
        CASTLING    = 1 << 3
    };

    //====================================================
    // Helpers
    //====================================================

    Move()
        : from(0),
          to(0),
          flags(QUIET),
          captured(EMPTY),
          promo(EMPTY)
    {
    }

    Move(uint8_t f, uint8_t t)
        : from(f),
          to(t),
          flags(QUIET),
          captured(EMPTY),
          promo(EMPTY)
    {
    }

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

    inline void setFlag(Flag f)
    {
        flags |= f;
    }

    inline void clearFlag(Flag f)
    {
        flags &= ~f;
    }
};