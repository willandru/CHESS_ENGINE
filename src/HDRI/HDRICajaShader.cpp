#include "HDRICajaShader.h"



//====================================================
// CONSTRUCTOR
//====================================================

HDRICajaShader::HDRICajaShader()
{

}



//====================================================
// DESTRUCTOR
//====================================================

HDRICajaShader::~HDRICajaShader()
{

}



//====================================================
// INITIALIZE
//====================================================

bool HDRICajaShader::initialize()
{

    return load(
        VERTEX_SHADER,
        FRAGMENT_SHADER
    );

}



//====================================================
// HDRI SLOT
//====================================================

void HDRICajaShader::setHDRITextureSlot(
    int slot
)
{

    bind();

    setInt(
        "hdriMap",
        slot
    );

}



//====================================================
// EXPOSURE
//====================================================

void HDRICajaShader::setExposure(
    float exposure
)
{

    bind();

    setFloat(
        "exposure",
        exposure
    );

}



//====================================================
// OFFSET
//====================================================

void HDRICajaShader::setOffset(
    const glm::vec2& offset
)
{

    bind();

    setVec2(
        "uvOffset",
        offset
    );

}



//====================================================
// SCALE
//====================================================

void HDRICajaShader::setScale(
    const glm::vec2& scale
)
{

    bind();

    setVec2(
        "uvScale",
        scale
    );

}



//====================================================
// ROTATION
//====================================================

void HDRICajaShader::setRotation(
    float angle
)
{

    bind();

    setFloat(
        "uvRotation",
        angle
    );

}