cmake_minimum_required(VERSION 3.29)
project(acme_pim)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)

add_executable(acme_pim
    main.cpp
    src/io/terminal.cpp
    src/io/terminal_implementations.cpp
    src/db/db_operator.cpp
    src/db/db_setup.cpp
)

target_link_libraries(acme_pim SQLite::SQLite3)