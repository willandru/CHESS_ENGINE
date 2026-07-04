#pragma once

#include "Screen.h"
#include "Button.h"
#include "Shader.h"

#include "ChessGame.h"

class GameScreen : public Screen
{
public:

    void onEnter() override;
    void update(float dt) override;
    void render() override;
    void onExit() override;

private:

    //=========================================
    // GAME
    //=========================================

    ChessGame game;

    //=========================================
    // SHADERS
    //=========================================

    // piezas + botones
    Shader shader;

    // tablero + highlights
    Shader boardShader;

    //=========================================
    // UI
    //=========================================

    Button back;
    Button start;
    Button stop;
};