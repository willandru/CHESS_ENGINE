#version 330 core


//------------------------------------------------
// OUTPUT
//------------------------------------------------

out vec4 FragColor;



//------------------------------------------------
// INPUT
//------------------------------------------------

in vec3 WorldPos;



//------------------------------------------------
// HDRI
//------------------------------------------------

uniform sampler2D hdriMap;



//------------------------------------------------
// PARAMETERS
//------------------------------------------------

uniform float rotation;

uniform float exposure;


// Radio de la esfera HDRI virtual

uniform float domeRadius;


// Altura de captura

uniform float captureHeight;


// Ajuste vertical del horizonte

uniform float horizonOffset;



const float PI =
    3.14159265359;



//====================================================
// DIRECTION TO UV
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
    // SPHERICAL COORDINATES
    //------------------------------------------------

    float longitude =
        atan(
            direction.z,
            direction.x
        );


    float latitude =
        asin(
            clamp(
                direction.y,
                -1.0,
                1.0
            )
        );



    longitude +=
        rotation;



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



    v +=
        horizonOffset;



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
// PROJECT FROM CAPTURE CAMERA
//====================================================

vec3 calculateHDRIDirection()
{

    //------------------------------------------------
    // VIRTUAL CAMERA POSITION
    //------------------------------------------------

    vec3 captureCamera =
        vec3(
            0.0,
            captureHeight,
            0.0
        );



    //------------------------------------------------
    // RAY
    //------------------------------------------------

    vec3 ray =
        normalize(
            WorldPos -
            captureCamera
        );



    //------------------------------------------------
    // SPHERE INTERSECTION
    //------------------------------------------------

    vec3 sphereCenter =
        vec3(
            0.0,
            0.0,
            0.0
        );



    vec3 oc =
        captureCamera -
        sphereCenter;



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
        domeRadius *
        domeRadius;



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



    vec3 hitPoint =
        captureCamera +
        ray *
        t;



    //------------------------------------------------
    // TRUE SPHERE DIRECTION
    //------------------------------------------------

    return normalize(
        hitPoint -
        sphereCenter
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
    // SAMPLE
    //------------------------------------------------

    vec3 color =
        texture(
            hdriMap,
            uv
        ).rgb;



    color *=
        exposure;



    FragColor =
        vec4(
            color,
            1.0
        );

}