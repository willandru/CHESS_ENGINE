#pragma once

#include <glm/glm.hpp>

class Camera3D
{
public:

    Camera3D();

    //------------------------------------------------
    // CAMERA MODE
    //------------------------------------------------

    enum class Mode
    {
        Overview,
        FirstPerson
    };

    void setMode(
        Mode mode
    );

    Mode getMode() const;

    void resetOverview();

    //------------------------------------------------
    // UPDATE
    //------------------------------------------------

    void update();

    //------------------------------------------------
    // POSITION
    //------------------------------------------------

    void setPosition(
        const glm::vec3& position
    );

    const glm::vec3& getPosition() const;

    //------------------------------------------------
    // TARGET
    //------------------------------------------------

    void setTarget(
        const glm::vec3& target
    );

    const glm::vec3& getTarget() const;

    //------------------------------------------------
    // UP
    //------------------------------------------------

    void setUp(
        const glm::vec3& up
    );

    const glm::vec3& getUp() const;

    //------------------------------------------------
    // LOOK AT
    //------------------------------------------------

    void lookAt(
        const glm::vec3& position,
        const glm::vec3& target
    );

    //------------------------------------------------
    // ORBIT CAMERA
    //------------------------------------------------

    void orbit(
        float deltaYaw,
        float deltaPitch
    );

    //------------------------------------------------
    // ZOOM
    //------------------------------------------------

    void zoom(
        float deltaDistance
    );

    //------------------------------------------------
    // DISTANCE
    //------------------------------------------------

    void setDistance(
        float value
    );

    float getDistance() const;

    //------------------------------------------------
    // ANGLES
    //------------------------------------------------

    void setYaw(
        float value
    );

    float getYaw() const;

    void setPitch(
        float value
    );

    float getPitch() const;

    //------------------------------------------------
    // PROJECTION
    //------------------------------------------------

    void setFieldOfView(
        float degrees
    );

    void setNearPlane(
        float value
    );

    void setFarPlane(
        float value
    );

    float getFieldOfView() const;

    float getNearPlane() const;

    float getFarPlane() const;

    //------------------------------------------------
    // MATRICES
    //------------------------------------------------

    glm::mat4 getViewMatrix() const;

    glm::mat4 getProjectionMatrix(
        float aspectRatio
    ) const;

private:

    //------------------------------------------------
    // INTERNAL
    //------------------------------------------------

    void updatePositionFromOrbit();

    //------------------------------------------------
    // CAMERA MODE
    //------------------------------------------------

    Mode mode = Mode::Overview;

    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    glm::vec3 position =
    {
        0.0f,
        0.0f,
        0.0f
    };

    glm::vec3 target =
    {
        0.0f,
        0.0f,
        0.0f
    };

    glm::vec3 up =
    {
        0.0f,
        1.0f,
        0.0f
    };

    //------------------------------------------------
    // ORBIT PARAMETERS
    //------------------------------------------------

    float distance = 7.5f;

    float yaw = -45.0f;

    float pitch = -35.0f;

    //------------------------------------------------
    // PROJECTION
    //------------------------------------------------

    float fieldOfView = 45.0f;

    float nearPlane = 0.1f;

    float farPlane = 100.0f;
};