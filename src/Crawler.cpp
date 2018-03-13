//
//  Crawler.cpp
//  
//
//  Created by Liam Brand on 11/03/18.
//

#include "Crawler.hpp"

void Crawler::crawl( boost::filesystem::path root )
{
    boost::filesystem::recursive_directory_iterator dir( root ), itr_end;
    while ( dir != itr_end ) {
        try {
            boost::filesystem::path f = dir->path();
            
            if( is_regular_file( f ) && f.extension() == ".pdf" ) {
                // If we don't need to update this file, just stop.
                if( index.needsUpdate( f ) ) {
                    // Only do something if we need to update the file.
                    std::string data = iris.read( f );
                    // Insert into index.
                    index.update( f, data );
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
}
