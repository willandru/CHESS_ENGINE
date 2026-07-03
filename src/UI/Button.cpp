#include "Button.h"
#include "Renderer.h"
#include "Shader.h"

Button::Button()
{
    useTexture = false;
    textureLoaded = false;
}

Button::Button(float x, float y, float width, float height, const char* text)
{
    setPosition(x, y);
    setSize(width, height);

    this->text = text;

    useTexture = false;
    textureLoaded = false;
}

void Button::setOnClick(std::function<void()> fn)
{
    onClick = std::move(fn);
}

void Button::setTexture(const char* path)
{
    textureLoaded = texture.loadFromFile(path);
    useTexture = textureLoaded;
}

void Button::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Button::setSize(float width, float height)
{
    this->width = width;
    this->height = height;
}

float Button::getX() const { return x; }
float Button::getY() const { return y; }
float Button::getWidth() const { return width; }
float Button::getHeight() const { return height; }

bool Button::contains(float px, float py) const
{
    return (px >= x && px <= x + width &&
            py >= y && py <= y + height);
}

void Button::update(float mouseX, float mouseY, bool clicked)
{
    hover = contains(mouseX, mouseY);

    if (hover && clicked && onClick)
        onClick();
}

void Button::render(Shader& shader)
{
    if (useTexture && textureLoaded)
    {
        Renderer::drawTextureRect(x, y, width, height, texture, shader);
        return;
    }

    float c = hover ? 0.35f : 0.20f;

    Renderer::drawRect(x, y, width, height, c, c, c, shader);
}