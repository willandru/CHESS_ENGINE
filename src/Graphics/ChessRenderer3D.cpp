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


    renderer.endFrame();
}



//====================================================
// CAMERA
//====================================================

Camera3D& ChessRenderer3D::getCamera()
{
    return camera;
}