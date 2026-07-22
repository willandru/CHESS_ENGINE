#pragma once

#include "Environment3D.h"

#include "DomeMesh3D.h"
#include "GroundDiskMesh3D.h"

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

    DomeMesh3D dome;

    GroundDiskMesh3D ground;

};