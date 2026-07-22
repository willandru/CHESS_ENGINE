#pragma once


#include "Shader3D.h"

#include <glm/glm.hpp>



//====================================================
// HDRI GROUND SHADER
//
// Shader especializado para proyectar HDRI
// sobre un plano de suelo.
//
// Responsabilidades:
//
// - Cargar shader del suelo HDRI.
// - Controlar textura HDR.
// - Controlar transformación angular.
// - Controlar cámara para proyección.
//
// No administra:
//
// - Geometría.
// - Cámara.
// - Renderizado.
// - Textura HDR.
//
//====================================================


class HDRIGroundShader : public Shader3D
{


public:


    HDRIGroundShader();


    ~HDRIGroundShader();



    //------------------------------------------------
    // INITIALIZATION
    //------------------------------------------------

    bool initialize();



    //------------------------------------------------
    // HDRI TEXTURE
    //------------------------------------------------

    void setHDRITextureSlot(
        int slot
    );



    //------------------------------------------------
    // EXPOSURE
    //------------------------------------------------

    void setExposure(
        float exposure
    );



    //------------------------------------------------
    // ROTATION
    //------------------------------------------------

    void setRotation(
        float rotation
    );



    //------------------------------------------------
    // SCALE
    //------------------------------------------------

    void setScaleX(
        float scaleX
    );


    void setScaleY(
        float scaleY
    );



    //------------------------------------------------
    // ZOOM
    //------------------------------------------------

    void setZoom(
        float zoom
    );



    //------------------------------------------------
    // HORIZON
    //------------------------------------------------

    void setHorizon(
        float horizon
    );



    //------------------------------------------------
    // CAMERA
    //------------------------------------------------

    void setCameraPosition(
        const glm::vec3& position
    );



private:


    //------------------------------------------------
    // SHADER FILES
    //------------------------------------------------

    static constexpr const char* VERTEX_SHADER =
        "Shaders/ground_hdr.vert";



    static constexpr const char* FRAGMENT_SHADER =
        "Shaders/ground_hdr.frag";


};