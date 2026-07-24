#include "CajaMesh3D.h"



//====================================================
// CONSTRUCTOR
//====================================================

CajaMesh3D::CajaMesh3D()
{

}



//====================================================
// INITIALIZE
//====================================================

void CajaMesh3D::initialize()
{

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


    return front;

}



//====================================================
// GET MESH
//====================================================

Mesh3D& CajaMesh3D::getMesh(
    Face face
)
{

    return getFace(
        face
    );

}