#pragma once

#include "Shader3D.h"


//====================================================
// HDRI DOME SHADER
//
// Shader especializado para representar un ambiente
// HDRI equirectangular.
//
// Hereda la gestión del programa OpenGL desde Shader3D.
//
// Responsabilidades:
// - Cargar shaders del domo.
// - Configurar uniforms propios del ambiente.
// - Controlar exposición y rotación.
//
// No administra:
// - Texturas.
// - Geometría.
// - Cámara.
// - Renderizado.
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
    // HDRI PARAMETERS
    //------------------------------------------------

    void setHDRITextureSlot(
        int slot
    );


    void setExposure(
        float exposure
    );


    void setRotation(
        float rotation
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