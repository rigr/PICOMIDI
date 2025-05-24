name: Build Pico Firmware

on:
  push:
    branches: [ "main" ]
  pull_request:
    branches: [ "main" ]

env:
  PICO_SDK_PATH: ${{ github.workspace }}/pico-sdk
  PICO_EXTRAS_PATH: ${{ github.workspace }}/pico-extras

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
      with:
        submodules: recursive
        
    - name: Set up Pico SDK
      run: |
        git clone --depth 1 --branch master https://github.com/raspberrypi/pico-sdk.git
        git clone --depth 1 https://github.com/raspberrypi/pico-extras.git
        
    - name: Install dependencies
      run: |
        sudo apt update
        sudo apt install -y cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
        
    - name: Create build directory
      run: mkdir build
      
    - name: Configure CMake
      working-directory: ./build
      run: cmake ..
      
    - name: Build
      working-directory: ./build
      run: make -j4
      
    - name: Upload artifact
      uses: actions/upload-artifact@v4
      with:
        name: picomidi-firmware
        path: build/picomidi.uf2
