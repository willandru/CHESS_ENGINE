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
// HDRI TEXTURE SLOT
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
// EXPOSURE
//====================================================

void HDRIGroundShader::setExposure(
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
// ZOOM
//====================================================

void HDRIGroundShader::setZoom(
    float zoom
)
{

    bind();


    setFloat(
        "hdriZoom",
        zoom
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
// CAMERA POSITION
//====================================================

void HDRIGroundShader::setCameraPosition(
    const glm::vec3& position
)
{

    bind();


    setVec3(
        "cameraPosition",
        position
    );

}