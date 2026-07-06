#include "PromotionRenderer.h"

#include "Renderer.h"
#include "Shader.h"
#include "BoardView.h"

#include <iostream>

Texture PromotionRenderer::textures[8];

//====================================================
// INIT
//====================================================

bool PromotionRenderer::init()
{
    bool ok = true;

    ok &= textures[0].loadFromFile("Assets/dama_blanca.png");
    ok &= textures[1].loadFromFile("Assets/torre_blanca.png");
    ok &= textures[2].loadFromFile("Assets/alfil_blanco.png");
    ok &= textures[3].loadFromFile("Assets/caballo_blanco.png");

    ok &= textures[4].loadFromFile("Assets/dama_negra.png");
    ok &= textures[5].loadFromFile("Assets/torre_negra.png");
    ok &= textures[6].loadFromFile("Assets/alfil_negro.png");
    ok &= textures[7].loadFromFile("Assets/caballo_negro.png");

    if (!ok)
    {
        std::cerr << "[PromotionRenderer] ERROR loading textures\n";
    }

    return ok;
}

//====================================================
// SHUTDOWN
//====================================================

void PromotionRenderer::shutdown()
{
    for (int i = 0; i < 8; ++i)
        textures[i].destroy();
}

//====================================================
// RENDER
//====================================================

void PromotionRenderer::render(
    Shader& shader,
    bool whiteSide,
    const BoardView& view)
{
    float baseX = view.x + view.size + 20.0f;
    float baseY = view.y + view.size * 0.5f;

    float size = view.squareSize * optionSizeScale;
    float spacing = size + view.squareSize * spacingScale;

    static const int whiteMap[4] = {0, 1, 2, 3};
    static const int blackMap[4] = {4, 5, 6, 7};

    const int* map = whiteSide ? whiteMap : blackMap;

    for (int i = 0; i < 4; ++i)
    {
        float x = baseX;
        float y = baseY + i * spacing - 1.5f * spacing;

        Renderer::drawTextureRect(
            x,
            y,
            size,
            size,
            textures[map[i]],
            shader
        );
    }
}

//====================================================
// PICKING
//====================================================

uint8_t PromotionRenderer::pickOption(
    float mouseX,
    float mouseY,
    const BoardView& view)
{
    float baseX = view.x + view.size + 20.0f;
    float baseY = view.y + view.size * 0.5f;

    float size = view.squareSize * optionSizeScale;
    float spacing = size + view.squareSize * spacingScale;

    for (int i = 0; i < 4; ++i)
    {
        float x = baseX;
        float y = baseY + i * spacing - 1.5f * spacing;

        if (mouseX >= x &&
            mouseX <= x + size &&
            mouseY >= y &&
            mouseY <= y + size)
        {
            return static_cast<uint8_t>(i);
        }
    }

    return 255;
}