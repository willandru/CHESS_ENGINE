#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>



class Shader3D
{
public:

    Shader3D();

    ~Shader3D();

    //------------------------------------------------
    // PROGRAM
    //------------------------------------------------

    bool load(
        const std::string& vertexPath,
        const std::string& fragmentPath
    );

    void bind() const;

    void unbind() const;

    unsigned int getID() const;

    //------------------------------------------------
    // UNIFORMS
    //------------------------------------------------

    void setBool(
        const std::string& name,
        bool value
    ) const;

    void setInt(
        const std::string& name,
        int value
    ) const;

    void setFloat(
        const std::string& name,
        float value
    ) const;

    void setVec2(
        const std::string& name,
        const glm::vec2& value
    ) const;

    void setVec3(
        const std::string& name,
        const glm::vec3& value
    ) const;

    void setVec4(
        const std::string& name,
        const glm::vec4& value
    ) const;

    void setMat3(
        const std::string& name,
        const glm::mat3& value
    ) const;

    void setMat4(
        const std::string& name,
        const glm::mat4& value
    ) const;

private:

    unsigned int programID = 0;

    mutable std::unordered_map<
        std::string,
        int
    > uniformLocations;

    std::string readFile(
        const std::string& path
    ) const;

    bool compileShader(
        unsigned int shader
    ) const;

    bool linkProgram(
        unsigned int program
    ) const;

    int getUniformLocation(
        const std::string& name
    ) const;
};