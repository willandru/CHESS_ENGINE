#include "ChessRenderer.h"

#include "ChessGame.h"

#include "ChessBoardRenderer.h"
#include "ChessPieceRenderer.h"
#include "HighlightRenderer.h"
#include "PromotionRenderer.h"

#include "BoardView.h"
#include "Window.h"
#include "MoveFilter.h"

extern Window gWindow;

void ChessRenderer::render(
    Shader& boardShader,
    Shader& pieceShader,
    const ChessGame& game)
{
    const GameState& state = game.getGameState();

    BoardView view = BoardView::compute(
        gWindow.getWindowWidth(),
        gWindow.getWindowHeight()
    );

    //------------------------------------------------
    // BOARD
    //------------------------------------------------
    ChessBoardRenderer::render(boardShader);

    //------------------------------------------------
    // STATUS (CHECK / MATE)
    //------------------------------------------------
    PlayerSide side = state.getTurn();

    bool inCheck = MoveFilter::isKingInCheck(state, side);
    bool inMate  = MoveFilter::isCheckmate(state, side);

    uint8_t kingSq = state.findKing(side);

    if (kingSq != 255)
    {
        if (inMate)
        {
            HighlightRenderer::render(
                boardShader,
                kingSq,
                1.0f, 0.0f, 0.0f,
                view
            );
        }
        else if (inCheck)
        {
            HighlightRenderer::render(
                boardShader,
                kingSq,
                0.0f, 0.4f, 1.0f,
                view
            );
        }
    }

    //------------------------------------------------
    // PIECE SELECTION UI
    //------------------------------------------------
    if (game.hasSelection())
    {
        HighlightRenderer::render(
            boardShader,
            game.getSelectedSquare(),
            0.15f, 0.85f, 0.20f,
            view
        );

        HighlightRenderer::renderMoves(
            boardShader,
            game.getMoves(),
            0.85f, 0.85f, 0.15f,
            view
        );
    }

    //------------------------------------------------
    // PIECES
    //------------------------------------------------
    const Piece* board = state.getBoard();

    for (uint8_t sq = 0; sq < 64; ++sq)
    {
        ChessPieceRenderer::render(pieceShader, board[sq], sq, view);
    }

    //------------------------------------------------
    // PROMOTION UI (OVERLAY FINAL)
    //------------------------------------------------
    if (game.isPromotionPending())
    {
        PromotionRenderer::render(
            pieceShader,
            state.getTurn() == PlayerSide::White,
            view
        );
    }
}