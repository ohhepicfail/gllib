//epicfail@gmail.com

#include <cmath>
#include "glLib.h"


void glLib::line (Vec2i begin, Vec2i end, TGAImage & image, const TGAColor & color)
{
    int x0 = begin.x_;
    int y0 = begin.y_;
    int x1 = end.x_;
    int y1 = end.y_;
    // maybe you forgot to normalize them?
    if (x0 < 0 || x1 < 0 || y0 < 0 || y1 < 0)
        THROW (NEGATIVE_COORDINATE);

    // if you don't understand what is happens here, you can read about Bresenham's algorithm
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
    if (t0.y_ > t1.y_) std::swap (t0, t1);
    if (t0.y_ > t2.y_) std::swap (t0, t2);
    if (t1.y_ > t2.y_) std::swap (t1, t2);

    // drawing triangle
    size_t width = (size_t) image.get_width ();
    Vec3i full_vec    = t2 - t0;
    for (int y = t0.y_; y <= t2.y_; y++)
    {
        int dy            = y <= t1.y_ ? (y - t0.y_) : (t2.y_ - y);
        Vec3i segment_vec = y <= t1.y_ ? (t1 - t0) : (t2 - t1);

        float alpha = 0.0;
        if (full_vec.y_ != 0.0)
            alpha = (float) dy / full_vec.y_;
        float beta = 0.0;
        if (segment_vec.y_ != 0)
            beta = (float) dy / segment_vec.y_;

        int beg_x  = (int) (y <= t1.y_ ? (alpha * full_vec.x_ + t0.x_) : (t2.x_ - alpha * full_vec.x_));
        int end_x  = (int) (y <= t1.y_ ? (beta * segment_vec.x_ + t0.x_) : (t2.x_ - beta * segment_vec.x_));
        int beg_z  = (int) (y <= t1.y_ ? (alpha * full_vec.z_ + t0.z_) : (t2.z_ - alpha * full_vec.z_));
        int end_z  = (int) (y <= t1.y_ ? (beta * segment_vec.z_ + t0.z_) : (t2.z_ - beta * segment_vec.z_));

        if (beg_x > end_x) { std::swap (beg_x, end_x); std::swap (beg_z, end_z); }

        // draw a horizontal line
        for (int x = beg_x; x <= end_x; x++)
        {
            size_t idx = y * width + x;
            double gamma = (beg_x == end_x) ? 1.0 : (double) (x - beg_x) / (end_x - beg_x);
            int z = (int) (gamma * (end_z - beg_z) + beg_z);
            if (zbuffer[idx] < z)
            {
                zbuffer[idx] = z;
                image.set (x, y, color);
            }
        }
    }
}


void glLib::gouraud_shading_traingle (Vec3i t0, Vec3i t1, Vec3i t2, float ity0, float ity1, float ity2, TGAImage &image,
                                      int *zbuffer)
{
    if (!zbuffer)
    THROW (ZERO_POINTER);

    // simple sort
    if (t0.y_ > t1.y_) { std::swap (t0, t1); std::swap (ity0, ity1); }
    if (t0.y_ > t2.y_) { std::swap (t0, t2); std::swap (ity0, ity2); }
    if (t1.y_ > t2.y_) { std::swap (t1, t2); std::swap (ity1, ity2); }

    // drawing triangle
    size_t width = (size_t) image.get_width ();
    Vec3i full_vec = t2 - t0;
    for (int y = t0.y_; y <= t2.y_; y++)
    {
        int dy            = y <= t1.y_ ? (y - t0.y_) : (t2.y_ - y);
        Vec3i segment_vec = y <= t1.y_ ? (t1 - t0) : (t2 - t1);

        float alpha = 0.0;
        if (full_vec.y_ != 0.0)
            alpha = (float) dy / full_vec.y_;
        float beta = 0.0;
        if (segment_vec.y_ != 0)
            beta = (float) dy / segment_vec.y_;

        int   beg_x = (int) (y <= t1.y_ ? (alpha * full_vec.x_    + t0.x_) : (t2.x_ - alpha * full_vec.x_));
        int   end_x = (int) (y <= t1.y_ ? (beta  * segment_vec.x_ + t0.x_) : (t2.x_ - beta  * segment_vec.x_));
        int   beg_z = (int) (y <= t1.y_ ? (alpha * full_vec.z_    + t0.z_) : (t2.z_ - alpha * full_vec.z_));
        int   end_z = (int) (y <= t1.y_ ? (beta  * segment_vec.z_ + t0.z_) : (t2.z_ - beta  * segment_vec.z_));
        float beg_n =        y <= t1.y_ ? (alpha * (ity2 - ity0)  + ity0)  : (ity2  - alpha * (ity2 - ity0));
        float end_n =        y <= t1.y_ ? (beta  * (ity1 - ity0)  + ity0)  : (ity2  - beta  * (ity2 - ity1));

        if (beg_x > end_x) { std::swap (beg_x, end_x); std::swap (beg_z, end_z); std::swap (beg_n, end_n);}
        for (int x = beg_x; x <= end_x; x++)      // draw a horizontal line
        {
            size_t idx = (size_t) y * width + (size_t) x;
            double gamma = (beg_x == end_x) ? 1.0 : (double) (x - beg_x) / (end_x - beg_x);
            int   z = (int) (gamma * (end_z - beg_z) + beg_z);
            double k =        gamma * (end_n - beg_n) + beg_n;
            if (zbuffer[idx] < z)
            {
                zbuffer[idx] = z;
                image.set (x, y, TGAColor(255, 255, 255) * k);
            }
        }
    }
}
