cmake_minimum_required(VERSION 3.10)
project(TodoV2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    src/folderops.cpp
    src/opendb.cpp
    src/taskops.cpp
    src/ui.cpp
)

add_executable(todo ${SOURCES})

target_include_directories(todo PRIVATE src)

# Find and link SQLiteCpp (system-wide)
find_package(SQLiteCpp REQUIRED)
target_link_libraries(todo PRIVATE SQLiteCpp)

target_compile_options(todo PRIVATE -Wall -Wextra -Wpedantic)