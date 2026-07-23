#pragma once


#include "Environment3D.h"


#include "CupulaMesh3D.h"

#include "HDRITexture.h"
#include "HDRICupulaShader.h"

#include "Camera3D.h"



class CupulaRenderer3D : public Environment3D
{

public:


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

    CupulaMesh3D cupula;



    //------------------------------------------------
    // HDRI
    //------------------------------------------------

    HDRITexture hdriTexture;


    HDRICupulaShader cupulaShader;



    //------------------------------------------------
    // CONTROLS
    //------------------------------------------------

    float hdriScaleX = 1.0f;


    float hdriScaleY = 1.0f;


    float hdriRotation = 0.0f;


    float hdriHorizon = 0.0f;


    float exposure = 1.0f;


};