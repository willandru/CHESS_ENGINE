#include "FeatureEngineering.h"

#include <cmath>

//====================================================
// ENCODE
//====================================================

std::vector<float> FeatureEngineering::encode(
    const GameState& state,
    const DecisionNode& node)
{
    std::vector<float> features;

    features.reserve(featureCount());

    encodeBoard(
        state,
        features);

    encodeMove(
        node,
        features);

    encodeGameState(
        state,
        features);

    return features;
}

//====================================================
// FEATURE COUNT
//====================================================

uint32_t FeatureEngineering::featureCount()
{
    return inputSize();
}

//====================================================
// BOARD
//====================================================

void FeatureEngineering::encodeBoard(
    const GameState& state,
    std::vector<float>& features)
{
    const Piece* board =
        state.getBoard();

    for (uint32_t square = 0; square < 64; ++square)
    {
        features.push_back(
            encodePiece(
                board[square]));
    }
}

//====================================================
// MOVE
//====================================================

void FeatureEngineering::encodeMove(
    const DecisionNode& node,
    std::vector<float>& features)
{
    const Move& move =
        node.move;

    features.push_back(
        normalizeSquare(
            move.from));

    features.push_back(
        normalizeSquare(
            move.to));

    features.push_back(
        normalizeFlags(
            move.flags));

    features.push_back(
        encodePiece(
            move.promo));
}

//====================================================
// GAME STATE
//====================================================

void FeatureEngineering::encodeGameState(
    const GameState& state,
    std::vector<float>& features)
{
    features.push_back(
        boolToFloat(
            state.getTurn() == PlayerSide::White));

    features.push_back(
        boolToFloat(
            state.canCastleKingside(PlayerSide::White)));

    features.push_back(
        boolToFloat(
            state.canCastleQueenside(PlayerSide::White)));

    features.push_back(
        boolToFloat(
            state.canCastleKingside(PlayerSide::Black)));

    features.push_back(
        boolToFloat(
            state.canCastleQueenside(PlayerSide::Black)));

    features.push_back(
        normalizeSquare(
            state.getEnPassantSquare()));
}

//====================================================
// ENCODE PIECE
//====================================================

float FeatureEngineering::encodePiece(
    Piece piece)
{
    switch (piece)
    {
        case EMPTY:
            return 0.0f;

        case WHITE_PAWN:
            return 1.0f / 12.0f;

        case WHITE_KNIGHT:
            return 2.0f / 12.0f;

        case WHITE_BISHOP:
            return 3.0f / 12.0f;

        case WHITE_ROOK:
            return 4.0f / 12.0f;

        case WHITE_QUEEN:
            return 5.0f / 12.0f;

        case WHITE_KING:
            return 6.0f / 12.0f;

        case BLACK_PAWN:
            return 7.0f / 12.0f;

        case BLACK_KNIGHT:
            return 8.0f / 12.0f;

        case BLACK_BISHOP:
            return 9.0f / 12.0f;

        case BLACK_ROOK:
            return 10.0f / 12.0f;

        case BLACK_QUEEN:
            return 11.0f / 12.0f;

        case BLACK_KING:
            return 1.0f;

        default:
            return 0.0f;
    }
}

//====================================================
// NORMALIZE SQUARE
//====================================================

float FeatureEngineering::normalizeSquare(
    uint8_t square)
{
    if (square >= 64)
        return -1.0f;

    return static_cast<float>(square) / 63.0f;
}

//====================================================
// NORMALIZE FLAGS
//====================================================

float FeatureEngineering::normalizeFlags(
    uint8_t flags)
{
    return static_cast<float>(flags) / 15.0f;
}

//====================================================
// BOOL TO FLOAT
//====================================================

float FeatureEngineering::boolToFloat(
    bool value)
{
    return value ? 1.0f : 0.0f;
}