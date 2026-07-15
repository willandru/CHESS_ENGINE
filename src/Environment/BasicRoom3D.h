#pragma once

#include "Environment3D.h"
#include "BasicWall3D.h"
#include "BasicRoomConstants.h"

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

    float roomWidth =
        BasicRoomConstants::ROOM_WIDTH;


    float roomHeight =
        BasicRoomConstants::ROOM_HEIGHT;


    float roomDepth =
        BasicRoomConstants::ROOM_DEPTH;



    glm::vec3 wallColor =
        BasicRoomConstants::WALL_COLOR;


    glm::vec3 floorColor =
        BasicRoomConstants::FLOOR_COLOR;


    glm::vec3 ceilingColor =
        BasicRoomConstants::CEILING_COLOR;

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