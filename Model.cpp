//
// Created by epicfail on 03.03.16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Model.h"


enum Errors
{
    NULL_FILENAME,
    NULL_FILE,
    NO_MEMORY_FOR_ALL_FILE,
    NO_ALL_FILE_WAS_READ,
    NO_MODEL_IN_FILE
};

Model::Model ():
    verts_ (0),
    faces_ (0)
{

}

Model::~Model ()
{

}

void Model::open (char * filename)
{
    if (!filename)
        throw NULL_FILENAME;

    FILE * file = fopen (filename, "rb");
    if (!file)
        throw NULL_FILE;

    fseek (file, 0, SEEK_END);
    size_t fsize = ftell (file);
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

    /*for (int i = 0; i < verts_.size (); i++)
        printf ("%f\t%f\t%f\n", verts_[i].x_, verts_[i].y_, verts_[i].z_);
    for (int i = 0; i < faces_.size (); i++)
        printf ("%d\t%d\t%d\n", faces_[i].at (0), faces_[i].at (1), faces_[i].at (2)); */

}