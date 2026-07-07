#include "ChessAnalyzer.h"

#include <iostream>


//====================================================
// CONSTRUCTOR
//====================================================

ChessAnalyzer::ChessAnalyzer()
{
}


//====================================================
// FILTER CONFIGURATION
//====================================================

void ChessAnalyzer::setFilter(
    Filter newFilter)
{
    filter = newFilter;
}


//====================================================
// ANALYSIS
//====================================================

void ChessAnalyzer::analyze(
    const GameState& state,
    uint32_t depth,
    uint8_t selectedSquare)
{
    //------------------------------------------------
    // Build tree from selected piece
    //------------------------------------------------

    tree.build(
        state,
        selectedSquare,
        depth);


    std::cout
        << "\n========== ChessAnalyzer ==========\n";


    std::cout
        << "Selected piece : "
        << GameState::squareToNotation(selectedSquare)
        << '\n';


    std::cout
        << "Analysis depth : "
        << depth
        << "\n\n";


    analyzeDepth(
        tree.getRoot(),
        depth,
        state.getTurn());


    std::cout
        << "===================================\n\n";
}



//====================================================
// TREE TRAVERSAL
//====================================================

void ChessAnalyzer::analyzeDepth(
    const DecisionNode& node,
    uint32_t targetDepth,
    PlayerSide rootSide)
{

    //------------------------------------------------
    // Desired depth reached
    //------------------------------------------------

    if (node.depth == targetDepth)
    {

        bool myCheck = false;
        bool myMate = false;

        bool enemyCheck = false;
        bool enemyMate = false;



        //------------------------------------------------
        // Determine result owner
        //------------------------------------------------

        if (node.sideToMove != rootSide)
        {
            myCheck = node.inCheck;
            myMate = node.checkmate;
        }
        else
        {
            enemyCheck = node.inCheck;
            enemyMate = node.checkmate;
        }



        //------------------------------------------------
        // Tactical result
        //------------------------------------------------

        if (myMate)
        {
            std::cout
            << GameState::squareToNotation(node.move.from)
            << " -> "
            << GameState::squareToNotation(node.move.to)
            << '\n';

            std::cout
                << "  RESULT : MATE\n";
        }
        else if (myCheck)
        {
            std::cout
            << GameState::squareToNotation(node.move.from)
            << " -> "
            << GameState::squareToNotation(node.move.to)
            << '\n';

            std::cout
                << "  RESULT : CHECK\n";
        }
        else if (enemyMate)
        {
            std::cout
            << GameState::squareToNotation(node.move.from)
            << " -> "
            << GameState::squareToNotation(node.move.to)
            << '\n';

            std::cout
                << "  RESULT : ENEMY MATE\n";
        }
        else if (enemyCheck)
        {
            std::cout
            << GameState::squareToNotation(node.move.from)
            << " -> "
            << GameState::squareToNotation(node.move.to)
            << '\n';

            std::cout
                << "  RESULT : ENEMY CHECK\n";
        }
        


        return;
    }



    //------------------------------------------------
    // Continue traversal
    //------------------------------------------------

    for (const DecisionNode& child : node.children)
    {
        analyzeDepth(
            child,
            targetDepth,
            rootSide);
    }
}