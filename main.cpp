//epicfail@gmail.com

#include <stdlib.h>
#include "tgaimage.h"
#include "glLib.h"
#include "Model.h"

const TGAColor white = TGAColor (255, 255, 255, 255);
const TGAColor red   = TGAColor (255, 0,   0,   255);
const TGAColor green = TGAColor (0,   255, 0,   255);

const int width  = 10000;
const int height = 10000;

void draw_grid (const Model & model, TGAImage & image, const TGAColor & color);

int main ()
{
    Model model;

    try
    {
        model.open ("obj/Avent.obj");
        model.choose_the_best_cood (width, height);
    }
    catch (Error err)
    {
        err.print_error ();
        exit (1);
    }

    TGAImage image(width, height, TGAImage::RGB);

    //draw_grid (model, image, red);

    for (int i=0; i<model.nfaces(); i++) {
        Vec3i face = model.face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j=0; j<3; j++)
        {
            world_coords[j] = model.vert (face[j] - 1);
            screen_coords[j] = Vec2i (world_coords[j].x_, world_coords[j].y_);
        }

        Vec3f triangle_norm = vector_product (world_coords[2] - world_coords[1], world_coords[2] - world_coords[0]);
        triangle_norm = normalize (triangle_norm);
        Vec3f light_dir (0.0, 0.0, -1.0);
        float intensity = scalar_product (triangle_norm, light_dir);

        if (intensity > 0)
            glLib::triangle (screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
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

