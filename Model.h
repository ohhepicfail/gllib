//
// Created by epicfail on 03.03.16.
//

//! @brief Work with .obj files (open, read, contains the necessary data).
#ifndef GLLIB_MODEL_H
#define GLLIB_MODEL_H

#include <vector>
#include "Vec.h"
#include "Errors.h"


class Model
{
public:
    Model   ();
    ~Model  ();

    //{-------------------------------------------------------
    //! @brief open .obj file and save faces ans verts into arrays
    //!
    //! @param filename name of the .obj file
    //!
    //! @throw NULL_FILENAME            param filename is NULL
    //! @throw NULL_FILE                file pointer is NULL
    //! @throw NO_MEMORY_FOR_ALL_FILE   can't malloc memory for file
    //! @throw NO_ALL_FILE_WAS_READ     file size != fread size
    //! @throw NO_MODEL_IN_FILE         strtok can't find "\n"
    //! @throw NO_VERTS_IN_FILE         file doesn't contain verts
    //! @throw NO_FACES_IN_FILE         file doesn't contain faces
    //}-------------------------------------------------------
    void    open (const char * filename);

    //{-------------------------------------------------------
    //! @return number of faces with contained in this model
    //}-------------------------------------------------------
    size_t  nfaces ();

    //{-------------------------------------------------------
    //! @return number of verts with contained in this model
    //}-------------------------------------------------------
    size_t  nverts ();

    //{-------------------------------------------------------
    //! @param i vert index
    //!
    //! @throw TOO_HIGH_VERT_INDEX  index is more than number of verts in array
    //!
    //! @return vert with index i
    //}-------------------------------------------------------
    Vec3f   vert (size_t i);

    //{-------------------------------------------------------
    //! @param i face index
    //!
    //! @throw TOO_HIGH_FACE_INDEX  index is more than number of faces in array
    //!
    //! @return face with index i
    //}-------------------------------------------------------
    Vec3i   face (size_t i);
private:
    //{-------------------------------------------------------
    //! @brief copy constructor is disabled
    //!
    //! @warning if you use it, function causes assert with message and aborts all program :)
    //}-------------------------------------------------------
    Model   (const Model &);

    //{-------------------------------------------------------
    //! @brief operator = is disabled
    //!
    //! @warning if you use it, function causes assert with message and aborts all program :)
    //}-------------------------------------------------------
    void    operator = (const Model & that);

    //{-------------------------------------------------------
    //! @brief if all verts are less than 0.1 or are more than 1, we must understand it
    //!
    //! @param vec one vert
    //!
    //! @warning I'm so sorry, but it works long :(
    //}-------------------------------------------------------
    void    test_standard (const Vec3f & vec);

    //{-------------------------------------------------------
    //! @brief if we have nonstandard verts, function says it to us
    //!
    //! @return true if nonstandard, else false
    //}-------------------------------------------------------
    bool    is_non_standard ();

    //{-------------------------------------------------------
    //! @brief if verts are nonstandard, function correct them
    //!
    //! @return true if nonstandard, else false
    //}-------------------------------------------------------
    void    make_standard (std::vector <Vec3f> & verts);

    std::vector <Vec3f> verts_;     //!<array of verts
    std::vector <Vec3i> faces_;     //!<array of faces
    bool    non_standard_;          //!<flag for nonstandard verts
    size_t  shift_for_standard_;    //!<stores a shift form the standard
};


#endif //GLLIB_MODEL_H
