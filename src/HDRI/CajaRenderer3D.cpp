// CajaRenderer3D.cpp
// PARTE 1

#include "CajaRenderer3D.h"

#include "CajaConstants3D.h"

#include "InputKeyboard.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>



//====================================================
// CONSTRUCTOR
//====================================================

CajaRenderer3D::CajaRenderer3D()
{

}



//====================================================
// INITIALIZE
//====================================================

bool CajaRenderer3D::initialize()
{

    //------------------------------------------------
    // MESH
    //------------------------------------------------

    caja.initialize();



    rebuildMesh();



    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    transform.setPosition(
        CajaConstants3D::CENTER
    );



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



    //------------------------------------------------
    // MATERIAL
    //------------------------------------------------

    material.setColor(
        CajaConstants3D::COLOR
    );



    //------------------------------------------------
    // HDRI
    //------------------------------------------------

    exposure =
        CajaConstants3D::HDRI_EXPOSURE;



    hdriRotation =
        CajaConstants3D::HDRI_ROTATION;



    if(
        !hdriTexture.loadFromFile(
            "Assets/Environment/pine_attic_8k.exr"
        )
    )
    {

        std::cout
            << "[CajaRenderer3D] HDRI load failed."
            << std::endl;


        return false;

    }



    //------------------------------------------------
    // SHADER
    //------------------------------------------------

    if(
        !hdriShader.initialize()
    )
    {

        return false;

    }



    return true;

}


//====================================================
// REBUILD MESH
//====================================================

void CajaRenderer3D::rebuildMesh()
{

    CajaMeshBuilder::build(

        caja,

        left,
        right,

        front,
        back,

        floor,
        ceiling,

        CajaConstants3D::COLOR

    );

}

//====================================================
// UPDATE
//====================================================

void CajaRenderer3D::update(
    Camera3D&,
    float dt
)
{

    constexpr float moveSpeed =
        2.0f;


    constexpr float rotationSpeed =
        1.5f;



    bool rebuild =
        false;



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
    // MOVE ROOM FACES
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_A
        )
    )
    {

        left -=
            moveSpeed * dt;


        rebuild = true;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_D
        )
    )
    {

        right +=
            moveSpeed * dt;


        rebuild = true;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_W
        )
    )
    {

        front +=
            moveSpeed * dt;


        rebuild = true;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_S
        )
    )
    {

        back -=
            moveSpeed * dt;


        rebuild = true;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_Q
        )
    )
    {

        ceiling +=
            moveSpeed * dt;


        rebuild = true;

    }



    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_E
        )
    )
    {

        floor -=
            moveSpeed * dt;


        rebuild = true;

    }



    //------------------------------------------------
    // APPLY CHANGES
    //------------------------------------------------

    if(rebuild)
    {

        rebuildMesh();

    }

}


//====================================================
// RENDER BACKGROUND
//====================================================

void CajaRenderer3D::renderBackground(
    Renderer3D& renderer,
    Shader3D&,
    Camera3D& camera,
    float aspectRatio
)
{

    //------------------------------------------------
    // STATE
    //------------------------------------------------

    glDisable(
        GL_CULL_FACE
    );


    glDisable(
        GL_BLEND
    );



    //------------------------------------------------
    // SHADER
    //------------------------------------------------

    hdriShader.bind();



    hdriTexture.bind(
        0
    );



    hdriShader.setHDRITextureSlot(
        0
    );


    hdriShader.setExposure(
        exposure
    );


    hdriShader.setRotation(
        hdriRotation
    );



    //------------------------------------------------
    // DRAW
    //------------------------------------------------

    renderer.renderObject(

        caja.getMesh(),

        transform,

        material,

        hdriShader,

        camera,

        aspectRatio

    );



    //------------------------------------------------
    // RESTORE
    //------------------------------------------------

    glEnable(
        GL_CULL_FACE
    );

}


//====================================================
// RENDER OBJECTS
//====================================================

void CajaRenderer3D::renderObjects(
    Renderer3D&,
    Shader3D&,
    Camera3D&,
    float
)
{

    // La Caja3D únicamente representa
    // el entorno HDRI.
    //
    // Los objetos de la escena se renderizan
    // desde sus propios renderers.

}