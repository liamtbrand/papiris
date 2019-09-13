#ifndef Iris_hpp
#define Iris_hpp

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <Magick++.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

class Iris
{
public:
    Iris( int density )
        : image()
    {
        // Setup ImageMagick
        image.density( std::to_string( density ).c_str() );
    }

    std::string read( boost::filesystem::path file );
private:
    Magick::Image image;
    std::string fmt = "png";

    std::string call_tesseract( std::string img );
};

#endif /* Iris_hpp */
