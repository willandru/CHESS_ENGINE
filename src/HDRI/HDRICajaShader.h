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
    // SELECT FACE
    //------------------------------------------------

    void setFace(
        int face
    );



    //------------------------------------------------
    // PER FACE ROTATION
    //------------------------------------------------

    void setFaceRotationX(
        float value
    );


    void setFaceRotationY(
        float value
    );



    //------------------------------------------------
    // PER FACE ZOOM
    //------------------------------------------------

    void setFaceZoom(
        float value
    );



    //------------------------------------------------
    // PER FACE OFFSET
    //------------------------------------------------

    void setFaceOffsetU(
        float value
    );


    void setFaceOffsetV(
        float value
    );



private:


    static constexpr const char* VERTEX_SHADER =
        "Shaders/caja_hdr.vert";



    static constexpr const char* FRAGMENT_SHADER =
        "Shaders/caja_hdr.frag";


};