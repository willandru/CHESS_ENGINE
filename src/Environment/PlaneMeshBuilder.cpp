#include "PlaneMeshBuilder.h"

#include <vector>

void PlaneMeshBuilder::build(
    Mesh3D& mesh,
    float width,
    float height,
    const glm::vec3& color
)
{
    constexpr float thickness = 0.10f;

    const float hx = width * 0.5f;
    const float hy = height * 0.5f;
    const float hz = thickness * 0.5f;

    std::vector<Vertex3D> vertices;
    std::vector<uint32_t> indices;

    auto addFace =
    [&](glm::vec3 a,
        glm::vec3 b,
        glm::vec3 c,
        glm::vec3 d,
        glm::vec3 normal)
    {
        uint32_t start =
            static_cast<uint32_t>(vertices.size());

        Vertex3D v;

        v.normal = normal;
        v.color  = color;

        v.position = a;
        v.texCoord = {0.0f,0.0f};
        vertices.push_back(v);

        v.position = b;
        v.texCoord = {1.0f,0.0f};
        vertices.push_back(v);

        v.position = c;
        v.texCoord = {1.0f,1.0f};
        vertices.push_back(v);

        v.position = d;
        v.texCoord = {0.0f,1.0f};
        vertices.push_back(v);

        indices.push_back(start + 0);
        indices.push_back(start + 1);
        indices.push_back(start + 2);

        indices.push_back(start + 2);
        indices.push_back(start + 3);
        indices.push_back(start + 0);
    };

    //------------------------------------------------
    // FRONT (+Z)
    //------------------------------------------------

    addFace(
        {-hx,-hy, hz},
        { hx,-hy, hz},
        { hx, hy, hz},
        {-hx, hy, hz},
        {0,0,1}
    );

    //------------------------------------------------
    // BACK (-Z)
    //------------------------------------------------

    addFace(
        { hx,-hy,-hz},
        {-hx,-hy,-hz},
        {-hx, hy,-hz},
        { hx, hy,-hz},
        {0,0,-1}
    );

    //------------------------------------------------
    // LEFT (-X)
    //------------------------------------------------

    addFace(
        {-hx,-hy,-hz},
        {-hx,-hy, hz},
        {-hx, hy, hz},
        {-hx, hy,-hz},
        {-1,0,0}
    );

    //------------------------------------------------
    // RIGHT (+X)
    //------------------------------------------------

    addFace(
        { hx,-hy, hz},
        { hx,-hy,-hz},
        { hx, hy,-hz},
        { hx, hy, hz},
        {1,0,0}
    );

    //------------------------------------------------
    // TOP (+Y)
    //------------------------------------------------

    addFace(
        {-hx, hy, hz},
        { hx, hy, hz},
        { hx, hy,-hz},
        {-hx, hy,-hz},
        {0,1,0}
    );

    //------------------------------------------------
    // BOTTOM (-Y)
    //------------------------------------------------

    addFace(
        {-hx,-hy,-hz},
        { hx,-hy,-hz},
        { hx,-hy, hz},
        {-hx,-hy, hz},
        {0,-1,0}
    );

    mesh.upload(
        vertices,
        indices
    );
}