#include "GameTime.h"

void GameTime::init(float startTime) {
    lastTime = startTime;
    currentTime = startTime;
    deltaTime = 0.0f;
}

void GameTime::update(float now) {
    currentTime = now;
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
}

float GameTime::getDeltaTime() const {
    return deltaTime;
}

float GameTime::getTime() const {
    return currentTime;
}