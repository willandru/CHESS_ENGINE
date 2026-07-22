#version 330 core

out vec4 FragColor;

in vec3 WorldPos;

uniform sampler2D hdriMap;

uniform vec3 cameraPosition;

uniform float rotation;
uniform float hdriScaleX;
uniform float hdriScaleY;
uniform float horizonOffset;

const float PI = 3.14159265359;

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

void main()
{

    //------------------------------------------------
    // RAYO CAMARA -> PIXEL SUELO
    //------------------------------------------------

    vec3 ray =
        normalize(
            WorldPos -
            cameraPosition
        );

    //------------------------------------------------
    // INTERSECCION CON ESFERA HDRI
    //------------------------------------------------

    float radius = 20.0;

    vec3 oc =
        cameraPosition;

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

    float t =
        -b +
        sqrt(
            discriminant
        );

    vec3 spherePoint =
        cameraPosition +
        ray *
        t;

    //------------------------------------------------
    // DIRECCION HDRI EXACTA DEL DOMO
    //------------------------------------------------

    vec3 direction =
        normalize(
            spherePoint
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