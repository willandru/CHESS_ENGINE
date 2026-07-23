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
            "Assets/Environment/pine_attic_8k.exr"
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
    Camera3D& camera,
    float dt
)
{

    float scaleSpeed = 0.4f;

    float fieldOfViewSpeed = 30.0f;

    float horizonSpeed = 0.5f;

    float rotationSpeed = 1.5f;

    float captureSpeed = 1.0f;



    //------------------------------------------------
    // SCALE Y
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(GLFW_KEY_Y)
    )
    {

        hdriScaleY -=
            scaleSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_H)
    )
    {

        hdriScaleY +=
            scaleSpeed * dt;

    }



    //------------------------------------------------
    // SCALE X
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(GLFW_KEY_U)
    )
    {

        hdriScaleX -=
            scaleSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_J)
    )
    {

        hdriScaleX +=
            scaleSpeed * dt;

    }



    //------------------------------------------------
    // FIELD OF VIEW
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(GLFW_KEY_I)
    )
    {

        camera.zoomFieldOfView(
            -fieldOfViewSpeed * dt
        );

    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_K)
    )
    {

        camera.zoomFieldOfView(
            fieldOfViewSpeed * dt
        );

    }



    //------------------------------------------------
    // HORIZON
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(GLFW_KEY_T)
    )
    {

        hdriHorizon +=
            horizonSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_G)
    )
    {

        hdriHorizon -=
            horizonSpeed * dt;

    }



    //------------------------------------------------
    // ROTATION
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(GLFW_KEY_R)
    )
    {

        hdriRotation +=
            rotationSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_F)
    )
    {

        hdriRotation -=
            rotationSpeed * dt;

    }



    //------------------------------------------------
    // VIRTUAL HDRI CAMERA HEIGHT
    // O / L
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(GLFW_KEY_O)
    )
    {

        captureHeight +=
            captureSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_L)
    )
    {

        captureHeight -=
            captureSpeed * dt;

    }



    //------------------------------------------------
    // LIMITS
    //------------------------------------------------

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



    captureHeight =
        glm::clamp(
            captureHeight,
            0.1f,
            10.0f
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


    hdriTexture.bind(
        0
    );


    domeShader.setHDRITextureSlot(
        0
    );


    domeShader.setRotation(
        hdriRotation
    );


    domeShader.setScaleX(
        hdriScaleX
    );


    domeShader.setScaleY(
        hdriScaleY
    );


    domeShader.setHorizon(
        hdriHorizon
    );


    //------------------------------------------------
    // MISMA CAMARA VIRTUAL HDRI
    //------------------------------------------------

    domeShader.setVirtualCameraHeight(
        captureHeight
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
    // GROUND DISK
    //------------------------------------------------

    glEnable(
        GL_DEPTH_TEST
    );


    groundShader.bind();


    hdriTexture.bind(
        0
    );


    groundShader.setHDRITextureSlot(
        0
    );


    groundShader.setRotation(
        hdriRotation
    );


    groundShader.setScaleX(
        hdriScaleX
    );


    groundShader.setScaleY(
        hdriScaleY
    );


    groundShader.setHorizon(
        hdriHorizon
    );


    //------------------------------------------------
    // MISMA CAMARA VIRTUAL HDRI
    //------------------------------------------------

    groundShader.setVirtualCameraHeight(
        captureHeight
    );


    //------------------------------------------------
    // RADIO DE PROYECCION
    //------------------------------------------------

    groundShader.setProjectionDistance(
        projectionDistance
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