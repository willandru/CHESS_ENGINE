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
#include "Table3D.h"

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
    // OBJECTS
    //------------------------------------------------

    Table3D table;



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
        CajaConstants3D::HDRI_EXPOSURE;



    float hdriRotation =
        CajaConstants3D::HDRI_ROTATION;



    //------------------------------------------------
    // HDRI PROJECTION HEIGHT
    //------------------------------------------------

    // Altura virtual del observador HDRI
    // Ajusta cómo cae la textura sobre el suelo

    float hdriHeight =
        CajaConstants3D::HDRI_HEIGHT;



    //------------------------------------------------
    // GEOMETRY LIMITS
    //------------------------------------------------

    float left =
        CajaConstants3D::LEFT;


    float right =
        CajaConstants3D::RIGHT;


    float front =
        CajaConstants3D::FRONT;


    float back =
        CajaConstants3D::BACK;


    float floor =
        CajaConstants3D::FLOOR;


    float ceiling =
        CajaConstants3D::CEILING;

};