#pragma once

#include "Shader3D.h"

//====================================================
// HDRI GROUND SHADER
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
    // ROTATION
    //------------------------------------------------

    void setRotation(
        float rotation
    );

    //------------------------------------------------
    // PROJECTION
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

    //------------------------------------------------
    // VIRTUAL HDRI CAMERA
    //------------------------------------------------

    void setVirtualCameraHeight(
        float height
    );

    //------------------------------------------------
    // DOME RADIUS
    //------------------------------------------------

    void setProjectionDistance(
        float distance
    );

private:

    static constexpr const char* VERTEX_SHADER =
        "Shaders/ground_hdr.vert";

    static constexpr const char* FRAGMENT_SHADER =
        "Shaders/ground_hdr.frag";

};