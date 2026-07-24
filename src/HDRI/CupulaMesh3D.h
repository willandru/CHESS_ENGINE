#pragma once

#include <glm/glm.hpp>

#include <vector>


class CupulaMesh3D
{

public:

    //------------------------------------------------
    // CONSTRUCTOR
    //------------------------------------------------

    CupulaMesh3D();



    //------------------------------------------------
    // INITIALIZE 2D PROFILE
    //------------------------------------------------

    void initialize();



    //------------------------------------------------
    // ACCESS PROFILE
    //------------------------------------------------

    const std::vector<glm::vec2>&
    getProfile() const;



private:

    //------------------------------------------------
    // REVOLUTION PROFILE
    //
    // x = radius
    // y = height
    //
    //------------------------------------------------

    std::vector<glm::vec2> profile;

};