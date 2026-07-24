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
        "rotation",
        rotation
    );

}



//====================================================
// TEXTURE ROTATION
//====================================================

void HDRICajaShader::setTextureRotation(
    float rotation
)
{

    bind();


    setFloat(
        "textureRotation",
        rotation
    );

}



//====================================================
// TEXTURE ZOOM
//====================================================

void HDRICajaShader::setTextureZoom(
    float zoom
)
{

    bind();


    setFloat(
        "textureZoom",
        zoom
    );

}



//====================================================
// SELECTED FACE
//====================================================

void HDRICajaShader::setFace(
    int face
)
{

    bind();


    setInt(
        "selectedFace",
        face
    );

}