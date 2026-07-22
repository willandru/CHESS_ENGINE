#pragma once

#include "Shader3D.h"


//====================================================
// HDRI DOME SHADER
//
// Shader especializado para representar un ambiente
// HDRI equirectangular.
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


    void setScale(
        float scale
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