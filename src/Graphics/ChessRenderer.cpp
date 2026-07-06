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

//====================================================
// MAIN RENDER PIPELINE
//====================================================
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
    // 1. BOARD
    //------------------------------------------------
    ChessBoardRenderer::render(boardShader);

    //------------------------------------------------
    // 2. CHECK / MATE VISUALIZATION
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
    // 3. PIECE SELECTION (DISABLED DURING PROMOTION)
    //------------------------------------------------
    if (game.hasSelection() && !game.isPromotionPending())
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
    // 4. PIECES
    //------------------------------------------------
    const Piece* board = state.getBoard();

    for (uint8_t sq = 0; sq < 64; ++sq)
    {
        ChessPieceRenderer::render(pieceShader, board[sq], sq, view);
    }

    //------------------------------------------------
    // 5. PROMOTION UI (FINAL LAYER)
    //------------------------------------------------
    if (game.isPromotionPending())
    {
        // 🔥 IMPORTANTE: usar snapshot, NO estado actual del turno
        bool whiteSide = (game.getPromotionSelectedSide() == 0);

        PromotionRenderer::render(
            pieceShader,
            whiteSide,
            view
        );
    }
}