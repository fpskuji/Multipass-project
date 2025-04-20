#include "ReleaseInfoAMD64.hpp"
#include "jsondownloader.hpp"
#include "jsonparser.hpp"
#include <filesystem>
#include <iostream>

using namespace std;
using namespace simplestream;


const char* ubuntu_art = R"(

__  __   __                        __                                   
/\ \/\ \ /\ \                      /\ \__                                
\ \ \ \ \\ \ \____   __  __    ___ \ \ ,_\  __  __                       
 \ \ \ \ \\ \ '__`\ /\ \/\ \ /' _ `\\ \ \/ /\ \/\ \                      
  \ \ \_\ \\ \ \L\ \\ \ \_\ \/\ \/\ \\ \ \_\ \ \_\ \                     
   \ \_____\\ \_,__/ \ \____/\ \_\ \_\\ \__\\ \____/                     
    \/_____/ \/___/   \/___/  \/_/\/_/ \/__/ \/___/                      
                   ___    __                                             
 /'\_/`\          /\_ \  /\ \__  __                                      
/\      \   __  __\//\ \ \ \ ,_\/\_\   _____      __       ____    ____  
\ \ \__\ \ /\ \/\ \ \ \ \ \ \ \/\/\ \ /\ '__`\  /'__`\    /',__\  /',__\ 
 \ \ \_/\ \\ \ \_\ \ \_\ \_\ \ \_\ \ \\ \ \L\ \/\ \L\.\_ /\__, `\/\__, `\
  \ \_\\ \_\\ \____/ /\____\\ \__\\ \_\\ \ ,__/\ \__/.\_\\/\____/\/\____/
   \/_/ \/_/ \/___/  \/____/ \/__/ \/_/ \ \ \/  \/__/\/_/ \/___/  \/___/ 
                                         \ \_\                           
                                          \/_/                           


)";

void display_menu() {
    cout << "Options:\n";
    cout << "0 - Exit\n";
    cout << "1 - View all supported releases\n";
    cout << "2 - Get latest LTS release\n";
    cout << "3 - Get the SHA256 of a given Ubuntu release\n";
}
    
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
        cout << "---Version Name: " << version.version_name << endl;
        for (const auto& file : version.file) {
            cout << "------File name: " << file.name << endl;
            cout << "------File MD5: " << file.md5 << endl;
            cout << "------File Path: " << file.path << endl;
            cout << "------File SHA256: " << file.sha256 << endl;
            cout << "------File Size: " << file.size << endl;
        }
    }
    cout << "----------------------------------------" << endl;
}

int main ()
{
    JSONDownloader downloader;
    JSONParser parser;
    rapidjson::Document document;
    list<CloudServerInfo> supportedReleases;
    optional<CloudServerInfo> serverInfo;
    optional<string> sha256;
    int choice = -1;
    string alias;

    filesystem::create_directories(".simplestream_cache");

    cout << "Downloading JSON information..." << endl;
    downloader.download_JSON_info();

    cout << "Parsing JSON information..." << endl;
    document = parser.fetch_products(FILENAME.data()).value();

    ReleaseInfoAMD64 releaseAMD64Info(document);

    while (choice != 0) {
        cout << ubuntu_art << endl;
        display_menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Exiting...\n";
                break;
            case 1:
                supportedReleases = releaseAMD64Info.get_supported_release_list();
                cout << "Supported Releases:" << endl;
                for (const auto& server : supportedReleases) {
                    printCloudServerInfo(server);
                }
                break;
            case 2:
                serverInfo = releaseAMD64Info.get_current_LTS_release();
                cout << "Current LTS Release:" << endl;
                printCloudServerInfo(serverInfo.value());
                break;
            case 3:
                cout << "Please input an alias of the release: \n";
                cin >> alias;
                sha256 = releaseAMD64Info.get_sha256_img(alias);
                if (sha256.has_value()) {
                    cout << "SHA256: " << sha256.value() << endl;
                } else {
                    cout << "No sha256 found" << endl;
                }
                cout << "----------------------------------------" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}