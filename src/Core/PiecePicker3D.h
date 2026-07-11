#pragma once

#include "Mesh3D.h"
#include "Transform3D.h"
#include "Camera3D.h"

#include <glm/glm.hpp>

class PiecePicker3D
{
public:

    //------------------------------------------------
    // PICK
    //------------------------------------------------

    static bool intersectMesh(
        float mouseX,
        float mouseY,
        int windowWidth,
        int windowHeight,
        const Camera3D& camera,
        const Mesh3D& mesh,
        const Transform3D& transform,
        float& distance
    );

private:

    //------------------------------------------------
    // RAY
    //------------------------------------------------

    static void buildRay(
        float mouseX,
        float mouseY,
        int windowWidth,
        int windowHeight,
        const Camera3D& camera,
        glm::vec3& rayOrigin,
        glm::vec3& rayDirection
    );

    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    static void transformRayToLocal(
        const glm::vec3& worldOrigin,
        const glm::vec3& worldDirection,
        const Transform3D& transform,
        glm::vec3& localOrigin,
        glm::vec3& localDirection
    );

    //------------------------------------------------
    // BOUNDING BOX
    //------------------------------------------------

    static bool intersectAABB(
        const glm::vec3& rayOrigin,
        const glm::vec3& rayDirection,
        const Mesh3D& mesh
    );

    //------------------------------------------------
    // TRIANGLES
    //------------------------------------------------

    static bool intersectTriangles(
        const glm::vec3& rayOrigin,
        const glm::vec3& rayDirection,
        const Mesh3D& mesh,
        float& distance
    );

    //------------------------------------------------
    // MÖLLER-TRUMBORE
    //------------------------------------------------

    static bool intersectTriangle(
        const glm::vec3& rayOrigin,
        const glm::vec3& rayDirection,
        const glm::vec3& v0,
        const glm::vec3& v1,
        const glm::vec3& v2,
        float& distance
    );
};
