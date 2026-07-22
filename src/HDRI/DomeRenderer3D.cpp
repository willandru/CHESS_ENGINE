#include "DomeRenderer3D.h"


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


    //------------------------------------------------
    // DOME GEOMETRY
    //------------------------------------------------

    dome.initialize();



    //------------------------------------------------
    // GROUND
    //------------------------------------------------

    ground.initialize();



    //------------------------------------------------
    // HDRI TEXTURE
    //------------------------------------------------

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



    //------------------------------------------------
    // HDRI SHADER
    //------------------------------------------------

    if(
        !domeShader.initialize()
    )
    {

        std::cout
            << "[HDRI] ERROR loading dome shader"
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
    float
)
{

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
    // HDRI DOME
    //------------------------------------------------


    glDisable(
        GL_CULL_FACE
    );


    glDisable(
        GL_DEPTH_TEST
    );



    //------------------------------------------------
    // HDRI SHADER
    //------------------------------------------------

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



    domeShader.setRotation(
        0.0f
    );



    //------------------------------------------------
    // RENDER DOME
    //------------------------------------------------

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



    //------------------------------------------------
    // GROUND
    //------------------------------------------------

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