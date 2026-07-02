#pragma once

class Screen {
public:
    virtual ~Screen() = default;

    virtual void onEnter() {}
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual void onExit() {}
};