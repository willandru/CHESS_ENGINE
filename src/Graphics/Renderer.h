#pragma once

class Shader;

class Renderer
{
public:
    static bool init();
    static void shutdown();

    static void setClearColor(float r,
                              float g,
                              float b,
                              float a);

    static void beginFrame();
    static void endFrame();

    static void drawRect(float x,
                         float y,
                         float width,
                         float height,
                         float r,
                         float g,
                         float b,
                         Shader& shader);

private:
    static unsigned int vao;
    static unsigned int vbo;
};