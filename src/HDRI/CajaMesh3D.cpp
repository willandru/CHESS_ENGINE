#include "CajaMesh3D.h"

#include <stdexcept>



//====================================================
// CONSTRUCTOR
//====================================================

CajaMesh3D::CajaMesh3D()
{

}



//====================================================
// INITIALIZATION
//====================================================

void CajaMesh3D::initialize()
{

    // Mesh3D no requiere inicialización explícita.
    // Cada cara será cargada por CajaMeshBuilder.

}



//====================================================
// GET FACE
//====================================================

Mesh3D& CajaMesh3D::getFace(
    Face face
)
{

    switch(face)
    {

        case Face::FLOOR:
            return floor;


        case Face::CEILING:
            return ceiling;


        case Face::FRONT:
            return front;


        case Face::BACK:
            return back;


        case Face::LEFT:
            return left;


        case Face::RIGHT:
            return right;

    }

    throw std::runtime_error(
        "CajaMesh3D::getFace() invalid face."
    );

}



//====================================================
// GET FACE CONST
//====================================================

const Mesh3D& CajaMesh3D::getFace(
    Face face
) const
{

    switch(face)
    {

        case Face::FLOOR:
            return floor;


        case Face::CEILING:
            return ceiling;


        case Face::FRONT:
            return front;


        case Face::BACK:
            return back;


        case Face::LEFT:
            return left;


        case Face::RIGHT:
            return right;

    }

    throw std::runtime_error(
        "CajaMesh3D::getFace() invalid face."
    );

}