#include "BoardPicker3D.h"

#include "Camera3D.h"
#include "SceneConstants.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>



//====================================================
// PICK SQUARE
//====================================================

bool BoardPicker3D::pickSquare(
    float mouseX,
    float mouseY,
    int windowWidth,
    int windowHeight,
    const Camera3D& camera,
    uint8_t& square
)
{
    //------------------------------------------------
    // SCREEN -> NDC
    //------------------------------------------------

    float x =
        (2.0f * mouseX) /
        static_cast<float>(windowWidth)
        - 1.0f;

    float y =
        1.0f -
        (2.0f * mouseY) /
        static_cast<float>(windowHeight);

    glm::vec4 rayClip(
        x,
        y,
        -1.0f,
        1.0f
    );



    //------------------------------------------------
    // CLIP -> EYE
    //------------------------------------------------

    float aspectRatio =
        static_cast<float>(windowWidth)
        /
        static_cast<float>(windowHeight);

    glm::mat4 projection =
        camera.getProjectionMatrix(
            aspectRatio
        );

    glm::vec4 rayEye =
        glm::inverse(projection)
        *
        rayClip;

    rayEye =
        glm::vec4(
            rayEye.x,
            rayEye.y,
            -1.0f,
            0.0f
        );



    //------------------------------------------------
    // EYE -> WORLD
    //------------------------------------------------

    glm::mat4 view =
        camera.getViewMatrix();

    glm::vec3 rayDirection =
        glm::normalize(
            glm::vec3(
                glm::inverse(view)
                *
                rayEye
            )
        );

    glm::vec3 rayOrigin =
        camera.getPosition();



    //------------------------------------------------
    // INTERSECTION
    //------------------------------------------------

    glm::vec3 hitPoint;

    if(
        !intersectBoard(
            rayOrigin,
            rayDirection,
            hitPoint
        )
    )
    {
        return false;
    }



    //------------------------------------------------
    // WORLD -> BOARD
    //------------------------------------------------

    int col =
        static_cast<int>(
            hitPoint.x +
            SceneConstants::HALF_BOARD_SIZE
        );


    int row =
        static_cast<int>(
            hitPoint.z +
            SceneConstants::HALF_BOARD_SIZE
        );

    if(col < 0 || col >= 8)
        return false;

    if(row < 0 || row >= 8)
        return false;



    square =
        static_cast<uint8_t>(
            row * 8 + col
        );

    return true;
}



//====================================================
// RAY / BOARD INTERSECTION
//====================================================

bool BoardPicker3D::intersectBoard(
    const glm::vec3& origin,
    const glm::vec3& direction,
    glm::vec3& hitPoint
)
{
    constexpr float BOARD_Y =
        SceneConstants::BOARD_HEIGHT +
        SceneConstants::BOARD_THICKNESS;


    if(glm::abs(direction.y) < 0.0001f)
        return false;


    float t =
        (BOARD_Y - origin.y)
        /
        direction.y;


    if(t < 0.0f)
        return false;


    hitPoint =
        origin
        +
        direction * t;


    return true;
}