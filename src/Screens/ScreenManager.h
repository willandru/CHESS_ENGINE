#pragma once

#include <memory>
#include "Screen.h"
#include "GameTime.h"

enum class ScreenType {
    Splash,
    MainMenu,
    Game
};

class ScreenManager {
public:
    ScreenManager() = default;
    ~ScreenManager();

    void init();
    void setScreen(ScreenType type);

    void update(GameTime& time);
    void render();

private:
    std::unique_ptr<Screen> current;

    ScreenType activeType = ScreenType::Splash;

    float splashTimer = 0.0f;
    const float splashDuration = 1.0f;
};