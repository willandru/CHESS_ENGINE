#pragma once

#include <cstdint>

#include <glm/glm.hpp>

class Camera3D;

class BoardPicker3D
{
public:

    //------------------------------------------------
    // PICK
    //------------------------------------------------

    static bool pickSquare(
        float mouseX,
        float mouseY,
        int windowWidth,
        int windowHeight,
        const Camera3D& camera,
        uint8_t& square
    );

private:

    //------------------------------------------------
    // HELPERS
    //------------------------------------------------

    static bool intersectBoard(
        const glm::vec3& origin,
        const glm::vec3& direction,
        glm::vec3& hitPoint
    );
};