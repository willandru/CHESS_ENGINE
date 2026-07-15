#include "Camera3D.h"

#include "InputMouse.h"
#include "SceneConstants.h"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <cmath>


//====================================================
// CONSTRUCTOR
//====================================================

Camera3D::Camera3D()
{
    fieldOfView =
        SceneConstants::CAMERA_FIELD_OF_VIEW;


    nearPlane =
        SceneConstants::CAMERA_NEAR_PLANE;


    farPlane =
        SceneConstants::CAMERA_FAR_PLANE;


    resetOverview();
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
        SceneConstants::CAMERA_OVERVIEW_POSITION_X,
        SceneConstants::CAMERA_OVERVIEW_POSITION_Y,
        SceneConstants::CAMERA_OVERVIEW_POSITION_Z
    };


    target =
    {
        SceneConstants::CAMERA_TARGET_X,
        SceneConstants::CAMERA_TARGET_Y,
        SceneConstants::CAMERA_TARGET_Z
    };


    up =
    {
        0.0f,
        1.0f,
        0.0f
    };


    glm::vec3 offset =
        position - target;


    distance =
        glm::length(
            offset
        );


    yaw =
        glm::degrees(
            std::atan2(
                offset.x,
                offset.z
            )
        );


    pitch =
        glm::degrees(
            std::asin(
                offset.y / distance
            )
        );
}



//====================================================
// UPDATE
//====================================================

void Camera3D::update()
{
    if(
        InputMouse::isButtonDown(
            GLFW_MOUSE_BUTTON_MIDDLE
        )
    )
    {
        orbit(
            InputMouse::getDeltaX()
            *
            SceneConstants::CAMERA_ORBIT_SENSITIVITY,

            -InputMouse::getDeltaY()
            *
            SceneConstants::CAMERA_ORBIT_SENSITIVITY
        );
    }



    float scroll =
        InputMouse::getScrollDelta();



    if(scroll != 0.0f)
    {
        zoom(
            -scroll
            *
            SceneConstants::CAMERA_ZOOM_SPEED
        );
    }



    distance =
        std::clamp(
            distance,
            SceneConstants::CAMERA_MIN_DISTANCE,
            SceneConstants::CAMERA_MAX_DISTANCE
        );


    pitch =
        std::clamp(
            pitch,
            SceneConstants::CAMERA_MIN_PITCH,
            SceneConstants::CAMERA_MAX_PITCH
        );


    updatePositionFromOrbit();
}



//====================================================
// UPDATE POSITION FROM ORBIT
//====================================================

void Camera3D::updatePositionFromOrbit()
{
    const float yawRadians =
        glm::radians(
            yaw
        );


    const float pitchRadians =
        glm::radians(
            pitch
        );



    position.x =
        target.x +
        distance *
        std::cos(
            pitchRadians
        ) *
        std::sin(
            yawRadians
        );


    position.y =
        target.y +
        distance *
        std::sin(
            pitchRadians
        );


    position.z =
        target.z +
        distance *
        std::cos(
            pitchRadians
        ) *
        std::cos(
            yawRadians
        );
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

    target = newTarget;


    glm::vec3 offset =
        position - target;


    distance =
        glm::length(
            offset
        );


    if(distance > 0.0001f)
    {

        yaw =
            glm::degrees(
                std::atan2(
                    offset.x,
                    offset.z
                )
            );


        pitch =
            glm::degrees(
                std::asin(
                    offset.y / distance
                )
            );

    }
}



//====================================================
// ORBIT
//====================================================

void Camera3D::orbit(
    float deltaYaw,
    float deltaPitch
)
{
    yaw += deltaYaw;

    pitch += deltaPitch;
}



//====================================================
// ZOOM
//====================================================

void Camera3D::zoom(
    float deltaDistance
)
{
    distance += deltaDistance;
}



//====================================================
// POSITION
//====================================================

void Camera3D::setPosition(
    const glm::vec3& value
)
{
    lookAt(
        value,
        target
    );
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
    lookAt(
        position,
        value
    );
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
// DISTANCE
//====================================================

void Camera3D::setDistance(
    float value
)
{
    distance =
        std::clamp(
            value,
            SceneConstants::CAMERA_MIN_DISTANCE,
            SceneConstants::CAMERA_MAX_DISTANCE
        );


    updatePositionFromOrbit();
}


float Camera3D::getDistance() const
{
    return distance;
}



//====================================================
// YAW
//====================================================

void Camera3D::setYaw(
    float value
)
{
    yaw = value;

    updatePositionFromOrbit();
}


float Camera3D::getYaw() const
{
    return yaw;
}



//====================================================
// PITCH
//====================================================

void Camera3D::setPitch(
    float value
)
{
    pitch =
        std::clamp(
            value,
            SceneConstants::CAMERA_MIN_PITCH,
            SceneConstants::CAMERA_MAX_PITCH
        );


    updatePositionFromOrbit();
}


float Camera3D::getPitch() const
{
    return pitch;
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