//
//  FileIndex.hpp
//  
//
//  Created by Liam Brand on 13/03/18.
//

#ifndef FileIndex_hpp
#define FileIndex_hpp

#include <boost/filesystem.hpp>

#include "FileIndexDB.hpp"

class FileIndex
{
public:
    FileIndex( boost::filesystem::path root_dir )
        : root( root_dir )
        , db( root_dir / "index.db" )
    {
        db.connect();
        db.createTables();
    }
    
    bool needsUpdate( boost::filesystem::path file );
    void update( boost::filesystem::path file, std::string data );
private:
    boost::filesystem::path root;
    FileIndexDB db;
};

#endif /* FileIndex_hpp */
