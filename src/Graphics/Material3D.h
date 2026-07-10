#pragma once

#include <glm/glm.hpp>


class Material3D
{
public:

    Material3D();


    //------------------------------------------------
    // COLOR
    //------------------------------------------------

    void setColor(
        const glm::vec3& value
    );


    const glm::vec3& getColor() const;



private:

    glm::vec3 color;

};