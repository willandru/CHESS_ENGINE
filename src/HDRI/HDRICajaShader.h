#pragma once

#include "Shader3D.h"


//====================================================
// HDRI CAJA SHADER
//====================================================

class HDRICajaShader : public Shader3D
{

public:

    HDRICajaShader();


    ~HDRICajaShader();



    //------------------------------------------------
    // INITIALIZE
    //------------------------------------------------

    bool initialize();



    //------------------------------------------------
    // HDRI
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



    //------------------------------------------------
    // HDRI PROJECTION
    //------------------------------------------------

    void setHeight(
        float height
    );



private:

    static constexpr const char* VERTEX_SHADER =
        "Shaders/caja_hdr.vert";



    static constexpr const char* FRAGMENT_SHADER =
        "Shaders/caja_hdr.frag";

};