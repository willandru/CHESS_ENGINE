#include "DecisionTreeEngine.h"

#include "MoveGenerator.h"
#include "MoveFilter.h"
#include "MoveExecutor.h"

void DecisionTreeEngine::expandNode(
    const Node& parent,
    std::vector<Node>& outChildren)
{
    outChildren.clear();

    std::vector<Move> moves;

    // 1. generar movimientos desde estado del nodo
    MoveGenerator::generateAllMoves(parent.state, moves);
    MoveFilter::filterLegalMoves(parent.state, moves);

    // 2. crear hijos
    for (const Move& m : moves)
    {
        Node child;
        child.state = parent.state;   // copiar estado
        MoveExecutor::execute(child.state, m);

        child.move = m;
        child.parent = -1; // si luego haces árbol real, aquí se asigna índice
        child.score = 0;

        outChildren.push_back(child);
    }
}