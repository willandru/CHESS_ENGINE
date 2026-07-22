#pragma once

#include "Shader3D.h"

//====================================================
// HDRI DOME SHADER
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