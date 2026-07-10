#pragma once

#include "Mesh3D.h"
#include "Shader3D.h"
#include "Transform3D.h"
#include "Camera3D.h"

#include "Material3D.h"

#include <glm/glm.hpp>


class Renderer3D
{
public:

    Renderer3D();


    //------------------------------------------------
    // FRAME
    //------------------------------------------------

    void beginFrame(
        const glm::vec4& clearColor
    ) const;


    void endFrame() const;



    //------------------------------------------------
    // DRAW BASIC
    //------------------------------------------------

    void draw(
        const Mesh3D& mesh,
        const Transform3D& transform,
        const Shader3D& shader,
        const Camera3D& camera,
        float aspectRatio
    ) const;



    //------------------------------------------------
    // DRAW PIECE
    //------------------------------------------------

    void renderPiece(
        const Mesh3D& mesh,
        const Transform3D& transform,
        const Material3D& material,
        const Shader3D& shader,
        const Camera3D& camera,
        float aspectRatio
    ) const;



    //------------------------------------------------
    // OPTIONS
    //------------------------------------------------

    void enableDepthTest() const;

    void disableDepthTest() const;


    void enableFaceCulling() const;

    void disableFaceCulling() const;


    void setViewport(
        int width,
        int height
    ) const;

};