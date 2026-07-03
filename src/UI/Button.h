#pragma once

#include <functional>
#include "Shader.h"

class Button
{
public:
    Button();
    Button(float x, float y, float width, float height, const char* text);

    void setOnClick(std::function<void()> fn);

    void update(float mouseX, float mouseY, bool clicked);
    void render(Shader& shader);

private:
    float x, y;
    float width, height;

    const char* text;
    bool hover;

    std::function<void()> onClick;
};