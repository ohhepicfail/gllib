//
// Created by epicfail on 03.03.16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <assert.h>
#include "Model.h"

Model::Model ():
    verts_ (0),
    faces_ (0),
    non_standard_ (false),
    shift_for_standard_ (1)
{
}


Model::Model (const Model & that)
{
    assert (("Ooooooh, nooooo! You use copy constructor Model::Model (const Model &)", 0));
}

void Model::operator = (const Model & that)
{
    assert (("Ooooooh, nooooo! You use Model::operator = (const Model & that)", 0));
}

Model::~Model ()
{

}

void Model::open (const char * filename)
{
    if (!filename)
        throw NULL_FILENAME;

    FILE * file = fopen (filename, "rb");
    if (!file)
        throw NULL_FILE;

    fseek (file, 0, SEEK_END);
    size_t fsize = (size_t) ftell (file);
    fseek (file, 0, SEEK_SET);

    char * obj = (char *) malloc (fsize * sizeof (char));
    if (!obj)
        throw NO_MEMORY_FOR_ALL_FILE;

    size_t fread_size = fread (obj, sizeof (char), fsize, file);
    if (fsize != fread_size)
        throw NO_ALL_FILE_WAS_READ;

    char * pobj = strtok (obj, "\n");
    if (!pobj)
        throw NO_MODEL_IN_FILE;

    while (pobj)
    {
        char str_to_cmp[3] = {*pobj, *(pobj + 1), '\0'};

        if (strcmp (str_to_cmp, "v ") == 0)
        {
            Vec3f vec;
            char trash = 0;

            sscanf (pobj, "%c%f%f%f", &trash, &vec.x_, &vec.y_, &vec.z_);

            test_standard (vec);

            verts_.push_back (vec);
        }
        else if (strcmp (str_to_cmp, "f ") == 0)
        {
            Vec3i vec;
            for (int i = 0; i < 3;)
            {
                if (*pobj == ' ')
                {
                    pobj++;
                    sscanf (pobj, "%d", &vec[i]);
                    i++;
                }
                else
                    pobj++;
            }
            faces_.push_back (vec);
        }

        pobj = strtok (NULL, "\n");
    }

    make_standard (verts_);

    if (nverts () == 0)
        throw NO_VERTS_IN_FILE;
    if (nfaces () == 0)
        throw NO_FACES_IN_FILE;
}

void Model::test_standard (const Vec3f & vec)
{
    //todo if all coordinates to small, i must correct it

    const size_t SHIFT = 2;
    if (std::abs (vec.x_) > 1 || std::abs (vec.y_) > 1 || std::abs (vec.z_) > 1)
    {
        non_standard_ = true;
        float x = std::abs (vec.x_);
        float y = std::abs (vec.y_);
        float z = std::abs (vec.z_);

        size_t del_counter = 1;
        while (x > 1.0 || y > 1.0 || z > 1.0)
        {
            x /= SHIFT;
            y /= SHIFT;
            z /= SHIFT;
            del_counter *= SHIFT;
        }
        if (del_counter > shift_for_standard_)
            shift_for_standard_ = del_counter;
    }
}


bool Model::is_non_standard ()
{
    return non_standard_;
}

void Model::make_standard (std::vector <Vec3f> & verts)
{
    if (is_non_standard ())
    {
        for (size_t i = 0; i < verts.size (); i++)
        {
            verts[i].x_ /= shift_for_standard_;
            verts[i].y_ /= shift_for_standard_;
            verts[i].z_ /= shift_for_standard_;
        }
    }
}

size_t Model::nfaces ()
{
    return faces_.size ();
}
size_t Model::nverts ()
{
    return verts_.size ();
}

Vec3f Model::vert (size_t i)
{
    if (i >= verts_.size ())
        throw (unsigned) TOO_HIGH_VERT_INDEX;
    return verts_[i];
}


Vec3i Model::face (size_t i)
{
    if (i >= faces_.size ())
        throw (unsigned) TOO_HIGH_FACE_INDEX;
    return faces_[i];
}