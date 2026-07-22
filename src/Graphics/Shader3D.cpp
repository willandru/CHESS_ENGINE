#include "Shader3D.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>


Shader3D::Shader3D()
{
}

Shader3D::~Shader3D()
{
    if (programID != 0)
    {
        glDeleteProgram(programID);
    }
}

//====================================================
// PROGRAM
//====================================================

bool Shader3D::load(
    const std::string& vertexPath,
    const std::string& fragmentPath
)
{
    if (programID != 0)
    {
        glDeleteProgram(programID);
        programID = 0;
    }

    uniformLocations.clear();

    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);

    if (vertexSource.empty() || fragmentSource.empty())
    {
        return false;
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char* vertexCode = vertexSource.c_str();

    glShaderSource(
        vertexShader,
        1,
        &vertexCode,
        nullptr
    );

    glCompileShader(vertexShader);

    if (!compileShader(vertexShader))
    {
        glDeleteShader(vertexShader);
        return false;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragmentCode = fragmentSource.c_str();

    glShaderSource(
        fragmentShader,
        1,
        &fragmentCode,
        nullptr
    );

    glCompileShader(fragmentShader);

    if (!compileShader(fragmentShader))
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    programID = glCreateProgram();

    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);

    glLinkProgram(programID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (!linkProgram(programID))
    {
        glDeleteProgram(programID);
        programID = 0;
        return false;
    }

    return true;
}

void Shader3D::bind() const
{
    glUseProgram(programID);
}

void Shader3D::unbind() const
{
    glUseProgram(0);
}

unsigned int Shader3D::getID() const
{
    return programID;
}

//====================================================
// UNIFORMS
//====================================================

void Shader3D::setBool(
    const std::string& name,
    bool value
) const
{
    glUniform1i(
        getUniformLocation(name),
        value
    );
}

void Shader3D::setInt(
    const std::string& name,
    int value
) const
{
    glUniform1i(
        getUniformLocation(name),
        value
    );
}

void Shader3D::setFloat(
    const std::string& name,
    float value
) const
{

    int location =
        getUniformLocation(name);


    std::cout
        << "[UNIFORM FLOAT] "
        << name
        << " location="
        << location
        << " value="
        << value
        << std::endl;


    glUniform1f(
        location,
        value
    );

}

void Shader3D::setVec2(
    const std::string& name,
    const glm::vec2& value
) const
{
    glUniform2fv(
        getUniformLocation(name),
        1,
        glm::value_ptr(value)
    );
}

void Shader3D::setVec3(
    const std::string& name,
    const glm::vec3& value
) const
{
    glUniform3fv(
        getUniformLocation(name),
        1,
        glm::value_ptr(value)
    );
}

void Shader3D::setVec4(
    const std::string& name,
    const glm::vec4& value
) const
{
    glUniform4fv(
        getUniformLocation(name),
        1,
        glm::value_ptr(value)
    );
}

void Shader3D::setMat3(
    const std::string& name,
    const glm::mat3& value
) const
{
    glUniformMatrix3fv(
        getUniformLocation(name),
        1,
        GL_FALSE,
        glm::value_ptr(value)
    );
}

void Shader3D::setMat4(
    const std::string& name,
    const glm::mat4& value
) const
{
    glUniformMatrix4fv(
        getUniformLocation(name),
        1,
        GL_FALSE,
        glm::value_ptr(value)
    );
}

//====================================================
// PRIVATE
//====================================================

std::string Shader3D::readFile(
    const std::string& path
) const
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr
            << "Cannot open shader: "
            << path
            << std::endl;

        return "";
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

bool Shader3D::compileShader(
    unsigned int shader
) const
{
    GLint success = 0;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success
    );

    if (success)
    {
        return true;
    }

    char infoLog[1024];

    glGetShaderInfoLog(
        shader,
        sizeof(infoLog),
        nullptr,
        infoLog
    );

    std::cerr
        << "Shader compilation failed:\n"
        << infoLog
        << std::endl;

    return false;
}

bool Shader3D::linkProgram(
    unsigned int program
) const
{
    GLint success = 0;

    glGetProgramiv(
        program,
        GL_LINK_STATUS,
        &success
    );

    if (success)
    {
        return true;
    }

    char infoLog[1024];

    glGetProgramInfoLog(
        program,
        sizeof(infoLog),
        nullptr,
        infoLog
    );

    std::cerr
        << "Program link failed:\n"
        << infoLog
        << std::endl;

    return false;
}

int Shader3D::getUniformLocation(
    const std::string& name
) const
{
    auto it = uniformLocations.find(name);

    if (it != uniformLocations.end())
    {
        return it->second;
    }

    GLint location =
        glGetUniformLocation(
            programID,
            name.c_str()
        );

    uniformLocations[name] = location;

    return location;
}