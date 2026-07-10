#include "Camera3D.h"

#include <glm/gtc/matrix_transform.hpp>



Camera3D::Camera3D()
{
    //------------------------------------------------
    // CAMERA
    //------------------------------------------------

    position = glm::vec3(
        0.0f,
        8.0f,
        10.0f
    );

    target = glm::vec3(
        0.0f,
        0.0f,
        0.0f
    );

    up = glm::vec3(
        0.0f,
        1.0f,
        0.0f
    );

    //------------------------------------------------
    // PROJECTION
    //------------------------------------------------

    fieldOfView = 45.0f;

    nearPlane = 0.1f;

    farPlane = 100.0f;
}



void Camera3D::setPosition(const glm::vec3& value)
{
    position = value;
}

const glm::vec3& Camera3D::getPosition() const
{
    return position;
}



void Camera3D::setTarget(const glm::vec3& value)
{
    target = value;
}

const glm::vec3& Camera3D::getTarget() const
{
    return target;
}



void Camera3D::setUp(const glm::vec3& value)
{
    up = value;
}

const glm::vec3& Camera3D::getUp() const
{
    return up;
}



void Camera3D::setFieldOfView(float value)
{
    fieldOfView = value;
}

void Camera3D::setNearPlane(float value)
{
    nearPlane = value;
}

void Camera3D::setFarPlane(float value)
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



glm::mat4 Camera3D::getViewMatrix() const
{
    return glm::lookAt(
        position,
        target,
        up
    );
}



glm::mat4 Camera3D::getProjectionMatrix(float aspectRatio) const
{
    return glm::perspective(
        glm::radians(fieldOfView),
        aspectRatio,
        nearPlane,
        farPlane
    );
}