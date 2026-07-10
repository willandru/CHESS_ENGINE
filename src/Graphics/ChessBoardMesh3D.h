#pragma once

#include "Mesh3D.h"


class ChessBoardMesh3D
{
public:

    ChessBoardMesh3D();


    //------------------------------------------------
    // MESH
    //------------------------------------------------

    const Mesh3D& getMesh() const;


private:

    Mesh3D mesh;


    //------------------------------------------------
    // BUILD
    //------------------------------------------------

    void build();


    void addCube(
        std::vector<Vertex3D>& vertices,
        std::vector<uint32_t>& indices,
        const glm::vec3& min,
        const glm::vec3& max,
        const glm::vec3& color
    );
};