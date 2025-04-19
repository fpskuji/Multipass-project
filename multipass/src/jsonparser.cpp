#include "jsonparser.hpp"
#include <iostream>
#include <fstream>
#include <rapidjson/filereadstream.h>

namespace simplestream {

    std::optional<rapidjson::Document> JSONParser::fetch_products(const std::string& filename) {
        FILE* fp = fopen(filename.c_str(), "r");
        if (!fp) {
            std::cerr << "Could not open file " << filename << std::endl;
            return std::nullopt;
        }

        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        rapidjson::Document document;
        document.ParseStream(is);
        fclose(fp);

        if (document.HasParseError()) {
            std::cerr << "Error parsing JSON file" << std::endl;
            return std::nullopt;
        }

        return document;
    }
}