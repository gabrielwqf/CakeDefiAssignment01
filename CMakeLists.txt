cmake_minimum_required(VERSION 3.11)

# set the project name
project(DeFiChainCppEx)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(DEFAULT_BUILD_TYPE "Release")

if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include(FetchContent)
#HTTP lib
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG e53437b79965e5de9e9bef5a3e7ec609587268d6) 
FetchContent_MakeAvailable(cpr)

#json lib
FetchContent_Declare(json 
GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
GIT_PROGRESS TRUE
GIT_SHALLOW TRUE
GIT_TAG v3.10.5)
FetchContent_MakeAvailable(json)

set(BOOST_ROOT boost_1_79_0)
find_package(Boost REQUIRED)

include_directories(includes ${Boost_INCLUDE_DIRS})

file(GLOB SOURCE_FILES "src/*.cpp")
add_executable(run ${SOURCE_FILES} main.cpp)

target_link_libraries(run PRIVATE cpr::cpr)
target_link_libraries(run PRIVATE nlohmann_json::nlohmann_json)



