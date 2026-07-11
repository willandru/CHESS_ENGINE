#include "InputConsole.h"

#include "InputKeyboard.h"

#include <GLFW/glfw3.h>

#include <cctype>
#include <iostream>

std::string InputConsole::buffer;

bool InputConsole::selectionReady = false;

uint8_t InputConsole::selectedSquare = 0;



//====================================================
// UPDATE
//====================================================

void InputConsole::update()
{

    selectionReady = false;


    for(int key = GLFW_KEY_A; key <= GLFW_KEY_Z; key++)
    {
        if(InputKeyboard::isKeyPressed(key))
        {
            processKey(key);
        }
    }



    for(int key = GLFW_KEY_0; key <= GLFW_KEY_9; key++)
    {
        if(InputKeyboard::isKeyPressed(key))
        {
            processKey(key);
        }
    }



    if(InputKeyboard::isKeyPressed(GLFW_KEY_ENTER))
    {
        std::cout
            << "ENTER BUFFER = "
            << buffer
            << std::endl;


        uint8_t square;

        if(parseSquare(buffer, square))
        {
            std::cout
                << "SQUARE = "
                << (int)square
                << std::endl;

            selectedSquare = square;
            selectionReady = true;
        }

        buffer.clear();
    }



    if(InputKeyboard::isKeyPressed(GLFW_KEY_BACKSPACE))
    {
        if(!buffer.empty())
            buffer.pop_back();
    }

}



//====================================================
// PROCESS KEY
//====================================================

void InputConsole::processKey(
    int key
)
{

    std::cout 
        << "KEY: "
        << key
        << std::endl;

    if(key >= GLFW_KEY_A &&
       key <= GLFW_KEY_Z)
    {

        char c =
            static_cast<char>(
                'A' + (key - GLFW_KEY_A)
            );


        buffer += c;
    }



    if(key >= GLFW_KEY_0 &&
       key <= GLFW_KEY_9)
    {

        char c =
            static_cast<char>(
                '0' + (key - GLFW_KEY_0)
            );


        buffer += c;
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
        std::toupper(text[0]);


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