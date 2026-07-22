#pragma once

#include "Renderer3D.h"
#include "Shader3D.h"
#include "Camera3D.h"

class Environment3D
{
public:

    virtual ~Environment3D() = default;

    //------------------------------------------------
    // LIFECYCLE
    //------------------------------------------------

    virtual bool initialize() = 0;

    virtual void update(
        Camera3D& camera,
        float dt
    ) = 0;

    //------------------------------------------------
    // BACKGROUND
    //------------------------------------------------

    virtual void renderBackground(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio
    ) = 0;

    //------------------------------------------------
    // OBJECTS
    //------------------------------------------------

    virtual void renderObjects(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio
    ) = 0;

};