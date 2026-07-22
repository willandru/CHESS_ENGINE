#include "DomeRenderer3D.h"


#include "InputKeyboard.h"


#include <iostream>


#include <glad/glad.h>



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
            "Assets/Environment/smelting_tower_interior_4k.exr"
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

        std::cout
            << "[HDRI] ERROR loading shader"
            << std::endl;


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

    std::cout
        << "Scale="
        << hdriScale
        << " Horizon="
        << hdriHorizon
        << " Rotation="
        << hdriRotation
        << std::endl;



    float speed = 0.5f;



    //------------------------------------------------
    // SCALE
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_Y
        )
    )
    {

        hdriScale -= speed * dt;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_H
        )
    )
    {

        hdriScale += speed * dt;

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

        hdriHorizon += speed * dt;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_G
        )
    )
    {

        hdriHorizon -= speed * dt;

    }



    //------------------------------------------------
    // ROTATION
    //------------------------------------------------

        if(InputKeyboard::isKeyDown(GLFW_KEY_R))
        {
            hdriRotation += 1.0f * dt;
        }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_F
        )
    )
    {

        hdriRotation -= speed * dt;

    }



    //------------------------------------------------
    // LIMITS
    //------------------------------------------------

    hdriScale =
        glm::clamp(
            hdriScale,
            0.1f,
            5.0f
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



    domeShader.setExposure(
        1.0f
    );



   std::cout
    << "SEND TO SHADER ROTATION = "
    << hdriRotation
    << std::endl;


domeShader.setRotation(
    hdriRotation
);



    domeShader.setScale(
        hdriScale
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



    glEnable(
        GL_DEPTH_TEST
    );



    renderer.renderObject(
        ground.getMesh(),
        ground.getTransform(),
        ground.getMaterial(),
        shader,
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