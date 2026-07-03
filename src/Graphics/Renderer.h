#pragma once

class Renderer {
public:
    static void setClearColor(float r, float g, float b, float a);

    static void beginFrame();
    static void endFrame();
};