#pragma once

#include <cstdint>

#include "GameState.h"
#include "DecisionTreeEngine.h"


class ChessAnalyzer
{
public:

    enum class Filter
    {
        All,
        Check,
        Checkmate,
        CheckOrMate
    };


public:

    ChessAnalyzer();


    //------------------------------------------------
    // CONFIGURATION
    //------------------------------------------------

    void setFilter(Filter filter);


    //------------------------------------------------
    // ANALYSIS
    //------------------------------------------------

    void analyze(
        const GameState& state,
        uint32_t depth,
        uint8_t selectedSquare);


private:

    //------------------------------------------------
    // TREE TRAVERSAL
    //------------------------------------------------

    void analyzeDepth(
        const DecisionNode& node,
        uint32_t targetDepth,
        PlayerSide rootSide);


private:

    //------------------------------------------------
    // SEARCH TREE
    //------------------------------------------------

    DecisionTreeEngine tree;


    //------------------------------------------------
    // OUTPUT FILTER
    //------------------------------------------------

    Filter filter = Filter::All;
};