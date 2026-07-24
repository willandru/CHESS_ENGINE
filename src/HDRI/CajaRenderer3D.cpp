#include "CajaRenderer3D.h"

#include "CajaConstants3D.h"

#include "InputKeyboard.h"

#include <iostream>

#include <glad/glad.h>

#include <glm/common.hpp>

#include <GLFW/glfw3.h>





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
    // CREATE GEOMETRY
    //------------------------------------------------

    cajaData.initialize();



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
            "Assets/Environment/pine_attic_8k.exr"
        )
    )
    {

        std::cout
            << "[HDRI] ERROR"
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



    std::cout
        << "[CAJA] initialized"
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


    constexpr float speed = 1.5f;


    constexpr float zoomSpeed = 0.5f;



    //------------------------------------------------
    // SELECT FACE
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
    // ROTATION X
    // T/G
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_T))
    {
        faceRotationX[face] += speed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_G))
    {
        faceRotationX[face] -= speed * dt;
    }




    //------------------------------------------------
    // ROTATION Y
    // R/F
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_R))
    {
        faceRotationY[face] += speed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_F))
    {
        faceRotationY[face] -= speed * dt;
    }





    //------------------------------------------------
    // OFFSET U
    // Y/H
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_Y))
    {
        faceOffsetU[face] += dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_H))
    {
        faceOffsetU[face] -= dt;
    }





    //------------------------------------------------
    // OFFSET V
    // U/J
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_U))
    {
        faceOffsetV[face] += dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_J))
    {
        faceOffsetV[face] -= dt;
    }





    //------------------------------------------------
    // ZOOM
    // O/L
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_O))
    {
        faceZoom[face] += zoomSpeed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_L))
    {
        faceZoom[face] -= zoomSpeed * dt;
    }



    faceZoom[face] =
        glm::clamp(
            faceZoom[face],
            0.1f,
            10.0f
        );

}








//====================================================
// RENDER ONE FACE
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
    // SEND FACE DATA
    //------------------------------------------------

    cajaShader.setFace(
        index
    );


    cajaShader.setFaceRotationX(
        faceRotationX[index]
    );


    cajaShader.setFaceRotationY(
        faceRotationY[index]
    );


    cajaShader.setFaceZoom(
        faceZoom[index]
    );


    cajaShader.setFaceOffsetU(
        faceOffsetU[index]
    );


    cajaShader.setFaceOffsetV(
        faceOffsetV[index]
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

    glDisable(GL_CULL_FACE);

    glDepthMask(GL_FALSE);

    glDisable(GL_DEPTH_TEST);



    cajaShader.bind();



    hdriTexture.bind(0);


    cajaShader.setHDRITextureSlot(0);


    cajaShader.setExposure(
        exposure
    );



    renderFace(renderer,camera,aspectRatio,CajaMesh3D::Face::FLOOR);

    renderFace(renderer,camera,aspectRatio,CajaMesh3D::Face::CEILING);

    renderFace(renderer,camera,aspectRatio,CajaMesh3D::Face::FRONT);

    renderFace(renderer,camera,aspectRatio,CajaMesh3D::Face::BACK);

    renderFace(renderer,camera,aspectRatio,CajaMesh3D::Face::LEFT);

    renderFace(renderer,camera,aspectRatio,CajaMesh3D::Face::RIGHT);



    glDepthMask(GL_TRUE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

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