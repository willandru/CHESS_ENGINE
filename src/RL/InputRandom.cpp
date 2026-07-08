#include "InputRandom.h"

#include <random>
#include <iostream>


//====================================================
// GENERATE NODES
//====================================================

std::vector<Node>
InputRandom::generateNodes(
    int amount
)
{
    std::vector<Node> nodes;


    nodes.reserve(
        amount
    );


    for(int i = 0; i < amount; i++)
    {
        Node node(
            static_cast<uint8_t>(i),
            static_cast<uint8_t>(i + 10)
        );


        nodes.push_back(
            node
        );
    }


    return nodes;
}


//====================================================
// SIMULATE TURN
//====================================================

std::vector<Node>
InputRandom::simulateTurn()
{
    //------------------------------------------------
    // Random generator
    //------------------------------------------------

    static std::random_device rd;

    static std::mt19937 generator(rd());


    std::uniform_int_distribution<int>
    distribution(
        1,
        10
    );


    int nodeCount =
        distribution(generator);



    std::cout
        << "\nTURN GENERATED NODES: "
        << nodeCount
        << "\n";


    //------------------------------------------------
    // Generate nodes
    //------------------------------------------------

    return generateNodes(
        nodeCount
    );
}