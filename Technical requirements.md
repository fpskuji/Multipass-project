
# Technical Requirements

1. **Create an Interface**

2. **Create a Derived Class**
    - Fetches the latest Ubuntu Cloud image information in Simplestreams format.
        - URL: https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json
        - `download_JSON_info()`
            - Download JSON file from URL
        - `fetch_products()`
            - Parse JSON file and put in a container  (class structure should be similar to Simplestreams format)

    - Provides 3 methods:
        - `get_supported_release_list()`
        - `get_current_LTS_release()`
        - `get_sha256_img()`
        - All 3 methods should be accessible via CLI

3. **Use 3rd Party Libraries** (optional but convenient)
    - JSON parser (rapidJSON library)
    - HTTP downloader (libcurl)

4. **Use CMake for Building the Project** with 3 targets:
    - Linux
    - Windows
    - MacOS

5. **Document the Methods**

6. **Create Build Instructions** (`README.md`)

7. **Project should be in a Tarball file**

8. **Upload the Project in a Git Repository**
