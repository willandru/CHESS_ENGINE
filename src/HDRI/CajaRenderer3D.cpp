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
    // SELECT FACE
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_1))
    {
        selectedFace =
            CajaMesh3D::Face::LEFT;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_2))
    {
        selectedFace =
            CajaMesh3D::Face::RIGHT;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_3))
    {
        selectedFace =
            CajaMesh3D::Face::FRONT;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_4))
    {
        selectedFace =
            CajaMesh3D::Face::BACK;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_5))
    {
        selectedFace =
            CajaMesh3D::Face::FLOOR;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_6))
    {
        selectedFace =
            CajaMesh3D::Face::CEILING;
    }



    //------------------------------------------------
    // HDRI ROTATION
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_R))
    {
        hdriRotation +=
            rotationSpeed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_F))
    {
        hdriRotation -=
            rotationSpeed * dt;
    }



    //------------------------------------------------
    // HDRI PROJECTION HEIGHT
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_T))
    {
        hdriHeight +=
            rotationSpeed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_G))
    {
        hdriHeight -=
            rotationSpeed * dt;
    }



    float amount =
        moveSpeed * dt;



    //------------------------------------------------
    // MOVE SELECTED FACE
    //------------------------------------------------

    switch(selectedFace)
    {


    case CajaMesh3D::Face::LEFT:

        if(InputKeyboard::isKeyDown(GLFW_KEY_A))
        {
            left -= amount;
            rebuild = true;
        }


        if(InputKeyboard::isKeyDown(GLFW_KEY_D))
        {
            left += amount;
            rebuild = true;
        }

        break;



    case CajaMesh3D::Face::RIGHT:

        if(InputKeyboard::isKeyDown(GLFW_KEY_A))
        {
            right -= amount;
            rebuild = true;
        }


        if(InputKeyboard::isKeyDown(GLFW_KEY_D))
        {
            right += amount;
            rebuild = true;
        }

        break;



    case CajaMesh3D::Face::FRONT:

        if(InputKeyboard::isKeyDown(GLFW_KEY_W))
        {
            front += amount;
            rebuild = true;
        }


        if(InputKeyboard::isKeyDown(GLFW_KEY_S))
        {
            front -= amount;
            rebuild = true;
        }

        break;



    case CajaMesh3D::Face::BACK:

        if(InputKeyboard::isKeyDown(GLFW_KEY_W))
        {
            back += amount;
            rebuild = true;
        }


        if(InputKeyboard::isKeyDown(GLFW_KEY_S))
        {
            back -= amount;
            rebuild = true;
        }

        break;



    case CajaMesh3D::Face::FLOOR:

        if(InputKeyboard::isKeyDown(GLFW_KEY_Q))
        {
            floor += amount;
            rebuild = true;
        }


        if(InputKeyboard::isKeyDown(GLFW_KEY_E))
        {
            floor -= amount;
            rebuild = true;
        }

        break;



    case CajaMesh3D::Face::CEILING:

        if(InputKeyboard::isKeyDown(GLFW_KEY_Q))
        {
            ceiling += amount;
            rebuild = true;
        }


        if(InputKeyboard::isKeyDown(GLFW_KEY_E))
        {
            ceiling -= amount;
            rebuild = true;
        }

        break;

    }



    //------------------------------------------------
    // APPLY
    //------------------------------------------------

    if(rebuild)
    {
        rebuildMesh();
    }

}


//====================================================
// RENDER BACKGROUND
//====================================================

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



    //------------------------------------------------
    // HDRI TEXTURE
    //------------------------------------------------

    hdriTexture.bind(
        0
    );


    hdriShader.setHDRITextureSlot(
        0
    );



    //------------------------------------------------
    // HDRI PARAMETERS
    //------------------------------------------------

    hdriShader.setExposure(
        exposure
    );


    hdriShader.setRotation(
        hdriRotation
    );


    hdriShader.setHeight(
        hdriHeight
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