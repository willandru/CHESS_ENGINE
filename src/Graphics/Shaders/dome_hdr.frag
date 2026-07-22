#version 330 core


out vec4 FragColor;


in vec3 WorldPos;


uniform sampler2D hdriMap;


uniform float horizonOffset;

uniform float hdriScaleX;

uniform float hdriScaleY;

uniform float hdriZoom;

uniform float rotation;



const float PI = 3.14159265359;



vec2 directionToUV(
    vec3 direction
)
{


    //------------------------------------------------
    // NORMALIZAR RAYO
    //------------------------------------------------

    direction =
        normalize(direction);



    //------------------------------------------------
    // ESCALAMIENTO ESFERICO
    //------------------------------------------------

    direction.x *= hdriScaleX;

    direction.y *= hdriScaleY;



    //------------------------------------------------
    // ZOOM REAL
    //------------------------------------------------

    direction.x /= hdriZoom;

    direction.y /= hdriZoom;



    direction =
        normalize(direction);



    //------------------------------------------------
    // ROTACION HORIZONTAL
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



    //------------------------------------------------
    // AJUSTE HORIZONTE
    //------------------------------------------------

    v += horizonOffset;



    //------------------------------------------------
    // WRAP CORRECTO HDRI
    //------------------------------------------------

    u =
        mod(
            u,
            1.0
        );


    if(u < 0.0)
    {
        u += 1.0;
    }



    //------------------------------------------------
    // LIMITAR VERTICAL
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