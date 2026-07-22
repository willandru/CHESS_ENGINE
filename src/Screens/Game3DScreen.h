#pragma once

#include "Screen.h"

#include "Camera3D.h"

#include "SceneRenderer3D.h"

#include "ChessRenderer3D.h"
#include "ChessGame.h"

class Game3DScreen : public Screen
{

public:

    void onEnter() override;

    void update(
        float dt
    ) override;

    void render() override;

    void onExit() override;


private:


    //------------------------------------------------
    // GLOBAL CAMERA
    //------------------------------------------------

    Camera3D camera;



    //------------------------------------------------
    // SCENE
    //------------------------------------------------

    SceneRenderer3D sceneRenderer;



    //------------------------------------------------
    // CHESS
    //------------------------------------------------

    ChessRenderer3D chessRenderer;



    //------------------------------------------------
    // GAME
    //------------------------------------------------

    ChessGame game;

};