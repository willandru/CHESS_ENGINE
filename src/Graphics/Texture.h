#pragma once

#include <string>

class Texture
{
public:
    Texture();
    ~Texture();

    bool loadFromFile(const std::string& path);
    void bind(unsigned int slot = 0) const;
    void destroy();


     unsigned int getId() const
    {
        return id;
    }

private:
    unsigned int id = 0;
    int width = 0, height = 0, channels = 0;
    bool loaded = false;
};