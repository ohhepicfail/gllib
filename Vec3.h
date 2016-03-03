//
// Created by epicfail on 03.03.16.
//

#ifndef GLLIB_VEC3_H
#define GLLIB_VEC3_H


typedef struct
{
    float x_;
    float y_;
    float z_;
} Vec3f;

class Vec3i
{
public:
    Vec3i ();
    ~Vec3i ();
    int value_[3];
    const int & operator [] (int i);
    Vec3i (const Vec3i & that);
    const int & at (int i);
private:
    const Vec3i & operator = (const Vec3i &);
};

#endif //GLLIB_VEC3_H
