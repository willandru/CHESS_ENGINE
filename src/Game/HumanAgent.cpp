#include "HumanAgent.h"

#include <iostream>

HumanAgent::HumanAgent()
{
    clear();
}

void HumanAgent::onSquareClicked(uint8_t square)
{
    clicked = true;
    clickedSquare = square;

    std::cout
        << "=================================\n"
        << "HumanAgent Click\n"
        << "Square : " << static_cast<int>(clickedSquare) << '\n'
        << "Row    : " << static_cast<int>(clickedSquare / 8) << '\n'
        << "Col    : " << static_cast<int>(clickedSquare % 8) << '\n'
        << "=================================\n";
}

bool HumanAgent::hasClick() const
{
    return clicked;
}

uint8_t HumanAgent::getClickedSquare() const
{
    return clickedSquare;
}

void HumanAgent::clear()
{
    clicked = false;
    clickedSquare = 0;
}