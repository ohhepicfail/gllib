//
// Created by epicfail on 03.03.16.
//

#ifndef GLLIB_VEC3_H
#define GLLIB_VEC3_H


#include <stddef.h>

//! @brief class works with 3 coordinates
class Vec3f
{
public:
    Vec3f   ();
    ~Vec3f  ();

    //{---------------------------------------------------------------
    //! @brief copy from one Vec3f to another
    //!
    //! @param that sample for copy
    //}---------------------------------------------------------------
    Vec3f (const Vec3f & that);

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
    const float & operator [] (size_t i);

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
    const float & at (size_t i);

    //{---------------------------------------------------------------
    //! @brief copy from one Vec3f to another
    //!
    //! @param that sample for copy
    //!
    //! @return copy
    //}---------------------------------------------------------------
    const Vec3f & operator = (const Vec3f & that);

    float x_;   //!<first coordinate
    float y_;   //!<second coordinate
    float z_;   //!<third coordinate
};


//! @brief class works with 3 numbers
class Vec3i
{
public:
    Vec3i ();
    ~Vec3i ();
    int value_[3];      //!<3 numbers - it's the meaning of this class

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
    const int & operator [] (size_t i);

    //{---------------------------------------------------------------
    //! @brief copy from one Vec3i to another
    //!
    //! @param that sample for copy
    //}---------------------------------------------------------------
    Vec3i (const Vec3i & that);

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
    const int & at (size_t i);

    //{---------------------------------------------------------------
    //! @brief copy from one Vec3i to another
    //!
    //! @param that sample for copy
    //!
    //! @return copy
    //}---------------------------------------------------------------
    const Vec3i & operator = (const Vec3i & that);
};

#endif //GLLIB_VEC3_H
