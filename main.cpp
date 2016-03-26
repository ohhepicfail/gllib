//epicfail@gmail.com

#include <stdlib.h>
#include <limits>
#include "tgaimage.h"
#include "glLib.h"
#include "Model.h"

const TGAColor white = TGAColor (255, 255, 255, 255);
const TGAColor red   = TGAColor (255, 0,   0,   255);
const TGAColor green = TGAColor (0,   255, 0,   255);
const TGAColor blue  = TGAColor(0, 0, 255, 255);

const int width  = 10000;
const int height = 10000;

void draw_grid (const Model & model, TGAImage & image, const TGAColor & color);

int main ()
{
    Model model;

    try
    {
        model.open ("obj/african_head.obj");
        model.choose_the_best_cood (width, height);
    }
    catch (Error err)
    {
        err.print_error ();
        exit (1);
    }

    TGAImage image(width, height, TGAImage::RGB);

    //draw_grid (model, image, red);

    if ((float) width * height >= (float) std::numeric_limits<int>::max ())
        WPRINT (WBIG_SIZE);
    int * zbuffer = new int[width * height];
    if (!zbuffer)
        THROW (ZERO_POINTER);
    for (int i = width * height - 1; i >= 0; i--)
        zbuffer[i] = std::numeric_limits<int>::min ();

    for (int i=0; i<model.nfaces(); i++) {
        Vec3i face = model.face(i);
        Vec3i screen_coords[3];
        Vec3f world_coords[3];
        for (int j=0; j<3; j++)
        {
            world_coords[j] = model.vert (face[j] - 1);
            screen_coords[j] = Vec3i (world_coords[j].x_, world_coords[j].y_, world_coords[j].z_);
        }

        Vec3f triangle_norm = vector_product (world_coords[2] - world_coords[1], world_coords[2] - world_coords[0]);
        triangle_norm = normalize (triangle_norm);
        Vec3f light_dir (0.0, 0.0, -1.0);
        float intensity = scalar_product (triangle_norm, light_dir);

        if (intensity > 0)
        {
            int temp = std::abs ((int) (intensity * 255));
            glLib::triangle (screen_coords[0], screen_coords[1], screen_coords[2], image,
                             TGAColor (temp, temp, temp, 255), zbuffer);
        }
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");

    delete[] zbuffer;
    return 0;
}

void draw_grid (const Model & model , TGAImage & image, const TGAColor & color)
{
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

            Vec2i begin, end;
            begin.x_ = (int) v0.x_;
            begin.y_ = (int) v0.y_;
            end.x_ = (int) v1.x_;
            end.y_ = (int) v1.y_;

            try
            {
                glLib::line (begin, end, image, color);
            }
            catch (Error err)
            {
                err.print_error ();
                exit (1);
            }
        }
    }
}

