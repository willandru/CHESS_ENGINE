#version 330 core

out vec4 FragColor;

in vec3 WorldPos;


uniform sampler2D hdriMap;


//------------------------------------------------
// HDRI CONTROLS
//------------------------------------------------

uniform float rotation;

uniform float hdriScaleX;

uniform float hdriScaleY;

uniform float horizonOffset;


//------------------------------------------------
// VIRTUAL HDRI CAMERA
//------------------------------------------------

uniform float virtualCameraHeight;



const float PI = 3.14159265359;



//====================================================
// DIRECTION -> UV
//====================================================

vec2 directionToUV(
    vec3 direction
)
{

    //------------------------------------------------
    // NORMALIZE
    //------------------------------------------------

    direction =
        normalize(direction);



    //------------------------------------------------
    // HDRI SCALE
    //------------------------------------------------

    direction.x *=
        hdriScaleX;


    direction.y *=
        hdriScaleY;



    direction =
        normalize(direction);



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



    //------------------------------------------------
    // ROTATION
    //------------------------------------------------

    longitude +=
        rotation;



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
    // HORIZON OFFSET
    //------------------------------------------------

    v +=
        horizonOffset;



    //------------------------------------------------
    // WRAP
    //------------------------------------------------

    u =
        fract(
            u
        );



    //------------------------------------------------
    // LIMIT
    //------------------------------------------------

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
    // SAME VIRTUAL CAMERA AS DOME
    //------------------------------------------------

    vec3 virtualCamera =
        vec3(
            0.0,
            virtualCameraHeight,
            0.0
        );



    //------------------------------------------------
    // WORLD DIRECTION
    //------------------------------------------------

    vec3 direction =
        normalize(
            WorldPos -
            virtualCamera
        );



    //------------------------------------------------
    // HDRI UV
    //------------------------------------------------

    vec2 uv =
        directionToUV(
            direction
        );



    //------------------------------------------------
    // SAMPLE HDRI
    //------------------------------------------------

    vec3 color =
        texture(
            hdriMap,
            uv
        ).rgb;



    FragColor =
        vec4(
            color,
            1.0
        );

}