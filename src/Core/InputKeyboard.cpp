#include "InputKeyboard.h"

#include <cstring>

GLFWwindow* InputKeyboard::window = nullptr;

bool InputKeyboard::currentKeys[512] = { false };
bool InputKeyboard::previousKeys[512] = { false };

void InputKeyboard::init(GLFWwindow* win)
{
    window = win;

    std::memset(currentKeys, 0, sizeof(currentKeys));
    std::memset(previousKeys, 0, sizeof(previousKeys));
}

void InputKeyboard::update()
{
    for (int i = 0; i < 512; i++)
    {
        previousKeys[i] = currentKeys[i];
        currentKeys[i] =
            glfwGetKey(window, i) == GLFW_PRESS;
    }
}

bool InputKeyboard::isKeyDown(int key)
{
    return currentKeys[key];
}

bool InputKeyboard::isKeyPressed(int key)
{
    return currentKeys[key] && !previousKeys[key];
}

bool InputKeyboard::isKeyReleased(int key)
{
    return !currentKeys[key] && previousKeys[key];
}