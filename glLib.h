//epicfail@gmail.com

//! @brief  Do graphic


#ifndef GLLIB_GLLIB_H
#define GLLIB_GLLIB_H

#include "tgaimage.h"
#include "Vec.h"

class glLib
{
public:
    //{-----------------------------------------------------------------------
    //! @brief draw a line in .tga image
    //!
    //! @param [in]  begin, end Vec2i   object which contain x and y coordinates
    //! @param [out] image              TGAImage object in which line is drawn
    //! @param [in]  color              line color
    //!
    //! @warning function sorts coordinates itself
    //!
    //! @throw NEGATIVE_COORDINATE  coordinate is less than zero
    //! @throw TOO_BIG_COORDINATE   coordinate is bigger than image width or height
    //}-----------------------------------------------------------------------
    static void line (Vec2i begin, Vec2i end, TGAImage & image, const TGAColor & color);

    //{-----------------------------------------------------------------------
    //! @brief draw a triangle in .tga  image
    //!
    //! @param [in]  t0, t1, t2 3   lines forming a triangle
    //! @param [out] image          TGAImage object in which line is drawn
    //! @param [in]  color          triangle color
    //!
    //! @warning there aren't "const Vec2i &", because function swapping objects into yourself.
    //!          So, you can see copy constructor here.
    //}-----------------------------------------------------------------------
    static void triangle (Vec2i t0, Vec2i t1, Vec2i t2, TGAImage & image, const TGAColor & color);
};


#endif //GLLIB_GLLIB_H
