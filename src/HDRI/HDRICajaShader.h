#pragma once

#include "Shader3D.h"

class HDRICajaShader : public Shader3D
{

public:

    HDRICajaShader();

    ~HDRICajaShader();

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



    //------------------------------------------------
    // UV
    //------------------------------------------------

    void setOffset(
        const glm::vec2& offset
    );

    void setScale(
        const glm::vec2& scale
    );

    void setRotation(
        float angle
    );



private:

    static constexpr const char* VERTEX_SHADER =
        "Shaders/caja_hdr.vert";

    static constexpr const char* FRAGMENT_SHADER =
        "Shaders/caja_hdr.frag";

};