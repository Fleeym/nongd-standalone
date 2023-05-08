cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)

project(nongd)

add_subdirectory(libs/minhook)
add_subdirectory(libs/cocos-headers)
add_subdirectory(libs/json)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(IS_MACOS On)
endif()

set(CMAKE_SIZEOF_VOID_P 4)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang AND NOT ${IS_MACOS})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target i386-pc-windows-msvc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target i386-pc-windows-msvc")
    add_definitions("--target=i386-pc-windows-msvc")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    libs/minhook/include
    libs/gd.h/include
    libs/gd.h/
    libs/json/include/nlohmann
)

target_link_libraries(${PROJECT_NAME} minhook cocos2d nlohmann_json::nlohmann_json)