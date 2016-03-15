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
        model.open ("obj/statue_head.obj");
        model.choose_the_best_cood (width, height);
    }
    catch (Error err)
    {
        err.print_error ();
        exit (1);
    }

    TGAImage image(width, height, TGAImage::RGB);

    for (size_t i = 0; i < model.nfaces (); i++)
    {
        Vec3i face;
        try
        {
            face = model.face (i);
        }
        catch (Error err)
        {
            err.print_error ();
            exit (1);
        }
        for (size_t j = 0; j < 3; j++)
        {
            Vec3f v0, v1;
            try
            {
                v0 = model.vert ((size_t) face[j] - 1);
                v1 = model.vert ((size_t) face[(j + 1) % 3] - 1);
            }
            catch (Error err)
            {
                err.print_error ();
                exit (1);
            }

            int x0 = (int) v0.x_;
            int y0 = (int) v0.y_;
            int x1 = (int) v1.x_;
            int y1 = (int) v1.y_;

            try
            {
                glLib::line (x0, y0, x1, y1, image, green);
            }
            catch (Error err)
            {
                err.print_error ();
                exit (1);
            }
        }
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}