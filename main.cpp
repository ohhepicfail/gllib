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

//    for (size_t i = 0; i < model.nfaces (); i++)
//    {
//        Vec3i face;
//        try
//        {
//            face = model.face (i);
//        }
//        catch (Error err)
//        {
//            err.print_error ();
//            exit (1);
//        }
//        for (size_t j = 0; j < 3; j++)
//        {
//            Vec3f v0, v1;
//            try
//            {
//                v0 = model.vert ((size_t) face[j] - 1);
//                v1 = model.vert ((size_t) face[(j + 1) % 3] - 1);
//            }
//            catch (Error err)
//            {
//                err.print_error ();
//                exit (1);
//            }
//
//            Vec2i begin, end;
//            begin.x_ = (int) v0.x_;
//            begin.y_ = (int) v0.y_;
//            end.x_ = (int) v1.x_;
//            end.y_ = (int) v1.y_;
//
//            try
//            {
//                glLib::line (begin, end, image, green);
//            }
//            catch (Error err)
//            {
//                err.print_error ();
//                exit (1);
//            }
//        }
//    }

//    Vec2i t0[3] = {Vec2i(100, 700),   Vec2i(500, 1600),  Vec2i(700, 800)};
//    Vec2i t1[3] = {Vec2i(1800, 500),  Vec2i(1500, 10),   Vec2i(700, 1800)};
//    Vec2i t2[3] = {Vec2i(1800, 1500), Vec2i(1200, 1600), Vec2i(1300, 1800)};
//
//
//    glLib::triangle(t0[0], t0[1], t0[2], image, red);
//    glLib::triangle(t1[0], t1[1], t1[2], image, white);
//    glLib::triangle(t2[0], t2[1], t2[2], image, green);

    for (int i=0; i<model.nfaces(); i++) {
        printf ("all is okey! i is %d\n", i);
        Vec3i face = model.face(i);
        Vec2i screen_coords[3];
        for (int j=0; j<3; j++) {
            Vec3f world_coords = model.vert(face[j] - 1);
            screen_coords[j] = Vec2i(world_coords.x_, world_coords.y_);
        }
        glLib::triangle (screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}