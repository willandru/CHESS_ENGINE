#include "Material3D.h"


Material3D::Material3D()
{
    //------------------------------------------------
    // DEFAULT MATERIAL
    //------------------------------------------------

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