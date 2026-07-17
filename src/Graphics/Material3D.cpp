#include "Material3D.h"

//====================================================
// CONSTRUCTOR
//====================================================

Material3D::Material3D()
{
    color =
    {
        1.0f,
        1.0f,
        1.0f
    };
}



//====================================================
// COLOR
//====================================================

void Material3D::setColor(
    const glm::vec3& value
)
{
    color = value;
}



const glm::vec3& Material3D::getColor() const
{
    return color;
}



//====================================================
// TEXTURE
//====================================================

void Material3D::setTexture(
    Texture* value
)
{
    texture = value;
}



Texture* Material3D::getTexture() const
{
    return texture;
}



bool Material3D::hasTexture() const
{
    return texture != nullptr;
}