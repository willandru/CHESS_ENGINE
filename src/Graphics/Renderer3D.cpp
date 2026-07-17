#include "Renderer3D.h"

#include <glad/glad.h>


Renderer3D::Renderer3D()
{
}



//====================================================
// FRAME
//====================================================

void Renderer3D::beginFrame(
    const glm::vec4& clearColor
) const
{

    glClearColor(
        clearColor.r,
        clearColor.g,
        clearColor.b,
        clearColor.a
    );


    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

}



void Renderer3D::endFrame() const
{

}



//====================================================
// BASIC DRAW
//====================================================

void Renderer3D::draw(
    const Mesh3D& mesh,
    const Transform3D& transform,
    const Shader3D& shader,
    const Camera3D& camera,
    float aspectRatio
) const
{

    shader.bind();


    shader.setMat4(
        "model",
        transform.getModelMatrix()
    );


    shader.setMat4(
        "view",
        camera.getViewMatrix()
    );


    shader.setMat4(
        "projection",
        camera.getProjectionMatrix(
            aspectRatio
        )
    );


    mesh.draw();


    shader.unbind();

}



//====================================================
// DRAW COLORED
//====================================================

void Renderer3D::drawColored(
    const Mesh3D& mesh,
    const Transform3D& transform,
    const Shader3D& shader,
    const Camera3D& camera,
    float aspectRatio,
    const glm::vec3& color
) const
{

    shader.bind();


    shader.setBool(
        "useUniformColor",
        true
    );


    shader.setVec3(
        "uniformColor",
        color
    );


    shader.setMat4(
        "model",
        transform.getModelMatrix()
    );


    shader.setMat4(
        "view",
        camera.getViewMatrix()
    );


    shader.setMat4(
        "projection",
        camera.getProjectionMatrix(
            aspectRatio
        )
    );


    mesh.draw();


    shader.setBool(
        "useUniformColor",
        false
    );


    shader.unbind();

}



//====================================================
// CHESS PIECE
//====================================================

void Renderer3D::renderPiece(
    const Mesh3D& mesh,
    const Transform3D& transform,
    const Material3D& material,
    const Shader3D& shader,
    const Camera3D& camera,
    float aspectRatio
) const
{

    shader.bind();


    shader.setMat4(
        "model",
        transform.getModelMatrix()
    );


    shader.setMat4(
        "view",
        camera.getViewMatrix()
    );


    shader.setMat4(
        "projection",
        camera.getProjectionMatrix(
            aspectRatio
        )
    );


    shader.setVec3(
        "materialColor",
        material.getColor()
    );


    mesh.draw();


    shader.unbind();

}



//====================================================
// ENVIRONMENT OBJECT
//====================================================

//====================================================
// ENVIRONMENT OBJECT
//====================================================

void Renderer3D::renderObject(
    const Mesh3D& mesh,
    const Transform3D& transform,
    const Material3D& material,
    const Shader3D& shader,
    const Camera3D& camera,
    float aspectRatio
) const
{

    shader.bind();


    //------------------------------------------------
    // MATRICES
    //------------------------------------------------

    shader.setMat4(
        "model",
        transform.getModelMatrix()
    );

    shader.setMat4(
        "view",
        camera.getViewMatrix()
    );

    shader.setMat4(
        "projection",
        camera.getProjectionMatrix(
            aspectRatio
        )
    );


    //------------------------------------------------
    // MATERIAL
    //------------------------------------------------

    shader.setVec3(
        "materialColor",
        material.getColor()
    );


    if(material.hasTexture())
    {

        shader.setBool(
            "useTexture",
            true
        );

        material
            .getTexture()
            ->bind(0);

        shader.setInt(
            "diffuseTexture",
            0
        );

    }
    else
    {

        shader.setBool(
            "useTexture",
            false
        );

    }


    //------------------------------------------------
    // DRAW
    //------------------------------------------------

    mesh.draw();

    shader.unbind();

}

//====================================================
// ENVIRONMENT WALL
//====================================================

void Renderer3D::renderWall(
    const Mesh3D& mesh,
    const Transform3D& transform,
    const glm::vec3& color,
    const Shader3D& shader,
    const Camera3D& camera,
    float aspectRatio
) const
{

    shader.bind();


    shader.setMat4(
        "model",
        transform.getModelMatrix()
    );


    shader.setMat4(
        "view",
        camera.getViewMatrix()
    );


    shader.setMat4(
        "projection",
        camera.getProjectionMatrix(
            aspectRatio
        )
    );


    shader.setVec3(
        "uniformColor",
        color
    );


    mesh.draw();


    shader.unbind();

}



//====================================================
// OPENGL OPTIONS
//====================================================

void Renderer3D::enableDepthTest() const
{
    glEnable(
        GL_DEPTH_TEST
    );
}



void Renderer3D::disableDepthTest() const
{
    glDisable(
        GL_DEPTH_TEST
    );
}



void Renderer3D::enableFaceCulling() const
{

    glEnable(
        GL_CULL_FACE
    );


    glCullFace(
        GL_BACK
    );


    glFrontFace(
        GL_CCW
    );

}



void Renderer3D::disableFaceCulling() const
{
    glDisable(
        GL_CULL_FACE
    );
}



void Renderer3D::setViewport(
    int width,
    int height
) const
{

    glViewport(
        0,
        0,
        width,
        height
    );

}