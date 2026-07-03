#pragma once

#include "Screen.h"
#include "Button.h"
#include "Shader.h"

class MainMenuScreen : public Screen
{
public:
    void onEnter() override;
    void update(float dt) override;
    void render() override;
    void onExit() override;

private:
    Shader shader;

    Button btn2D;
    Button btn25D;
    Button btn3D;
    Button exitBtn;
};