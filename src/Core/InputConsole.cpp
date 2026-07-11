#include "InputConsole.h"

#include "InputKeyboard.h"
#include "ChessGame.h"
#include "GameState.h"

#include <GLFW/glfw3.h>

#include <cctype>
#include <iostream>


//====================================================
// STATIC DATA
//====================================================

InputConsole::ConsoleMode
InputConsole::mode =
    InputConsole::ConsoleMode::Origin;


std::string InputConsole::buffer;


bool InputConsole::hasOrigin = false;


uint8_t InputConsole::originSquare = 0;


uint8_t InputConsole::destinationSquare = 0;


bool InputConsole::selectionReady = false;


uint8_t InputConsole::selectedSquare = 0;


//====================================================
// UPDATE
//====================================================

void InputConsole::update(
    ChessGame& game
)
{

    selectionReady = false;



    //------------------------------------------------
    // LETTER INPUT
    //------------------------------------------------

    for(int key = GLFW_KEY_A;
        key <= GLFW_KEY_Z;
        key++)
    {
        if(InputKeyboard::isKeyPressed(key))
        {
            processKey(key);
        }
    }



    //------------------------------------------------
    // NUMBER INPUT
    //------------------------------------------------

    for(int key = GLFW_KEY_0;
        key <= GLFW_KEY_9;
        key++)
    {
        if(InputKeyboard::isKeyPressed(key))
        {
            processKey(key);
        }
    }



    //------------------------------------------------
    // BACKSPACE
    //------------------------------------------------

    if(InputKeyboard::isKeyPressed(GLFW_KEY_BACKSPACE))
    {

        if(!buffer.empty())
        {
            buffer.pop_back();
        }

        return;
    }



    //------------------------------------------------
    // SPACE CANCEL
    //------------------------------------------------

    if(InputKeyboard::isKeyPressed(GLFW_KEY_SPACE))
    {
        cancel(game);
        return;
    }



    //------------------------------------------------
    // PROCESS TWO CHARACTER BUFFER
    //------------------------------------------------

    if(buffer.size() == 2)
    {
        processBuffer(game);
    }



    //------------------------------------------------
    // ENTER
    //------------------------------------------------

    if(InputKeyboard::isKeyPressed(GLFW_KEY_ENTER))
    {

        //------------------------------------------------
        // CONFIRM ORIGIN
        //------------------------------------------------

        if(mode == ConsoleMode::Origin)
        {

            if(hasOrigin)
            {

                mode =
                    ConsoleMode::Destination;


                buffer.clear();


                std::cout
                    << "ORIGIN CONFIRMED = "
                    << (int)originSquare
                    << std::endl;

            }


            return;
        }



        //------------------------------------------------
        // CONFIRM DESTINATION
        //------------------------------------------------

        if(mode == ConsoleMode::Destination)
        {

            uint8_t square;


            if(parseSquare(buffer,square))
            {

                selectedSquare = square;

                selectionReady = true;


                mode =
                    ConsoleMode::Origin;


                hasOrigin = false;


                buffer.clear();


                std::cout
                    << "DESTINATION CONFIRMED = "
                    << (int)square
                    << std::endl;

            }
            else
            {
                resetBuffer();
            }


        }

    }

}



//====================================================
// PROCESS BUFFER
//====================================================

void InputConsole::processBuffer(
    ChessGame& game
)
{

    uint8_t square;



    if(!parseSquare(buffer,square))
    {
        resetBuffer();
        return;
    }



    //------------------------------------------------
    // ORIGIN MODE
    //------------------------------------------------

    if(mode == ConsoleMode::Origin)
    {

        const GameState& state =
            game.getGameState();



        Piece piece =
            state.getPiece(square);



        //--------------------------------------------
        // EMPTY SQUARE
        //--------------------------------------------

        if(piece == EMPTY)
        {
            resetBuffer();
            return;
        }



        //--------------------------------------------
        // SELECT PIECE
        //--------------------------------------------

        game.onSquareClicked(square);



        originSquare = square;

        hasOrigin = true;



        std::cout
            << "ORIGIN PREVIEW = "
            << (int)square
            << std::endl;



        buffer.clear();


        return;

    }



    //------------------------------------------------
    // DESTINATION MODE
    //------------------------------------------------

    if(mode == ConsoleMode::Destination)
    {

        destinationSquare = square;


        std::cout
            << "DESTINATION PREVIEW = "
            << (int)square
            << std::endl;


        return;

    }

}



//====================================================
// PROCESS KEY
//====================================================

void InputConsole::processKey(
    int key
)
{

    if(buffer.size() >= 2)
    {
        return;
    }



    if(key >= GLFW_KEY_A &&
       key <= GLFW_KEY_Z)
    {

        buffer +=
            static_cast<char>(
                'A' +
                (key - GLFW_KEY_A)
            );

        return;

    }



    if(key >= GLFW_KEY_0 &&
       key <= GLFW_KEY_9)
    {

        buffer +=
            static_cast<char>(
                '0' +
                (key - GLFW_KEY_0)
            );

        return;

    }

}



//====================================================
// PARSE
//====================================================

bool InputConsole::parseSquare(
    const std::string& text,
    uint8_t& square
)
{

    if(text.size() != 2)
        return false;



    char file =
        std::toupper(
            text[0]
        );


    char rank =
        text[1];



    if(file < 'A' || file > 'H')
        return false;



    if(rank < '1' || rank > '8')
        return false;



    int column =
        file - 'A';



    int row =
        7 - (rank - '1');



    square =
        static_cast<uint8_t>(
            row * 8 + column
        );


    return true;

}



//====================================================
// RESET BUFFER
//====================================================

void InputConsole::resetBuffer()
{
    buffer.clear();
}



//====================================================
// CANCEL
//====================================================

void InputConsole::cancel(
    ChessGame& game
)
{

    buffer.clear();


    hasOrigin = false;


    originSquare = 0;


    destinationSquare = 0;


    mode =
        ConsoleMode::Origin;


    game.cancelSelection();


    std::cout
        << "CONSOLE CANCELLED"
        << std::endl;

}



//====================================================
// RESULT
//====================================================

bool InputConsole::hasSquareSelection()
{
    return selectionReady;
}



uint8_t InputConsole::getSelectedSquare()
{
    return selectedSquare;
}