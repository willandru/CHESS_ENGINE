#pragma once

#include "Mesh3D.h"
#include "Transform3D.h"

#include "Material3D.h"
#include "Texture.h"

#include "Renderer3D.h"
#include "Shader3D.h"
#include "Camera3D.h"

#include <glm/glm.hpp>

#include <string>


class GroundDiskMesh3D
{

public:

    GroundDiskMesh3D();



    //------------------------------------------------
    // INITIALIZATION
    //------------------------------------------------

    void initialize();


    bool loadTexture(
        const std::string& path
    );



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
    // ACCESS
    //------------------------------------------------

    const Mesh3D& getMesh() const;

    const Material3D& getMaterial() const;



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
    // TRANSFORM
    //------------------------------------------------

    Transform3D transform;



    //------------------------------------------------
    // MATERIAL
    //------------------------------------------------

    Material3D material;

    Texture texture;



    //------------------------------------------------
    // APPEARANCE
    //------------------------------------------------

    glm::vec3 color =
    {
        0.35f,
        0.35f,
        0.35f
    };

};