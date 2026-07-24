#pragma once

#include "Environment3D.h"

#include "CajaMesh3D.h"
#include "CajaMeshBuilder.h"

#include "Transform3D.h"
#include "Material3D.h"

#include "HDRITexture.h"
#include "HDRICajaShader.h"

#include "Camera3D.h"
#include "Renderer3D.h"

#include <glm/glm.hpp>



//====================================================
// CAJA RENDERER 3D
//====================================================

class CajaRenderer3D : public Environment3D
{

public:

    //------------------------------------------------
    // CONSTRUCTOR
    //------------------------------------------------

    CajaRenderer3D();



    //------------------------------------------------
    // LIFECYCLE
    //------------------------------------------------

    bool initialize() override;



    void update(
        Camera3D& camera,
        float dt
    ) override;



    //------------------------------------------------
    // RENDER
    //------------------------------------------------

    void renderBackground(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio
    ) override;



    void renderObjects(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio
    ) override;



private:


    //------------------------------------------------
    // INTERNAL
    //------------------------------------------------

    void renderFace(
        Renderer3D& renderer,
        Camera3D& camera,
        float aspectRatio,
        CajaMesh3D::Face face
    );



    void rebuildBox();



private:


    //------------------------------------------------
    // MESH
    //------------------------------------------------

    CajaMesh3D caja;



    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    Transform3D transform;



    //------------------------------------------------
    // MATERIAL
    //------------------------------------------------

    Material3D material;



    //------------------------------------------------
    // HDRI
    //------------------------------------------------

    HDRITexture hdriTexture;

    HDRICajaShader shader;



    float exposure = 1.0f;



    //------------------------------------------------
    // ROOM SIZE
    //------------------------------------------------

    float roomWidth  = 10.0f;

    float roomHeight = 5.0f;

    float roomDepth  = 10.0f;



    bool sizeChanged = false;



    //------------------------------------------------
    // HDRI FACE SETTINGS
    //------------------------------------------------

    struct FaceSettings
    {

        glm::vec2 offset =
        {
            0.0f,
            0.0f
        };


        glm::vec2 scale =
        {
            1.0f,
            1.0f
        };


        float rotation =
            0.0f;

    };



    FaceSettings faceSettings[6];



    CajaMesh3D::Face selectedFace =
        CajaMesh3D::Face::FRONT;

};