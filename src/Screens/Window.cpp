#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

bool Window::init(int w, int h, const char* title, bool fullscreen) {

    // 1. Inicializar GLFW
    if (!glfwInit()) {
        std::cout << "GLFW init failed\n";
        return false;
    }

    // 2. Configuración OpenGL (core profile 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 3. Fullscreen opcional
    GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;

    // 4. Crear ventana
    window = glfwCreateWindow(w, h, title, monitor, nullptr);
    if (!window) {
        std::cout << "Window creation failed\n";
        glfwTerminate();
        return false;
    }

    // 5. Hacer contexto actual
    glfwMakeContextCurrent(window);

    // 6. Cargar OpenGL (GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD init failed\n";
        return false;
    }

    // 7. Viewport inicial
    glViewport(0, 0, w, h);

    return true;
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

float Window::getTime() const {
    return (float)glfwGetTime();
}

void Window::shutdown() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

GLFWwindow* Window::getNative() const {
    return window;
}