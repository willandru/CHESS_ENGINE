#include "PawnMoves.h"

#include "ChessTypes.h"

void PawnMoves::generate(
    const GameState& state,
    uint8_t square,
    std::vector<Move>& moves)
{
    Piece p = state.getPiece(square);

    if (p == EMPTY)
        return;

    uint8_t row = GameState::getRow(square);
    uint8_t col = GameState::getCol(square);

    bool isWhite = (p >= WHITE_PAWN && p <= WHITE_KING);

    int dir = isWhite ? -1 : 1;

    int startRow = isWhite ? 6 : 1;

    //-----------------------------
    // Forward 1
    //-----------------------------
    int r1 = row + dir;

    if (r1 >= 0 && r1 < 8)
    {
        uint8_t to = GameState::getSquare(r1, col);

        if (state.getPiece(to) == EMPTY)
        {
            addMove(state, square, to, moves);

            //-------------------------
            // Forward 2 (initial)
            //-------------------------
            if (row == startRow)
            {
                int r2 = row + 2 * dir;
                uint8_t to2 = GameState::getSquare(r2, col);

                if (state.getPiece(to2) == EMPTY)
                {
                    Move m(square, to2);
                    moves.push_back(m);
                }
            }
        }
    }

    //-----------------------------
    // Captures
    //-----------------------------
    for (int dc : {-1, 1})
    {
        int cc = col + dc;
        int rr = row + dir;

        if (cc < 0 || cc > 7)
            continue;

        if (rr < 0 || rr > 7)
            continue;

        uint8_t to = GameState::getSquare(rr, cc);
        Piece target = state.getPiece(to);

        if (target != EMPTY && isEnemy(p, target))
        {
            Move m(square, to);
            m.setFlag(Move::CAPTURE);
            m.captured = target;

            moves.push_back(m);
        }
    }
}

void PawnMoves::addMove(
    const GameState& state,
    uint8_t from,
    uint8_t to,
    std::vector<Move>& moves)
{
    (void)state;

    Move m(from, to);
    moves.push_back(m);
}

bool PawnMoves::isEnemy(
    Piece a,
    Piece b)
{
    if (b == EMPTY)
        return false;

    bool whiteA = (a >= WHITE_PAWN && a <= WHITE_KING);
    bool whiteB = (b >= WHITE_PAWN && b <= WHITE_KING);

    return whiteA != whiteB;
}