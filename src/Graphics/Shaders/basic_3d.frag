#version 330 core

in vec3 Color;
in vec2 TexCoord;

uniform bool useUniformColor;
uniform vec3 uniformColor;

uniform bool useTexture;
uniform sampler2D diffuseTexture;

out vec4 FragColor;

void main()
{
    vec3 finalColor =
        useUniformColor
        ? uniformColor
        : Color;

    if(useTexture)
    {
        finalColor *= texture(
            diffuseTexture,
            TexCoord
        ).rgb;
    }

    FragColor = vec4(
        finalColor,
        1.0
    );
}