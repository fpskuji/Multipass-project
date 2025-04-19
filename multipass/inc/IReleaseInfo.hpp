#ifndef SIMPLESTREAM_H
#define SIMPLESTREAM_H

#include <string>
#include <cstdint>
#include <vector>
#include <stdbool.h>

namespace simplestream {

    typedef struct {
        std::string md5;
        std::string path;
        std::string sha256;
        uint32_t size;
    }FType;

    typedef struct {
        std::string version_name;
        std::vector<FType> file;
    } VersionInfo;

    typedef struct {
        std::string server_name;
        std::string alias;
        std::string arch;
        std::string os;
        std::string release;
        std::string release_codename;
        std::string release_title;
        std::string support_eol;
        bool supported;
        std::string version;
        std::vector<VersionInfo> versions;
    } CloudServerInfo;
    
    class IReleaseInfo {
    public:
        virtual ~IReleaseInfo() = default;
    
        virtual std::vector<std::string> get_supported_release_list() const = 0;
        virtual std::string get_current_LTS_release() const = 0;
        virtual std::string get_sha256_img(const std::string& release) const = 0;
    
    private:
        std::vector<CloudServerInfo> m_cloud_servers;
    };
    

}

#endif // SIMPLESTREAM_H