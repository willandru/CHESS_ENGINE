#pragma once

#include <string>

#include <glm/glm.hpp>

#include "ChessPieceMesh3D.h"
#include "Mesh3D.h"

#include "Transform3D.h"
#include "Material3D.h"
#include "Texture.h"
#include "LoadGLB.h"


class EnvironmentObject3D
{
public:

    EnvironmentObject3D();


    //------------------------------------------------
    // INITIALIZATION
    //------------------------------------------------

    virtual bool load() = 0;


protected:

    bool loadModel(
        const std::string& path
    );


    bool loadTexture(
        const std::string& path
    );


    bool loadGLB(
        const std::string& path
    );


public:


    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    void setPosition(
        const glm::vec3& position
    );


    void setRotation(
        const glm::vec3& rotation
    );


    void setScale(
        const glm::vec3& scale
    );



    //------------------------------------------------
    // APPEARANCE
    //------------------------------------------------

    void setColor(
        const glm::vec3& color
    );



    //------------------------------------------------
    // GETTERS
    //------------------------------------------------

    const Mesh3D& getMesh() const;


    const Transform3D& getTransform() const;


    const Material3D& getMaterial() const;



protected:


    //------------------------------------------------
    // OLD SYSTEM
    // Table3D / existing objects
    //------------------------------------------------

    ChessPieceMesh3D mesh;



    //------------------------------------------------
    // GLB SYSTEM
    // Chair3D / Blender assets
    //------------------------------------------------

    Mesh3D glbMesh;



    Transform3D transform;


    Texture texture;


    Material3D material;

};