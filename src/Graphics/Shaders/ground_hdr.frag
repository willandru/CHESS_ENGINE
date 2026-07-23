#version 330 core

out vec4 FragColor;

in vec3 WorldPos;

uniform sampler2D hdriMap;

uniform float rotation;
uniform float hdriScaleX;
uniform float hdriScaleY;
uniform float horizonOffset;

// Altura desde la que fue tomada la HDRI
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



    //------------------------------------------------
    // SCALE
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
    // UV
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
    // HORIZON
    //------------------------------------------------

    v +=
        horizonOffset;



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
    // HDRI CAPTURE CAMERA
    //------------------------------------------------

    vec3 captureCamera =
        vec3(
            0.0,
            captureHeight,
            0.0
        );



    //------------------------------------------------
    // VIEW RAY
    //------------------------------------------------

    vec3 ray =
        normalize(
            WorldPos -
            captureCamera
        );



    //------------------------------------------------
    // DOME INTERSECTION
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
        ) -
        radius *
        radius;

    float discriminant =
        b * b -
        c;

    if(
        discriminant < 0.0
    )
    {
        FragColor =
            vec4(0.0);

        return;
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
    // SAMPLE HDRI
    //------------------------------------------------

    vec3 direction =
        normalize(
            spherePoint -
            domeCenter
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

    FragColor =
        vec4(
            color,
            1.0
        );

}