#pragma once
#include "Screen.h"
#include "Button.h"

class GameScreen : public Screen {
public:
    void onEnter() override;
    void update(float dt) override;
    void render() override;
    void onExit() override;

private:
    Button back;
};