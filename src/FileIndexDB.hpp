#ifndef FileIndexDB_hpp
#define FileIndexDB_hpp

#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>

class FileIndexDB
{
public:
    FileIndexDB( boost::filesystem::path db_file_path )
        : db_file( db_file_path )
        , db( nullptr )
    {
    }

    int connect();
    void close();

    void createTables();

    static int default_callback(void *NotUsed, int argc, char **argv, char **azColName);

    //bool needsUpdate( boost::filesystem::path file );

    //void updateFor( boost::filesystem::path file, std::string data );

private:
    boost::filesystem::path db_file;
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
