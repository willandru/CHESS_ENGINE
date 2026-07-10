#include "Game3DScreen.h"

#include "BoardPicker3D.h"
#include "InputMouse.h"
#include "Window.h"

extern Window gWindow;



//====================================================
// ENTER
//====================================================

void Game3DScreen::onEnter()
{
    renderer3D.initialize(
        "Shaders/basic_3d.vert",
        "Shaders/basic_3d.frag"
    );

    game.reset();
}



//====================================================
// UPDATE
//====================================================

void Game3DScreen::update(float dt)
{
    game.update(dt);


    //------------------------------------------------
    // MOUSE CLICK
    //------------------------------------------------

    if(!InputMouse::isButtonPressed(0))
        return;


    float mx;
    float my;

    InputMouse::getUIPosition(
        mx,
        my
    );


    uint8_t square;

    if(
        BoardPicker3D::pickSquare(
            mx,
            my,
            gWindow.getWindowWidth(),
            gWindow.getWindowHeight(),
            renderer3D.getCamera(),
            square
        )
    )
    {
        game.onSquareClicked(
            square
        );
    }
}



//====================================================
// RENDER
//====================================================

void Game3DScreen::render()
{
    renderer3D.render(
        game
    );
}



//====================================================
// EXIT
//====================================================

void Game3DScreen::onExit()
{

}