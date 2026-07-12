#include "Camera3D.h"

#include <glm/gtc/matrix_transform.hpp>

Camera3D::Camera3D()
{
    resetOverview();

    fieldOfView = 45.0f;
    nearPlane   = 0.1f;
    farPlane    = 100.0f;
}

//====================================================
// MODE
//====================================================

void Camera3D::setMode(
    Mode value
)
{
    mode = value;
}

Camera3D::Mode Camera3D::getMode() const
{
    return mode;
}

//====================================================
// RESET OVERVIEW
//====================================================

void Camera3D::resetOverview()
{
    mode = Mode::Overview;

    position =
    {
        0.0f,
        8.0f,
        10.0f
    };

    target =
    {
        0.0f,
        0.0f,
        0.0f
    };

    up =
    {
        0.0f,
        1.0f,
        0.0f
    };
}

//====================================================
// POSITION
//====================================================

void Camera3D::setPosition(
    const glm::vec3& value
)
{
    position = value;
}

const glm::vec3&
Camera3D::getPosition() const
{
    return position;
}

//====================================================
// TARGET
//====================================================

void Camera3D::setTarget(
    const glm::vec3& value
)
{
    target = value;
}

const glm::vec3&
Camera3D::getTarget() const
{
    return target;
}

//====================================================
// UP
//====================================================

void Camera3D::setUp(
    const glm::vec3& value
)
{
    up = value;
}

const glm::vec3&
Camera3D::getUp() const
{
    return up;
}

//====================================================
// LOOK AT
//====================================================

void Camera3D::lookAt(
    const glm::vec3& newPosition,
    const glm::vec3& newTarget
)
{
    position = newPosition;
    target   = newTarget;
}

//====================================================
// PROJECTION
//====================================================

void Camera3D::setFieldOfView(
    float value
)
{
    fieldOfView = value;
}

void Camera3D::setNearPlane(
    float value
)
{
    nearPlane = value;
}

void Camera3D::setFarPlane(
    float value
)
{
    farPlane = value;
}

float Camera3D::getFieldOfView() const
{
    return fieldOfView;
}

float Camera3D::getNearPlane() const
{
    return nearPlane;
}

float Camera3D::getFarPlane() const
{
    return farPlane;
}

//====================================================
// MATRICES
//====================================================

glm::mat4 Camera3D::getViewMatrix() const
{
    return glm::lookAt(
        position,
        target,
        up
    );
}

glm::mat4 Camera3D::getProjectionMatrix(
    float aspectRatio
) const
{
    return glm::perspective(
        glm::radians(fieldOfView),
        aspectRatio,
        nearPlane,
        farPlane
    );
}