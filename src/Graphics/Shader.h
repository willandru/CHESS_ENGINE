#pragma once

#include <string>

class Shader
{
public:
    Shader();
    ~Shader();

    bool load(const std::string& vertexPath,
              const std::string& fragmentPath);

    void bind() const;
    void unbind() const;

    unsigned int getID() const;

    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;

private:
    unsigned int programID;

    std::string readFile(const std::string& path) const;
    bool checkShader(unsigned int shader) const;
    bool checkProgram(unsigned int program) const;
};