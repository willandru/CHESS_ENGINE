#include "ChessRenderer3D.h"

#include "Window.h"

#include <glm/glm.hpp>

extern Window gWindow;



ChessRenderer3D::ChessRenderer3D()
{
}



//====================================================
// INITIALIZATION
//====================================================

bool ChessRenderer3D::initialize(
    const std::string& vertexShader,
    const std::string& fragmentShader
)
{
    if (!shader.load(
        vertexShader,
        fragmentShader
    ))
    {
        return false;
    }

    renderer.enableDepthTest();

    renderer.enableFaceCulling();


    //------------------------------------------------
    // LOAD PIECES
    //------------------------------------------------

    if(!pieceRenderer.initialize())
    {
        return false;
    }

    return true;
}



//====================================================
// RENDER
//====================================================

void ChessRenderer3D::render()
{
    renderer.beginFrame(
        glm::vec4(
            0.15f,
            0.15f,
            0.18f,
            1.0f
        )
    );


    float aspectRatio =
        static_cast<float>(
            gWindow.getWindowWidth()
        )
        /
        static_cast<float>(
            gWindow.getWindowHeight()
        );


    //------------------------------------------------
    // BOARD
    //------------------------------------------------

    boardRenderer.render(
        renderer,
        shader,
        camera,
        aspectRatio
    );

    //------------------------------------------------
    // TEST PIECE
    //------------------------------------------------

    pieceRenderer.render(
        renderer,
        shader,
        camera,
        aspectRatio,
        Piece::WHITE_ROOK,
        27          // casilla de prueba (centro)
    );

    //------------------------------------------------
    // PIECES
    //------------------------------------------------
    //
    // AÚN FALTA RECORRER EL GAMESTATE.
    // Aquí después iremos llamando:
    //
    // pieceRenderer.render(...)
    //
    // para cada casilla ocupada.
    //
    //------------------------------------------------


    renderer.endFrame();
}



//====================================================
// CAMERA
//====================================================

Camera3D& ChessRenderer3D::getCamera()
{
    return camera;
}