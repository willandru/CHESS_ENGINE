#pragma once

#include <cstdint>

#include "ChessTypes.h"

class GameState
{
public:

    GameState();

    //----------------------------------------
    // Estado
    //----------------------------------------

    void reset();

    //----------------------------------------
    // Mouse
    //----------------------------------------

    void onMouseClick(
        float mouseX,
        float mouseY);

    //----------------------------------------
    // Board
    //----------------------------------------

    Piece getPiece(uint8_t square) const;

    void setPiece(
        uint8_t square,
        Piece piece);

    const Piece* getBoard() const;

    //----------------------------------------
    // Selection
    //----------------------------------------

    bool hasSelection() const;

    uint8_t getSelectedSquare() const;

    //----------------------------------------
    // Coordinates
    //----------------------------------------

    static uint8_t getSquare(
        uint8_t row,
        uint8_t col);

    static uint8_t getRow(
        uint8_t square);

    static uint8_t getCol(
        uint8_t square);

private:

    //----------------------------------------
    // Helpers
    //----------------------------------------

    bool mouseToSquare(
        float mouseX,
        float mouseY,
        uint8_t& row,
        uint8_t& col,
        uint8_t& square) const;

    bool hasPiece(
        uint8_t square) const;

    void selectPiece(
        uint8_t square);

    void moveSelectedPiece(
        uint8_t destination);

private:

    Piece board[64];

    bool selected = false;

    uint8_t selectedSquare = 0;
};