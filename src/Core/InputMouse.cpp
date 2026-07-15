#include "InputMouse.h"

#include <GLFW/glfw3.h>

#include <cstring>

GLFWwindow* InputMouse::window = nullptr;

double InputMouse::mouseX = 0.0;
double InputMouse::mouseY = 0.0;

double InputMouse::previousMouseX = 0.0;
double InputMouse::previousMouseY = 0.0;

float InputMouse::deltaX = 0.0f;
float InputMouse::deltaY = 0.0f;

float InputMouse::scrollDelta = 0.0f;

bool InputMouse::currentButtons[8] = { false };
bool InputMouse::previousButtons[8] = { false };


//====================================================
// INIT
//====================================================

void InputMouse::init(
    GLFWwindow* win
)
{
    window = win;

    std::memset(
        currentButtons,
        0,
        sizeof(currentButtons)
    );

    std::memset(
        previousButtons,
        0,
        sizeof(previousButtons)
    );

    glfwGetCursorPos(
        window,
        &mouseX,
        &mouseY
    );

    previousMouseX = mouseX;
    previousMouseY = mouseY;

    glfwSetScrollCallback(
        window,
        scrollCallback
    );
}


//====================================================
// UPDATE
//====================================================

void InputMouse::update()
{
    if(!window)
        return;

    //------------------------------------------------
    // BUTTONS
    //------------------------------------------------

    for(int i = 0; i < 8; ++i)
    {
        previousButtons[i] = currentButtons[i];

        currentButtons[i] =
            glfwGetMouseButton(
                window,
                i
            ) == GLFW_PRESS;
    }

    //------------------------------------------------
    // POSITION
    //------------------------------------------------

    previousMouseX = mouseX;
    previousMouseY = mouseY;

    glfwGetCursorPos(
        window,
        &mouseX,
        &mouseY
    );

    deltaX =
        static_cast<float>(
            mouseX - previousMouseX
        );

    deltaY =
        static_cast<float>(
            mouseY - previousMouseY
        );
}


//====================================================
// SCROLL CALLBACK
//====================================================

void InputMouse::scrollCallback(
    GLFWwindow*,
    double,
    double yoffset
)
{
    scrollDelta +=
        static_cast<float>(yoffset);
}


//====================================================
// POSITION
//====================================================

void InputMouse::getRawPosition(
    float& x,
    float& y
)
{
    x = static_cast<float>(mouseX);
    y = static_cast<float>(mouseY);
}

void InputMouse::getUIPosition(
    float& x,
    float& y
)
{
    x = static_cast<float>(mouseX);
    y = static_cast<float>(mouseY);
}


//====================================================
// DELTA
//====================================================

float InputMouse::getDeltaX()
{
    return deltaX;
}

float InputMouse::getDeltaY()
{
    return deltaY;
}


//====================================================
// SCROLL
//====================================================

float InputMouse::getScrollDelta()
{
    float value = scrollDelta;

    scrollDelta = 0.0f;

    return value;
}


//====================================================
// BUTTONS
//====================================================

bool InputMouse::isButtonDown(
    int button
)
{
    return currentButtons[button];
}

bool InputMouse::isButtonPressed(
    int button
)
{
    return
        currentButtons[button] &&
        !previousButtons[button];
}

bool InputMouse::isButtonReleased(
    int button
)
{
    return
        !currentButtons[button] &&
        previousButtons[button];
}