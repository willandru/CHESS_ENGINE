#include "ChessPieceMesh3D.h"

#include "Vertex3D.h"

#include <iostream>
#include <vector>

#include "tiny_gltf.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cfloat>


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

void ChessPieceMesh3D::setMesh(
    const Mesh3D& value
)
{
    mesh = value;
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
        std::cout << "[GLTF WARNING] " << warning << std::endl;


    if(!error.empty())
        std::cout << "[GLTF ERROR] " << error << std::endl;


    if(!result)
        return false;


    if(model.meshes.empty())
        return false;



    std::vector<Vertex3D> vertices;
    std::vector<uint32_t> indices;



    const auto& primitive =
        model.meshes[0].primitives[0];



    //------------------------------------------------
    // POSITION DATA
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
    // NORMAL DATA
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
    // TEXCOORD DATA
    //------------------------------------------------

    const float* texCoords = nullptr;

    if(primitive.attributes.count("TEXCOORD_0"))
    {
        auto texAccessor =
            model.accessors[
                primitive.attributes.at("TEXCOORD_0")
            ];

        auto texView =
            model.bufferViews[
                texAccessor.bufferView
            ];

        auto& texBuffer =
            model.buffers[
                texView.buffer
            ];

        texCoords =
            reinterpret_cast<const float*>(
                &texBuffer.data[
                    texAccessor.byteOffset +
                    texView.byteOffset
                ]
            );
    }

    //------------------------------------------------
    // APPLY GLTF NODE TRANSFORM
    //------------------------------------------------

    glm::mat4 nodeTransform(1.0f);


    for(const auto& node : model.nodes)
    {
        if(node.mesh == 0)
        {

            if(node.translation.size() == 3)
            {
                nodeTransform =
                    glm::translate(
                        nodeTransform,
                        glm::vec3(
                            node.translation[0],
                            node.translation[1],
                            node.translation[2]
                        )
                    );
            }


            if(node.scale.size() == 3)
            {
                nodeTransform =
                    glm::scale(
                        nodeTransform,
                        glm::vec3(
                            node.scale[0],
                            node.scale[1],
                            node.scale[2]
                        )
                    );
            }

            break;
        }
    }



    //------------------------------------------------
    // TEMP POSITIONS + BOUNDS
    //------------------------------------------------

    std::vector<glm::vec3> transformedPositions;

    transformedPositions.reserve(
        posAccessor.count
    );


    glm::vec3 minBounds(
        FLT_MAX
    );

    glm::vec3 maxBounds(
        -FLT_MAX
    );



    for(size_t i = 0;
        i < posAccessor.count;
        i++)
    {

        glm::vec4 p =
            nodeTransform *
            glm::vec4(
                positions[i*3+0],
                positions[i*3+1],
                positions[i*3+2],
                1.0f
            );


        glm::vec3 pos(
            p.x,
            p.y,
            p.z
        );


        transformedPositions.push_back(
            pos
        );


        minBounds =
            glm::min(
                minBounds,
                pos
            );


        maxBounds =
            glm::max(
                maxBounds,
                pos
            );
    }



    //------------------------------------------------
    // NORMALIZE ORIGIN
    //------------------------------------------------

    // Centro horizontal
    glm::vec3 center =
        (minBounds + maxBounds)
        * 0.5f;


    // Altura mínima de la pieza
    // La base queda en Y = 0
    float baseHeight =
        minBounds.y;



    //------------------------------------------------
    // BUILD VERTICES
    //------------------------------------------------

    for(size_t i = 0;
        i < transformedPositions.size();
        i++)
    {

        Vertex3D vertex;


        glm::vec3 position =
            transformedPositions[i];


        //------------------------------------------------
        // CENTER X/Z
        //------------------------------------------------

        position.x -= center.x;
        position.z -= center.z;


        //------------------------------------------------
        // PLACE BASE ON Y=0
        //------------------------------------------------

        position.y -= baseHeight;



        vertex.position =
            position;



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



       if(texCoords)
    {
        vertex.texCoord =
        {
            texCoords[i * 2 + 0],
            texCoords[i * 2 + 1]
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


        vertices.push_back(vertex);
    }



    //------------------------------------------------
    // INDICES
    //------------------------------------------------

    if(primitive.indices >= 0)
    {

        const auto& accessor =
            model.accessors[
                primitive.indices
            ];


        const auto& view =
            model.bufferViews[
                accessor.bufferView
            ];


        const auto& buffer =
            model.buffers[
                view.buffer
            ];


        const unsigned char* data =
            buffer.data.data()
            +
            view.byteOffset
            +
            accessor.byteOffset;



        switch(accessor.componentType)
        {

        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        {
            auto ptr =
                reinterpret_cast<const uint8_t*>(data);


            for(size_t i=0;i<accessor.count;i++)
                indices.push_back(ptr[i]);

            break;
        }


        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        {
            auto ptr =
                reinterpret_cast<const uint16_t*>(data);


            for(size_t i=0;i<accessor.count;i++)
                indices.push_back(ptr[i]);

            break;
        }


        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
        {
            auto ptr =
                reinterpret_cast<const uint32_t*>(data);


            for(size_t i=0;i<accessor.count;i++)
                indices.push_back(ptr[i]);

            break;
        }


        default:
            return false;
        }
    }



    //------------------------------------------------
    // UPLOAD
    //------------------------------------------------

    mesh.upload(
        vertices,
        indices
    );


    std::cout
        << "[ChessPieceMesh3D] Normalized base: "
        << path
        << std::endl;


    return true;
}