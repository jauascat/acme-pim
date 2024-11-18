cmake_minimum_required(VERSION 3.29)
project(acme_pim)

set(CMAKE_CXX_STANDARD 17)

include_directories("sqlite_libs")
link_directories("sqlite_libs")

#find_package(SQLite3 REQUIRED)

add_executable(acme_pim
    main.cpp
    src/database/database.cpp
    src/models/pim.cpp
    src/views/operation.cpp
    src/views/menu.cpp
    src/views/menus/Products/products.cpp
    src/views/app.cpp
    src/models/variant.h
    src/views/menus/Variants/variants.cpp
    src/views/menus/Variants/variants.h
    src/views/menus/Categories/categories.cpp
    src/views/menus/Categories/categories.h
)

# target_link_libraries(acme_pim SQLite:SQLite3)
target_link_libraries(acme_pim sqlite3)