#pragma once

#include <memory>

class Screen;
class GameTime;

enum class ScreenType
{
    Splash,
    MainMenu,
    Game
};

class ScreenManager
{
public:
    ScreenManager();
    ~ScreenManager();

    void init();

    void setScreen(ScreenType type);

    void update(GameTime& time);
    void render();

    ScreenType getActiveScreen() const;

private:
    std::unique_ptr<Screen> current = nullptr;

    ScreenType activeType = ScreenType::Splash;

    float splashTimer = 0.0f;
    static constexpr float splashDuration = 3.0f;
};