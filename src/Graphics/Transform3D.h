#pragma once

#include <glm/glm.hpp>


class Transform3D
{
public:

    Transform3D();

    //------------------------------------------------
    // POSITION
    //------------------------------------------------

    void setPosition(const glm::vec3& position);

    const glm::vec3& getPosition() const;

    void translate(const glm::vec3& offset);

    //------------------------------------------------
    // ROTATION
    //------------------------------------------------

    void setRotation(const glm::vec3& rotation);

    const glm::vec3& getRotation() const;

    void rotate(const glm::vec3& deltaRotation);

    //------------------------------------------------
    // SCALE
    //------------------------------------------------

    void setScale(const glm::vec3& scale);

    const glm::vec3& getScale() const;

    //------------------------------------------------
    // MODEL MATRIX
    //------------------------------------------------

    glm::mat4 getModelMatrix() const;

private:

    glm::vec3 position;

    glm::vec3 rotation;

    glm::vec3 scale;
};