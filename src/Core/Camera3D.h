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

    Mode mode;

    glm::vec3 position;

    glm::vec3 target;

    glm::vec3 up;

    float fieldOfView;

    float nearPlane;

    float farPlane;
};