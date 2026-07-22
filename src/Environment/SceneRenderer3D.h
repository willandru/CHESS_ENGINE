#pragma once


#include <memory>
#include <string>


#include "Renderer3D.h"
#include "Shader3D.h"
#include "Camera3D.h"

#include "Environment3D.h"



class SceneRenderer3D
{


public:


    SceneRenderer3D();



    bool initialize(
        const std::string& vertexShader,
        const std::string& fragmentShader
    );



    void update(
        Camera3D& camera,
        float dt
    );



    void render(
        Camera3D& camera,
        float aspectRatio
    );



    void setEnvironment(
        std::unique_ptr<Environment3D> environment
    );



private:


    Renderer3D renderer;


    Shader3D shader;



    std::unique_ptr<Environment3D> environment;

};