#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <rapidjson/document.h>
#include <string>
#include <optional>

namespace simplestream {

    class JSONParser {
    public:
   /**
    * @brief Fetches and parses the products from a JSON file.
    * @param filename The path to the JSON file containing the products.
    * @return std::optional<rapidjson::Document> The parsed JSON Document
    *         if successful, otherwise an empty std::optional.
    */
    std::optional<rapidjson::Document> fetch_products(const std::string& filename);
    };

}

#endif // JSONPARSER_H