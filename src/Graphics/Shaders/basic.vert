#version 330 core

layout(location = 0) in vec2 aPos;

uniform vec4 uRect;

void main()
{
    vec2 pos = aPos;

    pos = pos * uRect.zw + uRect.xy;

    // convertir de pixeles a NDC
    vec2 ndc = pos / vec2(1280.0, 720.0) * 2.0 - 1.0;
    ndc.y = -ndc.y;

    gl_Position = vec4(ndc, 0.0, 1.0);
}