//
// Created by epicfail on 03.03.16.
//

#include "Vec3.h"

Vec3i::Vec3i ()
{
}

Vec3i::~Vec3i ()
{
}

const int & Vec3i::operator [] (int i)
{
    return value_[i];
}

Vec3i::Vec3i (const Vec3i & that)
{
    for (int i = 0; i < 3; i++)
        value_[i] = that.value_[i];
}

const int & Vec3i::at (int i)
{
    return value_[i];
}