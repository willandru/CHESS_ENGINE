#pragma once

#include "Mesh3D.h"
#include "Transform3D.h"
#include "Renderer3D.h"
#include "Shader3D.h"
#include "Camera3D.h"

#include <glm/glm.hpp>

class BasicWall3D
{
public:

    BasicWall3D();

    //------------------------------------------------
    // INITIALIZATION
    //------------------------------------------------

    void initialize(
        float width,
        float height,
        const glm::vec3& color
    );

    //------------------------------------------------
    // DIMENSIONS
    //------------------------------------------------

    float getWidth() const;

    float getHeight() const;

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

    const Transform3D& getTransform() const;

    //------------------------------------------------
    // APPEARANCE
    //------------------------------------------------

    void setColor(
        const glm::vec3& color
    );

    const glm::vec3& getColor() const;

    //------------------------------------------------
    // RENDER
    //------------------------------------------------

    void render(
        const Renderer3D& renderer,
        const Shader3D& shader,
        const Camera3D& camera,
        float aspectRatio
    ) const;

private:

    //------------------------------------------------
    // GEOMETRY
    //------------------------------------------------

    Mesh3D mesh;

    //------------------------------------------------
    // DIMENSIONS
    //------------------------------------------------

    float width  = 1.0f;

    float height = 1.0f;

    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    Transform3D transform;

    //------------------------------------------------
    // APPEARANCE
    //------------------------------------------------

    glm::vec3 color =
    {
        0.8f,
        0.8f,
        0.8f
    };
};