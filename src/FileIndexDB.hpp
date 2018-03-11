//
//  FileIndexDB.hpp
//  
//
//  Created by Liam Brand on 11/03/18.
//

#ifndef FileIndexDB_hpp
#define FileIndexDB_hpp

#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>

class FileIndexDB
{
public:
    FileIndexDB( const char* database_path )
        : db_path( database_path )
        , db( nullptr )
    {
    }
    
    int connect();
    void close();
    
    static int default_callback(void *NotUsed, int argc, char **argv, char **azColName);
    void createTables();
    
    int fetchPathId( boost::filesystem::path path );
    
    int addPath( const char* path, int parent );
    
private:
    const char* db_path;
    sqlite3* db;
    
    std::vector< int > cached_path;
    
    const char* create_table_paths =
    "CREATE TABLE paths("
    "  id int IDENTITY,"
    "  path varchar(255),"
    "  parent int,"
    "  PRIMARY KEY (id),"
    "  FOREIGN KEY (parent) REFERENCES id"
    ");";
    
    const char* create_table_files =
    "CREATE TABLE files("
    "  id int,"
    "  path varchar(255),"
    "  parent int,"
    "  PRIMARY KEY (id),"
    "  FOREIGN KEY (parent) REFERENCES (paths.id)"
    ");";
};

#endif /* FileIndexDB_hpp */
