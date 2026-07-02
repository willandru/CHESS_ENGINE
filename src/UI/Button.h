#pragma once

#include <functional>

class Button {
public:
    Button();
    Button(float x, float y, float w, float h, const char* text);

    void setOnClick(std::function<void()> fn);
    void update(float mx, float my, bool clicked);
    void render();

private:
    float x, y, w, h;
    const char* text;
    bool hover;
    std::function<void()> onClick;
};