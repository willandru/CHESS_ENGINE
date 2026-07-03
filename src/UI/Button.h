#pragma once

#include <functional>

class Shader;

class Button
{
public:

    Button();

    Button(float x,
           float y,
           float width,
           float height,
           const char* text);

    void setOnClick(std::function<void()> callback);

    void update(float mouseX,
                float mouseY,
                bool clicked);

    void render(Shader& shader);

private:

    float x;
    float y;
    float width;
    float height;

    const char* text;

    bool hover;

    std::function<void()> onClick;
};