#pragma once

struct GLFWwindow;

class Window
{
public:
    bool init(int w, int h, const char* title, bool fullscreen);

    void pollEvents();
    void swapBuffers();

    bool shouldClose() const;

    float getTime() const;

    void shutdown();

    GLFWwindow* getNative() const;

    void setFullscreen(bool fullscreen);
    void setShouldClose(bool value);

    // Tamaño del framebuffer (OpenGL)
    int getWidth() const;
    int getHeight() const;

    // Tamaño de la ventana (UI)
    int getWindowWidth() const;
    int getWindowHeight() const;

private:
    void updateViewport();

private:
    GLFWwindow* window = nullptr;

    // Tamaño ACTUAL de la ventana
    int width = 0;
    int height = 0;

    // Tamaño de la última ventana en modo ventana
    int windowedWidth = 0;
    int windowedHeight = 0;

    // Posición de la última ventana en modo ventana
    int windowedPosX = 100;
    int windowedPosY = 100;

    // Tamaño real del framebuffer
    int framebufferWidth = 0;
    int framebufferHeight = 0;

    bool isFullscreen = false;
};