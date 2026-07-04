#pragma once

#include <cstdint>
#include "ChessTypes.h"

class ChessRules
{
public:

    // PIECE TYPE CHECKS
    static bool isWhitePiece(Piece piece);
    static bool isBlackPiece(Piece piece);

    static bool isPawn(Piece piece);
    static bool isKnight(Piece piece);
    static bool isBishop(Piece piece);
    static bool isRook(Piece piece);
    static bool isQueen(Piece piece);
    static bool isKing(Piece piece);

    static bool isEmpty(Piece p);

    // RELATIONS (PURE LOGIC ONLY)
    static bool areEnemies(Piece a, Piece b);
    static bool areAllies(Piece a, Piece b);

    // PAWN RULES
    static int pawnDirection(Piece pawn);

    static bool isPromotionRowWhite(uint8_t row);
    static bool isPromotionRowBlack(uint8_t row);

    static bool isPawnStartRowWhite(uint8_t row);
    static bool isPawnStartRowBlack(uint8_t row);

    // SPECIAL
    static bool canCastle(Piece king);
};