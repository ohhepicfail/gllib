//epicfail@gmail.com

#include <cmath>
#include "glLib.h"


void glLib::line (Vec2i begin, Vec2i end, TGAImage & image, const TGAColor & color)
{
    int x0 = begin.x_;
    int y0 = begin.y_;
    int x1 = end.x_;
    int y1 = end.y_;
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

    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror = std::abs (dy) * 2;
    int error  = 0;
    for (; x0 <= x1; x0++)
    {
        if (swap)
            image.set(y0, x0, color);
        else
            image.set(x0, y0, color);

        error += derror;

        if (error > dx)
        {
            y0 += (dy > 0 ? 1 : -1);
            error -= dx * 2;
        }
    }
}

void glLib::triangle (Vec2i t0, Vec2i t1, Vec2i t2, TGAImage & image, const TGAColor & color)
{
    // simple sort
    if (t0.y_ > t1.y_)
        std::swap (t0, t1);
    if (t0.y_ > t2.y_)
        std::swap (t0, t2);
    if (t1.y_ > t2.y_)
        std::swap (t1, t2);

    // bottom part of the triangle
    for (int y = t0.y_; y <= t1.y_; y++)
    {
        int x1 = 0, x2 = 0;

        int dy                = (y - t0.y_);
        int full_height       = (t2.y_ - t0.y_);
        int segment_height    = (t1.y_ - t0.y_);
        int full_width        = (t2.x_ - t0.x_);
        int segment_width     = (t1.x_ - t0.x_);

        if (segment_height == 0)
            x2 = t0.x_;
        if (dy == 0)
        {
            x1 = t0.x_;
            x2 = t0.x_;
        }
        else
        {
            x1 = (int) ((float) dy / full_height * full_width + t0.x_);
            x2 = (int) ((float) dy / segment_height * segment_width + t0.x_);
        }

        if (x1 > x2)
            std::swap (x1, x2);
        for (; x1 <= x2; x1++)      // draw a horizontal line
            image.set (x1, y, color);
    }

    // top part of the triangle
    for (int y = t2.y_; y > t1.y_; y--) // there are y > t1.y_, because y = t1.y_ I paint in the bottom part
    {
        int x0 = 0, x2 = 0;

        if (t2.y_ - t1.y_ == 0)
            x2 = t1.x_;
        else
        {
            x0 = (int) (t2.x_ - (float) (t2.y_ - y) / (t2.y_ - t0.y_) * (t2.x_ - t0.x_));
            x2 = (int) (t2.x_ - (float) (t2.y_ - y) / (t2.y_ - t1.y_) * (t2.x_ - t1.x_));
        }

        if (x0 < x2)
            std::swap (x0, x2);
        for (; x0 >= x2; x0--)
            image.set (x0, y, color);
    }
}