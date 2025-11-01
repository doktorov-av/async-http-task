cmake_minimum_required(VERSION 3.31)
project(rest_sender)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
        GIT_TAG v0.27.0
)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(httplib json)

file(GLOB source "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(rest_sender
        main.cpp
        ${source}
)

target_include_directories(rest_sender PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(rest_sender PRIVATE
        httplib
        nlohmann_json::nlohmann_json
)
