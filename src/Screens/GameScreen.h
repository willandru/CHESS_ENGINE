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

    // Texturas (botones y piezas)
    Shader shader;

    // Colores (tablero y highlights)
    Shader boardShader;

    Button back;
    Button start;
    Button stop;
};