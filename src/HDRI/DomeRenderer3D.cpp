#include "DomeRenderer3D.h"



//====================================================
// CONSTRUCTOR
//====================================================

DomeRenderer3D::DomeRenderer3D()
{
}



//====================================================
// INITIALIZATION
//====================================================

bool DomeRenderer3D::initialize()
{
    

    //------------------------------------------------
    // DOME
    //------------------------------------------------

    dome.initialize();



    //------------------------------------------------
    // GROUND
    //------------------------------------------------

    ground.initialize();



    return true;

}



//====================================================
// UPDATE
//====================================================

void DomeRenderer3D::update(
    float
)
{

}



//====================================================
// BACKGROUND
//====================================================

void DomeRenderer3D::renderBackground(
    Renderer3D& renderer,
    Shader3D& shader,
    Camera3D& camera,
    float aspectRatio
)
{

    //------------------------------------------------
    // DOME
    //------------------------------------------------

    renderer.renderObject(
        dome.getMesh(),
        dome.getTransform(),
        dome.getMaterial(),
        shader,
        camera,
        aspectRatio
    );



    //------------------------------------------------
    // GROUND
    //------------------------------------------------

    renderer.renderObject(
        ground.getMesh(),
        ground.getTransform(),
        ground.getMaterial(),
        shader,
        camera,
        aspectRatio
    );

}



//====================================================
// OBJECTS
//====================================================

void DomeRenderer3D::renderObjects(
    Renderer3D&,
    Shader3D&,
    Camera3D&,
    float
)
{

}