#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void framebufferSizeCallback(GLFWwindow* win, int w, int h)
{
    glViewport(0, 0, w, h);
}

bool Window::init(int w, int h, const char* title, bool fullscreen)
{
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    width = w;
    height = h;

    windowedWidth = w;
    windowedHeight = h;

    isFullscreen = fullscreen;

    GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;

    window = glfwCreateWindow(width, height, title, monitor, nullptr);

    if (!window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return false;

    glfwGetWindowPos(window, &windowedPosX, &windowedPosY);

    updateViewport();

    return true;
}

void Window::updateViewport()
{
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);
}

void Window::setFullscreen(bool fullscreen)
{
    if (!window || isFullscreen == fullscreen)
        return;

    isFullscreen = fullscreen;

    if (fullscreen)
    {
        // Guardar tamaño y posición actuales
        glfwGetWindowPos(window, &windowedPosX, &windowedPosY);
        glfwGetWindowSize(window, &windowedWidth, &windowedHeight);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwSetWindowMonitor(
            window,
            monitor,
            0,
            0,
            mode->width,
            mode->height,
            mode->refreshRate
        );

        width = mode->width;
        height = mode->height;
    }
    else
    {
        glfwSetWindowMonitor(
            window,
            nullptr,
            windowedPosX,
            windowedPosY,
            windowedWidth,
            windowedHeight,
            0
        );

        width = windowedWidth;
        height = windowedHeight;
    }

    updateViewport();
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

bool Window::shouldClose() const
{
    return window && glfwWindowShouldClose(window);
}

float Window::getTime() const
{
    return static_cast<float>(glfwGetTime());
}

void Window::shutdown()
{
    if (window)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    glfwTerminate();
}

GLFWwindow* Window::getNative() const
{
    return window;
}

void Window::setShouldClose(bool value)
{
    if (window)
        glfwSetWindowShouldClose(window, value);
}

int Window::getWidth() const
{
    return framebufferWidth;
}

int Window::getHeight() const
{
    return framebufferHeight;
}

int Window::getWindowWidth() const
{
    return width;
}

int Window::getWindowHeight() const
{
    return height;
}