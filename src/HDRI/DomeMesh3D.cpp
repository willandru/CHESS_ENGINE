#include "DomeMesh3D.h"

#include "DomeMeshBuilder.h"
#include "DomeConstants3D.h"


DomeMesh3D::DomeMesh3D()
{

}


//====================================================
// INITIALIZATION
//====================================================

void DomeMesh3D::initialize()
{

    color =
        DomeConstants3D::DOME_COLOR;

    DomeMeshBuilder::build(
        mesh,
        DomeConstants3D::DOME_RADIUS,
        DomeConstants3D::LATITUDE_SEGMENTS,
        DomeConstants3D::LONGITUDE_SEGMENTS,
        color
    );

    material.setColor(
        color
    );

    transform.setPosition(
        {
            DomeConstants3D::DOME_POS_X,
            DomeConstants3D::DOME_POS_Y,
            DomeConstants3D::DOME_POS_Z
        }
    );

    transform.setRotation(
        {
            DomeConstants3D::DOME_ROT_X,
            DomeConstants3D::DOME_ROT_Y,
            DomeConstants3D::DOME_ROT_Z
        }
    );

    transform.setScale(
        {
            1.0f,
            1.0f,
            1.0f
        }
    );

}



//====================================================
// TEXTURE
//====================================================

bool DomeMesh3D::loadTexture(
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
// TRANSFORM
//====================================================

void DomeMesh3D::setPosition(
    const glm::vec3& position
)
{

    transform.setPosition(
        position
    );

}



void DomeMesh3D::setRotation(
    const glm::vec3& rotation
)
{

    transform.setRotation(
        rotation
    );

}



void DomeMesh3D::setScale(
    const glm::vec3& scale
)
{

    transform.setScale(
        scale
    );

}



const Transform3D&
DomeMesh3D::getTransform() const
{

    return transform;

}



//====================================================
// APPEARANCE
//====================================================

void DomeMesh3D::setColor(
    const glm::vec3& color
)
{

    this->color = color;


    material.setColor(
        color
    );

}



const glm::vec3&
DomeMesh3D::getColor() const
{

    return color;

}



//====================================================
// ACCESS
//====================================================

const Mesh3D&
DomeMesh3D::getMesh() const
{

    return mesh;

}



const Material3D&
DomeMesh3D::getMaterial() const
{

    return material;

}



//====================================================
// RENDER
//====================================================

void DomeMesh3D::render(
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