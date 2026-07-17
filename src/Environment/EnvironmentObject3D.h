#pragma once

#include <string>

#include <glm/glm.hpp>

#include "ChessPieceMesh3D.h"
#include "Transform3D.h"

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

    glm::vec3 getColor() const;

private:

    //------------------------------------------------
    // TODO
    // Reemplazar ChessPieceMesh3D por AssetMesh3D
    // cuando el cargador GLTF sea renombrado.
    //------------------------------------------------

    ChessPieceMesh3D mesh;

    Transform3D transform;

    glm::vec3 color =
    {
        1.0f,
        1.0f,
        1.0f
    };

};