#include "ChessBoardRenderer3D.h"

#include "SceneConstants.h"


ChessBoardRenderer3D::ChessBoardRenderer3D()
{
    //------------------------------------------------
    // BOARD POSITION
    //------------------------------------------------

   transform.setPosition(
    {
        SceneConstants::BOARD_POSITION_X,

        SceneConstants::BOARD_HEIGHT,

        SceneConstants::BOARD_POSITION_Z
    });

    transform.setRotation(
    {
        0.0f,
        0.0f,
        0.0f
    });


    transform.setScale(
    {
        1.0f,
        1.0f,
        1.0f
    });
}


//====================================================
// RENDER
//====================================================

void ChessBoardRenderer3D::render(
    Renderer3D& renderer,
    Shader3D& shader,
    Camera3D& camera,
    float aspectRatio
)
{
    renderer.draw(
        boardMesh.getMesh(),
        transform,
        shader,
        camera,
        aspectRatio
    );
}