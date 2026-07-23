#include "HDRIDomeShader.h"

//====================================================
// CONSTRUCTOR
//====================================================

HDRIDomeShader::HDRIDomeShader()
{

}

//====================================================
// DESTRUCTOR
//====================================================

HDRIDomeShader::~HDRIDomeShader()
{

}

//====================================================
// INITIALIZATION
//====================================================

bool HDRIDomeShader::initialize()
{

    return load(
        VERTEX_SHADER,
        FRAGMENT_SHADER
    );

}

//====================================================
// HDRI TEXTURE SLOT
//====================================================

void HDRIDomeShader::setHDRITextureSlot(
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

void HDRIDomeShader::setExposure(
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
// ROTATION
//====================================================

void HDRIDomeShader::setRotation(
    float rotation
)
{

    bind();

    setFloat(
        "rotation",
        rotation
    );

}

//====================================================
// SCALE X
//====================================================

void HDRIDomeShader::setScaleX(
    float scaleX
)
{

    bind();

    setFloat(
        "hdriScaleX",
        scaleX
    );

}

//====================================================
// SCALE Y
//====================================================

void HDRIDomeShader::setScaleY(
    float scaleY
)
{

    bind();

    setFloat(
        "hdriScaleY",
        scaleY
    );

}

//====================================================
// HORIZON
//====================================================

void HDRIDomeShader::setHorizon(
    float horizon
)
{

    bind();

    setFloat(
        "horizonOffset",
        horizon
    );

}

//====================================================
// VIRTUAL CAMERA HEIGHT
//====================================================

void HDRIDomeShader::setVirtualCameraHeight(
    float height
)
{

    bind();

    setFloat(
        "virtualCameraHeight",
        height
    );

}