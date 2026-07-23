#include "ChessPieceRenderer3D.h"

#include "SceneConstants.h"

#include <iostream>



//====================================================
// CONSTRUCTOR
//====================================================

ChessPieceRenderer3D::ChessPieceRenderer3D()
{

    transform.setScale(
    {
        SceneConstants::PIECE_SCALE,
        SceneConstants::PIECE_SCALE,
        SceneConstants::PIECE_SCALE
    });


    whiteMaterial.setColor(
    {
        0.9f,
        0.9f,
        0.9f
    });


    blackMaterial.setColor(
    {
        0.05f,
        0.05f,
        0.05f
    });

}



//====================================================
// INITIALIZE
//====================================================

bool ChessPieceRenderer3D::initialize()
{

    bool ok = true;


    ok &= pieces[0].load(
        "Assets/peon.gltf"
    );


    ok &= pieces[1].load(
        "Assets/caballo.gltf"
    );


    ok &= pieces[2].load(
        "Assets/alfil.gltf"
    );


    ok &= pieces[3].load(
        "Assets/torre.gltf"
    );


    ok &= pieces[4].load(
        "Assets/dama.gltf"
    );


    ok &= pieces[5].load(
        "Assets/rey.gltf"
    );



    if(!ok)
    {
        std::cout
            << "[ChessPieceRenderer3D] ERROR loading pieces\n";
    }
    else
    {
        std::cout
            << "[ChessPieceRenderer3D] pieces loaded\n";
    }


    return ok;
}





//====================================================
// GET MESH
//====================================================

const Mesh3D& ChessPieceRenderer3D::getMesh(
    Piece piece
) const
{
    return pieces[
        getPieceIndex(piece)
    ].getMesh();
}







//====================================================
// BUILD TRANSFORM
//====================================================

Transform3D ChessPieceRenderer3D::buildTransform(
    Piece piece,
    uint8_t square
) const
{

    float x;
    float z;


    squareToWorld(
        square,
        x,
        z
    );



    Transform3D pieceTransform;



    float y =
    SceneConstants::PIECE_HEIGHT
    +
    getPieceYOffset(piece);



    pieceTransform.setPosition(
    {
        x,
        y,
        z
    });



    pieceTransform.setScale(
    {
        SceneConstants::PIECE_SCALE,
        SceneConstants::PIECE_SCALE,
        SceneConstants::PIECE_SCALE
    });



    return pieceTransform;
}







//====================================================
// RENDER
//====================================================

void ChessPieceRenderer3D::render(
    Renderer3D& renderer,
    Shader3D& shader,
    Camera3D& camera,
    float aspectRatio,
    Piece piece,
    uint8_t square
)
{

    if(piece == Piece::EMPTY)
        return;



    int index =
        getPieceIndex(piece);



    if(index < 0)
        return;




    Transform3D pieceTransform =
        buildTransform(
            piece,
            square
        );




    Material3D& currentMaterial =
        (piece >= Piece::BLACK_PAWN)
        ?
        blackMaterial
        :
        whiteMaterial;




    renderer.renderPiece(
        pieces[index].getMesh(),
        pieceTransform,
        currentMaterial,
        shader,
        camera,
        aspectRatio
    );

}







//====================================================
// PIECE INDEX
//====================================================

int ChessPieceRenderer3D::getPieceIndex(
    Piece piece
) const
{

    switch(piece)
    {

        case Piece::WHITE_PAWN:
        case Piece::BLACK_PAWN:
            return 0;


        case Piece::WHITE_KNIGHT:
        case Piece::BLACK_KNIGHT:
            return 1;


        case Piece::WHITE_BISHOP:
        case Piece::BLACK_BISHOP:
            return 2;


        case Piece::WHITE_ROOK:
        case Piece::BLACK_ROOK:
            return 3;


        case Piece::WHITE_QUEEN:
        case Piece::BLACK_QUEEN:
            return 4;


        case Piece::WHITE_KING:
        case Piece::BLACK_KING:
            return 5;


        default:
            return -1;

    }

}







//====================================================
// PIECE Y OFFSET
//====================================================

float ChessPieceRenderer3D::getPieceYOffset(
    Piece piece
) const
{

    switch(piece)
    {

        case Piece::WHITE_PAWN:
        case Piece::BLACK_PAWN:
            return SceneConstants::PAWN_OFFSET_Y;


        case Piece::WHITE_KNIGHT:
        case Piece::BLACK_KNIGHT:
            return SceneConstants::KNIGHT_OFFSET_Y;


        case Piece::WHITE_BISHOP:
        case Piece::BLACK_BISHOP:
            return SceneConstants::BISHOP_OFFSET_Y;


        case Piece::WHITE_ROOK:
        case Piece::BLACK_ROOK:
            return SceneConstants::ROOK_OFFSET_Y;


        case Piece::WHITE_QUEEN:
        case Piece::BLACK_QUEEN:
            return SceneConstants::QUEEN_OFFSET_Y;


        case Piece::WHITE_KING:
        case Piece::BLACK_KING:
            return SceneConstants::KING_OFFSET_Y;


        default:
            return 0.0f;

    }

}







//====================================================
// BOARD POSITION
//====================================================

void ChessPieceRenderer3D::squareToWorld(
    uint8_t square,
    float& x,
    float& z
) const
{

    int row =
        square /
        SceneConstants::BOARD_SQUARES;


    int col =
        square %
        SceneConstants::BOARD_SQUARES;



    x =
        (col * SceneConstants::SQUARE_SIZE)
        -
        SceneConstants::HALF_BOARD_SIZE
        +
        SceneConstants::SQUARE_SIZE * 0.5f;



    z =
        (row * SceneConstants::SQUARE_SIZE)
        -
        SceneConstants::HALF_BOARD_SIZE
        +
        SceneConstants::SQUARE_SIZE * 0.5f;

}







//====================================================
// MATERIALS
//====================================================

Material3D& ChessPieceRenderer3D::getWhiteMaterial()
{
    return whiteMaterial;
}



Material3D& ChessPieceRenderer3D::getBlackMaterial()
{
    return blackMaterial;
}








//====================================================
// WORLD POSITION
//====================================================

glm::vec3 ChessPieceRenderer3D::getWorldPosition(
    uint8_t square
) const
{

    float x;
    float z;


    squareToWorld(
        square,
        x,
        z
    );


    return
    {
        x,
        SceneConstants::PIECE_HEIGHT +
        SceneConstants::SCENE_VERTICAL_OFFSET,
        z
    };

}