#pragma once

#include "Shader3D.h"



class HDRICajaShader : public Shader3D
{

public:


    //------------------------------------------------
    // CONSTRUCTOR / DESTRUCTOR
    //------------------------------------------------

    HDRICajaShader();


    ~HDRICajaShader();



    //------------------------------------------------
    // INITIALIZATION
    //------------------------------------------------

    bool initialize();



    //------------------------------------------------
    // HDRI TEXTURE SLOT
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
    // TEXTURE TRANSFORM
    //------------------------------------------------

    void setTextureRotation(
        float rotation
    );



    void setTextureZoom(
        float zoom
    );



    //------------------------------------------------
    // SELECTED FACE
    //------------------------------------------------

    void setFace(
        int face
    );



private:


    static constexpr const char* VERTEX_SHADER =
        "Shaders/caja_hdr.vert";


    static constexpr const char* FRAGMENT_SHADER =
        "Shaders/caja_hdr.frag";

};