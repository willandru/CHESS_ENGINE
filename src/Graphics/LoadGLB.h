#pragma once

#include <string>
#include <vector>

#include "Mesh3D.h"
#include "Material3D.h"
#include "Texture.h"

namespace tinygltf
{
    class Model;
    class Primitive;
}

class LoadGLB
{
public:

    //------------------------------------------------
    // MAIN
    //------------------------------------------------

    static bool loadGLB(
        const std::string& path,
        Mesh3D& mesh,
        Material3D& material,
        Texture& texture
    );

private:

    //------------------------------------------------
    // MESH
    //------------------------------------------------

    static bool loadPrimitive(
        const tinygltf::Model& model,
        const tinygltf::Primitive& primitive,
        Mesh3D& mesh
    );

    //------------------------------------------------
    // MATERIAL
    //------------------------------------------------

    static bool loadMaterial(
        const tinygltf::Model& model,
        const tinygltf::Primitive& primitive,
        Material3D& material,
        Texture& texture
    );

    //------------------------------------------------
    // ACCESSORS
    //------------------------------------------------

    static const unsigned char* getAccessorData(
        const tinygltf::Model& model,
        int accessorIndex
    );

    static int getAccessorStride(
        const tinygltf::Model& model,
        int accessorIndex
    );

    //------------------------------------------------
    // INDICES
    //------------------------------------------------

    static bool loadIndices(
        const tinygltf::Model& model,
        const tinygltf::Primitive& primitive,
        std::vector<uint32_t>& indices
    );

};