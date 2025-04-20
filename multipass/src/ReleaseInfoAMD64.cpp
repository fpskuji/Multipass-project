#include "ReleaseInfoAMD64.hpp"
#include <algorithm>

namespace simplestream {

    ReleaseInfoAMD64::ReleaseInfoAMD64(const rapidjson::Document& document) {
        check_amd64_products(document);
    }

    void ReleaseInfoAMD64::check_amd64_products(const rapidjson::Document& document) {
        if (document.HasMember("products") && document["products"].IsObject()) {
            for (auto& member : document["products"].GetObject()) {

                std::string product_key = member.name.GetString();

                if (!product_key.empty() &&
                    product_key.size() >= 5 &&
                    product_key.find("amd64") != std::string::npos) {
                    const rapidjson::Value& product = member.value;
                    CloudServerInfo server_info;

                    server_info.server_name = product_key;
                    server_info.aliases = product["aliases"].GetString();
                    server_info.arch = product["arch"].GetString();
                    server_info.os = product["os"].GetString();
                    server_info.release = product["release"].GetString();
                    server_info.release_codename = product["release_codename"].GetString();
                    server_info.release_title = product["release_title"].GetString();
                    server_info.support_eol = product["support_eol"].GetString();
                    server_info.supported = product["supported"].GetBool();
                    server_info.version = product["version"].GetString();

                    const rapidjson::Value& versions = product["versions"];
                    for (auto& version : versions.GetObject()) {
                        VersionInfo version_info;
                        const rapidjson::Value& items = version.value["items"];
                        version_info.version_name = version.name.GetString();

                        for (auto& item : items.GetObject()) {
                            const rapidjson::Value& file = item.value;
                            FType ftype;

                            ftype.name = file["ftype"].GetString();
                            ftype.md5 = file["md5"].GetString();
                            ftype.path = file["path"].GetString();
                            ftype.sha256 = file["sha256"].GetString();
                            ftype.size = file["size"].GetUint();
                            version_info.file.push_front(ftype);
                        }
                        server_info.versions.push_front(version_info);
                    }
                    m_cloud_servers.push_front(server_info);
                }
            }
        }
    }

    std::list<CloudServerInfo> ReleaseInfoAMD64::get_supported_release_list() const {
        std::list<CloudServerInfo> supported_releases;
        
        for (const auto& server : m_cloud_servers) {
            if (server.supported) {
                supported_releases.push_back(server);
            }
        }
        return supported_releases;
    }
    
    std::optional<CloudServerInfo> ReleaseInfoAMD64::get_current_LTS_release() const {
        for (const auto& server : m_cloud_servers) {
            if (!server.release_title.empty() && 
                server.release_title.find(LTS) != std::string::npos) {
                return server;
            }
        }
        return std::nullopt;
    }

    std::optional<std::string> ReleaseInfoAMD64::get_sha256_img(const std::string& alias) const {
        for (const auto& server : m_cloud_servers) {
            if (server.aliases.find(alias) != std::string::npos) {
                for (auto itr = server.versions.rbegin(); itr != server.versions.rend(); ++itr) {
                    for (const auto& file : itr->file) {
                        if (file.name == IMAGE_NAME) {
                            return file.sha256;
                        }
                    }
                }
            }
        }
        return std::nullopt;
    }

}
