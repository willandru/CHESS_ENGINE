#include "CupulaRenderer3D.h"


#include "InputKeyboard.h"


#include <iostream>


#include <glad/glad.h>


#include <glm/common.hpp>



//====================================================
// CONSTRUCTOR
//====================================================

CupulaRenderer3D::CupulaRenderer3D()
{

}



//====================================================
// INITIALIZATION
//====================================================

bool CupulaRenderer3D::initialize()
{

    cupula.initialize();



    if(
        !hdriTexture.loadFromFile(
            "Assets/Environment/horn-koppe_snow_8k.exr"
        )
    )
    {

        std::cout
            << "[HDRI] ERROR loading EXR"
            << std::endl;


        return false;

    }



    if(
        !cupulaShader.initialize()
    )
    {

        return false;

    }



    std::cout
        << "[CUPULA] Environment initialized"
        << std::endl;



    return true;

}



//====================================================
// UPDATE
//====================================================

void CupulaRenderer3D::update(
    Camera3D& camera,
    float dt
)
{

    float rotationSpeed = 1.5f;

    float scaleSpeed = 0.4f;

    float horizonSpeed = 0.5f;



    //------------------------------------------------
    // HDRI ROTATION
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

}



//====================================================
// BACKGROUND
//====================================================

void CupulaRenderer3D::renderBackground(
    Renderer3D& renderer,
    Shader3D&,
    Camera3D& camera,
    float aspectRatio
)
{

    //------------------------------------------------
    // ENVIRONMENT SETTINGS
    //------------------------------------------------

    glDisable(
        GL_CULL_FACE
    );


    glDisable(
        GL_DEPTH_TEST
    );



    cupulaShader.bind();



    hdriTexture.bind(0);



    cupulaShader.setHDRITextureSlot(
        0
    );



    cupulaShader.setExposure(
        exposure
    );



    cupulaShader.setRotation(
        hdriRotation
    );



    cupulaShader.setScaleX(
        hdriScaleX
    );



    cupulaShader.setScaleY(
        hdriScaleY
    );



    cupulaShader.setHorizon(
        hdriHorizon
    );



    //------------------------------------------------
    // DRAW COMPLETE CUPULA
    //------------------------------------------------

    renderer.renderObject(
        cupula.getMesh(),
        cupula.getTransform(),
        cupula.getMaterial(),
        cupulaShader,
        camera,
        aspectRatio
    );



    glEnable(
        GL_DEPTH_TEST
    );

}



//====================================================
// OBJECTS
//====================================================

void CupulaRenderer3D::renderObjects(
    Renderer3D&,
    Shader3D&,
    Camera3D&,
    float
)
{

}