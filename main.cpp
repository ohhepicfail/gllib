//epicfail@gmail.com

#include "tgaimage.h"
#include "glLib.h"
#include "Model.h"

const TGAColor white = TGAColor (255, 255, 255, 255);
const TGAColor red   = TGAColor (255, 0,   0,   255);
const TGAColor green = TGAColor (0,   255, 0,   255);

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

    TGAImage image(100, 100, TGAImage::RGB);
    image.set(52, 41, white);

    try
    {
        glLib::line (13, 41, 80, 51, image, white);
        glLib::line (20, 13, 40, 80, image, red);
        glLib::line (80, 40, 13, 20, image, green);
    }
    catch (...)
    {
        printf ("bad agruments in glLib::line ()\n");
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}