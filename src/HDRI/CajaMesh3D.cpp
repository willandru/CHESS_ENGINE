#include "CajaMesh3D.h"



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

}



//====================================================
// GET MESH
//====================================================

Mesh3D& CajaMesh3D::getMesh()
{

    return mesh;

}



//====================================================
// GET MESH CONST
//====================================================

const Mesh3D& CajaMesh3D::getMesh() const
{

    return mesh;

}