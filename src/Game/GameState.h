#pragma once

#include <cstdint>

#include "ChessTypes.h"

enum class PlayerSide : uint8_t
{
    White,
    Black
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
    // COORDINATES
    //=========================================

    static uint8_t getSquare(uint8_t row, uint8_t col);
    static uint8_t getRow(uint8_t square);
    static uint8_t getCol(uint8_t square);

private:

    Piece board[64];
    PlayerSide turn;
};