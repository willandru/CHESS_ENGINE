#version 330 core


out vec4 FragColor;


in vec3 WorldPos;



uniform sampler2D hdriMap;


uniform float rotation;

uniform float hdriScaleX;

uniform float hdriScaleY;

uniform float horizonOffset;


uniform float exposure;



const float PI =
    3.14159265359;



//====================================================
// DIRECTION TO EQUIRECTANGULAR UV
//====================================================

vec2 directionToUV(
    vec3 direction
)
{

    direction =
        normalize(
            direction
        );



    //------------------------------------------------
    // HDRI SCALE
    //------------------------------------------------

    direction.x *= hdriScaleX;

    direction.y *= hdriScaleY;



    direction =
        normalize(
            direction
        );



    //------------------------------------------------
    // SPHERICAL COORDINATES
    //------------------------------------------------

    float longitude =
        atan(
            direction.z,
            direction.x
        );



    float latitude =
        asin(
            direction.y
        );



    longitude += rotation;



    //------------------------------------------------
    // EQUIRECTANGULAR MAPPING
    //------------------------------------------------

    float u =
        0.5 +
        longitude /
        (2.0 * PI);



    float v =
        0.5 -
        latitude /
        PI;



    v += horizonOffset;



    //------------------------------------------------
    // WRAP
    //------------------------------------------------

    u =
        fract(
            u
        );


    v =
        clamp(
            v,
            0.001,
            0.999
        );



    return vec2(
        u,
        v
    );

}



//====================================================
// MAIN
//====================================================

void main()
{

    //------------------------------------------------
    // VIEW DIRECTION FROM CUPULA CENTER
    //------------------------------------------------

    vec3 direction =
        normalize(
            WorldPos
        );



    vec2 uv =
        directionToUV(
            direction
        );



    vec3 color =
        texture(
            hdriMap,
            uv
        ).rgb;



    color *= exposure;



    FragColor =
        vec4(
            color,
            1.0
        );

}