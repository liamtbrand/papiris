#include "FileIndex.hpp"

bool FileIndex::needsUpdate( boost::filesystem::path file )
{
    return true;
}

void FileIndex::update( boost::filesystem::path file, std::string data )
{
    boost::filesystem::path index_path = root / "index";
    boost::filesystem::create_directory( index_path );
    boost::filesystem::path f = index_path / (file.filename().string() + ".papiris");

    boost::filesystem::ofstream ofs( f );
    ofs
    << f.string() << std::endl
    << data << std::endl;
}
