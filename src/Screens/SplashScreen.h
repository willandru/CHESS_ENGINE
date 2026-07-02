#pragma once

#include "Screen.h"

class SplashScreen : public Screen {
public:
    void onEnter() override;
    void update(float dt) override;
    void render() override;
    void onExit() override;

private:
    float t = 0.0f;
};