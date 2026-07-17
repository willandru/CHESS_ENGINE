#include "Texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture::Texture()
{
}

Texture::~Texture()
{
    destroy();
}

bool Texture::loadFromFile(const std::string& path)
{
    destroy();

    stbi_set_flip_vertically_on_load(false);

    unsigned char* data =
        stbi_load(
            path.c_str(),
            &width,
            &height,
            &channels,
            0
        );

    if(!data)
    {
        std::cout
            << "[Texture] ERROR loading: "
            << path
            << std::endl;

        std::cout
            << "[Texture] stb_image says: "
            << stbi_failure_reason()
            << std::endl;

        loaded = false;
        return false;
    }

    std::cout
        << "[Texture] Loaded: "
        << path
        << " ("
        << width
        << "x"
        << height
        << ", channels="
        << channels
        << ")"
        << std::endl;

    GLenum format = GL_RGB;

    if(channels == 1)
        format = GL_RED;
    else if(channels == 3)
        format = GL_RGB;
    else if(channels == 4)
        format = GL_RGBA;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );

    stbi_image_free(data);

    loaded = true;
    return true;
}

void Texture::bind(unsigned int slot) const
{
    if(!loaded)
        return;

    glActiveTexture(
        GL_TEXTURE0 + slot
    );

    glBindTexture(
        GL_TEXTURE_2D,
        id
    );
}

void Texture::destroy()
{
    if(id != 0)
    {
        glDeleteTextures(
            1,
            &id
        );

        id = 0;
    }

    width = 0;
    height = 0;
    channels = 0;
    loaded = false;
}