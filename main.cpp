//epicfail@gmail.com

#include "tgaimage.h"
#include "glLib.h"
#include "Model.h"

#define eprint( error )         printf ("%s in file %s on line %d\n", #error, __FILE__ , __LINE__)

const TGAColor white = TGAColor (255, 255, 255, 255);
const TGAColor red   = TGAColor (255, 0,   0,   255);
const TGAColor green = TGAColor (0,   255, 0,   255);

const int width  = 10000;
const int height = 10000;

int main ()
{
    Model model;

    try
    {
        model.open ("obj/navigator.obj");
        model.choose_the_best_cood (width, height);
    }
    catch (Errors error)
    {
        if (error == NULL_FILENAME)
            eprint ("NULL_FILENAME");
        else if (error == NULL_FILE)
            eprint ("NULL_FILE");
        else if (error == NO_MEMORY_FOR_ALL_FILE)
            eprint ("NO_MEMORY_FOR_ALL_FILE");
        else if (error == NO_ALL_FILE_WAS_READ)
            eprint ("NO_ALL_FILE_WAS_READ");
        else if (error == NO_MODEL_IN_FILE)
            eprint ("NO_MODEL_IN_FILE");
        else if (error == NO_VERTS_IN_FILE)
            eprint ("NO_VERTS_IN_FILE");
        else if (error == NO_FACES_IN_FILE)
            eprint ("NO_FACES_IN_FILE");
        else if (error == ZERO_SIZE)
            eprint ("ZERO_SIZE");
        else
            eprint ("else");
        abort ();
    }

    TGAImage image(width, height, TGAImage::RGB);

    try
    {
        for (size_t i = 0; i < model.nfaces (); i++)
        {
            Vec3i face = model.face (i);
            for (size_t j = 0; j < 3; j++)
            {
                Vec3f v0, v1;
                try
                {
                    v0 = model.vert ((size_t) face[j] - 1);
                    v1 = model.vert ((size_t) face[(j + 1) % 3] - 1);
                }
                catch (Errors error)
                {
                    if (error == TOO_HIGH_VERT_INDEX)
                        eprint ("TOO_HIGH_VERT_INDEX");
                    else
                        eprint ("else");
                    abort ();
                }

                int x0 = (int) v0.x_;
                int y0 = (int) v0.y_;
                int x1 = (int) v1.x_;
                int y1 = (int) v1.y_;

                try
                {
                    glLib::line (x0, y0, x1, y1, image, green);
                }
                catch (Errors error)
                {
                    if (error == NEGATIVE_COORDINATE)
                        eprint ("NEGATIVE_COORDINATE");
                    if (error == TOO_BIG_COORDINATE)
                        eprint ("TOO_BIG_COORDINATE");
                    else
                        eprint ("else");
                    abort ();
                }
            }
        }
    }
    catch (unsigned error)
    {
        if (error == TOO_HIGH_FACE_INDEX)
            printf ("TOO_HIGH_FACE_INDEX\n");
        else if (error == TOO_HIGH_VERT_INDEX)
            printf ("TOO_HIGH_VERT_INDEX\n");
        else
            printf ("draw model. Strange error\n");
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}