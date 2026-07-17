#pragma once

#include "EnvironmentObject3D.h"

class Table3D : public EnvironmentObject3D
{
public:

    Table3D();

    //------------------------------------------------
    // INITIALIZATION
    //------------------------------------------------

    bool load() override;

};