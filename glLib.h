//epicfail@gmail.com

//! @brief  Do graphic


#ifndef GLLIB_GLLIB_H
#define GLLIB_GLLIB_H

#include "tgaimage.h"

class glLib
{
public:
    //{-----------------------------------------------------------------------
    //! @brief draw a line in .tga image
    //!
    //! @param [in]  x0, y0, x1, y2 coordinates
    //! @param [out] image TGAImage object in which line is drawn
    //! @param [in]  color line color
    //!
    //! @warning function sorts coordinates itself
    //!
    //! @throw NEGATIVE_COORDINATE  coordinate is less than zero
    //! @throw TOO_BIG_COORDINATE   coordinate is bigger than image width or height
    //}-----------------------------------------------------------------------
    static void line (int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor & color);
};


#endif //GLLIB_GLLIB_H
