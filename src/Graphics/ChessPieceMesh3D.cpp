#include "ChessPieceMesh3D.h"

#include "Vertex3D.h"

#include <iostream>
#include <vector>

#include "tiny_gltf.h"


ChessPieceMesh3D::ChessPieceMesh3D()
{

}


//====================================================
// LOAD
//====================================================

bool ChessPieceMesh3D::load(
    const std::string& path
)
{
    return loadGLTF(path);
}



//====================================================
// GET MESH
//====================================================

const Mesh3D& ChessPieceMesh3D::getMesh() const
{
    return mesh;
}


bool ChessPieceMesh3D::loadGLTF(
    const std::string& path
)
{
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;

    std::string error;
    std::string warning;

    bool result =
        loader.LoadASCIIFromFile(
            &model,
            &error,
            &warning,
            path
        );

    if(!warning.empty())
    {
        std::cout
            << "[GLTF WARNING] "
            << warning
            << std::endl;
    }

    if(!error.empty())
    {
        std::cout
            << "[GLTF ERROR] "
            << error
            << std::endl;
    }

    if(!result)
    {
        return false;
    }

    if(model.meshes.empty())
    {
        return false;
    }

    std::vector<Vertex3D> vertices;
    std::vector<uint32_t> indices;

    //------------------------------------------------
    // FIRST MESH
    //------------------------------------------------

    const auto& gltfMesh =
        model.meshes[0];

    const auto& primitive =
        gltfMesh.primitives[0];

    //------------------------------------------------
    // POSITIONS
    //------------------------------------------------

    auto posAccessor =
        model.accessors[
            primitive.attributes.at("POSITION")
        ];

    auto posView =
        model.bufferViews[
            posAccessor.bufferView
        ];

    auto& posBuffer =
        model.buffers[
            posView.buffer
        ];

    const float* positions =
        reinterpret_cast<const float*>(
            &posBuffer.data[
                posAccessor.byteOffset +
                posView.byteOffset
            ]
        );

    //------------------------------------------------
    // NORMALS
    //------------------------------------------------

    const float* normals = nullptr;

    if(primitive.attributes.count("NORMAL"))
    {
        auto normalAccessor =
            model.accessors[
                primitive.attributes.at("NORMAL")
            ];

        auto normalView =
            model.bufferViews[
                normalAccessor.bufferView
            ];

        auto& normalBuffer =
            model.buffers[
                normalView.buffer
            ];

        normals =
            reinterpret_cast<const float*>(
                &normalBuffer.data[
                    normalAccessor.byteOffset +
                    normalView.byteOffset
                ]
            );
    }

    //------------------------------------------------
    // CREATE VERTICES
    //------------------------------------------------

    for(size_t i = 0;
        i < posAccessor.count;
        i++)
    {
        Vertex3D vertex;

        vertex.position =
        {
            positions[i*3+0],
            positions[i*3+1],
            positions[i*3+2]
        };

        if(normals)
        {
            vertex.normal =
            {
                normals[i*3+0],
                normals[i*3+1],
                normals[i*3+2]
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

        vertex.texCoord =
        {
            0.0f,
            0.0f
        };

        vertex.color =
        {
            1.0f,
            1.0f,
            1.0f
        };

        vertices.push_back(vertex);
    }

    //------------------------------------------------
    // INDICES
    //------------------------------------------------

    if(primitive.indices >= 0)
    {
        const auto& indexAccessor =
            model.accessors[
                primitive.indices
            ];

        const auto& indexView =
            model.bufferViews[
                indexAccessor.bufferView
            ];

        const auto& indexBuffer =
            model.buffers[
                indexView.buffer
            ];

        const unsigned char* buffer =
            indexBuffer.data.data()
            + indexView.byteOffset
            + indexAccessor.byteOffset;

        switch(indexAccessor.componentType)
        {
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
            {
                const uint8_t* data =
                    reinterpret_cast<const uint8_t*>(buffer);

                for(size_t i = 0;
                    i < indexAccessor.count;
                    i++)
                {
                    indices.push_back(data[i]);
                }

                break;
            }

            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
            {
                const uint16_t* data =
                    reinterpret_cast<const uint16_t*>(buffer);

                for(size_t i = 0;
                    i < indexAccessor.count;
                    i++)
                {
                    indices.push_back(data[i]);
                }

                break;
            }

            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
            {
                const uint32_t* data =
                    reinterpret_cast<const uint32_t*>(buffer);

                for(size_t i = 0;
                    i < indexAccessor.count;
                    i++)
                {
                    indices.push_back(data[i]);
                }

                break;
            }

            default:
            {
                std::cout
                    << "Unsupported index type: "
                    << indexAccessor.componentType
                    << std::endl;

                return false;
            }
        }

        std::cout
            << "Model: "
            << path
            << std::endl;

        std::cout
            << "Vertices: "
            << vertices.size()
            << std::endl;

        std::cout
            << "Indices: "
            << indices.size()
            << std::endl;

        std::cout
            << "Index component type: "
            << indexAccessor.componentType
            << std::endl;
    }

    //------------------------------------------------
    // GPU UPLOAD
    //------------------------------------------------

    mesh.upload(
        vertices,
        indices
    );

    std::cout
        << "[ChessPieceMesh3D] Loaded "
        << path
        << std::endl;

    return true;
}