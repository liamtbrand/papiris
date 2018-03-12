#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/filesystem/fstream.hpp>
//#include <openssl/md5.h>

#include "CommandParser.hpp"
#include "FileIndexDB.hpp"
#include "Iris.hpp"

int main( int argc, const char* argv[] ) {
    
    std::cout << "Starting Papiris.\n";
    std::cout << "[Papiris]: Args: " << *argv << "\n";
    
    // Find the home directory if possible.
    boost::filesystem::path home_path;
    const char* home = std::getenv( "HOME" );
    if( home != NULL ) {
        home_path = home;
    } else {
        std::cout << "[Papiris]: I can't find your home directory! Maybe you can set HOME=/some/path ?" << std::endl;
        std::cout << "[Papiris]: I don't know what to do with the data so I'll store it here for now." << std::endl;
        home_path = ".";
    }
    
    // Setup some important directories
    boost::filesystem::path papiris_path = ".papiris";
    boost::filesystem::create_directory( home_path / papiris_path );
    boost::filesystem::path db_file_path = "papiris.db";
    boost::filesystem::path full_db_file_path = home_path / papiris_path / db_file_path;
    boost::filesystem::path index_dir = home_path / papiris_path / "index";
    boost::filesystem::create_directory( index_dir );
    //boost::filesystem::path path_here = ".";
    
    std::string db_path = full_db_file_path.string();
    FileIndexDB index = FileIndexDB( db_path.c_str() );
    index.connect(); // Create the database connection
    index.createTables(); // Ensure we have the correct database..
    Iris iris = Iris( 300 );
    
    std::cout << "[Papiris]: Started.\n";
    
    // Start at root.
    std::cout << "[Papiris]: Crawling...\n";
    boost::filesystem::recursive_directory_iterator dir( home_path ), itr_end;
    while ( dir != itr_end ) {
        try {
            boost::filesystem::path f = dir->path();
            
            if( is_regular_file( f ) && f.extension() == ".pdf" ) {
                // If we don't need to update this file, just stop.
                if( index.needsUpdate( f ) ) {
                    // Only do something if we need to update the file.
                    std::string data = iris.read( f );
                    
                    boost::filesystem::path file = index_dir / (f.filename().string() + ".papiris");
                    boost::filesystem::ofstream ofs( file );
                    ofs
                    << f.string() << std::endl
                    << data << std::endl;
                }
            }
            
        } catch( boost::filesystem::filesystem_error& e ) {
            std::cout << e.what() << std::endl;
        }
        
        // Throttle back the speed so we don't use too much cpu.
        int throttle_back = 0;
        std::this_thread::sleep_for ( std::chrono::milliseconds( throttle_back ) );
        
        // Try to get the next directory.
        try {
            ++dir;
        // Maybe we need to skip this one if we get an error.
        } catch( boost::filesystem::filesystem_error& e ) {
            std::cout << e.what() << std::endl;
            dir.no_push();
            try {
                ++dir;
            } catch ( boost::filesystem::filesystem_error& er ) {
                std::cout << "!! " << er.what() << std::endl;
                break;
            }
        }
    }
    
    // example test...
    try {
        
        
        /*
        std::string file = "example.pdf";
        
        std::string hash = getHash( file );
        
        image.magick( intermediate_format );
        
        //Magick::Blob blob;
        //image.write( &blob );
        image.write( "tmp.png" );
        
        std::string data = call_tesseract( "tmp.png" );
        std::cout << data << "\n";*/
        
        /*
        Magick::ReadOptions options;
        std::list<Magick::Image> images;
        Magick::readImages( &images, "example.pdf", options );
        
        for( Magick::Image image : images ) {
            image.magick( "png" );
            image.write( "example.png" );
        }*/
        
        //pdf_file.read( "example.png" );
        //pdf_file.magick("png");
        
        //Magick::Blob blob;
        //pdf_file.write( &blob );
        
        //pdf_file.write("example.png");
    } catch ( Magick::Exception& ex ) {
        std::cout << ex.what() << std::endl;
    }
    
    CommandParser cp;
    CommandParser::Status s;
    
    do {
        
        std::string command;
        std::cin >> command;
        
        s = cp.parse( command );
        std::cout << "[Papiris]: " << cp.getMessage();
        
    } while ( s != CommandParser::STOP_SIGNAL );
    
    std::cout << "Stopping Papiris.\n";
    
    index.close();
    
    std::cout << "Stopped.\n";
    
    return 0;
}
