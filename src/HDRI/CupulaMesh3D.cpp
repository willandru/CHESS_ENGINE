#include "CupulaMesh3D.h"


#include "CupulaMeshBuilder.h"
#include "CupulaConstants3D.h"


#include <iostream>



//====================================================
// CONSTRUCTOR
//====================================================

CupulaMesh3D::CupulaMesh3D()
{

}



//====================================================
// INITIALIZATION
//====================================================

void CupulaMesh3D::initialize()
{

    color =
        CupulaConstants3D::CUPULA_COLOR;



    CupulaMeshBuilder::build(
        mesh,

        CupulaConstants3D::CUPULA_RADIUS,

        CupulaConstants3D::GROUND_RADIUS,

        CupulaConstants3D::CURVE_RADIUS,

        CupulaConstants3D::RADIAL_SEGMENTS,

        CupulaConstants3D::HEIGHT_SEGMENTS,

        color
    );



    material.setColor(
        color
    );



    transform.setPosition(
    {
        CupulaConstants3D::CENTER_X,
        CupulaConstants3D::CENTER_Y,
        CupulaConstants3D::CENTER_Z
    });



    transform.setRotation(
    {
        CupulaConstants3D::ROT_X,
        CupulaConstants3D::ROT_Y,
        CupulaConstants3D::ROT_Z
    });



    transform.setScale(
    {
        1.0f,
        1.0f,
        1.0f
    });



    std::cout
        << "[CUPULA] Initialized "
        << "Radius="
        << CupulaConstants3D::CUPULA_RADIUS
        << std::endl;

}



//====================================================
// TEXTURE
//====================================================

bool CupulaMesh3D::loadTexture(
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

void CupulaMesh3D::setPosition(
    const glm::vec3& position
)
{

    transform.setPosition(
        position
    );

}



void CupulaMesh3D::setRotation(
    const glm::vec3& rotation
)
{

    transform.setRotation(
        rotation
    );

}



void CupulaMesh3D::setScale(
    const glm::vec3& scale
)
{

    transform.setScale(
        scale
    );

}



const Transform3D&
CupulaMesh3D::getTransform() const
{

    return transform;

}



//====================================================
// APPEARANCE
//====================================================

void CupulaMesh3D::setColor(
    const glm::vec3& color
)
{

    this->color = color;


    material.setColor(
        color
    );

}



const glm::vec3&
CupulaMesh3D::getColor() const
{

    return color;

}



//====================================================
// ACCESS
//====================================================

const Mesh3D&
CupulaMesh3D::getMesh() const
{

    return mesh;

}



const Material3D&
CupulaMesh3D::getMaterial() const
{

    return material;

}



//====================================================
// RENDER
//====================================================

void CupulaMesh3D::render(
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