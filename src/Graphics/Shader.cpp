#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() : programID(0) {}

Shader::~Shader()
{
    if (programID)
        glDeleteProgram(programID);
}

std::string Shader::readFile(const std::string& path) const
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Cannot open shader: " << path << std::endl;
        return "";
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

bool Shader::load(const std::string& v, const std::string& f)
{
    if (programID)
        glDeleteProgram(programID);

    std::string vs = readFile(v);
    std::string fs = readFile(f);

    const char* vsrc = vs.c_str();
    const char* fsrc = fs.c_str();

    unsigned int vsh = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsh, 1, &vsrc, nullptr);
    glCompileShader(vsh);

    unsigned int fsh = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsh, 1, &fsrc, nullptr);
    glCompileShader(fsh);

    programID = glCreateProgram();
    glAttachShader(programID, vsh);
    glAttachShader(programID, fsh);
    glLinkProgram(programID);

    glDeleteShader(vsh);
    glDeleteShader(fsh);

    return true;
}

void Shader::bind() const { glUseProgram(programID); }
void Shader::unbind() const { glUseProgram(0); }
unsigned int Shader::getID() const { return programID; }

void Shader::setInt(const std::string& n, int v) const
{
    glUniform1i(glGetUniformLocation(programID, n.c_str()), v);
}

void Shader::setFloat(const std::string& n, float v) const
{
    glUniform1f(glGetUniformLocation(programID, n.c_str()), v);
}

void Shader::setVec2(const std::string& n, float x, float y) const
{
    glUniform2f(glGetUniformLocation(programID, n.c_str()), x, y);
}

void Shader::setVec3(const std::string& n, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(programID, n.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& n, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(programID, n.c_str()), x, y, z, w);
}