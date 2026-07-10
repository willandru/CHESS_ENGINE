#version 330 core

in vec3 Color;

uniform bool useUniformColor;
uniform vec3 uniformColor;

out vec4 FragColor;

void main()
{
    vec3 finalColor =
        useUniformColor
        ? uniformColor
        : Color;

    FragColor = vec4(finalColor, 1.0);
}