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