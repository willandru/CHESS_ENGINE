#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

class Material3D
{
public:

    Material3D();

    //------------------------------------------------
    // COLOR
    //------------------------------------------------

    void setColor(
        const glm::vec3& value
    );

    const glm::vec3& getColor() const;

    //------------------------------------------------
    // TEXTURE
    //------------------------------------------------

    void setTexture(
        Texture* texture
    );

    Texture* getTexture() const;

    bool hasTexture() const;

private:

    glm::vec3 color;

    Texture* texture = nullptr;

};