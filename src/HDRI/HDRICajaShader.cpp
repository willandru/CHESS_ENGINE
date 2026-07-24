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



//====================================================
// FACE ROTATION X
//====================================================

void HDRICajaShader::setFaceRotationX(
    float value
)
{

    bind();


    setFloat(
        "faceRotationX",
        value
    );

}



//====================================================
// FACE ROTATION Y
//====================================================

void HDRICajaShader::setFaceRotationY(
    float value
)
{

    bind();


    setFloat(
        "faceRotationY",
        value
    );

}



//====================================================
// FACE ZOOM
//====================================================

void HDRICajaShader::setFaceZoom(
    float value
)
{

    bind();


    setFloat(
        "faceZoom",
        value
    );

}



//====================================================
// FACE OFFSET U
//====================================================

void HDRICajaShader::setFaceOffsetU(
    float value
)
{

    bind();


    setFloat(
        "faceOffsetU",
        value
    );

}



//====================================================
// FACE OFFSET V
//====================================================

void HDRICajaShader::setFaceOffsetV(
    float value
)
{

    bind();


    setFloat(
        "faceOffsetV",
        value
    );

}