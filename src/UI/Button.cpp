#include "Button.h"

#include "Renderer.h"

Button::Button()
{
}

Button::Button(float x,
               float y,
               float width,
               float height,
               const char* text)
{
    setPosition(x, y);
    setSize(width, height);

    this->text = text;
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

float Button::getX() const
{
    return x;
}

float Button::getY() const
{
    return y;
}

float Button::getWidth() const
{
    return width;
}

float Button::getHeight() const
{
    return height;
}

void Button::setOnClick(std::function<void()> fn)
{
    onClick = std::move(fn);
}

bool Button::contains(float px, float py) const
{
    return
        px >= x &&
        px <= x + width &&
        py >= y &&
        py <= y + height;
}

void Button::update(float mouseX,
                    float mouseY,
                    bool clicked)
{
    hover = contains(mouseX, mouseY);

    if (hover && clicked && onClick)
    {
        onClick();
    }
}

void Button::render(Shader& shader)
{
    float color = hover ? 0.35f : 0.20f;

    Renderer::drawRect(
        x,
        y,
        width,
        height,
        color,
        color,
        color,
        shader
    );
}