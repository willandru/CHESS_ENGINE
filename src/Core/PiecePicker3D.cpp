#include "PiecePicker3D.h"

#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <limits>

namespace
{
    constexpr float EPSILON = 1e-6f;
}

//====================================================
// INTERSECT MESH
//====================================================

bool PiecePicker3D::intersectMesh(
    float mouseX,
    float mouseY,
    int windowWidth,
    int windowHeight,
    const Camera3D& camera,
    const Mesh3D& mesh,
    const Transform3D& transform,
    float& distance
)
{
    glm::vec3 rayOrigin;
    glm::vec3 rayDirection;

    buildRay(
        mouseX,
        mouseY,
        windowWidth,
        windowHeight,
        camera,
        rayOrigin,
        rayDirection
    );

    glm::vec3 localOrigin;
    glm::vec3 localDirection;

    transformRayToLocal(
        rayOrigin,
        rayDirection,
        transform,
        localOrigin,
        localDirection
    );

    if(
        !intersectAABB(
            localOrigin,
            localDirection,
            mesh
        )
    )
    {
        return false;
    }

    return intersectTriangles(
        localOrigin,
        localDirection,
        mesh,
        distance
    );
}

//====================================================
// BUILD RAY
//====================================================

void PiecePicker3D::buildRay(
    float mouseX,
    float mouseY,
    int windowWidth,
    int windowHeight,
    const Camera3D& camera,
    glm::vec3& rayOrigin,
    glm::vec3& rayDirection
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
    // PROJECTION
    //------------------------------------------------

    float aspect =
        static_cast<float>(windowWidth)
        /
        static_cast<float>(windowHeight);

    glm::mat4 projection =
        camera.getProjectionMatrix(
            aspect
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
    // WORLD
    //------------------------------------------------

    glm::mat4 view =
        camera.getViewMatrix();

    rayDirection =
        glm::normalize(
            glm::vec3(
                glm::inverse(view)
                *
                rayEye
            )
        );

    rayOrigin =
        camera.getPosition();
}


//====================================================
// WORLD RAY -> LOCAL RAY
//====================================================

void PiecePicker3D::transformRayToLocal(
    const glm::vec3& worldOrigin,
    const glm::vec3& worldDirection,
    const Transform3D& transform,
    glm::vec3& localOrigin,
    glm::vec3& localDirection
)
{
    glm::mat4 model =
        transform.getModelMatrix();

    glm::mat4 inverseModel =
        glm::inverse(model);

    //------------------------------------------------
    // ORIGIN
    //------------------------------------------------

    glm::vec4 origin =
        inverseModel *
        glm::vec4(
            worldOrigin,
            1.0f
        );

    localOrigin =
        glm::vec3(origin);

    //------------------------------------------------
    // DIRECTION
    //------------------------------------------------

    glm::vec4 direction =
        inverseModel *
        glm::vec4(
            worldDirection,
            0.0f
        );

    localDirection =
        glm::normalize(
            glm::vec3(direction)
        );
}

//====================================================
// RAY / AABB
//====================================================

bool PiecePicker3D::intersectAABB(
    const glm::vec3& rayOrigin,
    const glm::vec3& rayDirection,
    const Mesh3D& mesh
)
{
    const auto& vertices =
        mesh.getVertices();

    if(vertices.empty())
        return false;

    //------------------------------------------------
    // COMPUTE BOUNDS
    //------------------------------------------------

    glm::vec3 minPoint =
        vertices[0].position;

    glm::vec3 maxPoint =
        vertices[0].position;

    for(const Vertex3D& vertex : vertices)
    {
        minPoint =
            glm::min(
                minPoint,
                vertex.position
            );

        maxPoint =
            glm::max(
                maxPoint,
                vertex.position
            );
    }

    //------------------------------------------------
    // SLAB METHOD
    //------------------------------------------------

    float tMin = 0.0f;

    float tMax =
        std::numeric_limits<float>::max();

    for(int axis = 0; axis < 3; axis++)
    {
        float origin =
            rayOrigin[axis];

        float direction =
            rayDirection[axis];

        float minValue =
            minPoint[axis];

        float maxValue =
            maxPoint[axis];

        if(glm::abs(direction) < EPSILON)
        {
            if(origin < minValue)
                return false;

            if(origin > maxValue)
                return false;

            continue;
        }

        float inv =
            1.0f / direction;

        float t1 =
            (minValue - origin) * inv;

        float t2 =
            (maxValue - origin) * inv;

        if(t1 > t2)
            std::swap(t1, t2);

        tMin =
            glm::max(
                tMin,
                t1
            );

        tMax =
            glm::min(
                tMax,
                t2
            );

        if(tMin > tMax)
            return false;
    }

    return true;
}


//====================================================
// RAY / TRIANGLE (MÖLLER-TRUMBORE)
//====================================================

bool PiecePicker3D::intersectTriangle(
    const glm::vec3& rayOrigin,
    const glm::vec3& rayDirection,
    const glm::vec3& v0,
    const glm::vec3& v1,
    const glm::vec3& v2,
    float& distance
)
{
    //------------------------------------------------
    // EDGES
    //------------------------------------------------

    glm::vec3 edge1 =
        v1 - v0;

    glm::vec3 edge2 =
        v2 - v0;

    //------------------------------------------------
    // P VECTOR
    //------------------------------------------------

    glm::vec3 p =
        glm::cross(
            rayDirection,
            edge2
        );

    float determinant =
        glm::dot(
            edge1,
            p
        );

    //------------------------------------------------
    // PARALLEL
    //------------------------------------------------

    if(glm::abs(determinant) < EPSILON)
        return false;

    float inverseDeterminant =
        1.0f / determinant;

    //------------------------------------------------
    // U
    //------------------------------------------------

    glm::vec3 t =
        rayOrigin - v0;

    float u =
        glm::dot(
            t,
            p
        ) * inverseDeterminant;

    if(u < 0.0f)
        return false;

    if(u > 1.0f)
        return false;

    //------------------------------------------------
    // V
    //------------------------------------------------

    glm::vec3 q =
        glm::cross(
            t,
            edge1
        );

    float v =
        glm::dot(
            rayDirection,
            q
        ) * inverseDeterminant;

    if(v < 0.0f)
        return false;

    if(u + v > 1.0f)
        return false;

    //------------------------------------------------
    // DISTANCE
    //------------------------------------------------

    float tHit =
        glm::dot(
            edge2,
            q
        ) * inverseDeterminant;

    if(tHit < EPSILON)
        return false;

    distance =
        tHit;

    return true;
}


//====================================================
// RAY / TRIANGLES
//====================================================

bool PiecePicker3D::intersectTriangles(
    const glm::vec3& rayOrigin,
    const glm::vec3& rayDirection,
    const Mesh3D& mesh,
    float& distance
)
{
    const auto& vertices =
        mesh.getVertices();

    const auto& indices =
        mesh.getIndices();


    if(vertices.empty() || indices.empty())
        return false;


    bool hit = false;

    float closest =
        std::numeric_limits<float>::max();



    for(size_t i = 0; i + 2 < indices.size(); i += 3)
    {

        const glm::vec3& v0 =
            vertices[
                indices[i]
            ].position;


        const glm::vec3& v1 =
            vertices[
                indices[i + 1]
            ].position;


        const glm::vec3& v2 =
            vertices[
                indices[i + 2]
            ].position;



        float currentDistance;


        if(
            intersectTriangle(
                rayOrigin,
                rayDirection,
                v0,
                v1,
                v2,
                currentDistance
            )
        )
        {

            if(currentDistance < closest)
            {
                closest =
                    currentDistance;

                hit = true;
            }
        }
    }



    if(hit)
    {
        distance = closest;
    }


    return hit;
}