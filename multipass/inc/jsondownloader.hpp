#ifndef JSONDOWNLOADER_H
#define JSONDOWNLOADER_H

#include <string_view>
#include <cstddef>

/**
 * @namespace simplestream
 * Namespace containing constants and the JSONDownloader class for downloading JSON information.
 */
namespace simplestream {
    /**
     * @brief URL to download the JSON information.
     */
    constexpr std::string_view URL = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
    
    /**
     * @brief Filename to save the downloaded JSON information.
     */
    constexpr std::string_view FILENAME = ".simplestream_cache/releases.json";

    /**
     * @class JSONDownloader
     * @brief Class responsible for downloading JSON information from a specified URL.
     */
    class JSONDownloader {
        public:
            /**
             * @brief Constructor for JSONDownloader.
             */
            JSONDownloader();
            
            /**
             * @brief Destructor for JSONDownloader.
             */
            ~JSONDownloader();
            
            /**
             * @brief Downloads JSON information from the URL and saves it to the specified file.
             */
            void download_JSON_info() const;
        
        private:
            /**
             * @brief Callback function for writing data to a file.
             * @param contents Pointer to the data to be written.
             * @param size Size of each data element.
             * @param nmemb Number of data elements.
             * @param outFile Pointer to the output file stream.
             * @return The number of bytes written.
             */
            static size_t write_callback(void* contents, size_t size, size_t nmemb, std::ofstream* outFile);
    };
}    

#endif // JSONDOWNLOADER_H