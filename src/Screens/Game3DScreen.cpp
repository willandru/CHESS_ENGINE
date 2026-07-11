#include "Game3DScreen.h"

#include "BoardPicker3D.h"
#include "InputMouse.h"
#include "InputConsole.h"
#include "Window.h"
#include <iostream>

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
//====================================================
// UPDATE
//====================================================

void Game3DScreen::update(float dt)
{

    game.update(dt);



    //------------------------------------------------
    // INPUT CONSOLE
    //------------------------------------------------

    InputConsole::update();


    if(InputConsole::hasSquareSelection())
    {

        uint8_t sq =
            InputConsole::getSelectedSquare();


        std::cout
            << "CONSOLE SELECT SQUARE = "
            << static_cast<int>(sq)
            << std::endl;



        game.onSquareClicked(
            sq
        );


        std::cout
            << "HAS SELECTION = "
            << game.hasSelection()
            << std::endl;


        std::cout
            << "SELECTED SQUARE = "
            << static_cast<int>(
                game.getSelectedSquare()
            )
            << std::endl;


        std::cout
            << "LEGAL MOVES = "
            << game.getMoves().size()
            << std::endl;

    }




    //------------------------------------------------
    // MOUSE INPUT
    //------------------------------------------------

    if(!InputMouse::isButtonPressed(0))
        return;



    float mx;
    float my;


    InputMouse::getUIPosition(
        mx,
        my
    );




    //------------------------------------------------
    // TRY PICK PIECE
    //------------------------------------------------

    int pickedSquare =
        renderer3D.pickPiece(
            game,
            mx,
            my
        );



    if(pickedSquare != -1)
    {

        std::cout
            << "MOUSE PIECE PICKED = "
            << pickedSquare
            << std::endl;


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
            renderer3D.getCamera(),
            square
        )
    )
    {

        std::cout
            << "BOARD SQUARE PICKED = "
            << static_cast<int>(square)
            << std::endl;



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