#version 330 core


out vec4 FragColor;


in vec3 WorldPos;


uniform sampler2D hdriMap;


uniform float horizonOffset;

uniform float hdriScale;

uniform float rotation;


const float PI = 3.14159265359;



vec2 directionToUV(
    vec3 direction
)
{

    direction =
        normalize(direction);



    float longitude =
        atan(
            direction.z,
            direction.x
        );


    float latitude =
        asin(
            direction.y
        );



    //------------------------------------------------
    // ROTATION
    //------------------------------------------------

    longitude += rotation;



    //------------------------------------------------
    // EQUIRECTANGULAR UV
    //------------------------------------------------

    float u =
        0.5 +
        longitude /
        (2.0 * PI);



    float v =
        0.5 -
        latitude /
        PI;



    //------------------------------------------------
    // SCALE LIKE BLENDER TEXTURE SCALE
    //------------------------------------------------

    v =
        0.5 +
        (v - 0.5)
        *
        hdriScale;



    //------------------------------------------------
    // VERTICAL OFFSET
    //------------------------------------------------

    v += horizonOffset;



    return vec2(
        u,
        v
    );

}



void main()
{


    vec3 direction =
        normalize(WorldPos);



    vec2 uv =
        directionToUV(
            direction
        );



    vec3 hdrColor =
        texture(
            hdriMap,
            uv
        ).rgb;



    FragColor =
        vec4(
            hdrColor,
            1.0
        );

}