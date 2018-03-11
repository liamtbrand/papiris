//
//  FileIndexDB.cpp
//  
//
//  Created by Liam Brand on 11/03/18.
//

#include "FileIndexDB.hpp"

int FileIndexDB::default_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        std::cout << azColName[i] << " = " << ( argv[i] ? argv[i] : "NULL" ) << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

int FileIndexDB::connect()
{
    // Connect to database.
    std::cout << "[Papiris]: Connecting to database..." << std::endl;
    int rc;
    
    rc = sqlite3_open( db_path, &db );
    if( rc ) {
        std::cout << "[Papiris]: Couldn't open database! Severe." << std::endl;
        sqlite3_close( db );
        return rc;
    }
    std::cout << "[Papiris]: Database connection successful." << std::endl;
    return rc;
}

void FileIndexDB::close()
{
    sqlite3_close( db );
}

void FileIndexDB::createTables()
{
    char* zErrMsg;
    int rc;
    
    std::cout << create_table_paths << std::endl;
    
    /* Execute Query */
    rc = sqlite3_exec(
        db,
        create_table_paths,
        default_callback,
        0,
        &zErrMsg
    );
    
    /* Check Status */
    if( rc != SQLITE_OK ){
        std::cout << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free( zErrMsg );
    } else {
        std::cout << "Table created successfully." << std::endl;
    }
}

int FileIndexDB::fetchPathId( boost::filesystem::path path )
{
    // Ensure we are using the canonical path.
    boost::filesystem::path canonical_path = canonical( path );
    std::cout << "canonical: " << canonical_path << std::endl;
    // Check and update database if needed.
    
    // Return the path's id.
    return 1;
}

int FileIndexDB::addPath( const char* path, int parent )
{
    std::ostringstream query;
    
    query
    << "INSERT INTO paths VALUES("
    << "NULL,"
    << "'" << path << "',";
    if( parent == 0 ) {
        query << "NULL";
    } else {
        query << parent;
    }
    query << ");";
    
    char* zErrMsg;
    int rc;
    
    std::string querystr = query.str();
    
    /* Execute Query */
    rc = sqlite3_exec(
        db,
        querystr.c_str(),
        default_callback,
        0,
        &zErrMsg
    );
    
    /* Check Status */
    if( rc != SQLITE_OK ){
        std::cout << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free( zErrMsg );
    }
    return rc;
}
