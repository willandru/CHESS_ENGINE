#pragma once

#include <cstdint>
#include "ChessTypes.h"

enum class PlayerSide : uint8_t
{
    White,
    Black
};

//====================================================
// CASTLING RIGHTS (4 BITS)
//====================================================
//
// bit 0 -> White Kingside
// bit 1 -> White Queenside
// bit 2 -> Black Kingside
// bit 3 -> Black Queenside
//
enum CastleRights : uint8_t
{
    WHITE_KINGSIDE  = 1 << 0,
    WHITE_QUEENSIDE = 1 << 1,
    BLACK_KINGSIDE  = 1 << 2,
    BLACK_QUEENSIDE = 1 << 3,

    ALL_CASTLING_RIGHTS =
        WHITE_KINGSIDE |
        WHITE_QUEENSIDE |
        BLACK_KINGSIDE |
        BLACK_QUEENSIDE
};

class GameState
{
public:

    GameState();

    //=========================================
    // STATE
    //=========================================
    void clear();
    void reset();

    //=========================================
    // BOARD
    //=========================================
    Piece getPiece(uint8_t square) const;
    void setPiece(uint8_t square, Piece piece);

    const Piece* getBoard() const;

    //=========================================
    // TURN
    //=========================================
    PlayerSide getTurn() const;
    void setTurn(PlayerSide side);
    void switchTurn();

    //=========================================
    // EN PASSANT
    //=========================================
    uint8_t getEnPassantSquare() const;
    void setEnPassantSquare(uint8_t square);

    void clearEnPassant();

    //=========================================
    // CASTLING RIGHTS
    //=========================================
    uint8_t getCastleRights() const;
    void setCastleRights(uint8_t rights);

    bool canCastleKingside(PlayerSide side) const;
    bool canCastleQueenside(PlayerSide side) const;

    void removeKingsideCastle(PlayerSide side);
    void removeQueensideCastle(PlayerSide side);
    void removeAllCastle(PlayerSide side);

    //=========================================
    // COORDINATES
    //=========================================
    static uint8_t getSquare(uint8_t row, uint8_t col);
    static uint8_t getRow(uint8_t square);
    static uint8_t getCol(uint8_t square);

    uint8_t findKing(PlayerSide side) const;


    //=========================================
    // FIFTY-MOVE RULE
    //=========================================

    uint16_t getHalfMoveClock() const;
    void setHalfMoveClock(uint16_t value);
    void resetHalfMoveClock();
    void incrementHalfMoveClock();
    

private:

    Piece board[64];

    PlayerSide turn;

    // Square objetivo para captura al paso.
    // 255 = no disponible.
    uint8_t enPassantSquare = 255;

    // Derechos de enroque.
    uint8_t castleRights = 0;

    // Regla de los 50 movimientos.
    // Cuenta medio-movimientos (ply)
    // desde el último movimiento de peón
    // o captura.
    uint16_t halfMoveClock = 0;


};