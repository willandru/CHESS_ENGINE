#pragma once

class Shader;
class Texture;   // SOLO forward declaration

class Renderer
{
public:
    static bool init();
    static void shutdown();

    static void setClearColor(float r,float g,float b,float a);
    static void beginFrame();
    static void endFrame();

    static void drawRect(float x,float y,float w,float h,
                         float r,float g,float b,
                         Shader& shader);

    static void drawTextureRect(float x,float y,float w,float h,
                                Texture& texture,
                                Shader& shader);

private:
    static unsigned int vao;
    static unsigned int vbo;
};