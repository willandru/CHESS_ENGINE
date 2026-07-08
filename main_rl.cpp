#include <iostream>
#include <vector>

#include "Node.h"
#include "InputRandom.h"


int main()
{
    std::cout
        << "========== RL NODE TEST ==========\n";


    for(int turn = 0; turn < 5; turn++)
    {
        std::cout
            << "\n----------- TURN "
            << turn
            << " -----------\n";


        std::vector<Node> nodes =
            InputRandom::simulateTurn();



        std::cout
            << "\nINPUT:\n";


        for(size_t i = 0; i < nodes.size(); i++)
        {
            std::cout
                << "Node "
                << i
                << " from="
                << int(nodes[i].getFrom())
                << " to="
                << int(nodes[i].getTo())
                << "\n";
        }
    }


    std::cout
        << "\n=================================\n";


    return 0;
}