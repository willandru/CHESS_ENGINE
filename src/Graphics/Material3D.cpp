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