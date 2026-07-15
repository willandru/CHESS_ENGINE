#include "HighlightRenderer3D.h"

#include "ChessGame.h"
#include "GameState.h"
#include "MoveFilter.h"

#include "Renderer3D.h"
#include "Shader3D.h"
#include "Camera3D.h"

#include "Mesh3D.h"
#include "Vertex3D.h"
#include "Transform3D.h"

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "SceneConstants.h"

namespace
{

    Mesh3D gHighlightMesh;
    Transform3D gTransform;

    bool gInitialized = false;



    //------------------------------------------------
    // BUILD MESH
    //------------------------------------------------

    void buildMesh()
    {
        if(gInitialized)
            return;



        std::vector<Vertex3D> vertices(4);



        // Casilla 1x1 centrada en el origen

        vertices[0].position =
        {
            -0.5f,
            0.0f,
            -0.5f
        };


        vertices[1].position =
        {
             0.5f,
             0.0f,
            -0.5f
        };


        vertices[2].position =
        {
             0.5f,
             0.0f,
             0.5f
        };


        vertices[3].position =
        {
            -0.5f,
             0.0f,
             0.5f
        };



        for(Vertex3D& v : vertices)
        {
            v.normal =
            {
                0.0f,
                1.0f,
                0.0f
            };


            v.texCoord =
            {
                0.0f,
                0.0f
            };


            v.color =
            {
                1.0f,
                1.0f,
                1.0f
            };
        }



        std::vector<uint32_t> indices =
        {
            0,1,2,
            0,2,3
        };



        gHighlightMesh.upload(
            vertices,
            indices
        );



        gTransform.setScale(
        {
            1.0f,
            1.0f,
            1.0f
        });



        gInitialized = true;



        std::cout
            << "[Highlight] Mesh created"
            << std::endl;
    }





    //------------------------------------------------
    // BOARD POSITION
    //------------------------------------------------

    void squareToWorld(
    uint8_t square,
    float& x,
    float& z
    )
    {
        int row = square / SceneConstants::BOARD_SQUARES;
        int col = square % SceneConstants::BOARD_SQUARES;

        x =
            (col * SceneConstants::SQUARE_SIZE)
            - SceneConstants::HALF_BOARD_SIZE
            + (SceneConstants::SQUARE_SIZE * 0.5f);

        z =
            (row * SceneConstants::SQUARE_SIZE)
            - SceneConstants::HALF_BOARD_SIZE
            + (SceneConstants::SQUARE_SIZE * 0.5f);
    }

}





//====================================================
// RENDER
//====================================================

void HighlightRenderer3D::render(
    Renderer3D& renderer,
    Shader3D& shader,
    Camera3D& camera,
    float aspectRatio,
    const ChessGame& game
)
{

    buildMesh();



    const GameState& state =
        game.getGameState();



    PlayerSide side =
        state.getTurn();



    bool check =
        MoveFilter::isKingInCheck(
            state,
            side
        );


    bool mate =
        MoveFilter::isCheckmate(
            state,
            side
        );



    uint8_t king =
        state.findKing(side);





    if(king != 255)
    {

        if(mate)
        {
            renderSquare(
                renderer,
                shader,
                camera,
                aspectRatio,
                king,
                1.0f,
                0.0f,
                0.0f
            );
        }

        else if(check)
        {
            renderSquare(
                renderer,
                shader,
                camera,
                aspectRatio,
                king,
                0.0f,
                0.4f,
                1.0f
            );
        }
    }





    if(game.hasSelection())
    {

        renderSquare(
            renderer,
            shader,
            camera,
            aspectRatio,
            game.getSelectedSquare(),
            0.15f,
            0.85f,
            0.20f
        );



        renderMoves(
            renderer,
            shader,
            camera,
            aspectRatio,
            game.getMoves(),
            0.85f,
            0.85f,
            0.15f
        );
    }

}





//====================================================
// RENDER SQUARE
//====================================================

void HighlightRenderer3D::renderSquare(
    Renderer3D& renderer,
    Shader3D& shader,
    Camera3D& camera,
    float aspectRatio,
    uint8_t square,
    float r,
    float g,
    float b
)
{
    float x;
    float z;

    squareToWorld(
        square,
        x,
        z
    );

    gTransform.setPosition(
        glm::vec3(
            x,
            SceneConstants::BOARD_HEIGHT +
            SceneConstants::BOARD_THICKNESS +
            0.001f,
            z
        )
    );

    glDisable(
        GL_CULL_FACE
    );

    renderer.drawColored(
        gHighlightMesh,
        gTransform,
        shader,
        camera,
        aspectRatio,
        glm::vec3(
            r,
            g,
            b
        )
    );

    glEnable(
        GL_CULL_FACE
    );
}

//====================================================
// RENDER MOVES
//====================================================

void HighlightRenderer3D::renderMoves(
    Renderer3D& renderer,
    Shader3D& shader,
    Camera3D& camera,
    float aspectRatio,
    const std::vector<Move>& moves,
    float r,
    float g,
    float b
)
{

    for(const Move& move : moves)
    {

        renderSquare(
            renderer,
            shader,
            camera,
            aspectRatio,
            move.to,
            r,
            g,
            b
        );

    }

}