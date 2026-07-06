#pragma once

#include <vector>
#include <cstdint>

#include "GameState.h"
#include "Move.h"
#include "ChessRules.h"

#include "PawnMoves.h"
#include "KnightMoves.h"
#include "KingMoves.h"
#include "RookMoves.h"
#include "BishopMoves.h"

class MoveGenerator
{
public:

    static void generatePieceMoves(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves);

    static void generateAllMoves(
        const GameState& state,
        std::vector<Move>& moves);

    static bool attacksSquare(
        const GameState& state,
        uint8_t from,
        uint8_t target);

private:

    static void generatePawn(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves);

    static void generateKnight(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves);

    static void generateKing(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves);

    static void generateRook(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves);

    static void generateBishop(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves);

    static void generateQueen(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves);

    static void generateCastling(
        const GameState& state,
        uint8_t square,
        std::vector<Move>& moves);

private:

    static bool isInsideBoard(int square);
    static bool isSameColor(Piece a, Piece b);
    static bool isEnemy(Piece a, Piece b);

    static bool isCorrectTurn(const GameState& state, Piece piece);
    static bool crossedEdge(int from, int to, int dir);
    static bool isValidKnightMove(int from, int to);
    static bool isValidKingMove(int from, int to);
    static bool isValidPawnCapture(int from, int to);
};