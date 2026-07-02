#pragma once

class GameTime {
public:
    void init(float startTime);

    void update(float currentTime);

    float getDeltaTime() const;
    float getTime() const;

private:
    float lastTime = 0.0f;
    float currentTime = 0.0f;
    float deltaTime = 0.0f;
};