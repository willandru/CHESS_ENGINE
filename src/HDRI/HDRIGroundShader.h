#pragma once

#include "Shader3D.h"

#include <glm/glm.hpp>

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

    //------------------------------------------------
    // HDRI CAMERA HEIGHT
    //------------------------------------------------

    void setHDRICameraHeight(
        float height
    );

    //------------------------------------------------
    // CAPTURE HEIGHT
    //------------------------------------------------

    void setCaptureHeight(
        float captureHeight
    );
private:

    static constexpr const char* VERTEX_SHADER =
        "Shaders/ground_hdr.vert";

    static constexpr const char* FRAGMENT_SHADER =
        "Shaders/ground_hdr.frag";

};