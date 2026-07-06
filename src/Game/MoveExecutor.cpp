#include "MoveExecutor.h"

#include "ChessRules.h"
#include "InitialPosition.h"

#include <cstdlib>

//====================================================
// EXECUTE MOVE
//====================================================

MoveExecutor::Undo MoveExecutor::execute(
    GameState& state,
    const Move& move)
{
    Undo undo;

    undo.captured              = state.getPiece(move.to);
    undo.previousEnPassant     = state.getEnPassantSquare();
    undo.previousCastleRights  = state.getCastleRights();
    undo.previousTurn          = state.getTurn();
    undo.previousHalfMoveClock = state.getHalfMoveClock();

    Piece piece = state.getPiece(move.from);

    if (piece == EMPTY)
        return undo;

    //================================================
    // FIFTY-MOVE RULE
    //================================================

    if (ChessRules::isPawn(piece) ||
        undo.captured != EMPTY ||
        move.isEnPassant())
    {
        state.resetHalfMoveClock();
    }
    else
    {
        state.incrementHalfMoveClock();
    }

    //================================================
    // RESET EN PASSANT
    //================================================

    state.clearEnPassant();

    //================================================
    // UPDATE CASTLING RIGHTS
    //================================================

    switch (piece)
    {
        case WHITE_KING:
            state.removeAllCastle(PlayerSide::White);
            break;

        case BLACK_KING:
            state.removeAllCastle(PlayerSide::Black);
            break;

        case WHITE_ROOK:

            if (move.from == InitialPosition::WHITE_ROOK_KINGSIDE)
                state.removeKingsideCastle(PlayerSide::White);

            if (move.from == InitialPosition::WHITE_ROOK_QUEENSIDE)
                state.removeQueensideCastle(PlayerSide::White);

            break;

        case BLACK_ROOK:

            if (move.from == InitialPosition::BLACK_ROOK_KINGSIDE)
                state.removeKingsideCastle(PlayerSide::Black);

            if (move.from == InitialPosition::BLACK_ROOK_QUEENSIDE)
                state.removeQueensideCastle(PlayerSide::Black);

            break;

        default:
            break;
    }

    //------------------------------------------------
    // Si se captura una torre inicial también se pierde
    // ese derecho de enroque.
    //------------------------------------------------

    switch (undo.captured)
    {
        case WHITE_ROOK:

            if (move.to == InitialPosition::WHITE_ROOK_KINGSIDE)
                state.removeKingsideCastle(PlayerSide::White);

            if (move.to == InitialPosition::WHITE_ROOK_QUEENSIDE)
                state.removeQueensideCastle(PlayerSide::White);

            break;

        case BLACK_ROOK:

            if (move.to == InitialPosition::BLACK_ROOK_KINGSIDE)
                state.removeKingsideCastle(PlayerSide::Black);

            if (move.to == InitialPosition::BLACK_ROOK_QUEENSIDE)
                state.removeQueensideCastle(PlayerSide::Black);

            break;

        default:
            break;
    }

    //================================================
    // DOUBLE PAWN PUSH
    //================================================

    if (piece == WHITE_PAWN ||
        piece == BLACK_PAWN)
    {
        int fr = GameState::getRow(move.from);
        int tr = GameState::getRow(move.to);

        if (std::abs(tr - fr) == 2)
        {
            uint8_t ep =
                GameState::getSquare(
                    (fr + tr) / 2,
                    GameState::getCol(move.from));

            state.setEnPassantSquare(ep);
        }
    }

    //================================================
    // NORMAL MOVE
    //================================================

    state.setPiece(move.to, piece);
    state.setPiece(move.from, EMPTY);

    //================================================
    // PROMOTION
    //================================================

    if (move.isPromotion())
    {
        state.setPiece(
            move.to,
            move.promo);
    }

    //================================================
    // EN PASSANT
    //================================================

    if (move.isEnPassant())
    {
        int dir =
            ChessRules::pawnDirection(piece);

        uint8_t capturedSquare =
            GameState::getSquare(
                GameState::getRow(move.to) - dir,
                GameState::getCol(move.to));

        undo.captured =
            state.getPiece(capturedSquare);

        state.setPiece(
            capturedSquare,
            EMPTY);
    }

    //================================================
    // CASTLE
    //================================================

    if (move.isCastle())
    {
        switch (move.to)
        {
            case 62:
                state.setPiece(61, WHITE_ROOK);
                state.setPiece(63, EMPTY);
                break;

            case 58:
                state.setPiece(59, WHITE_ROOK);
                state.setPiece(56, EMPTY);
                break;

            case 6:
                state.setPiece(5, BLACK_ROOK);
                state.setPiece(7, EMPTY);
                break;

            case 2:
                state.setPiece(3, BLACK_ROOK);
                state.setPiece(0, EMPTY);
                break;
        }
    }

    //================================================
    // NEXT TURN
    //================================================

    state.switchTurn();

    return undo;
}

//====================================================
// UNDO MOVE
//====================================================

void MoveExecutor::undo(
    GameState& state,
    const Move& move,
    const Undo& undo)
{
    state.setTurn(undo.previousTurn);

    state.setHalfMoveClock(
        undo.previousHalfMoveClock);

    state.setEnPassantSquare(
        undo.previousEnPassant);

    state.setCastleRights(
        undo.previousCastleRights);

    Piece moved =
        state.getPiece(move.to);

    //================================================
    // PROMOTION
    //================================================

    if (move.isPromotion())
    {
        moved =
            ChessRules::isWhitePiece(moved)
            ? WHITE_PAWN
            : BLACK_PAWN;
    }

    state.setPiece(
        move.from,
        moved);

    state.setPiece(
        move.to,
        undo.captured);

    //================================================
    // EN PASSANT
    //================================================

    if (move.isEnPassant())
    {
        state.setPiece(
            move.to,
            EMPTY);

        int dir =
            ChessRules::pawnDirection(moved);

        uint8_t capturedSquare =
            GameState::getSquare(
                GameState::getRow(move.to) - dir,
                GameState::getCol(move.to));

        state.setPiece(
            capturedSquare,
            undo.captured);
    }

    //================================================
    // CASTLE
    //================================================

    if (move.isCastle())
    {
        switch (move.to)
        {
            // White kingside
            case 62:
                state.setPiece(63, WHITE_ROOK);
                state.setPiece(61, EMPTY);
                break;

            // White queenside
            case 58:
                state.setPiece(56, WHITE_ROOK);
                state.setPiece(59, EMPTY);
                break;

            // Black kingside
            case 6:
                state.setPiece(7, BLACK_ROOK);
                state.setPiece(5, EMPTY);
                break;

            // Black queenside
            case 2:
                state.setPiece(0, BLACK_ROOK);
                state.setPiece(3, EMPTY);
                break;
        }
    }
}