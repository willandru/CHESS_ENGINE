#include "CajaRenderer3D.h"

#include "CajaConstants3D.h"
#include "InputKeyboard.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/common.hpp>

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
    // GEOMETRY
    //------------------------------------------------

    caja.initialize();


    rebuildBox();



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
            << "[CajaRenderer3D] HDRI load failed."
            << std::endl;

        return false;

    }



    //------------------------------------------------
    // SHADER
    //------------------------------------------------

    if(
        !shader.initialize()
    )
    {

        return false;

    }



    //------------------------------------------------
    // FACE SETTINGS
    //------------------------------------------------

    for(
        int i = 0;
        i < 6;
        i++
    )
    {

        faceSettings[i].offset =
        {
            0.0f,
            0.0f
        };


        faceSettings[i].scale =
        {
            1.0f,
            1.0f
        };


        faceSettings[i].rotation =
            0.0f;

    }



    std::cout
        << "[CajaRenderer3D] Initialized."
        << std::endl;



    return true;

}



//====================================================
// REBUILD BOX
//====================================================

void CajaRenderer3D::rebuildBox()
{

    CajaMeshBuilder::build(
        caja,
        glm::vec3(
            roomWidth,
            roomHeight,
            roomDepth
        ),
        CajaConstants3D::CAJA_COLOR
    );

}



//====================================================
// UPDATE
//====================================================

//====================================================
// UPDATE
//====================================================

void CajaRenderer3D::update(
    Camera3D&,
    float dt
)
{

    constexpr float moveSpeed =
        1.0f;

    constexpr float scaleSpeed =
        0.5f;

    constexpr float rotationSpeed =
        1.5f;

    constexpr float resizeSpeed =
        2.0f;



    //------------------------------------------------
    // SELECT FACE
    //------------------------------------------------

    if(InputKeyboard::isKeyPressed(GLFW_KEY_1))
    {
        selectedFace =
            CajaMesh3D::Face::FLOOR;
    }


    if(InputKeyboard::isKeyPressed(GLFW_KEY_2))
    {
        selectedFace =
            CajaMesh3D::Face::CEILING;
    }


    if(InputKeyboard::isKeyPressed(GLFW_KEY_3))
    {
        selectedFace =
            CajaMesh3D::Face::FRONT;
    }


    if(InputKeyboard::isKeyPressed(GLFW_KEY_4))
    {
        selectedFace =
            CajaMesh3D::Face::BACK;
    }


    if(InputKeyboard::isKeyPressed(GLFW_KEY_5))
    {
        selectedFace =
            CajaMesh3D::Face::LEFT;
    }


    if(InputKeyboard::isKeyPressed(GLFW_KEY_6))
    {
        selectedFace =
            CajaMesh3D::Face::RIGHT;
    }



    //------------------------------------------------
    // ROOM SIZE CONTROL
    //------------------------------------------------

    bool rebuild =
        false;



    if(
        InputKeyboard::isKeyDown(GLFW_KEY_LEFT_SHIFT)
    )
    {

        //------------------------------------------------
        // WIDTH
        //------------------------------------------------

        if(
            InputKeyboard::isKeyDown(GLFW_KEY_R)
        )
        {
            roomWidth +=
                resizeSpeed * dt;

            rebuild = true;
        }


        if(
            InputKeyboard::isKeyDown(GLFW_KEY_F)
        )
        {
            roomWidth -=
                resizeSpeed * dt;

            rebuild = true;
        }



        //------------------------------------------------
        // HEIGHT
        //------------------------------------------------

        if(
            InputKeyboard::isKeyDown(GLFW_KEY_T)
        )
        {
            roomHeight +=
                resizeSpeed * dt;

            rebuild = true;
        }


        if(
            InputKeyboard::isKeyDown(GLFW_KEY_G)
        )
        {
            roomHeight -=
                resizeSpeed * dt;

            rebuild = true;
        }



        //------------------------------------------------
        // DEPTH
        //------------------------------------------------

        if(
            InputKeyboard::isKeyDown(GLFW_KEY_Y)
        )
        {
            roomDepth +=
                resizeSpeed * dt;

            rebuild = true;
        }


        if(
            InputKeyboard::isKeyDown(GLFW_KEY_H)
        )
        {
            roomDepth -=
                resizeSpeed * dt;

            rebuild = true;
        }

    }



    roomWidth =
        glm::max(
            roomWidth,
            2.0f
        );


    roomHeight =
        glm::max(
            roomHeight,
            2.0f
        );


    roomDepth =
        glm::max(
            roomDepth,
            2.0f
        );



    if(rebuild)
    {

        CajaMeshBuilder::build(
            caja,
            glm::vec3(
                roomWidth,
                roomHeight,
                roomDepth
            ),
            CajaConstants3D::CAJA_COLOR
        );

    }



    //------------------------------------------------
    // SELECT FACE SETTINGS
    //------------------------------------------------

    int index =
        static_cast<int>(
            selectedFace
        );



    FaceSettings& face =
        faceSettings[index];



    //------------------------------------------------
    // OFFSET U/V
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_A))
    {
        face.offset.x -=
            moveSpeed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_D))
    {
        face.offset.x +=
            moveSpeed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_W))
    {
        face.offset.y +=
            moveSpeed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_S))
    {
        face.offset.y -=
            moveSpeed * dt;
    }



    //------------------------------------------------
    // SCALE HDRI
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_Q))
    {
        face.scale.x +=
            scaleSpeed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_E))
    {
        face.scale.x -=
            scaleSpeed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_Z))
    {
        face.scale.y +=
            scaleSpeed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_X))
    {
        face.scale.y -=
            scaleSpeed * dt;
    }



    //------------------------------------------------
    // ROTATION HDRI
    //------------------------------------------------

    if(InputKeyboard::isKeyDown(GLFW_KEY_R))
    {
        face.rotation +=
            rotationSpeed * dt;
    }


    if(InputKeyboard::isKeyDown(GLFW_KEY_F))
    {
        face.rotation -=
            rotationSpeed * dt;
    }



    //------------------------------------------------
    // LIMITS
    //------------------------------------------------

    face.scale.x =
        glm::clamp(
            face.scale.x,
            0.1f,
            10.0f
        );


    face.scale.y =
        glm::clamp(
            face.scale.y,
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



    FaceSettings& settings =
        faceSettings[index];



    //------------------------------------------------
    // HDRI UV SETTINGS
    //------------------------------------------------

    shader.setOffset(
        settings.offset
    );


    shader.setScale(
        settings.scale
    );


    shader.setRotation(
        settings.rotation
    );



    //------------------------------------------------
    // DRAW
    //------------------------------------------------

    renderer.renderObject(
        caja.getFace(face),
        transform,
        material,
        shader,
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

    //------------------------------------------------
    // STATE
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
    // HDRI
    //------------------------------------------------

    shader.bind();



    hdriTexture.bind(
        0
    );


    shader.setHDRITextureSlot(
        0
    );


    shader.setExposure(
        exposure
    );



    //------------------------------------------------
    // SIX FACES
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