#pragma once

#include "Environment3D.h"

#include "CupulaMesh3D.h"
#include "CupulaMeshBuilder.h"

#include "Mesh3D.h"
#include "Material3D.h"
#include "Transform3D.h"

#include "HDRITexture.h"
#include "HDRICupulaShader.h"

#include "Camera3D.h"

#include "CupulaConstants3D.h"

#include "Table3D.h"

class CupulaRenderer3D : public Environment3D
{

public:

    //------------------------------------------------
    // CONSTRUCTOR
    //------------------------------------------------

    CupulaRenderer3D();



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
    // PROFILE DATA
    //------------------------------------------------

    CupulaMesh3D cupulaData;



    //------------------------------------------------
    // GENERATED GPU MESH
    //------------------------------------------------

    Mesh3D cupulaMesh;



    //------------------------------------------------
    // MATERIAL / TRANSFORM
    //------------------------------------------------

    Material3D material;

    Transform3D transform;



    //------------------------------------------------
    // HDRI
    //------------------------------------------------

    HDRITexture hdriTexture;

    HDRICupulaShader cupulaShader;



    //------------------------------------------------
    // OBJECTS
    //------------------------------------------------

    Table3D table;



    //------------------------------------------------
    // HDRI CONTROLS
    //------------------------------------------------

    float hdriRotation =
        CupulaConstants3D::HDRI_ROTATION;

    float hdriHorizon =
        0.0f;

    float exposure =
        CupulaConstants3D::HDRI_EXPOSURE;



    //------------------------------------------------
    // HDRI CAPTURE
    //------------------------------------------------

    float captureHeight =
        CupulaConstants3D::HDRI_CAPTURE_HEIGHT;



    //------------------------------------------------
    // CUPULA SIZE CONTROL
    //------------------------------------------------

    float cupulaScale =
        1.0f;

};