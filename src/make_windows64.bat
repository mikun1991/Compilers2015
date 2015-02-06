rm -rf _build64
mkdir _build64
cd _build64

cmake .. -G"Visual Studio 12 2013 Win64" -DCMAKE_BUILD_TYPE=Debug