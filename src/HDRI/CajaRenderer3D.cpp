#include "CajaRenderer3D.h"

#include "CajaConstants3D.h"

#include "InputKeyboard.h"

#include <iostream>

#include <glad/glad.h>

#include <glm/common.hpp>



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
    // CREATE BOX
    //------------------------------------------------

    cajaData.initialize();



    //------------------------------------------------
    // BUILD BOX FACES
    //------------------------------------------------

    CajaMeshBuilder::build(
        cajaData,

        {
            CajaConstants3D::WIDTH,
            CajaConstants3D::HEIGHT,
            CajaConstants3D::DEPTH
        },

        CajaConstants3D::CAJA_COLOR
    );



    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    transform.setPosition(
    {
        CajaConstants3D::CENTER_X,
        CajaConstants3D::CENTER_Y,
        CajaConstants3D::CENTER_Z
    });



    transform.setRotation(
    {
        CajaConstants3D::ROT_X,
        CajaConstants3D::ROT_Y,
        CajaConstants3D::ROT_Z
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
        CajaConstants3D::CAJA_COLOR
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
        !cajaShader.initialize()
    )
    {

        return false;

    }



    //------------------------------------------------
    // DEFAULT VALUES
    //------------------------------------------------

    for(int i = 0; i < 6; i++)
    {
        faceRotation[i] = 0.0f;
        faceZoom[i] = 1.0f;
    }



    std::cout
        << "[CAJA] Environment initialized"
        << std::endl;



    return true;

}





//====================================================
// UPDATE
//====================================================

void CajaRenderer3D::update(
    Camera3D&,
    float dt
)
{

    constexpr float rotationSpeed = 1.5f;

    constexpr float zoomSpeed = 0.5f;



    //------------------------------------------------
    // FACE SELECTION
    //------------------------------------------------

    if(InputKeyboard::isKeyPressed(GLFW_KEY_1))
        selectedFace = CajaMesh3D::Face::FLOOR;


    if(InputKeyboard::isKeyPressed(GLFW_KEY_2))
        selectedFace = CajaMesh3D::Face::CEILING;


    if(InputKeyboard::isKeyPressed(GLFW_KEY_3))
        selectedFace = CajaMesh3D::Face::FRONT;


    if(InputKeyboard::isKeyPressed(GLFW_KEY_4))
        selectedFace = CajaMesh3D::Face::BACK;


    if(InputKeyboard::isKeyPressed(GLFW_KEY_5))
        selectedFace = CajaMesh3D::Face::LEFT;


    if(InputKeyboard::isKeyPressed(GLFW_KEY_6))
        selectedFace = CajaMesh3D::Face::RIGHT;



    int face =
        static_cast<int>(
            selectedFace
        );



    //------------------------------------------------
    // ROTATE TEXTURE
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_R
        )
    )
    {

        faceRotation[face] +=
            rotationSpeed *
            dt;

    }



    //------------------------------------------------
    // ZOOM TEXTURE
    //------------------------------------------------

    if(
        InputKeyboard::isKeyDown(
            GLFW_KEY_T
        )
    )
    {

        faceZoom[face] +=
            zoomSpeed *
            dt;

    }



    //------------------------------------------------
    // LIMIT
    //------------------------------------------------

    faceZoom[face] =
        glm::clamp(
            faceZoom[face],
            0.25f,
            5.0f
        );

}





//====================================================
// RENDER SINGLE FACE
//====================================================

void CajaRenderer3D::renderFace(
    Renderer3D& renderer,
    Camera3D& camera,
    float aspectRatio,
    CajaMesh3D::Face face
)
{

    int index =
        static_cast<int>(
            face
        );



    //------------------------------------------------
    // FACE SETTINGS
    //------------------------------------------------

    cajaShader.setFace(
        index
    );


    cajaShader.setTextureRotation(
        faceRotation[index]
    );


    cajaShader.setTextureZoom(
        faceZoom[index]
    );



    //------------------------------------------------
    // DRAW
    //------------------------------------------------

    renderer.renderObject(
        cajaData.getFace(face),
        transform,
        material,
        cajaShader,
        camera,
        aspectRatio
    );

}






//====================================================
// BACKGROUND
//====================================================

void CajaRenderer3D::renderBackground(
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

    cajaShader.bind();



    //------------------------------------------------
    // HDRI
    //------------------------------------------------

    hdriTexture.bind(
        0
    );


    cajaShader.setHDRITextureSlot(
        0
    );


    cajaShader.setExposure(
        exposure
    );


    cajaShader.setRotation(
        hdriRotation
    );



    //------------------------------------------------
    // DRAW EACH FACE
    //------------------------------------------------

    renderFace(
        renderer,
        camera,
        aspectRatio,
        CajaMesh3D::Face::FLOOR
    );


    renderFace(
        renderer,
        camera,
        aspectRatio,
        CajaMesh3D::Face::CEILING
    );


    renderFace(
        renderer,
        camera,
        aspectRatio,
        CajaMesh3D::Face::FRONT
    );


    renderFace(
        renderer,
        camera,
        aspectRatio,
        CajaMesh3D::Face::BACK
    );


    renderFace(
        renderer,
        camera,
        aspectRatio,
        CajaMesh3D::Face::LEFT
    );


    renderFace(
        renderer,
        camera,
        aspectRatio,
        CajaMesh3D::Face::RIGHT
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

void CajaRenderer3D::renderObjects(
    Renderer3D&,
    Shader3D&,
    Camera3D&,
    float
)
{

}