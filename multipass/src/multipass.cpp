#include "simplestream.hpp"
#include "jsondownloader.hpp"
#include <filesystem>
#include <iostream>


using namespace std;

int main ()
{
    simplestream::JSONDownloader downloader;
    std::filesystem::create_directories(".simplestream_cache");
    downloader.download_JSON_info();

    return 0;
}