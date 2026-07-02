#pragma once

class Renderer {
public:
    static void beginFrame();
    static void endFrame();
    static void setClearColor(float r, float g, float b, float a);
};