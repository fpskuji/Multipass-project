#ifndef IRELEASEINFO_H
#define IRELEASEINFO_H

#include <string>
#include <cstdint>
#include <list>
#include <optional>

namespace simplestream {

    typedef struct {
        std::string name;
        std::string md5;
        std::string path;
        std::string sha256;
        uint32_t size;
    }FType;

    typedef struct {
        std::string version_name;
        std::list<FType> file;
    } VersionInfo;

    typedef struct {
        std::string server_name;
        std::string aliases;
        std::string arch;
        std::string os;
        std::string release;
        std::string release_codename;
        std::string release_title;
        std::string support_eol;
        bool supported;
        std::string version;
        std::list<VersionInfo> versions;
    } CloudServerInfo;
    
    class IReleaseInfo {
    public:
        virtual ~IReleaseInfo() = default;
    
        virtual std::list<CloudServerInfo> get_supported_release_list() const = 0;
        virtual std::optional<CloudServerInfo> get_current_LTS_release() const = 0;
        virtual std::optional<std::string> get_sha256_img(const std::string& alias) const = 0;
    
    protected:
        std::list<CloudServerInfo> m_cloud_servers;
    };
    

}

#endif // IRELEASEINFO_H