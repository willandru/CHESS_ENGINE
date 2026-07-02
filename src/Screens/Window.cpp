#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

bool Window::init(int w, int h, const char* title, bool fullscreen)
{
    if (!glfwInit())
    {
        std::cout << "GLFW init failed\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    width  = w;
    height = h;

    GLFWmonitor* monitor = nullptr;

    if(fullscreen)
    {
        monitor = glfwGetPrimaryMonitor();
    }
    else
    {
        // Splash
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    window = glfwCreateWindow(width,height,title,monitor,nullptr);

    if(!window)
    {
        glfwTerminate();
        return false;
    }

    if(!fullscreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        int x = (mode->width  - width ) / 2;
        int y = (mode->height - height) / 2;

        glfwSetWindowPos(window, x, y);
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD failed\n";
        return false;
    }

    glViewport(0,0,width,height);

    return true;
}

void Window::setFullscreen(bool fullscreen)
{
    if(fullscreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);

        glfwSetWindowMonitor(
            window,
            monitor,
            0,
            0,
            mode->width,
            mode->height,
            mode->refreshRate
        );

        glViewport(0,0,mode->width,mode->height);
    }
    else
    {
        glfwSetWindowMonitor(
            window,
            nullptr,
            100,
            100,
            width,
            height,
            0
        );

        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        int x = (mode->width  - width ) / 2;
        int y = (mode->height - height) / 2;

        glfwSetWindowPos(window,x,y);

        glViewport(0,0,width,height);
    }
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
    return glfwWindowShouldClose(window);
}

float Window::getTime() const
{
    return (float)glfwGetTime();
}

void Window::shutdown()
{
    if(window)
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