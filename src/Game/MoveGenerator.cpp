#include "MoveGenerator.h"

//====================================================
// TURN FILTER (CLAVE DEL DISEÑO)
//====================================================

bool MoveGenerator::isCorrectTurn(const GameState& state, Piece piece)
{
    if (piece == EMPTY)
        return false;

    if (ChessRules::isWhitePiece(piece))
        return state.getTurn() == PlayerSide::White;

    return state.getTurn() == PlayerSide::Black;
}

//====================================================
// PUBLIC API
//====================================================

void MoveGenerator::generatePieceMoves(
    const GameState& state,
    uint8_t square,
    std::vector<Move>& moves)
{
    Piece p = state.getPiece(square);

    if (p == EMPTY)
        return;

    // 🔴 FILTRO DE TURNO GLOBAL
    if (!isCorrectTurn(state, p))
        return;

    switch (p)
    {
        case WHITE_PAWN:
        case BLACK_PAWN:
            generatePawn(state, square, moves);
            break;

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            generateKnight(state, square, moves);
            break;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            generateBishop(state, square, moves);
            break;

        case WHITE_ROOK:
        case BLACK_ROOK:
            generateRook(state, square, moves);
            break;

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            generateQueen(state, square, moves);
            break;

        case WHITE_KING:
        case BLACK_KING:
            generateKing(state, square, moves);
            break;

        default:
            break;
    }
}

//====================================================
// ALL MOVES (for validation or AI)
//====================================================

void MoveGenerator::generateAllMoves(
    const GameState& state,
    std::vector<Move>& moves)
{
    moves.clear();

    for (uint8_t sq = 0; sq < 64; ++sq)
    {
        Piece p = state.getPiece(sq);

        if (p == EMPTY)
            continue;

        if (!isCorrectTurn(state, p))
            continue;

        generatePieceMoves(state, sq, moves);
    }
}

//====================================================
// HELPERS
//====================================================

bool MoveGenerator::isInsideBoard(int square)
{
    return square >= 0 && square < 64;
}

bool MoveGenerator::isSameColor(Piece a, Piece b)
{
    if (a == EMPTY || b == EMPTY)
        return false;

    return ChessRules::isWhitePiece(a) == ChessRules::isWhitePiece(b);
}

bool MoveGenerator::isEnemy(Piece a, Piece b)
{
    if (b == EMPTY)
        return false;

    return !isSameColor(a, b);
}



//====================================================
// KNIGHT
//====================================================

void MoveGenerator::generateKnight(
    const GameState& state,
    uint8_t square,
    std::vector<Move>& moves)
{
    Piece p = state.getPiece(square);

    for (int8_t off : KnightMoves::moves)
    {
        int to = square + off;

        if (!isInsideBoard(to))
            continue;

        // FIX: evita wrap-around horizontal/vertical inválido
        if (!isValidKnightMove(square, to))
            continue;

        Piece target = state.getPiece(to);

        if (isSameColor(p, target))
            continue;

        Move m(square, to);

        if (isEnemy(p, target))
            m.setFlag(Move::CAPTURE);

        moves.push_back(m);
    }
}
//====================================================
// KING
//====================================================

void MoveGenerator::generateKing(
    const GameState& state,
    uint8_t square,
    std::vector<Move>& moves)
{
    Piece p = state.getPiece(square);

    for (int8_t off : KingMoves::moves)
    {
        int to = square + off;

        if (!isInsideBoard(to))
            continue;

        // FIX borde tablero
        if (!isValidKingMove(square, to))
            continue;

        Piece target = state.getPiece(to);

        if (isSameColor(p, target))
            continue;

        Move m(square, to);

        if (isEnemy(p, target))
            m.setFlag(Move::CAPTURE);

        moves.push_back(m);
    }
}

//====================================================
// ROOK
//====================================================

void MoveGenerator::generateRook(
    const GameState& state,
    uint8_t square,
    std::vector<Move>& moves)
{
    Piece p = state.getPiece(square);

    for (int8_t dir : RookMoves::directions)
    {
        int to = square;

        while (true)
        {
            int previous = to;
            to += dir;

            if (!isInsideBoard(to))
                break;

            if (crossedEdge(previous, to, dir))
                break;

            Piece target = state.getPiece(to);

            if (isSameColor(p, target))
                break;

            Move m(square, to);

            if (isEnemy(p, target))
            {
                m.setFlag(Move::CAPTURE);
                moves.push_back(m);
                break;
            }

            moves.push_back(m);
        }
    }
}

//====================================================
// BISHOP
//====================================================

void MoveGenerator::generateBishop(
    const GameState& state,
    uint8_t square,
    std::vector<Move>& moves)
{
    Piece p = state.getPiece(square);

    for (int8_t dir : BishopMoves::directions)
    {
        int to = square;

        while (true)
        {
            int previous = to;
            to += dir;

            if (!isInsideBoard(to))
                break;

            if (crossedEdge(previous, to, dir))
                break;

            Piece target = state.getPiece(to);

            if (isSameColor(p, target))
                break;

            Move m(square, to);

            if (isEnemy(p, target))
            {
                m.setFlag(Move::CAPTURE);
                moves.push_back(m);
                break;
            }

            moves.push_back(m);
        }
    }
}

//====================================================
// QUEEN
//====================================================

void MoveGenerator::generateQueen(
    const GameState& state,
    uint8_t square,
    std::vector<Move>& moves)
{
    generateRook(state, square, moves);
    generateBishop(state, square, moves);
}

//====================================================
// PAWN
//====================================================
void MoveGenerator::generatePawn(
    const GameState& state,
    uint8_t square,
    std::vector<Move>& moves)
{
    Piece p = state.getPiece(square);

    int dir = ChessRules::pawnDirection(p);
    if (dir == 0)
        return;

    int row = square >> 3;
    int col = square & 7;

    int startRow = (p == WHITE_PAWN) ? 6 : 1;

    //====================================================
    // SINGLE PUSH
    //====================================================
    int forward = square + (8 * dir);

    if (isInsideBoard(forward) &&
        state.getPiece(forward) == EMPTY)
    {
        moves.emplace_back(square, forward);

        //================================================
        // DOUBLE PUSH
        //================================================
        int forward2 = square + (16 * dir);

        if (row == startRow &&
            state.getPiece(forward2) == EMPTY &&
            state.getPiece(forward) == EMPTY)
        {
            Move m2(square, forward2);
            moves.push_back(m2);
        }
    }

    //====================================================
    // NORMAL CAPTURES
    //====================================================
    int left  = square + (8 * dir) - 1;
    int right = square + (8 * dir) + 1;

    if (isInsideBoard(left) && isValidPawnCapture(square, left))
    {
        Piece t = state.getPiece(left);
        if (isEnemy(p, t))
        {
            Move m(square, left);
            m.setFlag(Move::CAPTURE);
            moves.push_back(m);
        }
    }

    if (isInsideBoard(right) && isValidPawnCapture(square, right))
    {
        Piece t = state.getPiece(right);
        if (isEnemy(p, t))
        {
            Move m(square, right);
            m.setFlag(Move::CAPTURE);
            moves.push_back(m);
        }
    }

    //====================================================
    // EN PASSANT (FIXED LOGIC)
    //====================================================
    int epSquare = state.getEnPassantSquare();

    if (epSquare != 255)
    {
        int epRow = epSquare >> 3;
        int epCol = epSquare & 7;

        // el peón atacante debe estar en la fila correcta
        bool validRank = (row == (p == WHITE_PAWN ? 3 : 4));

        if (validRank)
        {
            if (col - 1 == epCol || col + 1 == epCol)
            {
                Move m(square, epSquare);
                m.setFlag(Move::EN_PASSANT);
                moves.push_back(m);
            }
        }
    }
}


bool MoveGenerator::crossedEdge(int from, int to, int dir)
{
    int fromCol = from & 7;
    int toCol   = to & 7;

    switch (dir)
    {
        case 1:   return toCol != fromCol + 1;
        case -1:  return toCol != fromCol - 1;

        case 9:   return toCol != fromCol + 1;
        case -9:  return toCol != fromCol - 1;

        case 7:   return toCol != fromCol - 1;
        case -7:  return toCol != fromCol + 1;
    }

    return false;
}

bool MoveGenerator::isValidKnightMove(int from, int to)
{
    int fr = from >> 3;
    int fc = from & 7;

    int tr = to >> 3;
    int tc = to & 7;

    int dr = fr - tr;
    int dc = fc - tc;

    if (dr < 0) dr = -dr;
    if (dc < 0) dc = -dc;

    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

bool MoveGenerator::isValidKingMove(int from, int to)
{
    int fr = from >> 3;
    int fc = from & 7;

    int tr = to >> 3;
    int tc = to & 7;

    int dr = fr - tr;
    int dc = fc - tc;

    if (dr < 0) dr = -dr;
    if (dc < 0) dc = -dc;

    return (dr <= 1 && dc <= 1);
}

bool MoveGenerator::isValidPawnCapture(int from, int to)
{
    int fc = from & 7;
    int tc = to & 7;

    int dc = fc - tc;

    return (dc == 1 || dc == -1);
}


bool MoveGenerator::attacksSquare(
    const GameState& state,
    uint8_t from,
    uint8_t target)
{
    Piece p = state.getPiece(from);

    if (p == EMPTY)
        return false;

    int fr = from >> 3;
    int fc = from & 7;

    int tr = target >> 3;
    int tc = target & 7;

    int dr = tr - fr;
    int dc = tc - fc;

    auto absv = [](int x) { return x < 0 ? -x : x; };

    switch (p)
    {
        //==================================================
        // PAWN
        //==================================================
        case WHITE_PAWN:
            return (dr == -1 && (dc == -1 || dc == 1));

        case BLACK_PAWN:
            return (dr == 1 && (dc == -1 || dc == 1));

        //==================================================
        // KNIGHT
        //==================================================
        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
        {
            return (absv(dr) == 2 && absv(dc) == 1) ||
                   (absv(dr) == 1 && absv(dc) == 2);
        }

        //==================================================
        // KING
        //==================================================
        case WHITE_KING:
        case BLACK_KING:
        {
            return absv(dr) <= 1 && absv(dc) <= 1;
        }

        //==================================================
        // ROOK
        //==================================================
        case WHITE_ROOK:
        case BLACK_ROOK:
        {
            if (fr != tr && fc != tc)
                return false;

            int step = (fr == tr)
                ? ((tc > fc) ? 1 : -1)
                : ((tr > fr) ? 8 : -8);

            int sq = from + step;

            while (sq != target)
            {
                if (state.getPiece(sq) != EMPTY)
                    return false;
                sq += step;
            }

            return true;
        }

        //==================================================
        // BISHOP
        //==================================================
        case WHITE_BISHOP:
        case BLACK_BISHOP:
        {
            if (absv(dr) != absv(dc))
                return false;

            int step = ((tr > fr) ? 8 : -8) +
                       ((tc > fc) ? 1 : -1);

            int sq = from + step;

            while (sq != target)
            {
                if (state.getPiece(sq) != EMPTY)
                    return false;
                sq += step;
            }

            return true;
        }

        //==================================================
        // QUEEN (FIX REAL)
        //==================================================
        case WHITE_QUEEN:
        case BLACK_QUEEN:
        {
            // rook-like
            bool rookLine = (fr == tr || fc == tc);

            // bishop-like
            bool bishopLine = (absv(dr) == absv(dc));

            if (rookLine)
            {
                int step = (fr == tr)
                    ? ((tc > fc) ? 1 : -1)
                    : ((tr > fr) ? 8 : -8);

                int sq = from + step;

                while (sq != target)
                {
                    if (state.getPiece(sq) != EMPTY)
                        return false;
                    sq += step;
                }

                return true;
            }

            if (bishopLine)
            {
                int step = ((tr > fr) ? 8 : -8) +
                           ((tc > fc) ? 1 : -1);

                int sq = from + step;

                while (sq != target)
                {
                    if (state.getPiece(sq) != EMPTY)
                        return false;
                    sq += step;
                }

                return true;
            }

            return false;
        }

        default:
            return false;
    }
}