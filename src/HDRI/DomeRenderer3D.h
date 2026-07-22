#pragma once


#include "Environment3D.h"


#include "DomeMesh3D.h"
#include "GroundDiskMesh3D.h"


#include "HDRITexture.h"
#include "HDRIDomeShader.h"



class DomeRenderer3D : public Environment3D
{


public:


    DomeRenderer3D();



    //------------------------------------------------
    // LIFECYCLE
    //------------------------------------------------

    bool initialize() override;



    void update(
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


    // Cúpula que contiene el ambiente HDR

    DomeMesh3D dome;



    // Superficie física del suelo

    GroundDiskMesh3D ground;



    //------------------------------------------------
    // HDRI SYSTEM
    //------------------------------------------------


    // Textura EXR HDR

    HDRITexture hdriTexture;



    // Shader especializado del cielo

    HDRIDomeShader domeShader;



};