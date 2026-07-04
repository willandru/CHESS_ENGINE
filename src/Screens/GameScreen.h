#pragma once

#include "Screen.h"
#include "Button.h"
#include "Shader.h"
#include "GameState.h"

class GameScreen : public Screen
{
public:

    void onEnter() override;
    void update(float dt) override;
    void render() override;
    void onExit() override;

private:

    //=========================================
    // Game
    //=========================================

    GameState gameState;

    //=========================================
    // Shaders
    //=========================================

    // Botones y piezas
    Shader shader;

    // Tablero y highlights
    Shader boardShader;

    //=========================================
    // UI
    //=========================================

    Button back;
    Button start;
    Button stop;
};