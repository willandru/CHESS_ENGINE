#pragma once

#include "Screen.h"
#include "Button.h"
#include "Shader.h"

class GameScreen : public Screen
{
public:
    void onEnter() override;
    void update(float dt) override;
    void render() override;
    void onExit() override;

private:
    // UI (botones con texturas)
    Shader shader;

    // Tablero (colores sólidos)
    Shader boardShader;

    Button back;
    Button start;
    Button stop;
};