#include "BasicWall3D.h"

#include "PlaneMeshBuilder.h"


BasicWall3D::BasicWall3D()
{

}



//====================================================
// INITIALIZATION
//====================================================

void BasicWall3D::initialize(
    float wallWidth,
    float wallHeight,
    const glm::vec3& wallColor
)
{

    width  = wallWidth;

    height = wallHeight;


    color = wallColor;



    PlaneMeshBuilder::build(
        mesh,
        width,
        height,
        color
    );


    material.setColor(
        color
    );

}



//====================================================
// TEXTURE
//====================================================

bool BasicWall3D::loadTexture(
    const std::string& path
)
{

    if(
        !texture.loadFromFile(path)
    )
    {
        return false;
    }



    material.setTexture(
        &texture
    );


    return true;
}



//====================================================
// DIMENSIONS
//====================================================

float BasicWall3D::getWidth() const
{
    return width;
}



float BasicWall3D::getHeight() const
{
    return height;
}



//====================================================
// TRANSFORM
//====================================================

void BasicWall3D::setPosition(
    const glm::vec3& position
)
{
    transform.setPosition(
        position
    );
}



void BasicWall3D::setRotation(
    const glm::vec3& rotation
)
{
    transform.setRotation(
        rotation
    );
}



void BasicWall3D::setScale(
    const glm::vec3& scale
)
{
    transform.setScale(
        scale
    );
}



const Transform3D&
BasicWall3D::getTransform() const
{
    return transform;
}



//====================================================
// APPEARANCE
//====================================================

void BasicWall3D::setColor(
    const glm::vec3& wallColor
)
{

    color = wallColor;


    material.setColor(
        color
    );

}



const glm::vec3&
BasicWall3D::getColor() const
{
    return color;
}



//====================================================
// RENDER
//====================================================

void BasicWall3D::render(
    const Renderer3D& renderer,
    const Shader3D& shader,
    const Camera3D& camera,
    float aspectRatio
) const
{

    renderer.renderObject(
        mesh,
        transform,
        material,
        shader,
        camera,
        aspectRatio
    );

}