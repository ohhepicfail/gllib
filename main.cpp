//epicfail@gmail.com

#include "tgaimage.h"
#include "glLib.h"

const TGAColor white = TGAColor (255, 255, 255, 255);
const TGAColor red   = TGAColor (255, 0,   0,   255);
const TGAColor green = TGAColor (0,   255, 0,   255);

int main ()
{
    TGAImage image(100, 100, TGAImage::RGB);
    image.set(52, 41, white);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image

    try
    {
        glLib::line (13, 21, 80, 41, image, white);
        glLib::line (20, 13, 40, 80, image, red);
        glLib::line (80, 40, 13, 20, image, green);
    }
    catch (...)
    {
        printf ("hello, my error\n");
    }

    image.write_tga_file("output.tga");
    return 0;
}