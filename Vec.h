//
// Created by epicfail on 03.03.16.
//

#ifndef GLLIB_VEC3_H
#define GLLIB_VEC3_H


#include <stddef.h>
#include <stdio.h>
#include "Errors.h"

//! @brief class works with 3 numbers
template <class t> class Vec3
{
public:
    //{---------------------------------------------------------------
    //! @brief light constructor
    //}---------------------------------------------------------------
    Vec3<t>   (): x_ (0), y_ (0), z_ (0) {}

    //{---------------------------------------------------------------
    //! @brief destructor fills all the poison
    //}---------------------------------------------------------------
    ~Vec3<t>  ()
    {
        x_ = 0xBADF00D;
        y_ = 0xBADF00D;
        z_ = 0xBADF00D;
    }

    //{---------------------------------------------------------------
    //! @brief copy from one Vec3 to another
    //!
    //! @param that sample for copy
    //}---------------------------------------------------------------
    Vec3<t> (const Vec3<t> & that)
    {
        x_ = that.x_;
        y_ = that.y_;
        z_ = that.z_;
    }

    //{---------------------------------------------------------------
    //! @brief you can work with class like as array with 3 elements
    //!
    //! @param i element index
    //!
    //! @warning remember, that there are only three elements in array!
    //!
    //! @throw INDEX_OUT_OF_BOUNDS array index out of bounds
    //!
    //! @return int number that lies on the index
    //}---------------------------------------------------------------
    const t & operator [] (size_t i)
    {
        if (i == 0)
            return x_;
        if (i == 1)
            return y_;
        if (i == 2)
            return z_;
        else
            throw INDEX_OUT_OF_BOUNDS;
    }

    //{---------------------------------------------------------------
    //! @brief access to the array elements
    //!
    //! @param i element index
    //!
    //! @warning remember, that there are only three elements in array!
    //!
    //! @throw INDEX_OUT_OF_BOUNDS array index out of bounds
    //!
    //! @return int number that lies on the index
    //}---------------------------------------------------------------
    const t & at (size_t i)
    {
        if (i == 0)
            return x_;
        if (i == 1)
            return y_;
        if (i == 2)
            return z_;
        else
            throw INDEX_OUT_OF_BOUNDS;
    }

    //{---------------------------------------------------------------
    //! @brief copy from one Vec3 to another
    //!
    //! @param that sample for copy
    //!
    //! @return copy
    //}---------------------------------------------------------------
    const Vec3<t> & operator = (const Vec3<t> & that)
    {
        x_ = that.x_;
        y_ = that.y_;
        z_ = that.z_;

        return *this;
    }

    t x_;   //!<First element of array (You can use x_ if you works with coordinates).
            //!<Otherwise don't use it. Work with elements such as array.
    t y_;   //!<Second element of array (You can use y_ if you works with coordinates).
            //!<Otherwise don't use it. Work with elements such as array.
    t z_;   //!<Third element of array (You can use Z_ if you works with coordinates).
            //!<Otherwise don't use it. Work with elements such as array.
};


//! @brief class works with 2 numbers
template <class t> class Vec2
{
public:
    //{---------------------------------------------------------------
    //! @brief light constructor
    //}---------------------------------------------------------------
    Vec2<t>   (): x_ (0), y_ (0) {}

    //{---------------------------------------------------------------
    //! @brief destructor fills all the poison
    //}---------------------------------------------------------------
    ~Vec2<t>  ()
    {
        x_ = 0xBADF00D;
        y_ = 0xBADF00D;
    }

    //{---------------------------------------------------------------
    //! @brief copy from one Vec2 to another
    //!
    //! @param that sample for copy
    //}---------------------------------------------------------------
    Vec2<t> (const Vec2<t> & that)
    {
        x_ = that.x_;
        y_ = that.y_;
    }

    //{---------------------------------------------------------------
    //! @brief you can work with class like as array with 2 elements
    //!
    //! @param i element index
    //!
    //! @warning remember, that there are only 2 elements in array!
    //!
    //! @throw INDEX_OUT_OF_BOUNDS array index out of bounds
    //!
    //! @return int number that lies on the index
    //}---------------------------------------------------------------
    const t & operator [] (size_t i)
    {
        if (i == 0)
            return x_;
        if (i == 1)
            return y_;
        else
            throw INDEX_OUT_OF_BOUNDS;
    }

    //{---------------------------------------------------------------
    //! @brief access to the array elements
    //!
    //! @param i element index
    //!
    //! @warning remember, that there are only 2 elements in array!
    //!
    //! @throw INDEX_OUT_OF_BOUNDS array index out of bounds
    //!
    //! @return int number that lies on the index
    //}---------------------------------------------------------------
    const t & at (size_t i)
    {
        if (i == 0)
            return x_;
        if (i == 1)
            return y_;
        else
            throw INDEX_OUT_OF_BOUNDS;
    }

    //{---------------------------------------------------------------
    //! @brief copy from one Vec2 to another
    //!
    //! @param that sample for copy
    //!
    //! @return copy
    //}---------------------------------------------------------------
    const Vec2<t> & operator = (const Vec2<t> & that)
    {
        x_ = that.x_;
        y_ = that.y_;

        return *this;
    }

    t x_;   //!<First element of array (You can use x_ if you works with coordinates).
            //!<Otherwise don't use it. Work with elements such as array.
    t y_;   //!<Second element of array (You can use y_ if you works with coordinates).
            //!<Otherwise don't use it. Work with elements such as array.
};

typedef Vec3<float> Vec3f;
typedef Vec3<int>   Vec3i;
typedef Vec2<float> Vec2f;
typedef Vec2<int>   Vec2i;

#endif //GLLIB_VEC3_H
