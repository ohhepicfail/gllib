//
// Created by epicfail on 03.03.16.
//

//! @brief Enum with all errors for throw with are encountered in gllib

#ifndef GLLIB_ERRORS_H
#define GLLIB_ERRORS_H

#include <stdio.h>

//! @brief use in other files there are we throw something
#define THROW( type_error )     {\
                                    Error oh_now_I_have_an_error ( type_error, __FILE__, __LINE__, __PRETTY_FUNCTION__);\
                                    throw oh_now_I_have_an_error;\
                                }

//{-------------------------------------------------------------------
//! @brief enum with all errors
//}-------------------------------------------------------------------
enum error_type
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
    INDEX_OUT_OF_BOUNDS,        //!<array index out of bounds
    ZERO_SIZE                   //!<used a number which meaning is zero, but it's invalid value
};

class Error
{
public:

    //{-------------------------------------------------------------------
    //! @brief use it, when you are throwing an error
    //!
    //! @warning function write info into log_file__. If constructor can't open log_file__ all program aborting!
    //! @warning if !filename, line <= 0 or !pretty_function constructor write it in log_file__ and abort program
    //}-------------------------------------------------------------------
    Error (error_type err, const char * filename, int line, const char * pretty_function);

    ~Error ();

    //{-------------------------------------------------------------------
    //! @brief used when we catch error
    //!
    //! @warning if !filename, line <= 0 or !pretty_function constructor write it in log_file__ and abort program
    //}-------------------------------------------------------------------
    Error (const Error & that);

    void print_error ();

private:

    //{-------------------------------------------------------------------
    //! @brief file where the error occured
    //!
    //! @warning I'm so sorry, but I must use const size, because otherwise there is a cycle:(
    //}-------------------------------------------------------------------
    char filename_[256];

    //! @brief line where the error occured
    int line_;

    //{-------------------------------------------------------------------
    //! @brief function where the error occured
    //!
    //! @warning I'm so sorry, but I must use const size, because otherwise there is a cycle:(
    //}-------------------------------------------------------------------
    char function_[256];

    //! @brief number of error
    error_type error_;

    //! @brief class Error writing all in this file
    static FILE * log_file__;
};

#endif //GLLIB_ERRORS_H