#include "Button.h"
#include <iostream>

Button::Button()
    : x(0), y(0), w(0), h(0), text(""), hover(false) {}

Button::Button(float x, float y, float w, float h, const char* text)
    : x(x), y(y), w(w), h(h), text(text), hover(false) {}

void Button::setOnClick(std::function<void()> fn) {
    onClick = fn;
}

void Button::update(float mx, float my, bool clicked) {

    hover =
        (mx >= x && mx <= x + w &&
         my >= y && my <= y + h);

    if (hover && clicked) {
        if (onClick)
            onClick();
    }
}

void Button::render() {
    std::cout << (hover ? "[HOVER] " : "") << text << "\n";
}