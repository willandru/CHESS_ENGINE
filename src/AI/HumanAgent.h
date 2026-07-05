#pragma once

#include <cstdint>

class HumanAgent
{
public:

    HumanAgent();

    void onSquareClicked(uint8_t square);

    bool hasClick() const;

    uint8_t getClickedSquare() const;

    void clear();

private:

    bool clicked = false;

    uint8_t clickedSquare = 0;
};