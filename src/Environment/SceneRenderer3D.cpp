#include "SceneRenderer3D.h"



//====================================================
// CONSTRUCTOR
//====================================================

SceneRenderer3D::SceneRenderer3D()
{
}



//====================================================
// INITIALIZATION
//====================================================

bool SceneRenderer3D::initialize(
    const std::string& vertexShader,
    const std::string& fragmentShader
)
{

    //------------------------------------------------
    // LOAD SHADER
    //------------------------------------------------

    if(
        !shader.load(
            vertexShader,
            fragmentShader
        )
    )
    {
        return false;
    }



    //------------------------------------------------
    // OPENGL STATE
    //------------------------------------------------

    renderer.enableDepthTest();

    renderer.disableFaceCulling();



    return true;
}






//====================================================
// UPDATE
//====================================================

void SceneRenderer3D::update(
    float dt
)
{

    if(environment)
    {
        environment->update(
            dt
        );
    }

}






//====================================================
// RENDER
//====================================================

void SceneRenderer3D::render(
    Camera3D& camera,
    float aspectRatio
)
{

    if(!environment)
    {
        return;
    }



    //------------------------------------------------
    // ROOM GEOMETRY
    //------------------------------------------------

    environment->renderBackground(
        renderer,
        shader,
        camera,
        aspectRatio
    );



    //------------------------------------------------
    // OBJECTS
    //------------------------------------------------

    environment->renderObjects(
        renderer,
        shader,
        camera,
        aspectRatio
    );

}






//====================================================
// ENVIRONMENT
//====================================================

void SceneRenderer3D::setEnvironment(
    std::unique_ptr<Environment3D> env
)
{

    environment =
        std::move(env);



    if(environment)
    {

        environment->initialize();

    }

}