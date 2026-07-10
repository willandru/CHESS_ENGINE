#include "Transform3D.h"

#include <glm/gtc/matrix_transform.hpp>



Transform3D::Transform3D()
{
    position = glm::vec3(
        0.0f,
        0.0f,
        0.0f
    );

    rotation = glm::vec3(
        0.0f,
        0.0f,
        0.0f
    );

    scale = glm::vec3(
        1.0f,
        1.0f,
        1.0f
    );
}



void Transform3D::setPosition(const glm::vec3& value)
{
    position = value;
}

const glm::vec3& Transform3D::getPosition() const
{
    return position;
}

void Transform3D::translate(const glm::vec3& offset)
{
    position += offset;
}



void Transform3D::setRotation(const glm::vec3& value)
{
    rotation = value;
}

const glm::vec3& Transform3D::getRotation() const
{
    return rotation;
}

void Transform3D::rotate(const glm::vec3& deltaRotation)
{
    rotation += deltaRotation;
}



void Transform3D::setScale(const glm::vec3& value)
{
    scale = value;
}

const glm::vec3& Transform3D::getScale() const
{
    return scale;
}



glm::mat4 Transform3D::getModelMatrix() const
{
    glm::mat4 model(1.0f);

    //------------------------------------------------
    // TRANSLATION
    //------------------------------------------------

    model = glm::translate(
        model,
        position
    );

    //------------------------------------------------
    // ROTATION X
    //------------------------------------------------

    model = glm::rotate(
        model,
        glm::radians(rotation.x),
        glm::vec3(
            1.0f,
            0.0f,
            0.0f
        )
    );

    //------------------------------------------------
    // ROTATION Y
    //------------------------------------------------

    model = glm::rotate(
        model,
        glm::radians(rotation.y),
        glm::vec3(
            0.0f,
            1.0f,
            0.0f
        )
    );

    //------------------------------------------------
    // ROTATION Z
    //------------------------------------------------

    model = glm::rotate(
        model,
        glm::radians(rotation.z),
        glm::vec3(
            0.0f,
            0.0f,
            1.0f
        )
    );

    //------------------------------------------------
    // SCALE
    //------------------------------------------------

    model = glm::scale(
        model,
        scale
    );

    return model;
}