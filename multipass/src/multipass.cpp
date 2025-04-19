#include "simplestream.hpp"
#include "jsondownloader.hpp"
#include "jsonparser.hpp"
#include <filesystem>
#include <iostream>


using namespace std;    

int main ()
{
    simplestream::JSONDownloader downloader;
    std::filesystem::create_directories(".simplestream_cache");
    downloader.download_JSON_info();

    simplestream::JSONParser parser;
    rapidjson::Document document;
    document = parser.fetch_products(simplestream::FILENAME.data()).value();
    
    // Extract and print all keys under products
    for (auto& itr : document["products"].GetObject()) {
        std::cout << "product_key: " << itr.name.GetString() << std::endl;
    }

    return 0;
}