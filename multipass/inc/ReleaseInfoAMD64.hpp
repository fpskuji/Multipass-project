#ifndef RELEASEINFOAMD64_HPP
#define RELEASEINFOAMD64_HPP
#include "IReleaseInfo.hpp"
#include <rapidjson/document.h>
#include <string>
#include <optional>

namespace simplestream {

    constexpr std::string_view IMAGE_NAME = "disk1.img";
    constexpr std::string_view LTS = "LTS";

    class ReleaseInfoAMD64 : public IReleaseInfo {
    public:
        ReleaseInfoAMD64(const rapidjson::Document& document);
        
        std::list<CloudServerInfo> get_supported_release_list() const override;

        std::optional<CloudServerInfo> get_current_LTS_release() const override;

        std::optional<std::string> get_sha256_img(const std::string& alias) const override;


    private:
        std::list<CloudServerInfo> cloud_servers;

        void check_amd64_products(const rapidjson::Document& document);
    };

}

#endif // RELEASEINFOAMD64_HPP