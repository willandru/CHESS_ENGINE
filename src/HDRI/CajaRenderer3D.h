#pragma once

#include "Environment3D.h"

#include "CajaMesh3D.h"
#include "CajaMeshBuilder.h"

#include "Transform3D.h"
#include "Material3D.h"

#include "HDRITexture.h"
#include "HDRICajaShader.h"

#include "Camera3D.h"
#include "Renderer3D.h"

#include <glm/glm.hpp>
#include "CajaConstants3D.h"

class CajaRenderer3D : public Environment3D
{

public:

    CajaRenderer3D();


    bool initialize() override;


    void update(
        Camera3D& camera,
        float dt
    ) override;



    void renderBackground(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio
    ) override;



    void renderObjects(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio
    ) override;



private:

    void rebuildMesh();



private:


    //------------------------------------------------
    // SELECTED FACE
    //------------------------------------------------

    CajaMesh3D::Face selectedFace =
        CajaMesh3D::Face::LEFT;



    //------------------------------------------------
    // MESH
    //------------------------------------------------

    CajaMesh3D caja;



    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    Transform3D transform;



    //------------------------------------------------
    // MATERIAL
    //------------------------------------------------

    Material3D material;



    //------------------------------------------------
    // HDRI
    //------------------------------------------------

    HDRITexture hdriTexture;

    HDRICajaShader hdriShader;



    float exposure =
        1.0f;


    float hdriRotation =
        0.0f;



    //------------------------------------------------
    // GEOMETRY LIMITS
    //------------------------------------------------

    float left =
        -6.0f;


    float right =
         6.0f;


    float front =
         6.0f;


    float back =
        -6.0f;


    float floor =
        CajaConstants3D::FLOOR;


    float ceiling =
        CajaConstants3D::CEILING;

};