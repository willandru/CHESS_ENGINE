#pragma once


#include "Shader3D.h"



//====================================================
// HDRI DOME SHADER
//
// Shader especializado para representar un ambiente
// HDRI equirectangular sobre una cúpula.
//
// Controla:
// - Textura HDRI
// - Exposición
// - Rotación horizontal
// - Escala horizontal
// - Escala vertical
// - Zoom de proyección
// - Ajuste del horizonte
//
// No administra:
// - Textura
// - Geometría
// - Cámara
// - Renderizado
//
//====================================================


class HDRIDomeShader : public Shader3D
{


public:


    HDRIDomeShader();


    ~HDRIDomeShader();



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
    // PROJECTION CONTROLS
    //------------------------------------------------

    void setScaleX(
        float scaleX
    );


    void setScaleY(
        float scaleY
    );


    void setZoom(
        float zoom
    );


    void setHorizon(
        float horizon
    );



private:


    //------------------------------------------------
    // SHADER FILES
    //------------------------------------------------

    static constexpr const char* VERTEX_SHADER =
        "Shaders/dome_hdr.vert";


    static constexpr const char* FRAGMENT_SHADER =
        "Shaders/dome_hdr.frag";


};