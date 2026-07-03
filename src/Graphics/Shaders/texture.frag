#version 330 core

in vec2 vUV;

uniform sampler2D uTexture;
uniform vec3 uColor;

out vec4 FragColor;

void main()
{
    FragColor = texture(uTexture, vUV);
}