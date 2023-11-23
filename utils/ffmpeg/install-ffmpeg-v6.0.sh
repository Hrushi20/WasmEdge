#!/usr/bin/env bash
rm -rf FFmpeg-n6.0 ffmpeg.zip
echo $(pwd)

curl -sL https://github.com/FFmpeg/FFmpeg/archive/refs/tags/n6.0.zip -o ffmpeg.zip

unzip ffmpeg.zip

cd FFmpeg-n6.0
mkdir -p output
./configure --prefix=$(pwd)/output --enable-gpl --enable-nonfree --enable-shared --disable-static

cd ..
echo $(pwd)

#Setting PKG_CONFIG_PATH to be discoverd
PKG_CONFIG_PATH=$(pwd)/WasmEdge/FFmpeg-n6.0/output/lib/pkgconfig cmake -Bbuild_pr2885 -GNinja -DCMAKE_BUILD_TYPE=Release -DWASMEDGE_BUILD_TESTS=ON  -DWASMEDGE_PLUGIN_FFMPEG=ON .