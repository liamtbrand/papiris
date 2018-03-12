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
    
    bool needsUpdate( boost::filesystem::path file );
    
private:
    const char* db_path;
    sqlite3* db;
    
    const char* create_table_files = R"EOF(
    CREATE TABLE files(
        id int IDENTITY,
        path varchar(255) UNIQUE,
        modified int,
        PRIMARY KEY (id)
    );
    )EOF";
    
    int getId( std::string path );
};

#endif /* FileIndexDB_hpp */
