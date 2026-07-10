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

    //------------------------------------------------
    // BOARD SHADER
    //------------------------------------------------

    if(!boardShader.load(
        vertexShader,
        fragmentShader
    ))
    {
        return false;
    }



    //------------------------------------------------
    // PIECE SHADER
    //------------------------------------------------

    if(!pieceShader.load(
        "Shaders/basic_piece_3d.vert",
        "Shaders/basic_piece_3d.frag"
    ))
    {
        return false;
    }



    //------------------------------------------------
    // OPENGL OPTIONS
    //------------------------------------------------

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
        boardShader,
        camera,
        aspectRatio
    );



    //------------------------------------------------
    // TEST PIECES
    //------------------------------------------------


    pieceRenderer.render(
        renderer,
        pieceShader,
        camera,
        aspectRatio,
        Piece::WHITE_ROOK,
        27
    );



    pieceRenderer.render(
        renderer,
        pieceShader,
        camera,
        aspectRatio,
        Piece::BLACK_ROOK,
        1
    );



    //------------------------------------------------
    // FUTURE:
    // recorrer GameState
    // y renderizar todas las piezas
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