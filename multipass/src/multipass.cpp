#include "ReleaseInfoAMD64.hpp"
#include "jsondownloader.hpp"
#include "jsonparser.hpp"
#include <filesystem>
#include <iostream>


using namespace std;
using namespace simplestream;

// For test only (m_cloud_servers set to public)
void printCloudServerInfo(const CloudServerInfo& server) {
    cout << "Server Name: " << server.server_name << endl;
    cout << "Aliases: " << server.aliases << endl;
    cout << "Architecture: " << server.arch << endl;
    cout << "OS: " << server.os << endl;
    cout << "Release: " << server.release << endl;
    cout << "Release Codename: " << server.release_codename << endl;
    cout << "Release Title: " << server.release_title << endl;
    cout << "Support EOL: " << server.support_eol << endl;
    cout << "Supported: " << (server.supported ? "Yes" : "No") << endl;
    cout << "Version: " << server.version << endl;

    for (const auto& version : server.versions) {
        cout << "  Version Name: " << version.version_name << endl;
        for (const auto& file : version.file) {
            cout << "  File name: " << file.name << endl;
            cout << "  File MD5: " << file.md5 << endl;
            cout << "  File Path: " << file.path << endl;
            cout << "  File SHA256: " << file.sha256 << endl;
            cout << "  File Size: " << file.size << endl;
        }
    }
}
    

int main ()
{
    JSONDownloader downloader;
    JSONParser parser;
    rapidjson::Document document;

    filesystem::create_directories(".simplestream_cache");

    cout << "Downloading JSON information..." << endl;
    downloader.download_JSON_info();

    cout << "Parsing JSON information..." << endl;
    document = parser.fetch_products(FILENAME.data()).value();

    ReleaseInfoAMD64 releaseAMD64Info(document);

    list<CloudServerInfo> supportedReleases = releaseAMD64Info.get_supported_release_list();
    cout << "Supported Releases:" << endl;
    for (const auto& server : supportedReleases) {
        cout << server.release_title << endl;
    }
    cout << "----------------------------------------" << endl;

    cout << "Current LTS Release:" << endl;
    optional<CloudServerInfo> serverInfo = releaseAMD64Info.get_current_LTS_release();
    cout << serverInfo->release_title << endl;
    cout << "----------------------------------------" << endl;

    cout << "SHA256:" << endl;
    optional<string> sha256 = releaseAMD64Info.get_sha256_img("noble");
    if (sha256.has_value()) {
        cout << sha256.value() << endl;
    } else {
        cout << "No sha256 found" << endl;
    }
    cout << "----------------------------------------" << endl;

    return 0;
}