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
        BasicRoomConstants::ROOM_WIDTH,
        BasicRoomConstants::ROOM_DEPTH,
        BasicRoomConstants::FLOOR_COLOR
    );


    floor.loadTexture(
        "Assets/Environment/floor_texture.png"
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
        BasicRoomConstants::ROOM_WIDTH,
        BasicRoomConstants::ROOM_DEPTH,
        BasicRoomConstants::CEILING_COLOR
    );


    ceiling.loadTexture(
        "Assets/Environment/ceiling_texture.png"
    );


    ceiling.setRotation({
        90.0f,
        0.0f,
        0.0f
    });


    ceiling.setPosition({
        0.0f,
        BasicRoomConstants::ROOM_HEIGHT,
        0.0f
    });




    //------------------------------------------------
    // NORTH WALL (+Z)
    //------------------------------------------------

    northWall.initialize(
        BasicRoomConstants::ROOM_WIDTH,
        BasicRoomConstants::ROOM_HEIGHT,
        BasicRoomConstants::WALL_COLOR
    );


    northWall.loadTexture(
        "Assets/Environment/leather_texture.png"
    );


    northWall.setRotation({
        0.0f,
        180.0f,
        0.0f
    });


    northWall.setPosition({
        0.0f,
        BasicRoomConstants::ROOM_HEIGHT * 0.5f,
        BasicRoomConstants::ROOM_DEPTH * 0.5f
    });




    //------------------------------------------------
    // SOUTH WALL (-Z)
    //------------------------------------------------

    southWall.initialize(
        BasicRoomConstants::ROOM_WIDTH,
        BasicRoomConstants::ROOM_HEIGHT,
        BasicRoomConstants::WALL_COLOR
    );


    southWall.loadTexture(
        "Assets/Environment/leather_texture.png"
    );


    southWall.setRotation({
        0.0f,
        0.0f,
        0.0f
    });


    southWall.setPosition({
        0.0f,
        BasicRoomConstants::ROOM_HEIGHT * 0.5f,
        -BasicRoomConstants::ROOM_DEPTH * 0.5f
    });




    //------------------------------------------------
    // EAST WALL (+X)
    //------------------------------------------------

    eastWall.initialize(
        BasicRoomConstants::ROOM_DEPTH,
        BasicRoomConstants::ROOM_HEIGHT,
        BasicRoomConstants::WALL_COLOR
    );


    eastWall.loadTexture(
        "Assets/Environment/wall_texture.png"
    );


    eastWall.setRotation({
        0.0f,
        -90.0f,
        0.0f
    });


    eastWall.setPosition({
        BasicRoomConstants::ROOM_WIDTH * 0.5f,
        BasicRoomConstants::ROOM_HEIGHT * 0.5f,
        0.0f
    });




    //------------------------------------------------
    // WEST WALL (-X)
    //------------------------------------------------

    westWall.initialize(
        BasicRoomConstants::ROOM_DEPTH,
        BasicRoomConstants::ROOM_HEIGHT,
        BasicRoomConstants::WALL_COLOR
    );


    westWall.loadTexture(
        "Assets/Environment/wall_texture.png"
    );


    westWall.setRotation({
        0.0f,
        90.0f,
        0.0f
    });


    westWall.setPosition({
        -BasicRoomConstants::ROOM_WIDTH * 0.5f,
        BasicRoomConstants::ROOM_HEIGHT * 0.5f,
        0.0f
    });




    //------------------------------------------------
    // TABLE
    //------------------------------------------------

    if(
        !table.load()
    )
    {
        return false;
    }



    table.setPosition({
        0.0f,
        0.0f,
        0.0f
    });




    //------------------------------------------------
    // CHAIR
    //------------------------------------------------

    if(
        !chair.load()
    )
    {
        return false;
    }



    chair.setPosition({
        4.0f,
        0.0f,
        3.0f
    });



    return true;
}




//====================================================
// UPDATE
//====================================================

void BasicRoom3D::update(
    Camera3D&,
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
    Renderer3D& renderer,
    Shader3D& shader,
    Camera3D& camera,
    float aspectRatio
)
{


    //------------------------------------------------
    // TABLE
    //------------------------------------------------

    renderer.renderObject(
        table.getMesh(),
        table.getTransform(),
        table.getMaterial(),
        shader,
        camera,
        aspectRatio
    );



    //------------------------------------------------
    // CHAIR
    //------------------------------------------------

    renderer.renderObject(
        chair.getMesh(),
        chair.getTransform(),
        chair.getMaterial(),
        shader,
        camera,
        aspectRatio
    );

}