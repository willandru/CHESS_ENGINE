#include "EnvironmentObject3D.h"

EnvironmentObject3D::EnvironmentObject3D()
{
}



//====================================================
// INITIALIZATION
//====================================================

bool EnvironmentObject3D::loadModel(
    const std::string& path
)
{
    return mesh.load(
        path
    );
}



//====================================================
// TRANSFORM
//====================================================

void EnvironmentObject3D::setPosition(
    const glm::vec3& position
)
{
    transform.setPosition(
        position
    );
}



void EnvironmentObject3D::setRotation(
    const glm::vec3& rotation
)
{
    transform.setRotation(
        rotation
    );
}



void EnvironmentObject3D::setScale(
    const glm::vec3& scale
)
{
    transform.setScale(
        scale
    );
}



//====================================================
// APPEARANCE
//====================================================

void EnvironmentObject3D::setColor(
    const glm::vec3& value
)
{
    color = value;
}



//====================================================
// GETTERS
//====================================================

const Mesh3D& EnvironmentObject3D::getMesh() const
{
    return mesh.getMesh();
}



const Transform3D& EnvironmentObject3D::getTransform() const
{
    return transform;
}



glm::vec3 EnvironmentObject3D::getColor() const
{
    return color;
}