#include "DomeRenderer3D.h"

#include "InputKeyboard.h"

#include <iostream>

#include <glad/glad.h>

#include <glm/common.hpp>



//====================================================
// CONSTRUCTOR
//====================================================

DomeRenderer3D::DomeRenderer3D()
{

}



//====================================================
// INITIALIZATION
//====================================================

bool DomeRenderer3D::initialize()
{

    dome.initialize();


    ground.initialize();



    if(
        !hdriTexture.loadFromFile(
            "Assets/Environment/small_workshop_4k.exr"
        )
    )
    {

        std::cout
            << "[HDRI] ERROR loading EXR"
            << std::endl;

        return false;

    }



    if(
        !domeShader.initialize()
    )
    {

        return false;

    }



    if(
        !groundShader.initialize()
    )
    {

        return false;

    }



    std::cout
        << "[DOME] Environment initialized"
        << std::endl;



    return true;

}






//====================================================
// UPDATE
//====================================================

void DomeRenderer3D::update(
    float dt
)
{


    float scaleSpeed = 0.4f;

    float zoomSpeed = 0.6f;

    float horizonSpeed = 0.5f;

    float rotationSpeed = 1.5f;



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_Y)
    )
    {
        hdriScaleY -= scaleSpeed * dt;
    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_H)
    )
    {
        hdriScaleY += scaleSpeed * dt;
    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_U)
    )
    {
        hdriScaleX -= scaleSpeed * dt;
    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_J)
    )
    {
        hdriScaleX += scaleSpeed * dt;
    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_I)
    )
    {
        hdriZoom += zoomSpeed * dt;
    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_K)
    )
    {
        hdriZoom -= zoomSpeed * dt;
    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_T)
    )
    {
        hdriHorizon += horizonSpeed * dt;
    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_G)
    )
    {
        hdriHorizon -= horizonSpeed * dt;
    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_R)
    )
    {
        hdriRotation += rotationSpeed * dt;
    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_F)
    )
    {
        hdriRotation -= rotationSpeed * dt;
    }



    hdriScaleX =
        glm::clamp(
            hdriScaleX,
            0.25f,
            4.0f
        );


    hdriScaleY =
        glm::clamp(
            hdriScaleY,
            0.25f,
            4.0f
        );


    hdriZoom =
        glm::clamp(
            hdriZoom,
            0.25f,
            4.0f
        );

}





//====================================================
// BACKGROUND
//====================================================

void DomeRenderer3D::renderBackground(
    Renderer3D& renderer,
    Shader3D& shader,
    Camera3D& camera,
    float aspectRatio
)
{


    //------------------------------------------------
    // DOME
    //------------------------------------------------

    glDisable(
        GL_CULL_FACE
    );


    glDisable(
        GL_DEPTH_TEST
    );



    domeShader.bind();



    hdriTexture.bind(0);



    domeShader.setHDRITextureSlot(0);


    domeShader.setExposure(1.0f);


    domeShader.setRotation(
        hdriRotation
    );


    domeShader.setScaleX(
        hdriScaleX
    );


    domeShader.setScaleY(
        hdriScaleY
    );


    domeShader.setZoom(
        hdriZoom
    );


    domeShader.setHorizon(
        hdriHorizon
    );



    renderer.renderObject(
        dome.getMesh(),
        dome.getTransform(),
        dome.getMaterial(),
        domeShader,
        camera,
        aspectRatio
    );





    //------------------------------------------------
    // GROUND
    //------------------------------------------------

    glEnable(
        GL_DEPTH_TEST
    );



    groundShader.bind();


    hdriTexture.bind(0);



    groundShader.setHDRITextureSlot(0);


    groundShader.setExposure(1.0f);



    groundShader.setRotation(
        hdriRotation
    );


    groundShader.setScaleX(
        hdriScaleX
    );


    groundShader.setScaleY(
        hdriScaleY
    );


    groundShader.setZoom(
        hdriZoom
    );


    groundShader.setHorizon(
        hdriHorizon
    );



    //------------------------------------------------
    // IMPORTANTE
    //
    // Continuidad cámara -> suelo
    //
    //------------------------------------------------

    groundShader.setCameraPosition(
        camera.getPosition()
    );



    renderer.renderObject(
        ground.getMesh(),
        ground.getTransform(),
        ground.getMaterial(),
        groundShader,
        camera,
        aspectRatio
    );


}





//====================================================
// OBJECTS
//====================================================

void DomeRenderer3D::renderObjects(
    Renderer3D&,
    Shader3D&,
    Camera3D&,
    float
)
{

}