#pragma once

#include "EnvironmentObject3D.h"


class Chair3D : public EnvironmentObject3D
{

public:

    Chair3D();


    bool load() override;

};