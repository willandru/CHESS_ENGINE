#include "CupulaRenderer3D.h"

#include "CupulaConstants3D.h"

#include "CupulaMeshBuilder.h"

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
// INITIALIZE
//====================================================

bool CupulaRenderer3D::initialize()
{

    //------------------------------------------------
    // CREATE PROFILE
    //------------------------------------------------

    cupulaData.initialize();



    //------------------------------------------------
    // BUILD REVOLUTION MESH
    //------------------------------------------------

    CupulaMeshBuilder::build(
        cupulaMesh,

        cupulaData.getProfile(),

        CupulaConstants3D::RADIAL_SEGMENTS,

        CupulaConstants3D::CUPULA_COLOR
    );



    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    transform.setPosition(
    {
        CupulaConstants3D::CENTER_X,
        CupulaConstants3D::CENTER_Y,
        CupulaConstants3D::CENTER_Z
    });



    transform.setRotation(
    {
        CupulaConstants3D::ROT_X,
        CupulaConstants3D::ROT_Y,
        CupulaConstants3D::ROT_Z
    });



    transform.setScale(
    {
        1.0f,
        1.0f,
        1.0f
    });



    //------------------------------------------------
    // MATERIAL
    //------------------------------------------------

    material.setColor(
        CupulaConstants3D::CUPULA_COLOR
    );



    //------------------------------------------------
    // HDRI
    //------------------------------------------------

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



    //------------------------------------------------
    // SHADER
    //------------------------------------------------

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
    Camera3D&,
    float dt
)
{

    constexpr float rotationSpeed =
        1.5f;


    constexpr float scaleSpeed =
        0.4f;


    constexpr float horizonSpeed =
        0.5f;


    constexpr float captureHeightSpeed =
        1.0f;



    //------------------------------------------------
    // ROTATION
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_R
        )
    )
    {

        hdriRotation +=
            rotationSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_F
        )
    )
    {

        hdriRotation -=
            rotationSpeed * dt;

    }



    //------------------------------------------------
    // SCALE X
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_U
        )
    )
    {

        hdriScaleX -=
            scaleSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_J
        )
    )
    {

        hdriScaleX +=
            scaleSpeed * dt;

    }



    //------------------------------------------------
    // SCALE Y
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_Y
        )
    )
    {

        hdriScaleY -=
            scaleSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_H
        )
    )
    {

        hdriScaleY +=
            scaleSpeed * dt;

    }



    //------------------------------------------------
    // HORIZON
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_T
        )
    )
    {

        hdriHorizon +=
            horizonSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_G
        )
    )
    {

        hdriHorizon -=
            horizonSpeed * dt;

    }



    //------------------------------------------------
    // CAPTURE HEIGHT
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_O
        )
    )
    {

        captureHeight +=
            captureHeightSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_L
        )
    )
    {

        captureHeight -=
            captureHeightSpeed * dt;

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
            0.10f,
            5.00f
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
    // INSIDE ENVIRONMENT
    //------------------------------------------------

    glDisable(
        GL_CULL_FACE
    );


    glDepthMask(
        GL_FALSE
    );


    glDisable(
        GL_DEPTH_TEST
    );



    //------------------------------------------------
    // HDRI SHADER
    //------------------------------------------------

    cupulaShader.bind();



    //------------------------------------------------
    // HDRI TEXTURE
    //------------------------------------------------

    hdriTexture.bind(
        0
    );


    cupulaShader.setHDRITextureSlot(
        0
    );



    //------------------------------------------------
    // PARAMETERS
    //------------------------------------------------

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
    // CAPTURE HEIGHT
    //------------------------------------------------

    cupulaShader.setCaptureHeight(
        captureHeight
    );



    //------------------------------------------------
    // DRAW COMPLETE CUPULA
    //------------------------------------------------

    renderer.renderObject(
        cupulaMesh,
        transform,
        material,
        cupulaShader,
        camera,
        aspectRatio
    );



    //------------------------------------------------
    // RESTORE
    //------------------------------------------------

    glDepthMask(
        GL_TRUE
    );


    glEnable(
        GL_DEPTH_TEST
    );


    glEnable(
        GL_CULL_FACE
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