//epicfail@gmail.com

#include "tgaimage.h"
#include "glLib.h"
#include "Model.h"

const TGAColor white = TGAColor (255, 255, 255, 255);
const TGAColor red   = TGAColor (255, 0,   0,   255);
const TGAColor green = TGAColor (0,   255, 0,   255);

const int width  = 800;
const int height = 800;

int main ()
{
    Model model;
    try
    {
        model.open ("african_head.obj");
    }
    catch (...)
    {
        printf ("hoho\n");
    }

    TGAImage image(width, height, TGAImage::RGB);
    //image.set(52, 41, white);

    /*try
    {
        glLib::line (13, 41, 80, 51, image, white);
        glLib::line (20, 13, 40, 80, image, red);
        glLib::line (80, 40, 13, 20, image, green);
    }
    catch (...)
    {
        printf ("bad agruments in glLib::line ()\n");
    }*/

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
                glLib::line (x0, y0, x1, y1, image, white);
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