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

    //------------------------------------------------
    // CREATE PROFILE
    //------------------------------------------------

    cupulaData.initialize(
        CupulaConstants3D::RADIUS
    );



    //------------------------------------------------
    // BUILD MESH
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
        cupulaScale,
        cupulaScale,
        cupulaScale
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
            "Assets/Environment/outdoor/alps_field_8k.exr"
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


    constexpr float horizonSpeed =
        0.5f;


    constexpr float captureHeightSpeed =
        1.0f;


    constexpr float scaleSpeed =
        0.5f;



    //------------------------------------------------
    // HDRI ROTATION
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
    // CUPULA RADIUS / SIZE
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_X
        )
    )
    {

        cupulaScale +=
            scaleSpeed * dt;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_Z
        )
    )
    {

        cupulaScale -=
            scaleSpeed * dt;

    }



    //------------------------------------------------
    // LIMITS
    //------------------------------------------------

    captureHeight =
        glm::clamp(
            captureHeight,
            0.10f,
            10.0f
        );



    hdriHorizon =
        glm::clamp(
            hdriHorizon,
            -1.0f,
            1.0f
        );



    cupulaScale =
        glm::clamp(
            cupulaScale,
            0.1f,
            10.0f
        );



    //------------------------------------------------
    // APPLY SCALE
    //------------------------------------------------

    transform.setScale(
    {
        cupulaScale,
        cupulaScale,
        cupulaScale
    });

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
    // SHADER
    //------------------------------------------------

    cupulaShader.bind();



    //------------------------------------------------
    // TEXTURE
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


    cupulaShader.setHorizon(
        hdriHorizon
    );


    cupulaShader.setCaptureHeight(
        captureHeight
    );


    //------------------------------------------------
    // UNICO RADIO
    //------------------------------------------------

    cupulaShader.setRadius(
        CupulaConstants3D::RADIUS *
        cupulaScale
    );



    //------------------------------------------------
    // DRAW
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