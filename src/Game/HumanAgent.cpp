#include "HumanAgent.h"

#include <iostream>

HumanAgent::HumanAgent()
{
    clearSelection();
}

void HumanAgent::onSquareClicked(
    const GameState& state,
    uint8_t square)
{
    selected = true;

    selectedSquare = square;
    selectedPiece = state.getPiece(square);

    std::cout
        << "=================================\n"
        << "HumanAgent Selection\n"
        << "Square : " << static_cast<int>(selectedSquare) << '\n'
        << "Row    : " << static_cast<int>(GameState::getRow(selectedSquare)) << '\n'
        << "Col    : " << static_cast<int>(GameState::getCol(selectedSquare)) << '\n'
        << "Piece  : " << static_cast<int>(selectedPiece) << '\n'
        << "=================================\n";
}

bool HumanAgent::hasSelection() const
{
    return selected;
}

uint8_t HumanAgent::getSelectedSquare() const
{
    return selectedSquare;
}

Piece HumanAgent::getSelectedPiece() const
{
    return selectedPiece;
}

void HumanAgent::clearSelection()
{
    selected = false;
    selectedSquare = 0;
    selectedPiece = EMPTY;
}