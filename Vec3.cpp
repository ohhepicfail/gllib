//
// Created by epicfail on 03.03.16.
//

#include "Vec3.h"
#include "Errors.h"

Vec3i::Vec3i ()
{
}

Vec3i::~Vec3i ()
{
    for (int i = 0; i < 3; i++)
        value_[i] = 0xBADF00D;
}

const int & Vec3i::operator [] (size_t i)
{
    if (i > 2)
        throw INDEX_OUT_OF_BOUNDS;
    return value_[i];
}

const Vec3i & Vec3i::operator = (const Vec3i & that)
{
    for (int i = 0; i < 3; i++)
        value_[i] = that.value_[i];
    return *this;
}

Vec3i::Vec3i (const Vec3i & that)
{
    for (int i = 0; i < 3; i++)
        value_[i] = that.value_[i];
}

const int & Vec3i::at (size_t i)
{
    if (i > 2)
        throw INDEX_OUT_OF_BOUNDS;
    return value_[i];
}


Vec3f::Vec3f ()
{
}

Vec3f::~Vec3f ()
{
    x_ = 0xBADF00D;
    y_ = 0xBADF00D;
    z_ = 0xBADF00D;
}

const float & Vec3f::operator [] (size_t i)
{
    if (i == 0)
        return x_;
    if (i == 1)
        return y_;
    if (i == 2)
        return z_;
    else
        throw INDEX_OUT_OF_BOUNDS;
}

const float & Vec3f::at (size_t i)
{
    if (i == 0)
        return x_;
    if (i == 1)
        return y_;
    if (i == 2)
        return z_;
    else
        throw INDEX_OUT_OF_BOUNDS;
}

Vec3f::Vec3f (const Vec3f & that)
{
    x_ = that.x_;
    y_ = that.y_;
    z_ = that.z_;
}

const Vec3f & Vec3f::operator = (const Vec3f & that)
{
    x_ = that.x_;
    y_ = that.y_;
    z_ = that.z_;

    return *this;
}