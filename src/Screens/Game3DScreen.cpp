#include "Game3DScreen.h"

#include "BoardPicker3D.h"
#include "InputMouse.h"
#include "InputConsole.h"
#include "Window.h"
#include "CupulaRenderer3D.h"
#include "CajaRenderer3D.h"

#include <glad/glad.h>

#include <iostream>

#include <GLFW/glfw3.h>

#include <memory>

extern Window gWindow;



//====================================================
// ENTER
//====================================================

void Game3DScreen::onEnter()
{

    //------------------------------------------------
    // CAMERA
    //------------------------------------------------

    camera.resetOverview();



    //------------------------------------------------
    // SCENE
    //------------------------------------------------

    sceneRenderer.initialize(
        "Shaders/basic_3d.vert",
        "Shaders/basic_3d.frag"
    );


    sceneRenderer.setEnvironment(
        std::make_unique<CajaRenderer3D>()
    );



    //------------------------------------------------
    // CHESS
    //------------------------------------------------

    chessRenderer.initialize(
        "Shaders/basic_3d.vert",
        "Shaders/basic_3d.frag"
    );



    //------------------------------------------------
    // GAME
    //------------------------------------------------

    game.reset();

}





//====================================================
// UPDATE
//====================================================

void Game3DScreen::update(
    float dt
)
{

    //------------------------------------------------
    // CAMERA
    //------------------------------------------------

    camera.update();



    //------------------------------------------------
    // SCENE
    //------------------------------------------------

    sceneRenderer.update(
        camera,
        dt
    );



    //------------------------------------------------
    // GAME
    //------------------------------------------------

    game.update(
        dt
    );



    //------------------------------------------------
    // CONSOLE INPUT
    //------------------------------------------------

    InputConsole::update(
        game
    );


    if(
        InputConsole::hasSquareSelection()
    )
    {

        uint8_t square =
            InputConsole::getSelectedSquare();

        std::cout
            << "CONSOLE SELECT SQUARE = "
            << static_cast<int>(square)
            << std::endl;

        game.onSquareClicked(
            square
        );

    }



    //------------------------------------------------
    // IGNORE CLICKS WHILE ROTATING CAMERA
    //------------------------------------------------

    if(
        InputMouse::isButtonDown(
            GLFW_MOUSE_BUTTON_MIDDLE
        )
    )
    {
        return;
    }



    //------------------------------------------------
    // MOUSE CLICK
    //------------------------------------------------

    if(
        !InputMouse::isButtonPressed(
            GLFW_MOUSE_BUTTON_LEFT
        )
    )
    {
        return;
    }



    float mx;
    float my;

    InputMouse::getUIPosition(
        mx,
        my
    );



    //------------------------------------------------
    // PICK PIECE
    //------------------------------------------------

    int pickedSquare =
        chessRenderer.pickPiece(
            game,
            camera,
            mx,
            my
        );


    if(
        pickedSquare != -1
    )
    {

        game.onSquareClicked(
            static_cast<uint8_t>(
                pickedSquare
            )
        );

        return;

    }



    //------------------------------------------------
    // PICK BOARD
    //------------------------------------------------

    uint8_t square;

    if(
        BoardPicker3D::pickSquare(
            mx,
            my,
            gWindow.getWindowWidth(),
            gWindow.getWindowHeight(),
            camera,
            square
        )
    )
    {

        std::cout
            << "BOARD PICK = "
            << static_cast<int>(
                square
            )
            << std::endl;

        game.onSquareClicked(
            square
        );

    }
    else
    {

        std::cout
            << "NO BOARD HIT"
            << std::endl;

    }

}





//====================================================
// RENDER
//====================================================

void Game3DScreen::render()
{

    //------------------------------------------------
    // UPDATE VIEWPORT
    //------------------------------------------------

    glViewport(
        0,
        0,
        gWindow.getWidth(),
        gWindow.getHeight()
    );



    //------------------------------------------------
    // ASPECT RATIO
    //------------------------------------------------

    float aspectRatio =
        static_cast<float>(
            gWindow.getWidth()
        )
        /
        static_cast<float>(
            gWindow.getHeight()
        );



    //------------------------------------------------
    // CLEAR FRAME
    //------------------------------------------------

    glClearColor(
        0.15f,
        0.15f,
        0.18f,
        1.0f
    );

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );



    //------------------------------------------------
    // SCENE
    //------------------------------------------------

    sceneRenderer.render(
        camera,
        aspectRatio
    );



    //------------------------------------------------
    // CHESS
    //------------------------------------------------

    chessRenderer.render(
        game,
        camera
    );

}





//====================================================
// EXIT
//====================================================

void Game3DScreen::onExit()
{

}