#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform vec4 uRect;

out vec2 TexCoord;

void main()
{
    // Quad unitario (0..1)
    vec2 pos = aPos;

    // Escalar al tamaño del rectángulo y trasladar
    pos = pos * uRect.zw + uRect.xy;

    // Convertir de píxeles a NDC
    vec2 ndc = pos / vec2(1280.0, 720.0);
    ndc = ndc * 2.0 - 1.0;

    // Invertir eje Y
    ndc.y = -ndc.y;

    gl_Position = vec4(
        ndc,
        0.0,
        1.0
    );

    TexCoord = aTexCoord;
}