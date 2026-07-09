#pragma once

#include <vector>

#include "Node.h"


class InputRandom
{
public:

    //------------------------------------------------
    // Genera una cantidad fija de nodos
    //------------------------------------------------

    static std::vector<Node> generateNodes(
        int amount
    );


    //------------------------------------------------
    // Simula un turno:
    // genera entre 1 y 10 nodos
    //------------------------------------------------

    static std::vector<Node> simulateTurn();

};