#pragma once


#include "Environment3D.h"

#include "CajaMesh3D.h"
#include "CajaMeshBuilder.h"

#include "Material3D.h"
#include "Transform3D.h"

#include "HDRITexture.h"
#include "HDRICajaShader.h"

#include "Camera3D.h"



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
    // DRAW ONE FACE
    //------------------------------------------------

    void renderFace(
        Renderer3D& renderer,
        Camera3D& camera,
        float aspectRatio,
        CajaMesh3D::Face face
    );



private:


    //------------------------------------------------
    // BOX GEOMETRY
    //------------------------------------------------

    CajaMesh3D cajaData;



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


    HDRICajaShader cajaShader;



    //------------------------------------------------
    // EXPOSURE ONLY
    //------------------------------------------------
    // No rotation global.
    // No zoom global.

    float exposure = 1.0f;



    //------------------------------------------------
    // SELECTED FACE
    //------------------------------------------------

    CajaMesh3D::Face selectedFace =
        CajaMesh3D::Face::FRONT;



    //------------------------------------------------
    // PER FACE ROTATION
    //------------------------------------------------

    float faceRotationX[6] =
    {
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f
    };



    float faceRotationY[6] =
    {
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f
    };



    //------------------------------------------------
    // PER FACE ZOOM
    //------------------------------------------------

    float faceZoom[6] =
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };



    //------------------------------------------------
    // PER FACE OFFSET
    //------------------------------------------------

    float faceOffsetU[6] =
    {
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f
    };


    float faceOffsetV[6] =
    {
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f
    };


};