#include "Iris.hpp"

std::string Iris::call_tesseract( std::string img ) {
    // Tesseract
    char* outText;
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

    if (api->Init(NULL, "eng")) {
        std::cout << "Could not initialize tesseract.\n";
        exit(1);
    }

    Pix *image = pixRead( img.c_str() );
    api->SetImage(image);
    outText = api->GetUTF8Text();

    std::string out = std::string( outText );

    // IMPORTANT, don't leak memory here!!
    api->End();
    delete [] outText;
    pixDestroy(&image);

    return out;
}

std::string Iris::read( boost::filesystem::path file )
{
    std::ostringstream data;

    for( int i = 0; i < 1 ; ++i ) {
        // Read and extract info for each page.
        image.density( "300" );
        try {
            image.read( file.string() + "[" + std::to_string( i ) + "]" );
            image.magick( fmt );
            image.write( "tmp.png" );
        } catch ( Magick::Exception& ex ) {
            std::cout << ex.what() << std::endl;
        }

        data << call_tesseract( "tmp.png" );
    }

    return data.str();
    /*
    // Get the directory where we store the papiris file.
    int id = db->fetchPathId( file );
    boost::filesystem::path p = index_dir / std::to_string( id );
    create_directory( p );

    // Get the file where we save to.
    std::string name = file.filename().string() + ".papiris";
    boost::filesystem::path f = p / name;

    std::cout << "write to: " << f.string();

    boost::filesystem::ofstream fs( f );

    // Process the pdf into an image.
    image.read( f.string() );

    fs
    << file << std::endl
    << "data_here" << std::endl;
    */
}
