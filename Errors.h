//
// Created by epicfail on 03.03.16.
//

//! @brief Enum with all errors for throw with are encountered in gllib

#ifndef GLLIB_ERRORS_H
#define GLLIB_ERRORS_H

enum Errors
{
    NULL_FILENAME,              //!<char * filename is NULL
    NULL_FILE,                  //!<file pointer is NULL
    NO_MEMORY_FOR_ALL_FILE,     //!<can't malloc memory for file
    NO_ALL_FILE_WAS_READ,       //!<file size != fread size
    NO_MODEL_IN_FILE,           //!<strtok can't find "\n"
    TOO_HIGH_VERT_INDEX,        //!<file doesn't contain verts
    TOO_HIGH_FACE_INDEX,        //!<file doesn't contain faces
    NO_VERTS_IN_FILE,           //!<index is more than number of verts in array
    NO_FACES_IN_FILE,           //!<index is more than number of faces in array
    NEGATIVE_COORDINATE,        //!<coordinate is less than zero
    TOO_BIG_COORDINATE,         //!<coordinate is bigger than image width or height
    INDEX_OUT_OF_BOUNDS         //!<array index out of bounds
};

#endif //GLLIB_ERRORS_H