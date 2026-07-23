#include "HDRIGroundShader.h"

//====================================================
// CONSTRUCTOR
//====================================================

HDRIGroundShader::HDRIGroundShader()
{

}

//====================================================
// DESTRUCTOR
//====================================================

HDRIGroundShader::~HDRIGroundShader()
{

}

//====================================================
// INITIALIZATION
//====================================================

bool HDRIGroundShader::initialize()
{

    return load(
        VERTEX_SHADER,
        FRAGMENT_SHADER
    );

}

//====================================================
// HDRI TEXTURE
//====================================================

void HDRIGroundShader::setHDRITextureSlot(
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
// ROTATION
//====================================================

void HDRIGroundShader::setRotation(
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

void HDRIGroundShader::setScaleX(
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

void HDRIGroundShader::setScaleY(
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

void HDRIGroundShader::setHorizon(
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

void HDRIGroundShader::setVirtualCameraHeight(
    float height
)
{

    bind();

    setFloat(
        "virtualCameraHeight",
        height
    );

}

//====================================================
// PROJECTION DISTANCE
//====================================================

void HDRIGroundShader::setProjectionDistance(
    float distance
)
{

    bind();

    setFloat(
        "projectionDistance",
        distance
    );

}