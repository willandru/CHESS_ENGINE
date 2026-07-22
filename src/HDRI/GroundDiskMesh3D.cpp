#include "GroundDiskMesh3D.h"

#include "DomeMeshBuilder.h"
#include "DomeConstants3D.h"
#include <iostream>

GroundDiskMesh3D::GroundDiskMesh3D()
{
}



//====================================================
// INITIALIZATION
//====================================================

void GroundDiskMesh3D::initialize()
{

    color =
        DomeConstants3D::GROUND_COLOR;


    DomeMeshBuilder::buildGroundDisk(
        mesh,
        DomeConstants3D::GROUND_RADIUS,
        DomeConstants3D::LONGITUDE_SEGMENTS,
        color
    );


    material.setColor(
        color
    );


    transform.setPosition(
        {
            DomeConstants3D::GROUND_POS_X,
            DomeConstants3D::GROUND_POS_Y,
            DomeConstants3D::GROUND_POS_Z
        }
    );


    transform.setRotation(
        {
            DomeConstants3D::GROUND_ROT_X,
            DomeConstants3D::GROUND_ROT_Y,
            DomeConstants3D::GROUND_ROT_Z
        }
    );


    transform.setScale(
        {
            1.0f,
            1.0f,
            1.0f
        }
    );

    std::cout << "[GROUND] R=" << DomeConstants3D::GROUND_RADIUS
    << " PosY=" << DomeConstants3D::GROUND_POS_Y << std::endl;

}



//====================================================
// TRANSFORM
//====================================================

void GroundDiskMesh3D::setPosition(
    const glm::vec3& position
)
{

    transform.setPosition(
        position
    );

}



void GroundDiskMesh3D::setRotation(
    const glm::vec3& rotation
)
{

    transform.setRotation(
        rotation
    );

}



void GroundDiskMesh3D::setScale(
    const glm::vec3& scale
)
{

    transform.setScale(
        scale
    );

}



//====================================================
// GETTERS
//====================================================

const Mesh3D&
GroundDiskMesh3D::getMesh() const
{

    return mesh;

}



const Transform3D&
GroundDiskMesh3D::getTransform() const
{

    return transform;

}



const Material3D&
GroundDiskMesh3D::getMaterial() const
{

    return material;

}