#pragma once

#include <cstdint>

#include "GameState.h"

class HumanAgent
{
public:

    HumanAgent();

    void onSquareClicked(
        const GameState& state,
        uint8_t square);

    bool hasSelection() const;

    uint8_t getSelectedSquare() const;
    Piece getSelectedPiece() const;

    void clearSelection();

private:

    bool selected;

    uint8_t selectedSquare;
    Piece selectedPiece;
};