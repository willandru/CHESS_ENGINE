#pragma once

#include "Environment3D.h"

#include "DomeMesh3D.h"
#include "GroundDiskMesh3D.h"

#include "HDRITexture.h"

#include "HDRIDomeShader.h"
#include "HDRIGroundShader.h"
#include "Camera3D.h"

class DomeRenderer3D : public Environment3D
{

public:

    DomeRenderer3D();



    //------------------------------------------------
    // LIFECYCLE
    //------------------------------------------------

    bool initialize() override;


    void update(
        Camera3D& camera,
        float dt
    ) override;



    //------------------------------------------------
    // BACKGROUND
    //------------------------------------------------

    void renderBackground(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio
    ) override;



    //------------------------------------------------
    // OBJECTS
    //------------------------------------------------

    void renderObjects(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio
    ) override;



private:


    //------------------------------------------------
    // GEOMETRY
    //------------------------------------------------

    DomeMesh3D dome;


    GroundDiskMesh3D ground;



    //------------------------------------------------
    // HDRI SYSTEM
    //------------------------------------------------

    HDRITexture hdriTexture;


    HDRIDomeShader domeShader;


    HDRIGroundShader groundShader;



    //------------------------------------------------
    // HDRI CONTROLS
    //------------------------------------------------

    float hdriScaleX = 1.0f;


    float hdriScaleY = 0.8f;


    float hdriZoom = 1.0f;


    float hdriHorizon = 0.0f;


    float hdriRotation = 0.0f;



    //------------------------------------------------
    // HDRI CAPTURE HEIGHT
    //------------------------------------------------
    //
    // Altura aproximada desde la cual se tomó
    // la fotografía HDRI.
    //
    // Se ajustará manualmente con:
    //
    //      O = subir
    //      L = bajar
    //
    //------------------------------------------------

    float captureHeight = 1.60f;

};