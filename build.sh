mkdir -p build
cd build
cmake ..
cmake --build .
rm ../run
cp run ../test