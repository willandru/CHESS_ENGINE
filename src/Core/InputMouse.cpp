#include "InputMouse.h"

#include <GLFW/glfw3.h>
#include <cstring>

GLFWwindow* InputMouse::window = nullptr;

double InputMouse::mouseX = 0.0;
double InputMouse::mouseY = 0.0;

bool InputMouse::currentButtons[8] = { false };
bool InputMouse::previousButtons[8] = { false };

void InputMouse::init(GLFWwindow* win)
{
    window = win;

    std::memset(currentButtons, 0, sizeof(currentButtons));
    std::memset(previousButtons, 0, sizeof(previousButtons));
}

void InputMouse::update()
{
    if (!window)
        return;

    for (int i = 0; i < 8; i++)
    {
        previousButtons[i] = currentButtons[i];
        currentButtons[i] = (glfwGetMouseButton(window, i) == GLFW_PRESS);
    }

    glfwGetCursorPos(window, &mouseX, &mouseY);
}

void InputMouse::getRawPosition(float& x, float& y)
{
    x = static_cast<float>(mouseX);
    y = static_cast<float>(mouseY);
}

void InputMouse::getUIPosition(float& x, float& y)
{
    if (!window)
    {
        x = 0.0f;
        y = 0.0f;
        return;
    }

    // La UI utiliza coordenadas de ventana (origen arriba-izquierda),
    // por lo que simplemente devolvemos la posición del cursor.
    x = static_cast<float>(mouseX);
    y = static_cast<float>(mouseY);
}

bool InputMouse::isButtonDown(int button)
{
    return currentButtons[button];
}

bool InputMouse::isButtonPressed(int button)
{
    return currentButtons[button] && !previousButtons[button];
}

bool InputMouse::isButtonReleased(int button)
{
    return !currentButtons[button] && previousButtons[button];
}