#pragma once

#include "Environment3D.h"
#include "BasicWall3D.h"

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
    // ROOM DIMENSIONS
    //------------------------------------------------

    float roomWidth  = 12.0f;

    float roomHeight = 5.0f;

    float roomDepth  = 12.0f;

    //------------------------------------------------
    // COLORS
    //------------------------------------------------

    glm::vec3 wallColor =
    {
        0.88f,
        0.87f,
        0.82f
    };

    glm::vec3 floorColor =
    {
        0.55f,
        0.40f,
        0.28f
    };

    glm::vec3 ceilingColor =
    {
        0.95f,
        0.95f,
        0.95f
    };

    //------------------------------------------------
    // PANELS
    //------------------------------------------------

    BasicWall3D northWall;

    BasicWall3D southWall;

    BasicWall3D eastWall;

    BasicWall3D westWall;

    BasicWall3D floor;

    BasicWall3D ceiling;

};