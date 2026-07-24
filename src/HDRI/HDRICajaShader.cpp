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
// HDRI TEXTURE SLOT
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
// ROTATION
//====================================================

void HDRICajaShader::setRotation(
    float rotation
)
{

    bind();


    setFloat(

        "hdriRotation",

        rotation

    );

}