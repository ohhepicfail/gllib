//epicfail@gmail.com

#include <cmath>
#include "glLib.h"
#include "Errors.h"


void glLib::line (int x0, int y0, int x1, int y1, TGAImage & image, const TGAColor & color)
{
    if (x0 < 0 || x1 < 0 || y0 < 0 || y1 < 0)
        THROW (NEGATIVE_COORDINATE);

    bool swap = false;
    if (std::abs (x1 - x0) < std::abs (y1 - y0))
    {
        std::swap (x0, y0);
        std::swap (x1, y1);
        swap = true;
    }

    if (x0 > x1)
    {
        std::swap (x0, x1);
        std::swap (y0, y1);
    }

    if (swap)
    {
        if (std::max (x0, x1) > image.get_height () || std::max (y0, y1) > image.get_width ())
            THROW (TOO_BIG_COORDINATE);
    }
    else
    {
        if (std::max (x0, x1) > image.get_width () || std::max (y0, y1) > image.get_height ())
            THROW (TOO_BIG_COORDINATE);
    }

    const float ratio = (float)(std::fabs (y1 - y0)) / (float)(x1 - x0);
    float error = 0.0;
    for (; x0 < x1; x0++)
    {
        if (swap)
            image.set(y0, x0, color);
        else
            image.set(x0, y0, color);

        error += ratio;

        if (error > 0.5)
        {
            y0 += (y1 > y0 ? 1 : -1);
            error -= 1;
        }
    }
}