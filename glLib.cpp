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

// todo: doc it
// todo: not here
Vec3<float> vi_to_vf (const Vec3<int> & vi)
{
    Vec3<float> vf;
    vf.x_ = (float) vi.x_;
    vf.y_ = (float) vi.y_;
    vf.z_ = (float) vi.z_;

    return vf;
}

// todo: doc it
// todo: not here
Vec3<int> vf_to_vi (const Vec3<float> & vf)
{
    Vec3<int> vi;
    vi.x_ =  (int) (vf.x_ + 0.5);
    vi.y_ =  (int) (vf.y_ + 0.5);
    vi.z_ =  (int) (vf.z_ + 0.5);

    return vi;
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
        int x1 = 0, x2 = 0;

        int dy                = y <= t1.y_ ? (y - t0.y_) : (t2.y_ - y);
        int full_height       = (t2.y_ - t0.y_);
        int full_width        = (t2.x_ - t0.x_);
        int segment_height    = y <= t1.y_ ? (t1.y_ - t0.y_) : (t2.y_ - t1.y_);
        int segment_width     = y <= t1.y_ ? (t1.x_ - t0.x_) : (t2.x_ - t1.x_);

        printf ("%d\t", dy);
        float shift_for_beg = 0.0;
        float shift_for_end = 0.0;
        if (dy != 0)
            shift_for_beg = (float) dy / full_height * full_width;
        if (segment_height != 0.0 && dy != 0)
            shift_for_end = (float) dy / segment_height * segment_width;
        printf ("%f\t%f\t", shift_for_beg, shift_for_end);
        x1 = (int) (y <= t1.y_ ? (shift_for_beg + t0.x_) : (t2.x_ - shift_for_beg));
        x2 = (int) (y <= t1.y_ ? (shift_for_end + t0.x_) : (t2.x_ - shift_for_end));
        printf ("%d\t%d\n", x1, x2);
        if (x1 > x2)
            std::swap (x1, x2);
        for (; x1 <= x2; x1++)      // draw a horizontal line
            image.set (x1, y, color);
    }
}


void glLib::rasterize (Vec2i t0, Vec2i t1, TGAImage & image, const TGAColor & color, int * ybuffer)
{
    if (t0.x_ > t1.x_)
        std::swap (t0, t1);

    for (int x = t0.x_; x <= t1.x_; x++)
    {
        int y = (float) (x - t0.x_) / (t1.x_ - t0.x_) * (t1.y_ - t0.y_) + t0.y_;
        if (y > ybuffer[x])
        {
            ybuffer[x] = y;
            image.set (x, 1, color);
        }

    }
}