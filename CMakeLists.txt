cmake_minimum_required(VERSION 3.24)

cmake_policy(SET CMP0167 NEW)  # Use Boost config files, no warning

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Prefer target-based includes over global include_directories
# include_directories(src include)  # Can remove this line

find_package(Boost REQUIRED COMPONENTS system)

add_executable(server
    src/main.cpp
    src/server.cpp
    src/store.cpp
    src/protocol.cpp
)

# Add include dirs and link Boost libraries to 'server'
target_include_directories(server PRIVATE
    ${Boost_INCLUDE_DIRS}
    src
    include
)


target_link_libraries(server PRIVATE
    ${Boost_LIBRARIES}
)

add_executable(client
    client/main.cpp
)

target_include_directories(client PRIVATE
    ${Boost_INCLUDE_DIRS}
    src
    include
)


