#pragma once

#include <cstdint>
#include "ChessTypes.h"

//====================================================
// Move
//====================================================
//
// Representa una jugada del motor.
//
// Contiene toda la información necesaria para:
//
//  • ejecutar un movimiento
//  • deshacer un movimiento
//
// No pertenece a la IA.
// No representa un nodo del árbol.
//====================================================

struct Move
{
    //------------------------------------------------
    // MOVE
    //------------------------------------------------

    uint8_t from;
    uint8_t to;

    //------------------------------------------------
    // TYPE
    //------------------------------------------------

    uint8_t flags;

    //------------------------------------------------
    // EXECUTION DATA
    //------------------------------------------------

    Piece captured;
    Piece promo;

    //------------------------------------------------
    // UNDO DATA
    //------------------------------------------------

    uint8_t previousEnPassant;

    //------------------------------------------------
    // FLAGS
    //------------------------------------------------

    enum Flag : uint8_t
    {
        CAPTURE    = 1 << 0,
        PROMOTION  = 1 << 1,
        EN_PASSANT = 1 << 2,
        CASTLING   = 1 << 3
    };

    //------------------------------------------------
    // CONSTRUCTORS
    //------------------------------------------------

    Move()
        : from(0),
          to(0),
          flags(0),
          captured(EMPTY),
          promo(EMPTY),
          previousEnPassant(255)
    {
    }

    Move(
        uint8_t f,
        uint8_t t)
        : from(f),
          to(t),
          flags(0),
          captured(EMPTY),
          promo(EMPTY),
          previousEnPassant(255)
    {
    }

    Move(
        uint8_t f,
        uint8_t t,
        uint8_t fl)
        : from(f),
          to(t),
          flags(fl),
          captured(EMPTY),
          promo(EMPTY),
          previousEnPassant(255)
    {
    }

    //------------------------------------------------
    // QUERY
    //------------------------------------------------

    bool isCapture() const
    {
        return (flags & CAPTURE) != 0;
    }

    bool isPromotion() const
    {
        return (flags & PROMOTION) != 0;
    }

    bool isEnPassant() const
    {
        return (flags & EN_PASSANT) != 0;
    }

    bool isCastling() const
    {
        return (flags & CASTLING) != 0;
    }

    bool isQuiet() const
    {
        return flags == 0;
    }

    //------------------------------------------------
    // FLAGS
    //------------------------------------------------

    void setFlag(Flag flag)
    {
        flags |= flag;
    }

    void clearFlag(Flag flag)
    {
        flags &= ~flag;
    }
};