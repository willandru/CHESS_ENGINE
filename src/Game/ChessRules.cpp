#include "ChessRules.h"

//==============================
// PIECE TYPES
//==============================

bool ChessRules::isWhitePiece(Piece piece)
{
    return piece >= WHITE_PAWN && piece <= WHITE_KING;
}

bool ChessRules::isBlackPiece(Piece piece)
{
    return piece >= BLACK_PAWN && piece <= BLACK_KING;
}

bool ChessRules::isPawn(Piece piece)
{
    return piece == WHITE_PAWN || piece == BLACK_PAWN;
}

bool ChessRules::isKnight(Piece piece)
{
    return piece == WHITE_KNIGHT || piece == BLACK_KNIGHT;
}

bool ChessRules::isBishop(Piece piece)
{
    return piece == WHITE_BISHOP || piece == BLACK_BISHOP;
}

bool ChessRules::isRook(Piece piece)
{
    return piece == WHITE_ROOK || piece == BLACK_ROOK;
}

bool ChessRules::isQueen(Piece piece)
{
    return piece == WHITE_QUEEN || piece == BLACK_QUEEN;
}

bool ChessRules::isKing(Piece piece)
{
    return piece == WHITE_KING || piece == BLACK_KING;
}

bool ChessRules::isEmpty(Piece p)
{
    return p == EMPTY;
}

//==============================
// RELATIONS (PURE)
//==============================

bool ChessRules::areEnemies(Piece a, Piece b)
{
    if (a == EMPTY || b == EMPTY)
        return false;

    return isWhitePiece(a) != isWhitePiece(b);
}

bool ChessRules::areAllies(Piece a, Piece b)
{
    if (a == EMPTY || b == EMPTY)
        return false;

    return isWhitePiece(a) == isWhitePiece(b);
}

//==============================
// PAWN RULES
//==============================

int ChessRules::pawnDirection(Piece pawn)
{
    if (pawn == WHITE_PAWN) return -1;
    if (pawn == BLACK_PAWN) return +1;
    return 0;
}

bool ChessRules::isPromotionRowWhite(uint8_t row)
{
    return row == 0;
}

bool ChessRules::isPromotionRowBlack(uint8_t row)
{
    return row == 7;
}

bool ChessRules::isPawnStartRowWhite(uint8_t row)
{
    return row == 6;
}

bool ChessRules::isPawnStartRowBlack(uint8_t row)
{
    return row == 1;
}

//==============================
// SPECIAL
//==============================

bool ChessRules::canCastle(Piece king)
{
    return king == WHITE_KING || king == BLACK_KING;
}