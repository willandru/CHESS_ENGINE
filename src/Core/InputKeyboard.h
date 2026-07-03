#pragma once

#include <GLFW/glfw3.h>

class InputKeyboard
{
public:

    static void init(GLFWwindow* window);

    static void update();

    static bool isKeyDown(int key);

    static bool isKeyPressed(int key);

    static bool isKeyReleased(int key);

private:

    static GLFWwindow* window;

    static bool currentKeys[512];
    static bool previousKeys[512];
};