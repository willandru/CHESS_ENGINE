#include "Button.h"

#include "Renderer.h"
#include "Shader.h"

Button::Button()
    : x(0.0f),
      y(0.0f),
      width(0.0f),
      height(0.0f),
      text(""),
      hover(false)
{
}

Button::Button(float x,
               float y,
               float width,
               float height,
               const char* text)
    : x(x),
      y(y),
      width(width),
      height(height),
      text(text),
      hover(false)
{
}

void Button::setOnClick(std::function<void()> callback)
{
    onClick = callback;
}

void Button::update(float mouseX,
                    float mouseY,
                    bool clicked)
{
    hover =
        mouseX >= x &&
        mouseX <= x + width &&
        mouseY >= y &&
        mouseY <= y + height;

    if (hover && clicked && onClick)
    {
        onClick();
    }
}

void Button::render(Shader& shader)
{
    if (hover)
    {
        Renderer::drawRect(
            x,
            y,
            width,
            height,
            0.35f,
            0.35f,
            0.35f,
            shader);
    }
    else
    {
        Renderer::drawRect(
            x,
            y,
            width,
            height,
            0.20f,
            0.20f,
            0.20f,
            shader);
    }

    // El renderizado del texto se implementará más adelante.
}