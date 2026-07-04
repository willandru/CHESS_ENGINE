#include "ChessRenderer.h"

#include "ChessGame.h"

#include "ChessBoardRenderer.h"
#include "ChessPieceRenderer.h"
#include "HighlightRenderer.h"

#include "BoardView.h"
#include "Window.h"

extern Window gWindow;

void ChessRenderer::render(
    Shader& boardShader,
    Shader& pieceShader,
    const ChessGame& game)
{
    BoardView view = BoardView::compute(
        gWindow.getWindowWidth(),
        gWindow.getWindowHeight()
    );

    //------------------------------------------------
    // BOARD
    //------------------------------------------------

    ChessBoardRenderer::render(boardShader);

    //------------------------------------------------
    // SELECTED SQUARE
    //------------------------------------------------

    if (game.hasSelection())
    {
        HighlightRenderer::render(
            boardShader,
            game.getSelectedSquare(),
            0.15f,
            0.85f,
            0.20f,
            view
        );
    }

    //------------------------------------------------
    // PIECES
    //------------------------------------------------

    const Piece* board =
        game.getGameState().getBoard();

    for (uint8_t square = 0; square < 64; ++square)
    {
        ChessPieceRenderer::render(
            pieceShader,
            board[square],
            square,
            view
        );
    }

    //------------------------------------------------
    // FUTURE:
    // - legal move highlights
    // - last move
    // - check
    // - checkmate
    // - etc.
    //------------------------------------------------
}