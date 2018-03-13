#include <iostream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/filesystem/fstream.hpp>
//#include <openssl/md5.h>

#include "CommandParser.hpp"
#include "FileIndex.hpp"
#include "Iris.hpp"
#include "Crawler.hpp"

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
    
    boost::filesystem::path papiris_path = ".papiris";
    boost::filesystem::create_directory( home_path / papiris_path );
    Crawler crawler = Crawler( Iris( 300 ), FileIndex( home_path / papiris_path ) );
    
    std::cout << "[Papiris]: Started.\n";
    
    std::cout << "[Papiris]: Crawling...\n";
    crawler.crawl( home_path );
    
    CommandParser cp;
    CommandParser::Status s;
    
    do {
        
        std::string command;
        std::cin >> command;
        
        s = cp.parse( command );
        std::cout << "[Papiris]: " << cp.getMessage();
        
    } while ( s != CommandParser::STOP_SIGNAL );
    
    std::cout << "Stopping Papiris.\n";
    
    std::cout << "Stopped.\n";
    
    return 0;
}
