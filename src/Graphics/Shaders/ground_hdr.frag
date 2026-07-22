#version 330 core


out vec4 FragColor;


in vec3 WorldPos;



uniform sampler2D hdriMap;



// Posición real de la cámara en mundo

uniform vec3 cameraPosition;



// Controles HDRI compartidos con el domo

uniform float rotation;

uniform float hdriScaleX;

uniform float hdriScaleY;

uniform float hdriZoom;

uniform float horizonOffset;



const float PI = 3.14159265359;



//====================================================
// DIRECCION HDRI -> UV EQUIRECTANGULAR
//====================================================

vec2 directionToUV(
    vec3 direction
)
{


    direction =
        normalize(direction);



    //------------------------------------------------
    // MISMAS TRANSFORMACIONES QUE EL DOMO
    //------------------------------------------------

    direction.x *= hdriScaleX;

    direction.y *= hdriScaleY;



    direction /= hdriZoom;



    direction =
        normalize(direction);



    //------------------------------------------------
    // ESFERICA
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



    //------------------------------------------------
    // AJUSTE HORIZONTE
    //------------------------------------------------

    v += horizonOffset;



    //------------------------------------------------
    // WRAP
    //------------------------------------------------

    u =
        fract(u);



    //------------------------------------------------
    // LIMITE VERTICAL
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
    // RAYO DESDE LA CAMARA
    // HACIA EL FRAGMENTO DEL DISCO
    //------------------------------------------------

    vec3 rayDirection =
        normalize(
            WorldPos -
            cameraPosition
        );



    //------------------------------------------------
    // PLANO DEL SUELO
    //------------------------------------------------

    float groundHeight = 0.0;



    float distanceToGround =
        (
            groundHeight -
            cameraPosition.y
        )
        /
        rayDirection.y;



    //------------------------------------------------
    // PUNTO REAL DE IMPACTO
    //------------------------------------------------

    vec3 hitPoint =
        cameraPosition +
        rayDirection *
        distanceToGround;



    //------------------------------------------------
    // DIRECCION HDRI
    //
    // IMPORTANTE:
    // NO usar hitPoint como direccion
    //------------------------------------------------

    vec3 hdriDirection =
        normalize(
            hitPoint -
            cameraPosition
        );



    vec2 uv =
        directionToUV(
            hdriDirection
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