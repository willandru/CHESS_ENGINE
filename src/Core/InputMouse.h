#pragma once

struct GLFWwindow;

class InputMouse
{
public:

    static void init(
        GLFWwindow* window
    );

    static void update();

    //------------------------------------------------
    // POSITION
    //------------------------------------------------

    static void getRawPosition(
        float& x,
        float& y
    );

    static void getUIPosition(
        float& x,
        float& y
    );

    //------------------------------------------------
    // MOTION
    //------------------------------------------------

    static float getDeltaX();

    static float getDeltaY();

    //------------------------------------------------
    // SCROLL
    //------------------------------------------------

    static float getScrollDelta();

    //------------------------------------------------
    // BUTTONS
    //------------------------------------------------

    static bool isButtonDown(
        int button
    );

    static bool isButtonPressed(
        int button
    );

    static bool isButtonReleased(
        int button
    );

private:

    static void scrollCallback(
        GLFWwindow* window,
        double xoffset,
        double yoffset
    );

private:

    static GLFWwindow* window;

    //------------------------------------------------
    // POSITION
    //------------------------------------------------

    static double mouseX;
    static double mouseY;

    static double previousMouseX;
    static double previousMouseY;

    //------------------------------------------------
    // DELTA
    //------------------------------------------------

    static float deltaX;
    static float deltaY;

    //------------------------------------------------
    // SCROLL
    //------------------------------------------------

    static float scrollDelta;

    //------------------------------------------------
    // BUTTONS
    //------------------------------------------------

    static bool currentButtons[8];
    static bool previousButtons[8];
};