#version 330 core

layout(location = 0) in vec2 aPos;

uniform vec4 uRect;
uniform vec2 uScreenSize;

void main()
{
    // Convierte el quad unitario (0..1) al rectángulo en píxeles
    vec2 pos = aPos * uRect.zw + uRect.xy;

    // Convierte de píxeles (origen arriba-izquierda) a NDC de OpenGL
    vec2 ndc;
    ndc.x = (pos.x / uScreenSize.x) * 2.0 - 1.0;
    ndc.y = 1.0 - (pos.y / uScreenSize.y) * 2.0;

    gl_Position = vec4(ndc, 0.0, 1.0);
}