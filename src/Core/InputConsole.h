#pragma once

#include <string>
#include <cstdint>


class ChessGame;


class InputConsole
{
public:

    //------------------------------------------------
    // UPDATE
    //------------------------------------------------

    static void update(
        ChessGame& game
    );


    //------------------------------------------------
    // RESULT
    //------------------------------------------------

    static bool hasSquareSelection();


    static uint8_t getSelectedSquare();



private:

    //------------------------------------------------
    // CONSOLE STATE
    //------------------------------------------------

    enum class ConsoleMode
    {
        Origin,
        Destination
    };


    static ConsoleMode mode;



    //------------------------------------------------
    // INPUT BUFFER
    //------------------------------------------------

    static std::string buffer;



    //------------------------------------------------
    // CURRENT SELECTION
    //------------------------------------------------

    static bool hasOrigin;


    static uint8_t originSquare;


    static uint8_t destinationSquare;



    //------------------------------------------------
    // OUTPUT EVENT
    //------------------------------------------------

    static bool selectionReady;


    static uint8_t selectedSquare;



    //------------------------------------------------
    // INTERNAL
    //------------------------------------------------

    static void processKey(
        int key
    );


    static void processBuffer(
        ChessGame& game
    );


    static bool parseSquare(
        const std::string& text,
        uint8_t& square
    );


    static void resetBuffer();


    static void cancel(
        ChessGame& game
    );

};