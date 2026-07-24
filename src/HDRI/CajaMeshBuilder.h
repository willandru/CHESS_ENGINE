#pragma once

#include "CajaMesh3D.h"

#include <glm/glm.hpp>



//====================================================
// CAJA MESH BUILDER
//====================================================

class CajaMeshBuilder
{

public:

    //------------------------------------------------
    // BUILD COMPLETE ROOM
    //------------------------------------------------

    static void build(
        CajaMesh3D& caja,
        const glm::vec3& size,
        const glm::vec3& color
    );



private:

    //------------------------------------------------
    // BUILD ONE FACE
    //------------------------------------------------

    static void buildFloor(
        CajaMesh3D& caja,
        float hx,
        float hy,
        float hz,
        const glm::vec3& color
    );



    static void buildCeiling(
        CajaMesh3D& caja,
        float hx,
        float hy,
        float hz,
        const glm::vec3& color
    );



    static void buildFront(
        CajaMesh3D& caja,
        float hx,
        float hy,
        float hz,
        const glm::vec3& color
    );



    static void buildBack(
        CajaMesh3D& caja,
        float hx,
        float hy,
        float hz,
        const glm::vec3& color
    );



    static void buildLeft(
        CajaMesh3D& caja,
        float hx,
        float hy,
        float hz,
        const glm::vec3& color
    );



    static void buildRight(
        CajaMesh3D& caja,
        float hx,
        float hy,
        float hz,
        const glm::vec3& color
    );



    //------------------------------------------------
    // UPLOAD
    //------------------------------------------------

    static void uploadFace(
        Mesh3D& mesh,
        const std::vector<Vertex3D>& vertices,
        const std::vector<uint32_t>& indices
    );

};