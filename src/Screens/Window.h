#pragma once

struct GLFWwindow;

class Window {
public:
    bool init(int w, int h, const char* title, bool fullscreen);

    void pollEvents();
    void swapBuffers();

    bool shouldClose() const;

    float getTime() const;

    void shutdown();

    GLFWwindow* getNative() const;

    void setFullscreen(bool fullscreen);

private:
    GLFWwindow* window = nullptr;

    int width = 0;
    int height = 0;
};