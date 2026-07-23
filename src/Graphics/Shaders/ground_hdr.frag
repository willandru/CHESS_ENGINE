#version 330 core

out vec4 FragColor;

in vec3 WorldPos;

uniform sampler2D hdriMap;

uniform float rotation;
uniform float hdriScaleX;
uniform float hdriScaleY;
uniform float horizonOffset;

uniform float captureHeight;


const float PI = 3.14159265359;



//====================================================
// DIRECTION -> UV
//====================================================

vec2 directionToUV(
    vec3 direction
)
{

    direction =
        normalize(direction);



    direction.x *= hdriScaleX;
    direction.y *= hdriScaleY;



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



    longitude += rotation;



    float u =
        0.5 +
        longitude /
        (2.0 * PI);



    float v =
        0.5 -
        latitude /
        PI;



    v += horizonOffset;



    u =
        fract(u);


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
    // CAMERA OF THE HDRI CAPTURE
    //------------------------------------------------

    vec3 captureCamera =
        vec3(
            0.0,
            captureHeight,
            0.0
        );



    //------------------------------------------------
    // RAY FROM CAPTURE CAMERA
    //------------------------------------------------

    vec3 ray =
        normalize(
            WorldPos -
            captureCamera
        );



    //------------------------------------------------
    // GROUND PLANE INTERSECTION
    //
    // Plane:
    // y = 0
    //------------------------------------------------


    float t =
        -captureHeight /
        ray.y;



    if(t <= 0.0)
    {

        FragColor =
            vec4(
                0.0
            );

        return;

    }



    vec3 groundPoint =
        captureCamera +
        ray *
        t;



    //------------------------------------------------
    // DIRECTION THAT HDRI CAMERA SAW
    //------------------------------------------------

    vec3 direction =
        normalize(
            groundPoint -
            captureCamera
        );



    //------------------------------------------------
    // SAMPLE HDRI
    //------------------------------------------------

    vec2 uv =
        directionToUV(
            direction
        );



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