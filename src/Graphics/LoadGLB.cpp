#include "LoadGLB.h"

#include "Vertex3D.h"

#include "tiny_gltf.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <cfloat>


//====================================================
// MAIN LOADER
//====================================================

bool LoadGLB::loadGLB(
    const std::string& path,
    Mesh3D& mesh,
    Material3D& material,
    Texture& texture
)
{
    tinygltf::TinyGLTF loader;

    tinygltf::Model model;

    std::string error;
    std::string warning;


    //------------------------------------------------
    // LOAD GLB
    //------------------------------------------------

    bool result =
        loader.LoadBinaryFromFile(
            &model,
            &error,
            &warning,
            path
        );


    if(!warning.empty())
    {
        std::cout
            << "[GLB WARNING] "
            << warning
            << std::endl;
    }


    if(!error.empty())
    {
        std::cout
            << "[GLB ERROR] "
            << error
            << std::endl;
    }


    if(!result)
    {
        std::cout
            << "[GLB] Failed loading "
            << path
            << std::endl;

        return false;
    }


    if(model.meshes.empty())
    {
        std::cout
            << "[GLB] No meshes found"
            << std::endl;

        return false;
    }


    //------------------------------------------------
    // TAKE FIRST MESH
    //------------------------------------------------

    const tinygltf::Mesh& gltfMesh =
        model.meshes[0];


    if(gltfMesh.primitives.empty())
    {
        std::cout
            << "[GLB] Mesh has no primitives"
            << std::endl;

        return false;
    }


    const tinygltf::Primitive& primitive =
        gltfMesh.primitives[0];



    //------------------------------------------------
    // LOAD GEOMETRY
    //------------------------------------------------

    if(
        !loadPrimitive(
            model,
            primitive,
            mesh
        )
    )
    {
        std::cout
            << "[GLB] Failed loading geometry"
            << std::endl;

        return false;
    }



    //------------------------------------------------
    // LOAD MATERIAL + TEXTURE
    //------------------------------------------------

    loadMaterial(
        model,
        primitive,
        material,
        texture
    );



    std::cout
        << "[GLB] Loaded successfully: "
        << path
        << std::endl;


    return true;
}




//====================================================
// ACCESSOR DATA
//====================================================

const unsigned char* LoadGLB::getAccessorData(
    const tinygltf::Model& model,
    int accessorIndex
)
{
    const tinygltf::Accessor& accessor =
        model.accessors[accessorIndex];


    const tinygltf::BufferView& view =
        model.bufferViews[
            accessor.bufferView
        ];


    const tinygltf::Buffer& buffer =
        model.buffers[
            view.buffer
        ];


    return
        buffer.data.data()
        +
        view.byteOffset
        +
        accessor.byteOffset;
}




//====================================================
// ACCESSOR STRIDE
//====================================================

int LoadGLB::getAccessorStride(
    const tinygltf::Model& model,
    int accessorIndex
)
{
    const tinygltf::Accessor& accessor =
        model.accessors[accessorIndex];


    const tinygltf::BufferView& view =
        model.bufferViews[
            accessor.bufferView
        ];


    if(view.byteStride != 0)
        return view.byteStride;


    int componentSize = 0;


    switch(accessor.componentType)
    {

        case TINYGLTF_COMPONENT_TYPE_FLOAT:
            componentSize = sizeof(float);
            break;


        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
            componentSize = sizeof(uint8_t);
            break;


        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
            componentSize = sizeof(uint16_t);
            break;


        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
            componentSize = sizeof(uint32_t);
            break;


        default:
            return 0;
    }



    int components = 0;


    switch(accessor.type)
    {

        case TINYGLTF_TYPE_SCALAR:
            components = 1;
            break;


        case TINYGLTF_TYPE_VEC2:
            components = 2;
            break;


        case TINYGLTF_TYPE_VEC3:
            components = 3;
            break;


        case TINYGLTF_TYPE_VEC4:
            components = 4;
            break;


        default:
            return 0;
    }


    return componentSize * components;
}

//====================================================
// LOAD PRIMITIVE
//====================================================

bool LoadGLB::loadPrimitive(
    const tinygltf::Model& model,
    const tinygltf::Primitive& primitive,
    Mesh3D& mesh
)
{

    //------------------------------------------------
    // REQUIRED POSITION
    //------------------------------------------------

    if(
        primitive.attributes.find("POSITION")
        ==
        primitive.attributes.end()
    )
    {
        std::cout
            << "[GLB] Missing POSITION"
            << std::endl;

        return false;
    }



    int positionAccessor =
        primitive.attributes.at(
            "POSITION"
        );



    const tinygltf::Accessor& posAccessor =
        model.accessors[
            positionAccessor
        ];



    const unsigned char* posData =
        getAccessorData(
            model,
            positionAccessor
        );



    int posStride =
        getAccessorStride(
            model,
            positionAccessor
        );



    //------------------------------------------------
    // NORMAL
    //------------------------------------------------

    const unsigned char* normalData =
        nullptr;


    int normalStride = 0;


    if(
        primitive.attributes.find("NORMAL")
        !=
        primitive.attributes.end()
    )
    {

        int normalAccessor =
            primitive.attributes.at(
                "NORMAL"
            );


        normalData =
            getAccessorData(
                model,
                normalAccessor
            );


        normalStride =
            getAccessorStride(
                model,
                normalAccessor
            );
    }



    //------------------------------------------------
    // UV
    //------------------------------------------------

    const unsigned char* uvData =
        nullptr;


    int uvStride = 0;


    if(
        primitive.attributes.find("TEXCOORD_0")
        !=
        primitive.attributes.end()
    )
    {

        int uvAccessor =
            primitive.attributes.at(
                "TEXCOORD_0"
            );


        uvData =
            getAccessorData(
                model,
                uvAccessor
            );


        uvStride =
            getAccessorStride(
                model,
                uvAccessor
            );
    }



    //------------------------------------------------
    // CREATE VERTICES
    //------------------------------------------------

    std::vector<Vertex3D> vertices;


    vertices.reserve(
        posAccessor.count
    );



    glm::vec3 minBounds(
        FLT_MAX
    );


    glm::vec3 maxBounds(
        -FLT_MAX
    );



    std::vector<glm::vec3> positions;


    positions.reserve(
        posAccessor.count
    );



    //------------------------------------------------
    // READ POSITIONS
    //------------------------------------------------

    for(size_t i = 0; i < posAccessor.count; i++)
    {

        const float* p =
            reinterpret_cast<const float*>(
                posData + i * posStride
            );


        glm::vec3 position(
            p[0],
            p[1],
            p[2]
        );


        positions.push_back(
            position
        );


        minBounds =
            glm::min(
                minBounds,
                position
            );


        maxBounds =
            glm::max(
                maxBounds,
                position
            );
    }



    //------------------------------------------------
    // CENTER + BASE
    //------------------------------------------------

    glm::vec3 center =
        (minBounds + maxBounds)
        *
        0.5f;


    float base =
        minBounds.y;



    //------------------------------------------------
    // BUILD VERTEX ARRAY
    //------------------------------------------------

    for(size_t i = 0; i < positions.size(); i++)
    {

        Vertex3D vertex;


        glm::vec3 p =
            positions[i];


        p.x -= center.x;
        p.z -= center.z;
        p.y -= base;



        vertex.position =
            p;



        //------------------------------------------------
        // NORMAL
        //------------------------------------------------

        if(normalData)
        {

            const float* n =
                reinterpret_cast<const float*>(
                    normalData
                    +
                    i * normalStride
                );


            vertex.normal =
            {
                n[0],
                n[1],
                n[2]
            };

        }
        else
        {

            vertex.normal =
            {
                0.0f,
                1.0f,
                0.0f
            };

        }



        //------------------------------------------------
        // UV
        //------------------------------------------------

        if(uvData)
        {

            const float* uv =
                reinterpret_cast<const float*>(
                    uvData
                    +
                    i * uvStride
                );


            vertex.texCoord =
            {
                uv[0],
                uv[1]
            };

        }
        else
        {

            vertex.texCoord =
            {
                0.0f,
                0.0f
            };

        }



        vertex.color =
        {
            1.0f,
            1.0f,
            1.0f
        };



        vertices.push_back(
            vertex
        );
    }




    //------------------------------------------------
    // INDICES
    //------------------------------------------------

    std::vector<uint32_t> indices;


    if(
        !loadIndices(
            model,
            primitive,
            indices
        )
    )
    {
        return false;
    }




    //------------------------------------------------
    // UPLOAD GPU
    //------------------------------------------------

    mesh.upload(
        vertices,
        indices
    );


    return true;
}

//====================================================
// LOAD INDICES
//====================================================

bool LoadGLB::loadIndices(
    const tinygltf::Model& model,
    const tinygltf::Primitive& primitive,
    std::vector<uint32_t>& indices
)
{

    //------------------------------------------------
    // NO INDEX BUFFER
    //------------------------------------------------

    if(primitive.indices < 0)
    {
        return false;
    }



    const tinygltf::Accessor& accessor =
        model.accessors[
            primitive.indices
        ];



    const unsigned char* data =
        getAccessorData(
            model,
            primitive.indices
        );



    indices.reserve(
        accessor.count
    );



    //------------------------------------------------
    // COMPONENT TYPE
    //------------------------------------------------

    switch(accessor.componentType)
    {

        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        {

            const uint8_t* ptr =
                reinterpret_cast<const uint8_t*>(
                    data
                );


            for(size_t i = 0; i < accessor.count; i++)
            {
                indices.push_back(
                    ptr[i]
                );
            }

            break;
        }



        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        {

            const uint16_t* ptr =
                reinterpret_cast<const uint16_t*>(
                    data
                );


            for(size_t i = 0; i < accessor.count; i++)
            {
                indices.push_back(
                    ptr[i]
                );
            }

            break;
        }



        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
        {

            const uint32_t* ptr =
                reinterpret_cast<const uint32_t*>(
                    data
                );


            for(size_t i = 0; i < accessor.count; i++)
            {
                indices.push_back(
                    ptr[i]
                );
            }

            break;
        }



        default:

            std::cout
                << "[GLB] Unsupported index type"
                << std::endl;

            return false;
    }



    return true;
}






//====================================================
// LOAD MATERIAL + TEXTURE
//====================================================

bool LoadGLB::loadMaterial(
    const tinygltf::Model& model,
    const tinygltf::Primitive& primitive,
    Material3D& material,
    Texture& texture
)
{

    //------------------------------------------------
    // DEFAULT COLOR
    //------------------------------------------------

    material.setColor(
        {
            1.0f,
            1.0f,
            1.0f
        }
    );



    //------------------------------------------------
    // NO MATERIAL
    //------------------------------------------------

    if(primitive.material < 0)
    {
        return true;
    }



    if(
        primitive.material
        >=
        static_cast<int>(
            model.materials.size()
        )
    )
    {
        return false;
    }



    const tinygltf::Material& gltfMaterial =
        model.materials[
            primitive.material
        ];

       

    //------------------------------------------------
    // BASE COLOR
    //------------------------------------------------

    const auto& pbr =
        gltfMaterial
        .pbrMetallicRoughness;


    if(
        pbr.baseColorFactor.size()
        == 4
    )
    {

        material.setColor(
            {
                static_cast<float>(
                    pbr.baseColorFactor[0]
                ),

                static_cast<float>(
                    pbr.baseColorFactor[1]
                ),

                static_cast<float>(
                    pbr.baseColorFactor[2]
                )
            }
        );
    }




    //------------------------------------------------
    // BASE COLOR TEXTURE
    //------------------------------------------------

    int textureIndex =
        pbr
        .baseColorTexture
        .index;



    if(textureIndex < 0)
    {
        return true;
    }



    if(
        textureIndex
        >=
        static_cast<int>(
            model.textures.size()
        )
    )
    {
        return false;
    }



    const tinygltf::Texture& gltfTexture =
        model.textures[
            textureIndex
        ];



    //------------------------------------------------
    // IMAGE SOURCE
    //------------------------------------------------

    int imageIndex =
        gltfTexture.source;



    if(imageIndex < 0)
    {
        return false;
    }



    if(
        imageIndex
        >=
        static_cast<int>(
            model.images.size()
        )
    )
    {
        return false;
    }



    const tinygltf::Image& image =
        model.images[
            imageIndex
        ];


    //------------------------------------------------
    // LOAD EMBEDDED IMAGE
    //------------------------------------------------

    if(
        image.image.empty()
    )
    {
        std::cout
            << "[GLB] Image empty"
            << std::endl;

        return false;
    }


    
    
    std::vector<unsigned char> textureData;


    if(image.bits == 16)
    {
       

        const unsigned short* src =
            reinterpret_cast<const unsigned short*>(
                image.image.data()
            );


        size_t pixelCount =
            image.width *
            image.height *
            image.component;


        textureData.resize(
            pixelCount
        );


        for(size_t i = 0; i < pixelCount; i++)
        {
            textureData[i] =
                static_cast<unsigned char>(
                    src[i] >> 8
                );
        }
    }
    else
    {
        textureData =
            image.image;
    }



    bool loaded =
        texture.loadFromMemory(
            textureData.data(),

            image.width,

            image.height,

            image.component
        );



    if(!loaded)
    {
        std::cout
            << "[GLB] Failed creating texture"
            << std::endl;

        return false;
    }



    material.setTexture(
        &texture
    );



  
    return true;
}


//====================================================
// END OF FILE VALIDATION HELPERS
//====================================================


//----------------------------------------------------
// NOTE:
//
// GLTF materials are PBR.
// The renderer currently uses:
//
// baseColorFactor
// baseColorTexture
//
// Metallic and roughness are intentionally ignored
// because Material3D currently supports only:
//
// color
// texture
//
// This keeps compatibility with the current engine.
//----------------------------------------------------



//====================================================
// EOF
//====================================================