#pragma once

#include "Mesh3D.h"

#include <string>


class ChessPieceMesh3D
{

public:

    ChessPieceMesh3D();


    //------------------------------------------------
    // LOAD MODEL
    //------------------------------------------------

    bool load(
        const std::string& path
    );


    //------------------------------------------------
    // MESH
    //------------------------------------------------

    void setMesh(
        const Mesh3D& value
    );
    const Mesh3D& getMesh() const;


private:

    Mesh3D mesh;


    bool loadGLTF(
        const std::string& path
    );

};