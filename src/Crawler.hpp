//
//  Crawler.hpp
//  
//
//  Created by Liam Brand on 11/03/18.
//

#ifndef Crawler_hpp
#define Crawler_hpp

#include <boost/filesystem.hpp>
#include <thread>
#include <chrono>

#include "Iris.hpp"
#include "FileIndex.hpp"

class Crawler
{
public:
    Crawler( Iris crawler_iris, FileIndex file_index )
        : iris( crawler_iris )
        , index( file_index )
    {
    }
    
    void crawl( boost::filesystem::path root );
private:
    Iris iris;
    FileIndex index;
};

#endif /* Crawler_hpp */
