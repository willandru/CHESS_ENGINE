#include "ChessBoardMesh3D.h"

#include "Vertex3D.h"

#include <glm/glm.hpp>

#include <vector>


ChessBoardMesh3D::ChessBoardMesh3D()
{
    build();
}


//====================================================
// MESH
//====================================================

const Mesh3D& ChessBoardMesh3D::getMesh() const
{
    return mesh;
}



//====================================================
// BUILD
//====================================================

void ChessBoardMesh3D::build()
{
    constexpr float squareSize = 1.0f;

    constexpr float boardSize = squareSize * 8.0f;

    constexpr float halfBoard = boardSize * 0.5f;

    constexpr float boardHeight = 0.25f;



    std::vector<Vertex3D> vertices;

    std::vector<uint32_t> indices;



    vertices.reserve(64 * 24);

    indices.reserve(64 * 36);



    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {

            float x0 =
                col * squareSize - halfBoard;


            float x1 =
                x0 + squareSize;


            float z0 =
                row * squareSize - halfBoard;


            float z1 =
                z0 + squareSize;



            glm::vec3 color;


                if ((row + col) % 2 == 0)
            {
                // Beige
                color = glm::vec3(
                    0.93f,
                    0.87f,
                    0.73f
                );
            }
            else
            {
                // Azul
                color = glm::vec3(
                    0.23f,
                    0.35f,
                    0.58f
                );
            }


            addCube(
                vertices,
                indices,

                glm::vec3(
                    x0,
                    0.0f,
                    z0
                ),

                glm::vec3(
                    x1,
                    boardHeight,
                    z1
                ),

                color
            );
        }
    }



    mesh.upload(
        vertices,
        indices
    );
}



//====================================================
// CUBE GENERATOR
//====================================================

void ChessBoardMesh3D::addCube(
    std::vector<Vertex3D>& vertices,
    std::vector<uint32_t>& indices,
    const glm::vec3& min,
    const glm::vec3& max,
    const glm::vec3& color
)
{

    uint32_t offset =
        static_cast<uint32_t>(
            vertices.size()
        );



    Vertex3D v[8];



    // Bottom

    v[0].position = {min.x, min.y, min.z};
    v[1].position = {max.x, min.y, min.z};
    v[2].position = {max.x, min.y, max.z};
    v[3].position = {min.x, min.y, max.z};


    // Top

    v[4].position = {min.x, max.y, min.z};
    v[5].position = {max.x, max.y, min.z};
    v[6].position = {max.x, max.y, max.z};
    v[7].position = {min.x, max.y, max.z};



    for(int i = 0; i < 8; i++)
    {
        v[i].color = color;
        v[i].texCoord = {0.0f,0.0f};
    }



    // Normals

    v[0].normal = {0,-1,0};
    v[1].normal = {0,-1,0};
    v[2].normal = {0,-1,0};
    v[3].normal = {0,-1,0};

    v[4].normal = {0,1,0};
    v[5].normal = {0,1,0};
    v[6].normal = {0,1,0};
    v[7].normal = {0,1,0};



    for(int i = 0; i < 8; i++)
    {
        vertices.push_back(v[i]);
    }



    // Bottom

    indices.insert(
        indices.end(),
        {
            offset+0,
            offset+2,
            offset+1,

            offset+0,
            offset+3,
            offset+2
        }
    );



    // Top

    indices.insert(
        indices.end(),
        {
            offset+4,
            offset+5,
            offset+6,

            offset+4,
            offset+6,
            offset+7
        }
    );



    // Front

    indices.insert(
        indices.end(),
        {
            offset+0,
            offset+1,
            offset+5,

            offset+0,
            offset+5,
            offset+4
        }
    );



    // Back

    indices.insert(
        indices.end(),
        {
            offset+3,
            offset+7,
            offset+6,

            offset+3,
            offset+6,
            offset+2
        }
    );



    // Left

    indices.insert(
        indices.end(),
        {
            offset+0,
            offset+4,
            offset+7,

            offset+0,
            offset+7,
            offset+3
        }
    );



    // Right

    indices.insert(
        indices.end(),
        {
            offset+1,
            offset+2,
            offset+6,

            offset+1,
            offset+6,
            offset+5
        }
    );
}