#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <rapidjson/document.h>
#include <string>
#include <optional>

namespace simplestream {

    class JSONParser {
    public:
    std::optional<rapidjson::Document> fetch_products(const std::string& filename);
    };

}

#endif // JSONPARSER_H