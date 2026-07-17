#pragma once

#include "Environment3D.h"

#include "BasicWall3D.h"
#include "BasicRoomConstants.h"

#include "Table3D.h"

class BasicRoom3D : public Environment3D
{
public:

    BasicRoom3D();

    //------------------------------------------------
    // LIFECYCLE
    //------------------------------------------------

    bool initialize() override;

    void update(
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
    // ROOM
    //------------------------------------------------

    BasicWall3D northWall;

    BasicWall3D southWall;

    BasicWall3D eastWall;

    BasicWall3D westWall;

    BasicWall3D floor;

    BasicWall3D ceiling;

    //------------------------------------------------
    // OBJECTS
    //------------------------------------------------

    Table3D table;

};