#pragma once

#include <vector>
#include <cstdint>

#include "GameState.h"
#include "DecisionNode.h"

class FeatureEngineering
{
public:

    //------------------------------------------------
    // Encode
    //------------------------------------------------
    // Encodes the current game state and one
    // candidate move into a fixed-size input vector.
    //------------------------------------------------

    static std::vector<float> encode(
        const GameState& state,
        const DecisionNode& node);

    //------------------------------------------------
    // Input Size
    //------------------------------------------------

    static constexpr uint32_t inputSize()
    {
        return

            //=============================
            // Board
            //=============================
            64 +

            //=============================
            // Move
            // from
            // to
            // flags
            // promotion piece
            //=============================
            4 +

            //=============================
            // Game State
            // turn
            // white K
            // white Q
            // black K
            // black Q
            // en passant
            //=============================
            6;
    }

    static uint32_t featureCount();

private:

    //------------------------------------------------
    // Encoders
    //------------------------------------------------

    static void encodeBoard(
        const GameState& state,
        std::vector<float>& features);

    static void encodeMove(
        const DecisionNode& node,
        std::vector<float>& features);

    static void encodeGameState(
        const GameState& state,
        std::vector<float>& features);

    //------------------------------------------------
    // Helpers
    //------------------------------------------------

    static float encodePiece(
        Piece piece);

    static float normalizeSquare(
        uint8_t square);

    static float normalizeFlags(
        uint8_t flags);

    static float boolToFloat(
        bool value);
};