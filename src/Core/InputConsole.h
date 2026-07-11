#pragma once

#include <string>
#include <cstdint>


class InputConsole
{
public:

    //------------------------------------------------
    // UPDATE
    //------------------------------------------------

    static void update();


    //------------------------------------------------
    // SELECTION
    //------------------------------------------------

    static bool hasSquareSelection();


    static uint8_t getSelectedSquare();


private:

    //------------------------------------------------
    // BUFFER
    //------------------------------------------------

    static std::string buffer;


    static bool selectionReady;


    static uint8_t selectedSquare;


    //------------------------------------------------
    // PARSE
    //------------------------------------------------

    static void processKey(
        int key
    );


    static bool parseSquare(
        const std::string& text,
        uint8_t& square
    );

};