#include "Texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() {}

Texture::~Texture()
{
    destroy();
}

bool Texture::loadFromFile(const std::string& path)
{
    destroy();

    unsigned char* data = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        4
    );

    if (!data)
        return false;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    stbi_image_free(data);
    loaded = true;
    return true;
}

void Texture::bind(unsigned int slot) const
{
    if (!loaded) return;

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::destroy()
{
    if (id)
    {
        glDeleteTextures(1, &id);
        id = 0;
    }
    loaded = false;
}