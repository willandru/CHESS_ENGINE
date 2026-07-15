#include "BasicRoom3D.h"

BasicRoom3D::BasicRoom3D()
{
}

//====================================================
// INITIALIZATION
//====================================================

bool BasicRoom3D::initialize()
{

    //------------------------------------------------
    // FLOOR
    //------------------------------------------------

    floor.initialize(
        roomWidth,
        roomDepth,
        floorColor
    );

    floor.setRotation({
        -90.0f,
        0.0f,
        0.0f
    });

    floor.setPosition({
        0.0f,
        0.0f,
        0.0f
    });



    //------------------------------------------------
    // CEILING
    //------------------------------------------------

    ceiling.initialize(
        roomWidth,
        roomDepth,
        ceilingColor
    );

    ceiling.setRotation({
        90.0f,
        0.0f,
        0.0f
    });

    ceiling.setPosition({
        0.0f,
        roomHeight,
        0.0f
    });



    //------------------------------------------------
    // NORTH WALL (+Z)
    //------------------------------------------------

    northWall.initialize(
        roomWidth,
        roomHeight,
        wallColor
    );

    northWall.setRotation({
        0.0f,
        180.0f,
        0.0f
    });

    northWall.setPosition({
        0.0f,
        roomHeight * 0.5f,
        roomDepth * 0.5f
    });



    //------------------------------------------------
    // SOUTH WALL (-Z)
    //------------------------------------------------

    southWall.initialize(
        roomWidth,
        roomHeight,
        wallColor
    );

    southWall.setRotation({
        0.0f,
        0.0f,
        0.0f
    });

    southWall.setPosition({
        0.0f,
        roomHeight * 0.5f,
        -roomDepth * 0.5f
    });



    //------------------------------------------------
    // EAST WALL (+X)
    //------------------------------------------------

    eastWall.initialize(
        roomDepth,
        roomHeight,
        wallColor
    );

    eastWall.setRotation({
        0.0f,
        -90.0f,
        0.0f
    });

    eastWall.setPosition({
        roomWidth * 0.5f,
        roomHeight * 0.5f,
        0.0f
    });



    //------------------------------------------------
    // WEST WALL (-X)
    //------------------------------------------------

    westWall.initialize(
        roomDepth,
        roomHeight,
        wallColor
    );

    westWall.setRotation({
        0.0f,
        90.0f,
        0.0f
    });

    westWall.setPosition({
        -roomWidth * 0.5f,
        roomHeight * 0.5f,
        0.0f
    });

    return true;
}



//====================================================
// UPDATE
//====================================================

void BasicRoom3D::update(
    float
)
{
}



//====================================================
// BACKGROUND
//====================================================

void BasicRoom3D::renderBackground(
    Renderer3D& renderer,
    Shader3D& shader,
    Camera3D& camera,
    float aspectRatio
)
{
    floor.render(
        renderer,
        shader,
        camera,
        aspectRatio
    );

    ceiling.render(
        renderer,
        shader,
        camera,
        aspectRatio
    );

    northWall.render(
        renderer,
        shader,
        camera,
        aspectRatio
    );

    southWall.render(
        renderer,
        shader,
        camera,
        aspectRatio
    );

    eastWall.render(
        renderer,
        shader,
        camera,
        aspectRatio
    );

    westWall.render(
        renderer,
        shader,
        camera,
        aspectRatio
    );
}



//====================================================
// OBJECTS
//====================================================

void BasicRoom3D::renderObjects(
    Renderer3D&,
    Shader3D&,
    Camera3D&,
    float
)
{
}