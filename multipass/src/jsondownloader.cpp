#include "jsondownloader.hpp"
#include <iostream>
#include <fstream>
#include <curl/curl.h>


namespace simplestream {
    
    JSONDownloader::JSONDownloader() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }
    
    JSONDownloader::~JSONDownloader() {
        curl_global_cleanup();
    }
    

    size_t JSONDownloader::write_callback(void* contents, size_t size, size_t nmemb, std::ofstream* output_file) {
        size_t totalSize = size * nmemb;
        output_file->write(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    
    void JSONDownloader::download_JSON_info() const {
        CURL* curl;
        CURLcode res;
        std::ofstream output_file(FILENAME.data(), std::ios::binary);
    
        if (!output_file.is_open()) {
            std::cerr << "Failed to open file: " << FILENAME << std::endl;
            return;
        }
    
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, URL.data());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output_file);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
    
            if(res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }
        }
    
        output_file.close();
    }
    
}