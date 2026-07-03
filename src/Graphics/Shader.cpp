#include "Shader.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader()
    : programID(0)
{
}

Shader::~Shader()
{
    if (programID != 0)
        glDeleteProgram(programID);
}

std::string Shader::readFile(const std::string& path) const
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "ERROR: Cannot open shader file:\n"
                  << path << std::endl;

        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

bool Shader::checkShader(unsigned int shader) const
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success)
        return true;

    char log[1024];

    glGetShaderInfoLog(
        shader,
        sizeof(log),
        nullptr,
        log);

    std::cerr
        << "Shader compilation failed:\n"
        << log
        << std::endl;

    return false;
}

bool Shader::checkProgram(unsigned int program) const
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (success)
        return true;

    char log[1024];

    glGetProgramInfoLog(
        program,
        sizeof(log),
        nullptr,
        log);

    std::cerr
        << "Shader link failed:\n"
        << log
        << std::endl;

    return false;
}

bool Shader::load(const std::string& vertexPath,
                  const std::string& fragmentPath)
{
    if (programID != 0)
    {
        glDeleteProgram(programID);
        programID = 0;
    }

    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);

    if (vertexSource.empty() || fragmentSource.empty())
        return false;

    const char* vertexCode = vertexSource.c_str();
    const char* fragmentCode = fragmentSource.c_str();

    unsigned int vertexShader =
        glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexCode,
        nullptr);

    glCompileShader(vertexShader);

    if (!checkShader(vertexShader))
    {
        glDeleteShader(vertexShader);
        return false;
    }

    unsigned int fragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentCode,
        nullptr);

    glCompileShader(fragmentShader);

    if (!checkShader(fragmentShader))
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

    return checkProgram(programID);
}

void Shader::bind() const
{
    glUseProgram(programID);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

unsigned int Shader::getID() const
{
    return programID;
}

void Shader::setInt(const std::string& name,
                    int value) const
{
    glUniform1i(
        glGetUniformLocation(programID, name.c_str()),
        value);
}

void Shader::setFloat(const std::string& name,
                      float value) const
{
    glUniform1f(
        glGetUniformLocation(programID, name.c_str()),
        value);
}

void Shader::setVec2(const std::string& name,
                     float x,
                     float y) const
{
    glUniform2f(
        glGetUniformLocation(programID, name.c_str()),
        x,
        y);
}

void Shader::setVec3(const std::string& name,
                     float x,
                     float y,
                     float z) const
{
    glUniform3f(
        glGetUniformLocation(programID, name.c_str()),
        x,
        y,
        z);
}

void Shader::setVec4(const std::string& name,
                     float x,
                     float y,
                     float z,
                     float w) const
{
    glUniform4f(
        glGetUniformLocation(programID, name.c_str()),
        x,
        y,
        z,
        w);
}