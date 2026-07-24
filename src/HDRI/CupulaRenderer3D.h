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
    // HDRI CONTROLS
    //------------------------------------------------


    // Rotación horizontal HDRI

    float hdriRotation =
        CupulaConstants3D::HDRI_ROTATION;



    // Movimiento vertical HDRI

    float hdriHorizon =
        0.0f;



    // Exposición HDR

    float exposure =
        CupulaConstants3D::HDRI_EXPOSURE;



    //------------------------------------------------
    // HDRI CAPTURE
    //------------------------------------------------


    // Altura cámara virtual HDRI

    float captureHeight =
        CupulaConstants3D::HDRI_CAPTURE_HEIGHT;



    //------------------------------------------------
    // CUPULA SIZE CONTROL
    //------------------------------------------------
    //
    // Este controla el radio efectivo visible.
    //
    // X aumenta
    // Z disminuye
    //

    float cupulaScale =
        1.0f;


};