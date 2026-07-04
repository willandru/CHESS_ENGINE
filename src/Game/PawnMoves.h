#pragma once

#include <array>
#include <cstdint>

//=====================================================
// Pawn geometric moves
//
// Offsets are defined from White's perspective.
// For Black pawns, MoveGenerator simply negates
// the offset.
//
// These are ONLY geometric possibilities.
// Legality is determined by MoveGenerator using
// ChessRules and GameState.
//=====================================================

enum class PawnMoveType : uint8_t
{
    Forward1,
    Forward2,

    CaptureLeft,
    CaptureRight,

    EnPassantLeft,
    EnPassantRight
};

struct PawnMove
{
    int8_t offset;
    PawnMoveType type;
};

class PawnMoves
{
public:

    static constexpr std::array<PawnMove, 6> moves =
    {{
        {  -8, PawnMoveType::Forward1      },
        { -16, PawnMoveType::Forward2      },

        {  -9, PawnMoveType::CaptureLeft   },
        {  -7, PawnMoveType::CaptureRight  },

        {  -9, PawnMoveType::EnPassantLeft },
        {  -7, PawnMoveType::EnPassantRight}
    }};
};