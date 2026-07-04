#pragma once

#include <cstdint>

struct BoardView
{
    float x;
    float y;
    float size;
    float squareSize;

    static BoardView compute(int screenW, int screenH)
    {
        BoardView v;

        v.size = screenH * 0.85f;
        v.squareSize = v.size / 8.0f;

        v.x = (screenW - v.size) * 0.5f;
        v.y = (screenH - v.size) * 0.5f;

        return v;
    }

    inline void squareToXY(uint8_t square, float& outX, float& outY) const
    {
        uint8_t row = square / 8;
        uint8_t col = square % 8;

        outX = x + col * squareSize;
        outY = y + row * squareSize;
    }
};