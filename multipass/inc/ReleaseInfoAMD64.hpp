#ifndef RELEASEINFOAMD64_HPP
#define RELEASEINFOAMD64_HPP
#include "IReleaseInfo.hpp"
#include <rapidjson/document.h>
#include <string>
#include <optional>

namespace simplestream {

    constexpr std::string_view IMAGE_NAME = "disk1.img";
    constexpr std::string_view LTS = "LTS";

    /**
     * @brief Class representing release information for AMD64 architecture.
     */
    class ReleaseInfoAMD64 : public IReleaseInfo {
    public:
        /**
         * @brief Constructs a ReleaseInfoAMD64 object from a JSON document.
         * @param document The JSON document containing release information.
         */
        ReleaseInfoAMD64(const rapidjson::Document& document);
        
        /**
         * @brief Retrieves a list of supported cloud server releases.
         * @return A list of CloudServerInfo structure representing supported releases.
         */
        std::list<CloudServerInfo> get_supported_release_list() const override;

        /**
         * @brief Retrieves the current Long Term Support (LTS) release.
         * @return An optional CloudServerInfo structure representing the current LTS release.
         */
        std::optional<CloudServerInfo> get_current_LTS_release() const override;

        /**
         * @brief Retrieves the SHA-256 checksum of the disk1.img associated with a given release alias.
         * @param alias Any alias associated with the server release.
         * @return An optional string containing the SHA-256 checksum.
         */
        std::optional<std::string> get_sha256_img(const std::string& alias) const override;

    private:
        /**
         * @brief Checks and processes AMD64 products from the JSON document.
         * @param document The JSON document containing product information.
         */
        void check_amd64_products(const rapidjson::Document& document);
    };

}

#endif // RELEASEINFOAMD64_HPP
