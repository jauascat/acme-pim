cmake_minimum_required(VERSION 3.29)
project(acme_pim)

set(CMAKE_CXX_STANDARD 17)

add_executable(acme_pim
    main.cpp
        src/terminal.cpp
    src/terminal_implementations.cpp
)