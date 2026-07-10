#pragma once

#include "Screen.h"

#include "ChessRenderer3D.h"


class Game3DScreen : public Screen
{

public:

    void onEnter() override;

    void update(float dt) override;

    void render() override;

    void onExit() override;


private:

    ChessRenderer3D renderer3D;

};