#include "Renderer.h"
#include <glad/glad.h>

void Renderer::setClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Renderer::beginFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::endFrame()
{
    // Reservado para futuras extensiones.
}