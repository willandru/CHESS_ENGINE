#version 330 core

layout(location = 0) in vec2 aPos;

uniform vec4 uRect;
uniform vec2 uScreenSize;

out vec2 vUV;

void main()
{
    vec2 pos = aPos * uRect.zw + uRect.xy;

    vec2 ndc = pos / uScreenSize;
    ndc = ndc * 2.0 - 1.0;
    ndc.y = -ndc.y;

    vUV = aPos;

    gl_Position = vec4(ndc, 0.0, 1.0);
}