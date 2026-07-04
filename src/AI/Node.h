#pragma once

#include <cstdint>
#include <vector>
#include "GameState.h"
#include "Move.h"

struct Node
{
    GameState state;     // estado del tablero en ese punto
    Move move;           // movimiento que generó este nodo
    int score = 0;       // evaluado por una IA externa

    int parent = -1;     // índice del padre (si usas pool)
};