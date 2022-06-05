cmake_minimum_required(VERSION 3.16.0)
project(circle-game VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set (USR_INCLUDE_DIR "/usr/include")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)


find_package(Boost REQUIRED)

add_executable(server src/server.cpp)

target_include_directories(server PUBLIC
"${CMAKE_SOURCE_DIR}/include"
"${USR_INCLUDE_DIR}"
"${Boost_INCLUDE_DIRS}")


target_link_libraries(server
                      ${Boost_LIBRARIES}
                      Threads::Threads
                      OpenSSL::SSL
                      OpenSSL::Crypto)