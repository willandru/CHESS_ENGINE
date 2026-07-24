#version 330 core


out vec4 FragColor;


in vec3 WorldPos;



uniform sampler2D hdriMap;


uniform float rotation;

uniform float hdriScaleX;

uniform float hdriScaleY;

uniform float horizonOffset;


uniform float exposure;


// Altura de la cámara donde fue capturada la HDRI
uniform float captureHeight;



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
    // EQUIRECTANGULAR
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
// HDRI CAPTURE PROJECTION
//====================================================

vec3 calculateHDRIDirection()
{

    //------------------------------------------------
    // HDRI CAMERA POSITION
    //------------------------------------------------

    vec3 captureCamera =
        vec3(
            0.0,
            captureHeight,
            0.0
        );



    //------------------------------------------------
    // RAY FROM CAPTURE CAMERA TO SURFACE
    //------------------------------------------------

    vec3 ray =
        normalize(
            WorldPos -
            captureCamera
        );



    //------------------------------------------------
    // HDRI SPHERE
    //------------------------------------------------

    const float radius =
        20.0;



    vec3 domeCenter =
        vec3(
            0.0,
            0.0,
            0.0
        );



    vec3 oc =
        captureCamera -
        domeCenter;



    float b =
        dot(
            oc,
            ray
        );


    float c =
        dot(
            oc,
            oc
        )
        -
        radius *
        radius;



    float discriminant =
        b * b -
        c;



    if(discriminant < 0.0)
    {

        return normalize(
            WorldPos
        );

    }



    float t =
        -b +
        sqrt(
            discriminant
        );



    vec3 spherePoint =
        captureCamera +
        ray *
        t;



    //------------------------------------------------
    // TRUE HDRI DIRECTION
    //------------------------------------------------

    return normalize(
        spherePoint -
        domeCenter
    );

}



//====================================================
// MAIN
//====================================================

void main()
{

    //------------------------------------------------
    // HDRI DIRECTION
    //------------------------------------------------

    vec3 direction =
        calculateHDRIDirection();



    //------------------------------------------------
    // UV
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



    color *= exposure;



    FragColor =
        vec4(
            color,
            1.0
        );

}