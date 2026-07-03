#include "Renderer.h"
#include "Shader.h"
#include "Window.h"
#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern Window gWindow;

unsigned int Renderer::vao = 0;
unsigned int Renderer::vbo = 0;

bool Renderer::init()
{
    // BLENDING (CRÍTICO PARA PNG)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float vertices[] =
    {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void Renderer::shutdown()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Renderer::beginFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::endFrame() {}

void Renderer::drawRect(float x,
                        float y,
                        float width,
                        float height,
                        float r,
                        float g,
                        float b,
                        Shader& shader)
{
    shader.bind();

    shader.setVec4("uRect", x, y, width, height);
    shader.setVec2("uScreenSize",
        (float)gWindow.getWindowWidth(),
        (float)gWindow.getWindowHeight());

    shader.setVec3("uColor", r, g, b);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    shader.unbind();
}

void Renderer::drawTextureRect(float x,
                               float y,
                               float width,
                               float height,
                               Texture& texture,
                               Shader& shader)
{
    shader.bind();

    shader.setVec4("uRect", x, y, width, height);
    shader.setVec2("uScreenSize",
        (float)gWindow.getWindowWidth(),
        (float)gWindow.getWindowHeight());

    texture.bind(0);
    shader.setInt("uTexture", 0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    shader.unbind();
}