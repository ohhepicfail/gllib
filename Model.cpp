//
// Created by epicfail on 03.03.16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <assert.h>
#include "Model.h"
#include "Errors.h"


Model::Model ():
        verts_ (0),
        faces_ (0)
{
}


Model::Model (const Model & that)
{
    assert (("Ooooooh, nooooo! You use copy constructor Model::Model (const Model &)", &that, false));
}

void Model::operator = (const Model & that)
{
    assert (("Ooooooh, nooooo! You use Model::operator = (const Model & that)", &that, false));
}

Model::~Model ()
{

}

void Model::open (const char * filename)
{
    if (!filename)
        THROW (NULL_FILENAME);

    FILE * file = fopen (filename, "rb");
    if (!file)
        THROW (NULL_FILE);

    fseek (file, 0, SEEK_END);
    size_t fsize = (size_t) ftell (file);
    fseek (file, 0, SEEK_SET);

    char * obj = (char *) malloc (fsize * sizeof (char));
    if (!obj)
        THROW (NO_MEMORY_FOR_ALL_FILE);

    size_t fread_size = fread (obj, sizeof (char), fsize, file);
    if (fsize != fread_size)
        THROW (NO_ALL_FILE_WAS_READ);

    char * pobj = strtok (obj, "\n");
    if (!pobj)
        THROW (NO_MODEL_IN_FILE);

    while (pobj)
    {
        char str_to_cmp[3] = {*pobj, *(pobj + 1), '\0'};

        if (strcmp (str_to_cmp, "v ") == 0)
        {
            Vec3f vec;
            char trash = 0;

            sscanf (pobj, "%c%f%f%f", &trash, &vec.x_, &vec.y_, &vec.z_);

            verts_.push_back (vec);
        }
        else if (strcmp (str_to_cmp, "f ") == 0)
        {
            Vec3i vec;
            for (int i = 0; i < 3;)
            {
                if (*pobj == ' ')
                {
                    try
                    {
                        pobj++;
                        sscanf (pobj, "%d", &vec[i]);
                        i++;
                    }
                    catch (Error err)
                    {
                        err.print_error ();
                        exit (1);
                    }
                }
                else
                    pobj++;
            }
            faces_.push_back (vec);
        }

        pobj = strtok (NULL, "\n");
    }

    if (nverts () == 0)
        THROW (NO_VERTS_IN_FILE);
    if (nfaces () == 0)
        THROW (NO_FACES_IN_FILE);
}

size_t Model::nfaces ()
{
    return faces_.size ();
}

size_t Model::nverts ()
{
    return verts_.size ();
}

const Vec3f & Model::vert (size_t i)
{
    if (i >= verts_.size ())
        THROW (TOO_HIGH_VERT_INDEX);
    return verts_[i];
}

const Vec3i & Model::face (size_t i)
{
    if (i >= faces_.size ())
        THROW (TOO_HIGH_FACE_INDEX);
    return faces_[i];
}

void Model::choose_the_best_cood (size_t width, size_t height)
{
    if (!width || !height)
        THROW (ZERO_SIZE);

    float x_min = 0.0;      //left
    float x_max = 0.0;      //right
    float y_min = 0.0;      //bottom
    float y_max = 0.0;      //top

    for (size_t i = 0; i < nverts (); i++)
    {
        Vec3f v = vert (i);

        x_min = x_min < v.x_ ? x_min : v.x_;
        y_min = y_min < v.y_ ? y_min : v.y_;
        x_max = x_max > v.x_ ? x_max : v.x_;
        y_max = y_max > v.y_ ? y_max : v.y_;
    }

    if (!x_min || !x_max || !y_min || !y_max)
        WPRINT (ZERO_COORDINATE);

    float ratio_x = (float) std::min (std::abs (1.0 * width / x_min), std::abs (1.0 * width / x_max));
    float ratio_y = (float) std::min (std::abs (1.0 * height / y_min), std::abs (1.0 * height / y_max));
    float best_ratio = std::min (ratio_x, ratio_y);

    for (size_t i = 0; i < nverts (); i++)
    {
        verts_[i].x_ = (verts_[i].x_ * best_ratio + width) / 2;
        verts_[i].y_ = (verts_[i].y_ * best_ratio + height) / 2;
    }
}