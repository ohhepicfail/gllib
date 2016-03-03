//epicfail@gmail.com

#include "tgaimage.h"
#include "glLib.h"
#include "Model.h"

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
    }
    catch (...)
    {
        printf ("Can't open the model\n");
    }

    TGAImage image(width, height, TGAImage::RGB);

    try
    {
        for (size_t i = 0; i < model.nfaces (); i++)
        {
            Vec3i face = model.face (i);
            for (size_t j = 0; j < 3; j++)
            {
                Vec3f v0 = model.vert ((size_t) face[j] - 1);
                Vec3f v1 = model.vert ((size_t) face[(j + 1) % 3] - 1);
                int x0 = (v0.x_ + 1.) * width / 2.;
                int y0 = (v0.y_ + 1.) * height / 2.;
                int x1 = (v1.x_ + 1.) * width / 2.;
                int y1 = (v1.y_ + 1.) * height / 2.;
                //printf ("j = %lu\t X %d\t%d\n", j,  x0, x1);
                //printf ("j = %lu\t Y %d\t%d\n", j,  y0, y1);
                glLib::line (x0, y0, x1, y1, image, white);
            }
            //printf ("\n");
            //image.flip_vertically();
            //image.write_tga_file("output.tga");
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