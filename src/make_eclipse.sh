
rm -rf ../_eclipse
mkdir ../_eclipse
cd ../_eclipse

cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../src