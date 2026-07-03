#include "Button.h"
#include "Renderer.h"

Button::Button()
    : x(0), y(0), width(0), height(0), text(""), hover(false)
{}

Button::Button(float x, float y, float width, float height, const char* text)
    : x(x), y(y), width(width), height(height), text(text), hover(false)
{}

void Button::setOnClick(std::function<void()> fn)
{
    onClick = fn;
}

void Button::update(float mx, float my, bool clicked)
{
    hover =
        mx >= x && mx <= x + width &&
        my >= y && my <= y + height;

    if (hover && clicked && onClick)
    {
        onClick();
    }
}

void Button::render(Shader& shader)
{
    float c = hover ? 0.35f : 0.20f;

    Renderer::drawRect(x, y, width, height, c, c, c, shader);
}