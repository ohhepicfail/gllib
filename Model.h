//
// Created by epicfail on 03.03.16.
//

#ifndef GLLIB_MODEL_H
#define GLLIB_MODEL_H

#include <vector>
#include "Vec3.h"

class Model
{
public:
    Model ();
    ~Model ();
    void open (char * filename);
private:
    std::vector <Vec3f> verts_;
    std::vector <Vec3i> faces_;
};


#endif //GLLIB_MODEL_H
