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
    std::vector <Vec3f> verts_;
    std::vector <Vec3i> faces_;
};


#endif //GLLIB_MODEL_H
