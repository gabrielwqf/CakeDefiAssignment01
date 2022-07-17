if not exist "build" mkdir "build"
cd build
cmake .. -A x64
cmake --build . --config Release
del "..\test\run.exe"
copy "Release\run.exe" "..\test"
copy "Release\cpr.dll" "..\test"
copy "Release\libcurl.dll" "..\test"
copy "Release\zlib.dll" "..\test"
PAUSE