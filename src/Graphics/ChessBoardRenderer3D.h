#pragma once

#include "Renderer3D.h"
#include "Shader3D.h"
#include "Camera3D.h"
#include "Transform3D.h"
#include "ChessBoardMesh3D.h"


class ChessBoardRenderer3D
{
public:

    ChessBoardRenderer3D();


    //------------------------------------------------
    // RENDER
    //------------------------------------------------

    void render(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio
    );


private:

    ChessBoardMesh3D boardMesh;

    Transform3D transform;
};