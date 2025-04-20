# Build instructions
1. **Install CMake:**  
    **Linux(ubuntu)** `sudo apt install cmake`  
    **Windows(Windows Package Manager)** `winget install kitware.cmake`  
    **MacOS**`brew install cmake`
2. **Install libcurl library:**  
    **Linux(ubuntu)** `sudo apt install libcurl4-openssl-dev`  
    **Windows(Windows Package Manager)** `winget install curl`  
    **MacOS**`brew install curl`
3. **Install rapidJSON library:**  
    **Linux(ubuntu)** `sudo apt install rapidjson-dev`  
    **Windows(Windows Package Manager)** `winget install rapidjson`  
    **MacOS**`brew install rapidjson`
4. **Open terminal and navigate to build directory/folder:**  
    `Multipass-project/multipass/build`
5. **Run `cmake ..` to generate the build files**
6. **Run `make` (Note: Install MinGW or Cygwin if you are on Windows environment to be able to run make)**

# How to use
**Run the `Multipass` binary and there is a menu of things the tool can do, enjoy! ;)**
1. View all supported releases
2. Get latest LTS release
3. Get the SHA256 of a given Ubuntu release