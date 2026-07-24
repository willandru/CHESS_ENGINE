#version 330 core


out vec4 FragColor;


in vec3 WorldPos;



uniform sampler2D hdriMap;


uniform float exposure;


uniform int selectedFace;



// controles individuales

uniform float faceRotationX;

uniform float faceRotationY;

uniform float faceZoom;

uniform float faceOffsetU;

uniform float faceOffsetV;



const float PI = 3.14159265359;



//====================================================
// ROTATE VECTOR
//====================================================

vec3 rotateX(
    vec3 v,
    float angle
)
{

    float c = cos(angle);

    float s = sin(angle);


    return vec3(
        v.x,
        v.y*c - v.z*s,
        v.y*s + v.z*c
    );

}



vec3 rotateY(
    vec3 v,
    float angle
)
{

    float c = cos(angle);

    float s = sin(angle);


    return vec3(
        v.x*c + v.z*s,
        v.y,
        -v.x*s + v.z*c
    );

}




//====================================================
// FACE NORMAL DIRECTION
//====================================================

vec3 getDirection()
{

    vec3 dir;



    // FLOOR

    if(selectedFace == 0)
    {

        dir =
        vec3(
            WorldPos.x,
            -1.0,
            WorldPos.z
        );

    }



    // CEILING

    else if(selectedFace == 1)
    {

        dir =
        vec3(
            WorldPos.x,
            1.0,
            WorldPos.z
        );

    }



    // FRONT

    else if(selectedFace == 2)
    {

        dir =
        vec3(
            WorldPos.x,
            WorldPos.y,
            1.0
        );

    }



    // BACK

    else if(selectedFace == 3)
    {

        dir =
        vec3(
            -WorldPos.x,
            WorldPos.y,
            -1.0
        );

    }



    // LEFT

    else if(selectedFace == 4)
    {

        dir =
        vec3(
            -1.0,
            WorldPos.y,
            WorldPos.z
        );

    }



    // RIGHT

    else
    {

        dir =
        vec3(
            1.0,
            WorldPos.y,
            WorldPos.z
        );

    }



    return normalize(dir);

}





//====================================================
// DIRECTION -> HDRI UV
//====================================================

vec2 directionToUV(
    vec3 dir
)
{

    dir =
        normalize(dir);



    float longitude =
        atan(
            dir.z,
            dir.x
        );



    float latitude =
        asin(
            dir.y
        );



    float u =
        0.5 +
        longitude /
        (2.0 * PI);



    float v =
        0.5 -
        latitude /
        PI;



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


    vec3 direction =
        getDirection();



    //------------------------------------------------
    // PER FACE ADJUSTMENT
    //------------------------------------------------

    direction =
        rotateX(
            direction,
            faceRotationX
        );


    direction =
        rotateY(
            direction,
            faceRotationY
        );



    //------------------------------------------------
    // HDRI UV
    //------------------------------------------------

    vec2 uv =
        directionToUV(
            direction
        );



    //------------------------------------------------
    // ZOOM AROUND CENTER
    //------------------------------------------------

    uv -= 0.5;


    uv *= faceZoom;


    uv.x += faceOffsetU;

    uv.y += faceOffsetV;


    uv += 0.5;



    //------------------------------------------------
    // SAMPLE
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