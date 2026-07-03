#pragma once

struct GLFWwindow;

class InputMouse
{
public:
    static void init(GLFWwindow* window);
    static void update();

    // Coordenadas crudas de GLFW (origen: arriba-izquierda)
    static void getRawPosition(float& x, float& y);

    // Coordenadas UI (origen: arriba-izquierda, coherente con Button)
    static void getUIPosition(float& x, float& y);

    static bool isButtonDown(int button);
    static bool isButtonPressed(int button);
    static bool isButtonReleased(int button);

private:
    static GLFWwindow* window;

    static double mouseX;
    static double mouseY;

    static bool currentButtons[8];
    static bool previousButtons[8];
};