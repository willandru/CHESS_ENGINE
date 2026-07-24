#pragma once


#include "Environment3D.h"

#include "CajaMesh3D.h"
#include "CajaMeshBuilder.h"

#include "Mesh3D.h"
#include "Material3D.h"
#include "Transform3D.h"

#include "HDRITexture.h"
#include "HDRICajaShader.h"

#include "Camera3D.h"


#include <array>



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
    // RENDER INDIVIDUAL FACE
    //------------------------------------------------

    void renderFace(
        Renderer3D& renderer,
        Camera3D& camera,
        float aspectRatio,
        CajaMesh3D::Face face
    );



    //------------------------------------------------
    // BOX DATA
    //------------------------------------------------

    CajaMesh3D cajaData;



    //------------------------------------------------
    // MATERIAL / TRANSFORM
    //------------------------------------------------

    Material3D material;

    Transform3D transform;



    //------------------------------------------------
    // HDRI
    //------------------------------------------------

    HDRITexture hdriTexture;


    HDRICajaShader cajaShader;



    //------------------------------------------------
    // HDRI SETTINGS
    //------------------------------------------------

    float hdriRotation = 0.0f;


    float exposure = 1.0f;



    //------------------------------------------------
    // SELECTED FACE
    //------------------------------------------------

    CajaMesh3D::Face selectedFace =
        CajaMesh3D::Face::FLOOR;



    //------------------------------------------------
    // PER FACE CONTROLS
    //------------------------------------------------

    std::array<float,6> faceRotation =
    {
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f
    };


    std::array<float,6> faceZoom =
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };


};