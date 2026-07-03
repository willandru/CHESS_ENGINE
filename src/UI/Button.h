#pragma once

#include <functional>
#include <string>

#include "Texture.h"

class Shader;

class Button
{
public:
    Button();
    Button(float x, float y, float width, float height, const char* text);

    void setPosition(float x, float y);
    void setSize(float width, float height);

    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    void setOnClick(std::function<void()> fn);

    void setTexture(const char* path);

    void update(float mouseX, float mouseY, bool clicked);
    void render(Shader& shader);

private:
    bool contains(float px, float py) const;

private:
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    const char* text = "";

    bool hover = false;
    bool useTexture = false;
    bool textureLoaded = false;

    Texture texture;
    std::function<void()> onClick;
};