#include "HDRICupulaShader.h"


//====================================================
// CONSTRUCTOR
//====================================================

HDRICupulaShader::HDRICupulaShader()
{

}



//====================================================
// DESTRUCTOR
//====================================================

HDRICupulaShader::~HDRICupulaShader()
{

}



//====================================================
// INITIALIZE
//====================================================

bool HDRICupulaShader::initialize()
{

    return load(
        VERTEX_SHADER,
        FRAGMENT_SHADER
    );

}



//====================================================
// HDRI TEXTURE SLOT
//====================================================

void HDRICupulaShader::setHDRITextureSlot(
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

void HDRICupulaShader::setExposure(
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

void HDRICupulaShader::setRotation(
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

void HDRICupulaShader::setScaleX(
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

void HDRICupulaShader::setScaleY(
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

void HDRICupulaShader::setHorizon(
    float horizon
)
{

    bind();


    setFloat(
        "horizonOffset",
        horizon
    );

}