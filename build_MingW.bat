if not exist "build" mkdir "build"
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
del "../test/run.exe"
copy run.exe "../test"
copy libcpr.dll "../test"
copy libcurl-d.dll "../test"
copy libzlib.dll "../test"
PAUSE