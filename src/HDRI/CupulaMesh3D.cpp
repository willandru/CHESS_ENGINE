#include "CupulaMesh3D.h"

#include "CupulaConstants3D.h"

#include <cmath>


//====================================================
// CONSTRUCTOR
//====================================================

CupulaMesh3D::CupulaMesh3D()
{

}



//====================================================
// INITIALIZE PROFILE
//====================================================

void CupulaMesh3D::initialize()
{

    profile.clear();



    const float R =
        CupulaConstants3D::RADIUS;



    const float C =
        CupulaConstants3D::CURVE_RADIUS;



    //------------------------------------------------
    // FLOOR CENTER
    //------------------------------------------------

    profile.emplace_back(
        0.0f,
        0.0f
    );



    //------------------------------------------------
    // FLOOR EDGE
    //------------------------------------------------

    profile.emplace_back(
        R - C,
        0.0f
    );



    //------------------------------------------------
    // CURVED TRANSITION
    //------------------------------------------------

    for(uint32_t i = 1;
        i <= CupulaConstants3D::CURVE_SEGMENTS;
        ++i)
    {

        float t =
            static_cast<float>(i) /
            static_cast<float>(
                CupulaConstants3D::CURVE_SEGMENTS
            );



        float angle =
            t *
            CupulaConstants3D::PI *
            0.5f;



        float x =
            (R - C) +
            C *
            std::sin(angle);



        float y =
            C *
            (
                1.0f -
                std::cos(angle)
            );



        profile.emplace_back(
            x,
            y
        );

    }



    //------------------------------------------------
    // DOME
    //------------------------------------------------

    float centerY =
        C;



    for(uint32_t i = 1;
        i <= CupulaConstants3D::DOME_SEGMENTS;
        ++i)
    {

        float t =
            static_cast<float>(i) /
            static_cast<float>(
                CupulaConstants3D::DOME_SEGMENTS
            );



        float angle =
            t *
            CupulaConstants3D::PI *
            0.5f;



        float x =
            R *
            std::cos(angle);



        float y =
            centerY +
            R *
            std::sin(angle);



        profile.emplace_back(
            x,
            y
        );

    }

}



//====================================================
// GET PROFILE
//====================================================

const std::vector<glm::vec2>&
CupulaMesh3D::getProfile() const
{

    return profile;

}