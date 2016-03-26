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

void glLib::triangle (Vec3i t0, Vec3i t1, Vec3i t2, TGAImage & image, const TGAColor & color, int * zbuffer)
{
    if (!zbuffer)
        THROW (ZERO_POINTER);

    // simple sort
    if (t0.y_ > t1.y_)
        std::swap (t0, t1);
    if (t0.y_ > t2.y_)
        std::swap (t0, t2);
    if (t1.y_ > t2.y_)
        std::swap (t1, t2);

    // drawing triangle
    for (int y = t0.y_; y <= t2.y_; y++)
    {
        int dy            = y <= t1.y_ ? (y - t0.y_) : (t2.y_ - y);
        Vec3i full_vec    = t2 - t0;
        Vec3i segment_vec = y <= t1.y_ ? (t1 - t0) : (t2 - t1);

        float shift_for_beg = 0.0;
        float shift_for_end = 0.0;
        if (dy != 0)
            shift_for_beg = (float) dy / full_vec.y_ * full_vec.x_;
        if (segment_vec.y_ != 0 && dy != 0)
            shift_for_end = (float) dy / segment_vec.y_ * segment_vec.x_;

        int beg_x = (int) (y <= t1.y_ ? (shift_for_beg + t0.x_) : (t2.x_ - shift_for_beg));
        int end_x = (int) (y <= t1.y_ ? (shift_for_end + t0.x_) : (t2.x_ - shift_for_end));

        if (beg_x > end_x)
            std::swap (beg_x, end_x);
        for (; beg_x <= end_x; beg_x++)      // draw a horizontal line
        {
            float shift_for_z = (float) dy / full_vec.y_ * full_vec.z_;
            int z = (int) (y <= t1.y_ ? shift_for_z + t0.z_ : t2.z_ - shift_for_z);
            if (zbuffer[y * image.get_width () + beg_x] < z)
            {
                zbuffer[y * image.get_width () + beg_x] = z;
                image.set (beg_x, y, color);
            }
        }
    }
}