#pragma once


#include "Shader3D.h"



class HDRICupulaShader : public Shader3D
{

public:


    HDRICupulaShader();


    ~HDRICupulaShader();



    //------------------------------------------------
    // INITIALIZATION
    //------------------------------------------------

    bool initialize();



    //------------------------------------------------
    // HDRI TEXTURE
    //------------------------------------------------

    void setHDRITextureSlot(
        int slot
    );



    //------------------------------------------------
    // EXPOSURE
    //------------------------------------------------

    void setExposure(
        float exposure
    );



    //------------------------------------------------
    // ROTATION
    //------------------------------------------------

    void setRotation(
        float rotation
    );



    //------------------------------------------------
    // SCALE
    //------------------------------------------------

    void setScaleX(
        float scaleX
    );


    void setScaleY(
        float scaleY
    );



    //------------------------------------------------
    // HORIZON OFFSET
    //------------------------------------------------

    void setHorizon(
        float horizon
    );



private:


    static constexpr const char* VERTEX_SHADER =
        "Shaders/cupula_hdr.vert";


    static constexpr const char* FRAGMENT_SHADER =
        "Shaders/cupula_hdr.frag";


};