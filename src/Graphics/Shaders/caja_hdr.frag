#version 330 core


out vec4 FragColor;


in vec3 WorldPos;



uniform sampler2D hdriMap;


uniform float rotation;


uniform float textureRotation;


uniform float textureZoom;


uniform float exposure;


uniform int selectedFace;



const float PI =
    3.14159265359;



//====================================================
// GET FACE DIRECTION
//====================================================

vec3 getFaceDirection()
{

    vec3 direction;



    //------------------------------------------------
    // FLOOR
    //------------------------------------------------

    if(selectedFace == 0)
    {

        direction =
        vec3(
            WorldPos.x,
            -1.0,
            WorldPos.z
        );

    }



    //------------------------------------------------
    // CEILING
    //------------------------------------------------

    else if(selectedFace == 1)
    {

        direction =
        vec3(
            WorldPos.x,
            1.0,
            WorldPos.z
        );

    }



    //------------------------------------------------
    // FRONT (+Z)
    //------------------------------------------------

    else if(selectedFace == 2)
    {

        direction =
        vec3(
            WorldPos.x,
            WorldPos.y,
            1.0
        );

    }



    //------------------------------------------------
    // BACK (-Z)
    //------------------------------------------------

    else if(selectedFace == 3)
    {

        direction =
        vec3(
            -WorldPos.x,
            WorldPos.y,
            -1.0
        );

    }



    //------------------------------------------------
    // LEFT (-X)
    //------------------------------------------------

    else if(selectedFace == 4)
    {

        direction =
        vec3(
            -1.0,
            WorldPos.y,
            -WorldPos.z
        );

    }



    //------------------------------------------------
    // RIGHT (+X)
    //------------------------------------------------

    else
    {

        direction =
        vec3(
            1.0,
            WorldPos.y,
            WorldPos.z
        );

    }



    return normalize(direction);

}





//====================================================
// DIRECTION TO HDRI UV
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
    // GLOBAL ROTATION
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



    vec2 uv =
    {
        u,
        v
    };



    //------------------------------------------------
    // FACE TEXTURE ROTATION
    //------------------------------------------------

    uv -= 0.5;



    float cs =
        cos(
            textureRotation
        );


    float sn =
        sin(
            textureRotation
        );



    uv =
        mat2(
            cs,
            -sn,
            sn,
            cs
        )
        *
        uv;



    //------------------------------------------------
    // FACE TEXTURE ZOOM
    //------------------------------------------------

    uv *=
        textureZoom;



    uv +=
        0.5;



    //------------------------------------------------
    // WRAP
    //------------------------------------------------

    uv.x =
        fract(
            uv.x
        );


    uv.y =
        clamp(
            uv.y,
            0.001,
            0.999
        );



    return uv;

}





//====================================================
// MAIN
//====================================================

void main()
{

    //------------------------------------------------
    // FACE PROJECTION
    //------------------------------------------------

    vec3 direction =
        getFaceDirection();



    //------------------------------------------------
    // HDRI UV
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