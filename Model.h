//
// Created by epicfail on 03.03.16.
//

#ifndef GLLIB_MODEL_H
#define GLLIB_MODEL_H

#include <vector>
#include "Vec3.h"
#include "Errors.h"


class Model
{
public:
    Model ();
    ~Model ();
    void   open (char * filename);
    size_t nfaces ();
    size_t nverts ();
    Vec3f  vert (size_t i);
    Vec3i  face (size_t i);
private:
    void test_standard (const Vec3f & vec);
    bool is_non_standard ();
    void make_standard (std::vector <Vec3f> & verts);
    bool non_standard_;
    size_t shift_for_standard_;
    std::vector <Vec3f> verts_;
    std::vector <Vec3i> faces_;
};


#endif //GLLIB_MODEL_H
